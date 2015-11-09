/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BEGIN = 258,
    END = 259,
    IF = 260,
    THEN = 261,
    ELSE = 262,
    FI = 263,
    WHILE = 264,
    DO = 265,
    DONE = 266,
    SKIP = 267,
    FREE = 268,
    EXIT = 269,
    TRUE = 270,
    FALSE = 271,
    IS = 272,
    RETURN = 273,
    CALL = 274,
    PAIR = 275,
    INT = 276,
    BOOL = 277,
    CHAR = 278,
    STRING = 279,
    NULL = 280,
    ASSIGN = 281,
    LESSEQUALS = 282,
    LESS = 283,
    GREATEREQUALS = 284,
    GREATER = 285,
    EQUALS = 286,
    BANG = 287,
    NOTEQUALS = 288,
    PLUS = 289,
    MINUS = 290,
    STAR = 291,
    SLASH = 292,
    MODULO = 293,
    LOGAND = 294,
    LOGOR = 295,
    LPAREN = 296,
    RPAREN = 297,
    LSQUARE = 298,
    RSQUARE = 299,
    SEMICOLON = 300,
    COMMA = 301,
    ERROR = 302,
    PRINT = 303,
    PRINTLN = 304,
    READ = 305,
    NEWPAIR = 306,
    FST = 307,
    SND = 308,
    LEN = 309,
    ORD = 310,
    CHR = 311,
    IDENTIFIER = 312,
    STRINGLIT = 313,
    CHARLIT = 314,
    INTEGER = 315
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 23 "parser.y" /* yacc.c:1909  */

  int                     token;
  std::string         	  *string;
	int 									  intValue;
	char									  charValue;
  Program                 program;
  Identifier 		 		      id;
  Type                    type;
  Statement 		 		      statement;
  AssignLhs               assignlhs;
  AssignRhs               assignrhs;
  Expression     		      expression;
  ExpressionList 		     	exprlist;
  VariableList            varlist;
  VariableDeclaration     vardec;
  FunctionDeclaration     fundec;
  FunctionList         funlist;

#line 134 "parser.hpp" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
