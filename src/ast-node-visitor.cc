#include "ast-node-visitor.hh"

SemanticId*
AstNodeVisitor::lookUp(std::string& id) {
  std::map<std::string, SemanticId>::iterator it = symbolTables.find(id);
  if(it != symbolTables.end()) {
     return &(symbolTable[id]);
  } 
  return NULL;
}

SemanticId*
AstNodeVisitor::lookUpAll(std::string& id) {
  for(auto it = symbolTables.begin(); it != symbolTables.end(); it++) {
    SemanticId *obj =  
  }
}

