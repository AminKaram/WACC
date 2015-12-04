#ifndef FRONT_END_HH
#define FRONT_END_HH
#include "parsing-driver.hh"
#include "semantic-visitor.hh"

class FrontEnd{
public:
  FrontEnd();
  ~FrontEnd();
  int check(Program*);
  int run(char*);
  Program *getProgram();

private:
  ParsingDriver *driver;
  AstNodeVisitor *semanticAnalyzer;
  bool parsed = false;
};

#endif // ! FRONT_END_HH
