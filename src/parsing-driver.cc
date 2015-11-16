#include "parsing-driver.hh"
#include "parser.hh"

ParsingDriver::ParsingDriver() : trace_scanning(false), 
                                   trace_parsing(false) 
{ }

ParsingDriver::~ParsingDriver() { 
  delete ast;
  ast = NULL;
}

int ParsingDriver::parse(const std::string &f) {
  file = f;
  scan_begin();
  yy::parser parser(*this);
  parser.set_debug_level(trace_parsing);
  parser.parse();
  scan_end();
  return errorTrace; 
}

void ParsingDriver::error(const yy::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
  errorTrace = 1;
}

void ParsingDriver::error(const std::string& m)
{
  std::cerr << m << std::endl;
  errorTrace = 1;
}
