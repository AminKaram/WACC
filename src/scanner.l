%{
  /* C++ sting header */
  #include <string>
  /* Implementation of yyFlexScanner */
  #include "mc_scanner.hpp"

  /* Typedef to make return types for the tokens shorter */
  typedef MC::MC_Parser::token token;

  /* Helpful Macro */
  #define STOKEN(x) ( new std::string(x) )

  /* Define yyterminate like this instead of NULL */
  #define yyterminate() return( token::END )
%}

%option noyywrap 
%option debug
%option nodefault
%option yyclass="MC_Scanner"
%option c++

digit         [0-9]
number        {digit}+
letter        [a-zA-Z]
identifier    [a-zA-Z|_]{1}[a-zA-Z|0-9|_]*
whitespace    [ \t\n]+
comment       #[^\n]*
charlit       \'[^\'"]{1}|\0|\b|\n|\r|\"|\'|\\\'
stringlit     \"(\\.|[^\\"])*\"

%% 
begin         return (token::BEGIN);
end           return (token::END);
if            return (token::IF); 
then          return (token::THEN); 
else          return (token::ELSE); 
fi            return (token::FI); 
while         return (token::WHILE); 
do            return (token::DO); 
done          return (token::DONE); 
skip          return (token::SKIP); 
free          return (token::FREE); 
exit          return (token::EXIT); 
is            return (token::IS);
return        return (token::RETURN); 
call          return (token::CALL); 
pair          return (token::PAIR); 
int           return (token::INT); 
bool          return (token::BOOL); 
char          return (token::CHAR); 
string        return (token::STRING); 
null          return (token::NULLTOKEN);
print         return (token::PRINT); 
println       return (token::PRINTLN); 
read          return (token::READ); 
newpair       return (token::NEWPAIR); 
fst           return (token::FST); 
snd           return (token::SND); 
len           return (token::LEN); 
ord           return (token::ORD); 
chr           return (token::CHR); 
true		      return (token::TRUE);
false 		    return (token::FALSE);
"<="          return (token::LESSEQUALS);
"<"           return (token::LESS);
">="          return (token::GREATEREQUALS);
">"           return (token::GREATER);
"=="          return (token::EQUALS);
"!="          return (token::NOTEQUALS);
"="           return (token::ASSIGN);
"!"           return (token::BANG);
"+"           return (token::PLUS); 
"-"           return (token::MINUS); 
"*"           return (token::STAR); 
"/"           return (token::SLASH); 
"%"           return (token::MODULO);
"&&"          return (token::LOGAND);
"||"          return (token::LOGOR);
"("           return (token::LPAREN); 
")"           return (token::RPAREN); 
";"           return (token::SEMICOLON); 
","           return (token::COMMA); 
"["           return (token::LSQUARE);
"]"           return (token::RSQUARE);

{number}      yylval->iVal = std::stoi(yytext);  return (token::INTEGER); 
{identifier}  yylval->sVal = STOKEN(yytext);     return (token::IDENTIFIER); 
{whitespace} 
{stringlit}   yylval->sVal = SToken(yytext);     return (token::STRINGLIT); 
{comment}     { } 
{charlit}     yylval->cVal = yytext[0];          return (token::CHARLIT);  
.             return ERROR; 

%%  
