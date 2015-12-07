#ifndef CODE_GENERATION_VISITOR_HH
#define CODE_GENERATION_VISITOR_HH
#include "astnode.hh"
#include <sstream>
#include <cstring>

class CodeGenVisitor {
public:
  const int MAX_REG_NUMBER = 16;
  CodeGenVisitor(std::ostream *stream);
  ~CodeGenVisitor();

  //void visit(ASTnode *node);
  void visit(Program *node);
 // void visit(AssignRhs *node);
 // void visit(AssignLhs *node);
 // void visit(Expression *node);
  void visit(StatSeq *node);
  void visit(FunctionDecList *node);
  void visit(VariableDeclaration *node);
  void visit(FunctionDeclaration *node);
  void visit(FunctionCall *node, std::string reg);
  void visit(Assignment *node);
  void visit(FreeStatement *node);
  void visit(ReturnStatement *node);
  void visit(ExitStatement *node);
  void visit(BeginStatement *node);
  void visit(IfStatement *node);
  void visit(WhileStatement *node);
  void visit(ReadStatement *node);
  void print(std::string stringToPrint);
  void printMsg(TypeId *type);
  void printlnMsg();
  void visit(PrintStatement *node);
  void visit(PrintlnStatement *node);
  void visit(SkipStatement *node);
  void visit(Number *node, std::string reg);
  void visit(Boolean *node, std::string reg);
  void visit(Char *node, std::string reg);
  void visit(String *node, std::string reg);
  void visit(Null *node, std::string reg);
  void visit(BinaryOperator *node, std::string reg);
  void visit(Identifier *node, std::string reg);
  void visit(ArrayElem *node, std::string reg);
  void visit(PairElem *node, std::string reg);
  void visit(ArrayLiter *node, std::string reg);
  void visit(NewPair *node, std::string reg);
  void visit(UnaryOperator *node, std::string reg);

  void populateRegMap();
  std::string getAvailableRegister();
  void freeRegister(std::string reg);
  

private:
  std::ostream *file;
  std::stringstream begin;
  std::stringstream middle;
  std::stringstream end;
  std::map<std::string, bool> *regTable;
  int labelNum   = 0;
  int messageNum = 0;
  int actualPrintMessageNum = 0;
  bool p_throw_overflow_errorb = false;
  bool p_throw_runtime_errorb  = false;
  bool p_check_divide_by_zerob = false;
  void p_throw_runtime_error(void);
  void p_throw_overflow_error(void);
  void p_check_divide_by_zero(void);
};


#endif // ! CODE_GENERATION_VISITOR_HH
