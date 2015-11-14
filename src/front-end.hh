#ifndef FRONT_END_HH
#define FRONT_END_HH

class FrontEnd{
public:
  int check(Program*);
  int run(char*);

private:
  ParsingDriver *driver;
  AstNodeVisitor *semanticAnalyzer;
}

#endif // ! FRONT_END_HH
