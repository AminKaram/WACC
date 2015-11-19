#include "semantic-id.hh"

SemanticId::SemanticId(ASTnode* astnode) : astnode(astnode){ }

TypeId:: TypeId(ASTnode* astnode) : SemanticId(astnode) {}

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

  NullId *nullMe = dynamic_cast<NullId*>(this);
  NullId *nullOther = dynamic_cast<NullId*>(other);
  if(nullMe || nullOther) return true;

  PairId *pairMe = dynamic_cast<PairId*>(this);
  PairId *pairOther = dynamic_cast<PairId *>(other);
  if(pairMe && pairOther) {return pairMe->equals(pairOther);}
  if(stringMe && arrayOther){
    return arrayOther -> elementType->equals(new CharTypeId(NULL));
  }

  if(stringOther && arrayMe){

    return arrayMe -> elementType->equals(new CharTypeId(NULL));
  }

  if(pairKeyMe && pairOther) return true;
  if(pairKeyOther && pairMe) return true;

  return false;
}

IntTypeId::IntTypeId(ASTnode* astnode) : TypeId(astnode) {}

CharTypeId::CharTypeId(ASTnode* astnode) : TypeId(astnode) {}

StringTypeId::StringTypeId(ASTnode* astnode) : TypeId(astnode) {}

VariableId::VariableId(ASTnode* astnode, TypeId *type)
                     : SemanticId(astnode), type(type){}

ParamId::ParamId(ASTnode* astnode, TypeId *type)
               : SemanticId(astnode), type(type) {}

ArrayId:: ArrayId(ASTnode* astnode, TypeId *elementType)
             : TypeId(astnode), elementType(elementType) {}

bool ArrayId::equals(ArrayId *other) {
    return elementType->equals(other->elementType);
}

PairId::PairId(ASTnode* astnode, TypeId *fst, TypeId *snd)
                     : TypeId(astnode), fst(fst), snd(snd) {}

bool PairId::equals(PairId *other) {
  NullId* null = dynamic_cast<NullId*> (this);
  NullId* nullOther = dynamic_cast<NullId*>(other);
  if (null || nullOther ) {
    return true;
  }
  return (fst->equals(other->fst) && snd->equals(other->snd));
}

PairKeyId::PairKeyId(ASTnode *astnode) : TypeId(astnode) { }

FunctionId::FunctionId(ASTnode* astnode, TypeId *ret,
                          std::vector<ParamId> params)
: SemanticId(astnode), returnType(ret), params(params) { }

NullId::NullId() : PairId(NULL, new TypeId(NULL), new TypeId(NULL)){}
