#include "semantic-id.hh"

SemanticId::SemanticId() { }

TypeId::TypeId() : SemanticId() {}
TypeId::~TypeId() {}

IntTypeId::IntTypeId() : TypeId() {}
bool IntTypeId::equals(TypeId *other) {
  IntTypeId *intOther = dynamic_cast<IntTypeId*>(other);
  return intOther != NULL; 
}
std::string IntTypeId::name() {
  return std::string("int");
}
int IntTypeId::size() {
  return 4;
}

BoolTypeId::BoolTypeId() : TypeId() {}
bool BoolTypeId::equals(TypeId *other) {
  BoolTypeId* boolOther = dynamic_cast<BoolTypeId*>(other);
  return boolOther != NULL;
}
std::string BoolTypeId::name() {
  return std::string("bool");
}
int BoolTypeId::size() {
  return 1;
}

CharTypeId::CharTypeId() : TypeId() {}
bool CharTypeId::equals(TypeId *other) {
  CharTypeId *charOther = dynamic_cast<CharTypeId*>(other);
  return charOther != NULL;
}
std::string CharTypeId::name() {
  return std::string("char");
}
int CharTypeId::size() {
  return 1;
}

StringTypeId::StringTypeId() : TypeId() {}
bool StringTypeId::equals(TypeId *other) {
  StringTypeId *stringOther = dynamic_cast<StringTypeId*>(other);
  ArrayId *arrayOther = dynamic_cast<ArrayId*>(other);
  if(arrayOther) {
    if (arrayOther->elementType->equals(new CharTypeId())) {
      return true;
    }
  }
  return stringOther != NULL;
}
std::string StringTypeId::name() {
  return std::string("string");
}
int StringTypeId::size() {
  return 4;
}

VariableId::VariableId(TypeId *type) : SemanticId(), type(type){}

ParamId::ParamId(TypeId *type) : SemanticId(), type(type) {}

ArrayId:: ArrayId(TypeId *elementType) : TypeId(), elementType(elementType) {}
bool ArrayId::equals(TypeId *other) {
  ArrayId *arrayOther = dynamic_cast<ArrayId*>(other);
  StringTypeId *stringOther = dynamic_cast<StringTypeId*>(other);
  if(stringOther && elementType->equals(new CharTypeId())) {
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
int ArrayId::size() {
  return 4;
}

PairId::PairId(TypeId *fst, TypeId *snd) : TypeId(), fst(fst), snd(snd) {}
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
int PairId::size() {
  return 4;
}

PairKeyId::PairKeyId() : PairId(NULL, NULL) { }
bool PairKeyId::equals(TypeId *other) {
  PairId *pairOther = dynamic_cast<PairId*>(other);
  return other != NULL;
}
std::string PairKeyId::name() {
  return std::string("pair");
}
int PairKeyId::size() {
  return 4;
}

FunctionId::FunctionId(TypeId *ret, std::vector<ParamId> params)
                    : SemanticId(), returnType(ret), params(params) { }

NullId::NullId() : PairId(NULL, NULL){}
bool NullId::equals(TypeId* other) {
  PairId *pairOther = dynamic_cast<PairId*>(other);
  return other != NULL;
}
std::string NullId::name() {
  return std::string("null");
}
int NullId::size() {
  return 4;
}
