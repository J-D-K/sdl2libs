#include <array>
#include <cstdarg>
#include <fstream>

#include "logger.hpp"

namespace
{
    // Log file stream
    std::ofstream s_LogFile;
    // VA Buffer size
    constexpr int VA_BUFFER_SIZE = 0x1000;
}

void logger::init(void)
{
    s_LogFile.open("sdl2Base.txt");
}

void logger::log(const char *format, ...)
{
    // Buffer for va
    std::array<char, VA_BUFFER_SIZE> vaBuffer;

    // Va
    std::va_list vaList;
    va_start(vaList, format);
    vsnprintf(vaBuffer.data(), VA_BUFFER_SIZE, format, vaList);
    va_end(vaList);

    // Write to log
    s_LogFile << vaBuffer.data() << std::endl;
}