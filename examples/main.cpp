#include <iostream>

import NGIN.Util;

int main()
{
    std::cout << NGIN::Util::Format("Hello, {}!", "World") << std::endl;
    return 0; 
}
