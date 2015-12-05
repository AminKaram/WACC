#include "code-generation-visitor.hh"
#include "parser.hh"
#define tok yy::parser::token::yytokentype

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
std::string CodeGenVisitor::visitAndPrintReg(Expression *node) {
	*output << "MOV R1, \"Hello World\"" << std::endl;
//			    "string:" << std::endl <<
//				".ascii \"Hello Worldn\" " << std::endl;
				
	return "R1";
}
void CodeGenVisitor::visit(PrintStatement *node) {
	std::cout << "print statement" << std::endl;
	*output <<  "PUSH R0" << std::endl <<
				"PUSH R1" << std::endl <<
				"PUSH R7" << std::endl <<
				std::endl <<
				"MOV R7, #4" << std::endl <<
		 		"MOV R0, #1" << std::endl <<
			 	"MOV R2, #12" << std::endl;
			 				 	
	*output <<	"LDR R1, " << visitAndPrintReg(node->expr) << std::endl <<
				"SWI 0" << std::endl <<
				"MOV R7, #1" << std::endl <<
				"SWI 0" << std::endl <<
				"POP R7" << std::endl <<
				"POP R1" << std::endl <<
				"POP R0";
				
}

void CodeGenVisitor::visit(PrintlnStatement *node) {}
void CodeGenVisitor::visit(Number *node) {}
void CodeGenVisitor::visit(Boolean *node) {}
void CodeGenVisitor::visit(Char *node) {}
void CodeGenVisitor::visit(String *node) {}
void CodeGenVisitor::visit(Null *node) {}
void CodeGenVisitor::visit(BinaryOperator *node) {
   int oper = node -> op;
   if (oper == tok::TOK_LOGOR){
        // Implementation code-gen for OR 
   } else if (oper == tok::TOK_LOGAND){
        // Implementation code-gen for AND 
   } else if (oper == tok::TOK_STAR){
        // Implementation code gen for MULTIPLY
   } else if (oper == tok::TOK_SLASH){
        // Implementation code-gen for DIVIDE 
   } else if (oper == tok::TOK_MODULO){
        // Implementation code-gen for MODULO 
   } else if (oper == tok::TOK_PLUS){
        // Implementation code-gen for PLUS 
   } else if (oper == tok::TOK_MINUS){
        // Implementation code-gen for MINUS
   } else if (oper == tok::TOK_LESS){
        // Implementation code-gen for LESS 
   } else if (oper == tok::TOK_LESSEQUALS){
        // Implementation code-gen for LESSEQUALS 
   } else if (oper == tok::TOK_GREATER){
        // Implementation code-gen for GREATER 
   } else if (oper == tok::TOK_GREATEREQUALS){
        // Implementation code-gen for GREATEREQUALS 
   } else if (oper == tok::TOK_EQUALS){
        // Implementation code-gen for EQUALS 
   } else if (oper == tok::TOK_NOTEQUALS){
        // Implementation code-gen for Not EQUAL
   }
 

}
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
	*output << "MOV " << reg << ", " << "0" << std::endl; 
}
