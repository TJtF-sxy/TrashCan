#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <string>

namespace fs = std::filesystem;   // 简化 std::filesystem 的写法

int main()
{
    // 本地测试用相对路径；交付到 Ubuntu 考核环境时改成 "/input/" 和 "/out/"
    const std::string inputDir  = "input/";
    const std::string outputDir = "out/";
    const std::string debugDir  = "debug/";

    // 1. 检查输入目录是否存在
    if (!fs::exists(inputDir)) {
        std::cerr << "Input directory does not exist: " << inputDir << std::endl;
        return 1;
    }

    // 2. 创建输出目录（已存在也不会报错）
    fs::create_directories(outputDir);
    fs::create_directories(debugDir);

    // 3. 收集 input/ 下所有 .png 文件（不递归子目录）
    std::vector<fs::path> files;
    for (const auto& entry : fs::directory_iterator(inputDir)) {
        if (!entry.is_regular_file()) continue;          // 跳过子目录
        if (entry.path().extension() == ".png") {        // 只留 .png
            files.push_back(entry.path());
        }
    }

    // 4. 按文件名升序排列，满足考核输出顺序要求
    std::sort(files.begin(), files.end(),
              [](const fs::path& a, const fs::path& b) {
                  return a.filename().string() < b.filename().string();
              });

    if (files.empty()) {
        std::cout << "input/ is empty" << std::endl;
        return 0;
    }

    // 5. 逐个读取并原样保存
    const int cannylow = 50;
    const int cannyhigh = 150;

    for (const auto& path : files) {
        cv::Mat img = cv::imread(path.string(), cv::IMREAD_COLOR);

        // 读图失败要检查，否则后面用空 Mat 会出错
        if (img.empty()) {
            std::cerr << "can't read: " << path << std::endl;
            continue;
        }

        cv::Mat gray;
        cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

        cv::Mat edges;
        cv::Canny(gray, edges, cannylow, cannyhigh);

        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(edges, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        cv::Mat contourVis(img.size(), CV_8UC3, cv::Scalar(255,255,255));
        cv::RNG rng(12345);
        for(size_t i = 0; i < contours.size(); i++) {
            cv::Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
            cv::drawContours(contourVis, contours, i, color, 2);
        }

        std::string stem = path.stem().string();   // 不含扩展名的文件名
        cv::imwrite(debugDir + stem + "_gray.png",  gray);
        cv::imwrite(debugDir + stem + "_edges.png", edges);
        cv::imwrite(debugDir + stem + "_contours.png", contourVis);
        cv::imwrite(outputDir + path.filename().string(), img);

        std::string outPath = outputDir + path.filename().string();
        // cv::imwrite(outputDir + path.filename().string(), img);
        if (!cv::imwrite(outPath, img)) {
            std::cerr << "can't write: " << outPath << std::endl;
            continue;
        }

        std::cout << path.filename().string() << ": processed" << std::endl;
    }

    return 0;
}