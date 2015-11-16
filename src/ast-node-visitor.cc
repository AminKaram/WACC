#include "ast-node-visitor.hh"
#include "astnode.hh"
#include "semantic-id.hh"

AstNodeVisitor::AstNodeVisitor() {
  scope = new SymbolTable();
}

AstNodeVisitor::~AstNodeVisitor() {
  delete scope;
  scope = NULL;
}

void AstNodeVisitor::visit(ASTnode *node){

}

void AstNodeVisitor::visit(Program *node) {
  std::cout << "Program" << std::endl;
  scope->add(&"int", &IntTypeId(NULL));
  std::cout << " add" << std::endl;
  scope->add(&"char", &CharTypeId(NULL));
  scope->add(&"string", &StringTypeId(NULL));
  scope->add(&"bool", &BoolTypeId(NULL));
  scope->add(&"array", &ArrayId(NULL, TypeId(NULL, "type")));
  scope->add(&"pair", &PairId(NULL, TypeId(NULL, "type"), TypeId(NULL, "type")));
  std::cout << "CREATE SCOPE" << std::endl;
  scope = new SymbolTable(scope);
  scope->add(&"", &IntTypeId(NULL)); 
  node->functions->accept(this);
  node->statements->accept(this);
}

void AstNodeVisitor::visit(StatSeq *node) {
  std::cout << "StatSeq" << std::endl;
  for(int i = 0; i < node->statements.size(); i++) {
    (node->statements)[i]->accept(this);
  }
}

void AstNodeVisitor::visit(VariableDeclaration *node) {
  std::cout << "VariableDeclaration" << std::endl;
  SemanticId *type = scope->lookUpAll(node->type->name);
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
}

void AstNodeVisitor::visit(FunctionDecList *node) {
  std::cout << "FunctionDecList" << std::endl;
  for(int i = 0; i < node->funcs.size(); i++) {
    (node->funcs)[i]->accept(this);
  }
}

void AstNodeVisitor::visit(FunctionDeclaration *node) {
  std::cout << "FunctionDeclaration" << std::endl;
  std::vector<ParamId> params;
  SemanticId *type;
  for(int i = 0; i < node->parameters->size(); i++) {
    VariableDeclaration *var = node->parameters->operator[](i);
    type = scope->lookUpAll((*(node->parameters))[i]->type->name);
         if (!type) {
        std::cerr<< "Unknown type " << (*(node->parameters))[i]->type->name << std::endl;
        exit(200);
      }
      TypeId * t = dynamic_cast<TypeId* > (type);
      if (!t) {
        std::cerr<< "Is not a type" << (*(node->parameters))[i]->type->name << std::endl;
        exit(200);
      }
    ParamId tmp(var, *t);
    params.push_back(tmp);
  }
  type = scope->lookUpAll(node->type->name);
  SemanticId *func = scope->lookUp(node->id->id);
  if (!type) {
    std::cerr<< "Unknown type " << node->type->name << std::endl;
    exit(200);
  }
  TypeId * t = dynamic_cast<TypeId* > (type);
  if (!t) {
    std::cerr<< "Is not a type" << node->type->name << std::endl;
    exit(200);
  }
  if (!func) {
    std::cerr<< "Already declared" << node->type->name << std::endl;
    exit(200);
  }
  FunctionId tmp(node, *t, params);
  scope->add(node->id->id, &tmp);
  scope =  new SymbolTable(scope);
//Empty string represents the return type variable must have names  
  scope->add(&"", &tmp.returnType);
  for (int i = 0; i < node->parameters->size(); i++) {
    (*(node->parameters))[i]->accept(this);
  }
  node->block->accept(this);
  SymbolTable* oldScope = scope->getEncScope();
  delete scope;
  scope = oldScope;
}

void AstNodeVisitor::visit(FunctionCall *node) {
  std::cout << "FunctionCall" << std::endl;
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
  for(int i = 0; i < node->parameters->size(); i++) {
    if(((func->params)[i].type.name) != (node->parameters->operator[](i)->type)) {
      std::cerr << "Incorrect argument type in function call " << node->id->id << std::endl;
      exit(200);
    }  
  }
  node->type = func->returnType.name;
}

void AstNodeVisitor::visit(Assignment *node) {
  std::cout << "Assignment" << std::endl;
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
  std::cout << "BeginStatement" << std::endl;
	scope = new SymbolTable(scope);;
	node->scope->accept(this);
  SymbolTable *tmp = scope->getEncScope();
  delete scope;
  scope = tmp;
}

void AstNodeVisitor::visit(IfStatement *node) {
  std::cout << "IfStatement" << std::endl;
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
  std::cout << "WhileStatement" << std::endl;
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
  std::cout << "ReadStatement" << std::endl;
  SemanticId *value = scope->lookUpAll(node->id->getId());
  if(!value) {
    std::cerr << "Cannot read undeclared variable: " << node->id->getId() 
              << std::endl;
    exit(200);
  }
}

void AstNodeVisitor::visit(PrintStatement *node) {
  std::cout << "PrintStatement" << std::endl;
  node->expr->accept(this);
//  SemanticId *value = scope->lookUpAll(node->->getId());
//  if(!value) {
//    std::cerr << "Cannot print undeclared variable: " << node->id->getId() 
//              << std::endl;
//    exit(200);
//  }
}

void AstNodeVisitor::visit(PrintlnStatement *node) {
  std::cout << "PrintlnStatement" << std::endl;
  node->expr->accept(this);
//  SemanticId *value = scope->lookUpAll(node->->getId());
//  if(!value) {
//    std::cerr << "Cannot println undeclared variable: " << node->id->getId() 
//              << std::endl;
//    exit(200);
//  }
}

void AstNodeVisitor::visit(BinaryOperator *node) {
  std::cout << "BinaryOperator" << std::endl;
  node->left->accept(this);
  node->right->accept(this);
  if(node->left->type != node->right->type) {
    std::cerr << "Types in binary op do not match" << std::endl;
    exit(200);
  }
  node->type = "int";
}

void AstNodeVisitor::visit(ArrayElem *node) {
  std::cout << "ArrayElem" << std::endl;
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
  std::cout << "PairElem" << std::endl;
  node->expr->accept(this);
  if(node->expr->type != "pair") {
    std::cerr << "Type mismatch cannot get pair element of non pair expression" 
              << std::endl;
    exit(200);
  } 
  // Do something to set pair elem type
}

void AstNodeVisitor::visit(UnaryOperator *node) {
  std::cout << "UnaryOperator" << std::endl;
  node->expr->accept(this);
  if(node->expr->type != "int") {
    std::cerr << "Type mismatch, cannot apply unary operation to " <<
      node->expr->type << std::endl;
    exit(200);
  }
  node->type = "int";
}

void AstNodeVisitor::visit(FreeStatement *node) {
  std::cout << "FreeStatement" << std::endl;
  node->expr->accept(this);
  if (node->expr->type != "pair") {
    std::cerr << "semantic error freeing a non pair type expression" << std::endl;
    exit(200);
  }
}

void AstNodeVisitor::visit(ReturnStatement *node) {
  std::cout << "ReturnStatement" << std::endl;
  node->expr->accept(this);
  if(node->expr->type != scope->lookUpAll("")->name) {
    std::cerr << "semantic error : wrong return type " << node->expr->type 
              << " instead of " << scope->lookUpAll("")->name << std::endl;
  }
}

void AstNodeVisitor::visit(ExitStatement *node) { 
  std::cout << "ExitStatement" << std::endl;
  node->expr->accept(this);
  if(node->expr->type != "int") {
    std::cerr << "semantic error : wrong exit type, expected int got: " << node->expr->type
              << std::endl;
  }
}

void AstNodeVisitor::visit(Number *node) {
  std::cout << "Number" << std::endl;
}

void AstNodeVisitor::visit(Boolean *node) {
  std::cout << "Boolean" << std::endl;
}

void AstNodeVisitor::visit(Char *node) {
  std::cout << "Char" << std::endl;
}

void AstNodeVisitor::visit(String *node) {
  std::cout << "String" << std::endl;
}

void AstNodeVisitor::visit(NewPair *node) {
  std::cout << "NewPair" << std::endl;
}

void AstNodeVisitor::visit(ArrayLiter *node) {
  std::cout << "ArrayLiter" << std::endl;
}

void AstNodeVisitor::visit(PairType *node) {
  std::cout << "PairType" << std::endl;
}

void AstNodeVisitor::visit(Null *node) {
  std::cout << "Null" << std::endl;
}

void AstNodeVisitor::visit(ArrayType *node) {
  std::cout << "ArrayType" << std::endl;
}

void AstNodeVisitor::visit(Identifier *node) {
  std::cout << "Identifier" << std::endl;
}