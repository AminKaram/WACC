#ifndef SEMANTIC_ID_HH
#define SEMANTIC_ID_HH
#include "astnode.hh"


class SemanticId {
public:
  ASTnode* astnode;
  SemanticId(ASTnode* astnode);
  virtual ~SemanticId();
};


class TypeId : public SemanticId {
public:
  TypeId(ASTnode* astnode);
  bool equals(TypeId *other);
};

class IntTypeId : public TypeId {
public:
  IntTypeId(ASTnode* astnode);
};

class BoolTypeId : public TypeId {
public:
  BoolTypeId(ASTnode* astnode) : TypeId(astnode) {}
};

class CharTypeId : public TypeId {
public:
  CharTypeId(ASTnode* astnode);
};

class StringTypeId : public TypeId {
public:
  StringTypeId(ASTnode* astnode);
};

class VariableId : public SemanticId {
public:
  TypeId *type;
  VariableId(ASTnode* astnode, TypeId *type);
};

class ParamId : public SemanticId {
public:
  TypeId *type;
  ParamId(ASTnode* astnode, TypeId *type);
};

class ArrayId : public TypeId {
public:
  TypeId *elementType = new TypeId(NULL);
  ArrayId(ASTnode* astnode, TypeId *elementType);
  bool equals(ArrayId *other);
};

class PairId : public TypeId {
public:
  TypeId *fst;
  TypeId *snd;
  PairId(ASTnode* astnode, TypeId *fst, TypeId *snd);
  bool equals(PairId *other);
};

class PairKeyId : public TypeId {
public:
  PairKeyId(ASTnode *astnode);
};

class FunctionId : public SemanticId {
public:
  TypeId *returnType;
  std::vector<ParamId> params;
  FunctionId(ASTnode* astnode, TypeId *ret, std::vector<ParamId> params);
};

class NullId : public PairId {
public:
  NullId();
};

#endif // ! SEMANTIC_ID_HH

