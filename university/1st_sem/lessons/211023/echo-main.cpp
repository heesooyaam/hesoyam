#include <iostream>

int main(int argc, const char** argv)
{
    for(size_t i = 1; i < argc; ++i)
    {
        std::cout << argv[i];
        if(i != argc - 1)
        {
            std::cout << ' ';
        }
    }
    std::cout << std::endl;
}