#ifndef ASTNODE_HH
#define ASTNODE_HH

#include <vector>
#include <iostream>

template<class T>
void freePtr(T *ptr) {
     if(ptr) { 
        delete ptr;
     }
}


class ASTnode {
public:
  virtual ~ASTnode() {}
  virtual void check() {}
};

class AssignLhs : public ASTnode {
};

class AssignRhs : public ASTnode { 
};

class Expression : public AssignRhs { };
typedef std::vector<Expression*> ExpressionList;

class Statement : public ASTnode { };
typedef std::vector<Statement*> StatementList;

class StatSeq : public Statement {
public:
  StatementList statements;
  StatSeq() { }  
};

class Type : public ASTnode {
};

class IntegerType : public Type {
};

class BoolType : public Type {
};

class CharType : public Type {
};

class StringType : public Type {
};

class ArrayType : public Type {
public:
	Type *type;
	
	ArrayType(Type *type) : type(type) {}
  ~ArrayType() { freePtr(type); }
};

class PairKeyword : public Type {
};

class PairType : public Type {
public:
  Type *fst;
	Type *snd;

	PairType(Type *fst, Type *snd) : fst(fst), snd(snd) {}
    ~PairType() {  freePtr(fst); freePtr(snd); }
};

class Identifier : public Expression, public AssignLhs {
public:
  std::string id;
	
  Identifier() {}
  Identifier(std::string& id) : id(id) {}
};

class VariableDeclaration : public Statement { 
public:
  Type *type;
  Identifier *id;
  AssignRhs *rhs;

  VariableDeclaration(Type *type, Identifier *id) 
    : type(type), id(id) {}

  VariableDeclaration(Type *type, Identifier *id, AssignRhs *rhs) 
    : type(type), id(id), rhs(rhs) {}

  ~VariableDeclaration() { 
    freePtr(type); 
    freePtr(id)
	freePtr(rhs)
	}
};
typedef std::vector<VariableDeclaration*> VariableList;

class FunctionDeclaration : public Statement {
public:
  Type *type;
  Identifier *id;
  VariableList *parameters;
  StatSeq *block;
  
  FunctionDeclaration(Type *type, Identifier *id, StatSeq *block) 
    : type(type), id(id), parameters(0), block(block) {}

  FunctionDeclaration(Type *type, Identifier *id, 
      VariableList *parameters, StatSeq *block) 
    : type(type), id(id), parameters(parameters), block(block) {}

  ~FunctionDeclaration() { 
    freePtr(type)
    freePtr(id)
    if (parameters != NULL) {
      for(int i=0; i < parameters->size(); i++) {
        freePtr((*parameters)[i]);
      }
      freePtr(parameters)
    }
    freePtr(block);
  }
};

typedef std::vector<FunctionDeclaration*> FunctionList;

class FunctionDecList : public ASTnode {
public:
  FunctionList funcs;
  FunctionDecList() { }
};

class FunctionCall : public Expression {
public:
  Identifier *id;
  ExpressionList *parameters;
  
  FunctionCall(Identifier *id, ExpressionList *parameters) 
    : id(id), parameters(parameters) {}
  FunctionCall(Identifier *id) 
    : id(id) {}

  ~FunctionCall() {
     freePtr(id);
     if (parameters != NULL) {
        for(int i=0; i < parameters->size(); i++) {
          freePtr((*parameters)[i]);
        }
        freePtr(parameters)
     }
  }  
};

class Program : public ASTnode{
public:  
	FunctionDecList* functions;
  StatSeq* statements;
  
  Program(FunctionDecList* fs, StatSeq* stats)
		 : functions(fs), statements(stats) {}

  ~Program() { freePtr(functions); freePtr(statements); }
};

class Assignment : public Statement {
public:
  AssignLhs *lhs;
  AssignRhs *rhs;

  Assignment(AssignLhs *lhs, AssignRhs *rhs) 
    : lhs(lhs), rhs(rhs) {}

  ~Assignment() { freePtr(lhs); freePtr(rhs); }
};

class SkipStatement : public Statement {
};

class FreeStatement : public Statement {
public:
	Expression *expr;

  FreeStatement(Expression *expr) : expr(expr) {}
  ~FreeStatement() { freePtr(expr); }
};

class ReturnStatement : public Statement {
public:
  Expression *expr;

  ReturnStatement(Expression *expr) : expr(expr) {}
  ~ReturnStatement() { freePtr(expr); }
};

class ExitStatement : public Statement {
public:
  Expression *expr;

  ExitStatement(Expression *expr) : expr(expr) {}
  ~ExitStatement() { freePtr(expr);}
};

class BeginStatement : public Statement {
public:
  
  StatSeq *scope;
  BeginStatement(StatSeq *scope) : scope(scope) {}
  ~BeginStatement() { freePtr(scope); }
};

class IfStatement : public Statement {
public:
  Expression *expr;
  StatSeq *thenS;
  StatSeq *elseS; 

  IfStatement(Expression *expr, StatSeq *thenS) 
    : expr(expr), thenS(thenS) {}

  IfStatement(Expression *expr, StatSeq *thenS, StatSeq *elseS)
    : expr(expr), thenS(thenS), elseS(elseS) {}

  ~IfStatement() {
    freePtr(expr); 
    freePtr(thenS);
    freePtr(elseS);
//  }
};

class WhileStatement : public Statement {
public:
  Expression *expr;
  StatSeq *doS;

  WhileStatement(Expression *expr, StatSeq *doS) 
    : expr(expr), doS(doS) {}
//  ~WhileStatement() { delete expr; delete doS; }
};

class RepeatStatement : public Statement {
public:
  StatSeq *block;
  Expression *expr;

  RepeatStatement(StatSeq *block, Expression *expr) 
    : block(block), expr(expr) {}
  ~RepeatStatement() {freePtr(block); freePtr(expr);}
};

class ReadStatement : public Statement {
public:
  AssignLhs *id;
  
  ReadStatement(AssignLhs *id) : id(id) {}
  ~ReadStatement() {freePtr(id);}
};

class PrintStatement : public Statement {
public:
  Expression *expr;

  PrintStatement(Expression *expr) : expr(expr) {}
  ~PrintStatement() {freePtr(expr);}
};

class PrintlnStatement : public Statement {
public:
  Expression *expr;

  PrintlnStatement(Expression *expr) : expr(expr) {}
  ~PrintlnStatement() {freePtr(expr);}
};

class Number : public Expression {
public:
  int value;
  
  Number(int value) : value(value) {}
};

class Boolean : public Expression {
public:
  bool value;

  Boolean(bool value) : value(value) {}
};

class Char : public Expression {
public:
  char value;

  Char(char value) : value(value) {}
};

class String : public Expression {
public:
  std::string value;

  String(std::string value) : value(value) {}
};

class Null : public Expression {
};

class BinaryOperator : public Expression {
public:
  int op;
  Expression *left;
  Expression *right;
	
  BinaryOperator(Expression *left, int op, Expression *right) 
    : left(left), right(right), op(op) {}
  ~BinaryOperator() {freePtr(left); freePtr(right);}
};

class ArrayElem : public AssignLhs, public Expression {
public:
	Identifier *id;
	ExpressionList *idxs;

	ArrayElem(Identifier *id, ExpressionList *idxs) : id(id), idxs(idxs) {}
  ~ArrayElem() {
    freePtr(id);
    for (int i = 0; i < idxs->size(); ++i){
      freePtr((*idxs)[i]);
    }
    freePtr(idxs);
  }
};

class PairElem : public AssignLhs, public AssignRhs {
public:
	bool fst;
	Expression *expr;
	
	PairElem(bool fst, Expression *expr) : fst(fst), expr(expr) {} 
    ~PairElem() {freePtr(expr)}
};

class ArrayLiter : public AssignRhs {
public:
	ExpressionList *elems;

	ArrayLiter(ExpressionList *elems) : elems(elems) {}
    ~ArrayLiter() {
      for (int i = 0; i < elems->size(); ++i) {
        delete (*elems)[i];
      }
      freePtr(elems);
    }
};

class NewPair : public AssignRhs {
public: 
	Expression *fst;
	Expression *snd;

	NewPair(Expression *fst, Expression *snd) : fst(fst), snd(snd) {}
  ~NewPair() {freePtr(fst); freePtr(snd);}
};

class UnaryOperator : public Expression	{
public:	
	int op;
	Expression *expr;

	UnaryOperator(int op, Expression *expr) : op(op), expr(expr) {}
    ~UnaryOperator() {freePtr(expr);}
};

#endif // ! ASTNODE_HH
