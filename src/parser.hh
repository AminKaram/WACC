// A Bison parser, made by GNU Bison 3.0.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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

/**
 ** \file parser.hh
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_YY_PARSER_HH_INCLUDED
# define YY_YY_PARSER_HH_INCLUDED
// //                    "%code requires" blocks.
#line 10 "parser.yy" // lalr1.cc:372

  #include <iostream>
  #include <string>
  #include <typeinfo>
  #include <vector>
  #include "astnode.hh"
  class ParsingDriver;
  bool containsRetOrExit(StatSeq*);

#line 54 "parser.hh" // lalr1.cc:372

# include <cassert>
# include <vector>
# include <iostream>
# include <stdexcept>
# include <string>
# include "stack.hh"
# include "location.hh"
#include <typeinfo>
#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif


namespace yy {
#line 130 "parser.hh" // lalr1.cc:372



  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
      : yytname_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    variant (const T& t)
      : yytname_ (typeid (T).name ())
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (t);
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {
      YYASSERT (!yytname_);
    }

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    build ()
    {
      YYASSERT (!yytname_);
      YYASSERT (sizeof (T) <= S);
      yytname_ = typeid (T).name ();
      return *new (yyas_<T> ()) T;
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    build (const T& t)
    {
      YYASSERT (!yytname_);
      YYASSERT (sizeof (T) <= S);
      yytname_ = typeid (T).name ();
      return *new (yyas_<T> ()) T (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      YYASSERT (yytname_ == typeid (T).name ());
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      YYASSERT (yytname_ == typeid (T).name ());
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsability.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      YYASSERT (yytname_);
      YYASSERT (yytname_ == other.yytname_);
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
      build<T> ();
      swap<T> (other);
      other.destroy<T> ();
    }

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      build<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytname_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator=(const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const char *yytname_;
  };


  /// A Bison parser.
  class parser
  {
  public:
#ifndef YYSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // assign_lhs
      // pair_elem_lhs
      // array_elem_lhs
      char dummy1[sizeof(AssignLhs*)];

      // assign_rhs
      // pair_elem_rhs
      // array_liter
      char dummy2[sizeof(AssignRhs*)];

      // expr
      // unary_op
      // binary_op
      // array_elem_exp
      // int_liter
      // bool_liter
      // char_liter
      // str_liter
      // pair_liter
      char dummy3[sizeof(Expression *)];

      // arg_list
      // array_index
      // expr_list
      char dummy4[sizeof(ExpressionList*)];

      // func_list
      char dummy5[sizeof(FunctionDecList*)];

      // function_declaration
      char dummy6[sizeof(FunctionDeclaration*)];

      // ident
      char dummy7[sizeof(Identifier*)];

      // statement_seq
      char dummy8[sizeof(StatSeq*)];

      // statement
      char dummy9[sizeof(Statement *)];

      // type
      // base_type
      // array_type
      // pair_type
      // pair_elem_type
      char dummy10[sizeof(Type*)];

      // param
      char dummy11[sizeof(VariableDeclaration*)];

      // param_list
      char dummy12[sizeof(VariableList*)];

      // CHARLIT
      char dummy13[sizeof(char)];

      // ASSIGN
      // LOGOR
      // LOGAND
      // STAR
      // SLASH
      // MODULO
      // PLUS
      // MINUS
      // LESS
      // LESSEQUALS
      // GREATER
      // GREATEREQUALS
      // EQUALS
      // NOTEQUALS
      // BANG
      // LEN
      // ORD
      // CHR
      // INTEGER
      // int_sign
      char dummy14[sizeof(int)];

      // IDENTIFIER
      // STRINGLIT
      char dummy15[sizeof(std::string)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m);
      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        TOK_ENDF = 0,
        TOK_BEGIN = 258,
        TOK_END = 259,
        TOK_IF = 260,
        TOK_THEN = 261,
        TOK_ELSE = 262,
        TOK_FI = 263,
        TOK_WHILE = 264,
        TOK_DO = 265,
        TOK_DONE = 266,
        TOK_SKIP = 267,
        TOK_FREE = 268,
        TOK_EXIT = 269,
        TOK_TRUE = 270,
        TOK_FALSE = 271,
        TOK_IS = 272,
        TOK_RETURN = 273,
        TOK_CALL = 274,
        TOK_PAIR = 275,
        TOK_INT = 276,
        TOK_BOOL = 277,
        TOK_CHAR = 278,
        TOK_STRING = 279,
        TOK_NULLTOKEN = 280,
        TOK_ASSIGN = 281,
        TOK_LOGOR = 282,
        TOK_LOGAND = 283,
        TOK_STAR = 284,
        TOK_SLASH = 285,
        TOK_MODULO = 286,
        TOK_PLUS = 287,
        TOK_MINUS = 288,
        TOK_LESS = 289,
        TOK_LESSEQUALS = 290,
        TOK_GREATER = 291,
        TOK_GREATEREQUALS = 292,
        TOK_EQUALS = 293,
        TOK_NOTEQUALS = 294,
        TOK_BANG = 295,
        TOK_LEN = 296,
        TOK_ORD = 297,
        TOK_CHR = 298,
        TOK_LPAREN = 299,
        TOK_RPAREN = 300,
        TOK_LSQUARE = 301,
        TOK_RSQUARE = 302,
        TOK_SEMICOLON = 303,
        TOK_COMMA = 304,
        TOK_PRINT = 305,
        TOK_PRINTLN = 306,
        TOK_READ = 307,
        TOK_NEWPAIR = 308,
        TOK_FST = 309,
        TOK_SND = 310,
        TOK_ERROR = 311,
        TOK_IDENTIFIER = 312,
        TOK_STRINGLIT = 313,
        TOK_CHARLIT = 314,
        TOK_INTEGER = 315,
        TOK_UMINUS = 316,
        TOK_UPLUS = 317
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Internal symbol number.
    typedef int symbol_number_type;

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols, and symbols from each type.

  basic_symbol (typename Base::kind_type t, const location_type& l);

  basic_symbol (typename Base::kind_type t, const AssignLhs* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const AssignRhs* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Expression * v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ExpressionList* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const FunctionDecList* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const FunctionDeclaration* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Identifier* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const StatSeq* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Statement * v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Type* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const VariableDeclaration* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const VariableList* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const char v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const int v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l);


      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v,
                    const location_type& l);

      ~basic_symbol ();

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// -1 when this symbol is empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      enum { empty = 0 };

      /// The symbol type.
      /// -1 when this symbol is empty.
      token_number_type type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;

    // Symbol constructors declarations.
    static inline
    symbol_type
    make_ENDF (const location_type& l);

    static inline
    symbol_type
    make_BEGIN (const location_type& l);

    static inline
    symbol_type
    make_END (const location_type& l);

    static inline
    symbol_type
    make_IF (const location_type& l);

    static inline
    symbol_type
    make_THEN (const location_type& l);

    static inline
    symbol_type
    make_ELSE (const location_type& l);

    static inline
    symbol_type
    make_FI (const location_type& l);

    static inline
    symbol_type
    make_WHILE (const location_type& l);

    static inline
    symbol_type
    make_DO (const location_type& l);

    static inline
    symbol_type
    make_DONE (const location_type& l);

    static inline
    symbol_type
    make_SKIP (const location_type& l);

    static inline
    symbol_type
    make_FREE (const location_type& l);

    static inline
    symbol_type
    make_EXIT (const location_type& l);

    static inline
    symbol_type
    make_TRUE (const location_type& l);

    static inline
    symbol_type
    make_FALSE (const location_type& l);

    static inline
    symbol_type
    make_IS (const location_type& l);

    static inline
    symbol_type
    make_RETURN (const location_type& l);

    static inline
    symbol_type
    make_CALL (const location_type& l);

    static inline
    symbol_type
    make_PAIR (const location_type& l);

    static inline
    symbol_type
    make_INT (const location_type& l);

    static inline
    symbol_type
    make_BOOL (const location_type& l);

    static inline
    symbol_type
    make_CHAR (const location_type& l);

    static inline
    symbol_type
    make_STRING (const location_type& l);

    static inline
    symbol_type
    make_NULLTOKEN (const location_type& l);

    static inline
    symbol_type
    make_ASSIGN (const int& v, const location_type& l);

    static inline
    symbol_type
    make_LOGOR (const int& v, const location_type& l);

    static inline
    symbol_type
    make_LOGAND (const int& v, const location_type& l);

    static inline
    symbol_type
    make_STAR (const int& v, const location_type& l);

    static inline
    symbol_type
    make_SLASH (const int& v, const location_type& l);

    static inline
    symbol_type
    make_MODULO (const int& v, const location_type& l);

    static inline
    symbol_type
    make_PLUS (const int& v, const location_type& l);

    static inline
    symbol_type
    make_MINUS (const int& v, const location_type& l);

    static inline
    symbol_type
    make_LESS (const int& v, const location_type& l);

    static inline
    symbol_type
    make_LESSEQUALS (const int& v, const location_type& l);

    static inline
    symbol_type
    make_GREATER (const int& v, const location_type& l);

    static inline
    symbol_type
    make_GREATEREQUALS (const int& v, const location_type& l);

    static inline
    symbol_type
    make_EQUALS (const int& v, const location_type& l);

    static inline
    symbol_type
    make_NOTEQUALS (const int& v, const location_type& l);

    static inline
    symbol_type
    make_BANG (const int& v, const location_type& l);

    static inline
    symbol_type
    make_LEN (const int& v, const location_type& l);

    static inline
    symbol_type
    make_ORD (const int& v, const location_type& l);

    static inline
    symbol_type
    make_CHR (const int& v, const location_type& l);

    static inline
    symbol_type
    make_LPAREN (const location_type& l);

    static inline
    symbol_type
    make_RPAREN (const location_type& l);

    static inline
    symbol_type
    make_LSQUARE (const location_type& l);

    static inline
    symbol_type
    make_RSQUARE (const location_type& l);

    static inline
    symbol_type
    make_SEMICOLON (const location_type& l);

    static inline
    symbol_type
    make_COMMA (const location_type& l);

    static inline
    symbol_type
    make_PRINT (const location_type& l);

    static inline
    symbol_type
    make_PRINTLN (const location_type& l);

    static inline
    symbol_type
    make_READ (const location_type& l);

    static inline
    symbol_type
    make_NEWPAIR (const location_type& l);

    static inline
    symbol_type
    make_FST (const location_type& l);

    static inline
    symbol_type
    make_SND (const location_type& l);

    static inline
    symbol_type
    make_ERROR (const location_type& l);

    static inline
    symbol_type
    make_IDENTIFIER (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_STRINGLIT (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_CHARLIT (const char& v, const location_type& l);

    static inline
    symbol_type
    make_INTEGER (const int& v, const location_type& l);

    static inline
    symbol_type
    make_UMINUS (const location_type& l);

    static inline
    symbol_type
    make_UPLUS (const location_type& l);


    /// Build a parser object.
    parser (ParsingDriver& driver_yyarg);
    virtual ~parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// This class is not copyable.
    parser (const parser&);
    parser& operator= (const parser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yytoken   the lookahead token type, or yyempty_.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         symbol_number_type yytoken) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const signed char yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const short int yytable_[];

  static const short int yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short int yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// "empty" when empty.
      symbol_number_type type_get () const;

      enum { empty = 0 };

      /// The state.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    // Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 448,     ///< Last index in yytable_.
      yynnts_ = 33,  ///< Number of nonterminal symbols.
      yyempty_ = -2,
      yyfinal_ = 4, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 63  ///< Number of tokens.
    };


    // User arguments.
    ParsingDriver& driver;
  };

  // Symbol number corresponding to token number t.
  inline
  parser::token_number_type
  parser::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62
    };
    const unsigned int user_token_number_max_ = 317;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 71: // assign_lhs
      case 75: // pair_elem_lhs
      case 86: // array_elem_lhs
        value.copy< AssignLhs* > (other.value);
        break;

      case 72: // assign_rhs
      case 74: // pair_elem_rhs
      case 93: // array_liter
        value.copy< AssignRhs* > (other.value);
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
        value.copy< Expression * > (other.value);
        break;

      case 73: // arg_list
      case 87: // array_index
      case 94: // expr_list
        value.copy< ExpressionList* > (other.value);
        break;

      case 65: // func_list
        value.copy< FunctionDecList* > (other.value);
        break;

      case 66: // function_declaration
        value.copy< FunctionDeclaration* > (other.value);
        break;

      case 84: // ident
        value.copy< Identifier* > (other.value);
        break;

      case 69: // statement_seq
        value.copy< StatSeq* > (other.value);
        break;

      case 70: // statement
        value.copy< Statement * > (other.value);
        break;

      case 76: // type
      case 77: // base_type
      case 78: // array_type
      case 79: // pair_type
      case 80: // pair_elem_type
        value.copy< Type* > (other.value);
        break;

      case 68: // param
        value.copy< VariableDeclaration* > (other.value);
        break;

      case 67: // param_list
        value.copy< VariableList* > (other.value);
        break;

      case 59: // CHARLIT
        value.copy< char > (other.value);
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
        value.copy< int > (other.value);
        break;

      case 57: // IDENTIFIER
      case 58: // STRINGLIT
        value.copy< std::string > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 71: // assign_lhs
      case 75: // pair_elem_lhs
      case 86: // array_elem_lhs
        value.copy< AssignLhs* > (v);
        break;

      case 72: // assign_rhs
      case 74: // pair_elem_rhs
      case 93: // array_liter
        value.copy< AssignRhs* > (v);
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
        value.copy< Expression * > (v);
        break;

      case 73: // arg_list
      case 87: // array_index
      case 94: // expr_list
        value.copy< ExpressionList* > (v);
        break;

      case 65: // func_list
        value.copy< FunctionDecList* > (v);
        break;

      case 66: // function_declaration
        value.copy< FunctionDeclaration* > (v);
        break;

      case 84: // ident
        value.copy< Identifier* > (v);
        break;

      case 69: // statement_seq
        value.copy< StatSeq* > (v);
        break;

      case 70: // statement
        value.copy< Statement * > (v);
        break;

      case 76: // type
      case 77: // base_type
      case 78: // array_type
      case 79: // pair_type
      case 80: // pair_elem_type
        value.copy< Type* > (v);
        break;

      case 68: // param
        value.copy< VariableDeclaration* > (v);
        break;

      case 67: // param_list
        value.copy< VariableList* > (v);
        break;

      case 59: // CHARLIT
        value.copy< char > (v);
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
        value.copy< int > (v);
        break;

      case 57: // IDENTIFIER
      case 58: // STRINGLIT
        value.copy< std::string > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const AssignLhs* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const AssignRhs* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Expression * v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ExpressionList* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const FunctionDecList* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const FunctionDeclaration* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Identifier* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const StatSeq* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Statement * v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Type* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const VariableDeclaration* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const VariableList* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const char v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const int v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
  parser::basic_symbol<Base>::~basic_symbol ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 71: // assign_lhs
      case 75: // pair_elem_lhs
      case 86: // array_elem_lhs
        value.template destroy< AssignLhs* > ();
        break;

      case 72: // assign_rhs
      case 74: // pair_elem_rhs
      case 93: // array_liter
        value.template destroy< AssignRhs* > ();
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
        value.template destroy< Expression * > ();
        break;

      case 73: // arg_list
      case 87: // array_index
      case 94: // expr_list
        value.template destroy< ExpressionList* > ();
        break;

      case 65: // func_list
        value.template destroy< FunctionDecList* > ();
        break;

      case 66: // function_declaration
        value.template destroy< FunctionDeclaration* > ();
        break;

      case 84: // ident
        value.template destroy< Identifier* > ();
        break;

      case 69: // statement_seq
        value.template destroy< StatSeq* > ();
        break;

      case 70: // statement
        value.template destroy< Statement * > ();
        break;

      case 76: // type
      case 77: // base_type
      case 78: // array_type
      case 79: // pair_type
      case 80: // pair_elem_type
        value.template destroy< Type* > ();
        break;

      case 68: // param
        value.template destroy< VariableDeclaration* > ();
        break;

      case 67: // param_list
        value.template destroy< VariableList* > ();
        break;

      case 59: // CHARLIT
        value.template destroy< char > ();
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
        value.template destroy< int > ();
        break;

      case 57: // IDENTIFIER
      case 58: // STRINGLIT
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 71: // assign_lhs
      case 75: // pair_elem_lhs
      case 86: // array_elem_lhs
        value.move< AssignLhs* > (s.value);
        break;

      case 72: // assign_rhs
      case 74: // pair_elem_rhs
      case 93: // array_liter
        value.move< AssignRhs* > (s.value);
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
        value.move< Expression * > (s.value);
        break;

      case 73: // arg_list
      case 87: // array_index
      case 94: // expr_list
        value.move< ExpressionList* > (s.value);
        break;

      case 65: // func_list
        value.move< FunctionDecList* > (s.value);
        break;

      case 66: // function_declaration
        value.move< FunctionDeclaration* > (s.value);
        break;

      case 84: // ident
        value.move< Identifier* > (s.value);
        break;

      case 69: // statement_seq
        value.move< StatSeq* > (s.value);
        break;

      case 70: // statement
        value.move< Statement * > (s.value);
        break;

      case 76: // type
      case 77: // base_type
      case 78: // array_type
      case 79: // pair_type
      case 80: // pair_elem_type
        value.move< Type* > (s.value);
        break;

      case 68: // param
        value.move< VariableDeclaration* > (s.value);
        break;

      case 67: // param_list
        value.move< VariableList* > (s.value);
        break;

      case 59: // CHARLIT
        value.move< char > (s.value);
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
        value.move< int > (s.value);
        break;

      case 57: // IDENTIFIER
      case 58: // STRINGLIT
        value.move< std::string > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
  parser::by_type::by_type ()
     : type (empty)
  {}

  inline
  parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.type = empty;
  }

  inline
  int
  parser::by_type::type_get () const
  {
    return type;
  }

  inline
  parser::token_type
  parser::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short int
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
  parser::symbol_type
  parser::make_ENDF (const location_type& l)
  {
    return symbol_type (token::TOK_ENDF, l);
  }

  parser::symbol_type
  parser::make_BEGIN (const location_type& l)
  {
    return symbol_type (token::TOK_BEGIN, l);
  }

  parser::symbol_type
  parser::make_END (const location_type& l)
  {
    return symbol_type (token::TOK_END, l);
  }

  parser::symbol_type
  parser::make_IF (const location_type& l)
  {
    return symbol_type (token::TOK_IF, l);
  }

  parser::symbol_type
  parser::make_THEN (const location_type& l)
  {
    return symbol_type (token::TOK_THEN, l);
  }

  parser::symbol_type
  parser::make_ELSE (const location_type& l)
  {
    return symbol_type (token::TOK_ELSE, l);
  }

  parser::symbol_type
  parser::make_FI (const location_type& l)
  {
    return symbol_type (token::TOK_FI, l);
  }

  parser::symbol_type
  parser::make_WHILE (const location_type& l)
  {
    return symbol_type (token::TOK_WHILE, l);
  }

  parser::symbol_type
  parser::make_DO (const location_type& l)
  {
    return symbol_type (token::TOK_DO, l);
  }

  parser::symbol_type
  parser::make_DONE (const location_type& l)
  {
    return symbol_type (token::TOK_DONE, l);
  }

  parser::symbol_type
  parser::make_SKIP (const location_type& l)
  {
    return symbol_type (token::TOK_SKIP, l);
  }

  parser::symbol_type
  parser::make_FREE (const location_type& l)
  {
    return symbol_type (token::TOK_FREE, l);
  }

  parser::symbol_type
  parser::make_EXIT (const location_type& l)
  {
    return symbol_type (token::TOK_EXIT, l);
  }

  parser::symbol_type
  parser::make_TRUE (const location_type& l)
  {
    return symbol_type (token::TOK_TRUE, l);
  }

  parser::symbol_type
  parser::make_FALSE (const location_type& l)
  {
    return symbol_type (token::TOK_FALSE, l);
  }

  parser::symbol_type
  parser::make_IS (const location_type& l)
  {
    return symbol_type (token::TOK_IS, l);
  }

  parser::symbol_type
  parser::make_RETURN (const location_type& l)
  {
    return symbol_type (token::TOK_RETURN, l);
  }

  parser::symbol_type
  parser::make_CALL (const location_type& l)
  {
    return symbol_type (token::TOK_CALL, l);
  }

  parser::symbol_type
  parser::make_PAIR (const location_type& l)
  {
    return symbol_type (token::TOK_PAIR, l);
  }

  parser::symbol_type
  parser::make_INT (const location_type& l)
  {
    return symbol_type (token::TOK_INT, l);
  }

  parser::symbol_type
  parser::make_BOOL (const location_type& l)
  {
    return symbol_type (token::TOK_BOOL, l);
  }

  parser::symbol_type
  parser::make_CHAR (const location_type& l)
  {
    return symbol_type (token::TOK_CHAR, l);
  }

  parser::symbol_type
  parser::make_STRING (const location_type& l)
  {
    return symbol_type (token::TOK_STRING, l);
  }

  parser::symbol_type
  parser::make_NULLTOKEN (const location_type& l)
  {
    return symbol_type (token::TOK_NULLTOKEN, l);
  }

  parser::symbol_type
  parser::make_ASSIGN (const int& v, const location_type& l)
  {
    return symbol_type (token::TOK_ASSIGN, v, l);
  }

  parser::symbol_type
  parser::make_LOGOR (const int& v, const location_type& l)
  {
    return symbol_type (token::TOK_LOGOR, v, l);
  }

  parser::symbol_type
  parser::make_LOGAND (const int& v, const location_type& l)
  {
    return symbol_type (token::TOK_LOGAND, v, l);
  }

  parser::symbol_type
  parser::make_STAR (const int& v, const location_type& l)
  {
    return symbol_type (token::TOK_STAR, v, l);
  }

  parser::symbol_type
  parser::make_SLASH (const int& v, const location_type& l)
  {
    return symbol_type (token::TOK_SLASH, v, l);
  }

  parser::symbol_type
  parser::make_MODULO (const int& v, const location_type& l)
  {
    return symbol_type (token::TOK_MODULO, v, l);
  }

  parser::symbol_type
  parser::make_PLUS (const int& v, const location_type& l)
  {
    return symbol_type (token::TOK_PLUS, v, l);
  }

  parser::symbol_type
  parser::make_MINUS (const int& v, const location_type& l)
  {
    return symbol_type (token::TOK_MINUS, v, l);
  }

  parser::symbol_type
  parser::make_LESS (const int& v, const location_type& l)
  {
    return symbol_type (token::TOK_LESS, v, l);
  }

  parser::symbol_type
  parser::make_LESSEQUALS (const int& v, const location_type& l)
  {
    return symbol_type (token::TOK_LESSEQUALS, v, l);
  }

  parser::symbol_type
  parser::make_GREATER (const int& v, const location_type& l)
  {
    return symbol_type (token::TOK_GREATER, v, l);
  }

  parser::symbol_type
  parser::make_GREATEREQUALS (const int& v, const location_type& l)
  {
    return symbol_type (token::TOK_GREATEREQUALS, v, l);
  }

  parser::symbol_type
  parser::make_EQUALS (const int& v, const location_type& l)
  {
    return symbol_type (token::TOK_EQUALS, v, l);
  }

  parser::symbol_type
  parser::make_NOTEQUALS (const int& v, const location_type& l)
  {
    return symbol_type (token::TOK_NOTEQUALS, v, l);
  }

  parser::symbol_type
  parser::make_BANG (const int& v, const location_type& l)
  {
    return symbol_type (token::TOK_BANG, v, l);
  }

  parser::symbol_type
  parser::make_LEN (const int& v, const location_type& l)
  {
    return symbol_type (token::TOK_LEN, v, l);
  }

  parser::symbol_type
  parser::make_ORD (const int& v, const location_type& l)
  {
    return symbol_type (token::TOK_ORD, v, l);
  }

  parser::symbol_type
  parser::make_CHR (const int& v, const location_type& l)
  {
    return symbol_type (token::TOK_CHR, v, l);
  }

  parser::symbol_type
  parser::make_LPAREN (const location_type& l)
  {
    return symbol_type (token::TOK_LPAREN, l);
  }

  parser::symbol_type
  parser::make_RPAREN (const location_type& l)
  {
    return symbol_type (token::TOK_RPAREN, l);
  }

  parser::symbol_type
  parser::make_LSQUARE (const location_type& l)
  {
    return symbol_type (token::TOK_LSQUARE, l);
  }

  parser::symbol_type
  parser::make_RSQUARE (const location_type& l)
  {
    return symbol_type (token::TOK_RSQUARE, l);
  }

  parser::symbol_type
  parser::make_SEMICOLON (const location_type& l)
  {
    return symbol_type (token::TOK_SEMICOLON, l);
  }

  parser::symbol_type
  parser::make_COMMA (const location_type& l)
  {
    return symbol_type (token::TOK_COMMA, l);
  }

  parser::symbol_type
  parser::make_PRINT (const location_type& l)
  {
    return symbol_type (token::TOK_PRINT, l);
  }

  parser::symbol_type
  parser::make_PRINTLN (const location_type& l)
  {
    return symbol_type (token::TOK_PRINTLN, l);
  }

  parser::symbol_type
  parser::make_READ (const location_type& l)
  {
    return symbol_type (token::TOK_READ, l);
  }

  parser::symbol_type
  parser::make_NEWPAIR (const location_type& l)
  {
    return symbol_type (token::TOK_NEWPAIR, l);
  }

  parser::symbol_type
  parser::make_FST (const location_type& l)
  {
    return symbol_type (token::TOK_FST, l);
  }

  parser::symbol_type
  parser::make_SND (const location_type& l)
  {
    return symbol_type (token::TOK_SND, l);
  }

  parser::symbol_type
  parser::make_ERROR (const location_type& l)
  {
    return symbol_type (token::TOK_ERROR, l);
  }

  parser::symbol_type
  parser::make_IDENTIFIER (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOK_IDENTIFIER, v, l);
  }

  parser::symbol_type
  parser::make_STRINGLIT (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOK_STRINGLIT, v, l);
  }

  parser::symbol_type
  parser::make_CHARLIT (const char& v, const location_type& l)
  {
    return symbol_type (token::TOK_CHARLIT, v, l);
  }

  parser::symbol_type
  parser::make_INTEGER (const int& v, const location_type& l)
  {
    return symbol_type (token::TOK_INTEGER, v, l);
  }

  parser::symbol_type
  parser::make_UMINUS (const location_type& l)
  {
    return symbol_type (token::TOK_UMINUS, l);
  }

  parser::symbol_type
  parser::make_UPLUS (const location_type& l)
  {
    return symbol_type (token::TOK_UPLUS, l);
  }



} // yy
#line 2104 "parser.hh" // lalr1.cc:372




#endif // !YY_YY_PARSER_HH_INCLUDED
