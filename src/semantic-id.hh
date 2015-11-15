#ifndef SEMANTIC_ID_HH
#define SEMANTIC_ID_HH
#include "astnode.hh"


class SemanticId { 
  ASTnode* astnode = NULL;
  SemanticId(ASTnode* astnode) : astnode(astnode) { }
};

class TypeId : public SemanticId {
  TypeId(ASTnode* astnode) : SemanticId(astnode) { }
};

class IntTypeId : public TypeId {
  IntTypeId(ASTnode* astnode) : TypeId(astnode) { }
};

class BoolTypeId : public TypeId {
  BoolTypeId(ASTnode* astnode) : TypeId(astnode) { }
};

class CharTypeId : public TypeId {
  CharTypeId(ASTnode* astnode) : TypeId(astnode) { }
};

class StringTypeId : public TypeId {
  StringTypeId(ASTnode* astnode) : TypeId(astnode) { }
};

class VariableId : public SemanticId {
  TypeId type;
  VariableId(ASTnode* astnode, TypeId type) : SemanticId(astnode), type(type) { }
};

class ParamId : public SemanticId {
  TypeId type;
  ParamId(ASTnode* astnode, TypeId type) : SemanticId(astnode), type(type) { }
};

class ArrayId : public TypeId {
  TypeId elementType;
  ArrayId(ASTnode* astnode) : SemanticId(astnode) { }
  ArrayId(ASTnode* astnode, TypeId elementType) : SemanticId(astnode),
                                              elementType(elementType) {}
};

class FunctionId : public SemanticId {
  TypeId returnType;
  std::vector<ParamId> params;
  FunctionId(ASTnode* astnode, TypeId ret, std::vector<ParamId> params)
      : SemanticId(astnode), returnType(ret), params(params) { }
};

#endif // ! SEMANTIC_ID_HH
