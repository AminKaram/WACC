#include "parsing-driver.hh"
#include "parser.hh"

parsingDriver::frontEndDriver() : trace_scanning(false), 
                                   trace_parsing(false) 
{ }

parsingDriver::~frontEndDriver() { 
  delete ast;
}

int parsingDriver::parse(const std::string &f) {
  file = f;
  scan_begin();
  yy::parser parser(*this);
  parser.set_debug_level(trace_parsing);
  int res = parser.parse();
  scan_end();
  return res;
}

void parsingDriver::error(const yy:location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}

void parsingDriver::error(const std::string& m)
{
  std::cerr << m << std::endl;
}
