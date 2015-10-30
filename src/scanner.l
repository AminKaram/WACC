%{
  #include <iostream>
  #include <fstream>
  using namespace std;
  #include "astnode.h"
  int error_count = 0;
  #include "parser.hpp"

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
if            return IF; 
then          return THEN; 
else          return ELSE; 
fi            return FI; 
while         return WHILE; 
do            return DO; 
done          return DONE; 
read          return READ; 
print         return PRINT; 
println       return PRINTLN; 
skip          return SKIP; 
free          return FREE; 
return        return RETURN; 
exit          return EXIT; 
newpair       return NEWPAIR; 
call          return CALL; 
fst           return FST; 
snd           return SND; 
int           return INT; 
bool          return BOOL; 
char          return CHAR; 
string        return STRING; 
pair          return PAIR; 
len           return LEN; 
ord           return ORD; 
chr           return CHR; 
is            return IS;
null          return NULL;
"="           return EQUAL;
"<"           return LESS; 
">"           return GREATER;
"!"           return BANG;
"+"           return PLUS; 
"-"           return MINUS; 
"*"           return STAR; 
"/"           return SLASH; 
"%"           return MODULO;
"("           return LPAREN; 
")"           return RPAREN; 
";"           return SEMICOLON; 
","           return COMMA; 
"["           return LSQUARE;
"]"           return RSQUARE;
"&&"          return LOGAND;
"||"          return LOGOR;

{number}      yylval.string = new std::string(yytext,yyleng); return INTEGER;; 
{identifier}  yylval.string = new std::string(yytext,yyleng); return IDENTIFIER; 
{whitespace} 
{stringlit}   yylval.string = new std::string(yytext,yyleng); return STRINGLIT; 
{comment}    
{charlit}     yylval.string = new std::string(yytext,yyleng); return CHARLIT;  
.             return ERROR; 

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

