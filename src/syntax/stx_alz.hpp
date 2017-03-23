#ifndef STX_ALZ_DEFINED

#include <string>

namespace cal { namespace syntax {
void expr();
void rest();
void term();

int tokenize(int token);

}}

#define STX_ALZ_DEFINED
#endif