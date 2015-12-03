#include "semantic-id.hh"

SemanticId::SemanticId(ASTnode* astnode) : astnode(astnode){ }

TypeId::TypeId(ASTnode* astnode) : SemanticId(astnode) {}
TypeId::~TypeId() {}

IntTypeId::IntTypeId(ASTnode* astnode) : TypeId(astnode) {}
bool IntTypeId::equals(TypeId *other) {
  IntTypeId *intOther = dynamic_cast<IntTypeId*>(other);
  return intOther != NULL; 
}
std::string IntTypeId::name() {
  return std::string("int");
}

BoolTypeId::BoolTypeId(ASTnode *astnode) : TypeId(astnode) {}
bool BoolTypeId::equals(TypeId *other) {
  BoolTypeId* boolOther = dynamic_cast<BoolTypeId*>(other);
  return boolOther != NULL;
}
std::string BoolTypeId::name() {
  return std::string("bool");
}

CharTypeId::CharTypeId(ASTnode* astnode) : TypeId(astnode) {}
bool CharTypeId::equals(TypeId *other) {
  CharTypeId *charOther = dynamic_cast<CharTypeId*>(other);
  return charOther != NULL;
}
std::string CharTypeId::name() {
  return std::string("char");
}

StringTypeId::StringTypeId(ASTnode* astnode) : TypeId(astnode) {}
bool StringTypeId::equals(TypeId *other) {
  StringTypeId *stringOther = dynamic_cast<StringTypeId*>(other);
  ArrayId *arrayOther = dynamic_cast<ArrayId*>(other);
  if(arrayOther) {
    if (arrayOther->elementType->equals(new CharTypeId(NULL))) {
      return true;
    }
  }
  return stringOther != NULL;
}
std::string StringTypeId::name() {
  return std::string("string");
}

VariableId::VariableId(ASTnode* astnode, TypeId *type)
                     : SemanticId(astnode), type(type){}

ParamId::ParamId(ASTnode* astnode, TypeId *type)
               : SemanticId(astnode), type(type) {}

ArrayId:: ArrayId(ASTnode* astnode, TypeId *elementType)
             : TypeId(astnode), elementType(elementType) {}
bool ArrayId::equals(TypeId *other) {
  ArrayId *arrayOther = dynamic_cast<ArrayId*>(other);
  StringTypeId *stringOther = dynamic_cast<StringTypeId*>(other);
  if(stringOther && elementType->equals(new CharTypeId(NULL))) {
    return true;
  }
  if(arrayOther) {
    return elementType->equals(arrayOther->elementType);
  }
  return false;
}
std::string ArrayId::name() {
  return std::string (elementType->name() + "[]");
}

PairId::PairId(ASTnode* astnode, TypeId *fst, TypeId *snd)
                     : TypeId(astnode), fst(fst), snd(snd) {}
bool PairId::equals(TypeId *other) {
  PairId *pairOther = dynamic_cast<PairId*>(other);
  if(pairOther) {
    PairKeyId *pairKeyOther = dynamic_cast<PairKeyId*>(other);
    NullId *nullOther = dynamic_cast<NullId*>(other);
    if(pairKeyOther || nullOther) {
      return true;
    }
    return (fst->equals(pairOther->fst) && snd->equals(pairOther->snd));
  }
  return false;
}
std::string PairId::name() {
  return std::string("(" + fst->name() + ", " + snd->name() + ")");
}

PairKeyId::PairKeyId(ASTnode *astnode) : PairId(astnode, NULL, NULL) { }
bool PairKeyId::equals(TypeId *other) {
  PairId *pairOther = dynamic_cast<PairId*>(other);
  return other != NULL;
}
std::string PairKeyId::name() {
  return std::string("pair");
}

FunctionId::FunctionId(ASTnode* astnode, TypeId *ret,
                          std::vector<ParamId> params)
: SemanticId(astnode), returnType(ret), params(params) { }

NullId::NullId() : PairId(NULL, NULL, NULL){}
bool NullId::equals(TypeId* other) {
  PairId *pairOther = dynamic_cast<PairId*>(other);
  return other != NULL;
}
std::string NullId::name() {
  return std::string("null");
}
