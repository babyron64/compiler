#include "common.hpp"

namespace cal{

bool is_digit(char c) {
    return ('0' <= c && c <= '9');
}

bool is_letter(char c) {
    return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}

bool is_char(char c) {
    return (is_letter(c) || is_digit(c));
}

bool is_ws(char c) {
    return (c == ' ' || c == '\t');
}

bool is_ret(char c) {
    return (c == '\n');
}

}