#include "astnode.hh"
#include "ast-node-visitor.hh"

void ASTnode::accept(AstNodeVisitor *visitor) {
  visitor->visit(this);
}

Program::Program(FunctionDecList* fs, StatSeq* stats) : functions(fs), statements(stats) { }
Program::~Program() { freePtr(functions); freePtr(statements); }

void Program::accept(AstNodeVisitor *visitor) {
  visitor->visit(this);
}

StatSeq::StatSeq() { };
StatSeq:: ~StatSeq() {
  for(int i = 0; i < statements.size(); i++ ) {
    freePtr(statements[i]);
  }
}

bool StatSeq::containRet() {
  for(int i=0; i < statements.size(); i++) {
    ReturnStatement *ret = dynamic_cast<ReturnStatement*>(statements[i]);
    if(ret) {
      return true;    
    }
  }
  return false;
}

void StatSeq::accept(AstNodeVisitor *visitor) {
  visitor->visit(this);
}

FunctionDecList::FunctionDecList() { }
FunctionDecList::~FunctionDecList() {
    for(int i=0; i < funcs.size(); i++) {
      freePtr(funcs[i]);
    }
}

void FunctionDecList::accept(AstNodeVisitor *visitor) {
  visitor->visit(this);
}

void Expression::accept(AstNodeVisitor *visitor) {
  visitor->visit(this);
}

VariableDeclaration::VariableDeclaration(Type *type, Identifier *id)
    : type(type), id(id) {}

VariableDeclaration::VariableDeclaration(Type *type, Identifier *id, AssignRhs *rhs)
    : type(type), id(id), rhs(rhs) {}

VariableDeclaration::~VariableDeclaration() {
    freePtr(type);
    freePtr(id);
    freePtr(rhs);
}

FunctionDeclaration::FunctionDeclaration(Type *type, Identifier *id, StatSeq *block) 
    : type(type), id(id), block(block) {
        parameters = new VariableList();
        }

FunctionDeclaration::FunctionDeclaration(Type *type, Identifier *id, 
      VariableList *parameters, StatSeq *block) 
    : type(type), id(id), parameters(parameters), block(block) {}

FunctionDeclaration::~FunctionDeclaration() {
    freePtr(type);
    freePtr(id);
    if (parameters != NULL) {
      for(int i=0; i < parameters->size(); i++) {
        freePtr((*parameters)[i]);
      }
      freePtr(parameters);
    }
    freePtr(block);
}

void FunctionDeclaration::accept(AstNodeVisitor *visitor) {
  visitor->visit(this);
}

Type::Type(std::string name) : name(name) { }
Type::~Type() { }

IntegerType::IntegerType() : Type("int") { }

BoolType::BoolType() : Type("bool") { }

CharType::CharType() : Type("char") { }

SkipStatement::SkipStatement() {}
SkipStatement::~SkipStatement() {}


StringType::StringType() : Type("string") { }

ArrayType::ArrayType(Type *type) : Type("array"), type(type) { }
ArrayType::~ArrayType() { freePtr(type); }


PairKeyword::PairKeyword() : Type("pair") { }
PairKeyword::~PairKeyword() { }


PairType::PairType(Type *fst, Type *snd) : Type("pair"), fst(fst), snd(snd) {}
PairType::~PairType() {freePtr(fst); freePtr(snd); }

FunctionCall::FunctionCall(Identifier *id, ExpressionList *parameters)
    : id(id), parameters(parameters) {}
FunctionCall::FunctionCall(Identifier *id)
    : id(id) {
        parameters = new ExpressionList();
        }

void FunctionCall::accept(AstNodeVisitor *visitor) {
  visitor->visit(this);
}


FunctionCall::~FunctionCall() {
     freePtr(id);
     if (parameters != NULL) {
        for(int i=0; i < parameters->size(); i++) {
          freePtr((*parameters)[i]);
        }
        freePtr(parameters);
     }
}

Assignment::Assignment(AssignLhs *lhs, AssignRhs *rhs)
  : lhs(lhs), rhs(rhs) {}

Assignment::~Assignment() { freePtr(lhs); freePtr(rhs); }

FreeStatement::FreeStatement(Expression *expr) : expr(expr) {}
FreeStatement::~FreeStatement() { freePtr(expr); }


ReturnStatement::ReturnStatement(Expression *expr) : expr(expr) {}
ReturnStatement::~ReturnStatement() { freePtr(expr); }

void ReturnStatement::accept(AstNodeVisitor* visitor) {
  visitor->visit(this);
}

ExitStatement::ExitStatement(Expression *expr) : expr(expr) {}
ExitStatement::~ExitStatement() { freePtr(expr);}

void ExitStatement::accept(AstNodeVisitor *visitor) {
  visitor->visit(this);
}


BeginStatement::BeginStatement(StatSeq *scope) : scope(scope) {}
BeginStatement::~BeginStatement() {freePtr(scope); }

void BeginStatement::accept(AstNodeVisitor *visitor) {
  std::cout << "begin" << std::endl;
  visitor -> visit(this);
}

IfStatement::IfStatement(Expression *expr, StatSeq *thenS)
  : expr(expr), thenS(thenS) {}

IfStatement::IfStatement(Expression *expr, StatSeq *thenS, StatSeq *elseS)
  : expr(expr), thenS(thenS), elseS(elseS) {}

IfStatement::~IfStatement() {
  freePtr(expr);
  freePtr(thenS);
  freePtr(elseS);
}

void IfStatement::accept(AstNodeVisitor *visitor) {
  visitor->visit(this);
}


WhileStatement::WhileStatement(Expression *expr, StatSeq *doS)
  : expr(expr), doS(doS) {}
WhileStatement::~WhileStatement() {freePtr(expr); freePtr(doS); }

void WhileStatement::accept(AstNodeVisitor *visitor) {
  visitor->visit(this);
}


ReadStatement::ReadStatement(AssignLhs *id) : id(id) {}
ReadStatement::~ReadStatement() {freePtr(id);}


PrintStatement::PrintStatement(Expression *expr) : expr(expr) {}
PrintStatement::~PrintStatement() {freePtr(expr);}

void PrintStatement::accept(AstNodeVisitor *visitor) {
	visitor->visit(this);
}

PrintlnStatement::PrintlnStatement(Expression *expr) : expr(expr) {}
PrintlnStatement::~PrintlnStatement() {freePtr(expr);}


Number::Number(int value) : value(value) {}

void Number::accept(AstNodeVisitor *visitor) {
  visitor->visit(this);
}

Boolean::Boolean(bool value) : value(value) {}

void Boolean::accept(AstNodeVisitor *visitor) {
  visitor->visit(this);
}

Char::Char(char value) : value(value) {}

void Char::accept(AstNodeVisitor *visitor) {
  visitor->visit(this);
}

String::String(std::string value) : value(value) {}

void String::accept(AstNodeVisitor *visitor) {
  visitor->visit(this);
}

void Null::accept(AstNodeVisitor *visitor) {
  visitor->visit(this);
}

BinaryOperator::BinaryOperator(Expression *left, int op, Expression *right)
  : left(left), right(right), op(op) { }
BinaryOperator::~BinaryOperator() {freePtr(left); freePtr(right);}

void BinaryOperator::accept(AstNodeVisitor *visitor) {
  visitor->visit(this);
}

ArrayElem::ArrayElem(Identifier *id, ExpressionList *idxs) : id(id), idxs(idxs) {}
ArrayElem::~ArrayElem() {
  freePtr(id);
  for(int i=0; i < idxs->size(); i++) {
    freePtr(idxs->operator[](i));
  }
  freePtr(idxs);
}

std::string ArrayElem::getId() {
  return (id->id);
}

void ArrayElem::accept(AstNodeVisitor *visitor) {
  visitor->visit(this);
}

PairElem::PairElem(bool fst, Expression *expr) : fst(fst), expr(expr) {}
PairElem::~PairElem() {freePtr(expr);}

std::string PairElem::getId() {
  ArrayElem *arrayElem = dynamic_cast<ArrayElem*>(expr);
  Identifier *ident = dynamic_cast<Identifier*>(expr);
  if(arrayElem) return arrayElem->getId();
  if(ident) return ident->getId();
  return "0";
}

ArrayLiter::ArrayLiter(ExpressionList *elems) : AssignRhs("array"),
                                                     elems(elems) {
}

ArrayLiter::~ArrayLiter() {
  for (int i = 0; i < elems->size(); ++i) {
    delete (*elems)[i];
  }
  freePtr(elems);
}


NewPair::NewPair(Expression *fst, Expression *snd) : AssignRhs("pair"), 
                                                     fst(fst),
                                                     snd(snd) {}
NewPair::~NewPair() {freePtr(fst); freePtr(snd);}

UnaryOperator::UnaryOperator(int op, Expression *expr) : op(op), expr(expr) {}
UnaryOperator::~UnaryOperator() {freePtr(expr);}

void UnaryOperator::accept(AstNodeVisitor *visitor) {
  visitor->visit(this);
}

std::string Identifier::getId() {
  return id;
}

void Identifier::accept(AstNodeVisitor *visitor) {
  visitor->visit(this);
}

AssignRhs::AssignRhs(std::string type) {this->type = type; }

std::string AssignLhs::getId() {
 ArrayElem *arr = dynamic_cast<ArrayElem*>(this);
 Identifier *ident = dynamic_cast<Identifier*>(this);
 PairElem *pair = dynamic_cast<PairElem*>(this);

 if(arr) return arr->getId();
 if(ident) return ident->getId();
 if(pair) return pair->getId();
 return NULL;
}

