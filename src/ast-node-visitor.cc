#include "ast-node-visitor.hh"

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


//void AstNodeVisitor::visit(RepeatStatement *node) {
//	
//}


void AstNodeVisitor::visit(ExitStatement *node) {
}


void AstNodeVisitor::visit(ReadStatement *node) {
}


void AstNodeVisitor::visit(PrintStatement *node) {
}


void AstNodeVisitor::visit(PrintlnStatement *node) {
}



