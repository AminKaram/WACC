#include "preprocessor.hh"
#include <fstream>
#include <string.h>

Preprocessor::Preprocessor(std::string filename) {
  infile.open(filename.c_str());
  std::string sub = filename.substr(filename.find_last_of("/")); 
  dir = filename.erase(filename.find_last_of("/")+1, sub.length()); 
  sub.erase(0,1);
  sub.append("r");
  outfile.open(sub);
}

Preprocessor::~Preprocessor() {
  infile.close();
  outfile.close();
}

void Preprocessor::import() {
  getImports();
  std::string line;
  std::string pre("begin");
  while(std::getline(infile, line)) {
    auto cmp = std::mismatch(pre.begin(), pre.end(), line.begin());
    outfile << line << std::endl;
    if(cmp.first == pre.end()) {
      break;
    }
  }
  for(int i = 0; i < imports.size(); i++) {
    importFile(imports[i]);
  }
  while(std::getline(infile,line)) {
    outfile << line << std::endl;
  }
}

void Preprocessor::getImports() {
  std::string line;
  std::string pre("import");
  while (std::getline(infile, line)) { 
    auto cmp = std::mismatch(pre.begin(), pre.end(), line.begin());
    if(cmp.first == pre.end()) {
      line.erase(0, pre.size()+1);
      imports.push_back(line);
      break;
    }
    outfile << line << std::endl;
  }
}

void Preprocessor::importFile(std::string filename) {
  std::ifstream importing;
  std::string fullName = dir + filename;
  importing.open(fullName);
  if(!importing.is_open()) {
    std::cerr << filename << "does not exist in working directory."
              << std::endl;
    exit(100);
  }
  std::string line;
  while(std::getline(importing, line)) {
    outfile << "  "  << line << std::endl; 
  }
}
