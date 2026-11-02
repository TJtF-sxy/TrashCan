#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
//#include "stack.h"

int main(void)
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int count_data;
  std::cin >> count_data;
  while(count_data > 0)
  {
    std::stack<unsigned long long> stack;
    int count_cmd;
    std::cin >> count_cmd;
    
    while(count_cmd--)
    {
      std::string cmd;
      std::cin >> cmd;
      //CmdId id = parse_command(cmd);

        if(cmd == "push")
        {
          unsigned long long value = 0;          
          std::cin >> value;
          stack.push(value);
        }
        else if(cmd == "pop")
        {
          if(stack.empty())
          {
            std::cout << "Empty" << '\n';
            continue;
          }
          stack.pop();
        }
        else if(cmd == "query")
        {
          if(stack.empty())
          {
            std::cout << "Anguei!" << '\n';
            continue;
          }
          else
          {
            std::cout << stack.top() << '\n';
          }
        }
        else if(cmd == "size")
        {
          /*if(stack.empty())
          {
            std::cout << 0 << std::endl;
            continue;
          }*/
          int stack_size = stack.size();
          std::cout << stack_size << '\n';
        }
        else
        {
          std::cerr << "Unknown command!" << '\n';
        }
      //count_cmd--;
    }
    count_data--;
  }
  return 0;
}