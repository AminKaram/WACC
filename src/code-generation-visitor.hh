#ifndef CODE_GENERATION_VISITOR_HH
#define CODE_GENERATION_VISITOR_HH
#include "astnode.hh"
#include <sstream>
#include <cstring>
#include <map>

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
  void printAssemblyOfReadInt();
  void printAssemblyOfReadChar();
  void printMsgRead(TypeId *type);
  void printStatementForRead(TypeId *type);
  void visit(ReadStatement *node);
  void printMsgPrint(TypeId *type);
  void printlnMsg();
  void printAssemblyOfPrintString();
  void printAssemblyOfPrintBool();
  void printAssemblyOfPrintInt();
  void printStatement(TypeId *type);
  void visit(PrintStatement *node);
  void printAssemblyOfPrintln();
  void visit(PrintlnStatement *node);
  void visit(SkipStatement *node);
  void visit(Number *node, std::string reg);
  void visit(Boolean *node, std::string reg);
  void visit(Char *node, std::string reg);
  void visit(String *node, std::string reg);
  void visit(Null *node, std::string reg);
  void visit(BinaryOperator *node, std::string reg);
  void visit(Identifier *node, std::string reg);
  void visit(Identifier *node);
  void visit(ArrayElem *node, std::string reg);
  void visit(ArrayElem *node);
  void visit(PairElem *node, std::string reg);
  void visit(PairElem *node);
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
  
  bool p_print_string = false;
  bool p_print_bool   = false;
  bool p_print_int    = false;
  bool p_print_ln     = false;

  bool p_read_char = false;
  bool p_read_int  = false;
  
  bool beginInitialisation = false;
  
  int stringMessageNum  = -1;
  int boolMessageNum    = -1;
  int newlineMessageNum = -1;
  int intMessageNum     = -1;
  int charMessageNum    = -1;
  
  bool msgInt     = false;
  bool msgString  = false;
  bool msgBool    = false;
  bool msgChar    = false;
  bool msgNewLine = false;

  bool p_throw_overflow_errorb = false;
  bool p_throw_runtime_errorb  = false;
  bool p_check_divide_by_zerob = false;
  
  void p_throw_runtime_error(void);
  void p_throw_overflow_error(void);
  void p_check_divide_by_zero(void);
  int scopeSize = 0;
  std::map <std::string, int> *varMap;
};


#endif // ! CODE_GENERATION_VISITOR_HH
