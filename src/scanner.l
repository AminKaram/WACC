%{
  #include <iostream>
  #include <fstream>
  # include "parser.hpp"
  # include "astnode.h"
  using namespace std;
  int error_count = 0;

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
begin         return BEGIN;
end           return END;
if            return IF; 
then          return THEN; 
else          return ELSE; 
fi            return FI; 
while         return WHILE; 
do            return DO; 
done          return DONE; 
skip          return SKIP; 
free          return FREE; 
exit          return EXIT; 
is            return IS;
return        return RETURN; 
call          return CALL; 
pair          return PAIR; 
int           return INT; 
bool          return BOOL; 
char          return CHAR; 
string        return STRING; 
null          return NULL;
print         return PRINT; 
println       return PRINTLN; 
read          return READ; 
newpair       return NEWPAIR; 
fst           return FST; 
snd           return SND; 
len           return LEN; 
ord           return ORD; 
chr           return CHR; 
true		  return TRUE;
false 		  return FALSE;
"<="          return LESSEQUALS;
"<"           return LESS;
">="          return GREATEREQUALS;
">"           return GRATER
"=="          return EQUALS;
"!="          return NOTEQUALS;
"="           return ASSIGN;
"!"           return BANG;
"+"           return PLUS; 
"-"           return MINUS; 
"*"           return STAR; 
"/"           return SLASH; 
"%"           return MODULO;
"&&"          return LOGAND;
"||"          return LOGOR;
"("           return LPAREN; 
")"           return RPAREN; 
";"           return SEMICOLON; 
","           return COMMA; 
"["           return LSQUARE;
"]"           return RSQUARE;

{number}      yylval.intValue = atoi(yytext);                 return INTEGER; 
{identifier}  yylval.string = new std::string(yytext,yyleng); return IDENTIFIER; 
{whitespace} 
{stringlit}   yylval.string = new std::string(yytext,yyleng); return STRINGLIT; 
{comment}     { } 
{charlit}     yylval.charValue = yytext[0];                   return CHARLIT;  
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

