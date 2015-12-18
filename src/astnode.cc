#include "astnode.hh"
#include "semantic-visitor.hh"
#include "code-generation-visitor.hh"
#include "parser.hh"
#define tok yy::parser::token::yytokentype
ASTnode::~ASTnode() { };
void ASTnode::accept(SemanticVisitor *visitor) { };
void ASTnode::accept(CodeGenVisitor *visitor) { };

Program::Program(FunctionDecList* fs, StatSeq* stats) : functions(fs), statements(stats) { }
Program::~Program() { freePtr(functions); freePtr(statements); }

Expression::~Expression() { }

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
    : id(id) {
  this->type = type;      
}

VariableDeclaration::VariableDeclaration(TypeId *type, Identifier *id, AssignRhs *rhs)
    : id(id), rhs(rhs) {
  this->type =type;      
}

VariableDeclaration::~VariableDeclaration() {
    freePtr(type);
    freePtr(id);
    freePtr(rhs);
}

Param::Param(TypeId *type, Identifier *id) : id(id) {
  this->type = type;  
}
Param::~Param() {
  freePtr(type);
  freePtr(id);
}

FunctionDeclaration::FunctionDeclaration(TypeId *type, Identifier *id, StatSeq *block) 
    : type(type), id(id), block(block) {
        parameters = new ParamList();
        }

FunctionDeclaration::FunctionDeclaration(TypeId *type, Identifier *id, 
      ParamList *parameters, StatSeq *block) 
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

Expression* FunctionCall::optimise() {
  return this;
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

Expression* Number::optimise() {
  return this;
}

Boolean::Boolean(bool value) : value(value) {}

Expression* Boolean::optimise() {
  return this;
}

Char::Char(char value) : value(value) {}

Expression* Char::optimise() {
  return this;
}

String::String(std::string value) : value(value) {}

Expression* String::optimise() {
  return this;
}

Expression* Null::optimise() {
  return this;
}
BinaryOperator::BinaryOperator(Expression *left, int op, Expression *right): 
                    left(left), right(right), op(op) { }
BinaryOperator::~BinaryOperator() {freePtr(left); freePtr(right);}
Expression* BinaryOperator::optimise(){
  this->left = this->left->optimise();
  this->right = this->right->optimise();
  Number *numberLeft     = dynamic_cast<Number*>(this->left);
  Boolean *boolLeft      = dynamic_cast<Boolean*>(this->left);

  //StringTypeId *stringTypeIdLeft  = dynamic_cast<StringTypeId*>(left);
  //CharTypeId *charTypeIdLeft      = dynamic_cast<CharTypeId*>(left);  
  

  Number *numberRight    = dynamic_cast<Number*>(right);
  Boolean *boolRight     = dynamic_cast<Boolean*>(right);

  if (!((boolLeft && boolRight) || (numberLeft && numberRight))) {
    return this;
  }
  //StringTypeId *stringTypeIdRight = dynamic_cast<StringTypeId*>(right);
  //CharTypeId *charTypeIdRight     = dynamic_cast<CharTypeId*>(right);


  int oper = op;
  if(oper == tok::TOK_LOGOR || oper == tok::TOK_LOGAND){
        // if node left and right are both not constant
      if (oper == tok::TOK_LOGOR){
          return new Boolean(boolLeft->value || boolRight->value);
       } else if (oper == tok::TOK_LOGAND){
          //Implementation code-gen for AND 

         return new Boolean(boolLeft->value && boolRight->value);

      }      
   } else if (oper >= tok::TOK_STAR && oper <= tok::TOK_MINUS){
           if(oper == tok :: TOK_STAR){
               //Implementation code gen for MULTIPLY
               return new Number(numberLeft->value * numberRight->value);
           } else if (oper == tok::TOK_SLASH){
               //Implementation code gen for DIVIDE
               return new Number(numberLeft->value / numberRight->value);
           } else if (oper == tok::TOK_MODULO){
               //Implementation code-gen for MODULO
               return new Number(numberLeft->value % numberRight->value);
           } else if (oper == tok::TOK_PLUS){
               // Implementation code-gen for PLUS 
            return new Number(numberLeft->value + numberRight->value);
           } else if (oper == tok::TOK_MINUS){
               // Implementation code-gen for MINUS
            return new Number(numberLeft->value - numberRight->value);
           } 
        }else if (oper >= tok::TOK_LESS && oper <= tok::TOK_NOTEQUALS){
             if (oper == tok::TOK_LESS){
               // Implementation code-gen for LESS 
                  return new Boolean(numberLeft->value < numberRight->value);

           } else if (oper == tok::TOK_LESSEQUALS){
               //Implementation code-gen for LESSEQUALS
               return new Boolean(numberLeft->value <= numberRight->value);
                     
           } else if (oper == tok::TOK_GREATER){
               // Implementation code-gen for GREATER
               return new Boolean(numberLeft->value >= numberRight->value);
 
           } else if (oper == tok::TOK_GREATEREQUALS){
               // Implementation code-gen for GREATEREQUALS 
               return new Number(numberLeft->value / numberRight->value);
 
           } else if (oper == tok::TOK_EQUALS){
               //Implementation code-gen for EQUALS 
 
           } else if (oper == tok::TOK_NOTEQUALS){
               // Implementation code-gen for Not EQUAL
                     
           }
    }
    return this;
}

Expression* ArrayElem::optimise() {
  return this;
}

ArrayElem::ArrayElem(Identifier *id, ExpressionList *idxs) : id(id), 
              idxs(idxs) {}
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

Expression* UnaryOperator::optimise() {
  return this;
}

std::string Identifier::getId() {
  return id;
}

Expression* Identifier::optimise() {
  return this;
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
void Param::accept(SemanticVisitor *visitor) { visitor->visit(this); }
int Param::accept(CodeGenVisitor *visitor, int scope) { return visitor->visit(this, scope); }
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
void Identifier::accept(CodeGenVisitor *visitor) { visitor->visit(this); }
void Identifier::accept(CodeGenVisitor *visitor, std::string reg) { visitor->visit(this, reg); }
void ArrayElem::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void ArrayElem::accept(CodeGenVisitor *visitor) { visitor->visit(this); }
void ArrayElem::accept(CodeGenVisitor *visitor, std::string reg) { visitor->visit(this, reg); }
void PairElem::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void PairElem::accept(CodeGenVisitor *visitor) { visitor->visit(this); }
void PairElem::accept(CodeGenVisitor *visitor, std::string reg) { visitor->visit(this, reg); }
void ArrayLiter::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void ArrayLiter::accept(CodeGenVisitor *visitor, std::string reg) { visitor->visit(this, reg); }
void NewPair::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void NewPair::accept(CodeGenVisitor *visitor, std::string reg) { visitor->visit(this, reg); }
void UnaryOperator::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void UnaryOperator::accept(CodeGenVisitor *visitor, std::string reg) { visitor->visit(this, reg); }
void SkipStatement::accept(SemanticVisitor *visitor) { visitor->visit(this); }
void SkipStatement::accept(CodeGenVisitor *visitor) { visitor->visit(this); }

