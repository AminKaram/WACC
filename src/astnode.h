#include <vector>
#include <iostream>

class ASTnode {
public:
  virtual ~ASTnode() {}
  virtual void check() {}
};

class Expression : public ASTnode { };
typedef std::vector<Expression*> ExpressionList;

class Statement : public ASTnode { };
typedef std::vector<Statement*> StatementList;

class AssignLhs : public ASTnode {
};

class AssignRhs : public ASTnode { 
};

class Identifier : public Expression, public AssignLhs, public AssignRhs {
public:
  std::string id;
	
  Identifier(std::string& id) : id(id) {}
};

class StatSeq : public Statement {
public:
  StatementList& statements;

  StatSeq() : statements(new StatementList()) {} 
};

class VariableDeclaration : public Statement { 
public:
  Identifier& type;
  Identifier& id;
  AssignRhs* rhs;

  VariableDeclaration(Identifier& type, Identifier& id) 
    : type(type), id(id) {}

  VariableDeclaration(Identifier& type, Identifier& id, AssignRhs *rhs) 
    : type(type), id(id), rhs(rhs) {}
};
typedef std::vector<VariableDeclaration*> VariableList;

class FunctionDecList : public ASTnode {
public:
	FunctionList& funcs;

	FunctionDecList() : funcs(new FunctionList()) {}
};

class FunctionDeclaration : public Statement {
public:
  Identifier& type;
  Identifier& id;
  VariableList parameters;
  StatSeq& block;
  
  FunctionDeclaration(Identifier& type, Identifier& id, StatSeq& block) 
    : type(type), id(id), parameters(new VariableList()), block(block) {}

  FunctionDeclaration(Identifier& type, Identifier& id, 
      VariableList& parameters, StatSeq& block) 
    : type(type), id(id), parameters(parameters), block(block) {}
};
typedef std::vector<FunctionDeclaration*> FunctionList;

class FunctionCall : public Expression {
public:
  Identifier& id;
  ExpressionList parameters;
  
  FunctionCall(Identifier& id, ExpressionList& parameters) 
    : id(id), parameters(parameters) {}
  FunctionCall(Identifier& id) 
    : id(id) {}
};

class Program : public ASTnode{
public:  
	FunctionDecList& functions;
  StatSeq& statements;
  
  Program(FunctionDecList& fs, StatSeq& stats)
		 : functions(fs), statements(stats) {}
};

class Assignment : public Statement {
public:
  AssignLhs& lhs;
  AssignRhs& rhs;

  Assignment(AssignLhs& lhs, AssignRhs& rhs) 
    : lhs(lhs), rhs(rhs) {}
};

class SkipStatement : public Statement {
};

class FreeStatement : public Statement {
public:
	Expression& expr;

  FreeStatement(Expression& expr) : expr(expr) {}
};

class ReturnStatement : public Statement {
public:
  Expression& expr;

  ReturnStatement(Expression& expr) : expr(expr) {}
};

class ExitStatement : public Statement {
public:
  Expression& expr;

  ExitStatement(Expression& expr) : expr(expr) {}
};

class IfStatement : public Statement {
public:
  Expression& expr;
  StatSeq& thenS;
  StatSeq* elseS; 

  IfStatement(Expression& expr, StatSeq& thenS) 
    : expr(expr), thenS(thenS) {}

  IfStatement(Expression& expr, StatSeq& thenS, StatSeq* elseS)
    : expr(expr), thenS(thenS), elseS(elseS) {}
};

class WhileStatement : public Statement {
public:
  Expression& expr;
  StatSeq& doS;

  WhileStatement(Expression& expr, StatSeq& doS) 
    : expr(expr), doS(doS) {}
};

class RepeatStatement : public Statement {
public:
  StatSeq& block;
  Expression& expr;

  RepeatStatement(StatSeq& block, Expression& expr) 
    : block(block), expr(expr) {}
};

class ReadStatement : public Statement {
public:
  AssignLhs& id;
  
  ReadStatement(AssignLhs& id) : id(id) {}
};

class PrintStatement : public Statement {
public:
  Expression& expr;

  PrintStatement(Expression& expr) : expr(expr) {}
};

class PrintlnStatement : public Statement {
public:
  Expression& expr;

  PrintlnStatement(Expression& expr) : expr(expr) {}
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
  Expression& left;
  Expression& right;
	
  BinaryOperator(Expression& left, int op, Expression& right) 
    : left(left), right(right), op(op) {}
};

class ArrayElem : public AssignLhs {
public:
	Identifier& id;
	Expression& expr;

	ArrayElem(Identifier& id, Expression& expr) : id(id), expr(expr) {}
};

class PairElem : public AssignLhs, public AssignRhs {
public:
	bool fst;
	Expression& expr;
	
	PairElem(bool fst, Expression& expr) : fst(fst), expr(expr) {}
};

class ArrayLiter : public AssignRhs {
public:
	ExpressionList elems;

	ArrayLiter(ExpressionList& elems) : elems(elems) {}
};

class NewPair : public AssignRhs {
public: 
	Expression& fst;
	Expression& snd;

	NewPair(Expression& fst, Expression& snd) : fst(fst), snd(snd) {}
};

class UnaryOperator : public Expression	{
public:	
	int op;
	Expression& expr;

	UnaryOperator(int op, Expression& expr) : op(op), expr(expr) {}
};

