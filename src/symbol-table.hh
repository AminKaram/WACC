#ifndef SYMBOL_TABLE_HH
#define SYMBOL_TABLE_HH
#include "semantic-id.hh"
#include <map>
#include <string>

class SymbolTable {
public:
  SymbolTable();
  SymbolTable(SymbolTable*);
  ~SymbolTable();

  SemanticId* lookUp(std::string);
  SemanticId* lookUpAll(std::string);
  int add(std::string, SemanticId);
  SymbolTable* getEncScope();

private:
  SymbolTable *encScope = NULL;
  std::map<std::string, SemanticId> *dictionary = NULL;
};

#endif
