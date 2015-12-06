#include "code-generation-visitor.hh"

CodeGenVisitor::CodeGenVisitor(std::ostream* stream) {
  output   = stream;
  regTable = new std::map<std::string, bool>();
}

CodeGenVisitor::~CodeGenVisitor() { }

void CodeGenVisitor::visit(ASTnode *node) {
}

void CodeGenVisitor::visit(Program *node) {
  *output << ".text" << std::endl << std:: endl
          << ".global main" << std::endl;

  node->functions->accept(this);

  *output << "main:"       << std::endl
          << "  PUSH {lr}" << std::endl;


  node->statements->accept(this);
  *output << "  LDR R0, =0" << std::endl
          << "  POP {pc}" << std::endl
          << "  .ltorg"   << std::endl;

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
void CodeGenVisitor::visit(FunctionDeclaration *node) {
  *output << node->id->id.append("_").append(node->id->id).append(":")
          << std::endl
          << "  PUSH {lr}" << std::endl;
  node->block->accept(this);
  *output << "  POP {pc}" << std::endl
          << "  .ltorg"   << std::endl;


}
void CodeGenVisitor::visit(FunctionCall *node) {}
void CodeGenVisitor::visit(Assignment *node) {}
void CodeGenVisitor::visit(FreeStatement *node) {}

void CodeGenVisitor::visit(ReturnStatement *node) {

  node->expr->accept(this);
  *output << "  somehow store result of expr into r4" << std::endl
          << "  Mov R0, R4" << std::endl;

}

void CodeGenVisitor::visit(ExitStatement *node) {
  node->expr->accept(this);

  *output  << "  somehow store result of expr into r4" << std::endl
           << "  MOV R0, R4" << std:: endl
           << "  BL exit"    << std::endl;
}

void CodeGenVisitor::visit(BeginStatement *node) {}

void CodeGenVisitor::visit(IfStatement *node) {
  node->expr->accept(this);
  *output << "  somehow store result of expr into r4 " << std::endl
          << "  CMP R4, #0"                            << std::endl
          << "  BEQ L" << std::to_string(labelNum)     << std::endl;
  labelNum++;
  node->thenS->accept(this);

  *output << "  B L"  << std::to_string(labelNum)              << std::endl
          << "L"      << std::to_string(labelNum - 1)   << ":" << std::endl;

  node->elseS->accept(this);

  *output << "L" << std::to_string(labelNum) << ":"  << std::endl;
  labelNum--;
}

void CodeGenVisitor::visit(WhileStatement *node) {
  node->expr->accept(this);

  *output << "  B L" << std::to_string(labelNum) << std::endl;
  labelNum++;
  *output << "L" << std::to_string(labelNum) << ":" << std::endl;
  node->doS->accept(this);
  *output << "L" << std::to_string(labelNum - 1) << ": " << std::endl
          << "  somehow store result of expr into r4 "     << std::endl
          << "  CMP R4, #1"                                << std::endl
          << "  BEQ L" << std::to_string(labelNum)         << std::endl;
}

void CodeGenVisitor::visit(ReadStatement *node) {}

std::string CodeGenVisitor::visitAndPrintReg(Expression *node) {
	*output << "  MOV R1, \"Hello World\"" << std::endl;
//			    "string:" << std::endl <<
//				".ascii \"Hello Worldn\" " << std::endl;

	return "R1";
}

void CodeGenVisitor::visit(PrintStatement *node) {
	*output <<  "  PUSH R0" << std::endl <<
				"  PUSH R1" << std::endl <<
				"  PUSH R7" << std::endl <<
				std::endl <<
				"  MOV R7, #4" << std::endl <<
		 		"  MOV R0, #1" << std::endl <<
			 	"  MOV R2, #12" << std::endl;

	*output <<	"  LDR R1, " << visitAndPrintReg(node->expr) << std::endl <<
				"  SWI 0" << std::endl <<
				"  MOV R7, #1" << std::endl <<
				"  SWI 0" << std::endl <<
				"  POP R7" << std::endl <<
				"  POP R1" << std::endl <<
				"  POP R0";

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

void CodeGenVisitor::freeRegister(std::string reg) {
	regTable->find(reg)->second = true;
	*output << "  MOV " << reg << ", " << "0" << std::endl;
}
