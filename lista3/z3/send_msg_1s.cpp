#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std::chrono_literals;

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "usage: " << argv[0] << " message(s)..." << std::endl;
        return 1;
    }

    std::stringstream stream;
    std::copy(argv + 1, argv + argc, std::ostream_iterator<const char*>(stream, " "));
    std::string text = stream.str();

    while (std::cout << text << std::endl;)
    {
        std::this_thread::sleep_for(1s);
    }
}
