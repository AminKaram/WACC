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
  // when you prin you should add
  // msg_0:
  //  .word 13
  //  .ascii  "Hello World!\n"
  // msg_1:
  //  .word 5
  //  .ascii  "%.*s\0"
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
void CodeGenVisitor::visit(Expression *node) {
  Identifier *ident      = dynamic_cast<Identifier*>(node);
  FunctionCall *funcCall = dynamic_cast<FunctionCall*>(node);
  Number *number         = dynamic_cast<Number*>(node);
  Boolean *boolean       = dynamic_cast<Boolean*>(node);
  Char *charId           = dynamic_cast<Char*>(node);
  String *stringId       = dynamic_cast<String*>(node);
  Null *null             = dynamic_cast<Null*>(node);
  BinaryOperator *binop  = dynamic_cast<BinaryOperator*>(node);
  ArrayElem *arrayElem   = dynamic_cast<ArrayElem*>(node);
  UnaryOperator *unop    = dynamic_cast<UnaryOperator*>(node);

  if(ident) ident->accept(this);
  if(funcCall) funcCall->accept(this);
  if(number) number->accept(this);
  if(boolean) boolean->accept(this);
  if(charId) charId->accept(this);
  if(stringId) stringId->accept(this);
  if(null) null->accept(this);
  if(binop) binop->accept(this);
  if(arrayElem) arrayElem->accept(this);
  if(unop) unop->accept(this);
}

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


  *output << "  B L" << std::to_string(labelNum) << std::endl;
  labelNum++;
  *output << "L" << std::to_string(labelNum) << ":" << std::endl;
  node->doS->accept(this);
  *output << "L" << std::to_string(labelNum - 1) << ": " << std::endl;
      node->expr->accept(this);
  *output << "  somehow store result of expr into r4 "     << std::endl
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
  node->expr->accept(this);
  //std::string reg1 = getAvailableRegister();
  //std::string reg2 = getAvailableRegister();
	*output <<  
        "p_print_string: " << std::endl <<
        "  PUSH {lr}" << std::endl <<
				"  LDR r1, [register where the message was put in main = r0]" << std::endl <<
				"  ADD r2, r0, #4" << std::endl <<
				"  LDR r0, =msg_1" << std::endl <<
		 		"  ADD r0, r0, #4" << std::endl <<
			 	"  BL printf" << std::endl <<
        "  MOV r0, #0" << std::endl <<
        "  BL fflush" << std::endl <<
        "  POP {pc}" << std::endl;
}

void CodeGenVisitor::visit(PrintlnStatement *node) {
  node->expr->accept(this);
  // visit the print node first ant then:
  *output <<  
        "p_print_string: " << std::endl <<
        "  PUSH {lr}" << std::endl <<
        "  LDR r1, [register where the message was put in main = r0]" << std::endl <<
        "  ADD r2, r0, #4" << std::endl <<
        "  LDR r0, =msg_1" << std::endl <<
        "  ADD r0, r0, #4" << std::endl <<
        "  BL printf" << std::endl <<
        "  MOV r0, #0" << std::endl <<
        "  BL fflush" << std::endl <<
        "  POP {pc}" << std::endl;
  *output <<  
      "p_print_ln: " << std::endl <<
      "  PUSH {lr}" << std::endl <<
      "  LDR r0, =msg_2" << std::endl <<
      "  ADD r0, r0, #4" << std::endl <<
      "  BL puts" << std::endl <<
      "  ADD r0, r0, #4" << std::endl <<
      "  MOV r0, #0" << std::endl <<
      "  BL fflush" << std::endl <<
      "  POP {pc}" << std::endl;
}
void CodeGenVisitor::visit(Number *node) {
  *output << "  LDR R4, =" << node->value << std::endl;
}
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
	*output << "  MOV " << reg << ", " << "#0" << std::endl;
}
