#include "ast-node-visitor.hh"

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
