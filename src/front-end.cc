#include "front-end.hh"

FrontEnd::FrontEnd() {
  driver = new ParsingDriver();
  semanticAnalyzer = new AstNodeVisitor();
}

FrontEnd::~FrontEnd() {
	delete driver;
	delete semanticAnalyzer;
}

int FrontEnd::run(char *fileName) {
	int res = driver->parse(fileName);
	check(driver->ast);
	if(res) {
		return 100;
	}
	return 0;
}

int FrontEnd::check(Program *node) {
	semanticAnalyzer->visit(node);
	return 0;
}