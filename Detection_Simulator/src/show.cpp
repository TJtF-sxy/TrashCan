#include <iostream>
#include <iomanip>
#include <string>
#include "database.h"

void show_perception_system(const PerceptionSystem* ps)
{
  for(int y = 0; y < ps->height; y++)
  {
    for(int x = 0; x < ps->width; x++)
    {
      std::cout << std::left << std::setw(4) << (int)ps->image[y * ps->width + x];
    }
    std::cout << std::endl;
  }
}
