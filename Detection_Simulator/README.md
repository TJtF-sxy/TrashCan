# Detection_Simulator —— 感知系统模拟器

一个基于命令行交互的图像处理模拟程序。程序内部维护一张 100×100 的灰度图像（每个像素取值 0–255），通过命令进行初始化、加噪、降噪、边缘检测、二值化、目标查找、翻转、撤销等操作，并用文本形式在终端输出图像预览、直方图等信息。

- 语言/标准：C++17
- 运行环境：Windows 11

---

## 一、已完成的功能（Task）

| 命令            | 对应文件         | 功能说明                                                           |
| --------------- | ---------------- | ------------------------------------------------------------------ |
| init            | Init.cpp         | 初始化 100×100 随机灰度图，计算平均亮度，输出状态信息和 20×10 预览 |
| show            | show.cpp         | 以 4 位定宽打印整幅像素矩阵                                        |
| noise `<n>`     | noise.cpp        | 向图像添加椒盐噪声（n 取值 0–100），并更新噪声水平与平均亮度       |
| denoise         | denoise.cpp      | 5×5 邻域中值滤波降噪，噪声水平降为原来的 30%                       |
| edge            | edge.cpp         | 基于水平/垂直梯度幅值（阈值 100）输出边缘图（`#`/`.`）             |
| histogram       | vertical_map.cpp | 输出亮度直方图（分 16 级，每 100 个像素显示一个 `#`）              |
| threshold `<v>` | threshold.cpp    | 按阈值 v（0–255）二值化：大于 v 置 255（白），否则置 0（黑）       |
| find            | find.cpp         | 4 邻域连通分量标记，查找面积 ≥2 的目标并输出面积                   |
| flip `<h/v/b>`  | flip.cpp         | 水平 / 垂直 / 双向翻转图像                                         |
| reset           | reset.cpp        | 重新生成一幅随机图像（使用固定种子 2024）                          |
| undo            | undo.cpp         | 撤销到上一个状态                                                   |
| help            | parse_cmd.cpp    | 列出所有可用命令                                                   |
| exit            | main.cpp         | 退出程序                                                           |

辅助实现（非独立命令）：

- `get_average_brightness()`（avg_brightness.cpp）：重新计算整幅图像的平均亮度
- `img_preview()`（img_preview.cpp）：生成 20×10 的字符预览
- `show_info()`（Init.cpp）：输出当前状态摘要（尺寸 / 噪声 / 亮度 / 目标数）
- `parse_command()`（parse_cmd.cpp）：字符串命令 → 命令 ID 的映射

---

## 二、程序目前存在的不足

1. **`reset` 后平均亮度显示乱值**
   `reset.cpp` 中局部结构体 `new_ps.avg_brightness` 未初始化就累加（读取未初始化内存，属未定义行为），实测 `reset` 后亮度显示为负数乱值（正常应为 0–255）。
   修复：在 `new_ps.width = 100;` 前加一行 `new_ps.avg_brightness = 0;`（与 `threshold.cpp` 中已写的初始化保持一致）。

2. **超长命令栈缓冲区溢出**
   `char cmd[10]` 没有长度限制，

---

## 三、编译方式

CMake

```bash
cmake -S . -B build
cmake --build build
# 可执行文件位于 build/perception_simulator
```

> 源码目录中已有的 `*.exe` 是历史残留，不要当作当前程序使用；请以上述方式重新编译。

---

## 四、使用方法

运行程序后进入命令行交互模式，先执行 `init` 初始化系统，之后即可输入命令。常用操作示例：

```
init            # 初始化图像
noise 30        # 添加 30% 椒盐噪声
denoise         # 中值滤波降噪
edge            # 输出边缘图
threshold 100   # 按阈值 100 二值化
find            # 查找目标（需先二值化，find 只识别值为 255 的像素）
flip h          # 水平翻转
histogram       # 输出亮度直方图
help            # 查看命令列表
exit            # 退出
```

## 五 注意事项

一定一定规范输入，否则可能会冒出一些奇奇怪怪的问题
