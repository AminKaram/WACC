#ifndef SEMANTIC_ID_HH
#define SEMANTIC_ID_HH
#include <string>
#include <vector>

class SemanticId {
public:
  SemanticId();
  virtual ~SemanticId() { }
};

class TypeId : public SemanticId {
public:
  TypeId();
  virtual ~TypeId() = 0;
  bool virtual equals(TypeId *other) = 0;
  std::string virtual name() = 0; 
  int virtual size() = 0;
};

class IntTypeId : public TypeId {
public:
  IntTypeId();
  bool equals(TypeId *other);
  std::string name(); 
  int virtual size();
};

class BoolTypeId : public TypeId {
public:
  BoolTypeId();
  bool equals(TypeId *other);
  std::string name(); 
  int virtual size();
};

class CharTypeId : public TypeId {
public:
  CharTypeId();
  bool equals(TypeId *other);
  std::string name(); 
  int virtual size();
};

class StringTypeId : public TypeId {
public:
  StringTypeId();
  bool equals(TypeId *other);
  std::string name(); 
  int virtual size();
};

class VariableId : public SemanticId {
public:
  TypeId *type;
  VariableId(TypeId *type);
};

class ParamId : public SemanticId {
public:
  TypeId *type;
  ParamId(TypeId *type);
};

class ArrayId : public TypeId {
public:
  TypeId *elementType;
  ArrayId(TypeId *elementType);
  bool equals(TypeId *other);
  std::string name(); 
  int virtual size();
};

class PairId : public TypeId {
public:
  TypeId *fst;
  TypeId *snd;
  PairId(TypeId *fst, TypeId *snd);
  bool equals(TypeId *other);
  std::string name(); 
  int virtual size();
};

class PairKeyId : public PairId {
public:
  PairKeyId();
  bool equals(TypeId *other);
  std::string name(); 
  int virtual size();
};

class FunctionId : public SemanticId {
public:
  TypeId *returnType;
  std::vector<ParamId> params;
  FunctionId(TypeId *ret, std::vector<ParamId> params);
};

class NullId : public PairId {
public:
  NullId();
  bool equals(TypeId *other);
  std::string name(); 
  int virtual size();
};

#endif // ! SEMANTIC_ID_HH

