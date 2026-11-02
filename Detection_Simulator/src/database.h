#ifndef __DATABASE_H__
#define __DATABASE_H__
#include <map>
#include <string>

#define img_seed 2026
#define FIND_MIN_AREA 2

#define UNDO_HISTORY_SIZE 10

/**命令映射功能 */
enum CmdId{
  CMD_UNKNOWN = 0,
  CMD_INIT,
  CMD_SHOW,
  CMD_NOISE,
  CMD_DENOISE,
  CMD_EXIT,
  CMD_EDGE,
  CMD_RESET,
  CMD_HELP,
  CMD_HISTOGRAM,
  CMD_UNDO,
  CMD_THRESHOLD,
  CMD_FIND,
  CMD_FLIP,
};

/**结构体定义，程序所有用到的结构体都在这 */
typedef struct PerceptionSystem
{
  unsigned char image[10000];
  int width;
  int height;
  int noise_level;
  int avg_brightness;
  int target_count;
  bool is_initialized;
} PerceptionSystem;

extern PerceptionSystem history[];

CmdId parse_command(const char* name);
void init_perception_system(PerceptionSystem* ps);
void noise_perception_system(PerceptionSystem* ps, int noise_level);
void show_perception_system(const PerceptionSystem* ps);
void denoise_perception_system(PerceptionSystem* ps);
void edge_perception_system(PerceptionSystem* ps);
void reset_perception_system(PerceptionSystem* ps);
void print_commands();
void show_vertical_map(const PerceptionSystem* ps);
void undo_perception_system(PerceptionSystem* ps, int* temp_history_idx, int count_cmd, int history_count);
void get_average_brightness(PerceptionSystem* ps);
void show_info(const PerceptionSystem* ps);
void img_preview(const PerceptionSystem* ps);
void threshold_value(PerceptionSystem* ps, int value);
void find(PerceptionSystem *ps);
void flip(PerceptionSystem *ps);

#endif