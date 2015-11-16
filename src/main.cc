#include <iostream>
#include "front-end.hh"

int main(int argc, char **argv) {
  int res = 0;
  FrontEnd *frontEnd = new FrontEnd();
  res = frontEnd->run(argv[1]);
  delete frontEnd;
  return res;
}

