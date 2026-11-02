#include <iostream>
#include <math.h>
#include <string>
#include "database.h"

void sort_string(int* string, int length)
{
  for(int i = 0; i < length - 1; i++)
  {
    for(int j = 0; j < length - i - 1; j++)
    {
      if(string[j] > string[j + 1])
      {
        int temp = string[j];
        string[j] = string[j + 1];
        string[j + 1] = temp;
      }
    }
  }
}

void denoise_perception_system(PerceptionSystem* ps)
{
  int border = 2, denoise_range = 5;//距离边界这么多的像素不动+降噪参考值范围
  int start_y = border, end_y = ps->height - border;
  int start_x = border, end_x = ps->width - border;
  PerceptionSystem denoised_ps;

  //运行降噪逻辑
  for(int y = start_y; y < end_y; y++)
  {
    for(int x = start_x; x < end_x; x++)
    {
      int count_range = pow(denoise_range, 2);
      int range_data[count_range];
      for(int i = y - 2; i <= y + 2; i++)
      {
        for(int j = x - 2; j <= x + 2; j++)
        {
          range_data[(i - y + 2) * 5 + (j - x + 2)] = ps->image[i * ps->width + j];
        }
      }
      sort_string(range_data, count_range);
      denoised_ps.image[y * ps->width + x] = (unsigned char)range_data[count_range / 2];
    }
  }

  //将降噪完毕的图像覆盖原图像
  for(int y = start_y; y < end_y; y++)
  {
    for(int x = start_x; x < end_x; x++)
    {
      ps->image[y * ps->width + x] = denoised_ps.image[y * ps->width + x];
    }
  }
  ps->noise_level *= 0.3; // 降噪后噪声水平降低为原来的30%

  get_average_brightness(ps);
  show_info(ps);
}