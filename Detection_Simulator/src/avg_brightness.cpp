#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "database.h"

void get_average_brightness(PerceptionSystem* ps)
{
    int total_brightness = 0;
    ps->avg_brightness = 0; 
    for(int y = 0; y < ps->height; y++)
    {
        for(int x = 0; x < ps->width; x++)
        {
            total_brightness += ps->image[y * ps->width + x];
        }
    }
    int temp_avg = total_brightness / (ps->width * ps->height);
    ps->avg_brightness = temp_avg;
}