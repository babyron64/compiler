/* BNF
    expr -> expr + term     {print('+')}
          | expr - term     {print('-')}
          | term
    term -> term * factor   {print('*')}
          | term / factor   {print('/')}
          | factor
    factor -> (expr)
            | num   {print(num.value)}
            | id    {print(id.lexeme)}
*/

#include <iostream>
#include <string>
#include "common.hpp"
#include "lex_util.hpp"

using namespace cal;
using namespace cal::lexer;
using namespace std;

namespace cal { namespace lexer {

      std::istream* in_stream = &cin;
      std::ostream* out_stream = &cout;
      std::ostream* err_stream = &cerr;

      Token* scan() {
            if (is_ws(peek) || is_ret(peek)) skip_ws();
            if (is_digit(peek)) return scan_num();
            else if (is_letter(peek)) return scan_word();
            else {peek = ' '; return new Token(peek);}
      }

      void init() {
            WordToken wt_true(Tag::T, "true");
            WordToken wt_false(Tag::F, "false");
            reserve(wt_true);
            reserve(wt_false);
      }

}}

int main(){
      lex_loop();
      return 0;
}