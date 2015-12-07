#include "code-generation-visitor.hh"
#include "parser.hh"
#define tok yy::parser::token::yytokentype

CodeGenVisitor::CodeGenVisitor(std::ostream* stream) {
  file   = stream;
  regTable = new std::map<std::string, bool>();
}

CodeGenVisitor::~CodeGenVisitor() { }

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

//void CodeGenVisitor::visit(AssignRhs *node) {
//  ArrayLiter *arrayLiter = dynamic_cast<ArrayLiter*>(node);
//  NewPair *newPair       = dynamic_cast<NewPair*>(node);
//  Expression *expr       = dynamic_cast<Expression*>(node);
//  PairElem *pairElem     = dynamic_cast<PairElem*>(node);
//
//  if(arrayLiter) arrayLiter->accept(this);
//  if(newPair) newPair->accept(this);
//  if(expr) expr->accept(this);
//  if(pairElem) pairElem->accept(this);
//}
//void CodeGenVisitor::visit(AssignLhs *node) {}
//void CodeGenVisitor::visit(Expression *node) {
//  Identifier *ident      = dynamic_cast<Identifier*>(node);
//  FunctionCall *funcCall = dynamic_cast<FunctionCall*>(node);
//  Number *number         = dynamic_cast<Number*>(node);
//  Boolean *boolean       = dynamic_cast<Boolean*>(node);
//  Char *charId           = dynamic_cast<Char*>(node);
//  String *stringId       = dynamic_cast<String*>(node);
//  Null *null             = dynamic_cast<Null*>(node);
//  BinaryOperator *binop  = dynamic_cast<BinaryOperator*>(node);
//  ArrayElem *arrayElem   = dynamic_cast<ArrayElem*>(node);
//  UnaryOperator *unop    = dynamic_cast<UnaryOperator*>(node);
//
//  if(ident) ident->accept(this);
//  if(funcCall) funcCall->accept(this);
//  if(number) number->accept(this);
//  if(boolean) boolean->accept(this);
//  if(charId) charId->accept(this);
//  if(stringId) stringId->accept(this);
//  if(null) null->accept(this);
//  if(binop) binop->accept(this);
//  if(arrayElem) arrayElem->accept(this);
//  if(unop) unop->accept(this);
//}

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
  node->rhs->accept(this, "r4");
  if (node->type->equals(new BoolTypeId()) || node->type->equals(new CharTypeId())) {
     middle << "  STRB r4, [sp]" << "\n"; // offset needs to be added to this
  }
  else {
    middle << "  STR r4, [sp]" << "\n"; // offset needs to be added to this
  }
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
  middle << "f_" << node->id->id << ":\n"
          << "  PUSH {lr}" << "\n";
  node->block->accept(this);
  middle << "  POP {pc}" << "\n"
         << "  .ltorg"   << "\n";


}

void CodeGenVisitor::visit(FunctionCall *node, std::string reg) {
    int sizeParam = 0; 
    for(int i = node->parameters->size() - 1; i >= 0; i--) {
      node->parameters->operator[](i)->accept(this, reg);
      if(node->parameters->operator[](i)->type->size() > 1) {
        middle << "  STR " << reg << ", [sp, #" <<  node->parameters->operator[](i)->type->size() 
               << "]!\n";
      } else {
        middle << "  STRB " << reg << ", [sp, #" <<  node->parameters->operator[](i)->type->size() 
               << "]!\n";
      }
      sizeParam += node->parameters->operator[](i)->type->size();
    }

    middle << "  BL " << "f_" << node->id->id << "\n"; 
    if(sizeParam > 0 ) {
      middle << "  ADD sp, sp, #" << sizeParam << "\n";
    }
}

void CodeGenVisitor::visit(Assignment *node) {}
void CodeGenVisitor::visit(FreeStatement *node) {
    middle<< "BL p_free_pair" << std::endl;
    end   << "PUSH {lr}" << std::endl
          << "CMP r0, #0"<< std::endl
          << "LDREQ r0, =msg_"<<messageNum << std::endl
          << "BEQ p_throw_runtime_error"<< std::endl
          << "PUSH {r0}"<< std::endl
          << "LDR r0, [r0]"<< std::endl
          << "BL free"<< std::endl
          << "LDR r0, [sp]"<< std::endl
          << "LDR r0, [r0 , #4]"<< std::endl
          << "BL free"<< std::endl
          << "POP {r0}"<< std::endl
          << "BL free"<< std::endl
          << "POP {PC}"<< std::endl;
    p_throw_runtime_error();
    begin << "msg_"<< messageNum <<":"<<std::endl
          << ".word 50"<< std::endl
          << ".ascii \"NullReferenceError : dereference a null reference \\n\\0\""<< std::endl;
}

void CodeGenVisitor::visit(ReturnStatement *node) {
  node->expr->accept(this, "R0");
}

void CodeGenVisitor::visit(ExitStatement *node) {
  node->expr->accept(this, "R0");

  middle << "  BL exit"    << "\n";
}

void CodeGenVisitor::visit(BeginStatement *node) {}

void CodeGenVisitor::visit(IfStatement *node) {
  node->expr->accept(this, "R4");
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
      node->expr->accept(this, "R4");
  middle << "  CMP R4, #1"                                << "\n"
          << "  BEQ L" << std::to_string(labelNum)         << "\n";
}

void CodeGenVisitor::visit(ReadStatement *node) {}

void CodeGenVisitor::printMsg(TypeId *type) {
    IntTypeId *intTypeId       = dynamic_cast<IntTypeId*> (type);
    StringTypeId *stringTypeId = dynamic_cast<StringTypeId*> (type);
    BoolTypeId *boolTypeId     = dynamic_cast<BoolTypeId*> (type);
    CharTypeId *charTypeId     = dynamic_cast<CharTypeId*> (type);
    
    bool isInt    = false;
    bool isString = false;
    bool isBool   = false;
    bool isChar   = false;
    
    if (intTypeId)    isInt    = true;
    if (stringTypeId) isString = true;
    if (boolTypeId)   isBool   = true;
    if (charTypeId)   isChar   = true;
    
    if (!beginInitialisation) {
		beginInitialisation = true;
		begin << 
			".data" << "\n"
					<< "\n";
    }
    
    if (isChar) {
		middle <<
				"  BL putchar" << "\n";
	} else if(isString) {
		middle <<
				"  BL p_print_string" << "\n";
		begin << 
             "msg_" << messageNum << ":" << std::endl <<
             "  .word 5" << std::endl <<
             "  .ascii  \"%.*s\\0\"" << std::endl;
             
        stringMessageNum = messageNum;
		messageNum++;
	} else if(isInt) {
		begin << 
             "msg_" << messageNum << ":" << std::endl <<
             "  .word 3" << std::endl <<
             "  .ascii  \"%d\\0\"" << std::endl;
             
		messageNum++;
	} else if(isBool) {
		begin << 
             "msg_" << messageNum << ":" << std::endl <<
             "  .word 5" << std::endl <<
             "  .ascii  \"true\\0\"" << std::endl;
		begin << 
             "msg_" << messageNum << ":" << std::endl <<
             "  .word 6" << std::endl <<
             "  .ascii  \"false\\0\"" << std::endl;
             
		messageNum++;
	}
}

void CodeGenVisitor::printlnMsg() {
	middle <<
		  "  BL p_print_ln" << "\n";
	begin << 
		 "msg_" << messageNum << ":" << std::endl <<
		 "  .word 1" << std::endl <<
         "  .ascii  \"\\0\"" << std::endl;
             
    newlineMessageNum = messageNum;     
	messageNum++;
}

void CodeGenVisitor::print(std::string stringToPrint) {
	begin << 
		 "msg_" << messageNum << ":" << std::endl <<
	     "  .word " << stringToPrint.size() << std::endl <<
	     "  .ascii " << stringToPrint << std::endl;
    messageNum++;
}

void CodeGenVisitor::visit(PrintStatement *node) {
    node->expr->accept(this, "r0");
    std::string stringToPrint;
    TypeId *type = node->expr->type;

	printMsg(type);
    print(stringToPrint);
	std::cout<< "Fuck you bitch!!!" << std::endl;
	if (!p_print_string){
		p_print_string = true;
		std::cout<< " in if!!!" << std::endl;
		
		end <<
			"p_print_string: " << "\n" <<
			"  PUSH {lr}" << "\n" <<
			"  LDR r1, [r0]" << "\n" <<
			"  ADD r2, r0, #4" << "\n" <<
			"  LDR r0, =msg_" << stringMessageNum << "\n" <<
			"  ADD r0, r0, #4" << "\n" <<
			"  BL printf" << "\n" <<
			"  MOV r0, #0" << "\n" <<
			"  BL fflush" << "\n" <<
			"  POP {pc}" << "\n";
	}
}

void CodeGenVisitor::visit(PrintlnStatement *node) {
  node->expr->accept(this, "r0");

  printlnMsg();
		
  end <<
        "p_print_string: " << "\n" <<
        "  PUSH {lr}" << "\n" <<
		"  LDR r1, [r0]" << "\n" <<
		"  ADD r2, r0, #4" << "\n" <<
		"  LDR r0, =msg_" << stringMessageNum << "\n" <<
		"  ADD r0, r0, #4" << "\n" <<
		"  BL printf" << "\n" <<
        "  MOV r0, #0" << "\n" <<
        "  BL fflush" << "\n" <<
        "  POP {pc}" << "\n";
  end <<
      "p_print_ln: " << "\n" <<
      "  PUSH {lr}" << "\n" <<
      "  LDR r0, =msg_" << newlineMessageNum << "\n" <<
      "  ADD r0, r0, #4" << "\n" <<
      "  BL puts" << "\n" <<
      "  ADD r0, r0, #4" << "\n" <<
      "  MOV r0, #0" << "\n" <<
      "  BL fflush" << "\n" <<
      "  POP {pc}" << "\n";
}

void CodeGenVisitor::visit(SkipStatement *node) { }

void CodeGenVisitor::visit(Number *node, std::string reg) {
  middle << "  LDR " << reg << ", =" << node->value << std::endl;
}
void CodeGenVisitor::visit(Boolean *node, std::string reg) {
  middle << "  MOV " << reg << ", #" << node->value << std::endl;
}
void CodeGenVisitor::visit(Char *node, std::string reg) {
  middle << "  MOV " << reg << ", #'" << node->value  << "'" << std::endl;
}

void CodeGenVisitor::visit(String *node, std::string reg) {
  middle << " LDR " << reg << ", =msg_" << messageNum << "\n";
  begin  << "msg_" << messageNum << ":" << "\n"
         << ".word" << node->  value.length() << "\n"
         << ".ascii \""<< node-> value << "\""<< "\n";
}
void CodeGenVisitor::visit(Null *node, std::string reg) {}


void CodeGenVisitor::visit(BinaryOperator *node, std::string reg) {
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

void CodeGenVisitor::visit(Identifier *node, std::string reg) {}
void CodeGenVisitor::visit(Identifier *node) {}
void CodeGenVisitor::visit(ArrayElem *node, std::string reg) {}
void CodeGenVisitor::visit(ArrayElem *node) {}
void CodeGenVisitor::visit(PairElem *node, std::string reg) {}
void CodeGenVisitor::visit(PairElem*node) {}
void CodeGenVisitor::visit(ArrayLiter *node, std::string reg) {}
void CodeGenVisitor::visit(NewPair *node, std::string reg) {
  middle << "  LDR r0, =8\n"
         << "  BL malloc\n"
         << "  MOV r4, r0\n";
  node->fst->accept(this, "r5");

  middle << "  LDR r0, =" << node->fst->type->size() << "\n"
         << "  BL malloc\n";
   if (node->fst->type->equals(new CharTypeId)
         || node->fst->type->equals(new BoolTypeId)) {
     middle << "  STRB r5, [r0]\n";
   }
   else {
     middle << "  STRB r5, [r0]\n";
   }
   middle << "  STR r0, [r4]\n";
   node->snd->accept(this, "r5");
   middle << "  LDR r0, =" << node->fst->type->size() << "\n"
          << "  BL malloc\n";
   if (node->snd->type->equals(new CharTypeId)
        || node->snd->type->equals(new BoolTypeId)) {
     middle << "  STRB r5, [r0]\n";
   }
   else {
     middle << "  STRB r5, [r0]\n";
   }
   middle << "  STR r0, [r4,#4]\n";



}
void CodeGenVisitor::visit(UnaryOperator *node, std::string reg) {}

void CodeGenVisitor::p_check_divide_by_zero(void){ 
    if(!p_check_divide_by_zerob){
        end     << "p_check_divide_by_zero:"<< "\n"
                << "PUSH {lr}" << "\n"
                << "CMP r1, #0" << "\n"
                << "LDREQ r0, =msg_"<<messageNum << "\n"
                << "BLEQ p_throw_runtime_error" << "\n"
                << "POP {pc}" << "\n";
        begin   << "msg_"<< messageNum << ":"<< "\n"
                << ".word 45" << "\n"
                << ".ascii \" DivideByZeroError : divide or modulo by zero \\n\\0\""<< "\n";
                messageNum ++ ; 
        p_check_divide_by_zerob = true;
       p_throw_runtime_error();
    }
}

void CodeGenVisitor::p_throw_overflow_error(void){
    if(!p_throw_overflow_errorb){
        end     << "p_throw_overflow_error: " << "\n"
                << "LDR r0, =msg_"<< messageNum<< "\n"
                << "BL p_throw_runtime_error" << "\n";
        begin   << "msg_"<< messageNum << ":"<<"\n"
                << ".word 82"<< "\n"
                << ".ascii \"OverflowError: the result is too small/large to store in a 4 byte signed integer \\n\""<<"\n";
        messageNum ++ ; 
        p_throw_overflow_errorb = true;

        p_throw_runtime_error();
    }
}

void CodeGenVisitor::p_throw_runtime_error(void){
    if(!p_throw_runtime_errorb){
         end    << "p_throw_run_time_error:" << "\n"
                << "BL p_print_string"<< "\n"
                << "MOV r0, #-1" << "\n"
                << "BL exit"<< "\n";
        p_throw_runtime_errorb = true; 
    }
}

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
