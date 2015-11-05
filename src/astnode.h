
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

typedef std::vector<FunctionDeclaration*> FunctionList;

class Program : public ASTnode{
  FunctionList functionDeclarations;
  StatSeq statements;
  
  Program() {}
}


class StatSeq : public Statement {
public:
  StatementList statements;

  StatSeq () {} 
};

class Identifier : public Expression {
public:
  std::string id;
	
  Identifier(std::string& id) : id(id) {}
};

class Assignment : public Statement {
public:
  Identifier& var;
  Expression& expr;

  Assignment(Identifier& var, Expression& expr) 
    : var(var), expr(expr) {}
};

class SkipStatement : public Statement {
  
}

class FreeStatement : public Statement {
  public:
    Expression& expr;

    FreeStatement(Expression& expr) : expr(expr) {}
}

class ReturnStatement : public Statement {
  public:
    Expression& expr;

    ReturnStatement(Expression& expr) : expr(expr) {}
}

class ExitStatement : public Statement {
  public:
    Expression& expr;

    ExitStatement(Expression& expr) : expr(expr) {}
}

class IfStatement : public Statement {
public:
  Expression&   expr;
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
  Identifier& id;
  
  ReadStatement(Identifier& id) : id(id) {}
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
}

class Char : public Expression {
  public:
    char value;

    Char(char value) : value(value) {}
}

class String : public Expression {
  public:
    std::string value;

    String(std::string value) : value(value) {}
}

class Null : public Expression {
}


class BinaryOperator : public Expression {
public:
  int op;
  Expression& left;
  Expression& right;
	
  BinaryOperator(Expression& left, int op, Expression& right) 
    : left(left), right(right), op(op) {}
};

class VariableDeclaration : public Statement { 
public:
  Identifier& type;
  Identifier& id;
  Expression* expr;

  VariableDeclaration(Identifier& type, Identifier& id) 
    : type(type), id(id) {}
  VariableDeclaration(Identifier& type, Identifier& id, Expression *expr) 
    : type(type), id(id), expr(expr) {}
};
typedef std::vector<VariableDeclaration*> VariableList;

class FunctionDeclaration : public Statement {
public:
  Identifier& type;
  Identifier& id;
  VariableList parameters;
  StatSeq& block;
  
  FunctionDeclaration(Identifier& type, Identifier& id, 
      VariableList& parameters, StatSeq& block) 
    : type(type), id(id), parameters(parameters), block(block) {}
};

class FunctionCall : public Expression {
public:
  Identifier& id;
  ExpressionList parameters;
  
  FunctionCall(Identifier& id, ExpressionList& parameters) 
    : id(id), parameters(parameters) {}
  FunctionCall(Identifier& id) 
    : id(id) {}
};
