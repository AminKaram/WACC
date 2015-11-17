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
      case 93: // array_liter
        value.move< AssignRhs* > (that.value);
        break;

      case 81: // expr
      case 82: // unary_op
      case 83: // binary_op
      case 85: // array_elem_exp
      case 88: // int_liter
      case 90: // bool_liter
      case 91: // char_liter
      case 92: // str_liter
      case 95: // pair_liter
        value.move< Expression * > (that.value);
        break;

      case 73: // arg_list
      case 87: // array_index
      case 94: // expr_list
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
      case 89: // int_sign
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
      case 93: // array_liter
        value.copy< AssignRhs* > (that.value);
        break;

      case 81: // expr
      case 82: // unary_op
      case 83: // binary_op
      case 85: // array_elem_exp
      case 88: // int_liter
      case 90: // bool_liter
      case 91: // char_liter
      case 92: // str_liter
      case 95: // pair_liter
        value.copy< Expression * > (that.value);
        break;

      case 73: // arg_list
      case 87: // array_index
      case 94: // expr_list
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
      case 89: // int_sign
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

#line 603 "parser.cc" // lalr1.cc:725

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
      case 93: // array_liter
        yylhs.value.build< AssignRhs* > ();
        break;

      case 81: // expr
      case 82: // unary_op
      case 83: // binary_op
      case 85: // array_elem_exp
      case 88: // int_liter
      case 90: // bool_liter
      case 91: // char_liter
      case 92: // str_liter
      case 95: // pair_liter
        yylhs.value.build< Expression * > ();
        break;

      case 73: // arg_list
      case 87: // array_index
      case 94: // expr_list
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
      case 89: // int_sign
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
#line 821 "parser.cc" // lalr1.cc:847
    break;

  case 3:
#line 103 "parser.yy" // lalr1.cc:847
    {// //std::cout << " FUNCTION DEC SEQ BASE" << std::endl;
      yylhs.value.as< FunctionDecList* > () = new FunctionDecList(); }
#line 828 "parser.cc" // lalr1.cc:847
    break;

  case 4:
#line 106 "parser.yy" // lalr1.cc:847
    { ////std::cout << " FUNCTION DEC SEQ " << std::endl;
      std::swap(yylhs.value.as< FunctionDecList* > (), yystack_[1].value.as< FunctionDecList* > ());
      yylhs.value.as< FunctionDecList* > ()->funcs.push_back(yystack_[0].value.as< FunctionDeclaration* > ()); }
#line 836 "parser.cc" // lalr1.cc:847
    break;

  case 5:
#line 112 "parser.yy" // lalr1.cc:847
    {// //std::cout << " FUNCTION DEC " << std::endl;
      if(!(containsRetOrExit(yystack_[1].value.as< StatSeq* > ()))) { 
       yy::parser::error(yystack_[1].location, "syntax error: function path missing RETURN or EXIT"); 
      }
      yylhs.value.as< FunctionDeclaration* > () = new FunctionDeclaration(yystack_[6].value.as< Type* > (), yystack_[5].value.as< Identifier* > (), yystack_[1].value.as< StatSeq* > ()); }
#line 846 "parser.cc" // lalr1.cc:847
    break;

  case 6:
#line 118 "parser.yy" // lalr1.cc:847
    {// //std::cout << " FUNC DEC " << std::endl; 
      if(!(containsRetOrExit(yystack_[1].value.as< StatSeq* > ()))) {
       yy::parser::error(yystack_[1].location, "syntax error: function path missing RETURN or EXIT"); 
      }
      yylhs.value.as< FunctionDeclaration* > () = new FunctionDeclaration(yystack_[7].value.as< Type* > (), yystack_[6].value.as< Identifier* > (), yystack_[4].value.as< VariableList* > (), yystack_[1].value.as< StatSeq* > ()); }
#line 856 "parser.cc" // lalr1.cc:847
    break;

  case 7:
#line 126 "parser.yy" // lalr1.cc:847
    {// //std::cout << "PARAM LIST SEQ BASE " << std::endl;
      yylhs.value.as< VariableList* > () = new VariableList();
      yylhs.value.as< VariableList* > ()->push_back(yystack_[0].value.as< VariableDeclaration* > ()); }
#line 864 "parser.cc" // lalr1.cc:847
    break;

  case 8:
#line 130 "parser.yy" // lalr1.cc:847
    {// //std::cout << " PARAM LIST SEQ " << std::endl;
      std::swap(yylhs.value.as< VariableList* > (), yystack_[2].value.as< VariableList* > ());
      yylhs.value.as< VariableList* > ()->push_back(yystack_[0].value.as< VariableDeclaration* > ()); }
#line 872 "parser.cc" // lalr1.cc:847
    break;

  case 9:
#line 136 "parser.yy" // lalr1.cc:847
    { ////std::cout << " PARAM " << std::endl;
      yylhs.value.as< VariableDeclaration* > () = new VariableDeclaration(yystack_[1].value.as< Type* > (), yystack_[0].value.as< Identifier* > ()); }
#line 879 "parser.cc" // lalr1.cc:847
    break;

  case 10:
#line 141 "parser.yy" // lalr1.cc:847
    { ////std::cout << " STAT SEQ BASE " << std::endl;
      yylhs.value.as< StatSeq* > () = new StatSeq();
      yylhs.value.as< StatSeq* > ()->statements.push_back(yystack_[0].value.as< Statement * > ()); }
#line 887 "parser.cc" // lalr1.cc:847
    break;

  case 11:
#line 145 "parser.yy" // lalr1.cc:847
    {// //std::cout << " STAT SEQ " << std::endl;
       std::swap(yylhs.value.as< StatSeq* > (), yystack_[2].value.as< StatSeq* > ());
       yylhs.value.as< StatSeq* > ()->statements.push_back(yystack_[0].value.as< Statement * > ()); }
#line 895 "parser.cc" // lalr1.cc:847
    break;

  case 12:
#line 151 "parser.yy" // lalr1.cc:847
    {// //std::cout << " SKIP " << std::endl;
      yylhs.value.as< Statement * > () = new SkipStatement(); }
#line 902 "parser.cc" // lalr1.cc:847
    break;

  case 13:
#line 154 "parser.yy" // lalr1.cc:847
    {// //std::cout << " RETURN " << std::endl;
      yylhs.value.as< Statement * > () = new ReturnStatement(yystack_[0].value.as< Expression * > ()); }
#line 909 "parser.cc" // lalr1.cc:847
    break;

  case 14:
#line 157 "parser.yy" // lalr1.cc:847
    {// //std::cout << " ASSIGN " << std::endl;
      yylhs.value.as< Statement * > () = new VariableDeclaration(yystack_[3].value.as< Type* > (), yystack_[2].value.as< Identifier* > (), yystack_[0].value.as< AssignRhs* > ()); }
#line 916 "parser.cc" // lalr1.cc:847
    break;

  case 15:
#line 160 "parser.yy" // lalr1.cc:847
    {// //std::cout << " ASSIGN POST DECLARATION " << std::endl; 
      yylhs.value.as< Statement * > () = new Assignment(yystack_[2].value.as< AssignLhs* > (), yystack_[0].value.as< AssignRhs* > ()); }
#line 923 "parser.cc" // lalr1.cc:847
    break;

  case 16:
#line 163 "parser.yy" // lalr1.cc:847
    {// //std::cout << " READ " << std::endl;
      yylhs.value.as< Statement * > () = new ReadStatement(yystack_[0].value.as< AssignLhs* > ()); }
#line 930 "parser.cc" // lalr1.cc:847
    break;

  case 17:
#line 166 "parser.yy" // lalr1.cc:847
    {// //std::cout << " FREE " << std::endl;
      yylhs.value.as< Statement * > () = new FreeStatement(yystack_[0].value.as< Expression * > ()); }
#line 937 "parser.cc" // lalr1.cc:847
    break;

  case 18:
#line 169 "parser.yy" // lalr1.cc:847
    {// //std::cout << " EXIT " << std::endl;
      yylhs.value.as< Statement * > () = new ExitStatement(yystack_[0].value.as< Expression * > ()); }
#line 944 "parser.cc" // lalr1.cc:847
    break;

  case 19:
#line 172 "parser.yy" // lalr1.cc:847
    {// //std::cout << " PRINT " << std::endl;
      yylhs.value.as< Statement * > () = new PrintStatement(yystack_[0].value.as< Expression * > ()); }
#line 951 "parser.cc" // lalr1.cc:847
    break;

  case 20:
#line 175 "parser.yy" // lalr1.cc:847
    {// //std::cout << " PRINTLN " << std::endl;
      yylhs.value.as< Statement * > () = new PrintlnStatement(yystack_[0].value.as< Expression * > ()); }
#line 958 "parser.cc" // lalr1.cc:847
    break;

  case 21:
#line 178 "parser.yy" // lalr1.cc:847
    {// //std::cout << " BEGIN " << std::endl;
      yylhs.value.as< Statement * > () = new BeginStatement(yystack_[1].value.as< StatSeq* > ()); }
#line 965 "parser.cc" // lalr1.cc:847
    break;

  case 22:
#line 181 "parser.yy" // lalr1.cc:847
    {// //std::cout << " IF " << std::endl;
      yylhs.value.as< Statement * > () = new IfStatement(yystack_[5].value.as< Expression * > (), yystack_[3].value.as< StatSeq* > (), yystack_[1].value.as< StatSeq* > ());  }
#line 972 "parser.cc" // lalr1.cc:847
    break;

  case 23:
#line 184 "parser.yy" // lalr1.cc:847
    { ////std::cout << " WHILE " << std::endl;
      yylhs.value.as< Statement * > () = new WhileStatement(yystack_[3].value.as< Expression * > (), yystack_[1].value.as< StatSeq* > ()); }
#line 979 "parser.cc" // lalr1.cc:847
    break;

  case 24:
#line 189 "parser.yy" // lalr1.cc:847
    { //std::cout << " ASSIGN LHS " << std::endl;
      yylhs.value.as< AssignLhs* > () = dynamic_cast<AssignLhs*>(yystack_[0].value.as< Identifier* > ()); }
#line 986 "parser.cc" // lalr1.cc:847
    break;

  case 25:
#line 192 "parser.yy" // lalr1.cc:847
    { //std::cout << " ASSIGN LHS " << std::endl;
      yylhs.value.as< AssignLhs* > () = yystack_[0].value.as< AssignLhs* > (); }
#line 993 "parser.cc" // lalr1.cc:847
    break;

  case 26:
#line 195 "parser.yy" // lalr1.cc:847
    { //std::cout << " ASSIGN LHS " << std::endl;
      yylhs.value.as< AssignLhs* > () = yystack_[0].value.as< AssignLhs* > (); }
#line 1000 "parser.cc" // lalr1.cc:847
    break;

  case 27:
#line 200 "parser.yy" // lalr1.cc:847
    { //std::cout << " ASSIGN RHS " << std::endl; 
      yylhs.value.as< AssignRhs* > () = dynamic_cast<AssignRhs*>(yystack_[0].value.as< Expression * > ()); }
#line 1007 "parser.cc" // lalr1.cc:847
    break;

  case 28:
#line 203 "parser.yy" // lalr1.cc:847
    { //std::cout << " ASSIGN RHS " << std::endl; 
      yylhs.value.as< AssignRhs* > () = yystack_[0].value.as< AssignRhs* > (); }
#line 1014 "parser.cc" // lalr1.cc:847
    break;

  case 29:
#line 206 "parser.yy" // lalr1.cc:847
    { //std::cout << " ASSIGN RHS " << std::endl; 
      yylhs.value.as< AssignRhs* > () = new NewPair(yystack_[3].value.as< Expression * > (), yystack_[1].value.as< Expression * > ()); }
#line 1021 "parser.cc" // lalr1.cc:847
    break;

  case 30:
#line 209 "parser.yy" // lalr1.cc:847
    { //std::cout << " ASSIGN RHS " << std::endl; 
      yylhs.value.as< AssignRhs* > () = yystack_[0].value.as< AssignRhs* > (); }
#line 1028 "parser.cc" // lalr1.cc:847
    break;

  case 31:
#line 212 "parser.yy" // lalr1.cc:847
    { //std::cout << " ASSIGN RHS " << std::endl; 
      yylhs.value.as< AssignRhs* > () = new FunctionCall(yystack_[2].value.as< Identifier* > ()); }
#line 1035 "parser.cc" // lalr1.cc:847
    break;

  case 32:
#line 215 "parser.yy" // lalr1.cc:847
    { //std::cout << " ASSIGN RHS " << std::endl; 
      yylhs.value.as< AssignRhs* > () = new FunctionCall(yystack_[3].value.as< Identifier* > (), yystack_[1].value.as< ExpressionList* > ()); }
#line 1042 "parser.cc" // lalr1.cc:847
    break;

  case 33:
#line 220 "parser.yy" // lalr1.cc:847
    { //std::cout << " ARG LIST SEQ BASE " << //std::cout;
      yylhs.value.as< ExpressionList* > () = new ExpressionList();
      yylhs.value.as< ExpressionList* > ()->push_back(yystack_[0].value.as< Expression * > ());}
#line 1050 "parser.cc" // lalr1.cc:847
    break;

  case 34:
#line 224 "parser.yy" // lalr1.cc:847
    { //std::cout << " ARG LIST SEQ " << std::endl;
      std::swap(yylhs.value.as< ExpressionList* > (), yystack_[2].value.as< ExpressionList* > ());
      yylhs.value.as< ExpressionList* > ()->push_back(yystack_[0].value.as< Expression * > ()); }
#line 1058 "parser.cc" // lalr1.cc:847
    break;

  case 35:
#line 230 "parser.yy" // lalr1.cc:847
    { //std::cout << " PAIR ELEM " << std::endl; 
      yylhs.value.as< AssignRhs* > () = new PairElem(true, yystack_[0].value.as< Expression * > ()); }
#line 1065 "parser.cc" // lalr1.cc:847
    break;

  case 36:
#line 233 "parser.yy" // lalr1.cc:847
    { //std::cout << " PAIR ELEM " << std::endl; 
      yylhs.value.as< AssignRhs* > () = new PairElem(false, yystack_[0].value.as< Expression * > ()); }
#line 1072 "parser.cc" // lalr1.cc:847
    break;

  case 37:
#line 238 "parser.yy" // lalr1.cc:847
    { //std::cout << " PAIR ELEM " << std::endl; 
      yylhs.value.as< AssignLhs* > () = new PairElem(true, yystack_[0].value.as< Expression * > ()); }
#line 1079 "parser.cc" // lalr1.cc:847
    break;

  case 38:
#line 241 "parser.yy" // lalr1.cc:847
    { //std::cout << " PAIR ELEM " << std::endl; 
      yylhs.value.as< AssignLhs* > () = new PairElem(false, yystack_[0].value.as< Expression * > ()); }
#line 1086 "parser.cc" // lalr1.cc:847
    break;

  case 39:
#line 246 "parser.yy" // lalr1.cc:847
    { //std::cout << " TYPE " << std::endl; 
      yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > (); }
#line 1093 "parser.cc" // lalr1.cc:847
    break;

  case 40:
#line 249 "parser.yy" // lalr1.cc:847
    { //std::cout << " TYPE " << std::endl; 
      yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > (); }
#line 1100 "parser.cc" // lalr1.cc:847
    break;

  case 41:
#line 252 "parser.yy" // lalr1.cc:847
    { //std::cout << " TYPE " << std::endl; 
      yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > (); }
#line 1107 "parser.cc" // lalr1.cc:847
    break;

  case 42:
#line 257 "parser.yy" // lalr1.cc:847
    { //std::cout << " INTEGER TYPE " << std::endl;
      yylhs.value.as< Type* > () = new IntegerType(); }
#line 1114 "parser.cc" // lalr1.cc:847
    break;

  case 43:
#line 260 "parser.yy" // lalr1.cc:847
    { //std::cout << " BOOL TYPE " << std::endl;
      yylhs.value.as< Type* > () = new BoolType(); }
#line 1121 "parser.cc" // lalr1.cc:847
    break;

  case 44:
#line 263 "parser.yy" // lalr1.cc:847
    { //std::cout << " CHAR TYPE " << std::endl;
      yylhs.value.as< Type* > () = new CharType(); }
#line 1128 "parser.cc" // lalr1.cc:847
    break;

  case 45:
#line 266 "parser.yy" // lalr1.cc:847
    { //std::cout << " STRING TYPE " << std::endl;
      yylhs.value.as< Type* > () = new StringType(); }
#line 1135 "parser.cc" // lalr1.cc:847
    break;

  case 46:
#line 271 "parser.yy" // lalr1.cc:847
    { //std::cout << " ARRAY TYPE " << std::endl;
    yylhs.value.as< Type* > () = new ArrayType(yystack_[2].value.as< Type* > ()); }
#line 1142 "parser.cc" // lalr1.cc:847
    break;

  case 47:
#line 276 "parser.yy" // lalr1.cc:847
    { //std::cout << " PAIR TYPE " << std::endl;
    yylhs.value.as< Type* > () = new PairType(yystack_[3].value.as< Type* > (), yystack_[1].value.as< Type* > ()); }
#line 1149 "parser.cc" // lalr1.cc:847
    break;

  case 48:
#line 281 "parser.yy" // lalr1.cc:847
    { //std::cout << " PAIR ELEM TYPE " << std::endl; 
      yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > (); }
#line 1156 "parser.cc" // lalr1.cc:847
    break;

  case 49:
#line 284 "parser.yy" // lalr1.cc:847
    { //std::cout << " PAIR ELEM TYPE " << std::endl; 
      yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > (); }
#line 1163 "parser.cc" // lalr1.cc:847
    break;

  case 50:
#line 287 "parser.yy" // lalr1.cc:847
    { //std::cout << " PAIR ELEM TYPE " << std::endl; 
       yylhs.value.as< Type* > () = new PairKeyword(); }
#line 1170 "parser.cc" // lalr1.cc:847
    break;

  case 51:
#line 294 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR " << std::endl; 
      yylhs.value.as< Expression * > () = yystack_[0].value.as< Expression * > (); }
#line 1177 "parser.cc" // lalr1.cc:847
    break;

  case 52:
#line 297 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR " << std::endl; 
      yylhs.value.as< Expression * > () = yystack_[0].value.as< Expression * > (); }
#line 1184 "parser.cc" // lalr1.cc:847
    break;

  case 53:
#line 300 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR " << std::endl; 
      yylhs.value.as< Expression * > () = yystack_[0].value.as< Expression * > (); }
#line 1191 "parser.cc" // lalr1.cc:847
    break;

  case 54:
#line 303 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR " << std::endl; 
      yylhs.value.as< Expression * > () = yystack_[0].value.as< Expression * > (); }
#line 1198 "parser.cc" // lalr1.cc:847
    break;

  case 55:
#line 306 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR " << std::endl; 
      yylhs.value.as< Expression * > () = yystack_[0].value.as< Expression * > (); }
#line 1205 "parser.cc" // lalr1.cc:847
    break;

  case 56:
#line 309 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR " << std::endl; 
      yylhs.value.as< Expression * > () = yystack_[0].value.as< Identifier* > (); }
#line 1212 "parser.cc" // lalr1.cc:847
    break;

  case 57:
#line 312 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR " << std::endl; 
      yylhs.value.as< Expression * > () = yystack_[0].value.as< Expression * > (); }
#line 1219 "parser.cc" // lalr1.cc:847
    break;

  case 58:
#line 315 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR " << std::endl; 
      yylhs.value.as< Expression * > () = yystack_[0].value.as< Expression * > (); }
#line 1226 "parser.cc" // lalr1.cc:847
    break;

  case 59:
#line 318 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR " << std::endl; 
      yylhs.value.as< Expression * > () = yystack_[0].value.as< Expression * > (); }
#line 1233 "parser.cc" // lalr1.cc:847
    break;

  case 60:
#line 321 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR " << std::endl; 
      yylhs.value.as< Expression * > () = yystack_[1].value.as< Expression * > (); }
#line 1240 "parser.cc" // lalr1.cc:847
    break;

  case 61:
#line 327 "parser.yy" // lalr1.cc:847
    { //std::cout << " BANG UNARY " << std::endl;
      yylhs.value.as< Expression * > () = new UnaryOperator(yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1247 "parser.cc" // lalr1.cc:847
    break;

  case 62:
#line 330 "parser.yy" // lalr1.cc:847
    { //std::cout << " LEN UNARY " << std::endl;
      yylhs.value.as< Expression * > () = new UnaryOperator(yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1254 "parser.cc" // lalr1.cc:847
    break;

  case 63:
#line 333 "parser.yy" // lalr1.cc:847
    { //std::cout << " ORD UNARY " << std::endl;
      yylhs.value.as< Expression * > () = new UnaryOperator(yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1261 "parser.cc" // lalr1.cc:847
    break;

  case 64:
#line 336 "parser.yy" // lalr1.cc:847
    { //std::cout << " CHR ORD " << std::endl;
      yylhs.value.as< Expression * > () = new UnaryOperator(yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1268 "parser.cc" // lalr1.cc:847
    break;

  case 65:
#line 339 "parser.yy" // lalr1.cc:847
    { //std::cout << " MINUS UNARY " << std::endl;
      yylhs.value.as< Expression * > () = new UnaryOperator(yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1275 "parser.cc" // lalr1.cc:847
    break;

  case 66:
#line 344 "parser.yy" // lalr1.cc:847
    { //std::cout << " STAR BIN " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1282 "parser.cc" // lalr1.cc:847
    break;

  case 67:
#line 347 "parser.yy" // lalr1.cc:847
    { //std::cout << " SLASH BIN " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1289 "parser.cc" // lalr1.cc:847
    break;

  case 68:
#line 350 "parser.yy" // lalr1.cc:847
    { //std::cout << " MODULO BIN " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1296 "parser.cc" // lalr1.cc:847
    break;

  case 69:
#line 353 "parser.yy" // lalr1.cc:847
    { //std::cout << " PLUS BIN " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1303 "parser.cc" // lalr1.cc:847
    break;

  case 70:
#line 356 "parser.yy" // lalr1.cc:847
    { //std::cout << " MINUS BIN " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1310 "parser.cc" // lalr1.cc:847
    break;

  case 71:
#line 359 "parser.yy" // lalr1.cc:847
    { //std::cout << " GREATER BIN " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1317 "parser.cc" // lalr1.cc:847
    break;

  case 72:
#line 362 "parser.yy" // lalr1.cc:847
    { //std::cout << " GREATEREQUALS BIN " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1324 "parser.cc" // lalr1.cc:847
    break;

  case 73:
#line 365 "parser.yy" // lalr1.cc:847
    { //std::cout << " LESS BIN " << std::endl; 
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1331 "parser.cc" // lalr1.cc:847
    break;

  case 74:
#line 368 "parser.yy" // lalr1.cc:847
    { //std::cout << " LESSEQUALS BIN " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1338 "parser.cc" // lalr1.cc:847
    break;

  case 75:
#line 371 "parser.yy" // lalr1.cc:847
    { std::cout <<"token : " << yystack_[1].value.as< int > () << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1345 "parser.cc" // lalr1.cc:847
    break;

  case 76:
#line 374 "parser.yy" // lalr1.cc:847
    { //std::cout << " NOTEQUALS BIN " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1352 "parser.cc" // lalr1.cc:847
    break;

  case 77:
#line 377 "parser.yy" // lalr1.cc:847
    { //std::cout << " LOGAND " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1359 "parser.cc" // lalr1.cc:847
    break;

  case 78:
#line 380 "parser.yy" // lalr1.cc:847
    { //std::cout << " LOGOR " << std::endl;
      yylhs.value.as< Expression * > () = new BinaryOperator(yystack_[2].value.as< Expression * > (), yystack_[1].value.as< int > (), yystack_[0].value.as< Expression * > ()); }
#line 1366 "parser.cc" // lalr1.cc:847
    break;

  case 79:
#line 385 "parser.yy" // lalr1.cc:847
    { //std::cout << " IDENT " << std::endl;
      yylhs.value.as< Identifier* > () = new Identifier(yystack_[0].value.as< std::string > ()); }
#line 1373 "parser.cc" // lalr1.cc:847
    break;

  case 80:
#line 390 "parser.yy" // lalr1.cc:847
    { //std::cout << " ARRAY ELEM " << std::endl;
      yylhs.value.as< Expression * > () = new ArrayElem(yystack_[1].value.as< Identifier* > (), yystack_[0].value.as< ExpressionList* > ()); }
#line 1380 "parser.cc" // lalr1.cc:847
    break;

  case 81:
#line 395 "parser.yy" // lalr1.cc:847
    { //std::cout << " ARRAY ELEM " << std::endl;
      yylhs.value.as< AssignLhs* > () = new ArrayElem(yystack_[1].value.as< Identifier* > (), yystack_[0].value.as< ExpressionList* > ()); }
#line 1387 "parser.cc" // lalr1.cc:847
    break;

  case 82:
#line 400 "parser.yy" // lalr1.cc:847
    { //std::cout << " ARRAY INDEX SEQ BASE " << std::endl;
      yylhs.value.as< ExpressionList* > () = new ExpressionList(); 
      yylhs.value.as< ExpressionList* > ()->push_back(yystack_[1].value.as< Expression * > ()); }
#line 1395 "parser.cc" // lalr1.cc:847
    break;

  case 83:
#line 404 "parser.yy" // lalr1.cc:847
    { //std::cout << " ARRAY INDEX SEQ " << std::endl;
      std::swap(yylhs.value.as< ExpressionList* > (), yystack_[3].value.as< ExpressionList* > ());
      yylhs.value.as< ExpressionList* > ()->push_back(yystack_[1].value.as< Expression * > ()); }
#line 1403 "parser.cc" // lalr1.cc:847
    break;

  case 84:
#line 410 "parser.yy" // lalr1.cc:847
    { //std::cout << " INT LITER " << std::endl;
       yylhs.value.as< Expression * > () = new Number(yystack_[1].value.as< int > () * yystack_[0].value.as< int > ()); }
#line 1410 "parser.cc" // lalr1.cc:847
    break;

  case 85:
#line 415 "parser.yy" // lalr1.cc:847
    { yylhs.value.as< int > () = 1; }
#line 1416 "parser.cc" // lalr1.cc:847
    break;

  case 86:
#line 417 "parser.yy" // lalr1.cc:847
    { yylhs.value.as< int > () = 1; }
#line 1422 "parser.cc" // lalr1.cc:847
    break;

  case 87:
#line 421 "parser.yy" // lalr1.cc:847
    { //std::cout << " BOOL LITER " << std::endl;
      yylhs.value.as< Expression * > () = new Boolean(true); }
#line 1429 "parser.cc" // lalr1.cc:847
    break;

  case 88:
#line 424 "parser.yy" // lalr1.cc:847
    { //std::cout << " BOOL LITER " << std::endl;
      yylhs.value.as< Expression * > () = new Boolean(false); }
#line 1436 "parser.cc" // lalr1.cc:847
    break;

  case 89:
#line 429 "parser.yy" // lalr1.cc:847
    { //std::cout << " CHER LITER " << std::endl;
      yylhs.value.as< Expression * > () = new Char(yystack_[0].value.as< char > ());}
#line 1443 "parser.cc" // lalr1.cc:847
    break;

  case 90:
#line 434 "parser.yy" // lalr1.cc:847
    { //std::cout << " STRING LITER " << std::endl;
      yylhs.value.as< Expression * > () = new String(yystack_[0].value.as< std::string > ()); }
#line 1450 "parser.cc" // lalr1.cc:847
    break;

  case 91:
#line 439 "parser.yy" // lalr1.cc:847
    { //std::cout << " ARRAY LITER " << std::endl;
    yylhs.value.as< AssignRhs* > () = new ArrayLiter(yystack_[1].value.as< ExpressionList* > ()); }
#line 1457 "parser.cc" // lalr1.cc:847
    break;

  case 92:
#line 444 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR LIST SEQ BASE " << std::endl;
		yylhs.value.as< ExpressionList* > () = new ExpressionList();
	  }
#line 1465 "parser.cc" // lalr1.cc:847
    break;

  case 93:
#line 448 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR LIST SEQ BASE " << std::endl;
      yylhs.value.as< ExpressionList* > () = new ExpressionList();
      yylhs.value.as< ExpressionList* > ()->push_back(yystack_[0].value.as< Expression * > ()); }
#line 1473 "parser.cc" // lalr1.cc:847
    break;

  case 94:
#line 452 "parser.yy" // lalr1.cc:847
    { //std::cout << " EXPR LIST SEQ " << std::endl;
      std::swap(yylhs.value.as< ExpressionList* > (), yystack_[2].value.as< ExpressionList* > ());
      yylhs.value.as< ExpressionList* > ()->push_back(yystack_[0].value.as< Expression * > ()); }
#line 1481 "parser.cc" // lalr1.cc:847
    break;

  case 95:
#line 458 "parser.yy" // lalr1.cc:847
    { //std::cout << " NULL PAIR LITER " << std::endl;
      yylhs.value.as< Expression * > () = new Null(); }
#line 1488 "parser.cc" // lalr1.cc:847
    break;


#line 1492 "parser.cc" // lalr1.cc:847
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


  const signed char parser::yypact_ninf_ = -52;

  const signed char parser::yytable_ninf_ = -86;

  const short int
  parser::yypact_[] =
  {
      20,   -52,    16,   174,   -52,   174,   258,   258,   -52,   258,
     258,   258,   -15,   -52,   -52,   -52,   -52,   258,   258,   -12,
     258,   258,   -52,   -52,     3,   -52,     7,   -52,   -25,   -52,
     -52,   -52,     2,   -52,     4,   -25,   -52,   -52,   -52,   -52,
     258,   258,   258,   258,   258,   258,   -52,   -52,   172,   -52,
     -52,     2,   -52,   -52,   -20,   -52,   -52,   -52,   -52,   293,
     409,   409,   409,    43,   409,   409,   -52,   409,   409,   -52,
     174,   202,    -3,   -13,   258,    14,   -52,    35,   -52,   -52,
     -52,   -52,   -52,   371,   174,   258,   258,   258,   258,   258,
     258,   258,   258,   258,   258,   258,   258,   258,    14,   -52,
     174,   -15,    23,    29,    30,    28,   -52,    21,    83,    52,
     258,   258,   -52,   -52,   409,   -52,   -52,   202,    50,   329,
     258,   -52,    10,   275,   275,    25,   -52,   -52,    25,    25,
      25,    25,    25,    25,    25,    25,    11,    43,    56,   409,
       0,   258,   409,   409,   -52,    84,   -21,   -52,   -25,   -52,
     350,   174,   -52,    58,   237,   -52,   258,   306,   174,    90,
     110,   -52,   -52,    -2,   -52,   -52,   -19,   409,   409,   258,
       5,   174,   -52,   -52,   -52,   258,   390,   -52,     6,   409,
     -52,   -52
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     3,     0,     0,     1,     0,    85,    85,    12,    85,
      85,    85,     0,    42,    43,    44,    45,    85,    85,     0,
      85,    85,    79,     4,     0,    10,     0,    26,     0,    39,
      40,    41,    24,    25,     0,     0,    87,    88,    95,    86,
      85,    85,    85,    85,    85,    85,    90,    89,     0,    58,
      59,    56,    57,    51,     0,    52,    53,    54,    55,     0,
      17,    18,    13,     0,    19,    20,    16,    37,    38,     2,
       0,    85,     0,     0,    85,    81,    21,     0,    65,    61,
      62,    63,    64,     0,     0,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    80,    84,
       0,    50,     0,    48,    49,     0,    11,     0,    92,     0,
      85,    85,    15,    30,    27,    28,    46,    85,     0,     0,
      85,    60,     0,    78,    77,    66,    67,    68,    69,    70,
      73,    74,    71,    72,    75,    76,     0,     0,     0,    93,
       0,    85,    35,    36,    14,     0,     0,     7,     0,    82,
       0,     0,    23,     0,    85,    91,    85,     0,     0,     0,
       0,     9,    83,     0,    47,    31,     0,    33,    94,    85,
       0,     0,     8,    22,    32,    85,     0,     5,     0,    34,
      29,     6
  };

  const signed char
  parser::yypgoto_[] =
  {
     -52,   -52,   -52,   -52,   -52,   -51,    13,    40,    92,    -5,
     -52,   -52,   -52,    -1,   -44,   -43,   -52,   -18,    -6,   -52,
     -52,    22,   -52,   -52,    67,   -52,   -52,   -52,   -52,   -52,
     -52,   -52,   -52
  };

  const short int
  parser::yydefgoto_[] =
  {
      -1,     2,     3,    23,   146,   147,    24,    25,    26,   112,
     166,   113,    27,    35,    29,    30,    31,   105,   114,    49,
      50,    51,    52,    33,    75,    53,    54,    55,    56,    57,
     115,   140,    58
  };

  const short int
  parser::yytable_[] =
  {
      48,    59,    28,    60,    61,    62,   173,    69,    76,   177,
     181,    64,    65,   117,    67,    68,     4,   151,    34,   103,
     104,    72,   152,     1,   159,    32,   174,    32,   160,    63,
     175,   118,    22,    71,    78,    79,    80,    81,    82,    83,
      99,    32,    20,    21,   116,    22,    70,   155,    74,   156,
      73,    70,    70,    70,    70,    88,    89,    77,    70,    70,
     120,   117,   102,   101,    13,    14,    15,    16,   119,    72,
      12,    13,    14,    15,    16,   -39,   -40,   137,    22,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,    32,   103,   104,   145,   141,   122,    36,    37,
     154,   158,   139,   164,   142,   143,    32,   171,    38,   172,
     106,    66,   144,   136,   150,    39,    40,   148,    98,   153,
       0,     0,    32,    41,    42,    43,    44,    45,     0,   138,
      12,    13,    14,    15,    16,   157,   102,     0,     0,     0,
      22,    46,    47,   -85,     0,     0,     0,     0,   167,     0,
     168,     0,     0,     0,     0,     0,     0,     0,     0,   148,
       0,     0,     0,   176,   163,     0,     0,     0,     0,   179,
     161,   170,     0,    32,     0,     0,     0,     5,    84,     6,
      32,     0,     0,     7,   178,     0,     8,     9,    10,     0,
       0,     0,    11,    32,    12,    13,    14,    15,    16,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,     0,     0,     0,     0,     0,    36,    37,     0,
       0,   107,     0,     0,    17,    18,    19,    38,    20,    21,
       0,    22,     0,     0,    39,    40,     0,     0,     0,     0,
       0,     0,    41,    42,    43,    44,    45,     0,   108,     0,
       0,     0,    36,    37,     0,   109,   110,   111,     0,    22,
      46,    47,    38,     0,     0,     0,     0,     0,     0,    39,
      40,     0,     0,    36,    37,     0,     0,    41,    42,    43,
      44,    45,   165,    38,     0,     0,     0,     0,     0,     0,
      39,    40,     0,     0,    22,    46,    47,     0,    41,    42,
      43,    44,    45,   100,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    22,    46,    47,     0,     0,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   169,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,     0,
       0,     0,     0,     0,     0,     0,   149,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
       0,     0,     0,     0,     0,     0,     0,   162,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,     0,     0,     0,     0,     0,   121,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
       0,     0,     0,     0,     0,   180,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97
  };

  const short int
  parser::yycheck_[] =
  {
       6,     7,     3,     9,    10,    11,     8,     4,     4,     4,
       4,    17,    18,    26,    20,    21,     0,     7,     5,    63,
      63,    46,    11,     3,    45,     3,    45,     5,    49,    44,
      49,    44,    57,    26,    40,    41,    42,    43,    44,    45,
      60,    19,    54,    55,    47,    57,    48,    47,    46,    49,
      28,    48,    48,    48,    48,    30,    31,    35,    48,    48,
      46,    26,    63,    20,    21,    22,    23,    24,    74,    46,
      20,    21,    22,    23,    24,    46,    46,    49,    57,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    70,   137,   137,    45,    44,    84,    15,    16,
      44,    17,   108,    45,   110,   111,    84,    17,    25,   160,
      70,    19,   117,   100,   120,    32,    33,   118,    51,   137,
      -1,    -1,   100,    40,    41,    42,    43,    44,    -1,   107,
      20,    21,    22,    23,    24,   141,   137,    -1,    -1,    -1,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,   154,    -1,
     156,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   160,
      -1,    -1,    -1,   169,   151,    -1,    -1,    -1,    -1,   175,
     148,   158,    -1,   151,    -1,    -1,    -1,     3,     6,     5,
     158,    -1,    -1,     9,   171,    -1,    12,    13,    14,    -1,
      -1,    -1,    18,   171,    20,    21,    22,    23,    24,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    -1,    -1,    -1,    -1,    -1,    15,    16,    -1,
      -1,    19,    -1,    -1,    50,    51,    52,    25,    54,    55,
      -1,    57,    -1,    -1,    32,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    44,    -1,    46,    -1,
      -1,    -1,    15,    16,    -1,    53,    54,    55,    -1,    57,
      58,    59,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    -1,    -1,    15,    16,    -1,    -1,    40,    41,    42,
      43,    44,    45,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    33,    -1,    -1,    57,    58,    59,    -1,    40,    41,
      42,    43,    44,    10,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    57,    58,    59,    -1,    -1,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    49,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    -1,    -1,    -1,    -1,    -1,    45,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      -1,    -1,    -1,    -1,    -1,    45,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,    64,    65,     0,     3,     5,     9,    12,    13,
      14,    18,    20,    21,    22,    23,    24,    50,    51,    52,
      54,    55,    57,    66,    69,    70,    71,    75,    76,    77,
      78,    79,    84,    86,    69,    76,    15,    16,    25,    32,
      33,    40,    41,    42,    43,    44,    58,    59,    81,    82,
      83,    84,    85,    88,    89,    90,    91,    92,    95,    81,
      81,    81,    81,    44,    81,    81,    71,    81,    81,     4,
      48,    26,    46,    84,    46,    87,     4,    84,    81,    81,
      81,    81,    81,    81,     6,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    87,    60,
      10,    20,    76,    77,    78,    80,    70,    19,    46,    53,
      54,    55,    72,    74,    81,    93,    47,    26,    44,    81,
      46,    45,    69,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    69,    49,    84,    81,
      94,    44,    81,    81,    72,    45,    67,    68,    76,    47,
      81,     7,    11,    80,    44,    47,    49,    81,    17,    45,
      49,    84,    47,    69,    45,    45,    73,    81,    81,    49,
      69,    17,    68,     8,    45,    49,    81,     4,    69,    81,
      45,     4
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
      85,    86,    87,    87,    88,    89,    89,    90,    90,    91,
      92,    93,    94,    94,    94,    95
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
       2,     2,     3,     4,     2,     0,     1,     1,     1,     1,
       1,     3,     0,     1,     3,     1
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
  "array_elem_exp", "array_elem_lhs", "array_index", "int_liter",
  "int_sign", "bool_liter", "char_liter", "str_liter", "array_liter",
  "expr_list", "pair_liter", YY_NULLPTR
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
     389,   394,   399,   403,   409,   415,   416,   420,   423,   428,
     433,   438,   444,   447,   451,   457
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
#line 2044 "parser.cc" // lalr1.cc:1155
#line 467 "parser.yy" // lalr1.cc:1156


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
