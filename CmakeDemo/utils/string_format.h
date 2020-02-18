//
// Created by peter on 2020/2/18.
//

#ifndef CMAKEDEMO_STRING_FORMAT_H
#define CMAKEDEMO_STRING_FORMAT_H

#include <string>
#include <vector>

template <typename ...Args>
inline std::string format_string(const char *format, Args... args)
{
    constexpr size_t old_len = BUFSIZ;
    char buffer[old_len];

    size_t new_len = snprintf(&buffer[0], old_len, format, args...);
    ++ new_len;

    if (new_len > old_len)
    {
        std::vector<char> new_buffer(new_len);
        snprintf(new_buffer.data(), new_len, format, args...);
        return std::string(new_buffer.data());
    }

    return buffer;
}

#endif //CMAKEDEMO_STRING_FORMAT_H
