#include <iostream>
#include "parsing-driver.hh"

int main(int argc, char **argv) {
 // std::cout << " ! " << std::endl;
  int res = 0;
 // std::cout << " ! " << std::endl;
  ParsingDriver *driver = new ParsingDriver();
 // std::cout << " ! " << std::endl;
  if(driver->parse(argv[1])) {
   // std::cout << "Parse failed" << std::endl;
	 res = 200;
  }
  delete driver;
  return res;
}

