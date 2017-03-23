#ifndef STX_UTIL_DEFINED

#include <iostream>
#include <string>

#define START 0
//#define EOF -1
#define EOS -2
#define OTHER -3

namespace cal { namespace syntax {

extern std::istream* in_stream;
extern std::ostream* out_stream;
extern std::ostream* err_stream;

extern char lookahead;

extern void entry();

void match(char token);
int next_token();
int tokenize(char token);

void print(char token);
void print(int token);

class SyntaxErr {
private:
    char lookahead;
    std::string location;
    std::string message;
public:
    SyntaxErr(char lookahead, std::string location);
    SyntaxErr(char lookahead, std::string location, std::string message);
    friend std::ostream& operator<<(std::ostream& os, const SyntaxErr& err);
};

std::ostream& operator<<(std::ostream& os, const SyntaxErr& err);

void err_report(SyntaxErr err);

void init();

void syntax_loop();

}}
#define STX_UTIL_DEFINED
#endif