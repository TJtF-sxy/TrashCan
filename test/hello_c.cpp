#include <iostream>

int main()
{
    char Character;
    std::cin >> Character;
    int rst = (int)Character % 2;
    std::cout << rst;
}