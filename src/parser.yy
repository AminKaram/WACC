%skeleton "lalr1.cc"
%require "3.0.2"
%defines
%define parser_class_name {parser}

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires{
  #include <iostream>
  #include <string>
  #include <typeinfo>
  #include <vector>
  #include "astnode.hh"
  class ParsingDriver;
  bool containsRetOrExit(StatSeq*);
}

%param { ParsingDriver& driver }

%locations
%initial-action {
  //Initialize the initial location.
  @$.begin.filename = @$.end.filename = &driver.file;
};

%define parse.trace
%define parse.error verbose

%code{
  /* include for all driver functions */
  #include "parsing-driver.hh"
}


%define api.token.prefix {TOK_}

%token        BEGIN END IF THEN ELSE FI WHILE DO DONE SKIP FREE EXIT TRUE FALSE

%token        IS RETURN CALL

%token        PAIR INT BOOL CHAR STRING NULLTOKEN

%token <int>  ASSIGN LOGOR LOGAND STAR SLASH MODULO PLUS MINUS LESS LESSEQUALS 
%token <int>  GREATER GREATEREQUALS EQUALS NOTEQUALS BANG LEN ORD CHR 

%token        LPAREN RPAREN LSQUARE RSQUARE SEMICOLON COMMA 

%token        PRINT PRINTLN READ NEWPAIR FST SND

/* EOF token and other relevant tokens */
%token        ENDF 0

%token        ERROR

%token <std::string> IDENTIFIER STRINGLIT

%token <char> CHARLIT

%token <int> INTEGER


%type <TypeId*>               type base_type array_type pair_type pair_elem_type
%type <Identifier*>           ident
%type <StatSeq*>  		        statement_seq	
%type <Statement *>  		      statement 
%type <AssignLhs*>            assign_lhs array_elem_lhs pair_elem_lhs
%type <AssignRhs*>            assign_rhs array_liter pair_elem_rhs 
%type <Expression *> 			    expr int_liter bool_liter char_liter str_liter
%type <Expression *>          pair_liter array_elem_exp unary_op binary_op
%type <ExpressionList*>       arg_list expr_list array_index
%type <ParamList*>            param_list
%type <Param*>                param
%type <FunctionDeclaration*>  function_declaration
%type <FunctionDecList*>      func_list


/* Precedence of operators */
%left LOGOR LOGAND 
%left LESS GREATER LESSEQUALS GREATEREQUALS NOTEQUALS EQUALS PLUS MINUS 
%left STAR SLASH MODULO BANG LEN CHR ORD UMINUS UPLUS



/* Start symbol. If omitted will default to first non_terminal symbol */
%start program 

%%
program: 
    BEGIN func_list statement_seq END
		{
      driver.ast = new Program($2, $3); 
		 }
  ;
func_list:
    /* Empty production as base case*/
    {
      $$ = new FunctionDecList(); } 
  | func_list function_declaration
    { 
      std::swap($$, $1);
      $$->funcs.push_back($2); }
  ;
function_declaration:
		type ident LPAREN RPAREN IS statement_seq END
		{
      if(!(containsRetOrExit($6))) { 
       yy::parser::error(@6, "syntax error: function path missing RETURN or EXIT"); 
      }
      $$ = new FunctionDeclaration($1, $2, $6); }
	| type ident LPAREN param_list RPAREN IS statement_seq END
    {
      if(!(containsRetOrExit($7))) {
       yy::parser::error(@7, "syntax error: function path missing RETURN or EXIT"); 
      }
      $$ = new FunctionDeclaration($1, $2, $4, $7); }
    ;
param_list:
    param
		{
      $$ = new ParamList();
      $$->push_back($1); }
  | param_list COMMA param
		{
      std::swap($$, $1);
      $$->push_back($3); }
    ;
param:
		type ident
		{
      $$ = new Param($1, $2); }
    ;
statement_seq:
		statement
   	{ 
      $$ = new StatSeq();
      $$->statements.push_back($1); } 
	| statement_seq SEMICOLON statement
		 {
       std::swap($$, $1);
       $$->statements.push_back($3); }
    ;
statement:
    SKIP
		{
      $$ = new SkipStatement(); }
  | RETURN expr
    {
      $$ = new ReturnStatement($2); }
  | type ident ASSIGN assign_rhs
		{
      $$ = new VariableDeclaration($1, $2, $4); }
  | assign_lhs ASSIGN assign_rhs
		{
      $$ = new Assignment($1, $3); }
  | READ assign_lhs
		{
      $$ = new ReadStatement($2); }
  | FREE expr
		{
      $$ = new FreeStatement($2); }
  | EXIT expr
		{
      $$ = new ExitStatement($2); }
  | PRINT expr
		{
      $$ = new PrintStatement($2); }
  | PRINTLN expr
		{
      $$ = new PrintlnStatement($2); }
	| BEGIN statement_seq END
		{
      $$ = new BeginStatement($2); }
  | IF expr THEN statement_seq ELSE statement_seq FI
		{
      $$ = new IfStatement($2, $4, $6);  }
  | WHILE expr DO statement_seq DONE
		{
      $$ = new WhileStatement($2, $4); }
  ;
assign_lhs:
		ident
		{
      $$ = $1; } 
  | array_elem_lhs
		{
      $$ = $1; } 
	| pair_elem_lhs
		{
      $$ = $1; } 
    ;
assign_rhs:
    expr
		{ 
      $$ = $1; } 
  | array_liter
		{ 
      $$ = $1; } 
  | NEWPAIR LPAREN expr COMMA expr RPAREN
		{ 
      $$ = new NewPair($3, $5); } 
  | pair_elem_rhs
		{ 
      $$ = $1; } 
	| CALL ident LPAREN RPAREN
		{ 
      $$ = new FunctionCall($2); }
  | CALL ident LPAREN arg_list RPAREN
		{ 
      $$ = new FunctionCall($2, $4); }
    ;
arg_list:
    expr
		{ 
      $$ = new ExpressionList();
      $$->push_back($1);} 
  | arg_list COMMA expr 
		{ 
      std::swap($$, $1);
      $$->push_back($3); }
    ;
pair_elem_rhs:
    FST expr
		{ 
      $$ = new PairElem(true, $2); }
  | SND expr
		{ 
      $$ = new PairElem(false, $2); }
    ;
pair_elem_lhs:
    FST expr
		{ 
      $$ = new PairElem(true, $2); }
  | SND expr
		{ 
      $$ = new PairElem(false, $2); }
    ;
type:
    base_type
		{ 
      $$ = $1; }
  | array_type
		{ 
      $$ = $1; }
  | pair_type
		{ 
      $$ = $1; }
    ;
base_type:
    INT
		{ 
      $$ = new IntTypeId(); }
  | BOOL
		{ 
      $$ = new BoolTypeId(); }
  | CHAR
		{ 
      $$ = new CharTypeId(); }
  | STRING
		{ 
      $$ = new StringTypeId(); }
    ;
array_type:
  type LSQUARE RSQUARE
	{ 
    $$ = new ArrayId($1); }
    ;
pair_type:
  PAIR LPAREN pair_elem_type COMMA pair_elem_type RPAREN
	{ 
    $$ = new PairId($3, $5); }
    ;
pair_elem_type:
    base_type
		{ 
      $$ = $1; }
  | array_type
		{ 
      $$ = $1; }
  | PAIR
		{ 
       $$ = new PairKeyId(); }
    ;
/* shift/reduce conflict at the ident and array_elem_exp, but handled by default
shifting */
expr:
    int_liter
		{ 
      $$ = $1; }
  | bool_liter
		{ 
      $$ = $1; }
  | char_liter 
		{ 
      $$ = $1; }
  | str_liter
		{ 
      $$ = $1; }
  | pair_liter
		{ 
      $$ = $1; }
  | ident
		{ 
      $$ = $1; }
  | array_elem_exp
		{ 
      $$ = $1; }
  | unary_op
		{ 
      $$ = $1; }
  | binary_op
		{ 
      $$ = $1; }
  | LPAREN expr RPAREN
		{ 
      $$ = $2; }
  ;

unary_op:
    BANG expr
		{ 
      $$ = new UnaryOperator($1, $2); }
  | LEN expr
		{ 
      $$ = new UnaryOperator($1, $2); }
  | ORD expr
		{ 
      $$ = new UnaryOperator($1, $2); }
  | CHR expr
		{ 
      $$ = new UnaryOperator($1, $2); }
  | MINUS expr %prec UMINUS
    { 
      $$ = new UnaryOperator($1, $2); }
    ;
binary_op:
    expr STAR expr
    { 
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr SLASH expr
    { 
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr MODULO expr
    { 
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr PLUS expr 
    { 
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr MINUS expr
    { 
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr GREATER expr
    { 
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr GREATEREQUALS expr
    { 
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr LESS expr
    { 
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr LESSEQUALS expr
    { 
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr EQUALS expr
    { 
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr NOTEQUALS expr
    { 
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr LOGAND expr
    { 
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr LOGOR expr
    { 
      $$ = new BinaryOperator($1, $2, $3); } 
    ;
ident:
    IDENTIFIER
		{ 
      $$ = new Identifier($1); }
    ;
array_elem_exp:
    ident array_index
		{ 
      $$ = new ArrayElem($1, $2); }
    ;
array_elem_lhs:
    ident array_index
		{ 
      $$ = new ArrayElem($1, $2); }
    ;
array_index:
		LSQUARE expr RSQUARE
    { 
      $$ = new ExpressionList(); 
      $$->push_back($2); }
	| array_index LSQUARE expr RSQUARE
		{ 
      std::swap($$, $1);
      $$->push_back($3); }
    ;
int_liter:
	  INTEGER
		 { Number *res  = new Number($1);
       res->type = new IntTypeId();
       $$ = res; }
    ;
bool_liter:
		TRUE		
		{ Boolean *res = new Boolean(true);
      res->type = new BoolTypeId();
      $$ = res; }
	| FALSE
		{ Boolean *res = new Boolean(false);
      res->type = new BoolTypeId();
      $$ = res; }
    ;
char_liter:
		CHARLIT
		{ Char *res = new Char($1);
      res->type = new CharTypeId();
      $$ = res; }
    ;
str_liter:
		STRINGLIT
		{ String *res = new String($1);
      res->type = new StringTypeId();
      $$ =res; }
    ;
array_liter:
	LSQUARE expr_list RSQUARE
	{ $$ = new ArrayLiter($2); }
    ;
expr_list:
    /* Empty rule for empty list */
    { 
		$$ = new ExpressionList();
	  }
  | expr
		{ 
      $$ = new ExpressionList();
      $$->push_back($1); }
	| expr_list COMMA expr
		{ 
      std::swap($$, $1);
      $$->push_back($3); }
    ;
pair_liter:
		NULLTOKEN 
		{ Null *res = new Null(); 
      res->type = new NullId();
      $$ = res; }
    ;
%%

void yy::parser::error (const location_type& l, const std::string& m) {
  driver.error(l, m);
}

bool containsRetOrExit(StatSeq *seq) {
    Statement *stat= seq->statements.back();
    ReturnStatement *retstat;
    IfStatement *ifstat;
    ExitStatement *exitstat;
	   
    exitstat= dynamic_cast<ExitStatement*>(stat);
    retstat = dynamic_cast<ReturnStatement*>(stat);
    ifstat  = dynamic_cast<IfStatement*>(stat);

    if(retstat != NULL || exitstat != NULL) {
      return true;
    } else if(ifstat != NULL) {
      return (containsRetOrExit(ifstat->thenS)
																				 && containsRetOrExit(ifstat->elseS));
    }
    return false;
}
