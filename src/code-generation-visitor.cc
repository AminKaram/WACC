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

void CodeGenVisitor::visit(AssignRhs *node) {
  ArrayLiter *arrayLiter = dynamic_cast<ArrayLiter*>(node);
  NewPair *newPair       = dynamic_cast<NewPair*>(node);
  Expression *expr       = dynamic_cast<Expression*>(node);
  PairElem *pairElem     = dynamic_cast<PairElem*>(node);

  if(arrayLiter) arrayLiter->accept(this);
  if(newPair) newPair->accept(this);
  if(expr) expr->accept(this);
  if(pairElem) pairElem->accept(this);
}
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
void CodeGenVisitor::visit(VariableDeclaration *node) {
// simpliest version for implementing variable declaration
  *output<< "SUB sp, sp, #" /*<< typeSize*/ << std::endl
         << "MOV r0, #" /*<< the right hand side value*/ << std::endl
         << "STR r0 [sp]" << std::endl
         << "ADD sp, sp, #" /*<< typeSize*/ << std::endl
         << "MOV r0 #0" << std::endl;

// effective version of variable dec(USED IN DECLARING MULTIPLE VARIABLE)
// let x be sum of the memory size of type in each assignment statement for all of 
// the statement
// SUB sp, sp, x
// MOV r0, #value of first assign
// STR r0, [sp, x - memory size of first assignment type]
// repeat until all assignment done 
// ADD sp, sp, x
// See many variables declaration example for more information

  
}
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
  std::string stringToPrint;
  
  TypeId *type = node->expr->type;
  
  Number *number         = dynamic_cast<Number*>(node->expr);
  Boolean *boolean       = dynamic_cast<Boolean*>(node->expr);
  Char *charId           = dynamic_cast<Char*>(node->expr);
  String *stringId       = dynamic_cast<String*>(node->expr);
  Null *null             = dynamic_cast<Null*>(node->expr);
  
  if(number) number->
  if(boolean) boolean->accept(this);
  if(charId) charId->accept(this);
  if(stringId) stringId->accept(this);
  
  print(IntTypeId type){
	*output << "msg_0:" << std::endl <<
             "  .word 13" << std::endl <<
             "  .ascii " << stringToPrint << std::endl <<
             "msg_1:" << std::endl <<
             "  .word 5" << std::endl <<
             "  .ascii  \"%.*s\0\"";
  }
  
  //std::string reg1 = getAvailableRegister();
  //std::string reg2 = getAvailableRegister();
  
	output.seekp(0 + 6); // first line .data\n
	
  *output << "msg_0:" << std::endl <<
             "  .word 13" << std::endl <<
             "  .ascii " << stringToPrint << std::endl <<
             "msg_1:" << std::endl <<
             "  .word 5" << std::endl <<
             "  .ascii  \"%.*s\0\"";
	
	*output <<  
        "p_print_string: " << std::endl <<
        "  PUSH {lr}" << std::endl <<
			  "  LDR r1, [r0]" << std::endl <<
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
        "  LDR r1, [r0]" << std::endl <<
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
void CodeGenVisitor::visit(Boolean *node) {
  *output << "  MOV R4, #" << node->value << std::endl;
}
void CodeGenVisitor::visit(Char *node) {
  *output << "  MOV R4, #'" << node->value  << "'" << std::endl;
}
void CodeGenVisitor::visit(String *node) {}
void CodeGenVisitor::visit(Null *node) {}

void CodeGenVisitor::visit(BinaryOperator *node) {
   int oper = node -> op;
         std:: string firstReg = getAvailableRegister();
         std:: string secondReg = getAvailableRegister();

   if(oper == tok::TOK_LOGOR || oper == tok::TOK_LOGAND){
         *output << "LDRSB "<< firstReg /* << "[address where first value
         is stored]" (e.g. [sp])*/ << std::endl; 
         *output << "LDRSB "<< secondReg /* << "[address where second 
         value is stored] (e.g. [sp , #1] )" */ << std::endl;

      if (oper == tok::TOK_LOGOR){
      //Implementation code-gen for OR 
          
         *output << "ORR "<< firstReg << " " << firstReg << " " <<secondReg    
                 << std:: endl
                 << "MOV R0 " << firstReg;
    
       } else if (oper == tok::TOK_LOGAND){
      //Implementation code-gen for AND      
         *output << "AND "<< firstReg << " " << firstReg << " " <<secondReg    
                 << std:: endl
                 << "MOV R0 " << firstReg;
      }      
   } else if (oper >= tok::TOK_STAR && oper <= tok::TOK_NOTEQUALS){
   
             *output << "LDR "<< firstReg /* << "[address where first
             operand is stored]" (e.g. [sp])*/ << std::endl; 
             *output << "LDR "<< secondReg /* << "[address where second
             operand is stored] (e.g. [sp , #4] )" */ << std::endl;
           if(oper == tok :: TOK_STAR){
              //Implementation code gen for MULTIPLY

             *output << "SMULL "<< firstReg << " " << secondReg << " " 
             <<firstReg << " " << secondReg << std:: endl
                     
            << "MOV R0 " << firstReg;

        // Need to add the error code in


           } else if (oper == tok::TOK_SLASH){

        //Implementation code-gen for DIVIDE 


        // not sure about the following assembly code from here
        // Need to add the error code in


           } else if (oper == tok::TOK_MODULO){
         //Implementation code-gen for MODULO 
        // not sure about the following assembly code from here
        // Need to add the error code in

           } else if (oper == tok::TOK_PLUS){
        // Implementation code-gen for PLUS 
             *output << "ADDS "<< firstReg <<" "<< firstReg <<" "
             << secondReg << std::endl
                     //<< "BELVS p_throw_overflow_error"<< std::endl
                     << "MOV R0 "<< firstReg << std::endl;
                     
        // Need to add the error code in

           } else if (oper == tok::TOK_MINUS){
         // Implementation code-gen for MINUS
             *output << "SUBS "<< firstReg <<" "<< firstReg <<" "
             << secondReg << std::endl
                     << "MOV R0 "<< firstReg << std::endl;
                     
        // Need to add the error code in

           } else if (oper == tok::TOK_LESS){
        // Implementation code-gen for LESS 

             *output << "CMP "<< firstReg <<", "<< secondReg << std::endl
                     //<< "BELVS p_throw_overflow_error"<< std::endl
                     << "MOV R0 "<< firstReg << std::endl;
                     
        // some more implementation 

           } else if (oper == tok::TOK_LESSEQUALS){
        //Implementation code-gen for LESSEQUALS

             *output << "CMP "<< firstReg <<", "<< secondReg << std::endl
                     //<< "BELVS p_throw_overflow_error"<< std::endl
                     << "MOV R0 "<< firstReg << std::endl;
                     
        // some more implementation 
           } else if (oper == tok::TOK_GREATER){
        // Implementation code-gen for GREATER 


             *output << "CMP "<< firstReg <<", "<< secondReg << std::endl
                     //<< "BELVS p_throw_overflow_error"<< std::endl
                     << "MOV R0 "<< firstReg << std::endl;
                     
        // some more implementation 
           } else if (oper == tok::TOK_GREATEREQUALS){
        // Implementation code-gen for GREATEREQUALS 

             *output << "CMP "<< firstReg <<", "<< secondReg << std::endl
                     //<< "BELVS p_throw_overflow_error"<< std::endl
                     << "MOV R0 "<< firstReg << std::endl;
                     
        // some more implementation 
           } else if (oper == tok::TOK_EQUALS){
         //Implementation code-gen for EQUALS 

             *output << "CMP "<< firstReg <<", "<< secondReg << std::endl
                     //<< "BELVS p_throw_overflow_error"<< std::endl
                     << "MOV R0 "<< firstReg << std::endl;
                     
        // some more implementation 
           } else if (oper == tok::TOK_NOTEQUALS){
        // Implementation code-gen for Not EQUAL

             *output << "CMP "<< firstReg <<", "<< secondReg << std::endl
                     //<< "BELVS p_throw_overflow_error"<< std::endl
                     << "MOV R0 "<< firstReg << std::endl;
                     
        // some more implementation 
           }
    } 
    freeRegister(firstReg);
    freeRegister(secondReg);

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
