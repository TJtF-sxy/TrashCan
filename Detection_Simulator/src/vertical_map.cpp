#include <iostream>
#include <string>
#include <iomanip>
#include "database.h"

void show_vertical_map(const PerceptionSystem* ps)
{
  int present_ratio = 100;
  int map[16] = {0};
  for(int x = 0; x < ps->width; x++)
  {
    for(int y = 0; y < ps->height; y++)
    {
      if(ps->image[y * ps->width + x] < 16)
      {
        map[0]++;
        continue;
      }
      int brightness = (int)ps->image[y * ps->width + x] / 16;
      map[brightness]++;
    }
  }
  int start_brtnss = 0, end_brtnss = 15;
  for(int i = 0; i < 16; i++)
  {
    std::cout << std::right << std::setw(4) << start_brtnss << "-" << end_brtnss << ": " ;

    /*for(int k = 0; k < 16; k++)
    {
      std::cout << map[k] << " ";
    }*/

    for(int j = 0; j < map[i]; j++)
    {
      if(j % present_ratio == 0)
      {
        std::cout << "#";
      }
    }
    start_brtnss += 16;
    end_brtnss += 16;
    std::cout << std::endl;
  }
}