#include <iostream>
#include <string>
#include "database.h"


PerceptionSystem history[UNDO_HISTORY_SIZE];

void undo_perception_system(PerceptionSystem* ps, int* temp_history_idx, int count_cmd, int history_count)
{
  int history_idx = *temp_history_idx;
  if(history_idx >= UNDO_HISTORY_SIZE /*|| history_idx > count_cmd - 1*/)
  {
    std::cout << "[ERROR] History index out of bounds." << std::endl;
    (*temp_history_idx) = 1;
    return;
  }
  if(history[history_idx].is_initialized == false /*|| history_count <= 1 || history_idx > history_count*/)
  {
    std::cout << "[ERROR] Nothing to undo." << std::endl;
    //(*temp_history_idx) --;
    return;
  }
  *ps = history[history_idx];
  (*temp_history_idx)++;
  std::cout << "[INFO] Undo : load" << std::endl;
  show_info(ps);
  img_preview(ps);
}