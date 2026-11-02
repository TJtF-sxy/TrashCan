#include <iostream>
#include <string>
#include "database.h"

void reset_perception_system(PerceptionSystem* ps)
{
    PerceptionSystem new_ps;
    new_ps.width = 100;
    new_ps.height = 100;
    new_ps.noise_level = 0;
    new_ps.target_count = 0;
    new_ps.avg_brightness = 0;
    // Initialize the image array to nullptr
    srand(2024);

    for(int y = 0; y < new_ps.height; y++)
    {
      for(int x = 0; x < new_ps.width; x++)
      {
        new_ps.image[y * new_ps.width + x] = (unsigned char)(rand() % 256); // Random pixel value between 0 and 255
        new_ps.avg_brightness += new_ps.image[y * new_ps.width + x];
      }
    }
    new_ps.avg_brightness /= (new_ps.width * new_ps.height);
    *ps = new_ps;

    std::cout << "[INFO]Perception System Reset Complete." << std::endl;
    show_info(ps);

    img_preview(ps); // Display image preview after reset
}