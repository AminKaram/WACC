#include "ast-node-visitor.hh"
#include "astnode.hh"
#include "semantic-id.hh"
#include "parser.hh"
#define tok yy::parser::token::yytokentype

AstNodeVisitor::AstNodeVisitor() {
  scope = new SymbolTable(NULL);
  exprTable = new std::map<ASTnode*, TypeId*>();
}

AstNodeVisitor::~AstNodeVisitor() {
  delete scope;
  scope = NULL;
}

void AstNodeVisitor::addExpression(ASTnode* node, TypeId* id) {
  exprTable->operator[](node) = id;
}

TypeId* AstNodeVisitor::lookUpExpr(ASTnode* node) {
  auto it = exprTable->find(node);
  if ( it != exprTable->end()) return it->second;
  return NULL;
}

TypeId* AstNodeVisitor::typeBuilder(Type* type){
  IntegerType *intType = dynamic_cast<IntegerType*>(type);
  BoolType *boolType = dynamic_cast<BoolType*>(type);
  CharType *charType = dynamic_cast<CharType*>(type);
  StringType *stringType = dynamic_cast<StringType*>(type);
  ArrayType *arrayType = dynamic_cast<ArrayType*>(type);
  PairKeyword *pairKeyword = dynamic_cast<PairKeyword*>(type);
  PairType *pairType = dynamic_cast<PairType*>(type);

  if(intType) {
    return new IntTypeId(NULL); 
  }  else if(boolType) {
    return new BoolTypeId(NULL);
  } else if(charType) {
    return new CharTypeId(NULL);
  } else if(stringType) {
    return new StringTypeId(NULL);
  } else if(arrayType) {
    return new ArrayId(NULL, *typeBuilder(arrayType->type));
  } else if(pairKeyword) {
    return new PairKeyId(NULL);
  } else if(pairType) {
    return new PairId(NULL, *typeBuilder(pairType->fst), *typeBuilder(pairType->snd));
  } else {
    return NULL;
  }
}


void AstNodeVisitor::visit(ASTnode *node){
}

void AstNodeVisitor::visit(Program *node) {
  std::cout << "ProgramVisitor" << std::endl;
  IntTypeId intId(NULL);
//  scope->add("int", intId);
//  CharTypeId charId(NULL);
//  scope->add("char", charId);
//  StringTypeId stringId(NULL);
//  scope->add("string", stringId);
//  BoolTypeId boolId(NULL);
//  scope->add("bool", boolId);
//  ArrayId arrayId(NULL, TypeId(NULL, "type"));
//  scope->add("array", arrayId);
//  PairId pairId(PairId(NULL, TypeId(NULL, "type"), TypeId(NULL, "type")));
//  scope->add("pair", pairId);
//  scope = new SymbolTable(scope);
  scope->add("", intId); 
  node->functions->accept(this);
  node->statements->accept(this);
}

void AstNodeVisitor::visit(AssignRhs *node) { 
  ArrayLiter *arrayLiter = dynamic_cast<ArrayLiter*>(node);
  NewPair *newPair = dynamic_cast<NewPair*>(node);
  Expression *expr = dynamic_cast<Expression*>(node);
  PairElem *pairElem = dynamic_cast<PairElem*>(node);

  if(arrayLiter) arrayLiter->accept(this);
  if(newPair) newPair->accept(this);
  if(expr) expr->accept(this);
  if(pairElem) pairElem->accept(this);
}

void AstNodeVisitor::visit(AssignLhs *node) {

}

void AstNodeVisitor::visit(Expression *node) {
  Identifier *ident = dynamic_cast<Identifier*>(node);
  FunctionCall *funcCall = dynamic_cast<FunctionCall*>(node);
  Number *number = dynamic_cast<Number*>(node);
  Boolean *boolean = dynamic_cast<Boolean*>(node);
  Char *charId = dynamic_cast<Char*>(node);
  String *stringId =dynamic_cast<String*>(node);
  Null *null = dynamic_cast<Null*>(node);
  BinaryOperator *binop = dynamic_cast<BinaryOperator*>(node);
  ArrayElem *arrayElem = dynamic_cast<ArrayElem*>(node);
  UnaryOperator *unop = dynamic_cast<UnaryOperator*>(node);

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

void AstNodeVisitor::visit(StatSeq *node) {
  std::cout << "StatSeqVisitor" << std::endl;
  for(int i = 0; i < node->statements.size(); i++) {
    (node->statements)[i]->accept(this);
  }
}

void AstNodeVisitor::visit(VariableDeclaration *node) {
  std::cout << "VariableDeclarationVisitor" << std::endl;
  TypeId *type = typeBuilder(node->type);
  SemanticId *var = scope->lookUp(node->id->id);
  if (!type) {
    std::cerr<< "is not a type" << node->type->name << std::endl;
    exit(200);
  }
  //TypeId *t = dynamic_cast<TypeId*> (type);
  if (var) {
    std::cerr<< "Already declared" << node->id->id << std::endl;
    exit(200);
  }
  node->rhs->accept(this);
  if (!(lookUpExpr(node->rhs)->equals(type))) {
    std::cerr<< "RHS has invalid type. expected" << node->id->id << std::endl;
    exit(200);
  }
//   std::cout << "VariableDeclarationVisitorbeforeaccept" << std::endl;
// // node->rhs->accept(this);
//   std::cout << "VariableDeclarationVisitorhey" << std::endl;
//  //std::cout<< "rhs is of type" << node->rhs->type << std::endl;
//   std::cout << "VariableDeclarationVisitor" << std::endl;
// // if (node->rhs->type != t->name) {
// //   std::cerr<< "RHS has invalid type. expected" << node->id->id << std::endl;
// //   exit(200);
// // }
  VariableId variable(node, *type);
  scope->add(node->id->id, variable);
}

void AstNodeVisitor::visit(FunctionDecList *node) {
  std::cout << "FunctionDecListVisitor" << std::endl;
  for(int i = 0; i < node->funcs.size(); i++) {
    (node->funcs)[i]->accept(this);
  }
}

void AstNodeVisitor::visit(FunctionDeclaration *node) {
  std::cout << "FunctionDeclarationVisitor" << std::endl;
  TypeId *returnType = typeBuilder(node->type);
  SemanticId retType  = *returnType;
  std::vector<ParamId> params;
  for(int i=0; i < node->parameters->size(); i++) {
    TypeId *paramType = typeBuilder(node->parameters->operator[](i)->type);
    params.push_back(ParamId(NULL, *paramType));
  }
  FunctionId func(NULL, *returnType, params);
  scope->add(node->id->id, func);
  scope = new SymbolTable(scope);
  scope->add("", retType);
  node->block->accept(this);
  SymbolTable *tmp = scope->getEncScope();
  delete scope;
  scope = tmp; 
}

void AstNodeVisitor::visit(FunctionCall *node) {
  std::cout << "FunctionCallVisitor" << std::endl;
  SemanticId *value = scope->lookUpAll(node->id->id);
  
  if (!value) {
    std::cerr<< "unknown function" << node->id->id << std::endl;
    exit(200);
  }
  FunctionId* func = dynamic_cast<FunctionId*> (value);
  if(!func) {
    std::cerr<< "is not a function" << node->id->id << std::endl;
    exit(200);
  }
  
  // add a clause to check for correct number of args
  if(node->parameters->size() != func->params.size()) {
    std::cerr << "semantic error: wrong number of arguments in function call"
      << std::endl;
    exit(200);
  }

  for(int i = 0; i < node->parameters->size(); i++) {
    node->parameters->operator[](i)->accept(this);
    TypeId *paramId = lookUpExpr(node->parameters->operator[](i));
    if(!paramId->equals(&func->params.operator[](i).type)) {
      std::cerr << "Incorrect argument type in function call " << node->id->id << std::endl;
      exit(200);
    }  
  }
  addExpression(node,&func->returnType);
}

void AstNodeVisitor::visit(Assignment *node) {
  std::cout << "AssignmentVisitor" << std::endl;
  node->lhs->accept(this);
  node->rhs->accept(this);
  TypeId *type = lookUpExpr(node->lhs);
  SemanticId *value = scope->lookUpAll(node->lhs->getId());
  if(!value) {
    std::cerr << "semantic error: assigning to undeclared identifier" << node->lhs->getId() << std::endl;
    exit(200);
  }
  if(lookUpExpr(node->rhs)->equals(type)) {
    std::cerr << "Invalid type in assignment of " << node->lhs->getId()
    << "as opposed to " << node->rhs->type << std::endl;
    exit(200);
  }
  // TODO:: Update variable value;
}

void AstNodeVisitor::visit(BeginStatement *node) {
  std::cout << "BeginStatementVisitor" << std::endl;
  scope = new SymbolTable(scope);;
	node->scope->accept(this);
  SymbolTable *tmp = scope->getEncScope();
  delete scope;
  scope = tmp;
}

void AstNodeVisitor::visit(IfStatement *node) {
  std::cout << "IfStatementVisitor" << std::endl;
  node->expr->accept(this);
	  if (!(lookUpExpr(node->expr)->equals(new BoolTypeId(NULL)))) {
		std::cerr << "Type requiered: bool. Actual type: " 
			 << node->expr->type << std::endl;
		exit(200); 
	}
  scope = new SymbolTable(scope);
	node->thenS->accept(this);
  SymbolTable *tmp = scope->getEncScope();
  delete scope;
  scope = new SymbolTable(tmp);
	node->elseS->accept(this);
  delete scope;
  scope = tmp;
}


void AstNodeVisitor::visit(WhileStatement *node) {
  std::cout << "WhileStatementVisitor" << std::endl;
  node->expr->accept(this);
  if (!(lookUpExpr(node->expr)->equals(new BoolTypeId(NULL)))) {
		std::cerr << "Type of expression in while requiered: bool. Actual type: " 
             << node->expr->type << std::endl;
		exit(200); 
	}
  scope = new SymbolTable(scope);	
	node->doS->accept(this);
  SymbolTable *tmp = scope->getEncScope();
  delete scope;
  scope = tmp;
}

void AstNodeVisitor::visit(ReadStatement *node) {
  std::cout << "ReadStatementVisitor" << std::endl;
  SemanticId *value = scope->lookUpAll(node->id->getId());
  if(!value) {
    std::cerr << "Cannot read undeclared variable: " << node->id->getId() 
              << std::endl;
    exit(200);
  }
}

void AstNodeVisitor::visit(PrintStatement *node) {
  std::cout << "PrintStatementVisitor" << std::endl;
  node->expr->accept(this);
//  SemanticId *value = scope->lookUpAll(node->->getId());
//  if(!value) {
//    std::cerr << "Cannot print undeclared variable: " << node->id->getId() 
//              << std::endl;
//    exit(200);
//  }
}

void AstNodeVisitor::visit(PrintlnStatement *node) {
  std::cout << "PrintlnStatementVisitor" << std::endl;
  node->expr->accept(this);
//  SemanticId *value = scope->lookUpAll(node->->getId());
//  if(!value) {
//    std::cerr << "Cannot println undeclared variable: " << node->id->getId() 
//              << std::endl;
//    exit(200);
//  }
}

void AstNodeVisitor::visit(BinaryOperator *node) {
  std::cout << "BinaryOperatorVisitor" << std::endl;
  node->left->accept(this);
  node->right->accept(this);
	int oper = node->op;
	if((oper == tok::TOK_LOGOR) || (oper == tok::TOK_LOGAND)) {
    if(!(lookUpExpr(node->left)->equals(lookUpExpr(node->right)))
       || (!(lookUpExpr(node->left)->equals(new BoolTypeId(NULL))))) {
		  std::cerr << "Expected bool type for operands &&,||" 
					<< std::endl;
		  exit(200);
	  }
    addExpression(node, new BoolTypeId(NULL));
	} else if((oper >= tok::TOK_SLASH) && (oper <= tok::TOK_MINUS)) {
	  if(!(lookUpExpr(node->left)->equals(lookUpExpr(node->right)))
       || (!(lookUpExpr(node->left)->equals(new IntTypeId(NULL))))) {
		  std::cerr << "Expected int type for operands /,*,%,+,-"
					<< std::endl;
		  exit(200);
	  }
    addExpression(node, new IntTypeId(NULL));
	} else if((oper >= tok::TOK_LESS) && (oper <= tok::TOK_GREATEREQUALS)) {
    if(!(lookUpExpr(node->left)->equals(lookUpExpr(node->right)))
       || (!(lookUpExpr(node->left)->equals(new IntTypeId(NULL)))
       || (!(lookUpExpr(node->left)->equals(new CharTypeId(NULL)))))) {
			std::cerr << "Expected type int/char for operators <,<=,>,>=" 
					  << std::endl;
			exit(200);
	  }
    addExpression(node, new BoolTypeId(NULL));
	} else if((oper == tok::TOK_EQUALS) || (oper == tok::TOK_NOTEQUALS)) {
	  if(!(lookUpExpr(node->left)->equals(lookUpExpr(node->right)))) {
		  std::cerr << "lhs and rhs types do not match for operators ==,!="
					<< std::endl;
	  }
    addExpression(node, new BoolTypeId(NULL));
	}
  }

void AstNodeVisitor::visit(ArrayElem *node) {
  std::cout << "ArrayElemVisitor" << std::endl;
  SemanticId *value = scope->lookUpAll(node->id->id);
  if(!value) {
    std::cerr << "Cannot access non declared array elem" << std::endl;
    exit(200);
  } 
  ArrayId* arr = dynamic_cast<ArrayId*> (value);
  if(!arr) {
    std::cerr <<"semantic error: identifier is not an array" << std::endl;
    exit(200);
  }
  addExpression(static_cast<ASTnode*>(static_cast<AssignLhs*>(node)), &(arr->elementType));
}

void AstNodeVisitor::visit(PairElem *node) {
  std::cout << "PairElemVisitor" << std::endl;
  node->expr->accept(this);
  if(!(lookUpExpr(node->expr)->equals(new PairId(NULL, NullId(), NullId())))) {
    std::cerr << "Type mismatch cannot get pair element of non pair expression" 
              << std::endl;
    exit(200);
  } 
    TypeId *typeId = lookUpExpr(node->expr);
    PairId *pairType = dynamic_cast<PairId*>(typeId);
    if(!pairType) {
      std::cout << "semantic error accessing elem of undefined pair" << std::endl;
      exit(200);
    }
    ASTnode *n = static_cast<ASTnode*>(static_cast<AssignLhs*>(node));
  if (node->fst) {
    addExpression(n, &(pairType->fst));
  } else {
    addExpression(n, &(pairType->snd));
  }
}

void AstNodeVisitor::visit(UnaryOperator *node) {
  std::cout << "UnaryOperatorVisitor" << std::endl;
  node->expr->accept(this);
  int oper = node->op;
  if( oper == tok::TOK_BANG) {
	if(!lookUpExpr(node->expr)->equals(new BoolTypeId(NULL))) {
		std::cerr << "Operand of ! is not a bool" << std::endl;
		exit(200);
	} 
  addExpression(node, new BoolTypeId(NULL));
  } else if(oper == tok::TOK_MINUS) {
  if(!lookUpExpr(node->expr)->equals(new IntTypeId(NULL))) {
	  std::cerr << "Operand of - is not an int" << std::endl;
	  exit(200);
	}
    addExpression(node, new IntTypeId(NULL));
  } else if(oper == tok::TOK_ORD) {
	if(!lookUpExpr(node->expr)->equals(new CharTypeId(NULL))) {
		std::cerr << "Operand of ord is not a char" << std::endl;
		exit(200);
	}
    addExpression(node, new IntTypeId(NULL));
  } else if(oper == tok::TOK_CHR) {
	if(!lookUpExpr(node->expr)->equals(new IntTypeId(NULL))) {
		std::cerr << "Operand of chr is not an int" << std::endl;
		exit(200);
	}
  addExpression(node, new CharTypeId(NULL));
  } 
}

void AstNodeVisitor::visit(FreeStatement *node) {
  std::cout << "FreeStatementVisitor" << std::endl;
  node->expr->accept(this);
  if(!(lookUpExpr(node->expr)->equals(new PairId(NULL, NullId(), NullId())))) {
    std::cerr << "semantic error freeing a non pair type expression" << std::endl;
    exit(200);
  }
}

void AstNodeVisitor::visit(ReturnStatement *node) {
  std::cout << "ReturnStatementVisitor" << std::endl;
  node->expr->accept(this);
  TypeId *rettype = lookUpExpr(scope->lookUpAll("")->astnode);
  if(!(lookUpExpr(node->expr)->equals(rettype))) {
    std::cerr << "semantic error : wrong return type " << node->expr->type;
    exit(200);
  }
}

void AstNodeVisitor::visit(ExitStatement *node) { 
  std::cout << "ExitStatementVisitor" << std::endl;
  node->expr->accept(this);
  if(!(lookUpExpr(node->expr)->equals(new IntTypeId(NULL)))) {
    std::cerr << "semantic error : wrong exit type, expected int got: " << node->expr->type
              << std::endl;
    exit(200);
  }
}

void AstNodeVisitor::visit(Number *node) {
  addExpression(node, new IntTypeId(NULL));
}

void AstNodeVisitor::visit(Boolean *node) {
  addExpression(node, new BoolTypeId(NULL));
}

void AstNodeVisitor::visit(Char *node) {
  addExpression(node, new CharTypeId(NULL));
}

void AstNodeVisitor::visit(String *node) {
  addExpression(node, new StringTypeId(NULL));
}

void AstNodeVisitor::visit(NewPair *node) {
  node->fst->accept(this);
  node->snd->accept(this);
  addExpression(node, new PairId(NULL, *lookUpExpr(node->fst), *lookUpExpr(node->snd))); 
}

void AstNodeVisitor::visit(ArrayLiter *node) {
  node->elems->operator[](0)->accept(this);
  TypeId* elemType = lookUpExpr(node->elems->operator[](0));
  for(int i=1; i < node->elems->size(); i++) {
    node->elems->operator[](i)->accept(this);
    TypeId* tmp = lookUpExpr(node->elems->operator[](i));
    if(!tmp->equals(elemType)) {
      std::cerr << "semantic error non matching types in array literal" << std::endl;
      exit(200);
    }
  }
  addExpression(node, new ArrayId(NULL, *elemType));
}

void AstNodeVisitor::visit(PairType *node) {
}

void AstNodeVisitor::visit(Null *node) {
  addExpression(node, new NullId());
}

void AstNodeVisitor::visit(ArrayType *node) {
}

void AstNodeVisitor::visit(Identifier *node) {
  SemanticId *type = scope->lookUpAll(node->id);
  TypeId *idType = dynamic_cast<TypeId *>(type);
  if(!idType) {
    std::cerr << "semantic error: variable is not declared " << node->id
              << std::endl;
    exit(200);
  }
  addExpression(static_cast<ASTnode*>(static_cast<AssignLhs*>(node)), idType);
}
