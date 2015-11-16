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
  ASTnode() { }
  virtual ~ASTnode() {  }
  virtual void accept(AstNodeVisitor *visitor);
};

class AssignLhs : public ASTnode {
public:
  std::string type;
  virtual std::string getId();
};

class AssignRhs : public ASTnode {
public: 
  std::string type;
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
  void accept(AstNodeVisitor *visitor);
};

class PairKeyword : public Type {
public:
  PairKeyword();
  ~PairKeyword();
  void accept(AstNodeVisitor *visitor);
};

class PairType : public Type {
public:
  Type *fst;
  Type *snd;

  PairType(Type *fst, Type *snd);
  ~PairType();
  void accept(AstNodeVisitor *visitor);
};

class Identifier : public Expression, public AssignLhs {
public:
  std::string id;
	
  Identifier(){}
  Identifier(std::string& id) : id(id){}
  ~Identifier(){}
  void accept(AstNodeVisitor *visitor);
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
  void accept(AstNodeVisitor *visitor);
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
  SkipStatement();
  ~SkipStatement();

  void accept(AstNodeVisitor *visitor);
};

class FreeStatement : public Statement {
public:
	Expression *expr = NULL;

  FreeStatement(Expression *expr);
  ~FreeStatement();
  void accept(AstNodeVisitor* visitor);
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
  std::string type = "number";
  int value;
  
  Number(int value);
  void accept(AstNodeVisitor *visitor);
};

class Boolean : public Expression {
public:
  std::string type = "bool";
  bool value;

  Boolean(bool value);
  void accept(AstNodeVisitor *visitor);
};

class Char : public Expression {
public:
  std::string type = "char";
  char value;

  Char(char value);
  void accept(AstNodeVisitor *visitor);
};

class String : public Expression {
public:
  std::string value = "string";

  String(std::string value);
  void accept(AstNodeVisitor *visitor);
};

class Null : public Expression {
  std::string type = "null";
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
  void accept(AstNodeVisitor *visitor);
  std::string getId();
};

class PairElem : public AssignLhs, public AssignRhs {
public:
	bool fst;
	Expression *expr = NULL;
	
  PairElem(bool fst, Expression *expr);
  ~PairElem();
  void accept(AstNodeVisitor *visitor);
  std::string getId();
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
