#ifndef BACK_END_HH
#define BACK_END_HH
#include "code-generation-visitor.hh"

class BackEnd{
public:
  BackEnd(std::ostream* stream);
  ~BackEnd();

  void generateCode(Program* node);

private:
  CodeGenVisitor *codeGenerator;
};

#endif // ! BACKT_END_HH
