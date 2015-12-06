#ifndef AST_NODE_VISITOR_HH
#define AST_NODE_VISITOR_HH
#include "semantic-id.hh"
#include "astnode.hh"
#include "symbol-table.hh"

class AstNodeVisitor {
public:

  virtual ~AstNodeVisitor() {}

  virtual void visit(ASTnode *node) = 0;
  virtual void visit(Program *node) = 0;
  virtual void visit(AssignRhs *node) = 0;
  virtual void visit(AssignLhs *node) = 0;
  virtual void visit(Expression *node) = 0;
  virtual void visit(StatSeq *node) = 0;
  virtual void visit(FunctionDecList *node) = 0;
  virtual void visit(IntegerType *node) = 0;
  virtual void visit(BoolType *node) = 0;
  virtual void visit(CharType *node) = 0;
  virtual void visit(StringType *node) = 0;
  virtual void visit(ArrayType *node) = 0;
  virtual void visit(PairType *node) = 0;
  virtual void visit(VariableDeclaration *node) = 0;
  virtual void visit(FunctionDeclaration *node) = 0;
  virtual void visit(FunctionCall *node) = 0;
  virtual void visit(Assignment *node) = 0;
  virtual void visit(FreeStatement *node) = 0;
  virtual void visit(ReturnStatement *node) = 0;
  virtual void visit(ExitStatement *node) = 0;
  virtual void visit(BeginStatement *node) = 0;
  virtual void visit(IfStatement *node) = 0;
  virtual void visit(WhileStatement *node) = 0;
  virtual void visit(ReadStatement *node) = 0;
  virtual void visit(PrintStatement *node) = 0;
  virtual void visit(PrintlnStatement *node) = 0;
  virtual void visit(Number *node) = 0;
  virtual void visit(Boolean *node) = 0;
  virtual void visit(Char *node) = 0;
  virtual void visit(String *node) = 0;
  virtual void visit(Null *node) = 0;
  virtual void visit(BinaryOperator *node) = 0;
  virtual void visit(Identifier *node) = 0;
  virtual void visit(ArrayElem *node) = 0;
  virtual void visit(PairElem *node) = 0;
  virtual void visit(ArrayLiter *node) = 0;
  virtual void visit(NewPair *node) = 0;
  virtual void visit(UnaryOperator *node) = 0;
};

#endif // ! AST_NODE_VISITOR_HH
