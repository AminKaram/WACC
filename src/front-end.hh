#ifndef FRONT_END_HH
#define FRONT_END_HH
#include "parsing-driver.hh"
#include "semantic-visitor.hh"
#include <string>

class FrontEnd{
public:
  FrontEnd();
  ~FrontEnd();
  int check(Program*);
  int run(std::string fileName);
  Program *getProgram();

private:
  ParsingDriver *driver;
  SemanticVisitor *semanticAnalyzer;
  bool parsed = false;
};

#endif // ! FRONT_END_HH
