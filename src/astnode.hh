#ifndef ASTNODE_HH
#define ASTNODE_HH

#include <vector>
#include <iostream>
#include "semantic-id.hh"
#include "symbol-table.hh"

class AstNodeVisitor;

template<class T>
void freePtr(T *ptr) {
        if (ptr) delete ptr;
        ptr = NULL;
}

class ASTnode {
public:
  ASTnode() { }
  virtual ~ASTnode() {  }
  virtual void accept(AstNodeVisitor *visitor);
};

class AssignLhs : public virtual ASTnode {
public:
  virtual std::string getId();
  void accept(AstNodeVisitor *visitor);
};

class AssignRhs : public virtual ASTnode {
public: 
  SymbolTable *scope = NULL;
  TypeId *type = NULL;
  AssignRhs() { }
  void accept(AstNodeVisitor *visitor);
};

class Expression : public AssignRhs { 
public: 
  Expression() { }
  virtual ~Expression() { }; 
  void accept(AstNodeVisitor *visitor);
};
typedef std::vector<Expression*> ExpressionList;

class Statement : public ASTnode { 
public: 
  virtual ~Statement() {}
  void accept(AstNodeVisitor *visitor);
};
typedef std::vector<Statement*> StatementList;

class StatSeq : public Statement {
public:
  StatementList statements;
  StatSeq();
  ~StatSeq();
  bool containRet();
  void accept(AstNodeVisitor *visitor);
};

class Identifier : public Expression, public AssignLhs {
public:
  std::string id;
	
  Identifier(){}
  Identifier(std::string& id) : id(id){}
  ~Identifier(){}
  std::string getId();
  void accept(AstNodeVisitor *visitor);
};

class VariableDeclaration : public Statement { 
public:
  TypeId *type = NULL;
  SymbolTable *scope = NULL;
  Identifier *id = NULL;
  AssignRhs *rhs = NULL;

  VariableDeclaration(TypeId *type, Identifier *id);

  VariableDeclaration(TypeId *type, Identifier *id, AssignRhs *rhs);

  ~VariableDeclaration();
  void accept(AstNodeVisitor *visitor);
};
typedef std::vector<VariableDeclaration*> VariableList;

class FunctionDeclaration : public Statement {
public:
  TypeId *type = NULL;
  Identifier *id = NULL;
  VariableList *parameters = NULL;
  StatSeq *block = NULL;
  
  FunctionDeclaration(TypeId *type, Identifier *id, StatSeq *block);

  FunctionDeclaration(TypeId *type, Identifier *id, 
      VariableList *parameters, StatSeq *block);

  ~FunctionDeclaration(); 
  void accept(AstNodeVisitor *visitor);
};

typedef std::vector<FunctionDeclaration*> FunctionList;

class FunctionDecList : public ASTnode {
public:
  FunctionList funcs;
  FunctionDecList();
  ~FunctionDecList();
  void accept(AstNodeVisitor *visitor);
};

class FunctionCall : public Expression {
public:
  Identifier *id = NULL;
  ExpressionList *parameters = NULL;
  
  FunctionCall(Identifier *id, ExpressionList *parameters);
  FunctionCall(Identifier *id);

  ~FunctionCall();
  void accept(AstNodeVisitor *visitor);
};

class Program : public ASTnode{
public:  
  FunctionDecList* functions;
  StatSeq* statements;
  
  Program(FunctionDecList* fs, StatSeq* stats);
  ~Program();
  void accept(AstNodeVisitor *visitor);
};

class Assignment : public Statement {
public:
  AssignLhs *lhs = NULL;
  AssignRhs *rhs = NULL;

  Assignment(AssignLhs *lhs, AssignRhs *rhs);

  ~Assignment();
  void accept(AstNodeVisitor *visitor);

};

class SkipStatement : public Statement {
public:
  SkipStatement() { }
  ~SkipStatement() { }
  void accept(AstNodeVisitor *visitor);

};

class FreeStatement : public Statement {
public:
	Expression *expr = NULL;

  FreeStatement(Expression *expr);
  ~FreeStatement();
  void accept(AstNodeVisitor *visitor);
};

class ReturnStatement : public Statement {
public:
  Expression *expr = NULL;

  ReturnStatement(Expression *expr);
  ~ReturnStatement();
  void accept(AstNodeVisitor *visitor);
};

class ExitStatement : public Statement {
public:
  Expression *expr = NULL;

  ExitStatement(Expression *expr);
  ~ExitStatement();
  void accept(AstNodeVisitor *visitor);
};

class BeginStatement : public Statement {
public:
  
  StatSeq *scope = NULL;
  BeginStatement(StatSeq *scope);
  ~BeginStatement();
  void accept(AstNodeVisitor *visitor);
};

class IfStatement : public Statement {
public:
  Expression *expr = NULL;
  StatSeq *thenS = NULL;
  StatSeq *elseS = NULL; 

  IfStatement(Expression *expr, StatSeq *thenS);
  IfStatement(Expression *expr, StatSeq *thenS, StatSeq *elseS);
  ~IfStatement();
  void accept(AstNodeVisitor *visitor);
};

class WhileStatement : public Statement {
public:
  Expression *expr = NULL;
  StatSeq *doS = NULL;

  WhileStatement(Expression *expr, StatSeq *doS);
  ~WhileStatement();
  void accept(AstNodeVisitor *visitor);
};

class ReadStatement : public Statement {
public:
  AssignLhs *id = NULL;
  
  ReadStatement(AssignLhs *id);
  ~ReadStatement();
  void accept(AstNodeVisitor *visitor);
};

class PrintStatement : public Statement {
public:
  Expression *expr = NULL;

  PrintStatement(Expression *expr);
  ~PrintStatement();
  void accept(AstNodeVisitor *visitor);
};

class PrintlnStatement : public Statement {
public:
  Expression *expr = NULL;

  PrintlnStatement(Expression *expr);
  ~PrintlnStatement();
  void accept(AstNodeVisitor *visitor);
};

class Number : public Expression {
public:
  int value;
  
  Number(int value);
  void accept(AstNodeVisitor *visitor);
};

class Boolean : public Expression {
public:
  bool value;

  Boolean(bool value);
  void accept(AstNodeVisitor *visitor);
};

class Char : public Expression {
public:
  char value;

  Char(char value);
  void accept(AstNodeVisitor *visitor);
};

class String : public Expression {
public:
  std::string value;

  String(std::string value);
  void accept(AstNodeVisitor *visitor);
};

class Null : public Expression {
public:
  void accept(AstNodeVisitor *visitor);
};

class BinaryOperator : public Expression {
public:
  int op;
  Expression *left;
  Expression *right;
	
  BinaryOperator(Expression *left, int op, Expression *right);
  ~BinaryOperator();
  void accept(AstNodeVisitor *visitor);
};

class ArrayElem : public AssignLhs, public Expression {
public: 
	Identifier *id = NULL;
	ExpressionList *idxs = NULL;

  ArrayElem(Identifier *id, ExpressionList *idxs);
  ~ArrayElem();
  std::string getId();
  void accept(AstNodeVisitor *visitor);
};

class PairElem : public AssignLhs, public AssignRhs {
public:
	bool fst;
	Expression *expr = NULL;
	
  PairElem(bool fst, Expression *expr);
  ~PairElem();
  std::string getId();
  void accept(AstNodeVisitor *visitor);
};

class ArrayLiter : public AssignRhs {
public:
	ExpressionList *elems = NULL;

	ArrayLiter(ExpressionList *elems);
  ~ArrayLiter();
  void accept(AstNodeVisitor *visitor);
};

class NewPair : public AssignRhs {
public: 
	Expression *fst = NULL;
	Expression *snd = NULL;

  NewPair(Expression *fst, Expression *snd);
  ~NewPair();
  void accept(AstNodeVisitor *visitor);
};

class UnaryOperator : public Expression	{
public:	
	int op;
	Expression *expr;

	UnaryOperator(int op, Expression *expr);
  ~UnaryOperator();
  void accept(AstNodeVisitor *visitor);
};

#endif // ! ASTNODE_HH
