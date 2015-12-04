#include "code-generation-visitor.hh"

CodeGenVisitor::CodeGenVisitor(std::ostream* stream) {
  output = stream;
}
CodeGenVisitor::~CodeGenVisitor() { }

void CodeGenVisitor::visit(ASTnode *node) {
}

void CodeGenVisitor::visit(Program *node) {
  node->functions->accept(this);
  node->statements->accept(this);
}

void CodeGenVisitor::visit(AssignRhs *node) {}
void CodeGenVisitor::visit(AssignLhs *node) {}
void CodeGenVisitor::visit(Expression *node) {}
void CodeGenVisitor::visit(StatSeq *node) {}
void CodeGenVisitor::visit(FunctionDecList *node) {}
void CodeGenVisitor::visit(IntegerType *node) {}
void CodeGenVisitor::visit(BoolType *node) {}
void CodeGenVisitor::visit(CharType *node) {}
void CodeGenVisitor::visit(StringType *node) {}
void CodeGenVisitor::visit(ArrayType *node) {}
void CodeGenVisitor::visit(PairType *node) {}
void CodeGenVisitor::visit(VariableDeclaration *node) {}
void CodeGenVisitor::visit(FunctionDeclaration *node) {}
void CodeGenVisitor::visit(FunctionCall *node) {}
void CodeGenVisitor::visit(Assignment *node) {}
void CodeGenVisitor::visit(FreeStatement *node) {}
void CodeGenVisitor::visit(ReturnStatement *node) {}
void CodeGenVisitor::visit(ExitStatement *node) {std::cout<< "e" <<std::endl;}
void CodeGenVisitor::visit(BeginStatement *node) {}
void CodeGenVisitor::visit(IfStatement *node) {}
void CodeGenVisitor::visit(WhileStatement *node) {}
void CodeGenVisitor::visit(ReadStatement *node) {}
void CodeGenVisitor::visit(PrintStatement *node) {}
void CodeGenVisitor::visit(PrintlnStatement *node) {}
void CodeGenVisitor::visit(Number *node) {}
void CodeGenVisitor::visit(Boolean *node) {}
void CodeGenVisitor::visit(Char *node) {}
void CodeGenVisitor::visit(String *node) {}
void CodeGenVisitor::visit(Null *node) {}
void CodeGenVisitor::visit(BinaryOperator *node) {}
void CodeGenVisitor::visit(Identifier *node) {}
void CodeGenVisitor::visit(ArrayElem *node) {}
void CodeGenVisitor::visit(PairElem *node) {}
void CodeGenVisitor::visit(ArrayLiter *node) {}
void CodeGenVisitor::visit(NewPair *node) {}
void CodeGenVisitor::visit(UnaryOperator *node) {}

void CodeGenVisitor::defineLabel(String label) {}
