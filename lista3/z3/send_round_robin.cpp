#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "usage: " << argv[0] << " message(s)..." << std::endl;
        return 1;
    }

    while (true)
    {
        for (int i = 1; i < argc; ++i)
        {
            std::cout << argv[i] << std::endl;
            std::this_thread::sleep_for(1s);
        }
    }
}
