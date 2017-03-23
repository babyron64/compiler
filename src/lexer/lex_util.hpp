#ifndef LEX_UTIL_DEFINED

#include <map>

namespace cal { namespace lexer {

extern std::istream* in_stream;
extern std::ostream* out_stream;
extern std::ostream* err_stream;

enum Tag {
    NUM = 256,
    ID,
    T,
    F,
};

class Token {
public:
    const int tag;

    Token(int tag);
};

class NumToken : public Token {
public:
    const int value;

    NumToken(int value);
};

class WordToken : public Token {
public:
    const std::string lexeme;

    WordToken(std::string word);
    WordToken(int tag, std::string word);
};

std::ostream& operator<<(std::ostream& os, const Token t);
std::ostream& operator<<(std::ostream& os, const NumToken t);
std::ostream& operator<<(std::ostream& os, const WordToken t);

extern std::map<std::string, WordToken> words;
extern char peek;
extern int line;

Token* scan();

Token* scan_num();
Token* scan_word();
void skip_ws();

void reserve(const WordToken wt);

char next_char();

void init();
void lex_loop();

}}

#define LEX_UTIL_DEFINED
#endif