#ifndef SYMBOL_TABLE_HH
#define SYMBOL_TABLE_HH
#include "semantic-id.hh"
#include <map>
#include <string>
#include "maybe.hh"

class VariableDeclaration;

class SymbolTable {
public:
  SymbolTable(SymbolTable*);
  ~SymbolTable();

  SemanticId* lookUp(std::string);
  SemanticId* lookUpAll(std::string);
  Maybe<int> searchOffset(std::string);
  int add(std::string, SemanticId&);
  void addOffset(std::string, int);
  int addVariable(VariableDeclaration*);
  SymbolTable* getEncScope();
  std::vector<VariableDeclaration*> *variables = NULL;

private:
  Maybe<int> getOffsetScope(std::string);
  SymbolTable *encScope = NULL;
  std::map<std::string, SemanticId&> *dictionary = NULL;
  std::map<std::string, int> *varMap = NULL;
  
  
};

#endif
