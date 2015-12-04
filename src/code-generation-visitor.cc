#include "code-generation-visitor.hh"

CodeGenVisitor::CodeGenVisitor(std::ostream* stream) {
  output   = stream;
  regTable = new std::map<std::string, bool>();
}

CodeGenVisitor::~CodeGenVisitor() { }

void CodeGenVisitor::visit(ASTnode *node) {
}

void CodeGenVisitor::visit(Program *node) {
  node->functions->accept(this);
  node->statements->accept(this);
}

void CodeGenVisitor::visit(AssignRhs *node) {}
void CodeGenVisitor::visit(AssignLhs *node) {}
void CodeGenVisitor::visit(Expression *node) {}

void CodeGenVisitor::visit(StatSeq *node) {
  for(int i = 0; i < node->statements.size(); i++) {
    (node->statements)[i]->accept(this);
  }
}
void CodeGenVisitor::visit(FunctionDecList *node) {
  for(int i = 0; i < node->funcs.size(); i++) {
    (node->funcs)[i]->accept(this);
  }
}
void CodeGenVisitor::visit(IntegerType *node) {}
void CodeGenVisitor::visit(BoolType *node) {}
void CodeGenVisitor::visit(CharType *node) {}
void CodeGenVisitor::visit(StringType *node) {}
void CodeGenVisitor::visit(ArrayType *node) {}
void CodeGenVisitor::visit(PairType *node) {}
void CodeGenVisitor::visit(VariableDeclaration *node) {}
void CodeGenVisitor::visit(FunctionDeclaration *node) {}
void CodeGenVisitor::visit(FunctionCall *node) {}
void CodeGenVisitor::visit(Assignment *node) {}
void CodeGenVisitor::visit(FreeStatement *node) {}
void CodeGenVisitor::visit(ReturnStatement *node) {}
void CodeGenVisitor::visit(ExitStatement *node) {}
void CodeGenVisitor::visit(BeginStatement *node) {}
void CodeGenVisitor::visit(IfStatement *node) {}
void CodeGenVisitor::visit(WhileStatement *node) {}
void CodeGenVisitor::visit(ReadStatement *node) {}
void CodeGenVisitor::visit(PrintStatement *node) {
	*output <<  "PUSH R0" << std::endl <<
				"PUSH R1" << std::endl <<
				std::endl <<
				"MOV R7, #4" << std::endl <<
		 		"MOV R0, #1" << std::endl <<
			 	"MOV R2, #12" << std::endl <<
				"LDR R1, =string" << std::endl <<
				"SWI 0" << std::endl <<
				"MOV R7, #1" << std::endl <<
				"SWI 0" << std::endl <<
				".data" << std::endl <<
			  "string:" << std::endl <<
				" .ascii \"Hello World.\" " << std::endl <<
				std::endl <<
				"POP R1" << std::endl <<
				"POP R0";
				
}

void CodeGenVisitor::visit(PrintlnStatement *node) {}
void CodeGenVisitor::visit(Number *node) {}
void CodeGenVisitor::visit(Boolean *node) {}
void CodeGenVisitor::visit(Char *node) {}
void CodeGenVisitor::visit(String *node) {}
void CodeGenVisitor::visit(Null *node) {}
void CodeGenVisitor::visit(BinaryOperator *node) {}
void CodeGenVisitor::visit(Identifier *node) {}
void CodeGenVisitor::visit(ArrayElem *node) {}
void CodeGenVisitor::visit(PairElem *node) {}
void CodeGenVisitor::visit(ArrayLiter *node) {}
void CodeGenVisitor::visit(NewPair *node) {}
void CodeGenVisitor::visit(UnaryOperator *node) {}

void CodeGenVisitor::defineLabel(String label) {}

void CodeGenVisitor::populateRegMap() {
	for (int i = 0; i < MAX_REG_NUMBER - 1; ++i) {
		regTable->insert(std::pair <std::string, bool> 
										(std::string("R" + i), true));
	}  
}

std::string CodeGenVisitor::getAvailableRegister() {
	for (auto it = regTable->begin(); it != regTable->end(); ++it) {
		if(it->second) {
			it->second = false;
			return it->first;
		}
	}
	std::cerr << "ERROR. There are no available registers";
}


