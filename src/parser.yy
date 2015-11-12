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
  bool containsRet(StatSeq*);
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


%type <Type*>                 type base_type array_type pair_type pair_elem_type
%type <Identifier*>           ident
%type <StatSeq*>  		        statement_seq	
%type <Statement *>  		      statement 
%type <AssignLhs*>            assign_lhs array_elem_lhs pair_elem_lhs
%type <AssignRhs*>            assign_rhs array_liter pair_elem_rhs 
%type <Expression *> 			    expr int_liter bool_liter char_liter str_liter
%type <Expression *>          pair_liter array_elem_exp unary_op binary_op
%type <ExpressionList*>       arg_list expr_list array_index
%type <VariableList*>         param_list
%type <VariableDeclaration*>  param
%type <int>	     			        int_sign
%type <FunctionDeclaration*>  function_declaration
%type <FunctionDecList*>      func_list


/* Precedence of operators */
%left LESS GREATER LESSEQUALS GREATEREQUALS NOTEQUALS EQUALS PLUS MINUS STAR 
%left SLASH MODULO LOGOR LOGAND BANG LEN CHR ORD UMINUS UPLUS

/* Start symbol. If omitted will default to first non_terminal symbol */
%start program 

%%
program: 
    BEGIN func_list statement_seq END
		{ std::cout << " PROGRAM " << std::endl;
      std::cout << " HA " << std::endl;
      StatSeq tmp2 = *$3;
      std::cout << " HAHA " << std::endl;
      FunctionDecList tmp1 = *$2;
      std::cout << " HAHA " << std::endl;

      driver.ast = new Program(&tmp1, &tmp2 ); 
      std::cout << " HAHA " << std::endl; }
  ;
func_list:
    /* Empty production as base case*/
    { std::cout << " FUNCTION DEC SEQ BASE" << std::endl;
      $$ = new FunctionDecList(); } 
  | func_list function_declaration
    { std::cout << " FUNCTION DEC SEQ " << std::endl;
      std::swap($$, $1);
      $$->funcs.push_back($2); }
  ;
function_declaration:
		type ident LPAREN RPAREN IS statement_seq END
		{ std::cout << " FUNCTION DEC " << std::endl;
      if(!containsRet($6)) { 
       yy::parser::error(@6, "syntax error: function path missing RETURN"); 
      }
      $$ = new FunctionDeclaration($1, $2, $6); }
	| type ident LPAREN param_list RPAREN IS statement_seq END
    { std::cout << " FUNC DEC " << std::endl; 
      if(!containsRet($7)) {
       yy::parser::error(@6, "syntax error: function path missing RETURN"); 
      }
      $$ = new FunctionDeclaration($1, $2, $4, $7); }
    ;
param_list:
    param
		{ std::cout << "PARAM LIST SEQ BASE " << std::endl;
      $$ = new VariableList();
      $$->push_back($1); }
  | param_list COMMA param
		{ std::cout << " PARAM LIST SEQ " << std::endl;
      std::swap($$, $1);
      $$->push_back($3); }
    ;
param:
		type ident
		{ std::cout << " PARAM " << std::endl;
      $$ = new VariableDeclaration($1, $2); }
    ;
statement_seq:
		statement
   	{ std::cout << " STAT SEQ BASE " << std::endl;
      $$ = new StatSeq();
      $$->statements.push_back($1); } 
	| statement_seq SEMICOLON statement
		 { std::cout << " STAT SEQ " << std::endl;
       std::swap($$, $1);
       $$->statements.push_back($3); }
    ;
statement:
    SKIP
		{ std::cout << " SKIP " << std::endl;
      $$ = new SkipStatement(); }
  | RETURN expr
    { std::cout << " RETURN " << std::endl;
      $$ = new ReturnStatement($2); }
  | type ident ASSIGN assign_rhs
		{ std::cout << " ASSIGN " << std::endl;
      $$ = new VariableDeclaration($1, $2, $4); }
  | assign_lhs ASSIGN assign_rhs
		{ std::cout << " ASSIGN POST DECLARATION " << std::endl; 
      $$ = new Assignment($1, $3); }
  | READ assign_lhs
		{ std::cout << " READ " << std::endl;
      $$ = new ReadStatement($2); }
  | FREE expr
		{ std::cout << " FREE " << std::endl;
      $$ = new FreeStatement($2); }
  | EXIT expr
		{ std::cout << " EXIT " << std::endl;
      $$ = new ExitStatement($2); }
  | PRINT expr
		{ std::cout << " PRINT " << std::endl;
      $$ = new PrintStatement($2); }
  | PRINTLN expr
		{ std::cout << " PRINTLN " << std::endl;
      $$ = new PrintlnStatement($2); }
	| BEGIN statement_seq END
		{ std::cout << " BEGIN " << std::endl;
      $$ = new BeginStatement($2); }
  | IF expr THEN statement_seq ELSE statement_seq FI
		{ std::cout << " IF " << std::endl;
      $$ = new IfStatement($2, $4, $6);  }
  | WHILE expr DO statement_seq DONE
		{ std::cout << " WHILE " << std::endl;
      $$ = new WhileStatement($2, $4); }
  ;
assign_lhs:
		ident
		{ std::cout << " ASSIGN LHS " << std::endl;
      $$ = dynamic_cast<AssignLhs*>($1); } 
  | array_elem_lhs
		{ std::cout << " ASSIGN LHS " << std::endl;
      $$ = $1; } 
	| pair_elem_lhs
		{ std::cout << " ASSIGN LHS " << std::endl;
      $$ = $1; } 
    ;
assign_rhs:
    expr
		{ std::cout << " ASSIGN RHS " << std::endl; 
      $$ = dynamic_cast<AssignRhs*>($1); } 
  | array_liter
		{ std::cout << " ASSIGN RHS " << std::endl; 
      $$ = $1; } 
  | NEWPAIR LPAREN expr COMMA expr RPAREN
		{ std::cout << " ASSIGN RHS " << std::endl; 
      $$ = new NewPair($3, $5); } 
  | pair_elem_rhs
		{ std::cout << " ASSIGN RHS " << std::endl; 
      $$ = $1; } 
	| CALL ident LPAREN RPAREN
		{ std::cout << " ASSIGN RHS " << std::endl; 
      $$ = new FunctionCall($2); }
  | CALL ident LPAREN arg_list RPAREN
		{ std::cout << " ASSIGN RHS " << std::endl; 
      $$ = new FunctionCall($2, $4); }
    ;
arg_list:
    expr
		{ std::cout << " ARG LIST SEQ BASE " << std::cout;
      $$ = new ExpressionList();
      $$->push_back($1);} 
  | arg_list COMMA expr 
		{ std::cout << " ARG LIST SEQ " << std::endl;
      std::swap($$, $1);
      $$->push_back($3); }
    ;
pair_elem_rhs:
    FST expr
		{ std::cout << " PAIR ELEM " << std::endl; 
      $$ = new PairElem(true, $2); }
  | SND expr
		{ std::cout << " PAIR ELEM " << std::endl; 
      $$ = new PairElem(false, $2); }
    ;
pair_elem_lhs:
    FST expr
		{ std::cout << " PAIR ELEM " << std::endl; 
      $$ = new PairElem(true, $2); }
  | SND expr
		{ std::cout << " PAIR ELEM " << std::endl; 
      $$ = new PairElem(false, $2); }
    ;
type:
    base_type
		{ std::cout << " TYPE " << std::endl; 
      $$ = $1; }
  | array_type
		{ std::cout << " TYPE " << std::endl; 
      $$ = $1; }
  | pair_type
		{ std::cout << " TYPE " << std::endl; 
      $$ = $1; }
    ;
base_type:
    INT
		{ std::cout << " INTEGER TYPE " << std::endl;
      $$ = new IntegerType(); }
  | BOOL
		{ std::cout << " BOOL TYPE " << std::endl;
      $$ = new BoolType(); }
  | CHAR
		{ std::cout << " CHAR TYPE " << std::endl;
      $$ = new CharType(); }
  | STRING
		{ std::cout << " STRING TYPE " << std::endl;
      $$ = new StringType(); }
    ;
array_type:
  type LSQUARE RSQUARE
	{ std::cout << " ARRAY TYPE " << std::endl;
    $$ = new ArrayType($1); }
    ;
pair_type:
  PAIR LPAREN pair_elem_type COMMA pair_elem_type RPAREN
	{ std::cout << " PAIR TYPE " << std::endl;
    $$ = new PairType($3, $5); }
    ;
pair_elem_type:
    base_type
		{ std::cout << " PAIR ELEM TYPE " << std::endl; 
      $$ = $1; }
  | array_type
		{ std::cout << " PAIR ELEM TYPE " << std::endl; 
      $$ = $1; }
  | PAIR
		{ std::cout << " PAIR ELEM TYPE " << std::endl; 
       $$ = new PairKeyword(); }
    ;
/* shift/reduce conflict at the ident and array_elem_exp, but handled by default
shifting */
expr:
    int_liter
		{ std::cout << " EXPR " << std::endl; 
      $$ = $1; }
  | bool_liter
		{ std::cout << " EXPR " << std::endl; 
      $$ = $1; }
  | char_liter 
		{ std::cout << " EXPR " << std::endl; 
      $$ = $1; }
  | str_liter
		{ std::cout << " EXPR " << std::endl; 
      $$ = $1; }
  | pair_liter
		{ std::cout << " EXPR " << std::endl; 
      $$ = $1; }
  | ident
		{ std::cout << " EXPR " << std::endl; 
      $$ = $1; }
  | array_elem_exp
		{ std::cout << " EXPR " << std::endl; 
      $$ = $1; }
  | unary_op
		{ std::cout << " EXPR " << std::endl; 
      $$ = $1; }
  | binary_op
		{ std::cout << " EXPR " << std::endl; 
      $$ = $1; }
  | LPAREN expr RPAREN
		{ std::cout << " EXPR " << std::endl; 
      $$ = $2; }
  ;

unary_op:
    BANG expr
		{ std::cout << " BANG UNARY " << std::endl;
      $$ = new UnaryOperator($1, $2); }
  | LEN expr
		{ std::cout << " LEN UNARY " << std::endl;
      $$ = new UnaryOperator($1, $2); }
  | ORD expr
		{ std::cout << " ORD UNARY " << std::endl;
      $$ = new UnaryOperator($1, $2); }
  | CHR expr
		{ std::cout << " CHR ORD " << std::endl;
      $$ = new UnaryOperator($1, $2); }
  | MINUS expr %prec UMINUS
    { std::cout << " MINUS UNARY " << std::endl;
      $$ = new UnaryOperator($1, $2); }
    ;
binary_op:
    expr STAR expr
    { std::cout << " STAR BIN " << std::endl;
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr SLASH expr
    { std::cout << " SLASH BIN " << std::endl;
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr MODULO expr
    { std::cout << " MODULO BIN " << std::endl;
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr PLUS expr 
    { std::cout << " PLUS BIN " << std::endl;
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr MINUS expr
    { std::cout << " MINUS BIN " << std::endl;
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr GREATER expr
    { std::cout << " GREATER BIN " << std::endl;
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr GREATEREQUALS expr
    { std::cout << " GREATEREQUALS BIN " << std::endl;
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr LESS expr
    { std::cout << " LESS BIN " << std::endl; 
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr LESSEQUALS expr
    { std::cout << " LESSEQUALS BIN " << std::endl;
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr EQUALS expr
    { std::cout << " EQUAL BIN " << std::endl;
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr NOTEQUALS expr
    { std::cout << " NOTEQUALS BIN " << std::endl;
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr LOGAND expr
    { std::cout << " LOGAND " << std::endl;
      $$ = new BinaryOperator($1, $2, $3); } 
  | expr LOGOR expr
    { std::cout << " LOGOR " << std::endl;
      $$ = new BinaryOperator($1, $2, $3); } 
    ;
ident:
    IDENTIFIER
		{ std::cout << " IDENT " << std::endl;
      $$ = new Identifier($1); }
    ;
array_elem_exp:
    ident array_index
		{ std::cout << " ARRAY ELEM " << std::endl;
      $$ = new ArrayElem($1, $2); }
    ;
array_elem_lhs:
    ident array_index
		{ std::cout << " ARRAY ELEM " << std::endl;
      $$ = new ArrayElem($1, $2); }
    ;
array_index:
		LSQUARE expr RSQUARE
    { std::cout << " ARRAY INDEX SEQ BASE " << std::endl;
      $$ = new ExpressionList(); 
      $$->push_back($2); }
	| array_index LSQUARE expr RSQUARE
		{ std::cout << " ARRAY INDEX SEQ " << std::endl;
      std::swap($$, $1);
      $$->push_back($3); }
    ;
int_liter:
		int_sign INTEGER
		 { std::cout << " INT LITER " << std::endl;
       $$ = new Number($1 * $2); }
    ;
int_sign:
		/* empty */
		{ $$ = 1; }
	|	PLUS %prec UPLUS
		{ $$ = 1; }
    ;
bool_liter:
		TRUE		
		{ std::cout << " BOOL LITER " << std::endl;
      $$ = new Boolean(true); }
	| FALSE
		{ std::cout << " BOOL LITER " << std::endl;
      $$ = new Boolean(false); }
    ;
char_liter:
		CHARLIT
		{ std::cout << " CHER LITER " << std::endl;
      $$ = new Char($1);}
    ;
str_liter:
		STRINGLIT
		{ std::cout << " STRING LITER " << std::endl;
      $$ = new String($1); }
    ;
array_liter:
	LSQUARE expr_list RSQUARE
	{ std::cout << " ARRAY LITER " << std::endl;
    $$ = new ArrayLiter($2); }
    ;
expr_list:
    /* Empty rule for empty list */
    { std::cout << " EXPR LIST SEQ BASE " << std::endl; }
  | expr
		{ std::cout << " EXPR LIST SEQ BASE " << std::endl;
      $$ = new ExpressionList();
      $$->push_back($1); }
	| expr_list COMMA expr
		{ std::cout << " EXPR LIST SEQ " << std::endl;
      std::swap($$, $1);
      $$->push_back($3); }
    ;
pair_liter:
		NULLTOKEN 
		{ std::cout << " NULL PAIR LITER " << std::endl;
      $$ = new Null(); }
    ;

%%

void yy::parser::error (const location_type& l, const std::string& m) {
  driver.error(l, m);
  exit(100);
}

bool containsRet(StatSeq *seq) {
    //std::cout << " HERE " << std::endl;
    //std::cout << seq->statements.size() << std::endl;
    Statement *stat= seq->statements.back();
    ReturnStatement *retstat;
    IfStatement *ifstat;
    
    retstat = dynamic_cast<ReturnStatement*>(stat);
    ifstat  = dynamic_cast<IfStatement*>(stat);

    if(retstat != NULL) {
      //std::cout << " YH " << std::endl;
      return true;
    } else if(ifstat != NULL) {
      //std::cout << " OK " << std::endl;
      return (containsRet(ifstat->thenS) && containsRet(ifstat->elseS));
    }
    return false;
}

