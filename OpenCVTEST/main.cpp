#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

namespace fs = std::filesystem;

// 第六阶段：在考核坐标系（左下原点、y 向上）下排序角点
// 输出顺序：左上 → 右上 → 右下 → 左下（顺时针）
static std::vector<cv::Point2f> orderCorners(std::vector<cv::Point2f> pts)
{
    cv::Point2f c(0, 0);
    for (auto& p : pts) { c.x += p.x; c.y += p.y; }
    c.x /= 4; c.y /= 4;

    // 按极角升序（y 向上坐标系下为逆时针）
    std::sort(pts.begin(), pts.end(), [&](const cv::Point2f& a, const cv::Point2f& b) {
        return std::atan2(a.y - c.y, a.x - c.x) < std::atan2(b.y - c.y, b.x - c.x);
    });

    // 找左上角：y 最大，若接近则 x 最小
    int start = 0;
    for (int i = 1; i < 4; ++i) {
        if (pts[i].y > pts[start].y + 1e-3 ||
            (std::abs(pts[i].y - pts[start].y) <= 1e-3 && pts[i].x < pts[start].x)) {
            start = i;
        }
    }

    // 从左上开始，按顺时针（逆时针环的反向）输出
    std::vector<cv::Point2f> out;
    for (int i = 0; i < 4; ++i) out.push_back(pts[(start - i + 4) % 4]);
    return out;
}

int main()
{
    const std::string inputDir  = "input/";
    const std::string outputDir = "out/";
    const std::string debugDir  = "debug/";

    if (!fs::exists(inputDir)) {
        std::cerr << "Input directory does not exist: " << inputDir << std::endl;
        return 1;
    }
    fs::create_directories(outputDir);
    fs::create_directories(debugDir);

    std::vector<fs::path> files;
    for (const auto& entry : fs::directory_iterator(inputDir)) {
        if (!entry.is_regular_file()) continue;
        if (entry.path().extension() == ".png") {
            files.push_back(entry.path());
        }
    }
    std::sort(files.begin(), files.end(),
              [](const fs::path& a, const fs::path& b) {
                  return a.filename().string() < b.filename().string();
              });

    if (files.empty()) {
        std::cout << "input/ is empty" << std::endl;
        return 0;
    }

    const int    cannyLow     = 50;
    const int    cannyHigh    = 150;
    const double minAreaRatio = 0.0005;

    for (const auto& path : files) {
        cv::Mat img = cv::imread(path.string(), cv::IMREAD_COLOR);
        if (img.empty()) {
            std::cerr << "can't read: " << path << std::endl;
            continue;
        }
        const int H = img.rows;

        // ---- 阶段二：灰度 + 边缘 ----
        cv::Mat gray, edges;
        cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
        cv::Canny(gray, edges, cannyLow, cannyHigh);

        // ---- 阶段三：找所有外轮廓（RETR_EXTERNAL 自动忽略内部镂空） ----
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(edges, contours,
                         cv::RETR_EXTERNAL,
                         cv::CHAIN_APPROX_SIMPLE);

        std::vector<std::vector<cv::Point2f>> rects;   // 考核坐标下的 4 个角点
        std::vector<cv::Point2f> centers;              // 用于编号排序

        // ---- 阶段四 + 五：用外接矩形和面积比筛选 ----
        for (const auto& contour : contours) {
            double area = cv::contourArea(contour);
            // 过滤掉噪声碎边缘
            if (area < minAreaRatio * img.cols * img.rows) continue;

            // 拟合最小外接旋转矩形
            cv::RotatedRect rr = cv::minAreaRect(contour);
            double rectArea = double(rr.size.width) * double(rr.size.height);
            if (rectArea < 1e-6) continue;

            // 填充率：大矩形的面积和外接矩形面积非常接近，接近 1.0
            double fillRatio = area / rectArea;
            if (fillRatio < 0.85) continue;   // 排除三角形、圆等非矩形轮廓

            // 排除极细长的线条（虽然你的图里没有）
            double w = rr.size.width, h = rr.size.height;
            double aspect = std::max(w, h) / std::min(w, h);
            if (aspect > 20.0) continue;

            // 取 4 个顶点
            cv::Point2f v[4];
            rr.points(v);

            // ---- 阶段六：转坐标 ----
            std::vector<cv::Point2f> pts;
            for (int i = 0; i < 4; ++i) {
                pts.push_back(cv::Point2f(v[i].x, float(H - 1 - v[i].y)));
            }

            // ---- 阶段六：排序 ----
            pts = orderCorners(pts);

            cv::Point2f c(0, 0);
            for (auto& p : pts) { c.x += p.x; c.y += p.y; }
            c.x /= 4; c.y /= 4;

            rects.push_back(pts);
            centers.push_back(c);
        }

        // ---- 阶段六：按中心 x 升序（从左到右）编号 ----
        std::vector<int> idx(rects.size());
        for (size_t i = 0; i < idx.size(); ++i) idx[i] = int(i);
        std::sort(idx.begin(), idx.end(), [&](int a, int b) {
            return centers[a].x < centers[b].x;
        });

        // ---- 阶段六：画绿框 ----
        for (size_t k = 0; k < idx.size(); ++k) {
            const auto& q = rects[idx[k]];
            std::vector<cv::Point> drawPts;
            for (auto& p : q) {
                drawPts.push_back(cv::Point(cvRound(p.x), cvRound(H - 1 - p.y)));
            }
            cv::polylines(img, std::vector<std::vector<cv::Point>>{drawPts},
                          true, cv::Scalar(0, 255, 0), 2);
        }

        // ---- 阶段六：终端输出 ----
        std::string fname = path.filename().string();
        if (rects.empty()) {
            std::cout << fname << ": null\n";
        } else {
            std::cout << fname << ": ";
            for (size_t k = 0; k < idx.size(); ++k) {
                if (k > 0) std::cout << " | ";
                std::cout << "rect" << (k + 1) << " ";
                const auto& q = rects[idx[k]];
                for (int j = 0; j < 4; ++j) {
                    if (j > 0) std::cout << "; ";
                    std::cout << "(" << cvRound(q[j].x) << ", " << cvRound(q[j].y) << ")";
                }
            }
            std::cout << "\n";
        }

        // ---- 保存输出与调试图 ----
        cv::imwrite(outputDir + fname, img);
        std::string stem = path.stem().string();
        cv::imwrite(debugDir + stem + "_edges.png", edges);
        cv::imwrite(debugDir + stem + "_rects.png", img);
    }

    return 0;
}