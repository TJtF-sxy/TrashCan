#include <iostream>
#include <string>
#include "database.h"

void noise_perception_system(PerceptionSystem* ps, int noise_level)
{
  if(noise_level < 0 || noise_level > 100)
  {
    std::cout << "[ERROR] Noise level must be between 0 and 100." << std::endl;
    return;
  }
  ps->noise_level += noise_level * (100-ps->noise_level) / 100; // 计算新的噪声水平
  for(int y = 0; y < ps->height; y++)
  {
    for(int x = 0; x < ps->width; x++)
    {
      int n = rand() % 101; // 生成0到100之间的随机数
      if(n < noise_level)
      {
        int color = (rand() % 2 == 0) ? 0 : 1;
        ps->image[y * ps->width + x] = (unsigned char)(color * 255);
      }
    }
  }
  get_average_brightness(ps);
  show_info(ps);
}