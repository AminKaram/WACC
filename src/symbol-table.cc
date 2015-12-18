#include "symbol-table.hh"
#include "astnode.hh"
#include <iostream>

SymbolTable::SymbolTable(SymbolTable *encScope) : encScope(encScope) {
  dictionary = new std::map<std::string, SemanticId&>();    
  variables  = new std::vector<VariableDeclaration*>();
  varMap     = new std::map<std::string, int>();
  isDefined = new std::set<std::string>();
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
    if(val) {return val;}
    s = s->encScope;
  }

  return NULL;
}

int SymbolTable::add(std::string id, SemanticId& val) {
  auto ret = dictionary->insert(std::pair<std::string, SemanticId&>(id, val));
  if(ret.second) {
    return 0;
  }
  std::cerr << "semantic error: Redefined variable " << id << std::endl;
  exit(200);
}

void SymbolTable::addOffset(std::string id, int offset) {
  varMap->insert(std::pair<std::string, int>(id, offset));
}

int SymbolTable::addVariable(VariableDeclaration *var) {
  VariableId *variable = new VariableId(var->type);
  int res = add(var->id->id, *variable);
  variables->push_back(var);
  return res;
}

SymbolTable* SymbolTable::getEncScope() {
  return encScope;
}

Maybe<int> SymbolTable::getOffsetScope(std::string varName) {
  Maybe<int> res;
  auto it = varMap->find(varName);
  if (it != varMap->end() && isDefined->find(varName) != isDefined->end()) {
    res.valid = true;
    res.data = (it->second);
    return res;
  }
  res.valid = false;
  res.data = 0;
  return res;
}

int SymbolTable::searchOffset(std::string id) {
  SymbolTable *s = this;
  int offset = 0;
  while(s) {
    Maybe<int> val = s->getOffsetScope(id);
    if(val.valid)  {
      return offset + val.data + callOffset;
    }
    for (int i = 0; i < s->variables->size(); i++) {
      offset += s->variables->operator[](i)->type->size();
    }
    s = s->encScope;
  }
  Maybe<int> defaultRes = {0, false};
  return defaultRes.data;
}
