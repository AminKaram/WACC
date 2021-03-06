#include "code-generation-visitor.hh"
#include "parser.hh"
#define tok yy::parser::token::yytokentype

std::string CodeGenVisitor::allocateStack(int bytes) {
  std::string res = "";
  int tmp = bytes;
  while(tmp > 1024) {
    res += "  SUB sp, sp, #1024\n";
    tmp -= 1024;
  }
  if(tmp > 0) {
    res += "  SUB sp, sp, #" + std::to_string(tmp) + "\n";
  }
  return res;
}

std::string CodeGenVisitor::deallocateStack(int bytes) {
  std::string res = "";
  int tmp = bytes;
  while(tmp > 1024) {
    res += "  ADD sp, sp, #1024\n";
    tmp -= 1024;
  }
  if(tmp > 0) {
    res += "  ADD sp, sp, #" + std::to_string(tmp) + "\n";
  }
  return res;
}


CodeGenVisitor::CodeGenVisitor(std::ostream* stream) {
  file   = stream;
  regTable = new std::map<std::string, bool>();
  populateRegMap();
}

CodeGenVisitor::~CodeGenVisitor() { }

void CodeGenVisitor::visit(Program *node) {

  middle << ".text" << std::endl<< "\n"
         << ".global main" << "\n";

  node->functions->accept(this);
  currentScope = node->statements->table;
  currentScope->callOffset = 0;
  scopeSize = 0;
  for (int i = 0; i < node->statements->table->variables->size(); i++) {
    scopeSize += node->statements->table->variables->operator[](i)->type->size();
  }
  middle << "main:"       << "\n"
         << "  PUSH {lr}\n";

  middle << allocateStack(scopeSize);
  int temp = scopeSize;
  scopeSize += 4;
  node->statements->accept(this);
  scopeSize = temp;
  middle << deallocateStack(scopeSize)
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
  currentScope->callOffset = 0;
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
  if(node->rhs) {
    Expression* expr = dynamic_cast <Expression*> (node->rhs);
    std::cout << "wtf" << std::endl;
    if (expr) {
      std::cout<<"why" << std::endl;
      node->rhs = expr->optimise();
    }
   node->rhs->accept(this, "r4");
  }
  PairElem   *pairrhs = dynamic_cast<PairElem*>(node->rhs);
  if (pairrhs) {
    if(pairrhs->type->size() == 1) {
                middle << "  LDRSB r4, [r4]\n";
              } else {
                middle << "  LDR r4, [r4]\n";
              }
  }
  int sizeSoFar = 0;
  for (int i = currentScope->variables->size()-1; i >=0; i--) {
    if(currentScope->variables->operator[](i)->id->id.compare(node->id->id) == 0) {
    break;
   }
   sizeSoFar += currentScope->variables->operator[](i)->type->size();
  }
  int offset = sizeSoFar;
  if (node->type->equals(new BoolTypeId()) || node->type->equals(new CharTypeId())) {
     middle << "  STRB r4, [sp" << (offset == 0 ? "" : ", #" + std::to_string(offset)) << "]\n";
  } else {
    middle << "  STR r4, [sp"<< (offset == 0 ? "" : ", #" + std::to_string(offset)) << "]\n";
  }
  currentScope->isDefined->insert(node->id->id);
  currentScope->addOffset(node->id->id, offset);
}

void CodeGenVisitor::visit(FunctionDeclaration *node) {
  middle << "f_" << node->id->id << ":\n"
         << "  PUSH {lr}" << "\n";
  currentScope = node->block->table;
  currentScope->callOffset = 0;
  int scopeSize = 0;
  for (int i=0; i < node->block->table->variables->size(); i++) {
        scopeSize += node->block->table->variables->operator[](i)->type->size();
  }
  middle << allocateStack(scopeSize);
  sizeLocals = scopeSize;
  scopeSize+=4;
  int scope = scopeSize;
  for(int i = 0; i < node->parameters->size(); i++) {
    scope = node->parameters->operator[](i)->accept(this, scope);
  }
  node->block->accept(this);
  middle << "  POP {pc}" << "\n"
           << "  .ltorg"   << "\n";
  currentScope->callOffset = 0;
}


void CodeGenVisitor::visit(FunctionCall *node, std::string reg) {
  int sizeParam = 0;
    for(int i = node->parameters->size() - 1; i >= 0; i--) {
      node->parameters->operator[](i) = node->parameters->operator[](i)->optimise();
      node->parameters->operator[](i)->accept(this, reg);
      if(node->parameters->operator[](i)->type->size() > 1) {
        middle << "  STR " << reg << ", [sp, #-" 
               <<  node->parameters->operator[](i)->type->size() 
               << "]!\n";

      } else {
        middle << "  STRB " << reg << ", [sp, #-" 
               <<  node->parameters->operator[](i)->type->size() 
               << "]!\n";
      }
      sizeParam += node->parameters->operator[](i)->type->size();
      currentScope->callOffset += sizeParam;
    }


    middle << "  BL f_" << node->id->id << "\n"
           << "  ADD sp, sp, #" << sizeParam << "\n" 
           << "  MOV " << reg << ",r0 \n";
    currentScope->callOffset = 0;
}

void CodeGenVisitor::visit(Assignment *node) {

  node->rhs->accept(this, "r4");
  //node->lhs->accept(this); //might be wrong
  BoolTypeId *boolType = new BoolTypeId();
  CharTypeId *charType = new CharTypeId();
  PairElem   *pairlhs = dynamic_cast<PairElem*>(node->lhs);
  PairElem   *pairrhs = dynamic_cast<PairElem*>(node->rhs);
  ArrayElem *arrLhs = dynamic_cast<ArrayElem*>(node->lhs);



  if (pairrhs) {
    if(pairrhs->type->size() == 1) {
                middle << "  LDRSB r4, [r4]\n";
              } else {
                middle << "  LDR r4, [r4]\n";
              }
  }

  if (pairlhs) {
    node->lhs->accept(this, "r5");
    if(pairlhs->type->size() == 1) {
            middle << "  STRB r4, [r5]\n";
          } else {
            middle << "  STR r4, [r5]\n";
          }
  } else if(arrLhs) {
    printMsgCheckArrayBounds();
      if(!p_print_array_elem ) {
          p_print_array_elem = true;
          printAssemblyCheckArrayBounds();
      }
    middle << "  ADD r5, sp ,#" << currentScope->searchOffset(node->lhs->getId()) << "\n";
    for (int i=0; i < arrLhs->idxs->size(); i++) {
      arrLhs->idxs->operator[](i)->accept(this, "r6");
      middle << "  LDR r5, [r5]\n"
             << "  MOV r0, r6\n"
             << "  MOV r1, r5\n"
             //bound checking branch done here
             << "  ADD r5, r5, #4\n";
      if(arrLhs->type->size() == 1) {
        middle << "  ADD r5, r5, r6, LSL #0\n"
               << "  STRB r4, [r5]\n";
      } else {
        middle << "  ADD r5, r5, r6, LSL #2\n"
               << "  STR r4, [r5]\n";
      } 
    }
  }
   else if(node->lhs->type->equals(boolType) || node->lhs->type->equals(charType)) {
    if (currentScope->searchOffset(node->lhs->getId()) == 0) {
      middle << "  STRB r4, [sp]\n";
    } else {
      middle << "  STRB r4, [sp, #" << currentScope->searchOffset(node->lhs->getId()) 
             << "]\n";
    }
  } else {
      if (currentScope->searchOffset(node->lhs->getId()) == 0) {
        middle << "  STR r4, [sp]\n";
      } else {
        middle << "  STR r4, [sp, #" << currentScope->searchOffset(node->lhs->getId())
               << "]\n";
      }
  }
}


void CodeGenVisitor::visit(FreeStatement *node) {
         node->expr = node->expr->optimise();
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
               << "  POP {pc}"<< std::endl;
 if (!beginInitialisation) {
  beginInitialisation = true;
  begin << 
    ".data" << "\n"
        << "\n";
  }
  
         begin << "msg_"<< messageNum <<":"<<std::endl
               << "  .word 50"<< std::endl
               << "  .ascii \"NullReferenceError: dereference a null reference\\n\\0\""<< std::endl; 
        messageNum ++;
         p_throw_runtime_error();
        
        p_free_pairb = true;
        
    }
         
}


void CodeGenVisitor::visit(ReturnStatement *node) {
  node->expr = node->expr->optimise();
  node->expr->accept(this, "r0");
  middle << deallocateStack(sizeLocals);
  middle << "  POP {pc}" << std::endl;

}

void CodeGenVisitor::visit(ExitStatement *node) {
  node->expr = node->expr->optimise();
  node->expr->accept(this, "r0");

  middle << "  BL exit"    << "\n";

}

void CodeGenVisitor::visit(BeginStatement *node) {
  SymbolTable *prevScope = currentScope;
  currentScope = node->scope->table;
  scopeSize = 0;
  for (int i = 0; i < node->scope->table->variables->size(); i++) {
    scopeSize += node->scope->table->variables->operator[](i)->type->size();
  }

    middle << allocateStack(scopeSize);
    int temp = scopeSize;
    node->scope->accept(this);
    scopeSize= temp;
    middle << deallocateStack(scopeSize);
    currentScope = prevScope;
}

void CodeGenVisitor::visit(IfStatement *node) {
  node->expr = node->expr->optimise();
  node->expr->accept(this, "r4");
  labelNum+= 2;
  int tmp = labelNum;
  middle << "  CMP r4, #0\n"
         << "  BEQ L" << std::to_string(labelNum - 2)     << "\n";
  SymbolTable *prevScope = currentScope;
  currentScope = node->thenS->table;
    scopeSize = 0;
    for (int i = 0; i < node->thenS->table->variables->size(); i++) {
      scopeSize += node->thenS->table->variables->operator[](i)->type->size();
    }
  middle << allocateStack(scopeSize);
      int temp = scopeSize;
      node->thenS->accept(this);
      scopeSize = temp;
      middle << deallocateStack(scopeSize);
  labelNum = tmp;

  middle << "  B L"  << std::to_string(labelNum - 1)              << "\n"
          << "L"      << std::to_string(labelNum - 2)   << ":" << "\n";

  currentScope = node->elseS->table;
    scopeSize = 0;
    for (int i = 0; i < node->elseS->table->variables->size(); i++) {
      scopeSize += node->elseS->table->variables->operator[](i)->type->size();
    }

  middle << allocateStack(scopeSize);
      temp = scopeSize;
      node->elseS->accept(this);
      scopeSize = temp;
      middle << deallocateStack(scopeSize);
  labelNum = tmp;

  middle << "L" << std::to_string(labelNum -1) << ":"  << "\n";
  currentScope = prevScope;
}

void CodeGenVisitor::visit(WhileStatement *node) {
  node->expr = node->expr->optimise();
  labelNum += 2;
  int temp = labelNum;
  middle << "  B L" << std::to_string(labelNum - 2) << "\n";
  middle << "L" << std::to_string(labelNum - 1) << ":" << "\n";
  currentScope = node->doS->table;
      scopeSize = 0;
      for (int i = 0; i < node->doS->table->variables->size(); i++) {
        scopeSize += node->doS->table->variables->operator[](i)->type->size();
      }

    middle << allocateStack(scopeSize);
        int tmp = scopeSize;
        node->doS->accept(this);
        scopeSize = tmp;
        middle << deallocateStack(scopeSize);
  labelNum = temp;
  middle << "L" << std::to_string(labelNum - 2) << ": " << "\n";
  currentScope = currentScope->getEncScope();
  node->expr->accept(this, "r4");
  middle << "  CMP r4, #1"                                << "\n"

          << "  BEQ L" << std::to_string(labelNum - 1)         << "\n";
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
      if (!msgChar) {
        msgChar = true;
        begin << 
           "msg_" << messageNum << ":" << std::endl <<
           "  .word 4" << std::endl <<
           "  .ascii  \" %c\\0\"" << std::endl;
        charMessageNum = messageNum;
        messageNum++;
      }
  } else if(intTypeId) {
      middle <<
          "  BL p_read_int" << "\n";
      if (!msgInt){
        msgInt = true;
        begin << 
           "msg_" << messageNum << ":" << std::endl <<
           "  .word 3" << std::endl <<
           "  .ascii  \"%d\\0\"" << std::endl;
        intMessageNum = messageNum;
        messageNum++;
      }
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
    ArrayId *arrayTypeId       = dynamic_cast<ArrayId*> (type);
    PairId *pairTypeId         = dynamic_cast<PairId*> (type);

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
        intMessageNum = messageNum;
        messageNum++;
      }
  		
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
	  } else if(arrayTypeId || pairTypeId) {
      //std::cout << "  BL p_print_reference" << "\n";
      middle << "  BL p_print_reference" << "\n";
      
      if (!msgReference) {
        msgReference = true;
        begin << 
           "msg_" << messageNum << ":" << std::endl <<
           "  .word 3" << std::endl <<
           "  .ascii  \"%p\\0\"" << std::endl;
        referenceMessageNum = messageNum;
        printAssemblyOfPrintReference();
        messageNum++;
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

void CodeGenVisitor::printAssemblyOfPrintReference() {
  end <<
    "p_print_reference: " << std::endl<<
    "  PUSH {lr}" << std::endl<<
    "  MOV r1, r0" << std::endl<<
    "  LDR r0, =msg_" << referenceMessageNum << std::endl<<
    "  ADD r0, r0, #4" << std::endl<<
    "  BL printf" << std::endl<<
    "  MOV r0, #0" << std::endl<<
    "  BL fflush" << std::endl<<
    "  POP {pc}" << "\n";
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
  //std::cout << "printStatement" << "\n";
	if (!p_print_string && type->equals(new StringTypeId())) {
	  p_print_string = true;
		printAssemblyOfPrintString();
	} else if (!p_print_bool && type->equals(new BoolTypeId())) {
			p_print_bool = true;
			printAssemblyOfPrintBool();
	} else if (!p_print_int && type->equals(new IntTypeId())) {
			p_print_int = true;
			printAssemblyOfPrintInt();
	} else if (!p_print_reference && type->equals(new ArrayId(type))) {
    //std::cout << "printStatement" << "\n";
      p_print_reference = true;
      printAssemblyOfPrintReference();
    }
  //std::cout << "printStatement" << "\n";
}

void CodeGenVisitor::visit(PrintStatement *node) {
  //std::cout << "visit0" << "\n";
  node->expr = node->expr->optimise();
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
  node->expr = node->expr->optimise();
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
  //std::cout<< "visit Number" << std::endl;
  middle << "  LDR " << reg << ", =" << node->value << std::endl;
}
void CodeGenVisitor::visit(Boolean *node, std::string reg) {
  //std::cout<< "Boolean" << std::endl;
  bool val = node -> value;
  //middle << "  MOV " << reg << ", #" << node->value << std::endl;
  if(val == 0 ){
    middle << "  MOV " << reg << ", #0" << std::endl;
  } else {
    middle << "  MOV " << reg << ", #1" << std::endl;
  }
}
void CodeGenVisitor::visit(Char *node, std::string reg) {
  //std::cout<< "visit char" << std::endl;
  middle << "  MOV " << reg << ", #'" << node->value  << "'" << std::endl;
}

void CodeGenVisitor::visit(String *node, std::string reg) {
  //std::cout<< "visit String" << std::endl;
  int escapeChr = 0;
  if (!beginInitialisation) {
		beginInitialisation = true;
		begin << 
			".data" << "\n"
					<< "\n";
  }

  for (int i = 0; i < node->value.size() - 1; ++i ) {
    if((node->value.operator[](i) == '\\') && 
                                    (node->value.operator[](i + 1) != '\\')) {
        escapeChr++;    
    }
  }

  middle << 
		"  LDR " << reg << ", =msg_" << messageNum << "\n";
  begin  << 
		"msg_" << messageNum << ":" << std::endl<<
        "  .word " << node->value.size() - escapeChr - 2 << std::endl<<
        "  .ascii " << node->value << "\n";
  messageNum++;
         
}

void CodeGenVisitor::visit(Null *node, std::string reg) {
   middle << "  MOV " << reg << ", #0" << std::endl;
}


void CodeGenVisitor::visit(BinaryOperator *node, std::string reg) {


   int oper = node -> op;
         std::string firstReg  = reg;
         int tmp = atoi(reg.erase(0,1).c_str()) + 1;
         std::string secondReg = "r" + std::to_string(tmp);
         if (tmp > 10) { 
           secondReg = "r10";   
         }
         node->left->accept(this,firstReg);
         if(tmp > 10) {
           middle << "  PUSH {r10}\n";
         }
         node->right->accept(this,secondReg);
         if (tmp > 10) {
           middle << "  POP {r11}\n";
           firstReg = "r10";
           secondReg = "r11";
         }
     if(oper == tok::TOK_LOGOR || oper == tok::TOK_LOGAND){
        // if node left and right are both not constant
       
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
                    << " ASR #31" << "\n"

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
    middle << "  LDR " << reg << ", =0\n";
		middle << "  ADD " << reg << ", sp, #" << currentScope->searchOffset(node->id) << "\n";
    return;
	}
  if(node->type->equals(new CharTypeId) || node->type->equals(new BoolTypeId())) {

    if(currentScope->searchOffset(node->id) == 0) {
      middle << "  LDRSB " << reg << ", [sp]\n";
    } else { 
      middle << "  LDRSB " << reg 
             << ", [sp, #" << currentScope->searchOffset(node->id) << "]\n";
    }
  } else {
    if(currentScope->searchOffset(node->id) == 0) {
      middle << "  LDR " << reg << ", [sp]\n";
    } else { 
      middle << "  LDR " << reg
             << ", [sp, #" << currentScope->searchOffset(node->id) << "]\n";
    }
  }
}

void CodeGenVisitor::visit(ArrayElem *node){}

void CodeGenVisitor::printAssemblyCheckArrayBounds(){
  p_throw_runtime_error();
  end <<
    "p_check_array_bounds: " << std::endl <<
    "  PUSH {lr}" << std::endl <<
    "  CMP r0, #0" << std::endl<<
    "  LDRLT r0, =msg_" << checkArrayBoundMessageNum << std::endl <<
    "  BLLT p_throw_runtime_error" << std::endl <<
    "  LDR r1, [r1]" << std::endl<<
    "  CMP r0, r1" << std::endl<<
    "  LDRCS r0, =msg_" << checkArrayBoundMessageNum + 1 << std::endl <<
    "  BLCS p_throw_runtime_error" << std::endl <<
    "  POP {pc}" << "\n";
    
}

void CodeGenVisitor::printMsgCheckArrayBounds() {
  //ArrayId *arrayTypeId       = dynamic_cast<ArrayId*> (type);
  //  std::cout<< "print check" << std::endl;
  //if(arrayTypeId -> elementType) {
   // std::cout<< "print check" << std::endl;
  if (!beginInitialisation) {
      beginInitialisation = true;
      begin <<
        ".data" << "\n"
            << "\n";
   }
    if (!msgCheckArrayBound) {
      msgCheckArrayBound = true;
      begin << 
         "msg_" << messageNum << ":" << std::endl <<
         "  .word 44" << std::endl <<
         "  .ascii  \"ArrayIndexOutOfBoundsError: negative index\\n\\0\"" << std::endl;
      begin << 
         "msg_" << messageNum + 1 << ":" << std::endl <<
         "  .word 45" << std::endl <<
         "  .ascii  \"ArrayIndexOutOfBoundsError: index too large\\n\\0\"" << std::endl;
      checkArrayBoundMessageNum = messageNum;
      messageNum+=2;
    }
  //}
}

void CodeGenVisitor::visit(ArrayElem *node, std::string reg) {
  //TypeId *type = node->type;
    printMsgCheckArrayBounds();
    if(!p_print_array_elem ) {
        p_print_array_elem = true;
        printAssemblyCheckArrayBounds();
    }
    //std::cout << "visit ArrayElem" << std::endl;
    middle << "  ADD " << "r4" << ", sp ,#" << currentScope->searchOffset(node->getId()) << "\n";

    std::string tmpreg = "R4";
    for (int i=0; i < node->idxs->size(); i++) {
      node->idxs->operator[](i)->accept(this, "r5");


      middle << "  MOV r0, r5\n"
             << "  MOV r1, " << "r4" << "\n";

    middle << "  BL p_check_array_bounds" << std::endl; 
      printMsgCheckArrayBounds();


      middle << "  LDR " << "r4" << ", [r4]\n"
             << "  ADD " << "r4" << ", " << "r4" << ", #4\n";
      if(node->type->size() == 1) {
        middle << "  ADD " << "r4" << ", " << "r4" << ", r5\n";
      } else {
        middle << "  ADD " << "r4" << ", " << "r4" << ", r5, LSL #2\n";
      }
    }
    middle << "  LDR " << "r4" << ", ["<< "r4" << "]\n"
           << "  MOV " << reg << ", r4\n";

}

//LHS PairElem
void CodeGenVisitor::visit(PairElem *node){
  node->expr = node->expr->optimise();
  //adr = true;
  node->expr->accept(this, "r5");
  //adr = false;
  middle    << "  MOV r0, r5"              << std::endl   
            << "  BL p_check_null_pointer" << std::endl;

  p_check_null_pointer();
  
  if (node->fst){
    middle       << "  LDR r5, [r5]"          << std::endl;
    
  } else {
    middle   << "  LDR r5, [r5, #4]"      << std::endl;
  }

  
}

//RHS PairElem
// there is more to do here
void CodeGenVisitor::visit(PairElem *node, std::string reg) {
  //adr = true;
  node->expr->accept(this, reg);
  //adr = false;

  middle   << "  MOV r0, " << reg                        << std::endl 
           << "  BL p_check_null_pointer"                << std::endl;
  p_check_null_pointer();

  IntTypeId *intTypeId       = dynamic_cast<IntTypeId*>(node->type);
  StringTypeId *stringTypeId = dynamic_cast<StringTypeId*>(node->type);
  CharTypeId *charTypeId     = dynamic_cast<CharTypeId*>(node->type);
  BoolTypeId *boolTypeId     = dynamic_cast<BoolTypeId*>(node->type);

  if (node->fst){
      middle << "  LDR " << reg << ", [" << reg << "]"     << std::endl;

  } else {
      middle << "  LDR " << reg << ", [" << reg << ", #4]"     << std::endl;
  }
}

void CodeGenVisitor::visit(ArrayLiter *node, std::string reg) {
  ArrayId *arrType = dynamic_cast<ArrayId*>(node->type);
  int elemSize = 0;
  int typeSize = 0;
  if (!node->type->equals(new NullId())) {
    elemSize = arrType->elementType->size();
    typeSize = node->elems->size();
  }
  int mallocSize = (typeSize * elemSize) + 4;
  middle << "  LDR r0,=" <<  mallocSize << "\n"
         << "  BL malloc\n"
         << "  MOV " << reg << ", r0\n";
  for(int i = 0; i < node->elems->size();) {
    node->elems->operator[](i) = node->elems->operator [](i)->optimise();
    node->elems->operator[](i)->accept(this, "r5");
    middle << "  STR r5, [" << reg << ", #"<< ++i*elemSize << "]\n";
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
      middle << "  LDR " << reg << ", [" << reg << "]\n";  
   }else if(oper == tok::TOK_ORD){ 
   }else if(oper == tok::TOK_CHR){
   }
}

void CodeGenVisitor::visit(NewPair *node, std::string reg) {
  middle << "  LDR r0, =8\n"
         << "  BL malloc\n"
         << "  MOV r4, r0\n";
  node->fst = node->fst->optimise();
  node->fst->accept(this, "r5");

  middle << "  LDR r0, =" << node->fst->type->size() << "\n"
         << "  BL malloc\n";
   if (node -> fst -> type -> size() == 1) {
     middle << "  STRB r5, [r0]\n";
   }
   else {
     middle << "  STR r5, [r0]\n";
   }
   middle << "  STR r0, [r4]\n";
   node->snd = node->snd->optimise();
   node->snd->accept(this, "r5");
   middle << "  LDR r0, =" << node->snd->type->size() << "\n"
          << "  BL malloc\n";
   if (node->snd -> type ->size() == 1) {
     middle << "  STRB r5, [r0]\n";
   }
   else {
     middle << "  STR r5, [r0]\n";
   }
   middle << "  STR r0, [r4, #4]\n";

}

int CodeGenVisitor::visit(Param *node, int scope) {
   currentScope->addOffset(node->id->id, scope);
   currentScope->isDefined->insert(node->id->id);
   return scope + node->type->size();
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
    end << "p_throw_runtime_error:" << "\n"
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

void CodeGenVisitor::p_check_null_pointer(void){
  if (!p_check_null_pointerb){
    p_check_null_pointerb = true;

    if (!beginInitialisation) {
      beginInitialisation = true;
      begin <<
        ".data" << "\n"
            << "\n";
    }
    
    if (!msgNullPointer){
      msgNullPointer = true; 
      begin << "msg_" << messageNum << ":"                   << std::endl <<
               "  .word 50"                                  << std::endl <<
               "  .ascii  \"NullReferenceError: dereference" << 
                                 " a null reference\\n\\0\""   << std::endl;
      nullMessageNum = messageNum;
      messageNum++ ;
    }
    end << "p_check_null_pointer:"               << "\n"
           "  PUSH {lr}"                         << "\n"
           "  CMP r0, #0"                        << "\n"
           "  LDREQ r0, =msg_" << nullMessageNum << "\n"
           "  BLEQ p_throw_runtime_error"        << "\n"
           "  POP {pc}"                          << "\n";
    if (!p_throw_runtime_errorb) {
      p_throw_runtime_error();
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
