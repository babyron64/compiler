#ifndef COMMON_DEFINED

#include <iostream>
#include <string>

namespace cal {

const int eof = 26;
const int eos = '\n';

bool is_digit(char c);
bool is_letter(char c);
bool is_char(char c);
bool is_ws(char c);
bool is_ret(char c);

template<typename T>
void debug(std::string location, T value, std::string message) {
    std::cout << "debug: @" << location << "\n| value: " << value
        << "\n| " << message << std::endl; 
}

template<typename T>
void debug(std::string location, T value) {
    debug(location, value, "");
}

}

#define COMMON_DEFINED
#endif