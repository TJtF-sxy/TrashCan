#include <iostream>
#include <string>
#include "database.h"
#include <map>
using namespace std;

//映射表
static const std::map<std::string, CmdId> cmd_table = {
    {"init", CMD_INIT},
    {"show", CMD_SHOW},
    {"exit", CMD_EXIT},
    {"noise", CMD_NOISE},
    {"denoise", CMD_DENOISE},
    {"edge", CMD_EDGE},
    {"reset", CMD_RESET},
    {"help", CMD_HELP},
    {"histogram", CMD_HISTOGRAM},
    {"undo", CMD_UNDO},
    {"threshold", CMD_THRESHOLD},
    {"find", CMD_FIND},
    {"flip", CMD_FLIP},
};

void print_commands()
{
    std::cout << "available commands:\n";
    for (const auto& kv : cmd_table) {
        std::cout << "  " << kv.first << "\n";
    }
}

CmdId parse_command(const char* name)
{
    std::string cmd(name);
    auto it = cmd_table.find(cmd);
    if (it != cmd_table.end())
    {
        return it->second;
    }
    return CMD_UNKNOWN;
}