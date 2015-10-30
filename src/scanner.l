%{
  #include <iostream>
  #include <fstream>
  using namespace std;
  #include "astnode.h"
  int error_count = 0;
  //#include "parser.hpp"

%}

/* bison compatibility directive */
%option noyywrap 

digit         [0-9]
number        {digit}+
letter        [a-zA-Z]
identifier    [a-zA-Z|_]{1}[a-zA-Z|0-9|_]*
whitespace    [ \t\n]+
comment       #[^\n]*
charlit       \'[^\'"]{1}|\0|\b|\n|\r|\"|\'|\\\'
stringlit     \"(\\.|[^\\"])*\"

%% 
begin        {cout <<" BEGIN     "<<endl;} // return BEGIN;
end          {cout <<" END       "<<endl;} // return END; 
if           {cout <<" IF        "<<endl;} // return IF; 
then         {cout <<" THEN      "<<endl;} // return THEN; 
else         {cout <<" ELSE      "<<endl;} // return ELSE; 
fi           {cout <<" FI        "<<endl;} // return FI; 
while        {cout <<" WHILE     "<<endl;} // return WHILE; 
do           {cout <<" DO        "<<endl;} // return DO; 
done         {cout <<" DONE      "<<endl;} // return DONE; 
read         {cout <<" READ      "<<endl;} // return READ; 
print        {cout <<" PRINT     "<<endl;} // return PRINT; 
println      {cout <<" PRINTLN   "<<endl;} // return PRINTLN; 
skip         {cout <<" SKIP      "<<endl;} // return SKIP; 
free         {cout <<" FREE      "<<endl;} // return FREE; 
return       {cout <<" RETURN    "<<endl;} // return RETURN; 
exit         {cout <<" EXIT      "<<endl;} // return EXIT; 
newpair      {cout <<" PRINT     "<<endl;} // return PRINT; 
call         {cout <<" CALL      "<<endl;} // return CALL; 
fst          {cout <<" FST       "<<endl;} // return FST; 
snd          {cout <<" SND       "<<endl;} // return SND; 
int          {cout <<" INT       "<<endl;} // return INT; 
bool         {cout <<" BOOL      "<<endl;} // return BOOL; 
char         {cout <<" CHAR      "<<endl;} // return CHAR; 
string       {cout <<" STRING    "<<endl;} // return STRING; 
pair         {cout <<" PAIR      "<<endl;} // return PAIR; 
len          {cout <<" LEN       "<<endl;} // return LEN; 
ord          {cout <<" ORD       "<<endl;} // return ORD; 
chr          {cout <<" CHR       "<<endl;} // return CHR; 
is           {cout <<" IS        "<<endl;} // return IS;
null         {cout <<" NULL      "<<endl;} // return NULL;
"="          {cout <<" EQUAL     "<<endl;} // return EQUAL;
"<"          {cout <<" LESS      "<<endl;} // return LESS; 
">"          {cout <<" GREATER   "<<endl;} // return GREATER;
"!"          {cout <<" BANG      "<<endl;} // return BANG;
"+"          {cout <<" PLUS      "<<endl;} // return PLUS; 
"-"          {cout <<" MINUS     "<<endl;} // return MINUS; 
"*"          {cout <<" STAR      "<<endl;} // return STAR; 
"/"          {cout <<" SLASH     "<<endl;} // return SLASH; 
"%"          {cout <<" MODULO    "<<endl;} // return MODULO;
"("          {cout <<" LPAREN    "<<endl;} // return LPAREN; 
")"          {cout <<" RPAREN    "<<endl;} // return RPAREN; 
";"          {cout <<" SEMICOLON "<<endl;} // return SEMICOLON; 
","          {cout <<" COMMA     "<<endl;} // return COMMA; 
"["          {cout <<" LSQUARE   "<<endl;} //return LSQUARE;
"]"          {cout <<" RSQUARE   "<<endl;} //return RSQUARE;
"&&"         {cout <<" LOGAND    "<<endl;} //return LOGAND;
"||"         {cout <<" LOGOR     "<<endl;} //return LOGOR;

{number}      {cout <<" INTEGER "    << endl;} //yylval.string = new std::string(yytext,yyleng); return INTEGER;; 
{identifier}  {cout <<" IDENT "      << endl;} //yylval.string = new std::string(yytext,yyleng); return IDENTIFIER; 
{whitespace}  { }
{stringlit}   {cout <<" STRINGLIT " << yytext << endl;} //yylval.string = new std::string(yytext,yyleng); return STRINGLIT; 
{comment}     { } 
{charlit}     {cout <<" CHARLIT   " << yytext << endl;} 
.             {cout <<"ERROR      " << yytext << endl; error_count ++; exit(0);} //return ERROR; 

%%  
int main(int argc, char** argv) {

    ++argv; --argc;
	
    if(argc > 0) {
	    // open a file handle to a particular file
	    FILE *myfile = fopen(*argv, "r");
	    // make sure it's valid:
	    if (!myfile) {
		    cout << "I can't open the file." << argv << endl;
		    return -1;
	    }
	    // set lex to read from it instead of defaulting to STDIN:
	    yyin = myfile;
    }
	
	// lex through the input:
	yylex();
    cout << "# errors" << error_count << endl;
}

