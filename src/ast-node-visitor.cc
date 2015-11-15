include "ast-node-visitor.hh"
#include "symbol-table.hh"

void AstNodeVisitor::visit(VariableDeclaration *node) {
  semanticId *T = lookUpAll(node->type->name);
  semanticId *V = lookUp(node->id->id);
  
  if (!T) {
    std::cerr<< "Unknown type" << node->type->name << endl;
  }


void AstNodeVisitor::visit(Program *node) {
   scope.add("int", IntType(NULL));
   scope.add("char", CharType(NULL));
   scope.add("string", StringType(NULL));
   scope.add("bool", BoolType(NULL));
   scope.add("array", Array(NULL)); 
   scope = SymbolTable(scope);
   node->functions.accept(this);
   node->statements.accept(this);
}

void AstNodeVisitor::visit(StatSeq *node) {
  for(int i = 0; i < node->statements.size(); i++) {
    (node->statements)[i]->accept(this)
  }
}

void AstNodeVisitor::visit(FuncDecList *node) {
  for(int i = 0; i < node->statements.size(); i++) {
    (node->funcs)[i]->accept(this)
  }
}

void AstnodeVisitor::visit(FunctionDeclaration *node) {
  std::vector<Param> params;
  for(int i = 0; i < node->parameters->size(); i++) {
    params.push_back(Param((*(node->parameters))[i],
                              lookUpAll((*(node->parameters))[i]->type->name)));
  }
  function tmp(*node, scope.lookUpAll(node->type->name), params);
  scope.add(node->id->id, tmp);
  scope = SymbolTable(scope);
  scope.add("", tmp.returnType);
  for (int i = 0; i < node->parameters->size(); i++) {
    ((node->parameters)[i])->accept(this);
  }
  node->block->accept(this);
}

void AstNodeVisitor::visit(BeginStatement *node) {
	scope = SymbolTable(scope);
	node->scope.accept(this);	
}

void AstNodeVisitor::visit(IfStatement *node) {
	scope = SymbolTable(scope);
	node->expr.accept(this);	
	if (node->expr != bool) {
		std::cerr << "Type requiered: bool. Actual type: " 
																									<< node->expr << std::endl;
		exit(200); 
	}
	node->thenS.accept(this);	
	node->elseS.accept(this);	
}


void AstNodeVisitor::visit(WhileStatement *node) {
  scope = SymbolTable(scope);	
	node->expr.accept(this);	
	if (node->expr != bool) {
		std::cerr << "Type of expression in while requiered: bool. Actual type: " 
																									<< node->expr << std::endl;
		exit(200); 
	}
	node->doS.accept(this);	
}


void AstNodeVisitor::visit(ExitStatement *node) {
}


void AstNodeVisitor::visit(ReadStatement *node) {
}


void AstNodeVisitor::visit(PrintStatement *node) {
}


void AstNodeVisitor::visit(PrintlnStatement *node) {
}

  else if (
    
}
