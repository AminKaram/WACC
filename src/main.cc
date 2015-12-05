#include <iostream>
#include <fstream>
#include "front-end.hh"
#include "back-end.hh"
#include <string>

int main(int argc, char **argv) {
  int res = 0;
  FrontEnd *frontEnd = new FrontEnd();
  res = frontEnd->run(argv[1]);

  std::ofstream assemblyOutput;
  std::string argAsString (argv[1]);
  std::string substr = argAsString.substr(argAsString.find_last_of("/") + 1);
  assemblyOutput.open(substr.substr(0, substr.find(".wacc")).append(".s"));

  BackEnd* backEnd = new BackEnd(&assemblyOutput);
  backEnd->generateCode(frontEnd->getProgram());
  delete frontEnd;
  assemblyOutput.close();
  delete backEnd;
  return res;
}

