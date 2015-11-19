#include "symbol-table.hh"

SymbolTable::SymbolTable(SymbolTable *encScope) : encScope(encScope) {
  dictionary = new std::map<std::string, SemanticId&>();    
}

SymbolTable::~SymbolTable() {
  encScope = NULL;
  delete dictionary;
  dictionary = NULL;
}

SemanticId* SymbolTable::lookUp(std::string id) {

  auto it = dictionary->find(id);
  if (it != dictionary->end()) {
    return &(it->second);
  }
  return NULL;
}

SemanticId* SymbolTable::lookUpAll(std::string id) {
  SymbolTable *s = this;
  while(s) {
    SemanticId *val = s->lookUp(id);
    if(val) { return val;}
    s = s->encScope;
  }

  return NULL;
}

int SymbolTable::add(std::string id, SemanticId& val) {
  auto ret = dictionary->insert(std::pair<std::string, SemanticId&>(id, val));
  if(ret.second) {
    return 0;
  }
  std::cerr << "semantic error: Redefined variable." << id << std::endl;
  exit(200);
}

SymbolTable* SymbolTable::getEncScope() {
  return encScope;
}
