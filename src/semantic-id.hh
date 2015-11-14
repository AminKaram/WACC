v#ifndef SEMANTIC_ID_HH
#define SEMANTIC_ID_HH
#include "astnode.hh"


class SemanticId { 
  AstNode& astnode;
  SemanticId(AstNode& astnode) : astnode(astnode) { } 
}

class Type : public SemanticId {
  Type(AstNode& astnode) : SemanticId(astnode) { } 
}

class Variable : public SemanticId {
  Type type;
  Variable(AstNode& astnode, Type type) : SemanticId(astnode), type(type) { }
}

class Param : public SemanticId {
  Type type;
  Param(AstNode& astnode, Type type) : SemanticId(astnode), type(type) { }
}

class Array : public Type {
  Type elementType;
  Array(AstNode& astnode, Type elementType) : SemanticId(astnode),
                                              elementType(elementType) {}
}

class Function : public SemanticId {
  Type returnType;
  std::vector<Param> params;
  Function(Astnode& astnode, Type ret, std::vector<Param> params)
      : SemanticId(astnode), returnType(ret), params(params) { }
}

#endif // ! SEMANTIC_ID_HH
