#include <iostream>
#include <fstream>
#include "front-end.hh"
#include "back-end.hh"
#include "preprocessor.hh"
#include <string>
#include <stdio.h>

int main(int argc, char **argv) {
  std::string argAsString (argv[1]);
  std::string substr = argAsString.substr(argAsString.find_last_of("/"));
  Preprocessor *prepro = new Preprocessor(argAsString);
  prepro->import();
  delete prepro;
  int res = 0;
  FrontEnd *frontEnd = new FrontEnd();
  std::string generated(substr);
  generated.erase(0,1);
  generated.append("r");
  res = frontEnd->run(generated);
  if(res != 0) {
    remove(generated.c_str());
    return res;
  }
  remove(generated.c_str());

  std::ofstream assemblyOutput;
  std::string temp = "..";
  std::string file = temp.append(substr.substr(0, substr.find(".wacc")).append(".s"));
  assemblyOutput.open(file);

  BackEnd* backEnd = new BackEnd(&assemblyOutput);
  backEnd->generateCode(frontEnd->getProgram());
  assemblyOutput.close();
  delete frontEnd;
  delete backEnd;
  return res;
}

