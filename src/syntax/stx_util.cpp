#include <iostream>
#include <iterator>
#include <string>
#include "stx_util.hpp"
#include "common.hpp"

using namespace std;

namespace cal { namespace syntax {

istream_iterator<char> input;
istream_iterator<char> input_end;
char lookahead = START;

void match(char token) {
    if (token == lookahead)
        if (token == EOS || token == EOF) return;
        else lookahead = next_token();
    else err_report(SyntaxErr(lookahead, "match", "token:" + to_string(token)));
}

int next_token() {
    if (input != input_end && *input != eof && *input != eos)
        return tokenize(*input++);
    else if (*input == eos)
        return EOS;
    else
        return EOF;
}

void print(char c) {
    *out_stream << c;
}

void print(int n) {
    *out_stream << n;
}

SyntaxErr::SyntaxErr(char lookahead, string location) :
    SyntaxErr (lookahead, location, "") {}

SyntaxErr::SyntaxErr(char lookahead, string location, string message) :
    lookahead(lookahead), location(location), message(message){}

ostream& operator<<(ostream& os, const SyntaxErr& err) {
    os << "syntax error @ " << err.location << "\nLA:("
        << err.lookahead << "|" << (int)err.lookahead << ") " << err.message;
    return os;
}

void err_report(SyntaxErr err) {
    *err_stream << err << endl;
}

void init() {
    input = istream_iterator<char>(*in_stream);
    input_end = istream_iterator<char>();
    lookahead = START;
}

void syntax_loop() {
    while(true) {
        init();
        if (input == input_end) continue;
        match(START);
        entry();
        cout << endl;
        if (lookahead == EOF)
            break;
    }
}

}}