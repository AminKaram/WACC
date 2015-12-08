#include "code-generation-visitor.hh"
#include "parser.hh"
#define tok yy::parser::token::yytokentype

CodeGenVisitor::CodeGenVisitor(std::ostream* stream) {
  file   = stream;
  regTable = new std::map<std::string, bool>();
  varMap = new std::map<std::string, int>();
  populateRegMap();
}

CodeGenVisitor::~CodeGenVisitor() { }

void CodeGenVisitor::visit(Program *node) {

  middle << ".text" << std::endl<< "\n"
         << ".global main" << "\n";

  node->functions->accept(this);
 
  scopeSize = 0;
  for (int i = 0; i < node->table->variables->size(); i++) {
    scopeSize += node->table->variables->operator[](i)->type->size();
  }
  middle << "main:"       << "\n"
         << "  PUSH {lr}\n";
  int tmp = scopeSize;
  std::string toEnd("");
  while (tmp > 1024) {
    middle << "  SUB sp, sp, #1024\n";
    toEnd += "  ADD sp, sp, #1024\n";
    tmp -=1024;
  }
        
  middle << "  SUB sp, sp, #" << tmp << "\n";
  toEnd +=  "  ADD sp, sp, #" + std::to_string(tmp) + "\n";

  node->statements->accept(this);
  middle << toEnd
         << "  LDR r0, =0" << "\n"
         << "  POP {pc}" << "\n"
         << "  .ltorg";

  if (begin.rdbuf()->in_avail() != 0) {
    *file << begin.rdbuf() << std::endl;
  }
  if (middle.rdbuf()->in_avail() != 0) {
      *file << middle.rdbuf() << "\n";
    }
  if (end.rdbuf()->in_avail() != 0) {
      *file << end.rdbuf() << "\n" ;
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
  int sizeSoFar = 0;
  for (int i = 0; i < node->table->variables->size(); i++) {
    if(node->table->variables->operator[](i)->id->id.compare(node->id->id) == 0) {
      sizeSoFar += node->type->size();
      break;
    }
    sizeSoFar += node->table->variables->operator[](i)->type->size();
  }
  if (node->type->equals(new BoolTypeId()) || node->type->equals(new CharTypeId())) {
    middle << "  STRB r4, [sp, #" << scopeSize-sizeSoFar << "]\n"; 
  } else {
    middle << "  STR r4, [sp, #" << scopeSize-sizeSoFar << "]\n"; 
  }
  varMap->operator[](node->id->id) = scopeSize - sizeSoFar;

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
         << "  POP {pc}"  << "\n"
         << "  .ltorg"   << "\n";
}


void CodeGenVisitor::visit(FunctionCall *node, std::string reg) {
    int sizeParam = 0; 
    for(int i = node->parameters->size() - 1; i >= 0; i--) {
      node->parameters->operator[](i)->accept(this, reg);
      if(node->parameters->operator[](i)->type->size() > 1) {
        middle << "  STR " << reg << ", [sp, #" 
               <<  node->parameters->operator[](i)->type->size() 
               << "]!\n";
      } else {
        middle << "  STRB " << reg << ", [sp, #" 
               <<  node->parameters->operator[](i)->type->size() 
               << "]!\n";
      }
      sizeParam += node->parameters->operator[](i)->type->size();
    }


    middle << "  BL f_" << node->id->id << "\n"
           << "  MOV " << reg << ",r0 \n";
    if(sizeParam > 0 ) {
      middle << "  ADD sp, sp, #" << sizeParam << "\n";
    }
}

void CodeGenVisitor::visit(Assignment *node) {
  node->rhs->accept(this, "r4");
  BoolTypeId *boolType = new BoolTypeId();
  CharTypeId *charType = new CharTypeId();
  ArrayElem *arrLhs = dynamic_cast<ArrayElem*>(node->lhs);
  if(arrLhs) {
    middle << "  ADD r5, sp ,#" << varMap->operator[](node->lhs->getId()) << "\n";
    for (int i=0; i < arrLhs->idxs->size(); i++) {
      arrLhs->idxs->operator[](i)->accept(this, "r6");
      middle << "  LDR r5, [r5]\n"
             << "  MOV r0, r6\n"
             << "  MOV r1, r5\n"
             //bound checking branch done here
             << "  ADD r5, r5, #4\n";
      if(arrLhs->type->size() == 1) {
        middle << "  ADD r5, 5, r6\n";
      } else {
        middle << "  ADD r5, r5, r6, LSL #2\n";
      }
    }
    middle << "  STR r4, [r5]\n";
    
  } else if(node->lhs->type->equals(boolType) || node->lhs->type->equals(charType)) {
    if (varMap->operator[](node->lhs->getId()) == 0) {
      middle << "  STRB r4, [sp]\n";
    } else {
      middle << "  STRB r4, [sp, #" << varMap->operator[](node->lhs->getId()) 
             << "]\n";
    }
  } else {
      if (varMap->operator[](node->lhs->getId()) == 0) {
        middle << "  STR r4, [sp]\n";
      } else {
        middle << "  STR r4, [sp, #" << varMap->operator[](node->lhs->getId()) 
               << "]\n";
      }
  }
}


void CodeGenVisitor::visit(FreeStatement *node) {
         node -> expr -> accept(this,"r4");
         middle << "  Mov r0, r4\n"
                << "  BL p_free_pair\n";
    if(!p_free_pairb){     
         end   << "p_free_pair:"<<std::endl
               << "  PUSH {lr}" << std::endl
               << "  CMP r0, #0"<< std::endl
               << "  LDREQ r0, =msg_"<<messageNum << std::endl
               << "  BEQ p_throw_runtime_error"<< std::endl
               << "  PUSH {r0}"<< std::endl
               << "  LDR r0, [r0]"<< std::endl
               << "  BL free"<< std::endl
               << "  LDR r0, [sp]"<< std::endl
               << "  LDR r0, [r0 , #4]"<< std::endl
               << "  BL free"<< std::endl
               << "  POP {r0}"<< std::endl
               << "  BL free"<< std::endl
               << "  POP {PC}"<< std::endl;
         begin << "msg_"<< messageNum <<":"<<std::endl
               << "  .word 50"<< std::endl
               << "  .ascii \"NullReferenceError : dereference a null reference\\n\\0\""<< std::endl; 
        messageNum ++;
         p_throw_runtime_error();
        
        p_free_pairb = true;
        
    }
         
}


void CodeGenVisitor::visit(ReturnStatement *node) {
  node->expr->accept(this, "r0");
}

void CodeGenVisitor::visit(ExitStatement *node) {

  node->expr->accept(this, "r0");

  middle << "  BL exit"    << "\n";

}

void CodeGenVisitor::visit(BeginStatement *node) {}

void CodeGenVisitor::visit(IfStatement *node) {
  node->expr->accept(this, "r4");
  labelNum++;
  middle << "  CMP r4, #0\n"
         << "  BEQ L" << std::to_string(labelNum - 1)     << "\n";

  node->thenS->accept(this);

  middle << "  B L"  << std::to_string(labelNum)              << "\n"
          << "L"      << std::to_string(labelNum - 1)   << ":" << "\n";

  node->elseS->accept(this);

  middle << "L" << std::to_string(labelNum) << ":"  << "\n";
}

void CodeGenVisitor::visit(WhileStatement *node) {

  labelNum++;
  middle << "  B L" << std::to_string(labelNum - 1) << "\n";
  middle << "L" << std::to_string(labelNum) << ":" << "\n";
  node->doS->accept(this);
  middle << "L" << std::to_string(labelNum - 1) << ": " << "\n";
      node->expr->accept(this, "r4");
  middle << "  CMP r4, #1"                                << "\n"

          << "  BEQ L" << std::to_string(labelNum)         << "\n";
}

void CodeGenVisitor::printAssemblyOfReadInt() {
  end << 
      "p_read_int:" << "\n" <<
      "  PUSH {lr}" << "\n" <<
      "  MOV r1, r0" << "\n" <<
      "  LDR r0, =msg_"<< intMessageNum << "\n" <<
      "  ADD r0, r0, #4" << "\n" <<
      "  BL scanf" << "\n" <<
      "  POP {pc}" << "\n";
}

void CodeGenVisitor::printAssemblyOfReadChar() {
  end << 
      "p_read_char:" << "\n" <<
      "  PUSH {lr}" << "\n" <<
      "  MOV r1, r0" << "\n" <<
      "  LDR r0, =msg_"<< charMessageNum << "\n" <<
      "  ADD r0, r0, #4" << "\n" <<
      "  BL scanf" << "\n" <<
      "  POP {pc}" << "\n";
}

void CodeGenVisitor::printMsgRead(TypeId *type) {
  IntTypeId *intTypeId   = dynamic_cast<IntTypeId*> (type);
  CharTypeId *charTypeId = dynamic_cast<CharTypeId*> (type);
  
  if (!beginInitialisation) {
  beginInitialisation = true;
  begin << 
    ".data" << "\n"
        << "\n";
  }
  
  if (charTypeId) {
    middle <<
        "  BL p_read_char" << "\n";
      begin << 
         "msg_" << messageNum << ":" << std::endl <<
         "  .word 4" << std::endl <<
         "  .ascii  \" %c\\0\"" << std::endl;
      charMessageNum = messageNum;
      messageNum++;
  } else if(intTypeId) {
      middle <<
          "  BL p_read_int" << "\n";
        begin << 
           "msg_" << messageNum << ":" << std::endl <<
           "  .word 3" << std::endl <<
           "  .ascii  \"%d\\0\"" << std::endl;
      intMessageNum = messageNum;
      messageNum++;
  }
}

void CodeGenVisitor::printStatementForRead(TypeId *type) {
  if (!p_read_char && type->equals(new CharTypeId())) {
      p_read_char = true;
      printAssemblyOfReadChar();
  } else if (!p_read_int && type->equals(new IntTypeId())) {
      p_read_int = true;
      printAssemblyOfReadInt();
  }
}

void CodeGenVisitor::visit(ReadStatement *node) {
	adr = true;
  node->id->accept(this, "r0");
	adr = false;
  TypeId *type = node->id->type;
  printMsgRead(type);
  printStatementForRead(type);
}


void CodeGenVisitor::printMsg(TypeId *type) {
    IntTypeId *intTypeId       = dynamic_cast<IntTypeId*> (type);
    StringTypeId *stringTypeId = dynamic_cast<StringTypeId*> (type);
    BoolTypeId *boolTypeId     = dynamic_cast<BoolTypeId*> (type);
    CharTypeId *charTypeId     = dynamic_cast<CharTypeId*> (type);

    if (!beginInitialisation) {
		beginInitialisation = true;
		begin <<
			".data" << "\n"
					<< "\n";
    }

    if (charTypeId) {
		middle << "  BL putchar" << "\n";
	  } else if(stringTypeId) {
    		middle << "  BL p_print_string" << "\n";
    		if (!msgString) {
    			msgString  = true;
    			begin <<
    				 "msg_" << messageNum << ":" << std::endl <<
    				 "  .word 5" << std::endl <<
    				 "  .ascii  \"%.*s\\0\"" << std::endl;
          stringMessageNum = messageNum;
          messageNum++;
    		}
	} else if(intTypeId) {
  		middle << "  BL p_print_int" << "\n";
      if (!msgInt) {
        msgInt = true;
        begin << 
           "msg_" << messageNum << ":" << std::endl <<
           "  .word 3" << std::endl <<
           "  .ascii  \"%d\\0\"" << std::endl;
      }
  		intMessageNum = messageNum;
  		messageNum++;
	} else if(boolTypeId) {
  		middle << "  BL p_print_bool" << "\n";
  		if (!msgBool) {
  			msgBool = true;
  			begin << 
  				 "msg_" << messageNum << ":" << std::endl <<
  				 "  .word 5" << std::endl <<
  				 "  .ascii \"true\\0\"" << std::endl;
  			begin << 
  				 "msg_" << messageNum + 1 << ":" << std::endl <<
  				 "  .word 6" << std::endl <<
  				 "  .ascii \"false\\0\"" << std::endl;
        boolMessageNum = messageNum;
        messageNum+=2;
  		}
	  }
}

void CodeGenVisitor::printlnMsg() {
	middle <<
		  "  BL p_print_ln" << "\n";
	if (!msgNewLine) {
		msgNewLine = true;
		begin << 
			 "msg_" << messageNum << ":" << std::endl <<
			 "  .word 1" << std::endl <<
			 "  .ascii  \"\\0\"" << std::endl;
	  newlineMessageNum = messageNum;
	  messageNum++;
	}           
}



void CodeGenVisitor::printAssemblyOfPrintString() {
	end <<
		"p_print_string: " << std::endl<<
		"  PUSH {lr}" << std::endl<<
		"  LDR r1, [r0]" << std::endl<<
		"  ADD r2, r0, #4" << std::endl<<
		"  LDR r0, =msg_" << stringMessageNum << std::endl<<
		"  ADD r0, r0, #4" << std::endl<<
		"  BL printf" << std::endl<<
		"  MOV r0, #0" << std::endl<<
		"  BL fflush" << std::endl<<
		"  POP {pc}" << "\n";
}

void CodeGenVisitor::printAssemblyOfPrintBool() {
	end <<
		"p_print_bool: " << std::endl<<
		"  PUSH {lr}" << std::endl<<
		"  CMP r0, #0" << std::endl<<
		"  LDRNE r0, =msg_" << boolMessageNum     << std::endl<<
		"  LDREQ r0, =msg_" << boolMessageNum + 1 << std::endl<<
		"  ADD r0, r0, #4" << std::endl<<
		"  BL printf" << std::endl<<
		"  MOV r0, #0" << std::endl<<
		"  BL fflush" << std::endl<<
		"  POP {pc}" << "\n";
}

void CodeGenVisitor::printAssemblyOfPrintInt() {
	end <<
		"p_print_int: " << std::endl<<
		"  PUSH {lr}" << std::endl<<
		"  MOV r1, r0" << std::endl<<
		"  LDR r0, =msg_" << intMessageNum << std::endl<<
		"  ADD r0, r0, #4" << std::endl<<
		"  BL printf" << std::endl<<
		"  MOV r0, #0" << std::endl<<
		"  BL fflush" << std::endl<<
		"  POP {pc}" << "\n";
}

void CodeGenVisitor::printStatement(TypeId *type) {
	if (!p_print_string && type->equals(new StringTypeId())) {
		p_print_string = true;
		printAssemblyOfPrintString();
	} else if (!p_print_bool && type->equals(new BoolTypeId())) {
			p_print_bool = true;
			printAssemblyOfPrintBool();
	} else if (!p_print_int && type->equals(new IntTypeId())) {
			p_print_int = true;
			printAssemblyOfPrintInt();
	}
}

void CodeGenVisitor::visit(PrintStatement *node) {
  node->expr->accept(this, "r0");
  TypeId *type = node->expr->type;
	printMsg(type);
  printStatement(type);
}


void CodeGenVisitor::printAssemblyOfPrintln() {
	end <<
		  "p_print_ln: " << std::endl<<
		  "  PUSH {lr}" << std::endl<<
		  "  LDR r0, =msg_" << newlineMessageNum << std::endl<<
		  "  ADD r0, r0, #4" << std::endl<<
		  "  BL puts" << std::endl<<
		  "  MOV r0, #0" << std::endl<<
		  "  BL fflush" << std::endl<<
		  "  POP {pc}" << "\n";
}

void CodeGenVisitor::visit(PrintlnStatement *node) {
  node->expr->accept(this, "r0");
	TypeId *type = node->expr->type;
	
	printMsg(type);
	printStatement(type);
	printlnMsg();
	
	if(!p_print_ln) {	
		p_print_ln = true;
		printStatement(type);
	  printAssemblyOfPrintln();
	}
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
  if (!beginInitialisation) {
		beginInitialisation = true;
		begin << 
			".data" << "\n"
					<< "\n";
  }
  middle << 
		"  LDR " << reg << ", =msg_" << messageNum << "\n";
  begin  << 
		"msg_" << messageNum << ":" << std::endl<<
        "  .word " << node->value.size() - 2 << std::endl<<
        "  .ascii " << node->value << "\n";
  messageNum++;
         
}

void CodeGenVisitor::visit(Null *node, std::string reg) {}


void CodeGenVisitor::visit(BinaryOperator *node, std::string reg) {
   int oper = node -> op;
         
         std::string firstReg  = reg;
         int tmp = atoi(reg.erase(0,1).c_str()) + 1;
         std::string secondReg = "r" + std::to_string(tmp);
         if (tmp > 10) { 
           secondReg = "r10";   
         }
         node -> left -> accept(this,firstReg);
         if(tmp > 10) {
           middle << "  PUSH {r10}\n";
         }
         node -> right -> accept(this,secondReg);
         if (tmp > 10) {
           middle << "  POP {r11}\n";
           firstReg = "r10";
           secondReg = "r11";
         }
     if(oper == tok::TOK_LOGOR || oper == tok::TOK_LOGAND){

      if (oper == tok::TOK_LOGOR){
      //Implementation code-gen for OR
         middle << "  ORR "<< firstReg << ", " << firstReg << ", "

                << secondReg << "\n";
       } else if (oper == tok::TOK_LOGAND){
      //Implementation code-gen for AND      
         middle << "  AND "<< firstReg << ", " << firstReg << ", "
                << secondReg << "\n";
      }      
   } else if (oper >= tok::TOK_STAR && oper <= tok::TOK_MINUS){
           
           
           if(oper == tok :: TOK_STAR){
              //Implementation code gen for MULTIPLY

             middle << "  SMULL "<< firstReg << ", " << secondReg << ", "
                    << firstReg << ", " << secondReg << "\n"
                     
                    << "  CMP " << secondReg << ", "<< firstReg << ", "
                    << "  ASR #31" << "\n"

                    << "  BLNE p_throw_overflow_error"<< "\n";

                     p_throw_overflow_error();
                     

           } else if (oper == tok::TOK_SLASH){
               //Implementation code gen for DIVIDE
               middle << "  MOV r0, "<< firstReg  << "\n"
                      << "  MOV r1, "<< secondReg << "\n"

                      << "  BL p_check_divide_by_zero"<< "\n";
               p_check_divide_by_zero();
               middle << "  BL __aeabi_idiv"<< "\n";
        
           } else if (oper == tok::TOK_MODULO){
         //Implementation code-gen for MODULO 

               middle << "  MOV r0, "<< firstReg  << "\n"
                      << "  MOV r1, "<< secondReg << "\n"
                      << "  BL p_check_divide_by_zero"<< "\n";
               p_check_divide_by_zero();
               middle << "  BL __aeabi_idivmod\n"
                      << "  MOV r0, r1\n";
           } else if (oper == tok::TOK_PLUS){
        // Implementation code-gen for PLUS 
             middle << "  ADDS "<< firstReg <<", "<< firstReg <<", "
                    << secondReg << "\n"
            
                    << "  BLVS p_throw_overflow_error"<< "\n";

             p_throw_overflow_error();
                     

           } else if (oper == tok::TOK_MINUS){
         // Implementation code-gen for MINUS

             middle << "  SUBS "<< firstReg <<", "<< firstReg <<", "
                    << secondReg << "\n"

                    << "  BLVS p_throw_overflow_error"<< "\n";
             p_throw_overflow_error();
           } 
        }else if (oper >= tok::TOK_LESS && oper <= tok::TOK_NOTEQUALS){
            
            middle << "  CMP "<< firstReg <<", "<< secondReg << "\n";
             if (oper == tok::TOK_LESS){
        // Implementation code-gen for LESS 
            middle << "  MOVLT "<< firstReg << ", #1"<< "\n"
                   << "  MOVGE "<< firstReg << ", #0"<< "\n";

           } else if (oper == tok::TOK_LESSEQUALS){
        //Implementation code-gen for LESSEQUALS
            middle << "  MOVLE "<< firstReg << ", #1"<< "\n"
                   << "  MOVGT "<< firstReg << ", #0"<< "\n";
                     
           } else if (oper == tok::TOK_GREATER){
        // Implementation code-gen for GREATER 
            middle << "  MOVGT "<< firstReg << ", #1"<< "\n"
                   << "  MOVLE "<< firstReg << ", #0"<< "\n";
 
           } else if (oper == tok::TOK_GREATEREQUALS){
        // Implementation code-gen for GREATEREQUALS 
            middle << "  MOVGE "<< firstReg << ", #1"<< "\n"
                   << "  MOVLT "<< firstReg << ", #0"<< "\n";
 
           } else if (oper == tok::TOK_EQUALS){
         //Implementation code-gen for EQUALS 
            middle << "  MOVEQ "<< firstReg << ", #1"<< "\n"
                   << "  MOVNE "<< firstReg << ", #0"<< "\n";
 
           } else if (oper == tok::TOK_NOTEQUALS){
        // Implementation code-gen for Not EQUAL
            middle << "  MOVNE "<< firstReg << ", #1"<< "\n"
                   << "  MOVEQ "<< firstReg << ", #0"<< "\n";
                     
           }
    }
}

void CodeGenVisitor::visit(Identifier *node) {
    
}

void CodeGenVisitor::visit(Identifier *node, std::string reg) {
	if(adr) {
		middle << "  ADD " << reg << ", sp, #" << varMap->operator[](node->id) << "\n";
		return;
	}
  if(node->type->equals(new CharTypeId) || node->type->equals(new BoolTypeId())) {
    if(varMap->operator[](node->id) == 0) {
      middle << "  LDRB " << reg << ", [sp]\n";
    } else { 
      middle << "  LDRB " << reg 
             << ", [sp, #" << varMap->operator[](node->id) << "]\n";
    }
  } else {
    if(varMap->operator[](node->id) == 0) {
      middle << "  LDR " << reg << ", [sp]\n";
    } else { 
      middle << "  LDR " << reg
             << ", [sp, #" << varMap->operator[](node->id) << "]\n";
    }
  }
}

void CodeGenVisitor::visit(ArrayElem *node){}

void CodeGenVisitor::visit(ArrayElem *node, std::string reg) {
    middle << "  ADD " << reg << ", sp ,#" << varMap->operator[](node->getId()) << "\n";
    for (int i=0; i < node->idxs->size(); i++) {
      node->idxs->operator[](i)->accept(this, "r6");
      if ( reg == "r0") {
        middle << "  PUSH {r0}\n";
      }
      middle << "  MOV r0, r6\n"
             << "  MOV r1, " << reg << "\n";
             //bound checking branch done here
      if(reg == "r0") {
        middle << "  POP {r0}\n";        
      }
      middle << "  LDR " << reg << ", [" << reg << "]\n"
             << "  ADD " << reg << ", " << reg << ", #4\n";
      if(node->type->size() == 1) {
        middle << "  ADD " << reg << ", " << reg << ", r6\n";
      } else {
        middle << "  ADD " << reg << ", " << reg << ", r6, LSL #2\n";
      }
    }
    middle << "  LDR " << reg << ", ["<< reg << "]\n";
}

void CodeGenVisitor::visit(PairElem *node){}
void CodeGenVisitor::visit(PairElem *node, std::string reg) {}

void CodeGenVisitor::visit(ArrayLiter *node, std::string reg) {
  ArrayId *arrType = dynamic_cast<ArrayId*>(node->type);
  int elemSize = arrType->elementType->size();
  int mallocSize = (node->elems->size() * elemSize) + 4;
  middle << "  LDR r0,=" <<  mallocSize << "\n"
         << "  BL malloc\n"
         << "  MOV " << reg << ", r0\n";
  for(int i = node->elems->size(); i > 0; i--) {
    node->elems->operator[](i-1)->accept(this, "r5");
    middle << "  STR r5, [" << reg << ", #"<< mallocSize - i*elemSize << "]\n";
  }
  middle << "  LDR r5, =" << node->elems->size() << "\n";
  middle << "  STR r5, [" << reg << "]\n";
}

void CodeGenVisitor::visit(UnaryOperator *node, std::string reg) {
   int oper = node -> op;
   node->expr->accept(this, reg);
   if(oper == tok ::TOK_MINUS){
        middle << "  RSBS "<< reg << ", " << reg << ", #0"<< std::endl
               << "  BLVS p_throw_overflow_error" << std::endl
               << "  MOV r0, "<< reg << std::endl;
        p_throw_overflow_error();
   }else if(oper == tok::TOK_BANG){
        node->expr->accept(this, reg);
        middle << "  EOR "<< reg << ", " << reg << ", #1" << std::endl
               << "  MOV r0, " << reg << std::endl;
   }else if(oper == tok::TOK_LEN){
   //add implementation for len
   }else if(oper == tok::TOK_ORD){
   }else if(oper == tok::TOK_CHR){
   }
}

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
   middle << "  LDR r0, =" << node->snd->type->size() << "\n"
          << "  BL malloc\n";
   if (node->snd->type->equals(new CharTypeId)
        || node->snd->type->equals(new BoolTypeId)) {
     middle << "  STRB r5, [r0]\n";
   }
   else {
     middle << "  STR r5, [r0]\n";
   }
   middle << "  STR r0, [r4, #4]\n";

}

void CodeGenVisitor::p_check_divide_by_zero(void){ 
    if(!p_check_divide_by_zerob){
      if (!beginInitialisation) {
      beginInitialisation = true;
      begin <<
        ".data" << "\n"
            << "\n";
      }
        end     << "p_check_divide_by_zero:"<< "\n"
                << "  PUSH {lr}" << "\n"
                << "  CMP r1, #0" << "\n"
                << "  LDREQ r0, =msg_"<<messageNum << "\n"
                << "  BLEQ p_throw_runtime_error" << "\n"
                << "  POP {pc}" << "\n";
        begin   << "msg_"<< messageNum << ":"<< "\n"
                << "  .word 45" << "\n"
                << "  .ascii \" DivideByZeroError : divide or modulo by zero \\n\\0\""<< "\n";

                messageNum ++ ; 
        p_check_divide_by_zerob = true;
       p_throw_runtime_error();
    }
}

void CodeGenVisitor::p_throw_overflow_error(void){
    if(!p_throw_overflow_errorb){
      if (!beginInitialisation) {
      beginInitialisation = true;
      begin <<
        ".data" << "\n"
            << "\n";
      }
        end     << "p_throw_overflow_error: " << "\n"

                << "  LDR r0, =msg_"<< messageNum<< "\n"
                << "  BL p_throw_runtime_error  " << "\n";
        begin   << "msg_"<< messageNum << ":"<<"\n"
                << "  .word 82"<< "\n"
                << "  .ascii \"OverflowError: the result is too small/large to store in a 4 byte signed integer \\n\""<<"\n";

        messageNum ++ ; 
        p_throw_overflow_errorb = true;

        p_throw_runtime_error();
    }
}

void CodeGenVisitor::p_throw_runtime_error(void){
    if(!p_throw_runtime_errorb){
      if (!beginInitialisation) {
      beginInitialisation = true;
      begin <<
        ".data" << "\n"
            << "\n";
      }
         end    << "p_throw_runtime_error:" << "\n"
         "  BL p_print_string" << "\n";
             if (!msgString) {
               msgString  = true;
               begin <<
                  "msg_" << messageNum << ":" << std::endl <<
                  "  .word 5" << std::endl <<
                  "  .ascii  \"%.*s\\0\"" << std::endl;
                 stringMessageNum = messageNum;
                 messageNum ++ ;

              }
               end << "  MOV r0, #-1" << "\n"
                << "  BL exit"<< "\n";

        p_throw_runtime_errorb = true;
        if (!p_print_string) {
          p_print_string = true;
          printAssemblyOfPrintString();
        }
    }

}

void CodeGenVisitor::populateRegMap() {
	for (int i = 4; i < MAX_REG_NUMBER - 1; ++i) {
		regTable->insert(std::pair <std::string, bool>
										(std::string("R" + std::to_string(i)), true));
	}
}

std::string CodeGenVisitor::getAvailableRegister() {
	for (auto it = regTable->begin(); it != regTable->end(); ++it) {
		if(it->second) {
			it->second = false;
			return it->first;
		}
	}
	//std::cerr << "ERROR. There are no available registers";
  return "r4";
}

void CodeGenVisitor::freeRegister(std::string reg) {
	regTable->find(reg)->second = true;
}
