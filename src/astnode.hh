#ifndef ASTNODE_HH
#define ASTNODE_HH

#include <vector>
#include <iostream>

class AstNodeVisitor;

template<class T>
void freePtr(T *ptr) {
  if (ptr) delete ptr;
  ptr = NULL;
}

class ASTnode {
public:
  std::string type;
  ASTnode() { }
  virtual ~ASTnode() {  }
  virtual void accept(AstNodeVisitor *visitor);
};

class AssignLhs : public virtual ASTnode {
public:
  virtual std::string getId();
};

class AssignRhs : public virtual ASTnode {
public: 
  AssignRhs() { }
  AssignRhs(std::string type);
};

class Expression : public AssignRhs { 
public: 
  virtual ~Expression() {} 
};
typedef std::vector<Expression*> ExpressionList;

class Statement : public ASTnode { 
public: 
  virtual ~Statement() {}
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

class Type : public ASTnode {
public:
  std::string name;
  Type(std::string name);
  ~Type();
};

class IntegerType : public Type {
public:
  IntegerType();
};

class BoolType : public Type {
public:
  BoolType();
};

class CharType : public Type {
public:
  CharType();
};

class StringType : public Type {
public:
  StringType ();
};

class ArrayType : public Type {
public:
	Type *type = NULL;
	
  ArrayType(Type *type); 
  ~ArrayType();
};

class PairKeyword : public Type {
public:
  PairKeyword();
  ~PairKeyword();
};

class PairType : public Type {
public:
  Type *fst;
  Type *snd;

  PairType(Type *fst, Type *snd);
  ~PairType();
};

class Identifier : public Expression, public AssignLhs {
public:
  std::string id;
	
  Identifier(){}
  Identifier(std::string& id) : id(id){}
  ~Identifier(){}
  std::string getId();
};

class VariableDeclaration : public Statement { 
public:
  Type *type = NULL;
  Identifier *id = NULL;
  AssignRhs *rhs = NULL;

  VariableDeclaration(Type *type, Identifier *id);

  VariableDeclaration(Type *type, Identifier *id, AssignRhs *rhs);

  ~VariableDeclaration();
};
typedef std::vector<VariableDeclaration*> VariableList;

class FunctionDeclaration : public Statement {
public:
  Type *type = NULL;
  Identifier *id = NULL;
  VariableList *parameters = NULL;
  StatSeq *block = NULL;
  
  FunctionDeclaration(Type *type, Identifier *id, StatSeq *block);

  FunctionDeclaration(Type *type, Identifier *id, 
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
};

class SkipStatement : public Statement {
public:
  SkipStatement();
  ~SkipStatement();
};

class FreeStatement : public Statement {
public:
	Expression *expr = NULL;

  FreeStatement(Expression *expr);
  ~FreeStatement();
};

class ReturnStatement : public Statement {
public:
  Expression *expr = NULL;

  ReturnStatement(Expression *expr);
  ~ReturnStatement();
  void accept(AstNodeVisitor* visitor);
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
  void accept(AstNodeVisitor* visitor);
};

class WhileStatement : public Statement {
public:
  Expression *expr = NULL;
  StatSeq *doS = NULL;

  WhileStatement(Expression *expr, StatSeq *doS);
  ~WhileStatement();
  void accept(AstNodeVisitor * visitor);
};

class ReadStatement : public Statement {
public:
  AssignLhs *id = NULL;
  
  ReadStatement(AssignLhs *id);
  ~ReadStatement();
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
};

class Number : public Expression {
public:
  std::string type = "number";
  int value;
  
  Number(int value);
};

class Boolean : public Expression {
public:
  std::string type = "bool";
  bool value;

  Boolean(bool value);
};

class Char : public Expression {
public:
  std::string type = "char";
  char value;

  Char(char value);
};

class String : public Expression {
public:
  std::string value = "string";

  String(std::string value);
};

class Null : public Expression {
public:
};

class BinaryOperator : public Expression {
public:
  int op;
  Expression *left;
  Expression *right;
	
  BinaryOperator(Expression *left, int op, Expression *right);
  ~BinaryOperator();
};

class ArrayElem : public AssignLhs, public Expression {
public: 
	Identifier *id = NULL;
	ExpressionList *idxs = NULL;

  ArrayElem(Identifier *id, ExpressionList *idxs);
  ~ArrayElem();
  std::string getId();
};

class PairElem : public AssignLhs, public AssignRhs {
public:
	bool fst;
	Expression *expr = NULL;
	
  PairElem(bool fst, Expression *expr);
  ~PairElem();
  std::string getId();
};

class ArrayLiter : public AssignRhs {
public:
	ExpressionList *elems = NULL;

	ArrayLiter(ExpressionList *elems);
  ~ArrayLiter();
};

class NewPair : public AssignRhs {
public: 
	Expression *fst = NULL;
	Expression *snd = NULL;

  NewPair(Expression *fst, Expression *snd);
  ~NewPair();
};

class UnaryOperator : public Expression	{
public:	
	int op;
	Expression *expr;

	UnaryOperator(int op, Expression *expr);
    ~UnaryOperator();
};

#endif // ! ASTNODE_HH
