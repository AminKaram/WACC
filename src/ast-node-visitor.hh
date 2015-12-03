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

class SemanticVisitor : public AstNodeVisitor {

public:

  ~SemanticVisitor();
   SemanticVisitor();

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


private:
  SymbolTable *scope = NULL;
  std::map<ASTnode*, TypeId*> *exprTable;
  std::map<std::string,FunctionDeclaration*> *funcLook;
  void addExpression(ASTnode*, TypeId*);
  TypeId* lookUpExpr(ASTnode *node);
  TypeId* typeBuilder(Type*);
};

class CodeGenVisitor : public AstNodeVisitor {
public:
  CodeGenVisitor();
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
};


#endif // ! AST_NODE_VISITOR_HH
