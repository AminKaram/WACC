#include "symbol-table.hh"

SymbolTable::SymbolTable(Symboltable *encScope) : encScope(encScope) {
  dictionary = new std::map<std::string, SemanticId>();    
}

SymbolTable::~SymbolTable() {
  delete encScope;
  encScope = NULL;
  dictionnary.clear();
  delete dictionary;
  dictionnary = NULL;
}

SemanticId*
SymbolTable::lookUp(std::string id) {
  auto it = dictionary.find(id);
  if (it != dictionary.end()) {
    return it->second;
  }
  return NULL;
}

SemanticId* 
SymbolTable::lookUpAll(std::string id) {
  SymbolTable *s = this;
  while(s) {
    SemanticId *val = s->lookUp(id);
    if(val) return val;
    s = this->encScope;
  }
  return NULL;
}

int
SymbolTable::add(std::string id, SemanticId val) {
  bool in = dicitonnary.insert(std::pair<std::string, SemanticId>(id, val))->second;
  return (!in);
}
