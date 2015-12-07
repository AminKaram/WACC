#include "astnode.hh"
#include "semantic-visitor.hh"
#include "code-generation-visitor.hh"

ASTnode::~ASTnode() { };
void ASTnode::accept(SemanticVisitor *visitor) { };
void ASTnode::accept(CodeGenVisitor *visitor) { };

Program::Program(FunctionDecList* fs, StatSeq* stats) : functions(fs), statements(stats) { }
Program::~Program() { freePtr(functions); freePtr(statements); }

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

FunctionDecList::FunctionDecList() { }
FunctionDecList::~FunctionDecList() {
    for(int i=0; i < funcs.size(); i++) {
      freePtr(funcs[i]);
    }
}

VariableDeclaration::VariableDeclaration(TypeId *type, Identifier *id)
    : type(type), id(id) {}

VariableDeclaration::VariableDeclaration(TypeId *type, Identifier *id, AssignRhs *rhs)
    : type(type), id(id), rhs(rhs) {}

VariableDeclaration::~VariableDeclaration() {
    freePtr(type);
    freePtr(id);
    freePtr(rhs);
}

FunctionDeclaration::FunctionDeclaration(TypeId *type, Identifier *id, StatSeq *block) 
    : type(type), id(id), block(block) {
        parameters = new VariableList();
        }

FunctionDeclaration::FunctionDeclaration(TypeId *type, Identifier *id, 
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

FunctionCall::FunctionCall(Identifier *id, ExpressionList *parameters)
    : id(id), parameters(parameters) {}
FunctionCall::FunctionCall(Identifier *id)
    : id(id) {
        parameters = new ExpressionList();
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

ExitStatement::ExitStatement(Expression *expr) : expr(expr) {}
ExitStatement::~ExitStatement() { freePtr(expr);}


BeginStatement::BeginStatement(StatSeq *scope) : scope(scope) {}
BeginStatement::~BeginStatement() {freePtr(scope); }

IfStatement::IfStatement(Expression *expr, StatSeq *thenS)
  : expr(expr), thenS(thenS) {}

IfStatement::IfStatement(Expression *expr, StatSeq *thenS, StatSeq *elseS)
  : expr(expr), thenS(thenS), elseS(elseS) {}

IfStatement::~IfStatement() {
  freePtr(expr);
  freePtr(thenS);
  freePtr(elseS);
}


WhileStatement::WhileStatement(Expression *expr, StatSeq *doS)
  : expr(expr), doS(doS) {}
WhileStatement::~WhileStatement() {freePtr(expr); freePtr(doS); }


ReadStatement::ReadStatement(AssignLhs *id) : id(id) {}
ReadStatement::~ReadStatement() {freePtr(id);}

PrintStatement::PrintStatement(Expression *expr) : expr(expr) {}
PrintStatement::~PrintStatement() {freePtr(expr);}

PrintlnStatement::PrintlnStatement(Expression *expr) : expr(expr) {}
PrintlnStatement::~PrintlnStatement() {freePtr(expr);}


Number::Number(int value) : value(value) {}

Boolean::Boolean(bool value) : value(value) {}

Char::Char(char value) : value(value) {}

String::String(std::string value) : value(value) {}


BinaryOperator::BinaryOperator(Expression *left, int op, Expression *right)
  : left(left), right(right), op(op) { }
BinaryOperator::~BinaryOperator() {freePtr(left); freePtr(right);}

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

PairElem::PairElem(bool fst, Expression *expr) : fst(fst), expr(expr) {}
PairElem::~PairElem() {freePtr(expr);}
std::string PairElem::getId() {
  ArrayElem *arrayElem = dynamic_cast<ArrayElem*>(expr);
  Identifier *ident = dynamic_cast<Identifier*>(expr);
  if(arrayElem) return arrayElem->getId();
  if(ident) return ident->getId();
  return "0";
}

ArrayLiter::ArrayLiter(ExpressionList *elems) : AssignRhs(),
												                        elems(elems) {
}

ArrayLiter::~ArrayLiter() {
  for (int i = 0; i < elems->size(); ++i) {
    delete (*elems)[i];
  }
  freePtr(elems);
}

Statement::~Statement() { }

NewPair::NewPair(Expression *fst, Expression *snd) : AssignRhs(), 
                                                     fst(fst),
                                                     snd(snd) {}
NewPair::~NewPair() {freePtr(fst); freePtr(snd);}

UnaryOperator::UnaryOperator(int op, Expression *expr) : op(op), expr(expr) {}
UnaryOperator::~UnaryOperator() {freePtr(expr);}

std::string Identifier::getId() {
  return id;
}

std::string AssignLhs::getId() {
 ArrayElem *arr = dynamic_cast<ArrayElem*>(this);
 Identifier *ident = dynamic_cast<Identifier*>(this);
 PairElem *pair = dynamic_cast<PairElem*>(this);

 if(arr) return arr->getId();
 if(ident) return ident->getId();
 if(pair) return pair->getId();
 return NULL;
}

//void ASTnode::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void Program::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void Program::accept(CodeGenVisitor *visitor) { visitor->visit(this); }
//void AssignRhs::accept(SemanticVisitor *visitor) { visitor->visit(this); }
//void AssignLhs::accept(SemanticVisitor *visitor) { visitor->visit(this); }
//void Expression::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void StatSeq::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void StatSeq::accept(CodeGenVisitor *visitor) { visitor->visit(this); }
void FunctionDecList::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void FunctionDecList::accept(CodeGenVisitor *visitor) { visitor->visit(this); }
void VariableDeclaration::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void VariableDeclaration::accept(CodeGenVisitor *visitor) { visitor->visit(this); }
void FunctionDeclaration::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void FunctionDeclaration::accept(CodeGenVisitor *visitor) { visitor->visit(this); }
void FunctionCall::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void FunctionCall::accept(CodeGenVisitor *visitor, std::string reg) { visitor->visit(this, reg); }
void Assignment::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void Assignment::accept(CodeGenVisitor *visitor) { visitor->visit(this); }
void FreeStatement::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void FreeStatement::accept(CodeGenVisitor *visitor) { visitor->visit(this); }
void ReturnStatement::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void ReturnStatement::accept(CodeGenVisitor *visitor) { visitor->visit(this); }
void ExitStatement::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void ExitStatement::accept(CodeGenVisitor *visitor) { visitor->visit(this); }
void BeginStatement::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void BeginStatement::accept(CodeGenVisitor *visitor) { visitor->visit(this); }
void IfStatement::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void IfStatement::accept(CodeGenVisitor *visitor) { visitor->visit(this); }
void WhileStatement::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void WhileStatement::accept(CodeGenVisitor *visitor) { visitor->visit(this); }
void ReadStatement::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void ReadStatement::accept(CodeGenVisitor *visitor) { visitor->visit(this); }
void PrintStatement::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void PrintStatement::accept(CodeGenVisitor *visitor) { visitor->visit(this); }
void PrintlnStatement::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void PrintlnStatement::accept(CodeGenVisitor *visitor) { visitor->visit(this); }
void Number::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void Number::accept(CodeGenVisitor *visitor, std::string reg) { visitor->visit(this, reg); }
void Boolean::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void Boolean::accept(CodeGenVisitor *visitor, std::string reg) { visitor->visit(this, reg); }
void Char::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void Char::accept(CodeGenVisitor *visitor, std::string reg) { visitor->visit(this, reg); }
void String::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void String::accept(CodeGenVisitor *visitor, std::string reg) { visitor->visit(this, reg); }
void Null::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void Null::accept(CodeGenVisitor *visitor, std::string reg) { visitor->visit(this, reg); }
void BinaryOperator::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void BinaryOperator::accept(CodeGenVisitor *visitor, std::string reg) { visitor->visit(this, reg); }
void Identifier::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void Identifier::accept(CodeGenVisitor *visitor, std::string reg) { visitor->visit(this, reg); }
void ArrayElem::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void ArrayElem::accept(CodeGenVisitor *visitor, std::string reg) { visitor->visit(this, reg); }
void PairElem::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void PairElem::accept(CodeGenVisitor *visitor, std::string reg) { visitor->visit(this, reg); }
void ArrayLiter::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void ArrayLiter::accept(CodeGenVisitor *visitor, std::string reg) { visitor->visit(this, reg); }
void NewPair::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void NewPair::accept(CodeGenVisitor *visitor, std::string reg) { visitor->visit(this, reg); }
void UnaryOperator::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void UnaryOperator::accept(CodeGenVisitor *visitor, std::string reg) { visitor->visit(this, reg); }
void SkipStatement::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void SkipStatement::accept(CodeGenVisitor *visitor) { visitor->visit(this); }

