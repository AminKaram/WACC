#include "semantic-id.hh"

bool TypeId::equals(TypeId* other) {
  IntTypeId *intMe = dynamic_cast<IntTypeId*>(this);
  IntTypeId *intOther = dynamic_cast<IntTypeId*>(other);
  if(intMe && intOther) return true;
  
  BoolTypeId *boolMe = dynamic_cast<BoolTypeId*>(this);
  BoolTypeId *boolOther = dynamic_cast<BoolTypeId*>(other);
  if(boolMe && boolOther) return true;
  
  CharTypeId *charMe = dynamic_cast<CharTypeId*>(this);
  CharTypeId *charOther = dynamic_cast<CharTypeId*>(other);
  if(charMe && charOther) return true;
  
  StringTypeId *stringMe = dynamic_cast<StringTypeId*>(this);
  StringTypeId *stringOther = dynamic_cast<StringTypeId*>(other);
  if(stringMe && stringOther) return true;
  
  PairKeyId *pairKeyMe = dynamic_cast<PairKeyId*>(this);
  PairKeyId *pairKeyOther = dynamic_cast<PairKeyId*>(other);
  if(pairKeyMe && pairKeyOther) return true;
  
  ArrayId *arrayMe = dynamic_cast<ArrayId*>(this);
  ArrayId *arrayOther = dynamic_cast<ArrayId*>(other);
  if(arrayMe && arrayOther) return arrayMe->equals(arrayOther);
  
  PairId *pairMe = dynamic_cast<PairId*>(this);
  PairId *pairOther = dynamic_cast<PairId *>(other);
  if(pairMe && pairOther) return pairMe->equals(pairOther);
  return false;
}

bool ArrayId::equals(ArrayId *other) {
  return elementType.equals(&(other->elementType));
}

bool PairId::equals(PairId *other) {
  return (fst.equals(&(other->fst)) && snd.equals(&(other->snd)));
}

