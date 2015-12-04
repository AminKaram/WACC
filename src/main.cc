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
  std::string substr = argAsString.substr(0, argAsString.find(".wacc"));
  assemblyOutput.open(substr.append(".s"));

  BackEnd* backEnd = new BackEnd(&assemblyOutput);
  backEnd->generateCode(frontEnd->getProgram());
  delete frontEnd;
  assemblyOutput.close();
  delete backEnd;
  return res;
}

