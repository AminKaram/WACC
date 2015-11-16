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
	if(res) {
		return 100;
	}
	//res = check(driver->ast);
	return res;
}

int FrontEnd::check(Program *node) {
	semanticAnalyzer->visit(node);
	return 0;
}
