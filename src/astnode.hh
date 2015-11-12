#ifndef ASTNODE_HH
#define ASTNODE_HH

#include <vector>
#include <iostream>

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
  ~ArrayType() { delete type; }
};

class PairKeyword : public Type {
};

class PairType : public Type {
public:
  Type *fst;
	Type *snd;

	PairType(Type *fst, Type *snd) : fst(fst), snd(snd) {}
//  ~PairType() { delete fst; delete snd; }
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

//  ~VariableDeclaration() { 
//    delete type; 
//    delete id; 
//    if (rhs != NULL) {
//      delete rhs;
//    }
//  }
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

//  ~FunctionDeclaration() { 
//    delete type;
//    delete id;
//    if (parameters != NULL) {
//      for(int i=0; i < parameters->size(); i++) {
//        delete (*parameters)[i];
//      }
//      delete parameters;
//    }
//    delete block;
//  }

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

//  ~FunctionCall() {
//    delete id;
//    if (parameters != NULL) {
//      for(int i = 0; i < parameters->size(); ++i) {
//        delete (*parameters)[i];
//      }
//      delete parameters;
//    }
//  }
};

class Program : public ASTnode{
public:  
	FunctionDecList* functions;
  StatSeq* statements;
  
  Program(FunctionDecList* fs, StatSeq* stats)
		 : functions(fs), statements(stats) {}

//  ~Program() { delete functions; delete statements; }
};

class Assignment : public Statement {
public:
  AssignLhs *lhs;
  AssignRhs *rhs;

  Assignment(AssignLhs *lhs, AssignRhs *rhs) 
    : lhs(lhs), rhs(rhs) {}

//  ~Assignment() { delete lhs; delete rhs; }
};

class SkipStatement : public Statement {
};

class FreeStatement : public Statement {
public:
	Expression *expr;

  FreeStatement(Expression *expr) : expr(expr) {}
//  ~FreeStatement() { delete expr;}
};

class ReturnStatement : public Statement {
public:
  Expression *expr;

  ReturnStatement(Expression *expr) : expr(expr) {}
//  ~ReturnStatement() { delete expr; }
};

class ExitStatement : public Statement {
public:
  Expression *expr;

  ExitStatement(Expression *expr) : expr(expr) {}
//  ~ExitStatement() { delete expr; }
};

class BeginStatement : public Statement {
public:
	StatSeq *scope;

	BeginStatement(StatSeq *scope) : scope(scope) {}
//  ~BeginStatement() { delete scope; }
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

//  ~IfStatement() {
//    delete expr; 
//    delete thenS;
//    if (elseS != NULL) {
//       delete elseS;
//    }
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
//  ~RepeatStatement() {delete block; delete expr;}
};

class ReadStatement : public Statement {
public:
  AssignLhs *id;
  
  ReadStatement(AssignLhs *id) : id(id) {}
//  ~ReadStatement() {delete id;}
};

class PrintStatement : public Statement {
public:
  Expression *expr;

  PrintStatement(Expression *expr) : expr(expr) {}
//  ~PrintStatement() {delete expr;}
};

class PrintlnStatement : public Statement {
public:
  Expression *expr;

  PrintlnStatement(Expression *expr) : expr(expr) {}
//  ~PrintlnStatement() {delete expr;}
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
//  ~BinaryOperator() {delete left; delete right;}
};

class ArrayElem : public AssignLhs, public Expression {
public:
	Identifier *id;
	ExpressionList *idxs;

	ArrayElem(Identifier *id, ExpressionList *idxs) : id(id), idxs(idxs) {}
//  ~ArrayElem() {
//    delete id;
//    for (int i = 0; i < idxs->size(); ++i){
//      delete (*idxs)[i];
//    }
//    delete idxs;
//  }
};

class PairElem : public AssignLhs, public AssignRhs {
public:
	bool fst;
	Expression *expr;
	
	PairElem(bool fst, Expression *expr) : fst(fst), expr(expr) {} 
//  ~PairElem() {delete expr;}
};

class ArrayLiter : public AssignRhs {
public:
	ExpressionList *elems;

	ArrayLiter(ExpressionList *elems) : elems(elems) {}
//  ~ArrayLiter() {
//    for (int i = 0; i < elems->size(); ++i) {
//      delete (*elems)[i];
//    }
//    delete elems;
//  }
};

class NewPair : public AssignRhs {
public: 
	Expression *fst;
	Expression *snd;

	NewPair(Expression *fst, Expression *snd) : fst(fst), snd(snd) {}
//  ~NewPair() {delete fst; delete snd;}
};

class UnaryOperator : public Expression	{
public:	
	int op;
	Expression *expr;

	UnaryOperator(int op, Expression *expr) : op(op), expr(expr) {}
//  ~UnaryOperator() {delete expr;}
};

#endif // ! ASTNODE_HH
