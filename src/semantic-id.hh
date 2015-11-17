#ifndef SEMANTIC_ID_HH
#define SEMANTIC_ID_HH
#include "astnode.hh"


class SemanticId {
public:
  ASTnode* astnode;
  SemanticId() { }
  SemanticId(ASTnode* astnode, std::string name) : astnode(astnode), name(name) { }
  virtual ~SemanticId() {}
};


class TypeId : public SemanticId {
public:
  TypeId(ASTnode* astnode) : SemanticId(astnode) { }
  bool equals(Type *other) {
      IntTypeId *intMe = dynamic_cast<IntTypeId*>(this);
      IntTypeId *intOther = dynamic_cast<IntTypeId*>(other);
      if(intMe && intOther) return true;

      BoolTypeId *boolMe = dynamic_cast<BoolTypeId*>(this);
      BoolTypeId *boolOther = dynamic_cast<BoolTypeId*>(other);
      if(boolMe && boolOther) return true;

      CharTypeId *charMe = dynamic_cast<CharType*>(this);
      CharTypeId *charOther = dynamic_cast<CharType*>(other);
      if(charMe && charOther) return true;

      StringTypeId *stringMe = dynamic_cast<StringTypeId*>(this);
      StringTypeId *stringOther = dynamic_cast<StringTypeId*>(other);
      if(stringMe && stringOther) return true;

      PairKeyId *pairKeyMe = dynamic_cast<PairKeyId*>(this);
      PairKeyId *pairKeyOther = dynamic_cast<PairKeyId*>(other);
      if(pairKeyMe && pairKeyOther) return true;

      ArrayId *arrayMe = dynamic_cast<ArrayId*>(this);
      ArrayId *arrayOther = dynamic_cast<ArrayId*>(other);
      if(arrayMe && arrayOther) return arrayMe.equals(arrayOther);

      PairId *pairMe = dynamic_cast<PairId*>(this);
      PairId *pairOther = dynamic_cast<PairId *>(other);
      if(pairMe && pairOther) return pairMe.equals(pairOther);
  }
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
  bool equals(ArrayId *other) {
    return elementType.equals(&(other->elementType));
  }
};

class PairId : public TypeId {
public:
  TypeId fst;
  TypeId snd;
  PairId(ASTnode* astnode, TypeId fst, TypeId snd) : TypeId(astnode),
                                                     fst(fst),
                                                     snd(snd) { }
  bool equals(PairId *other) {
    return (fst.equals(&(other->fst)) && snd.equals(&(other->snd)));
  }
};

class PairKeyId : public TypeId {
  PairKeyId(ASTnode *astnode) : TypeId(astnode) { }
}

class FunctionId : public SemanticId {
public:
  TypeId returnType;
  std::vector<ParamId> params;
  FunctionId(ASTnode* astnode, TypeId ret, std::vector<ParamId> params) 
    : SemanticId(astnode), returnType(ret), params(params) { }
};

class NullId : public SemanticId {

};

#endif // ! SEMANTIC_ID_HH

