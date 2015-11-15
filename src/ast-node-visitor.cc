#include "ast-node-visitor.hh"
#include "astnode.hh"
#include "semantic-id.hh"


void AstNodeVisitor::visit(Program *node) {
   scope.add("int", IntTypeId(NULL));
   scope.add("char", CharTypeId(NULL));
   scope.add("string", StringTypeId(NULL));
   scope.add("bool", BoolTypeId(NULL));
   scope.add("array", ArrayId(NULL, TypeId(NULL, "type")));
   scope.add("pair", PairId(NULL, TypeId(NULL, "type"), TypeId(NULL, "type")));
   scope = SymbolTable(scope);
   scope.add("", IntTypeId(NULL)); 
   node->functions->accept(this);
   node->statements->accept(this);
}

void AstNodeVisitor::visit(StatSeq *node) {
  for(int i = 0; i < node->statements.size(); i++) {
    (node->statements)[i]->accept(this);
  }
}

void AstNodeVisitor::visit(VariableDeclaration *node) {
  SemanticId *T = scope.lookUpAll(node->type->name);
  SemanticId *V = scope.lookUp(node->id->id);

  if (!T) {
    std::cerr<< "Unknown type" << node->type->name << std::endl;
  }
}

void AstNodeVisitor::visit(FunctionDecList *node) {
  for(int i = 0; i < node->funcs.size(); i++) {
    (node->funcs)[i]->accept(this);
  }
}

void AstNodeVisitor::visit(FunctionDeclaration *node) {
  std::vector<ParamId> params;
  for(int i = 0; i < node->parameters->size(); i++) {
    VariableDeclaration *var = node->parameters->operator[](i);
    ParamId tmp(var, scope.lookUpAll((*(node->parameters))[i]->type->name));
    params.push_back(tmp);
  }
  Function tmp(*node, scope.lookUpAll(node->type->name), params);
  scope.add(node->id->id, tmp);
  scope = SymbolTable(scope);
//Empty string represents the return type variable must have names  
  scope.add("", tmp.returnType);
  for (int i = 0; i < node->parameters->size(); i++) {
    ((node->parameters)[i])->accept(this);
  }
  node->block->accept(this);
}

void AstNodeVisitor::visit(Functioncall *node) {
  FunctionId *value = scope.lookUpAll(node->id->id);
  for(int i = 0; i < node->parameters->size(); i++) {
    if(!(((node->parameters)[i])->type == (value->params)[i].type.namei)) {
      std::cerr << "Incorrect argument type in function call " << node->id->id
        << std::endl;
      exit(200);
    }  
  }
  node->type = value->returnType.name;
}

void AstNodeVisitor::visit(Assignment *node) {
  node->lhs->accept(this);
  node->rhs->accept(this);
  SemanticId *value = scope.lookUpAll(node->lhs->id);
  if(value->name != node->rhs->type) {
    std::cerr << "Invalid type in assignment of " << node->lhs->id << " of type " 
      << value->name << "as opposed to " << node->rhs->type << std::endl;
    exit(200);
  }
}

void AstNodeVisitor::visit(BeginStatement *node) {
	scope = SymbolTable(scope);
	node->scope.accept(this);	
}

void AstNodeVisitor::visit(IfStatement *node) {
	scope = SymbolTable(scope);
	node->expr.accept(this);	
	if (node->expr->type != "bool") {
		std::cerr << "Type requiered: bool. Actual type: " 
			 << node->expr->type << std::endl;
		exit(200); 
	}
	node->thenS.accept(this);	
	node->elseS.accept(this);	
}


void AstNodeVisitor::visit(WhileStatement *node) {
  scope = SymbolTable(scope);	
	node->expr.accept(this);	
	if (node->expr->type != "bool") {
		std::cerr << "Type of expression in while requiered: bool. Actual type: " 
             << node->expr->type << std::endl;
		exit(200); 
	}
	node->doS.accept(this);	
}

void AstNodeVisitor::visit(ReadStatement *node) {
  SemanticId *value = scope.lookUpAll(node->lhs->id);
  if(!value) {
    std::cerr << "Cannot read undeclared variable: " << node->lhs->id 
              << std::endl;
    exit(200);
  }
}

void AstNodeVisitor::visit(PrintStatement *node) {
  SemanticId *value = scope.lookUpAll(node->lhs->id);
  if(!value) {
    std::cerr << "Cannot print undeclared variable: " << node->lhs->id 
              << std::endl;
    exit(200);
  }
}

void AstNodeVisitor::visit(PrintLnStatement *node) {
  SemanticId *value = scope.lookUpAll(node->lhs->id);
  if(!value) {
    std::cerr << "Cannot println undeclared variable: " << node->lhs->id 
              << std::endl;
    exit(200);
  }
}

void AstNodeVisitor::visit(BinaryOperator *node) {
  node->left->accept(this);
  node->right->accept(this);
  if(node->left->type != node->right->type) {
    std::cerr << "Types in binary op do not match" << std::endl;
    exit(200);
  }
  node->type = "int";
}

void AstNodeVisitor::visit(ArrayElem *node) {
 ArrayId *value = scope.lookUpAll(node->id->id);
  if(!value) {
    std::cerr << "Cannot access non declared array elem" << std::endl;
    exit(200);
  } else if(value->name != "array") {
    std::cerr << "Type mismatch cannot access element of non array variable" 
              << std::endl;
    exit(200);
  }
  node->type = value->elementType->name;
}

void AstNodeVisitor::visit(PairElem *node) {
  node->expr->accept(this);
  if(node->expr->type != "pair") {
    std::cerr << "Type mismatch cannot get pair element of non pair expression" 
              << std::endl;
    exit(200);
  } 
  // Do something to set pair elem type
}

void AstNodeVisitor::visit(UnaryOperator *node) {
  node->expr->accept(this);
  if(node->expr->type != "int") {
    std::cerr << "Type mismatch, cannot apply unary operation to " <<
      node->expr->type << std::endl;
    exit(200);
  }
  node->type = "int";
}
