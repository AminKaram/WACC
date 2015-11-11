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
  #include "astnode.hh"
  class ParsingDriver;
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

%token <int>  ASSIGN BANG CHR EQUALS GREATER GREATEREQUALS LEN LESS LESSEQUALS    
%token <int>  LOGAND LOGOR MINUS MODULO NOTEQUALS ORD PLUS SLASH STAR 

%token        LPAREN RPAREN LSQUARE RSQUARE SEMICOLON COMMA 

%token        PRINT PRINTLN READ NEWPAIR FST SND

/* EOF token */
%token        ENDF 0

%token <std::string> IDENTIFIER STRINGLIT

%token <char> CHARLIT

%token <int> INTEGER


%type <Type>                  type base_type array_type pair_type pair_elem_type
%type <Identifier>            ident
%type <StatSeq>  		          statement_seq statement_seq_ret	
%type <Statement *>  		      statement  return_stat
%type <AssignLhs>             assign_lhs array_elem_lhs pair_elem_lhs
%type <AssignRhs>             assign_rhs array_liter pair_elem_rhs 
%type <Expression *> 			    expr int_liter bool_liter char_liter str_liter
%type <Expression *>          pair_liter array_elem_exp unary_op binary_op
%type <ExpressionList>        arg_list expr_list array_index
%type <VariableList>          param_list
%type <VariableDeclaration *> param
%type <int>	     			        int_sign
%type <FunctionDeclaration *> function_declaration
%type <FunctionDecList>       func_list


/* Precedence of operators */
%left LESS GREATER LESSEQUALS GREATEREQUALS NOTEQUALS EQUALS PLUS MINUS STAR 
%left SLASH MODULO LOGOR LOGAND BANG LEN CHR ORD UMINUS UPLUS

/* Start symbol. If omitted will default to first non_terminal symbol */
%start program 

%%
program: 
    BEGIN func_list statement_seq END
		{ driver.ast = new Program($2, $3); }
  ;
func_list:
    /* Empty production as base case*/
  | func_list function_declaration
    { $1.funcs.push_back($2); }
  ;
function_declaration:
		type ident LPAREN RPAREN IS statement_seq_ret END
		{ $$ = new FunctionDeclaration($1, $2, $6); }
	| type ident LPAREN param_list RPAREN IS statement_seq_ret END
		{ $$ = new FunctionDeclaration($1, $2, &$4, $7); }
    ;
param_list:
    param
		{ $$.push_back($1); }
  | param_list COMMA param
		{ $1.push_back($3); }
    ;
param:
		type ident
		{ $$ = new VariableDeclaration($1, $2); }
    ;
statement_seq:
		statement
		{ $$.statements.push_back($1); }
	| statement_seq SEMICOLON statement
		{ $1.statements.push_back($3); }
    ;

statement_seq_ret:
		return_stat
		{ $$.statements.push_back($1); }
	| statement_seq SEMICOLON statement
		{ $1.statements.push_back($3); }
    ;

statement:
    SKIP
		{ $$ = new SkipStatement(); }
  | type ident ASSIGN assign_rhs
		{ $$ = new VariableDeclaration($1, $2, &$4); }
  | return_stat
    { $$ = $1; }
  | assign_lhs ASSIGN assign_rhs
		{ $$ = new Assignment($1, $3); }
  | READ assign_lhs
		{ $$ = new ReadStatement($2); }
  | FREE expr
		{ $$ = new FreeStatement(*$2); }
  | EXIT expr
		{ $$ = new ExitStatement(*$2); }
  | PRINT expr
		{ $$ = new PrintStatement(*$2); }
  | PRINTLN expr
		{ $$ = new PrintlnStatement(*$2); }
	| BEGIN statement_seq END
		{ $$ = new BeginStatement($2); }
  | IF expr THEN statement_seq ELSE statement_seq FI
		{ $$ = new IfStatement(*$2, $4, &$6);  }
  | WHILE expr DO statement_seq DONE
		{ $$ = new WhileStatement(*$2, $4); }
  ;

return_stat:
    RETURN expr
    { $$ = new ReturnStatement(*$2); }

assign_lhs:
		ident
		{ AssignLhs tmp = $1;
      $$ = tmp; } 
  | array_elem_lhs
		{ $$ = $1; } 
	| pair_elem_lhs
		{ $$ = $1; } 
    ;
assign_rhs:
    expr
		{ AssignRhs tmp = *$1;
      $$ = tmp; } 
  | array_liter
		{ $$ = $1; } 
  | NEWPAIR LPAREN expr COMMA expr RPAREN
		{ NewPair tmp(*$3, *$5); 
      $$ = tmp;} 
  | pair_elem_rhs
		{ $$ = $1; } 
	| CALL ident LPAREN RPAREN
		{ FunctionCall tmp($2); 
      $$ = tmp;}
  | CALL ident LPAREN arg_list RPAREN
		{ FunctionCall tmp($2, $4);
      $$ = tmp;}
    ;
arg_list:
    expr
		{ $$.push_back($1); } 
  | arg_list COMMA expr 
		{ $1.push_back($3); }
    ;
pair_elem_rhs:
    FST expr
		{ PairElem tmp(true, *$2);
      $$ = tmp; }
  | SND expr
		{ PairElem tmp(false, *$2);
      $$ = tmp; }
    ;
pair_elem_lhs:
    FST expr
		{ PairElem tmp(true, *$2);
      $$ = tmp; }
  | SND expr
		{ PairElem tmp(false, *$2);
      $$ = tmp; }
    ;
type:
    base_type
		{ $$ = $1; }
  | array_type
		{ $$ = $1; }
  | pair_type
		{ $$ = $1; }
    ;
base_type:
    INT
		{ IntegerType tmp;
      $$ = tmp; }
  | BOOL
		{ BoolType tmp;
      $$ = tmp; }
  | CHAR
		{ CharType tmp;
      $$ = tmp; }
  | STRING
		{ StringType tmp;
      $$ = tmp; }
    ;
array_type:
  type LSQUARE RSQUARE
	{ ArrayType tmp($1); 
    $$ = tmp;}
    ;
pair_type:
  PAIR LPAREN pair_elem_type COMMA pair_elem_type RPAREN
	{ PairType tmp($3, $5);
    $$ = tmp; }
    ;
pair_elem_type:
    base_type
		{ $$ = $1; }
  | array_type
		{ $$ = $1; }
  | PAIR
	  { PairKeyword tmp;
      $$ = tmp; }
    ;
/* shift/reduce conflict at the ident and array_elem_exp, but handled by default
shifting */
expr:
    int_liter
		{ $$ = $1; }
  | bool_liter
		{ $$ = $1; }
  | char_liter 
		{ $$ = $1; }
  | str_liter
		{ $$ = $1; }
  | pair_liter
		{ $$ = $1; }
  | ident
		{ $$ = &$1; }
  | array_elem_exp
		{ $$ = $1; }
  | unary_op
		{ $$ = $1; }
  | binary_op
		{ $$ = $1; }
  | LPAREN expr RPAREN
	 	{ $$ = $2; }
  ;

unary_op:
    BANG expr
		{ $$ = new UnaryOperator($1, *$2); }
  | LEN expr
		{ $$ = new UnaryOperator($1, *$2); }
  | ORD expr
		{ $$ = new UnaryOperator($1, *$2); }
  | CHR expr
		{ $$ = new UnaryOperator($1, *$2); }
  | MINUS expr %prec UMINUS
    { $$ = new UnaryOperator($1, *$2); }
    ;
binary_op:
    expr STAR expr
    { $$ = new BinaryOperator(*$1, $2, *$3); } 
  | expr SLASH expr
    { $$ = new BinaryOperator(*$1, $2, *$3); } 
  | expr MODULO expr
    { $$ = new BinaryOperator(*$1, $2, *$3); } 
  | expr PLUS expr 
    { $$ = new BinaryOperator(*$1, $2, *$3); } 
  | expr MINUS expr
    { $$ = new BinaryOperator(*$1, $2, *$3); } 
  | expr GREATER expr
    { $$ = new BinaryOperator(*$1, $2, *$3); } 
  | expr GREATEREQUALS expr
    { $$ = new BinaryOperator(*$1, $2, *$3); } 
  | expr LESS expr
    { $$ = new BinaryOperator(*$1, $2, *$3); } 
  | expr LESSEQUALS expr
    { $$ = new BinaryOperator(*$1, $2, *$3); } 
  | expr EQUALS expr
    { $$ = new BinaryOperator(*$1, $2, *$3); } 
  | expr NOTEQUALS expr
    { $$ = new BinaryOperator(*$1, $2, *$3); } 
  | expr LOGAND expr
    { $$ = new BinaryOperator(*$1, $2, *$3); } 
  | expr LOGOR expr
    { $$ = new BinaryOperator(*$1, $2, *$3); } 
    ;
ident:
    IDENTIFIER
		{ Identifier tmp($1);
      $$ = tmp; } 
    ;
array_elem_exp:
    ident array_index
		{ $$ = new ArrayElem($1, $2); }
    ;
array_elem_lhs:
    ident array_index
		{ ArrayElem tmp($1, $2);
      $$ = tmp; }
    ;
array_index:
		LSQUARE expr RSQUARE
    { $$.push_back($2); }
	| array_index LSQUARE expr RSQUARE
		{ $1.push_back($3); }
    ;
int_liter:
		int_sign INTEGER
		 { $$ = new Number($1 * $2); }
    ;
int_sign:
		/* empty */
		{ $$ = 1; }
	|	PLUS %prec UPLUS
		{ $$ = 1; }
    ;
bool_liter:
		TRUE		
		{ $$ = new Boolean(true); }
	| FALSE
		{ $$ = new Boolean(false); }
    ;
char_liter:
		CHARLIT
		{ $$ = new Char($1);}
    ;
str_liter:
		STRINGLIT
		{ $$ = new String($1); }
    ;
array_liter:
	LSQUARE expr_list RSQUARE
	{ ArrayLiter tmp($2);
    $$ = tmp; }
    ;
expr_list:
    /* Empty rule for empty list */  
  |	expr
		{ $$.push_back($1); }
	| expr_list COMMA expr
		{ $1.push_back($3); }
    ;
pair_liter:
		NULLTOKEN 
		{ $$ = new Null(); }
    ;

%%

void yy::parser::error (const location_type& l, const std::string& m) {
  driver.error(l, m);
  exit(100);
}
