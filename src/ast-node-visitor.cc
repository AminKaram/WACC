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
  return new NullId();
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
    return new ArrayTypeId(NULL, typeBuilder(type->type));
  } else if(pairKeyword) {
    return new PairKeyId(NULL);
  } else if(PairType) {
    return new PairId(NULL, typeBuilder(type->fst), typeBuilder(type->snd));
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

}

void AstNodeVisitor::visit(StatSeq *node) {
  std::cout << "StatSeqVisitor" << std::endl;
  for(int i = 0; i < node->statements.size(); i++) {
    (node->statements)[i]->accept(this);
  }
}

void AstNodeVisitor::visit(VariableDeclaration *node) {
  std::cout << "VariableDeclarationVisitor" << std::endl;
  SemanticId *type = typeBuilder(node->type);
  SemanticId *var = scope->lookUp(node->id->id);
  if (!type) {
    std::cerr<< "Unknown type" << node->type->name << std::endl;
    exit(200);
  }
  TypeId * t = dynamic_cast<TypeId*> (type);
  if (!t) {
    std::cerr<< "Is not a type" << node->type->name << std::endl;
    exit(200);
  }
  if (var) {
    std::cerr<< "Already declared" << node->id->id << std::endl;
    exit(200);
  }
  node->rhs->accept(this);
  if (!(*lookUpExpr(node->rhs)->equals(type))) {
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
  VariableId variable(node, *t);
  scope->add(node->id->id, variable);
  std::cout << "VariableDeclarationVisitor end " << variable.name << std::endl;
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
  std::vector<ParamId> params;
  for(int i=0; i < parameters->size(); i++) {
    TypeId *paramType = typeBuilder(parameters->operator[](i)->type);
    params.push_back(ParamId(NULL, paramType))
  }
  FunctionId tmp(NULL, returnType, params);
  scope->add(node->id->id, tmp);
  scope = new SymbolTable(scope);
  scope->add("", returnType)
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
      << std::end;
    exit(200);
  }

  for(int i = 0; i < node->parameters->size(); i++) {
    node->parameters->operator[](i)->accept(this);
    TypeId *paramId = lookUpExpr(node->parameters->operator[](i));
    if(!paramId.equals(func->params.operator[](i))) {
      std::cerr << "Incorrect argument type in function call " << node->id->id << std::endl;
      exit(200);
    }  
  }
  addExpression(node,func->returnType);
}

void AstNodeVisitor::visit(Assignment *node) {
  std::cout << "AssignmentVisitor" << std::endl;
  node->lhs->accept(this);
  node->rhs->accept(this);
  SemanticId *value = scope->lookUpAll(node->lhs->getId());
  if(!value) {
    std::cerr << "semantic error: assigning to undeclared identifier" << node->lhs->getId() << std::endl;
    exit(200);
  }
  if(value->name != node->rhs->type) {
    std::cerr << "Invalid type in assignment of " << node->lhs->getId() << " of type " 
      << value->name << "as opposed to " << node->rhs->type << std::endl;
    exit(200);
  }
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
	if (node->expr->type != "bool") {
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
	if (node->expr->type != "bool") {
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
	  if((node->left->type != node->right->type) || (node->left->type != "bool")) {
		  std::cerr << "Expected bool type for operands &&,||" 
					<< std::endl;
		  exit(200);
	  }
	  node->type = "bool";
	} else if((oper >= tok::TOK_SLASH) && (oper <= tok::TOK_MINUS)) {
	  if((node->left->type != node->right->type) || (node->left->type != "int")) {
		  std::cerr << "Expected int type for operands /,*,%,+,-"
					<< std::endl;
		  exit(200);
	  }
	  node->type = "int";
	} else if((oper >= tok::TOK_LESS) && (oper <= tok::TOK_GREATEREQUALS)) {
	  if ((node->left->type != node->right->type) || (node->left->type != "int" || node->left->type != "char")) {
			std::cerr << "Expected type int/char for operators <,<=,>,>=" 
					  << std::endl;
			exit(200);
	  }
	  node->type = "bool";
	} else if((oper == tok::TOK_EQUALS) || (oper == tok::TOK_NOTEQUALS)) {
	  if((node->left->type != node->right->type)) {
		  std::cerr << "lhs and rhs types do not match for operators ==,!="
					<< std::endl;
	  }
	  node->type = "bool";
	}
  }

void AstNodeVisitor::visit(ArrayElem *node) {
  std::cout << "ArrayElemVisitor" << std::endl;
  SemanticId *value = scope->lookUpAll(node->id->id);
  if(!value) {
    std::cerr << "Cannot access non declared array elem" << std::endl;
    exit(200);
  } else if(value->name != "array") {
    std::cerr << "Type mismatch cannot access element of non array variable" 
              << std::endl;
    exit(200);
  }
  ArrayId* arr = dynamic_cast<ArrayId*> (value);
  node->AssignLhs::type = arr->elementType.name;
}

void AstNodeVisitor::visit(PairElem *node) {
  std::cout << "PairElemVisitor" << std::endl;
  node->expr->accept(this);
  if(node->expr->type != "pair") {
    std::cerr << "Type mismatch cannot get pair element of non pair expression" 
              << std::endl;
    exit(200);
  } 
  // Do something to set pair elem type
}

void AstNodeVisitor::visit(UnaryOperator *node) {
  std::cout << "UnaryOperatorVisitor" << std::endl;
  node->expr->accept(this);
  int oper = node->op;
  if( oper == tok::TOK_BANG) {
	if(node->expr->type != "bool") {
		std::cerr << "Operand of ! is not a bool" << std::endl;
		exit(200);
	} 
	node->type = "bool";
  } else if(oper == tok::TOK_MINUS) { 
	if( node->expr->type != "int") {
	  std::cerr << "Operand of - is not an int" << std::endl;
	  exit(200);
	}
	node->type = "int";
  } else if(oper == tok::TOK_ORD) {
	if(node->expr->type == "char") {
		std::cerr << "Operand of ord is not a char" << std::endl;
		exit(200);
	}
	node->type = "int";
  } else if(oper == tok::TOK_CHR) {
	if(node->expr->type == "int") {
		std::cerr << "Operand of chr is not an int" << std::endl;
		exit(200);
	}
	node->type = "char";
  } 
}

void AstNodeVisitor::visit(FreeStatement *node) {
  std::cout << "FreeStatementVisitor" << std::endl;
  node->expr->accept(this);
  if (node->expr->type != "pair") {
    std::cerr << "semantic error freeing a non pair type expression" << std::endl;
    exit(200);
  }
}

void AstNodeVisitor::visit(ReturnStatement *node) {
  std::cout << "ReturnStatementVisitor" << std::endl;
  node->expr->accept(this);
  if(node->expr->type != scope->lookUpAll("")->name) {
    std::cerr << "semantic error : wrong return type " << node->expr->type 
              << " instead of " << scope->lookUpAll("")->name << std::endl;
    exit(200);
  }
}

void AstNodeVisitor::visit(ExitStatement *node) { 
  std::cout << "ExitStatementVisitor" << std::endl;
  node->expr->accept(this);
  if(node->expr->type != "int") {
    std::cerr << "semantic error : wrong exit type, expected int got: " << node->expr->type
              << std::endl;
    exit(200);
  }
}

void AstNodeVisitor::visit(Number *node) {
}

void AstNodeVisitor::visit(Boolean *node) {
}

void AstNodeVisitor::visit(Char *node) {
}

void AstNodeVisitor::visit(String *node) {
}

void AstNodeVisitor::visit(NewPair *node) {
}

void AstNodeVisitor::visit(ArrayLiter *node) {
}

void AstNodeVisitor::visit(PairType *node) {
}

void AstNodeVisitor::visit(Null *node) {
}

void AstNodeVisitor::visit(ArrayType *node) {
}

void AstNodeVisitor::visit(Identifier *node) {
}
