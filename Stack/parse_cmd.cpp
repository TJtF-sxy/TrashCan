#include <iostream>
#include <string>
#include <algorithm>
#include "stack.h"
#include <map>

//映射表
static const std::map<std::string, CmdId> cmd_table = {
    {"unknown", CMD_UNKNOWN},
    {"push", CMD_PUSH},
    {"pop", CMD_POP},
    {"query", CMD_QUERY},
    {"size", CMD_SIZE}
};

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