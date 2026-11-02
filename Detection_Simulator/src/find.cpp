#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include "database.h"

void find(PerceptionSystem *ps)
{
  bool visited[10000] = {false}; // 用于标记像素是否已被访问
  int target_id = 0; // 目标编号
  for(int y = 0; y < ps->height; y++)
  {
    for(int x = 0; x < ps->width; x++)
    {
      if(ps->image[y * ps->width + x] == 255 && !visited[y * ps->width + x])
      {
        std::stack<std::pair<int, int>> stack;
        stack.push({x, y});
        visited[y * ps->width + x] = true; //标记为已访问
        int area = 0;
        
        int min_x = x, max_x = x, min_y = y, max_y = y; //用于计算当前搜索方向路径边界

        while(!stack.empty())
        {
          //弹出栈顶
          auto [cur_x, cur_y] = stack.top();
          stack.pop();

          //将当前像素添加到面积统计
          area++;
          if(cur_x < min_x) min_x = cur_x;
          if(cur_x > max_x) max_x = cur_x;
          if(cur_y < min_y) min_y = cur_y;
          if(cur_y > max_y) max_y = cur_y;

          //四个搜索方向
          const int dx[4] = {1, -1, 0, 0};
          const int dy[4] = {0, 0, 1, -1};

          //遍历四个方向并将符合条件的像素加入栈中
          for(int i = 0; i < 4; i++)
          {
            int nx = cur_x + dx[i];
            int ny = cur_y + dy[i];

            //边界检查
            if(nx < 0 || nx >= ps->width || ny < 0 || ny >= ps->height)
              continue;

            int img_idx = ny * ps->width + nx;
            if(ps->image[img_idx] == 255 && !visited[img_idx])
            {
              visited[img_idx] = true; //标记为已访问
              stack.push({nx, ny});
            }
          }
        }

        if(area >= FIND_MIN_AREA)
        {
          target_id++;
          std::cout << "[INFO] Target " << target_id << ": " << "center=(" << x << "," << y << "), area=" << area << std::endl;
        }
      }
    }
  }
  if(target_id == 0)
  {
    std::cout << "[INFO] No targets found." << std::endl;
  }
}