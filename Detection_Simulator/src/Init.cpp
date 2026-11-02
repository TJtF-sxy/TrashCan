#include <iostream>
#include <string>
#include "database.h"

void init_perception_system(PerceptionSystem* ps)
{
    ps->width = 100;
    ps->height = 100;
    ps->target_count = 0;
    ps->noise_level = 0;
    ps->target_count = 0;
    // Initialize the image array to nullptr
    srand(img_seed);

    for(int y = 0; y < ps->height; y++)
    {
      for(int x = 0; x < ps->width; x++)
      {
        ps->image[y * ps->width + x] = (unsigned char)(rand() % 256); // Random pixel value between 0 and 255
        ps->avg_brightness += ps->image[y * ps->width + x];
      }
    }

    ps->avg_brightness /= (ps->width * ps->height);
    ps->is_initialized = true;
    show_info(ps);                  //显示信息摘要

    //显示图像预览
    img_preview(ps);
}

void show_info(const PerceptionSystem* ps)
{
    std::cout << "[INFO] "<< "Status: " << ps->width << "x" << ps->height 
    << " noise= " << ps->noise_level 
    << " brightness: " << ps->avg_brightness 
    << " targets= " << ps->target_count << std::endl;
}