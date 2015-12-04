#include "ast-node-visitor.hh"
#include "semantic-visitor.hh"
#include "astnode.hh"
#include "semantic-id.hh"
#include "parser.hh"
#define tok yy::parser::token::yytokentype

SemanticVisitor::SemanticVisitor() {
  scope     = new SymbolTable(NULL);
  exprTable = new std::map<ASTnode*, TypeId*>();
  funcLook  = new std::map<std::string, FunctionDeclaration*>();
}

SemanticVisitor::~SemanticVisitor() {
  delete scope;
  scope = NULL;
}

void SemanticVisitor::addExpression(ASTnode* node, TypeId* id) {
  exprTable->operator[](node) = id;
}

TypeId* SemanticVisitor::lookUpExpr(ASTnode* node) {
  auto it = exprTable->find(node);
  if ( it != exprTable->end()) return it->second;
  return new NullId();
}

TypeId* SemanticVisitor::typeBuilder(Type* type){
  IntegerType *intType     = dynamic_cast<IntegerType*>(type);
  BoolType *boolType       = dynamic_cast<BoolType*>(type);
  CharType *charType       = dynamic_cast<CharType*>(type);
  StringType *stringType   = dynamic_cast<StringType*>(type);
  ArrayType *arrayType     = dynamic_cast<ArrayType*>(type);
  PairKeyword *pairKeyword = dynamic_cast<PairKeyword*>(type);
  PairType *pairType       = dynamic_cast<PairType*>(type);

  if(intType) {
    return new IntTypeId(NULL); 
  }  else if(boolType) {
    return new BoolTypeId(NULL);
  } else if(charType) {
    return new CharTypeId(NULL);
  } else if(stringType) {
    return new StringTypeId(NULL);
  } else if(arrayType) {
    return new ArrayId(NULL, typeBuilder(arrayType->type));
  } else if(pairKeyword) {
    return new PairKeyId(NULL);
  } else if(pairType) {
    return new PairId(NULL, typeBuilder(pairType->fst),
                  typeBuilder(pairType->snd));
  } else {
    return new NullId();
  }
}


void SemanticVisitor::visit(ASTnode *node){
}

void SemanticVisitor::visit(Program *node) {
  IntTypeId intId(NULL);
  for(int i=0; i < node->functions->funcs.size(); i++) {
    funcLook->insert(std::pair<std::string, FunctionDeclaration*>(node->functions->funcs[i]->id->id,
                node->functions->funcs[i]));
  }
  node->functions->accept(this);
  scope = new SymbolTable(scope);
  scope->add("", intId); 
  if(node->statements->containRet()) {
    std::cerr << "semantic error: invalid global return" << std::endl;
    exit(200);
  }
  node->statements->accept(this);
}

void SemanticVisitor::visit(AssignRhs *node) {
  ArrayLiter *arrayLiter = dynamic_cast<ArrayLiter*>(node);
  NewPair *newPair       = dynamic_cast<NewPair*>(node);
  Expression *expr       = dynamic_cast<Expression*>(node);
  PairElem *pairElem     = dynamic_cast<PairElem*>(node);

  if(arrayLiter) arrayLiter->accept(this);
  if(newPair) newPair->accept(this);
  if(expr) expr->accept(this);
  if(pairElem) pairElem->accept(this);
}

void SemanticVisitor::visit(AssignLhs *node) {
}

void SemanticVisitor::visit(Expression *node) {
  Identifier *ident      = dynamic_cast<Identifier*>(node);
  FunctionCall *funcCall = dynamic_cast<FunctionCall*>(node);
  Number *number         = dynamic_cast<Number*>(node);
  Boolean *boolean       = dynamic_cast<Boolean*>(node);
  Char *charId           = dynamic_cast<Char*>(node);
  String *stringId       = dynamic_cast<String*>(node);
  Null *null             = dynamic_cast<Null*>(node);
  BinaryOperator *binop  = dynamic_cast<BinaryOperator*>(node);
  ArrayElem *arrayElem   = dynamic_cast<ArrayElem*>(node);
  UnaryOperator *unop    = dynamic_cast<UnaryOperator*>(node);

  if(ident) ident->accept(this);
  if(funcCall) funcCall->accept(this);
  if(number) number->accept(this);
  if(boolean) boolean->accept(this);
  if(charId) charId->accept(this);
  if(stringId) stringId->accept(this);
  if(null) null->accept(this);
  if(binop) binop->accept(this);
  if(arrayElem) arrayElem->accept(this);
  if(unop) unop->accept(this);
}

void SemanticVisitor::visit(StatSeq *node) {
  for(int i = 0; i < node->statements.size(); i++) {
    (node->statements)[i]->accept(this);
  }
}

void SemanticVisitor::visit(VariableDeclaration *node) {
  TypeId *type = typeBuilder(node->type);
  SemanticId *var = scope->lookUp(node->id->id);
  
  if (!type) {
    std::cerr<< "is not a type" << node->type->name << std::endl;
    exit(200);
  }
  
  FunctionId *t = dynamic_cast<FunctionId*> (var);
  if (var && !t) {
    std::cerr<< "Already declared" << node->id->id << std::endl;
    exit(200);
  }
  
  node->rhs->accept(this);
  if (!(lookUpExpr(node->rhs)->equals(type))) {
    std::cerr << type->name << " RHS has invalid type. expected " 
        << lookUpExpr(node->rhs)->name << std::endl;
    exit(200);
  }

  VariableId *variable = new VariableId(node, type);
  scope->add(node->id->id, *variable);
}

void SemanticVisitor::visit(FunctionDecList *node) {
  for(int i = 0; i < node->funcs.size(); i++) {
    (node->funcs)[i]->accept(this);
  }
}

void SemanticVisitor::visit(FunctionDeclaration *node) {
  TypeId *returnType = typeBuilder(node->type);
  SemanticId *retType  = returnType;
  std::vector<ParamId> params;
  
  for(int i=0; i < node->parameters->size(); i++) {
    TypeId *paramType = typeBuilder(node->parameters->operator[](i)->type);
    params.push_back(ParamId(NULL, paramType));
  }
  
  FunctionId *func = new FunctionId(NULL, returnType, params);
  scope->add(node->id->id, *func);
  scope = new SymbolTable(scope);
  scope->add("", *retType);
  
  for(int i = 0; i < node->parameters->size(); i++) {
    std::string id = node->parameters->operator[](i)->id->id;
    VariableId *var = new VariableId(NULL, params[i].type);
    scope->add(id, *var);
  }
  
  node->block->accept(this);
  SymbolTable *tmp = scope->getEncScope();
  delete scope;
  scope = tmp; 
}

void SemanticVisitor::visit(FunctionCall *node) {
  auto it = funcLook->find(node->id->id);

  if (it == funcLook->end()) {
    std::cerr<< "unknown function " << node->id->id << std::endl;
    exit(200);
  }
  
  // add a clause to check for correct number of args
  if(node->parameters->size() != it->second->parameters->size()) {
    std::cerr << "semantic error: wrong number of arguments in function call"
        << std::endl;
    exit(200);
  }

  for(int i = 0; i < node->parameters->size(); i++) {
    node->parameters->operator[](i)->accept(this);
    TypeId *paramId = lookUpExpr(node->parameters->operator[](i));

    if(!paramId->equals(typeBuilder(it->second->parameters->operator[](i)->type))) {
      std::cerr << "Incorrect argument type in function call " << node->id->id << std::endl;
      exit(200);
    }  
  }
  addExpression(node, typeBuilder(it->second->type));
}

void SemanticVisitor::visit(Assignment *node) {
  node->lhs->accept(this);
  node->rhs->accept(this);
  TypeId *type = lookUpExpr(node->lhs);
  SemanticId *value = scope->lookUpAll(node->lhs->getId());
  
  if(!value) {
    std::cerr << "semantic error: assigning to undeclared identifier" 
        << node->lhs->getId() << std::endl;
    exit(200);
  }
  if(!lookUpExpr(node->rhs)->equals(type)) {
    std::cerr << "Invalid type in assignment of " << node->lhs->getId()
        << "as opposed to " << node->rhs->type << std::endl;
    exit(200);
  }
}

void SemanticVisitor::visit(BeginStatement *node) {
  scope = new SymbolTable(scope);;
  node->scope->accept(this);
  SymbolTable *tmp = scope->getEncScope();
  delete scope;
  scope = tmp;
}

void SemanticVisitor::visit(IfStatement *node) {
  node->expr->accept(this);
  if (!(lookUpExpr(node->expr)->equals(new BoolTypeId(NULL)))) {
    std::cerr << "Type requiered: bool. Actual type: "
       << node->expr->type << std::endl;
    exit(200);
  }
  scope = new SymbolTable(scope);
  node->thenS->accept(this);
  SymbolTable *tmp = scope->getEncScope();
  delete scope;
  scope = new SymbolTable(tmp);
  node->elseS->accept(this);
  delete scope;
  scope = tmp;
}


void SemanticVisitor::visit(WhileStatement *node) {
  node->expr->accept(this);
  if (!(lookUpExpr(node->expr)->equals(new BoolTypeId(NULL)))) {
    std::cerr << "Type of expression in while requiered: bool. Actual type: "
             << lookUpExpr(node->expr)->name << std::endl;
    exit(200);
  }
  scope = new SymbolTable(scope);
  node->doS->accept(this);
  SymbolTable *tmp = scope->getEncScope();
  delete scope;
  scope = tmp;
}

void SemanticVisitor::visit(ReadStatement *node) {
  SemanticId *value = scope->lookUpAll(node->id->getId());
  if(!value) {
    std::cerr << "Cannot read undeclared variable: " << node->id->getId() 
              << std::endl;
    exit(200);
  }
  VariableId *var = dynamic_cast<VariableId*>(value);
  PairId *pair = dynamic_cast<PairId*>(var->type);
  if(pair) {
    PairElem *p = dynamic_cast<PairElem*>(node->id);
    if(p) {
      p->expr->accept(this);
      TypeId *t = lookUpExpr(p->expr);
      PairKeyId *k = dynamic_cast<PairKeyId*>(t);
      if(!k) {
        return;
      }
    }
    std::cerr << "semantic error: reading into pair type is not allowed "
        << std::endl;
    exit(200);
  }
    BoolTypeId *b = dynamic_cast<BoolTypeId*>(var->type);
    if(b) {
     std::cerr << "semantic error: reading into bool type is not allowed "
         << std::endl;
     exit(200);
  }
}

void SemanticVisitor::visit(PrintStatement *node) {
  node->expr->accept(this);
}

void SemanticVisitor::visit(PrintlnStatement *node) {
  node->expr->accept(this);
}

void SemanticVisitor::visit(BinaryOperator *node) {
  node->left->accept(this);
  node->right->accept(this);
  int oper = node->op;
  
  if((oper == tok::TOK_LOGOR) || (oper == tok::TOK_LOGAND)) {
    if(!(lookUpExpr(node->left)->equals(lookUpExpr(node->right)))
       || (!(lookUpExpr(node->left)->equals(new BoolTypeId(NULL))))) {
     
      std::cerr << "Expected bool type for operands &&,||"
          << lookUpExpr(node->right)->name  << std::endl;
      exit(200);
    }
    addExpression(node, new BoolTypeId(NULL));
  } else if((oper >= tok::TOK_SLASH) && (oper <= tok::TOK_MINUS)) {
    if(!(lookUpExpr(node->left)->equals(lookUpExpr(node->right)))
       || (!(lookUpExpr(node->left)->equals(new IntTypeId(NULL))))) {
      std::cerr << "right " << lookUpExpr(node->right)->name << std::endl;  
      std::cerr <<  lookUpExpr(node->left) <<std::endl;
      std::cerr << "Expected int type for operands /,*,%,+,- "
          << lookUpExpr(node->left)->name  << std::endl;
      exit(200);
    }
    addExpression(node, new IntTypeId(NULL));
  } else if((oper >= tok::TOK_LESS) && (oper <= tok::TOK_GREATEREQUALS)) {
    if(!(lookUpExpr(node->left)->equals(lookUpExpr(node->right)))){
      std::cerr<<"Left and right of operator to be the same type"<<std::endl;
    }else if(!(lookUpExpr(node->left)->equals(new IntTypeId(NULL))||
       ((lookUpExpr(node->left)->equals(new CharTypeId(NULL)))))) {
      std::cerr << "Expected type int/char for operators <,<=,>,>="
          << lookUpExpr(node->left)->name  << std::endl;
      exit(200);
    }
    addExpression(node, new BoolTypeId(NULL));
  } else if((oper == tok::TOK_EQUALS) || (oper == tok::TOK_NOTEQUALS)) {
    if(!(lookUpExpr(node->left)->equals(lookUpExpr(node->right)))) {
      std::cerr << "lhs and rhs types do not match for operators ==,!="
          << lookUpExpr(node->left)->name  << std::endl;
          exit(200);
    }
    addExpression(node, new BoolTypeId(NULL));
  }
  }

void SemanticVisitor::visit(ArrayElem *node) {
  SemanticId *value = scope->lookUpAll(node->id->id);
  
  if(!value) {
    std::cerr << "Cannot access non declared array elem" << std::endl;
    exit(200);
  } 

  TypeId *type = dynamic_cast<TypeId*> (value);
  VariableId* var = dynamic_cast<VariableId*> (value);
  ArrayId *arr = dynamic_cast<ArrayId*>(var->type);
  StringTypeId *str = dynamic_cast<StringTypeId*>(var->type);
    if(str) {
        addExpression(node, new CharTypeId(NULL));
        return;
    }
  if(!arr && !type->equals(arr)) {
    std::cerr <<"semantic error: identifier is not an array" << std::endl;
    exit(200);
  }
  addExpression(node, arr->elementType);
}

void SemanticVisitor::visit(PairElem *node) {
  node->expr->accept(this);
  if(!(lookUpExpr(node->expr)->equals(new PairId(NULL, new NullId(), new NullId())))) {
    std::cerr << "Type mismatch cannot get pair element of non pair expression "
              <<lookUpExpr(node->expr)->name << std::endl;
    exit(200);
  } 
    TypeId *typeId = lookUpExpr(node->expr);
    PairId *pairType = dynamic_cast<PairId*>(typeId);
    if(!pairType) {
      std::cerr << "semantic error accessing elem of undefined pair" << std::endl;
      exit(200);
    }
    ASTnode *n = node;
    
  if (node->fst) {
    addExpression(n, pairType->fst);
  } else {
    addExpression(n, pairType->snd);
  }
}

void SemanticVisitor::visit(UnaryOperator *node) {
  node->expr->accept(this);
  int oper = node->op;
  if( oper == tok::TOK_BANG) {
  if(!lookUpExpr(node->expr)->equals(new BoolTypeId(NULL))) {
    std::cerr << "Operand of ! is not a bool" << std::endl;
    exit(200);
  }
  addExpression(node, new BoolTypeId(NULL));
  } else if(oper == tok::TOK_MINUS) {
  if(!lookUpExpr(node->expr)->equals(new IntTypeId(NULL))) {
    std::cerr << "Operand of - is not an int" << std::endl;
    exit(200);
  }
    addExpression(node, new IntTypeId(NULL));
  } else if(oper == tok::TOK_ORD) {
  if(!lookUpExpr(node->expr)->equals(new CharTypeId(NULL))) {
    std::cerr << "Operand of ord is not a char" << std::endl;
    exit(200);
  }
    addExpression(node, new IntTypeId(NULL));
  } else if(oper == tok::TOK_CHR) {
  if(!lookUpExpr(node->expr)->equals(new IntTypeId(NULL))) {
    std::cerr << "Operand of chr is not an int" << std::endl;
    exit(200);
  }

  addExpression(node, new CharTypeId(NULL));
  } 
}

void SemanticVisitor::visit(FreeStatement *node) {
  node->expr->accept(this);
  if(!(lookUpExpr(node->expr)->equals(new PairId(NULL, new NullId(), new NullId())))) {
    std::cerr << "semantic error freeing a non pair type expression" << std::endl;
    exit(200);
  }
}

void SemanticVisitor::visit(ReturnStatement *node) {
  node->expr->accept(this);
  SemanticId *rettype = scope->lookUpAll("");
  TypeId *ret = dynamic_cast<TypeId*>(rettype);
  if(!(lookUpExpr(node->expr)->equals(ret))) {
    std::cerr << "semantic error : wrong return type " << node->expr->type << std::endl;
    exit(200);
  }
}

void SemanticVisitor::visit(ExitStatement *node) {
  std::cout << "exit" << std::endl;
  node->expr->accept(this);
  if(!(lookUpExpr(node->expr)->equals(new IntTypeId(NULL)))) {
    std::cerr << "semantic error : wrong exit type, expected int got: " << node->expr->type
              << std::endl;
    exit(200);
  }
}

void SemanticVisitor::visit(Number *node) {
  addExpression(node, new IntTypeId(NULL));
}

void SemanticVisitor::visit(Boolean *node) {
  addExpression(node, new BoolTypeId(NULL));
}

void SemanticVisitor::visit(Char *node) {
  addExpression(node, new CharTypeId(NULL));
}

void SemanticVisitor::visit(String *node) {
  addExpression(node, new StringTypeId(NULL));
}

void SemanticVisitor::visit(NewPair *node) {
  node->fst->accept(this);
  node->snd->accept(this);
  addExpression(node, new PairId(NULL, lookUpExpr(node->fst), lookUpExpr(node->snd)));
}

void SemanticVisitor::visit(ArrayLiter *node) {
  if(node->elems->size() == 0) {
    addExpression(node, new NullId());
    return;
  }
  node->elems->operator[](0)->accept(this);
  TypeId* elemType = lookUpExpr(node->elems->operator[](0));
  for(int i=1; i < node->elems->size(); i++) {
    node->elems->operator[](i)->accept(this);
    TypeId* tmp = lookUpExpr(node->elems->operator[](i));
    if(!tmp->equals(elemType)) {
      std::cerr << "semantic error non matching types in array literal" << std::endl;
      exit(200);
    }
  }
  addExpression(node, new ArrayId(NULL, elemType));
}

void SemanticVisitor::visit(PairType *node) {
}

void SemanticVisitor::visit(Null *node) {
  addExpression(node, new NullId());
}

void SemanticVisitor::visit(ArrayType *node) {
}

void SemanticVisitor::visit(Identifier *node) {
  SemanticId *type = scope->lookUpAll(node->id);
  VariableId *idType = dynamic_cast<VariableId*>(type);
  if(!idType) {
    std::cerr << "semantic error: variable is not declared " << node->id
              << std::endl;
    exit(200);
  }
  addExpression(node, idType->type);
  addExpression(node, idType->type);
}

void SemanticVisitor::visit(IntegerType *node){}
void SemanticVisitor::visit(BoolType *node){}
void SemanticVisitor::visit(CharType *node){}
void SemanticVisitor::visit(StringType *node){}
