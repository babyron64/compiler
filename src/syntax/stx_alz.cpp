/* BNF
    expr -> term rest
    rest -> + term rest
          | - term rest
          | e
    term -> 0 | 1 | 2 |...| 9
*/

#include <iostream>
#include <fstream>
#include <string>
#include "common.hpp"
#include "stx_alz.hpp"
#include "stx_util.hpp"

using namespace std;
using namespace cal;

namespace cal { namespace syntax {

istream* in_stream = &cin;
ostream* out_stream = &cout;
ostream* err_stream = &cerr;

void entry() {
    expr();
}

void expr() {
    term(); rest();
}

void rest() {
    switch (lookahead) {
        case '+': match('+'); term(); print('+'); rest(); break;
        case '-': match('-'); term(); print('-'); rest(); break;
        case EOS: match(EOS); break;
        case EOF: match(EOF); break;
        default: err_report(SyntaxErr(lookahead, "rest")); break;
    }
}

void term() {
    if (is_digit(lookahead)) {char tmp = lookahead; match(lookahead); print(tmp);}
    else err_report(SyntaxErr(lookahead, "term"));
}

int tokenize(char token) {
    switch (token) {
        case '+':
        case '-':
            return token;
        default:
            if (is_digit(token)) return token;
            else return OTHER;
    }
}

}}

int main() {
    ifstream file;
    file.open("input.txt");
    file >> noskipws;
    cal::syntax::in_stream = &file;
    cal::syntax::syntax_loop();
    return 0;
}