// A Bison parser, made by GNU Bison 3.0.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2013 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "parser.cc" // lalr1.cc:399

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.hh"

// User implementation prologue.

#line 51 "parser.cc" // lalr1.cc:407
// Unqualified %code blocks.
#line 31 "parser.yy" // lalr1.cc:408

  /* include for all driver functions */
  #include "parsing-driver.hh"

#line 58 "parser.cc" // lalr1.cc:408


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyempty = true)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 144 "parser.cc" // lalr1.cc:474

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  parser::parser (ParsingDriver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  parser::~parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  parser::by_state::by_state ()
    : state (empty)
  {}

  inline
  parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.state = empty;
  }

  inline
  parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  parser::symbol_number_type
  parser::by_state::type_get () const
  {
    return state == empty ? 0 : yystos_[state];
  }

  inline
  parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 71: // assign_lhs
      case 75: // pair_elem_lhs
      case 86: // array_elem_lhs
        value.move< AssignLhs* > (that.value);
        break;

      case 72: // assign_rhs
      case 74: // pair_elem_rhs
      case 92: // array_liter
        value.move< AssignRhs* > (that.value);
        break;

      case 81: // expr
      case 82: // unary_op
      case 83: // binary_op
      case 85: // array_elem_exp
      case 87: // int_liter
      case 89: // bool_liter
      case 90: // char_liter
      case 91: // str_liter
      case 94: // pair_liter
        value.move< Expression * > (that.value);
        break;

      case 73: // arg_list
      case 93: // expr_list
        value.move< ExpressionList* > (that.value);
        break;

      case 65: // func_list
        value.move< FunctionDecList* > (that.value);
        break;

      case 66: // function_declaration
        value.move< FunctionDeclaration* > (that.value);
        break;

      case 84: // ident
        value.move< Identifier* > (that.value);
        break;

      case 69: // statement_seq
        value.move< StatSeq* > (that.value);
        break;

      case 70: // statement
        value.move< Statement * > (that.value);
        break;

      case 76: // type
      case 77: // base_type
      case 78: // array_type
      case 79: // pair_type
      case 80: // pair_elem_type
        value.move< Type* > (that.value);
        break;

      case 68: // param
        value.move< VariableDeclaration* > (that.value);
        break;

      case 67: // param_list
        value.move< VariableList* > (that.value);
        break;

      case 59: // CHARLIT
        value.move< char > (that.value);
        break;

      case 26: // ASSIGN
      case 27: // LOGOR
      case 28: // LOGAND
      case 29: // STAR
      case 30: // SLASH
      case 31: // MODULO
      case 32: // PLUS
      case 33: // MINUS
      case 34: // LESS
      case 35: // LESSEQUALS
      case 36: // GREATER
      case 37: // GREATEREQUALS
      case 38: // EQUALS
      case 39: // NOTEQUALS
      case 40: // BANG
      case 41: // LEN
      case 42: // ORD
      case 43: // CHR
      case 60: // INTEGER
      case 88: // int_sign
        value.move< int > (that.value);
        break;

      case 57: // IDENTIFIER
      case 58: // STRINGLIT
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty;
  }

  inline
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 71: // assign_lhs
      case 75: // pair_elem_lhs
      case 86: // array_elem_lhs
        value.copy< AssignLhs* > (that.value);
        break;

      case 72: // assign_rhs
      case 74: // pair_elem_rhs
      case 92: // array_liter
        value.copy< AssignRhs* > (that.value);
        break;

      case 81: // expr
      case 82: // unary_op
      case 83: // binary_op
      case 85: // array_elem_exp
      case 87: // int_liter
      case 89: // bool_liter
      case 90: // char_liter
      case 91: // str_liter
      case 94: // pair_liter
        value.copy< Expression * > (that.value);
        break;

      case 73: // arg_list
      case 93: // expr_list
        value.copy< ExpressionList* > (that.value);
        break;

      case 65: // func_list
        value.copy< FunctionDecList* > (that.value);
        break;

      case 66: // function_declaration
        value.copy< FunctionDeclaration* > (that.value);
        break;

      case 84: // ident
        value.copy< Identifier* > (that.value);
        break;

      case 69: // statement_seq
        value.copy< StatSeq* > (that.value);
        break;

      case 70: // statement
        value.copy< Statement * > (that.value);
        break;

      case 76: // type
      case 77: // base_type
      case 78: // array_type
      case 79: // pair_type
      case 80: // pair_elem_type
        value.copy< Type* > (that.value);
        break;

      case 68: // param
        value.copy< VariableDeclaration* > (that.value);
        break;

      case 67: // param_list
        value.copy< VariableList* > (that.value);
        break;

      case 59: // CHARLIT
        value.copy< char > (that.value);
        break;

      case 26: // ASSIGN
      case 27: // LOGOR
      case 28: // LOGAND
      case 29: // STAR
      case 30: // SLASH
      case 31: // MODULO
      case 32: // PLUS
      case 33: // MINUS
      case 34: // LESS
      case 35: // LESSEQUALS
      case 36: // GREATER
      case 37: // GREATEREQUALS
      case 38: // EQUALS
      case 39: // NOTEQUALS
      case 40: // BANG
      case 41: // LEN
      case 42: // ORD
      case 43: // CHR
      case 60: // INTEGER
      case 88: // int_sign
        value.copy< int > (that.value);
        break;

      case 57: // IDENTIFIER
      case 58: // STRINGLIT
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::parse ()
  {
    /// Whether yyla contains a lookahead.
    bool yyempty = true;

    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 23 "parser.yy" // lalr1.cc:725
{
  //Initialize the initial location.
  yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 601 "parser.cc" // lalr1.cc:725

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyempty)
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
        yyempty = false;
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Discard the token being shifted.
    yyempty = true;

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 71: // assign_lhs
      case 75: // pair_elem_lhs
      case 86: // array_elem_lhs
        yylhs.value.build< AssignLhs* > ();
        break;

      case 72: // assign_rhs
      case 74: // pair_elem_rhs
      case 92: // array_liter
        yylhs.value.build< AssignRhs* > ();
        break;

      case 81: // expr
      case 82: // unary_op
      case 83: // binary_op
      case 85: // array_elem_exp
      case 87: // int_liter
      case 89: // bool_liter
      case 90: // char_liter
      case 91: // str_liter
      case 94: // pair_liter
        yylhs.value.build< Expression * > ();
        break;

      case 73: // arg_list
      case 93: // expr_list
        yylhs.value.build< ExpressionList* > ();
        break;

      case 65: // func_list
        yylhs.value.build< FunctionDecList* > ();
        break;

      case 66: // function_declaration
        yylhs.value.build< FunctionDeclaration* > ();
        break;

      case 84: // ident
        yylhs.value.build< Identifier* > ();
        break;

      case 69: // statement_seq
        yylhs.value.build< StatSeq* > ();
        break;

      case 70: // statement
        yylhs.value.build< Statement * > ();
        break;

      case 76: // type
      case 77: // base_type
      case 78: // array_type
      case 79: // pair_type
      case 80: // pair_elem_type
        yylhs.value.build< Type* > ();
        break;

      case 68: // param
        yylhs.value.build< VariableDeclaration* > ();
        break;

      case 67: // param_list
        yylhs.value.build< VariableList* > ();
        break;

      case 59: // CHARLIT
        yylhs.value.build< char > ();
        break;

      case 26: // ASSIGN
      case 27: // LOGOR
      case 28: // LOGAND
      case 29: // STAR
      case 30: // SLASH
      case 31: // MODULO
      case 32: // PLUS
      case 33: // MINUS
      case 34: // LESS
      case 35: // LESSEQUALS
      case 36: // GREATER
      case 37: // GREATEREQUALS
      case 38: // EQUALS
      case 39: // NOTEQUALS
      case 40: // BANG
      case 41: // LEN
      case 42: // ORD
      case 43: // CHR
      case 60: // INTEGER
      case 88: // int_sign
        yylhs.value.build< int > ();
        break;

      case 57: // IDENTIFIER
      case 58: // STRINGLIT
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 93 "parser.yy" // lalr1.cc:847
    {// //std::cout << " PROGRAM " << std::endl;
     // //std::cout << " HA " << std::endl;
     // //std::cout << " HAHA " << std::endl;
     // //std::cout << " HAHA " << std::endl;
      driver.ast = new Program(yystack_[2].value.as< FunctionDecList* > (), yystack_[1].value.as< StatSeq* > ()); 
     // //std::cout << " HAHA " << std::endl; 
		 }
#line 818 "parser.cc" // lalr1.cc:847
    break;

  case 3:
#line 103 "parser.yy" // lalr1.cc:847
    {// //std::cout << " FUNCTION DEC SEQ BASE" << std::endl;
      yylhs.value.as< FunctionDecList* > () = new FunctionDecList(); }
#line 825 "parser.cc" // lalr1.cc:847
    break;

  case 4:
#line 106 "parser.yy" // lalr1.cc:847
    { ////std::cout << " FUNCTION DEC SEQ " << std::endl;
      std::swap(yylhs.value.as< FunctionDecList* > (), yystack_[1].value.as< FunctionDecList* > ());
      yylhs.value.as< FunctionDecList* > ()->funcs.push_back(yystack_[0].value.as< FunctionDeclaration* > ()); }
#line 833 "parser.cc" // lalr1.cc:847
    break;

  case 5:
#line 112 "parser.yy" // lalr1.cc:847
    {// //std::cout << " FUNCTION DEC " << std::endl;
      if(!(containsRetOrExit(yystack_[1].value.as< StatSeq* > ()))) { 
       yy::parser::error(yystack_[1].location, "syntax error: function path missing RETURN or EXIT"); 
      }
      yylhs.value.as< FunctionDeclaration* > () = new FunctionDeclaration(yystack_[6].value.as< Type* > (), yystack_[5].value.as< Identifier* > (), yystack_[1].value.as< StatSeq* > ()); }
#line 843 "parser.cc" // lalr1.cc:847
    break;

  case 6:
#line 118 "parser.yy" // lalr1.cc:847
    {// //std::cout << " FUNC DEC " << std::endl; 
      if(!(containsRetOrExit(yystack_[1].value.as< StatSeq* > ()))) {
       yy::parser::error(yystack_[1].location, "syntax error: function path missing RETURN or EXIT"); 
      }
      yylhs.value.as< FunctionDeclaration* > () = new FunctionDeclaration(yystack_[7].value.as< Type* > (), yystack_[6].value.as< Identifier* > (), yystack_[4].value.as< VariableList* > (), yystack_[1].value.as< StatSeq* > ()); }
#line 853 "parser.cc" // lalr1.cc:847
    break;

  case 7:
#line 126 "parser.yy" // lalr1.cc:847
    {// //std::cout << "PARAM LIST SEQ BASE " << std::endl;
      yylhs.value.as< VariableList* > () = new VariableList();
      yylhs.value.as< VariableList* > ()->push_back(yystack_[0].value.as< VariableDeclaration* > ()); }
#line 861 "parser.cc" // lalr1.cc:847
    break;

  case 8:
#line 130 "parser.yy" // lalr1.cc:847
    {// //std::cout << " PARAM LIST SEQ " << std::endl;
      std::swap(yylhs.value.as< VariableList* > (), yystack_[2].value.as< VariableList* > ());
      yylhs.value.as< VariableList* > ()->push_back(yystack_[0].value.as< VariableDeclaration* > ()); }
#line 869 "parser.cc" // lalr1.cc:847
    break;

  case 9:
#line 136 "parser.yy" // lalr1.cc:847
    { ////std::cout << " PARAM " << std::endl;
      yylhs.value.as< VariableDeclaration* > () = new VariableDeclaration(yystack_[1].value.as< Type* > (), yystack_[0].value.as< Identifier* > ()); }
#line 876 "parser.cc" // lalr1.cc:847
    break;

  case 10:
#line 141 "parser.yy" // lalr1.cc:847
    { ////std::cout << " STAT SEQ BASE " << std::endl;
      yylhs.value.as< StatSeq* > () = new StatSeq();
      yylhs.value.as< StatSeq* > ()->statements.push_back(yystack_[0].value.as< Statement * > ()); }
#line 884 "parser.cc" // lalr1.cc:847
    break;

  case 11:
#line 145 "parser.yy" // lalr1.cc:847
    {// //std::cout << " STAT SEQ " << std::endl;
       std::swap(yylhs.value.as< StatSeq* > (), yystack_[2].value.as< StatSeq* > ());
       yylhs.value.as< StatSeq* > ()->statements.push_back(yystack_[0].value.as< Statement * > ()); }
#line 892 "parser.cc" // lalr1.cc:847
    break;

  case 12:
#line 151 "parser.yy" // lalr1.cc:847
    {// //std::cout << " SKIP " << std::endl;
      yylhs.value.as< Statement * > () = new SkipStatement(); }
#line 899 "parser.cc" // lalr1.cc:847
    break;

  case 13:
#line 154 "parser.yy" // lalr1.cc:847
    {// //std::cout << " RETURN " << std::endl;
      yylhs.value.as< Statement * > () = new ReturnStatement(yystack_[0].value.as< Expression * > ()); }
#line 906 "parser.cc" // lalr1.cc:847
    break;

  case 14:
#line 157 "parser.yy" // lalr1.cc:847
    {// //std::cout << " ASSIGN " << std::endl;
      yylhs.value.as< Statement * > () = new VariableDeclaration(yystack_[3].value.as< Type* > (), yystack_[2].value.as< Identifier* > (), yystack_[0].value.as< AssignRhs* > ()); }
#line 913 "parser.cc" // lalr1.cc:847
    break;

  case 15:
#line 160 "parser.yy" // lalr1.cc:847
    {// //std::cout << " ASSIGN POST DECLARATION " << std::endl; 
      yylhs.value.as< Statement * > () = new Assignment(yystack_[2].value.as< AssignLhs* > (), yystack_[0].value.as< AssignRhs* > ()); }
#line 920 "parser.cc" // lalr1.cc:847
    break;

  case 16:
#line 163 "parser.yy" // lalr1.cc:847
    {// //std::cout << " READ " << std::endl;
      yylhs.value.as< Statement * > () = new ReadStatement(yystack_[0].value.as< AssignLhs* > ()); }
#line 927 "parser.cc" // lalr1.cc:847
    break;

  case 17:
#line 166 "parser.yy" // lalr1.cc:847
    {// //std::cout << " FREE " << std::endl;
      yylhs.value.as< Statement * > () = new FreeStatement(yystack_[0].value.as< Expression * > ()); }
#line 934 "parser.cc" // lalr1.cc:847
    break;

  case 18:
#line 169 "parser.yy" // lalr1.cc:847
    {// //std::cout << " EXIT " << std::endl;
      yylhs.value.as< Statement * > () = new ExitStatement(yystack_[0].value.as< Expression * > ()); }
#line 941 "parser.cc" // lalr1.cc:847
    break;

  case 19:
#line 172 "parser.yy" // lalr1.cc:847
    {// //std::cout << " PRINT " << std::endl;
      yylhs.value.as< Statement * > () = new PrintStatement(yystack_[0].value.as< Expression * > ()); }
#line 948 "parser.cc" // lalr1.cc:847
    break;

  case 20:
#line 175 "parser.yy" // lalr1.cc:847
    {// //std::cout << " PRINTLN " << std::endl;
      yylhs.value.as< Statement * > () = new PrintlnStatement(yystack_[0].value.as< Expression * > ()); }
#line 955 "parser.cc" // lalr1.cc:847
    break;

  case 21:
#line 178 "parser.yy" // lalr1.cc:847
    {// //std::cout << " BEGIN " << std::endl;
      yylhs.value.as< Statement * > () = new BeginStatement(yystack_[1].value.as< StatSeq* > ()); }
#line 962 "parser.cc" // lalr1.cc:847
    break;

  case 22:
#line 181 "parser.yy" // lalr1.cc:847
    {// //std::cout << " IF " << std::endl;
      yylhs.value.as< Statement * > () = new IfStatement(yystack_[5].value.as< Expression * > (), yystack_[3].value.as< StatSeq* > (), yystack_[1].value.as< StatSeq* > ());  }
#line 969 "parser.cc" // lalr1.cc:847
    break;

  case 23:
#line 184 "parser.yy" // lalr1.cc:847
    { ////std::cout << " WHILE " << std::endl;
      yylhs.value.as< Statement * > () = new WhileStatement(yystack_[3].value.as< Expression * > (), yystack_[1].value.as< StatSeq* > ()); }
#line 976 "parser.cc" // lalr1.cc:847
    break;

  case 24:
#line 189 "parser.yy" // lalr1.cc:847
    { //std::cout << " ASSIGN LHS " << std::endl;
      yylhs.value.as< AssignLhs* > () = dynamic_cast<AssignLhs*>(yystack_[0].value.as< Identifier* > ()); }
#line 983 "parser.cc" // lalr1.cc:847
    break;

  case 25:
#line 192 "parser.yy" // lalr1.cc:847
    { //std::cout << " ASSIGN LHS " << std::endl;
      yylhs.value.as< AssignLhs* > () = yystack_[0].value.as< AssignLhs* > (); }
#line 990 "parser.cc" // lalr1.cc:847
    break;

  case 26:
#line 195 "parser.yy" // lalr1.cc:847
    { //std::cout << " ASSIGN LHS " << std::endl;
      yylhs.value.as< AssignLhs* > () = yystack_[0].value.as< AssignLhs* > (); }
#line 997 "parser.cc" // lalr1.cc:847
    break;

  case 27:
#line 200 "parser.yy" // lalr1.cc:847
    { //std::cout << " ASSIGN RHS " << std::endl; 
      yylhs.value.as< AssignRhs* > () = dynamic_cast<AssignRhs*>(yystack_[0].value.as< Expression * > ()); }
#line 1004 "parser.cc" // lalr1.cc:847
    break;

  case 28:
#line 203 "parser.yy" // lalr1.cc:847
    { //std::cout << " ASSIGN RHS " << std::endl; 
      yylhs.value.as< AssignRhs* > () = yystack_[0].value.as< AssignRhs* > (); }
#line 1011 "parser.cc" // lalr1.cc:847
    break;

  case 29:
#line 206 "parser.yy" // lalr1.cc:847
    { //std::cout << " ASSIGN RHS " << std::endl; 
      yylhs.value.as< AssignRhs* > () = new NewPair(yystack_[3].value.as< Expression * > (), yystack_[1].value.as< Expression * > ()); }
#line 1018 "parser.cc" // lalr1.cc:847
    break;

  case 30:
#line 209 "parser.yy" // lalr1.cc:847
    { //std::cout << " ASSIGN RHS " << std::endl; 
      yylhs.value.as< AssignRhs* > () = yystack_[0].value.as< AssignRhs* > (); }
#line 1025 "parser.cc" // lalr1.cc:847
    break;

  case 31:
#line 212 "parser.yy" // lalr1.cc:847
    { //std::cout << " ASSIGN RHS " << std::endl; 
      yylhs.value.as< AssignRhs* > () = new FunctionCall(yystack_[2].value.as< Identifier* > ()); }
#line 1032 "parser.cc" // lalr1.cc:847
    break;

  case 32:
#line 215 "parser.yy" // lalr1.cc:847
    { //std::cout << " ASSIGN RHS " << std::endl; 
      yylhs.value.as< AssignRhs* > () = new FunctionCall(yystack_[3].value.as< Identifier* > (), yystack_[1].value.as< ExpressionList* > ()); }
#line 1039 "parser.cc" // lalr1.cc:847
    break;

  case 33:
#line 220 "parser.yy" // lalr1.cc:847
    { //std::cout << " ARG LIST SEQ BASE " << //std::cout;
      yylhs.value.as< ExpressionList* > () = new ExpressionList();
      yylhs.value.as< ExpressionList* > ()->push_back(yystack_[0].value.as< Expression * > ());}
#line 1047 "parser.cc" // lalr1.cc:847
    break;

  case 34:
#line 224 "parser.yy" // lalr1.cc:847
    { //std::cout << " ARG LIST SEQ " << std::endl;
      std::swap(yylhs.value.as< ExpressionList* > (), yystack_[2].value.as< ExpressionList* > ());
      yylhs.value.as< ExpressionList* > ()->push_back(yystack_[0].value.as< Expression * > ()); }
#line 1055 "parser.cc" // lalr1.cc:847
    break;

  case 35:
#line 230 "parser.yy" // lalr1.cc:847
    { //std::cout << " PAIR ELEM " << std::endl; 
      yylhs.value.as< AssignRhs* > () = new PairElem(true, yystack_[0].value.as< Expression * > ()); }
#line 1062 "parser.cc" // lalr1.cc:847
    break;

  case 36:
#line 233 "parser.yy" // lalr1.cc:847
    { //std::cout << " PAIR ELEM " << std::endl; 
      yylhs.value.as< AssignRhs* > () = new PairElem(false, yystack_[0].value.as< Expression * > ()); }
#line 1069 "parser.cc" // lalr1.cc:847
    break;

  case 37:
#line 238 "parser.yy" // lalr1.cc:847
    { //std::cout << " PAIR ELEM " << std::endl; 
      yylhs.value.as< AssignLhs* > () = new PairElem(true, yystack_[0].value.as< Expression * > ()); }
#line 1076 "parser.cc" // lalr1.cc:847
    break;

  case 38:
#line 241 "parser.yy" // lalr1.cc:847
    { //std::cout << " PAIR ELEM " << std::endl; 
      yylhs.value.as< AssignLhs* > () = new PairElem(false, yystack_[0].value.as< Expression * > ()); }
#line 1083 "parser.cc" // lalr1.cc:847
    break;

  case 39:
#line 246 "parser.yy" // lalr1.cc:847
    { //std::cout << " TYPE " << std::endl; 
      yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > (); }
#line 1090 "parser.cc" // lalr1.cc:847
    break;

  case 40:
#line 249 "parser.yy" // lalr1.cc:847
    { //std::cout << " TYPE " << std::endl; 
      yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > (); }
#line 1097 "parser.cc" // lalr1.cc:847
    break;

  case 41:
#line 252 "parser.yy" // lalr1.cc:847
    { //std::cout << " TYPE " << std::endl; 
      yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > (); }
#line 1104 "parser.cc" // lalr1.cc:847
    break;

  case 42:
#line 257 "parser.yy" // lalr1.cc:847
    { //std::cout << " INTEGER TYPE " << std::endl;
      yylhs.value.as< Type* > () = new IntegerType(); }
#line 1111 "parser.cc" // lalr1.cc:847
    break;

  case 43:
#line 260 "parser.yy" // lalr1.cc:847
    { //std::cout << " BOOL TYPE " << std::endl;
      yylhs.value.as< Type* > () = new BoolType(); }
#line 1118 "parser.cc" // lalr1.cc:847
    break;

  case 44:
#line 263 "parser.yy" // lalr1.cc:847
    { //std::cout << " CHAR TYPE " << std::endl;
      yylhs.value.as< Type* > () = new CharType(); }
#line 1125 "parser.cc" // lalr1.cc:847
    break;

  case 45:
#line 266 "parser.yy" // lalr1.cc:847
    { //std::cout << " STRING TYPE " << std::endl;
      yylhs.value.as< Type* > () = new StringType(); }
#line 1132 "parser.cc" // lalr1.cc:847
    break;

  case 46:
#line 271 "parser.yy" // lalr1.cc:847
    { //std::cout << " ARRAY TYPE " << std::endl;
    yylhs.value.as< Type* > () = new ArrayType(yystack_[2].value.as< Type* > ()); }
#line 1139 "parser.cc" // lalr1.cc:847
    break;

  case 47:
#line 276 "parser.yy" // lalr1.cc:847
    { //std::cout << " PAIR TYPE " << std::endl;
    yylhs.value.as< Type* > () = new PairType(yystack_[3].value.as< Type* > (), yystack_[1].value.as< Type* > ()); }
#line 1146 "parser.cc" // lalr1.cc:847
    break;

  case 48:
#line 281 "parser.yy" // lalr1.cc:847
    { //std::cout << " PAIR ELEM TYPE " << std::endl; 
      yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > (); }
#line 1153 "parser.cc" // lalr1.cc:847
    break;

  case 49:
#line 284 "parser.yy" // lalr1.cc:847
    { //std::cout << " PAIR ELEM TYPE " << std::endl; 
      yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > (); }
#line 1160 "parser.cc" // lalr1.cc:847
    break;

  case 50:
#line 287 "parser.yy" // lalr1.cc:847
    { //std::cout << " PAIR ELEM TYPE " << std::endl; 
       yylhs.value.as< Type* > () = new PairKeyword(); }
#line 1167 "parser.cc" // lalr1.cc:847
    break;

  case 51:
#line 294 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR " << std::endl; 
      yylhs.value.as< Expression * > () = yystack_[0].value.as< Expression * > (); }
#line 1174 "parser.cc" // lalr1.cc:847
    break;

  case 52:
#line 297 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR " << std::endl; 
      yylhs.value.as< Expression * > () = yystack_[0].value.as< Expression * > (); }
#line 1181 "parser.cc" // lalr1.cc:847
    break;

  case 53:
#line 300 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR " << std::endl; 
      yylhs.value.as< Expression * > () = yystack_[0].value.as< Expression * > (); }
#line 1188 "parser.cc" // lalr1.cc:847
    break;

  case 54:
#line 303 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR " << std::endl; 
      yylhs.value.as< Expression * > () = yystack_[0].value.as< Expression * > (); }
#line 1195 "parser.cc" // lalr1.cc:847
    break;

  case 55:
#line 306 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR " << std::endl; 
      yylhs.value.as< Expression * > () = yystack_[0].value.as< Expression * > (); }
#line 1202 "parser.cc" // lalr1.cc:847
    break;

  case 56:
#line 309 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR " << std::endl; 
      yylhs.value.as< Expression * > () = yystack_[0].value.as< Identifier* > (); }
#line 1209 "parser.cc" // lalr1.cc:847
    break;

  case 57:
#line 312 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR " << std::endl; 
      yylhs.value.as< Expression * > () = yystack_[0].value.as< Expression * > (); }
#line 1216 "parser.cc" // lalr1.cc:847
    break;

  case 58:
#line 315 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR " << std::endl; 
      yylhs.value.as< Expression * > () = yystack_[0].value.as< Expression * > (); }
#line 1223 "parser.cc" // lalr1.cc:847
    break;

  case 59:
#line 318 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR " << std::endl; 
      yylhs.value.as< Expression * > () = yystack_[0].value.as< Expression * > (); }
#line 1230 "parser.cc" // lalr1.cc:847
    break;

  case 60:
#line 321 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR " << std::endl; 
      yylhs.value.as< Expression * > () = yystack_[1].value.as< Expression * > (); }
#line 1237 "parser.cc" // lalr1.cc:847
    break;

  case 61:
#line 327 "parser.yy" // lalr1.cc:847
    { //std::cout << " BANG UNARY " << std::endl;
      yylhs.value.as< Expression * > () = new UnaryOperator(yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1244 "parser.cc" // lalr1.cc:847
    break;

  case 62:
#line 330 "parser.yy" // lalr1.cc:847
    { //std::cout << " LEN UNARY " << std::endl;
      yylhs.value.as< Expression * > () = new UnaryOperator(yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1251 "parser.cc" // lalr1.cc:847
    break;

  case 63:
#line 333 "parser.yy" // lalr1.cc:847
    { //std::cout << " ORD UNARY " << std::endl;
      yylhs.value.as< Expression * > () = new UnaryOperator(yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1258 "parser.cc" // lalr1.cc:847
    break;

  case 64:
#line 336 "parser.yy" // lalr1.cc:847
    { //std::cout << " CHR ORD " << std::endl;
      yylhs.value.as< Expression * > () = new UnaryOperator(yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1265 "parser.cc" // lalr1.cc:847
    break;

  case 65:
#line 339 "parser.yy" // lalr1.cc:847
    { //std::cout << " MINUS UNARY " << std::endl;
      yylhs.value.as< Expression * > () = new UnaryOperator(yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1272 "parser.cc" // lalr1.cc:847
    break;

  case 66:
#line 344 "parser.yy" // lalr1.cc:847
    { //std::cout << " STAR BIN " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1279 "parser.cc" // lalr1.cc:847
    break;

  case 67:
#line 347 "parser.yy" // lalr1.cc:847
    { //std::cout << " SLASH BIN " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1286 "parser.cc" // lalr1.cc:847
    break;

  case 68:
#line 350 "parser.yy" // lalr1.cc:847
    { //std::cout << " MODULO BIN " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1293 "parser.cc" // lalr1.cc:847
    break;

  case 69:
#line 353 "parser.yy" // lalr1.cc:847
    { //std::cout << " PLUS BIN " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1300 "parser.cc" // lalr1.cc:847
    break;

  case 70:
#line 356 "parser.yy" // lalr1.cc:847
    { //std::cout << " MINUS BIN " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1307 "parser.cc" // lalr1.cc:847
    break;

  case 71:
#line 359 "parser.yy" // lalr1.cc:847
    { //std::cout << " GREATER BIN " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1314 "parser.cc" // lalr1.cc:847
    break;

  case 72:
#line 362 "parser.yy" // lalr1.cc:847
    { //std::cout << " GREATEREQUALS BIN " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1321 "parser.cc" // lalr1.cc:847
    break;

  case 73:
#line 365 "parser.yy" // lalr1.cc:847
    { //std::cout << " LESS BIN " << std::endl; 
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1328 "parser.cc" // lalr1.cc:847
    break;

  case 74:
#line 368 "parser.yy" // lalr1.cc:847
    { //std::cout << " LESSEQUALS BIN " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1335 "parser.cc" // lalr1.cc:847
    break;

  case 75:
#line 371 "parser.yy" // lalr1.cc:847
    { std::cout <<"token : " << yystack_[1].value.as< int > () << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1342 "parser.cc" // lalr1.cc:847
    break;

  case 76:
#line 374 "parser.yy" // lalr1.cc:847
    { //std::cout << " NOTEQUALS BIN " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1349 "parser.cc" // lalr1.cc:847
    break;

  case 77:
#line 377 "parser.yy" // lalr1.cc:847
    { //std::cout << " LOGAND " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1356 "parser.cc" // lalr1.cc:847
    break;

  case 78:
#line 380 "parser.yy" // lalr1.cc:847
    { //std::cout << " LOGOR " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1363 "parser.cc" // lalr1.cc:847
    break;

  case 79:
#line 385 "parser.yy" // lalr1.cc:847
    { //std::cout << " IDENT " << std::endl;
      yylhs.value.as< Identifier* > () = new Identifier(yystack_[0].value.as< std::string > ()); }
#line 1370 "parser.cc" // lalr1.cc:847
    break;

  case 80:
#line 390 "parser.yy" // lalr1.cc:847
    { //std::cout << " ARRAY ELEM " << std::endl;
      yylhs.value.as< Expression * > () = new ArrayElem(yystack_[3].value.as< Identifier* > (), yystack_[1].value.as< Expression * > ()); }
#line 1377 "parser.cc" // lalr1.cc:847
    break;

  case 81:
#line 395 "parser.yy" // lalr1.cc:847
    { //std::cout << " ARRAY ELEM " << std::endl;
      yylhs.value.as< AssignLhs* > () = new ArrayElem(yystack_[3].value.as< Identifier* > (), yystack_[1].value.as< Expression * > ()); }
#line 1384 "parser.cc" // lalr1.cc:847
    break;

  case 82:
#line 410 "parser.yy" // lalr1.cc:847
    { //std::cout << " INT LITER " << std::endl;
       yylhs.value.as< Expression * > () = new Number(yystack_[1].value.as< int > () * yystack_[0].value.as< int > ()); }
#line 1391 "parser.cc" // lalr1.cc:847
    break;

  case 83:
#line 415 "parser.yy" // lalr1.cc:847
    { yylhs.value.as< int > () = 1; }
#line 1397 "parser.cc" // lalr1.cc:847
    break;

  case 84:
#line 417 "parser.yy" // lalr1.cc:847
    { yylhs.value.as< int > () = 1; }
#line 1403 "parser.cc" // lalr1.cc:847
    break;

  case 85:
#line 421 "parser.yy" // lalr1.cc:847
    { //std::cout << " BOOL LITER " << std::endl;
      yylhs.value.as< Expression * > () = new Boolean(true); }
#line 1410 "parser.cc" // lalr1.cc:847
    break;

  case 86:
#line 424 "parser.yy" // lalr1.cc:847
    { //std::cout << " BOOL LITER " << std::endl;
      yylhs.value.as< Expression * > () = new Boolean(false); }
#line 1417 "parser.cc" // lalr1.cc:847
    break;

  case 87:
#line 429 "parser.yy" // lalr1.cc:847
    { //std::cout << " CHER LITER " << std::endl;
      yylhs.value.as< Expression * > () = new Char(yystack_[0].value.as< char > ());}
#line 1424 "parser.cc" // lalr1.cc:847
    break;

  case 88:
#line 434 "parser.yy" // lalr1.cc:847
    { //std::cout << " STRING LITER " << std::endl;
      yylhs.value.as< Expression * > () = new String(yystack_[0].value.as< std::string > ()); }
#line 1431 "parser.cc" // lalr1.cc:847
    break;

  case 89:
#line 439 "parser.yy" // lalr1.cc:847
    { //std::cout << " ARRAY LITER " << std::endl;
    yylhs.value.as< AssignRhs* > () = new ArrayLiter(yystack_[1].value.as< ExpressionList* > ()); }
#line 1438 "parser.cc" // lalr1.cc:847
    break;

  case 90:
#line 444 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR LIST SEQ BASE " << std::endl;
	  }
#line 1445 "parser.cc" // lalr1.cc:847
    break;

  case 91:
#line 447 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR LIST SEQ BASE " << std::endl;
      yylhs.value.as< ExpressionList* > () = new ExpressionList();
      yylhs.value.as< ExpressionList* > ()->push_back(yystack_[0].value.as< Expression * > ()); }
#line 1453 "parser.cc" // lalr1.cc:847
    break;

  case 92:
#line 451 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR LIST SEQ " << std::endl;
      std::swap(yylhs.value.as< ExpressionList* > (), yystack_[2].value.as< ExpressionList* > ());
      yylhs.value.as< ExpressionList* > ()->push_back(yystack_[0].value.as< Expression * > ()); }
#line 1461 "parser.cc" // lalr1.cc:847
    break;

  case 93:
#line 457 "parser.yy" // lalr1.cc:847
    { //std::cout << " NULL PAIR LITER " << std::endl;
      yylhs.value.as< Expression * > () = new Null(); }
#line 1468 "parser.cc" // lalr1.cc:847
    break;


#line 1472 "parser.cc" // lalr1.cc:847
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type_get ()));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyempty)
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyempty = true;
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyempty)
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyempty)
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, symbol_number_type yytoken) const
  {
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -49;

  const signed char parser::yytable_ninf_ = -84;

  const short int
  parser::yypact_[] =
  {
      23,   -49,    32,   172,   -49,   172,   256,   256,   -49,   256,
     256,   256,    -4,   -49,   -49,   -49,   -49,   256,   256,   -12,
     256,   256,   -49,   -49,     3,   -49,    18,   -49,   -27,   -49,
     -49,   -49,    13,   -49,     4,   -27,   -49,   -49,   -49,   -49,
     256,   256,   256,   256,   256,   256,   -49,   -49,   170,   -49,
     -49,    14,   -49,   -49,   -11,   -49,   -49,   -49,   -49,   291,
     407,   407,   407,    43,   407,   407,   -49,   407,   407,   -49,
     172,   200,     9,   -13,   256,   -49,    35,   -49,   -49,   -49,
     -49,   -49,   369,   172,   256,   256,   256,   256,   256,   256,
     256,   256,   256,   256,   256,   256,   256,   256,   -49,   172,
      -4,    24,    30,    31,    20,   -49,    42,    82,    56,   256,
     256,   -49,   -49,   407,   -49,   -49,   200,    51,   327,   -49,
      10,   273,   273,    17,   -49,   -49,    17,    17,    17,    17,
      17,    17,    17,    17,   348,     7,    43,    58,   407,   -26,
     256,   407,   407,   -49,    89,   -21,   -49,   -27,   -49,   172,
     -49,   -49,    63,   235,   -49,   256,   304,   172,    92,   109,
     -49,    -2,   -49,   -49,   -16,   407,   407,   256,     5,   172,
     -49,   -49,   -49,   256,   388,   -49,     6,   407,   -49,   -49
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     3,     0,     0,     1,     0,    83,    83,    12,    83,
      83,    83,     0,    42,    43,    44,    45,    83,    83,     0,
      83,    83,    79,     4,     0,    10,     0,    26,     0,    39,
      40,    41,    24,    25,     0,     0,    85,    86,    93,    84,
      83,    83,    83,    83,    83,    83,    88,    87,     0,    58,
      59,    56,    57,    51,     0,    52,    53,    54,    55,     0,
      17,    18,    13,     0,    19,    20,    16,    37,    38,     2,
       0,    83,     0,     0,    83,    21,     0,    65,    61,    62,
      63,    64,     0,     0,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    82,     0,
      50,     0,    48,    49,     0,    11,     0,    90,     0,    83,
      83,    15,    30,    27,    28,    46,    83,     0,     0,    60,
       0,    78,    77,    66,    67,    68,    69,    70,    73,    74,
      71,    72,    75,    76,     0,     0,     0,     0,    91,     0,
      83,    35,    36,    14,     0,     0,     7,     0,    81,     0,
      80,    23,     0,    83,    89,    83,     0,     0,     0,     0,
       9,     0,    47,    31,     0,    33,    92,    83,     0,     0,
       8,    22,    32,    83,     0,     5,     0,    34,    29,     6
  };

  const signed char
  parser::yypgoto_[] =
  {
     -49,   -49,   -49,   -49,   -49,   -48,    11,    47,    93,    -3,
     -49,   -49,   -49,    -1,   -43,   -41,   -49,   -18,    -6,   -49,
     -49,    22,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,
     -49,   -49
  };

  const short int
  parser::yydefgoto_[] =
  {
      -1,     2,     3,    23,   145,   146,    24,    25,    26,   111,
     164,   112,    27,    35,    29,    30,    31,   104,   113,    49,
      50,    51,    52,    33,    53,    54,    55,    56,    57,   114,
     139,    58
  };

  const short int
  parser::yytable_[] =
  {
      48,    59,    28,    60,    61,    62,   171,    69,    75,   175,
     179,    64,    65,   116,    67,    68,    34,   149,   151,    72,
     102,   154,   103,   155,   158,    32,     1,    32,   159,   172,
      22,   117,     4,   173,    77,    78,    79,    80,    81,    82,
      63,    32,    20,    21,    71,    22,    70,    87,    88,    98,
      73,    70,    70,    70,    70,    70,   115,    76,    70,    74,
      97,   116,   101,   100,    13,    14,    15,    16,   118,   136,
      72,    12,    13,    14,    15,    16,   -39,   -40,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,    32,   102,   120,   103,   144,    36,    37,    22,
     140,   138,   153,   141,   142,    32,   157,    38,   162,   169,
     135,   170,    66,   143,    39,    40,   147,   105,   152,     0,
       0,    32,    41,    42,    43,    44,    45,     0,   137,    12,
      13,    14,    15,    16,   156,   101,     0,     0,     0,    22,
      46,    47,   -83,     0,     0,     0,     0,   165,     0,   166,
       0,     0,     0,     0,     0,     0,     0,     0,   147,     0,
     161,   174,     0,     0,     0,     0,     0,   177,   168,   160,
       0,    32,     0,     0,     0,     5,    83,     6,     0,    32,
     176,     7,     0,     0,     8,     9,    10,     0,     0,     0,
      11,    32,    12,    13,    14,    15,    16,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
       0,     0,     0,     0,     0,    36,    37,     0,     0,   106,
       0,     0,    17,    18,    19,    38,    20,    21,     0,    22,
       0,     0,    39,    40,     0,     0,     0,     0,     0,     0,
      41,    42,    43,    44,    45,     0,   107,     0,     0,     0,
      36,    37,     0,   108,   109,   110,     0,    22,    46,    47,
      38,     0,     0,     0,     0,     0,     0,    39,    40,     0,
       0,    36,    37,     0,     0,    41,    42,    43,    44,    45,
     163,    38,     0,     0,     0,     0,     0,     0,    39,    40,
       0,     0,    22,    46,    47,     0,    41,    42,    43,    44,
      45,    99,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    22,    46,    47,     0,     0,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   167,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,     0,     0,     0,
       0,     0,     0,     0,   148,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,     0,     0,
       0,     0,     0,     0,     0,   150,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,     0,
       0,     0,     0,     0,   119,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,     0,     0,
       0,     0,     0,   178,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96
  };

  const short int
  parser::yycheck_[] =
  {
       6,     7,     3,     9,    10,    11,     8,     4,     4,     4,
       4,    17,    18,    26,    20,    21,     5,     7,    11,    46,
      63,    47,    63,    49,    45,     3,     3,     5,    49,    45,
      57,    44,     0,    49,    40,    41,    42,    43,    44,    45,
      44,    19,    54,    55,    26,    57,    48,    30,    31,    60,
      28,    48,    48,    48,    48,    48,    47,    35,    48,    46,
      46,    26,    63,    20,    21,    22,    23,    24,    74,    49,
      46,    20,    21,    22,    23,    24,    46,    46,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    70,   136,    83,   136,    45,    15,    16,    57,
      44,   107,    44,   109,   110,    83,    17,    25,    45,    17,
      99,   159,    19,   116,    32,    33,   117,    70,   136,    -1,
      -1,    99,    40,    41,    42,    43,    44,    -1,   106,    20,
      21,    22,    23,    24,   140,   136,    -1,    -1,    -1,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,   153,    -1,   155,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   159,    -1,
     149,   167,    -1,    -1,    -1,    -1,    -1,   173,   157,   147,
      -1,   149,    -1,    -1,    -1,     3,     6,     5,    -1,   157,
     169,     9,    -1,    -1,    12,    13,    14,    -1,    -1,    -1,
      18,   169,    20,    21,    22,    23,    24,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      -1,    -1,    -1,    -1,    -1,    15,    16,    -1,    -1,    19,
      -1,    -1,    50,    51,    52,    25,    54,    55,    -1,    57,
      -1,    -1,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    -1,    46,    -1,    -1,    -1,
      15,    16,    -1,    53,    54,    55,    -1,    57,    58,    59,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    -1,
      -1,    15,    16,    -1,    -1,    40,    41,    42,    43,    44,
      45,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      -1,    -1,    57,    58,    59,    -1,    40,    41,    42,    43,
      44,    10,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    57,    58,    59,    -1,    -1,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    -1,
      -1,    -1,    -1,    -1,    45,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    -1,    -1,
      -1,    -1,    -1,    45,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,    64,    65,     0,     3,     5,     9,    12,    13,
      14,    18,    20,    21,    22,    23,    24,    50,    51,    52,
      54,    55,    57,    66,    69,    70,    71,    75,    76,    77,
      78,    79,    84,    86,    69,    76,    15,    16,    25,    32,
      33,    40,    41,    42,    43,    44,    58,    59,    81,    82,
      83,    84,    85,    87,    88,    89,    90,    91,    94,    81,
      81,    81,    81,    44,    81,    81,    71,    81,    81,     4,
      48,    26,    46,    84,    46,     4,    84,    81,    81,    81,
      81,    81,    81,     6,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    46,    60,    10,
      20,    76,    77,    78,    80,    70,    19,    46,    53,    54,
      55,    72,    74,    81,    92,    47,    26,    44,    81,    45,
      69,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    69,    49,    84,    81,    93,
      44,    81,    81,    72,    45,    67,    68,    76,    47,     7,
      47,    11,    80,    44,    47,    49,    81,    17,    45,    49,
      84,    69,    45,    45,    73,    81,    81,    49,    69,    17,
      68,     8,    45,    49,    81,     4,    69,    81,    45,     4
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    63,    64,    65,    65,    66,    66,    67,    67,    68,
      69,    69,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    71,    71,    71,    72,    72,    72,
      72,    72,    72,    73,    73,    74,    74,    75,    75,    76,
      76,    76,    77,    77,    77,    77,    78,    79,    80,    80,
      80,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    82,    82,    82,    82,    82,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    84,
      85,    86,    87,    88,    88,    89,    89,    90,    91,    92,
      93,    93,    93,    94
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     4,     0,     2,     7,     8,     1,     3,     2,
       1,     3,     1,     2,     4,     3,     2,     2,     2,     2,
       2,     3,     7,     5,     1,     1,     1,     1,     1,     6,
       1,     4,     5,     1,     3,     2,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     3,     6,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       4,     4,     2,     0,     1,     1,     1,     1,     1,     3,
       0,     1,     3,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "ENDF", "error", "$undefined", "BEGIN", "END", "IF", "THEN", "ELSE",
  "FI", "WHILE", "DO", "DONE", "SKIP", "FREE", "EXIT", "TRUE", "FALSE",
  "IS", "RETURN", "CALL", "PAIR", "INT", "BOOL", "CHAR", "STRING",
  "NULLTOKEN", "ASSIGN", "LOGOR", "LOGAND", "STAR", "SLASH", "MODULO",
  "PLUS", "MINUS", "LESS", "LESSEQUALS", "GREATER", "GREATEREQUALS",
  "EQUALS", "NOTEQUALS", "BANG", "LEN", "ORD", "CHR", "LPAREN", "RPAREN",
  "LSQUARE", "RSQUARE", "SEMICOLON", "COMMA", "PRINT", "PRINTLN", "READ",
  "NEWPAIR", "FST", "SND", "ERROR", "IDENTIFIER", "STRINGLIT", "CHARLIT",
  "INTEGER", "UMINUS", "UPLUS", "$accept", "program", "func_list",
  "function_declaration", "param_list", "param", "statement_seq",
  "statement", "assign_lhs", "assign_rhs", "arg_list", "pair_elem_rhs",
  "pair_elem_lhs", "type", "base_type", "array_type", "pair_type",
  "pair_elem_type", "expr", "unary_op", "binary_op", "ident",
  "array_elem_exp", "array_elem_lhs", "int_liter", "int_sign",
  "bool_liter", "char_liter", "str_liter", "array_liter", "expr_list",
  "pair_liter", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  parser::yyrline_[] =
  {
       0,    92,    92,   103,   105,   111,   117,   125,   129,   135,
     140,   144,   150,   153,   156,   159,   162,   165,   168,   171,
     174,   177,   180,   183,   188,   191,   194,   199,   202,   205,
     208,   211,   214,   219,   223,   229,   232,   237,   240,   245,
     248,   251,   256,   259,   262,   265,   270,   275,   280,   283,
     286,   293,   296,   299,   302,   305,   308,   311,   314,   317,
     320,   326,   329,   332,   335,   338,   343,   346,   349,   352,
     355,   358,   361,   364,   367,   370,   373,   376,   379,   384,
     389,   394,   409,   415,   416,   420,   423,   428,   433,   438,
     444,   446,   450,   456
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 2021 "parser.cc" // lalr1.cc:1155
#line 466 "parser.yy" // lalr1.cc:1156


void yy::parser::error (const location_type& l, const std::string& m) {
  driver.error(l, m);
}

bool containsRetOrExit(StatSeq *seq) {
    ////std::cout << " HERE " << std::endl;
    ////std::cout << seq->statements.size() << std::endl;
    Statement *stat= seq->statements.back();
    ReturnStatement *retstat;
    IfStatement *ifstat;
    ExitStatement *exitstat;
	   
    exitstat= dynamic_cast<ExitStatement*>(stat);
    retstat = dynamic_cast<ReturnStatement*>(stat);
    ifstat  = dynamic_cast<IfStatement*>(stat);

    if(retstat != NULL || exitstat != NULL) {
      ////std::cout << " YH " << std::endl;
      return true;
    } else if(ifstat != NULL) {
      ////std::cout << " OK " << std::endl;
      return (containsRetOrExit(ifstat->thenS)
																				 && containsRetOrExit(ifstat->elseS));
    }
    return false;
}
