#ifndef SEMANTIC_ID_HH
#define SEMANTIC_ID_HH
#include "astnode.hh"


class SemanticId {
public:
  std::string name;
  ASTnode* astnode;
  SemanticId(ASTnode* astnode, std::string name) : astnode(astnode), name(name) { }
  virtual ~SemanticId() {}
};


class TypeId : public SemanticId {
public:
  TypeId(ASTnode* astnode, std::string type) : SemanticId(astnode, type) { }
};

class IntTypeId : public TypeId {
public:
  IntTypeId(ASTnode* astnode) : TypeId(astnode, "int") { }
};

class BoolTypeId : public TypeId {
public:
  BoolTypeId(ASTnode* astnode) : TypeId(astnode, "bool") { }
};

class CharTypeId : public TypeId {
public:
  CharTypeId(ASTnode* astnode) : TypeId(astnode, "char") { }
};

class StringTypeId : public TypeId {
public:
  StringTypeId(ASTnode* astnode) : TypeId(astnode, "string") { }
};

class VariableId : public SemanticId {
public:
  TypeId type;
  VariableId(ASTnode* astnode, TypeId type) : SemanticId(astnode, type.name), type(type) { }
};

class ParamId : public SemanticId {
public:
  TypeId type;
  ParamId(ASTnode* astnode, TypeId type) : SemanticId(astnode, type.name), type(type) { }
};

class ArrayId : public TypeId {
public:
  TypeId elementType;
  ArrayId(ASTnode* astnode, TypeId elementType) : TypeId(astnode, "array"),
                                    elementType(elementType) { }
};

class PairId : public TypeId {
public:
  TypeId fst;
  TypeId snd;
  PairId(ASTnode* astnode, TypeId fst, TypeId snd) : TypeId(astnode, "pair"),
                                                     fst(fst),
                                                     snd(snd) { }
};

class FunctionId : public SemanticId {
public:
  TypeId returnType;
  std::vector<ParamId> params;
  FunctionId(ASTnode* astnode, TypeId ret, std::vector<ParamId> params) 
    : SemanticId(astnode, "function"), returnType(ret), params(params) { }
};

#endif // ! SEMANTIC_ID_HH

