#ifndef SEMANTIC_ID_HH
#define SEMANTIC_ID_HH
#include "astnode.hh"


class SemanticId {
public:
  ASTnode* astnode;
  SemanticId() { }
  SemanticId(ASTnode* astnode) : astnode(astnode){ }
  virtual ~SemanticId() {}
};


class TypeId : public SemanticId {
public:
  TypeId(ASTnode* astnode) : SemanticId(astnode) { }
  bool equals(TypeId *other);
};

class IntTypeId : public TypeId {
public:
  IntTypeId(ASTnode* astnode) : TypeId(astnode) { }
};

class BoolTypeId : public TypeId {
public:
  BoolTypeId(ASTnode* astnode) : TypeId(astnode) { }
};

class CharTypeId : public TypeId {
public:
  CharTypeId(ASTnode* astnode) : TypeId(astnode) { }
};

class StringTypeId : public TypeId {
public:
  StringTypeId(ASTnode* astnode) : TypeId(astnode) { }
};

class VariableId : public SemanticId {
public:
  TypeId type;
  VariableId(ASTnode* astnode, TypeId type) : SemanticId(astnode), type(type) { }
};

class ParamId : public SemanticId {
public:
  TypeId type;
  ParamId(ASTnode* astnode, TypeId type) : SemanticId(astnode), type(type) { }
};

class ArrayId : public TypeId {
public:
  TypeId elementType;
  ArrayId(ASTnode* astnode, TypeId elementType) : TypeId(astnode),
                                    elementType(elementType) { }
  bool equals(ArrayId *other);
};

class PairId : public TypeId {
public:
  TypeId fst;
  TypeId snd;
  PairId(ASTnode* astnode, TypeId fst, TypeId snd) : TypeId(astnode),
                                                     fst(fst),
                                                     snd(snd) { }
  bool equals(PairId *other);
};

class PairKeyId : public TypeId {
public:
  PairKeyId(ASTnode *astnode) : TypeId(astnode) { }
};

class FunctionId : public SemanticId {
public:
  TypeId returnType;
  std::vector<ParamId> params;
  FunctionId(ASTnode* astnode, TypeId ret, std::vector<ParamId> params) 
    : SemanticId(astnode), returnType(ret), params(params) { }
};

class NullId : public TypeId {
public:
  NullId() : TypeId(NULL){}
};

#endif // ! SEMANTIC_ID_HH

