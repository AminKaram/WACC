#ifndef SEMANTIC_ID_HH
#define SEMANTIC_ID_HH
#include "astnode.hh"
#include <string>

class SemanticId {
public:
  ASTnode* astnode;
  SemanticId(ASTnode* astnode);
  virtual ~SemanticId() { }
};


class TypeId : public SemanticId {
public:
  TypeId(ASTnode* astnode);
  virtual ~TypeId() = 0;
  bool virtual equals(TypeId *other) = 0;
  std::string virtual name() = 0; 
};

class IntTypeId : public TypeId {
public:
  IntTypeId(ASTnode* astnode);
  bool equals(TypeId *other);
  std::string name(); 
};

class BoolTypeId : public TypeId {
public:
  BoolTypeId(ASTnode* astnode);
  bool equals(TypeId *other);
  std::string name(); 
};

class CharTypeId : public TypeId {
public:
  CharTypeId(ASTnode* astnode);
  bool equals(TypeId *other);
  std::string name(); 
};

class StringTypeId : public TypeId {
public:
  StringTypeId(ASTnode* astnode);
  bool equals(TypeId *other);
  std::string name(); 
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
  TypeId *elementType;
  ArrayId(ASTnode* astnode, TypeId *elementType);
  bool equals(TypeId *other);
  std::string name(); 
};

class PairId : public TypeId {
public:
  TypeId *fst;
  TypeId *snd;
  PairId(ASTnode* astnode, TypeId *fst, TypeId *snd);
  bool equals(TypeId *other);
  std::string name(); 
};

class PairKeyId : public PairId {
public:
  PairKeyId(ASTnode *astnode);
  bool equals(TypeId *other);
  std::string name(); 
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
  bool equals(TypeId *other);
  std::string name(); 
};

#endif // ! SEMANTIC_ID_HH

