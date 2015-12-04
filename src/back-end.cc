#include "Back-End.hh"

BackEnd::BackEnd(std::ostream* stream) {
  codeGenerator = new CodeGenVisitor(stream);
}

BackEnd::~BackEnd() {
  delete codeGenerator;
  codeGenerator = NULL;
}

void BackEnd::generateCode(Program* node) {
  codeGenerator->visit(node);
}
