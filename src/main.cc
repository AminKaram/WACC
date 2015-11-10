#include <iostream>
#include "parsing-driver.hh"

int main(int argc, char **argv) {
  int res = 0;
  ParsingDriver driver;
  if(driver.parse(argv[1]))
      res = 200;
  return res;
}

