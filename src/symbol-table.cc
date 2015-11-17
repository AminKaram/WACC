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
  for (auto ite=dictionary->begin(); ite != dictionary->end(); ite++) {
    //std::cout<< "id: " << ite->first << std::endl;
  }
  auto it = dictionary->find(id);
  if (it != dictionary->end()) {
    //std::cout << &(it->second) << "lookUp" << std::endl;
    return &(it->second);
  }
  //std::cout<<"look up fails"<<std::endl;
  return NULL;
}

SemanticId* SymbolTable::lookUpAll(std::string id) {
  SymbolTable *s = this;
  while(s) {
    SemanticId *val = s->lookUp(id);
    if(val) { return val;}
    s = s->encScope;
  }
  //std::cerr << " hey in lookup" << std::endl;
  return NULL;
}

int SymbolTable::add(std::string id, SemanticId& val) {
  auto ret = dictionary->insert(std::pair<std::string, SemanticId&>(id, val));
  if(ret.second) {
    return 0;
  }
  //std::cerr << "semantic error: Redefined variable." << id << std::endl;
  exit(200);
}

SymbolTable* SymbolTable::getEncScope() {
  return encScope;
}
