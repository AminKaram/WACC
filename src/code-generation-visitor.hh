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

  void visit(Program *node);
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
  void printMsg(TypeId *type);
  void printlnMsg();
  void printAssemblyOfPrintReference();
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
  void printAssemblyCheckArrayBounds();
  void printMsgCheckArrayBounds();
  void visit(ArrayElem *node, std::string reg);
  void visit(ArrayElem *node);
  void visit(PairElem *node, std::string reg);
  void visit(PairElem *node);
  void visit(ArrayLiter *node, std::string reg);
  void visit(NewPair *node, std::string reg);
  void visit(UnaryOperator *node, std::string reg);
  int  visit(Param *node, int scope);

  void populateRegMap();
  std::string getAvailableRegister();
  void freeRegister(std::string reg);
  

private:

  std::string allocateStack(int bytes);
  std::string deallocateStack(int bytes);

  std::ostream *file;
  std::stringstream begin;
  std::stringstream middle;
  std::stringstream end;

  std::map<std::string, bool> *regTable;

  int labelNum   = 0;
  int messageNum = 0;

  bool adr = false;
  
  bool p_print_string = false;
  bool p_print_bool   = false;
  bool p_print_int    = false;
  bool p_print_ln     = false;

  bool p_read_char = false;
  bool p_read_int  = false;
  
  bool beginInitialisation = false;
  
  int stringMessageNum          = -1;
  int boolMessageNum            = -1;
  int newlineMessageNum         = -1;
  int intMessageNum             = -1;
  int charMessageNum            = -1;
  int referenceMessageNum       = -1;
  int checkArrayBoundMessageNum = -1;
  int nullMessageNum            = -1;      
  
  bool msgInt             = false;
  bool msgString          = false;
  bool msgBool            = false;
  bool msgChar            = false;
  bool msgNewLine         = false;
  bool msgReference       = false;
  bool msgCheckArrayBound = false;
  bool msgNullPointer     = false;      

  bool p_throw_overflow_errorb = false;
  bool p_throw_runtime_errorb  = false;
  bool p_check_divide_by_zerob = false;
  bool p_check_null_pointerb   = false;

  bool p_print_reference       = false;
  bool p_print_array_elem      = false;

  bool p_free_pairb  = false;
  
  void p_throw_runtime_error(void);
  void p_throw_overflow_error(void);
  void p_check_divide_by_zero(void);
  void p_check_null_pointer(void);

  int scopeSize = 0;

  std::map <std::string, int> *varMap;
  SymbolTable* currentScope;
};


#endif // ! CODE_GENERATION_VISITOR_HH
