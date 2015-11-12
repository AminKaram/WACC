#include "parsing-driver.hh"
#include "parser.hh"

ParsingDriver::ParsingDriver() : trace_scanning(false), 
                                   trace_parsing(false) 
{ }

ParsingDriver::~ParsingDriver() { 
  delete ast;
}

int ParsingDriver::parse(const std::string &f) {
  file = f;
  scan_begin();
  yy::parser parser(*this);
  parser.set_debug_level(trace_parsing);
  int res = parser.parse();
  std::cout << "end of generated code" << std::endl;
  scan_end();
  std::cout << " CLOSED FILE " << std::endl;
  return res;
}

void ParsingDriver::error(const yy::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}

void ParsingDriver::error(const std::string& m)
{
  std::cerr << m << std::endl;
}
