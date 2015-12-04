#ifndef CODE_GENERATION_VISITOR_HH
#define CODE_GENERATION_VISITOR_HH
#include "ast-node-visitor.hh"

class CodeGenVisitor : public AstNodeVisitor {
public:
  CodeGenVisitor(std::ostream *stream);
  ~CodeGenVisitor();

  void visit(ASTnode *node);
  void visit(Program *node);
  void visit(AssignRhs *node);
  void visit(AssignLhs *node);
  void visit(Expression *node);
  void visit(StatSeq *node);
  void visit(FunctionDecList *node);
  void visit(IntegerType *node);
  void visit(BoolType *node);
  void visit(CharType *node);
  void visit(StringType *node);
  void visit(ArrayType *node);
  void visit(PairType *node);
  void visit(VariableDeclaration *node);
  void visit(FunctionDeclaration *node);
  void visit(FunctionCall *node);
  void visit(Assignment *node);
  void visit(FreeStatement *node);
  void visit(ReturnStatement *node);
  void visit(ExitStatement *node);
  void visit(BeginStatement *node);
  void visit(IfStatement *node);
  void visit(WhileStatement *node);
  void visit(ReadStatement *node);
  void visit(PrintStatement *node);
  void visit(PrintlnStatement *node);
  void visit(Number *node);
  void visit(Boolean *node);
  void visit(Char *node);
  void visit(String *node);
  void visit(Null *node);
  void visit(BinaryOperator *node);
  void visit(Identifier *node);
  void visit(ArrayElem *node);
  void visit(PairElem *node);
  void visit(ArrayLiter *node);
  void visit(NewPair *node);
  void visit(UnaryOperator *node);

  void defineLabel(String label);

private:
  std::ostream *output;

};


#endif // ! CODE_GENERATION_VISITOR_HH
