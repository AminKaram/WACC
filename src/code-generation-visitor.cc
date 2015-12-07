#include "code-generation-visitor.hh"
#include "parser.hh"
#define tok yy::parser::token::yytokentype

CodeGenVisitor::CodeGenVisitor(std::ostream* stream) {
  file   = stream;
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
  middle << ".text" << "\n" << "\n"
          << ".global main" << "\n";

  node->functions->accept(this);

  middle << "main:"       << "\n"
          << "  PUSH {lr}\n";


  node->statements->accept(this);
  middle << "  LDR R0, =0" << "\n"
          << "  POP {pc}" << "\n"
          << "  .ltorg"   << "\n";

  if (begin.rdbuf()->in_avail() != 0) {
    *file << begin.rdbuf() ;
  }
  if (middle.rdbuf()->in_avail() != 0) {
      *file << middle.rdbuf() ;
    }
  if (end.rdbuf()->in_avail() != 0) {
      *file << end.rdbuf() ;
    }
}

void CodeGenVisitor::visit(AssignRhs *node) {
}
void CodeGenVisitor::visit(AssignLhs *node) {}
void CodeGenVisitor::visit(Expression *node) {
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
void CodeGenVisitor::visit(VariableDeclaration *node) {
// simpliest version for implementing variable declaration
  middle << "MOV r0, #" << "\n";
  node->rhs->accept(this);
  middle << "STR r0 [sp]" << "\n";

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
  middle << node->id->id.append("_").append(node->id->id).append(":")
          << "\n"
          << "  PUSH {lr}" << "\n";
  node->block->accept(this);
  middle << "  POP {pc}" << "\n"
          << "  .ltorg"   << "\n";


}

void CodeGenVisitor::visit(FunctionCall *node) {
  //middle <<
}

void CodeGenVisitor::visit(Assignment *node) {}
void CodeGenVisitor::visit(FreeStatement *node) {}

void CodeGenVisitor::visit(ReturnStatement *node) {

  node->expr->accept(this);
  middle << "  Mov R0, R4" << "\n";

}

void CodeGenVisitor::visit(ExitStatement *node) {
  node->expr->accept(this);

  middle  << "  MOV R0, R4" << "\n"
           << "  BL exit"    << "\n";
}

void CodeGenVisitor::visit(BeginStatement *node) {}

void CodeGenVisitor::visit(IfStatement *node) {
  node->expr->accept(this);
  middle << "  CMP R4, #0"                            << "\n"
          << "  BEQ L" << std::to_string(labelNum)     << "\n";
  labelNum++;
  node->thenS->accept(this);

  middle << "  B L"  << std::to_string(labelNum)              << "\n"
          << "L"      << std::to_string(labelNum - 1)   << ":" << "\n";

  node->elseS->accept(this);

  middle << "L" << std::to_string(labelNum) << ":"  << "\n";
  labelNum--;
}

void CodeGenVisitor::visit(WhileStatement *node) {


  middle << "  B L" << std::to_string(labelNum) << "\n";
  labelNum++;
  middle << "L" << std::to_string(labelNum) << ":" << "\n";
  node->doS->accept(this);
  middle << "L" << std::to_string(labelNum - 1) << ": " << "\n";
      node->expr->accept(this);
  middle << "  CMP R4, #1"                                << "\n"
          << "  BEQ L" << std::to_string(labelNum)         << "\n";
}

void CodeGenVisitor::visit(ReadStatement *node) {}

std::string CodeGenVisitor::visitAndPrintReg(Expression *node) {
	middle << "  MOV R1, \"Hello World\"" << "\n";
//			    "string:" << "\n" <<
//				".ascii \"Hello Worldn\" " << "\n";

	return "R1";
}

void CodeGenVisitor::visit(PrintStatement *node) {
  node->expr->accept(this);
  //std::string reg1 = getAvailableRegister();
  //std::string reg2 = getAvailableRegister();
	middle <<
        "p_print_string: " << "\n" <<
        "  PUSH {lr}" << "\n" <<
				"  LDR r1, [register where the message was put in main = r0]" << "\n" <<
				"  ADD r2, r0, #4" << "\n" <<
				"  LDR r0, =msg_1" << "\n" <<
		 		"  ADD r0, r0, #4" << "\n" <<
			 	"  BL printf" << "\n" <<
        "  MOV r0, #0" << "\n" <<
        "  BL fflush" << "\n" <<
        "  POP {pc}" << "\n";
}

void CodeGenVisitor::visit(PrintlnStatement *node) {
  node->expr->accept(this);
  // visit the print node first ant then:
  middle <<
        "p_print_string: " << "\n" <<
        "  PUSH {lr}" << "\n" <<
        "  LDR r1, [register where the message was put in main = r0]" << "\n" <<
        "  ADD r2, r0, #4" << "\n" <<
        "  LDR r0, =msg_1" << "\n" <<
        "  ADD r0, r0, #4" << "\n" <<
        "  BL printf" << "\n" <<
        "  MOV r0, #0" << "\n" <<
        "  BL fflush" << "\n" <<
        "  POP {pc}" << "\n";
  middle <<
      "p_print_ln: " << "\n" <<
      "  PUSH {lr}" << "\n" <<
      "  LDR r0, =msg_2" << "\n" <<
      "  ADD r0, r0, #4" << "\n" <<
      "  BL puts" << "\n" <<
      "  ADD r0, r0, #4" << "\n" <<
      "  MOV r0, #0" << "\n" <<
      "  BL fflush" << "\n" <<
      "  POP {pc}" << "\n";
}
void CodeGenVisitor::visit(Number *node) {
  middle << "  LDR R4, =" << node->value << "\n";
}
void CodeGenVisitor::visit(Boolean *node) {
  middle << "  MOV R4, #" << node->value << "\n";
}
void CodeGenVisitor::visit(Char *node) {
  middle << "  MOV R4, #'" << node->value  << "'" << "\n";
}
void CodeGenVisitor::visit(String *node) {}
void CodeGenVisitor::visit(Null *node) {}

void CodeGenVisitor::visit(BinaryOperator *node) {
   int oper = node -> op;
         std:: string firstReg = getAvailableRegister();
         std:: string secondReg = getAvailableRegister();

   if(oper == tok::TOK_LOGOR || oper == tok::TOK_LOGAND){
         middle << "LDRSB "<< firstReg << ", " /* << "[address where
         first value is stored]" (e.g. [sp])*/ << "\n";
         middle << "LDRSB "<< secondReg <<", " /* << "[address where
         second value is stored] (e.g. [sp , #1] )" */ << "\n";

      if (oper == tok::TOK_LOGOR){
      //Implementation code-gen for OR 
          
         middle << "ORR "<< firstReg << ", " << firstReg << ", "
                 << secondReg << "\n";
    
       } else if (oper == tok::TOK_LOGAND){
      //Implementation code-gen for AND      
         middle << "AND "<< firstReg << ", " << firstReg << ", "
                 << secondReg << "\n";
      }      
   } else if (oper >= tok::TOK_STAR && oper <= tok::TOK_MINUS){
   
             middle << "LDR "<< firstReg << ", " /* << "[address where
             first operand is stored]" (e.g. [sp])*/ << "\n";
             middle << "LDR "<< secondReg << ", "/* << "[address where
             second operand is stored] (e.g. [sp , #4] )" */ << "\n";
           
           
           if(oper == tok :: TOK_STAR){
              //Implementation code gen for MULTIPLY

             middle << "SMULL "<< firstReg << ", " << secondReg << ", "
                     << firstReg << ", " << secondReg << "\n"
                     
                     << "CMP " << secondReg << ", "<< firstReg << ", "
                     << "ASR #31" << "\n"

                     << "BLNE p_throw_overflow_error"<< "\n";
                     p_throw_overflow_error();
                     

           } else if (oper == tok::TOK_SLASH){
               //Implementation code gen for DIVIDE
               middle << "MOV R0, "<< firstReg  << "\n"
                       << "MOV R1, "<< secondReg << "\n"
                       << "BL p_checkdivide_by_zero"<< "\n";
               p_check_divide_by_zero();
               middle << "BL __aeabi_idiv"<< "\n";
        

           } else if (oper == tok::TOK_MODULO){
         //Implementation code-gen for MODULO 

               middle << "MOV R0, "<< firstReg  << "\n"
                       << "MOV R1, "<< secondReg << "\n"
                       << "BL p_checkdivide_by_zero"<< "\n";
               p_check_divide_by_zero();
               middle << "BL __aeabi_idivmod"<< "\n";
           } else if (oper == tok::TOK_PLUS){
        // Implementation code-gen for PLUS 
             middle << "ADDS "<< firstReg <<", "<< firstReg <<", "
             << secondReg << "\n"
            
             << "BELVS p_throw_overflow_error"<< "\n";
             p_throw_overflow_error();
                     

           } else if (oper == tok::TOK_MINUS){
         // Implementation code-gen for MINUS
             middle << "SUBS "<< firstReg <<", "<< firstReg <<", "
             << secondReg << "\n"

             << "BELVS p_throw_overflow_error"<< "\n";
             p_throw_overflow_error();
           } 
        }else if (oper >= tok::TOK_LESS && oper <= tok::TOK_NOTEQUALS){
            
            middle << "CMP "<< firstReg <<", "<< secondReg << "\n";
             if (oper == tok::TOK_LESS){
        // Implementation code-gen for LESS 
            middle << "MOVLT "<< firstReg << ", #1"<< "\n"
                    << "MOVGE "<< firstReg << ", #0"<< "\n";

           } else if (oper == tok::TOK_LESSEQUALS){
        //Implementation code-gen for LESSEQUALS
            middle << "MOVLE "<< firstReg << ", #1"<< "\n"
                    << "MOVGT "<< firstReg << ", #0"<< "\n";
                     
           } else if (oper == tok::TOK_GREATER){
        // Implementation code-gen for GREATER 
            middle << "MOVGT "<< firstReg << ", #1"<< "\n"
                    << "MOVLE "<< firstReg << ", #1"<< "\n";
 
           } else if (oper == tok::TOK_GREATEREQUALS){
        // Implementation code-gen for GREATEREQUALS 
            middle << "MOVGE "<< firstReg << ", #1"<< "\n"
                    << "MOVLT "<< firstReg << ", #0"<< "\n";
 
           } else if (oper == tok::TOK_EQUALS){
         //Implementation code-gen for EQUALS 
            middle << "MOVEQ "<< firstReg << ", #1"<< "\n"
                    << "MOVNE "<< firstReg << ", #0"<< "\n";
 
           } else if (oper == tok::TOK_NOTEQUALS){
        // Implementation code-gen for Not EQUAL
            middle << "MOVNE "<< firstReg << ", #1"<< "\n"
                    << "MOVEQ "<< firstReg << ", #1"<< "\n";
                     
           }
    }
    middle << "MOV R0, "<< firstReg << "\n";
    freeRegister(firstReg);
    freeRegister(secondReg);

}

void CodeGenVisitor::visit(Identifier *node) {}
void CodeGenVisitor::visit(ArrayElem *node) {}
void CodeGenVisitor::visit(PairElem *node) {}
void CodeGenVisitor::visit(ArrayLiter *node) {}
void CodeGenVisitor::visit(NewPair *node) {}
void CodeGenVisitor::visit(UnaryOperator *node) {}

void CodeGenVisitor::p_check_divide_by_zero(void){ }/*
    std::streampos originalPos;
    if(!p_check_divide_by_zerob){
        originalPos = middle -> std::ostream::tellp();
        middle << "PUSH {lr}" << "\n"
                << "CMP r1, #0" << "\n"
                << "LDREQ r0, =msg_"<<messageNum << "\n";
        middle -> seekp(6,std::ios_base::beg);
        middle << "msg_"<< messageNum << ":"<< "\n"
                << ".word 45" << "\n"
                << ".ascii \" DivideByZeroError : divide or modulo by zero \\n\\0\""<< "\n";
        middle -> seekp(originalPos);
        middle << "BLEQ p_throw_runtime_error" << "\n";
        p_throw_runtime_error();
        middle << "POP {pc}" << "\n";
    }
}*/

void CodeGenVisitor::p_throw_overflow_error(void){}
   /* std::streampos originalPos;
    if(!p_throw_overflow_errorb){
         originalPos = middle -> std::ostream::tellp();
         middle -> seekp(0,std::ios_base::end);
        middle << "p_throw_overflow_error: " << "\n"
                << "LDR r0, =msg_"<< messageNum<< "\n"
                << "BL p_throw_runtime_error" << "\n";
         middle -> seekp(6,std::ios_base::beg);
        middle << "msg_"<< messageNum++ << ":"<<"\n"
                << ".word 82"<< "\n"
                << ".ascii \"OverflowError: the result is too small/large to store in a 4 byte signed integer \\n\""<<"\n";
        middle -> seekp(originalPos);
        p_throw_overflow_errorb = true;

        p_throw_runtime_error();*/
  //  }
//}

void CodeGenVisitor::p_throw_runtime_error(void){}
    /*std::streampos originalPos;
    if(!p_throw_runtime_errorb){
         originalPos = middle->std::ostream::tellp();
         middle -> std::ostream::seekp(0,std::ios_base::end);
         middle<< "BL p_print_string"<< "\n"
                << "MOV r0, #-1" << "\n"
                << "BL exit"<< "\n";
        p_throw_runtime_errorb = true; 
        middle -> std::ostream::seekp(originalPos);
    }
}*/
void CodeGenVisitor::defineLabel(String label) {}

void CodeGenVisitor::populateRegMap() {
	for (int i = 4; i < MAX_REG_NUMBER - 1; ++i) {
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
  return "R4";
}

void CodeGenVisitor::freeRegister(std::string reg) {
	regTable->find(reg)->second = true;
	middle << "  MOV " << reg << ", " << "#0" << "\n";
}
