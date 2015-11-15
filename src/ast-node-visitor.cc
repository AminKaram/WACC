include "ast-node-visitor.hh"
#include "symbol-table.hh"

void AstNodeVisitor::visit(VariableDeclaration *node) {
  semanticId *T = lookUpAll(node->type->name);
  semanticId *V = lookUp(node->id->id);
  
  if (!T) {
    std::cerr<< "Unknown type" << node->type->name << endl;
  }

  else if (
    
}
