#include <iostream>
#include <limits>

void ClearBuffer(std::string& message) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << message << std::endl;
}
