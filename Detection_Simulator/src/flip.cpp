#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "database.h"

void flip(PerceptionSystem* ps)
{
  char flip_direction;
  std::cin>> flip_direction;
  if(flip_direction == 'h')
  {
    for (int y = 0; y < ps->height; ++y)
    {
      for (int x = 0; x < ps->width / 2; ++x)
      {
        int opposite_x = ps->width - 1 - x;
        std::swap(ps->image[y * ps->width + x], ps->image[y * ps->width + opposite_x]);
      }
    }
    std::cout << "[INFO] Image flipped horizontally." << std::endl;
    //return;
  }
  else if(flip_direction == 'v')
  {
    for (int y = 0; y < ps->height / 2; ++y)
    {
      for (int x = 0; x < ps->width; ++x)
      {
        int opposite_y = ps->height - 1 - y;
        std::swap(ps->image[y * ps->width + x], ps->image[opposite_y * ps->width + x]);
      }
    }
    std::cout << "[INFO] Image flipped vertically." << std::endl;
    //return;
  }
  else if(flip_direction == 'b')
  {
    for (int y = 0; y < ps->height; ++y)
    {
      for (int x = 0; x < ps->width / 2; ++x)
      {
        int opposite_x = ps->width - 1 - x;
        std::swap(ps->image[y * ps->width + x], ps->image[y * ps->width + opposite_x]);
      }
    }
    for (int y = 0; y < ps->height / 2; ++y)
    {
      for (int x = 0; x < ps->width; ++x)
      {
        int opposite_y = ps->height - 1 - y;
        std::swap(ps->image[y * ps->width + x], ps->image[opposite_y * ps->width + x]);
      }
    }
    std::cout << "[INFO] Image flipped both horizontally and vertically." << std::endl;
  }
  else
  {
    std::cout << "[ERROR] Invalid flip direction. Use 'h' for horizontal or 'v' for vertical." << std::endl;
    return;
  }
  show_info(ps);
  img_preview(ps); // Display image preview after flip
}