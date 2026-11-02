#include <iostream>
#include <string>
#include "database.h"

int get_absolute(int value)
{
  return (value < 0) ? -value : value;
}

void edge_perception_system(PerceptionSystem* ps)
{
  for(int y = 0; y < ps->height; y++)
  {
    for(int x = 0; x < ps->width; x++)
    {
      if (x == 0 || x == ps->width-1 || y == 0 || y == ps->height-1)
      {
        std::cout << ".";
        continue;
      }
      int horizontal_gradient = ps->image[y * ps->width + x + 1] - ps->image[y * ps->width + x - 1];
      int vertical_gradient = ps->image[(y + 1) * ps->width + x] - ps->image[(y - 1) * ps->width + x];
      int gradient_magnitude = get_absolute(horizontal_gradient) + get_absolute(vertical_gradient);
      if(gradient_magnitude > 100)
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