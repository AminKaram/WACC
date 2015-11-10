
#include <iostream>
#include "astnode.h"

using namespace std;

extern int yyparse();

extern StatSeq* ast;

int main(int argc, char **argv) {
  yyparse();
  return 0;
}

