#ifndef __MCDRIVER_HPP__
#define __MCDRIVER_HPP__ 1

#include <string>
#include "mc_scanner.hpp"
#include "mc_parser.tab.hh"

namespace MC{

class MC_Driver{
public:
   MC_Driver() : {};

   virtual ~MC_Driver();

   void parse( const char *filename );
  

   void add_upper();
   void add_lower();
   void add_word( const std::string &word );
   void add_newline();
   void add_char();

   std::ostream& print(std::ostream &stream);
private:
};

} /* end namespace MC */
#endif /* END __MCDRIVER_HPP__ */
