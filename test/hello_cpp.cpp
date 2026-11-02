#include <iostream>
#include <vector>
#include <string>

int main()
{
    int a, b;
    std::cin >> a >> b;
    std::cout << a / 10 << " " << b * 10 << " " << 10000 - a / 10 - b * 10 << std::endl;
    return 0;
}