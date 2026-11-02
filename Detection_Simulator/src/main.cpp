#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "database.h"

static bool init_complete = false;
PerceptionSystem ps;

int history_idx = 1;
bool undo_activate = false, present_activate = false;

int main()
{
  char cmd[10];    
  int count_cmd = 0;      // 记录命令执行次数
  int history_count = 0;    // 记录历史记录数量

  while(1)
  {
    undo_activate = 0;      // 判断命令是否是撤销类命令，若是则不保存历史记录
    present_activate = 0;   //判断命令是否是展示类命令，若是则不保存历史记录
    std::cin >> cmd;

    CmdId id = parse_command(cmd);

    if(id == CMD_INIT)
    {
      std::cout << "[INFO]Perception System Initialized." << std::endl;
      init_perception_system(&ps);
      init_complete = true;
      count_cmd++;
      history_count++;
    }
    else if(id == CMD_EXIT)
    {
      std::cout << "[INFO]Exiting..." << std::endl;
      return 0;
    }
    else if(id == CMD_HELP)
    {
      print_commands();
      continue;
    }
    else if(init_complete == false)
    {
      std::cout << "[ERROR] System not initialized! Please run 'init' first." << std::endl;
      continue;
    }
    else if(id == CMD_UNKNOWN)
    {
      std::cout << "[ERROR] Unknown command." << std::endl;
      continue;
    }

    switch(id)
    {
        case CMD_SHOW:
        {
          show_perception_system(&ps);
          present_activate = true;
          break;
        }
        case CMD_EXIT:
        {
          std::cout << "[INFO] Exiting..." << std::endl;
          return 0;
        }
        case CMD_UNKNOWN:
        {
          std::cout << "[ERROR] Unknown command." << std::endl;
          break;
        }
        case CMD_NOISE:
        {
          int noise_level;
          std::cin >> noise_level;
          noise_perception_system(&ps, noise_level);
          count_cmd++;
          break;
        }
        case CMD_DENOISE:
        {
          denoise_perception_system(&ps);
          count_cmd++;
          break;
        }
        case CMD_EDGE:
        {
          edge_perception_system(&ps);
          present_activate = true;
          break;
        }
        case CMD_RESET:
        {
          reset_perception_system(&ps);
          count_cmd++;
          break;
        }
        case CMD_HELP:
        {
          print_commands();
          present_activate = true;
          break;
        }
        case CMD_HISTOGRAM:
        {
          show_vertical_map(&ps);
          present_activate = true;
          break;
        }
        case CMD_UNDO:
        {
          undo_perception_system(&ps, &history_idx, count_cmd, history_count);
          undo_activate = 1;
          //std::cout<<history_idx<<std::endl;
          break;
        }
        case CMD_THRESHOLD:
        {
          int value;
          std::cin >> value;
          threshold_value(&ps, value);
          count_cmd++;
          break;
        }
        case CMD_FIND:
        {
          find(&ps);
          break;
        }
        case CMD_FLIP:
        {
          flip(&ps);
          break;
        }
    }
    if(undo_activate || present_activate)
    {
      continue;
    }
    int cur_pos = history_idx - 1;
    if (cur_pos < 0) 
    {
        cur_pos = 0;   // 防止历史索引被破坏时越界
    }

    if (cur_pos == 0)
    {
        // 没有撤销过：正常右移，history[0] 让给新状态
        std::move_backward(history, history + 9, history + 10);
    }
    else
    {
        // 撤销过：把 history[cur_pos..9] 左移到 history[1..]，丢掉被跳过的旧状态
        for (int i = 9; i >= cur_pos; i--)
        {
            history[i - cur_pos + 1] = history[i];
        }
    }

    history[0] = ps;     // 写入操作后的新状态
    history_idx = 1;     // 撤销指针重置为 1
    if (history_count < UNDO_HISTORY_SIZE)
    {
      history_count++;
    }
  }
}