%{
  /* C++ headers*/
  #include <iostream>
  #include <cerrno>
  #include <climits>
  #include <cstdlib>
  #include <string>
  /* Declarations of driver and parser to get the set of defined tokens */
  #include "parsing-driver.hh"
  #include "parser.hh"
  #define tok yy::parser::token::yytokentype

  // Work around an incompatibility in flex (at least versions
  // 2.5.31 through 2.5.33): it generates code that does
  // not conform to C89.  See Debian bug 333231
  // <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
  # undef yywrap
  # define yywrap() 1

  // The location of the current token.
  static yy::location loc;
  bool minus = false;

  /* Typedef to make return types for the tokens shorter */
  typedef yy::parser token;

  /* Define yyterminate like this instead of NULL */
  #define yyterminate() return( token::ENDF )
%}

%option noyywrap nounput batch debug noinput

digit         [0-9]
number        {digit}+
letter        [a-zA-Z]
identifier    [a-zA-Z|_]{1}[a-zA-Z|0-9|_]*
whitespace    [ \t]+
comment       #[^\n]*
charlit       \'[^\\\'\"]\'
escapedchar   \'(\\\\|\\\"|\\r|\\n|\\b|\\0)\'
stringlit     \"(\\.|[^\\"])*\"
import        [import].*.wacc

%{
  // Code run each time a pattern is matched.
  #define YY_USER_ACTION loc.columns(yyleng); 
%}

%%

%{
  // Code run each time yylex is called.
  loc.step();
%}

{whitespace}+     loc.step();
[\n]+             loc.lines(yyleng); loc.step();
{comment}         loc.step();
{import}          loc.step();

begin         return (token::make_BEGIN(loc));
end           return (token::make_END(loc));
if            return (token::make_IF(loc)); 
then          return (token::make_THEN(loc)); 
else          return (token::make_ELSE(loc)); 
fi            return (token::make_FI(loc)); 
while         return (token::make_WHILE(loc)); 
do            return (token::make_DO(loc)); 
done          return (token::make_DONE(loc)); 
skip          return (token::make_SKIP(loc)); 
free          return (token::make_FREE(loc)); 
exit          return (token::make_EXIT(loc)); 
is            return (token::make_IS(loc));
return        return (token::make_RETURN(loc)); 
call          return (token::make_CALL(loc)); 
pair          return (token::make_PAIR(loc)); 
int           return (token::make_INT(loc)); 
bool          return (token::make_BOOL(loc)); 
char          return (token::make_CHAR(loc)); 
string        return (token::make_STRING(loc)); 
null          return (token::make_NULLTOKEN(loc));
print         return (token::make_PRINT(loc)); 
println       return (token::make_PRINTLN(loc)); 
read          return (token::make_READ(loc)); 
newpair       return (token::make_NEWPAIR(loc)); 
fst           return (token::make_FST(loc)); 
snd           return (token::make_SND(loc)); 
len           return (token::make_LEN(tok::TOK_LEN, loc)); 
ord           return (token::make_ORD(tok::TOK_ORD, loc)); 
chr           return (token::make_CHR(tok::TOK_CHR, loc)); 
true		      return (token::make_TRUE(loc));
false 		    return (token::make_FALSE(loc));
"<="          return (token::make_LESSEQUALS(tok::TOK_LESSEQUALS, loc));
"<"           return (token::make_LESS(tok::TOK_LESS, loc));
">="          return (token::make_GREATEREQUALS(tok::TOK_GREATEREQUALS, loc));
">"           return (token::make_GREATER(tok::TOK_GREATER, loc));
"=="          return (token::make_EQUALS(tok::TOK_EQUALS, loc));
"!="          return (token::make_NOTEQUALS(tok::TOK_NOTEQUALS, loc));
"="           return (token::make_ASSIGN(tok::TOK_ASSIGN, loc));
"!"           return (token::make_BANG(tok::TOK_BANG, loc));
"+"           return (token::make_PLUS(tok::TOK_PLUS, loc)); 
"-"           minus = true; return (token::make_MINUS(tok::TOK_MINUS, loc)); 
"*"           return (token::make_STAR(tok::TOK_STAR, loc)); 
"/"           return (token::make_SLASH(tok::TOK_SLASH, loc)); 
"%"           return (token::make_MODULO(tok::TOK_MODULO, loc));
"&&"          return (token::make_LOGAND(tok::TOK_LOGAND, loc));
"||"          return (token::make_LOGOR(tok::TOK_LOGOR, loc));
"("           return (token::make_LPAREN(loc)); 
")"           return (token::make_RPAREN(loc)); 
";"           return (token::make_SEMICOLON(loc)); 
","           return (token::make_COMMA(loc)); 
"["           return (token::make_LSQUARE(loc));
"]"           return (token::make_RSQUARE(loc));

{number}      { 
                errno = 0;
                long val = strtol(yytext, NULL, 10);
                if(!minus && (val > INT_MAX || errno == ERANGE)) {
                  driver.error(loc, "syntax error: integer overflow");
                } else if(minus && (val - 1 > INT_MAX || errno == ERANGE)) {
                  driver.error(loc, "syntax error: integer overflow");
                }
                return token::make_INTEGER(val, loc);
              }

{identifier}  return (token::make_IDENTIFIER(yytext, loc));

{stringlit}   return (token::make_STRINGLIT(yytext, loc));

{charlit}     return (token::make_CHARLIT(yytext[1], loc));  

{escapedchar} return (token::make_CHARLIT(yytext[2], loc));

.             {
                driver.error(loc, "syntax error: invalid character");
              }

<<EOF>>       return token::make_ENDF(loc);

%%  

void ParsingDriver::scan_begin() {
  yy_flex_debug = trace_scanning;
  if(file.empty() || file == "-""")
    yyin = stdin;
  else if (!(yyin = fopen (file.c_str (), "r")))
    {
      error("cannot open " + file + ": " + strerror(errno));
      exit(EXIT_FAILURE);
    }
}

void ParsingDriver::scan_end() {
  fclose(yyin);
}
