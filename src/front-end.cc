#include "front-end.hh"

FrontEnd::FrontEnd() {
  driver           = new ParsingDriver();
  semanticAnalyzer = new SemanticVisitor();
}

FrontEnd::~FrontEnd() {
  delete driver;
  driver = NULL;
  delete semanticAnalyzer;
  semanticAnalyzer = NULL;
}

int FrontEnd::run(char *fileName) {
  int res = driver->parse(fileName);
  if(res) {
    return 100;
  }
  res = check(driver->ast);
  return res;
}

int FrontEnd::check(Program *node) {
	semanticAnalyzer->visit(node);
	return 0;
}

Program* FrontEnd::getProgram() {
  return driver->ast;
}
