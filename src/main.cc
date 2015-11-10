#include <iostream>
#include "astnode.hh"

using namespace std;

extern int yyparse();

extern StatSeq* ast;

int main(int argc, char **argv) {
  yyparse();
  return 0;
}

