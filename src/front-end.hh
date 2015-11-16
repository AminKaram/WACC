#ifndef FRONT_END_HH
#define FRONT_END_HH
#include "parsing-driver.hh"
#include "ast-node-visitor.hh"

class FrontEnd{
public:
  FrontEnd();
  ~FrontEnd();
  int check(Program*);
  int run(char*);

private:
  ParsingDriver *driver;
  AstNodeVisitor *semanticAnalyzer;
};

#endif // ! FRONT_END_HH
