#ifndef PREPROCESSOR_HH
#define PREPROCESSOR_HH

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class Preprocessor {
public:
  Preprocessor(std::string filename);
  ~Preprocessor();
  void import();
private:
  std::ifstream infile;
  std::ofstream outfile;
  std::stringstream importFuncs;
  std::string dir;
  std::vector<std::string> imports;
  void getImports();
  void importFile(std::string filename);
};

#endif // ! PREPROCESSOR_HH
