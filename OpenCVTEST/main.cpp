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

    // 1. 检查输入目录是否存在
    if (!fs::exists(inputDir)) {
        std::cerr << "输入目录不存在: " << inputDir << std::endl;
        return 1;
    }

    // 2. 创建输出目录（已存在也不会报错）
    fs::create_directories(outputDir);

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
        std::cout << "input/ 下没有 PNG 文件" << std::endl;
        return 0;
    }

    // 5. 逐个读取并原样保存
    for (const auto& path : files) {
        cv::Mat img = cv::imread(path.string(), cv::IMREAD_COLOR);

        // 读图失败要检查，否则后面用空 Mat 会出错
        if (img.empty()) {
            std::cerr << "无法读取: " << path << std::endl;
            continue;
        }

        std::string outPath = outputDir + path.filename().string();
        if (!cv::imwrite(outPath, img)) {
            std::cerr << "无法写入: " << outPath << std::endl;
            continue;
        }

        std::cout << path.filename().string() << ": 已处理" << std::endl;
    }

    return 0;
}