#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "database.h"

void img_preview(const PerceptionSystem* ps)
{
    std::cout <<"图像预览 (20x10):" << std::endl;
    for(int y = 0; y < ps->height; y+= 10)
    {
      for(int x = 0; x < ps->width; x+= 5)
      {
        int avg_brightness = 0;
        for(int dy = y; dy < y + 10 && dy < ps->height; dy++)
        {
          for(int dx = x; dx < x + 5 && dx < ps->width; dx++)
          {
            avg_brightness += ps->image[dy * ps->width + dx];
          }
        }
        avg_brightness /= 50;
        if(avg_brightness > 127) // 检测是否超过阈值
        {
          std::cout << "#";
        }
        else
        {
          std::cout << ".";
        }
      }
      std::cout << std::endl;
    }
}