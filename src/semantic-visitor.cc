#include "semantic-visitor.hh"
#include "parser.hh"
#define tok yy::parser::token::yytokentype

SemanticVisitor::SemanticVisitor() {
  scope = new SymbolTable(NULL);
  funcLook = new std::map<std::string, FunctionDeclaration*>();
}

SemanticVisitor::~SemanticVisitor() {
}

void SemanticVisitor::visit(ASTnode *node){
}

void SemanticVisitor::visit(Program *node) {
  IntTypeId intId;
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

  node->statements->table = scope;
}

void SemanticVisitor::visit(StatSeq *node) {
  for(int i = 0; i < node->statements.size(); i++) {
    (node->statements)[i]->accept(this);
  }
}

void SemanticVisitor::visit(VariableDeclaration *node) {
  SemanticId *var = scope->lookUp(node->id->id);
  
//  if (!type) {
//    std::cerr<< "is not a type" << type->name() << std::endl;
//    exit(200);
//  }
  
  FunctionId *t = dynamic_cast<FunctionId*> (var);
  if (var && !t) {
    std::cerr<< "semantic error: variable already declared" << node->id->id << std::endl;
    exit(200);
  }
  
  node->rhs->accept(this);
  if (!(node->rhs->type->equals(node->type))) {
    std::cerr << node->type->name() << " RHS has invalid type. expected " 
			  << node->rhs->type->name() << std::endl;
    exit(200);
  }

  scope->addVariable(node);
}

void SemanticVisitor::visit(FunctionDecList *node) {
  for(int i = 0; i < node->funcs.size(); i++) {
    (node->funcs)[i]->accept(this);
  }
}

void SemanticVisitor::visit(FunctionDeclaration *node) {
  TypeId *returnType   = node->type;
  SemanticId *retType  = returnType;
  std::vector<ParamId> params;

  for(int i=0; i < node->parameters->size(); i++) {
      TypeId *paramType = node->parameters->operator[](i)->type;
      ParamId id(paramType);
      params.push_back(id);
  }

  FunctionId *func = new FunctionId(returnType, params);
  scope->add(node->id->id, *func);
  scope = new SymbolTable(scope);
  scope->add("", *retType);
  
  for(int i=0; i < node->parameters->size(); i++) {
    TypeId *paramType = node->parameters->operator[](i)->type;
    ParamId *id = new ParamId(paramType);
    scope->add(node->parameters->operator[](i)->id->id, *id);
  }
  
  node->block->table = scope;
  node->block->accept(this);
  scope = scope->getEncScope();
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
    TypeId *paramId = node->parameters->operator[](i)->type;

    if(!paramId->equals(it->second->parameters->operator[](i)->type)) {
      std::cerr << "Incorrect argument type in function call " << node->id->id << std::endl;
      exit(200);
    }  
  }
  node->type = it->second->type;
}

void SemanticVisitor::visit(Assignment *node) {
  node->lhs->accept(this);
  node->rhs->accept(this);
  SemanticId *value = scope->lookUpAll(node->lhs->getId());
  TypeId *typeId = node->lhs->type;
  
  if(!value) {
    std::cerr << "semantic error: assigning to undeclared identifier" 
			  << node->lhs->getId() << std::endl;
    exit(200);
  }

  if(!node->rhs->type->equals(typeId)) {
    std::cerr << "Invalid type in assignment of " << typeId->name()
			  << " as opposed to " << node->rhs->type->name() << std::endl;
    exit(200);
  }
}

void SemanticVisitor::visit(BeginStatement *node) {
  scope = new SymbolTable(scope);;
  node->scope->table = scope;
  node->scope->accept(this);
  scope = scope->getEncScope();
}

void SemanticVisitor::visit(IfStatement *node) {
  node->expr->accept(this);
	if (!node->expr->type->equals(new BoolTypeId())) {
		std::cerr << "Type requiered: bool. Actual type: " 
			 << node->expr->type->name() << std::endl;
		exit(200); 
	}
  scope = new SymbolTable(scope);
  node->thenS->accept(this);
  scope = new SymbolTable(scope->getEncScope());
	node->elseS->accept(this);
  scope = scope->getEncScope();
}


void SemanticVisitor::visit(WhileStatement *node) {
  node->expr->accept(this);
  if (!node->expr->type->equals(new BoolTypeId())) {
		std::cerr << "Type of expression in while requiered: bool. Actual type: " 
              << node->expr->type->name() << std::endl;
		exit(200); 
	}
  scope = new SymbolTable(scope);	
	node->doS->accept(this);
  scope = scope->getEncScope();
}

void SemanticVisitor::visit(ReadStatement *node) {
  node->id->accept(this);
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
      TypeId *t = p->expr->type;
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
  TypeId *right = node->right->type;
  TypeId *left  = node->left->type;

	int oper = node->op;
  
	if((oper == tok::TOK_LOGOR) || (oper == tok::TOK_LOGAND)) {
    if(!left->equals(right) || !left->equals(new BoolTypeId())) {
		  std::cerr << "semantic error: expected bool type for operands &&,||, got instead " 
                << right->name() << std::endl;
		  exit(200);
	  }
    node->type= new BoolTypeId();
	} else if((oper >= tok::TOK_STAR) && (oper <= tok::TOK_MINUS)) {
	  if(!left->equals(right) || !left->equals(new IntTypeId())) {
      std::cerr << "semantic error: expected int type for operands /,*,%,+,-, got instead " 
                << left->name() << std::endl;
		  exit(200);
	  }
    node->type = new IntTypeId();
	} else if((oper >= tok::TOK_LESS) && (oper <= tok::TOK_GREATEREQUALS)) {
    if(!(left->equals(right)) || !(left->equals(new IntTypeId()) ||
       left->equals(new CharTypeId()))) {
			std::cerr << "semantic error: expected type int/char for operators <,<=,>,>=, got instead " 
					<< left->name()  << std::endl;
			exit(200);
	  }
    node->type = new BoolTypeId();
	} else if((oper == tok::TOK_EQUALS) || (oper == tok::TOK_NOTEQUALS)) {
	  if(!left->equals(right)) {
		  std::cerr << "semantic error: lhs and rhs types do not match for operators ==,!="
				        << std::endl;
          exit(200);
	  }
    node->type = new BoolTypeId();
	}
}

void SemanticVisitor::visit(ArrayElem *node) {
  SemanticId *value = scope->lookUpAll(node->id->id);
  for(int i = 0; i < node->idxs->size(); i++) {
    node->idxs->operator[](i)->accept(this);
  }
  
  if(!value) {
    std::cerr << "Cannot access non declared array elem" << std::endl;
    exit(200);
  } 

  TypeId *type = dynamic_cast<TypeId*> (value);
  VariableId* var = dynamic_cast<VariableId*> (value);
  ArrayId *arr = dynamic_cast<ArrayId*>(var->type);
  StringTypeId *str = dynamic_cast<StringTypeId*>(var->type);
  if(str) {
    node->type = new CharTypeId();
    return;
  }
  if(!arr && !type->equals(arr)) {
    std::cerr <<"semantic error: identifier is not an array" << std::endl;
    exit(200);
  }
  node->type = arr->elementType;
}

void SemanticVisitor::visit(PairElem *node) {
  node->expr->accept(this);
  if(!node->expr->type->equals(new PairKeyId())) {
    std::cerr << "semantic error: type mismatch cannot get pair element of non pair expression: "
              << node->expr->type->name() << std::endl;
    exit(200);
  } 
    TypeId *typeId   = node->expr->type;
    PairId *pairType = dynamic_cast<PairId*>(typeId);
    if(!pairType) {
      std::cerr << "semantic error accessing elem of undefined pair" << std::endl;
      exit(200);
    }
    
  if (node->fst) {
    node->type = pairType->fst;
  } else {
    node->type = pairType->snd;
  }
}

void SemanticVisitor::visit(UnaryOperator *node) {
  node->expr->accept(this);
  TypeId *type = node->expr->type;
  int oper = node->op;
  if( oper == tok::TOK_BANG) {
	  if(!type->equals(new BoolTypeId())) {
		  std::cerr << "Operand of ! is not a bool" << std::endl;
		  exit(200);
	  } 
    node->type = new BoolTypeId();
  } else if(oper == tok::TOK_MINUS) {
    if(!type->equals(new IntTypeId())) {
	    std::cerr << "Operand of - is not an int" << std::endl;
	    exit(200);
	  }
    node->type = new IntTypeId();
  } else if(oper == tok::TOK_LEN) {
    ArrayId *array = dynamic_cast<ArrayId*>(type);
    if(!array) {
      std::cerr << "semantic error: cannot get len of non array type" << std::endl;
      exit(200);
    }
    node->type = new IntTypeId();
  } else if(oper == tok::TOK_ORD) {
	  if(!type->equals(new CharTypeId())) {
		  std::cerr << "Operand of ord is not a char" << std::endl;
		  exit(200);
	  }
    node->type = new IntTypeId();
  } else if(oper == tok::TOK_CHR) {
	  if(!type->equals(new IntTypeId())) {
		  std::cerr << "Operand of chr is not an int" << std::endl;
		  exit(200);
	  }
    node->type = new CharTypeId();
  } 
}

void SemanticVisitor::visit(FreeStatement *node) {
  node->expr->accept(this);
  if(!(node->expr->type->equals(new PairKeyId()))) {
    std::cerr << "semantic error freeing a non pair type expression" << std::endl;
    exit(200);
  }
}

void SemanticVisitor::visit(ReturnStatement *node) {
  node->expr->accept(this);
  SemanticId *rettype = scope->lookUpAll("");
  TypeId *ret = dynamic_cast<TypeId*>(rettype);
  if(!(node->expr->type->equals(ret))) {
    std::cerr << "semantic error : wrong return type " << node->expr->type->name()
              << std::endl;
    exit(200);
  }
}

void SemanticVisitor::visit(ExitStatement *node) { 
  node->expr->accept(this);
  if(!(node->expr->type->equals(new IntTypeId()))) {
    std::cerr << "semantic error : wrong exit type, expected int got: " << node->expr->type->name()
              << std::endl;
    exit(200);
  }
}

void SemanticVisitor::visit(Number *node) {
  node->type = new IntTypeId();
}

void SemanticVisitor::visit(Boolean *node) {
  node->type = new BoolTypeId();
}

void SemanticVisitor::visit(Char *node) {
  node->type = new CharTypeId();
}

void SemanticVisitor::visit(String *node) {
  node->type = new StringTypeId();
}

void SemanticVisitor::visit(NewPair *node) {
  node->fst->accept(this);
  node->snd->accept(this);
  node->type = new PairId(node->fst->type, node->snd->type);
}

void SemanticVisitor::visit(ArrayLiter *node) {
  if(node->elems->size() == 0) {
    node->type = new NullId();
    return;
  }
  node->elems->operator[](0)->accept(this);
  TypeId* elemType = node->elems->operator[](0)->type;
  for(int i=1; i < node->elems->size(); i++) {
    node->elems->operator[](i)->accept(this);
    TypeId* tmp = node->elems->operator[](i)->type;
    if(!tmp->equals(elemType)) {
      std::cerr << "semantic error non matching types in array literal" << std::endl;
      exit(200);
    }
  }
  node->type = new ArrayId(elemType);
}

void SemanticVisitor::visit(Null *node) {
  node->type = new NullId();
}

void SemanticVisitor::visit(Identifier *node) {
  SemanticId *type = scope->lookUpAll(node->id);
  VariableId *idType = dynamic_cast<VariableId*>(type);
  ParamId *idParamType = dynamic_cast<ParamId*>(type);
  if(!idType && !idParamType) {
    std::cerr << "semantic error: variable is not declared " << node->id
              << std::endl;
    exit(200);
  }
  if(idType) {
    node->type = idType->type;
  } else {
    node->type = idParamType->type;
  }
}

void SemanticVisitor::visit(Param *node) {
  
}
