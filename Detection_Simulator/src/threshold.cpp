#include <iostream>
#include <string>
#include "database.h"

void threshold_value(PerceptionSystem* ps, int value)
{
  if(value < 0 || value > 255)
  {
    std::cout << "[ERROR] Threshold value must be between 0 and 255." << std::endl;
    return;
  }
  PerceptionSystem new_ps;
  new_ps.width = 100;
  new_ps.height = 100;
  new_ps.noise_level = 0;
  new_ps.target_count = 0;
  new_ps.avg_brightness = 0;

    for(int y = 0; y < new_ps.height; y++)
    {
      for(int x = 0; x < new_ps.width; x++)
      {
        if(ps->image[y * ps->width + x] > value)
        {
          new_ps.image[y * new_ps.width + x] = 255; // Set to white
        }
        else
        {
          new_ps.image[y * new_ps.width + x] = 0; // Set to black
        }
        new_ps.avg_brightness += new_ps.image[y * new_ps.width + x];
      }
    }
    new_ps.avg_brightness /= (new_ps.width * new_ps.height);
    *ps = new_ps;

    std::cout << "[INFO] Threshold applied (value=" << value << ")" << std::endl;
    show_info(ps);

    img_preview(ps); // Display image preview after reset
}