#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <map>
#include "common.hpp"
#include "lex_util.hpp"

using namespace cal;
using namespace std;

namespace cal { namespace lexer {

istream_iterator<char> input;
istream_iterator<char> input_end;
map<string, WordToken> words;

char peek;
int line = 1;

Token::Token(int tag) : tag(tag) {}
NumToken::NumToken(int value) : Token(Tag::NUM), value(value) {}
WordToken::WordToken(string lexeme) : WordToken(Tag::ID, lexeme) {}
WordToken::WordToken(int tag, string lexeme) : Token(tag), lexeme(lexeme) {}

ostream& operator<<(ostream& os, const Token t) {
    os << "t<" << (char)t.tag << ">";
    return os;
}
ostream& operator<<(ostream& os, const NumToken t) {
    os << "n<" << t.tag << ", " << t.value << ">";
    return os;
}
ostream& operator<<(ostream& os, const WordToken t) {
    os << "w<" << t.tag << ", " << t.lexeme << ">";
    return os;
}

Token* scan_word() {
    ostringstream strbuf;
    for(;;peek = next_char()) {
        if (is_char(peek)) strbuf << peek;
        else break;
    }
    string word = strbuf.str();
    auto itr = words.find(word);
    if(itr != words.end())
        return &itr->second;
    else {
        WordToken* wt = new WordToken(word);
        reserve(*wt);
        return wt;
    }
}

Token* scan_num() {
    int num = 0;
    for(;;peek = next_char()) {
        if (is_digit(peek)) num = num * 10 + (peek - '0');
        else break;
    }
    return new NumToken(num);
}

void skip_ws() {
    for(;;peek = next_char()) {
        if (is_ws(peek)) ;
        else if (is_ret(peek)) line++;
        else break;
    }
}

void reserve(const WordToken wt) {
    words.insert(map<string, WordToken>::value_type(wt.lexeme, wt));
}

static void init_util() {
    *in_stream >> noskipws;
    input = istream_iterator<char>(*in_stream);
    input_end = istream_iterator<char>();
}

char next_char() {
    if (input != input_end && *input != eof) return *input++;
    else return eof;
}

void display(Token* t) {
    switch (t->tag) {
        case Tag::NUM: cout << *static_cast<NumToken*>(t) << endl; break;
        case Tag::T:
        case Tag::F:
        case Tag::ID: cout << *static_cast<WordToken*>(t) << endl; break;
        default: cout << *t << endl; break;
    }
}

void lex_loop() {
    init_util();
    init();
    for (peek = next_char();;) {
        if (peek == eof) break;
        auto token = scan();
        display(token);
        delete token;
    }
}

}}