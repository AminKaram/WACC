#ifndef PARSING_DRIVER_HH
#define PARSING_DRIVER_HH
#include <string>
#include "parser.hh"
// Tells Flex the lexer's prototype ...
#define YY_DECL yy::parser::symbol_type yylex (ParsingDriver& driver)
// ... and declares it for the parser
YY_DECL;

// Does all the scanning and parsing of WACC file
class ParsingDriver {
public:
  ParsingDriver();
  virtual ~ParsingDriver();  

  Program *ast;

  // Handling the scanner
  void scan_begin();
  void scan_end();
  bool trace_scanning;
  
  // Run the parser on a file f
  int parse(const std::string& f);
  std::string file;
  bool trace_parsing;

  //Error handling
  void error(const yy::location& l, const std::string& m);
  void error(const std::string& m);
};

#endif // ! PARSING_DRIVER_HH
