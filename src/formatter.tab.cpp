// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.


// Take the name prefix into account.
#define yylex   fmtlex

// First part of user prologue.
#line 14 "src/formatter.yy"

  #include <iostream>
  #include <cmath>   // For pow, used in the grammar
  void fmterror(char const *);

#line 49 "src/formatter.tab.cpp"


#include "formatter.tab.hpp"


// Unqualified %code blocks.
#line 27 "src/formatter.yy"

  #include "fmtlex.hpp"

#line 60 "src/formatter.tab.cpp"


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


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if FMTDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
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
      yy_stack_print_ ();                \
  } while (false)

#else // !FMTDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !FMTDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace fmt {
#line 133 "src/formatter.tab.cpp"

  /// Build a parser object.
  parser::parser (std::string& result_yyarg)
#if FMTDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      result (result_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_NUM: // NUM
      case symbol_kind::S_VAR: // VAR
      case symbol_kind::S_FUN: // FUN
      case symbol_kind::S_implicit: // implicit
      case symbol_kind::S_exp: // exp
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_NUM: // NUM
      case symbol_kind::S_VAR: // VAR
      case symbol_kind::S_FUN: // FUN
      case symbol_kind::S_implicit: // implicit
      case symbol_kind::S_exp: // exp
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_NUM: // NUM
      case symbol_kind::S_VAR: // VAR
      case symbol_kind::S_FUN: // FUN
      case symbol_kind::S_implicit: // implicit
      case symbol_kind::S_exp: // exp
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_NUM: // NUM
      case symbol_kind::S_VAR: // VAR
      case symbol_kind::S_FUN: // FUN
      case symbol_kind::S_implicit: // implicit
      case symbol_kind::S_exp: // exp
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if FMTDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if FMTDEBUG
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
#endif // FMTDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_NUM: // NUM
      case symbol_kind::S_VAR: // VAR
      case symbol_kind::S_FUN: // FUN
      case symbol_kind::S_implicit: // implicit
      case symbol_kind::S_exp: // exp
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 5: // line: exp "\n"
#line 66 "src/formatter.yy"
             { result = yystack_[1].value.as < std::string > (); }
#line 555 "src/formatter.tab.cpp"
    break;

  case 6: // line: error "\n"
#line 67 "src/formatter.yy"
             { yyerrok;                      }
#line 561 "src/formatter.tab.cpp"
    break;

  case 7: // implicit: VAR
#line 71 "src/formatter.yy"
                                { yylhs.value.as < std::string > () += yystack_[0].value.as < std::string > ();                             }
#line 567 "src/formatter.tab.cpp"
    break;

  case 8: // implicit: FUN "(" exp ")"
#line 72 "src/formatter.yy"
                                { yylhs.value.as < std::string > () += yystack_[3].value.as < std::string > () + "(" + yystack_[1].value.as < std::string > () + ")";            }
#line 573 "src/formatter.tab.cpp"
    break;

  case 9: // implicit: "(" exp ")"
#line 73 "src/formatter.yy"
                                { yylhs.value.as < std::string > () += "(" + yystack_[1].value.as < std::string > () + ")";                 }
#line 579 "src/formatter.tab.cpp"
    break;

  case 10: // implicit: implicit VAR
#line 74 "src/formatter.yy"
                                { yylhs.value.as < std::string > () += yystack_[1].value.as < std::string > () + "*" + yystack_[0].value.as < std::string > ();                  }
#line 585 "src/formatter.tab.cpp"
    break;

  case 11: // implicit: implicit FUN "(" exp ")"
#line 75 "src/formatter.yy"
                                { yylhs.value.as < std::string > () += yystack_[4].value.as < std::string > () + "*" + yystack_[3].value.as < std::string > () + "(" + yystack_[1].value.as < std::string > () + ")"; }
#line 591 "src/formatter.tab.cpp"
    break;

  case 12: // implicit: implicit "(" exp ")"
#line 76 "src/formatter.yy"
                                { yylhs.value.as < std::string > () += yystack_[3].value.as < std::string > () + "*" + "(" + yystack_[1].value.as < std::string > () + ")";      }
#line 597 "src/formatter.tab.cpp"
    break;

  case 13: // exp: NUM
#line 79 "src/formatter.yy"
                     { yylhs.value.as < std::string > () += yystack_[0].value.as < std::string > ();                        }
#line 603 "src/formatter.tab.cpp"
    break;

  case 14: // exp: implicit
#line 80 "src/formatter.yy"
                     { yylhs.value.as < std::string > () += yystack_[0].value.as < std::string > ();                        }
#line 609 "src/formatter.tab.cpp"
    break;

  case 15: // exp: NUM implicit
#line 81 "src/formatter.yy"
                     { yylhs.value.as < std::string > () += yystack_[1].value.as < std::string > () + "*" + yystack_[0].value.as < std::string > ();             }
#line 615 "src/formatter.tab.cpp"
    break;

  case 16: // exp: exp "+" exp
#line 82 "src/formatter.yy"
                     { yylhs.value.as < std::string > () += yystack_[2].value.as < std::string > () + "+" + yystack_[0].value.as < std::string > ();             }
#line 621 "src/formatter.tab.cpp"
    break;

  case 17: // exp: exp "-" exp
#line 83 "src/formatter.yy"
                     { yylhs.value.as < std::string > () += yystack_[2].value.as < std::string > () + "-" + yystack_[0].value.as < std::string > ();             }
#line 627 "src/formatter.tab.cpp"
    break;

  case 18: // exp: exp "*" exp
#line 84 "src/formatter.yy"
                     { yylhs.value.as < std::string > () += yystack_[2].value.as < std::string > () + "*" + yystack_[0].value.as < std::string > ();             }
#line 633 "src/formatter.tab.cpp"
    break;

  case 19: // exp: exp "/" exp
#line 85 "src/formatter.yy"
                     { yylhs.value.as < std::string > () += yystack_[2].value.as < std::string > () + "/" + yystack_[0].value.as < std::string > ();             }
#line 639 "src/formatter.tab.cpp"
    break;

  case 20: // exp: "-" exp
#line 86 "src/formatter.yy"
                     { yylhs.value.as < std::string > () += "-" + yystack_[0].value.as < std::string > ();                  }
#line 645 "src/formatter.tab.cpp"
    break;

  case 21: // exp: exp "^" exp
#line 87 "src/formatter.yy"
                     { yylhs.value.as < std::string > () += yystack_[2].value.as < std::string > () + "^" + yystack_[0].value.as < std::string > ();             }
#line 651 "src/formatter.tab.cpp"
    break;


#line 655 "src/formatter.tab.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
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
        std::string msg = YY_("syntax error");
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

#if FMTDEBUG || 0
  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if FMTDEBUG || 0









  const signed char parser::yypact_ninf_ = -5;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
      -5,    23,    -5,    -3,    26,    26,    -5,     1,    -5,     2,
      -5,    61,    -2,    -5,    -1,    38,    61,    26,    26,    -5,
       3,    26,    26,    26,    26,    26,    -5,    -5,    45,    52,
      26,    65,    65,    -1,    -1,    -1,    -5,    -5,    59,    -5
  };

  const signed char
  parser::yydefact_[] =
  {
       2,     0,     1,     0,     0,     0,     4,    13,     7,     0,
       3,    14,     0,     6,    20,     0,    15,     0,     0,    10,
       0,     0,     0,     0,     0,     0,     5,     9,     0,     0,
       0,    17,    16,    18,    19,    21,     8,    12,     0,    11
  };

  const signed char
  parser::yypgoto_[] =
  {
      -5,    -5,    -5,    15,    -4
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,     1,    10,    11,    12
  };

  const signed char
  parser::yytable_[] =
  {
      14,    15,    21,    22,    23,    24,    25,    25,    13,    26,
       5,    17,    30,    28,    29,     8,     9,    31,    32,    33,
      34,    35,    16,     2,     3,     0,    38,     4,     0,     0,
       4,     0,     5,     0,     6,     5,     7,     8,     9,     7,
       8,     9,    21,    22,    23,    24,    25,     0,    27,    21,
      22,    23,    24,    25,     0,    36,    21,    22,    23,    24,
      25,     0,    37,    21,    22,    23,    24,    25,     0,    39,
      18,    23,    24,    25,     0,    19,    20
  };

  const signed char
  parser::yycheck_[] =
  {
       4,     5,     4,     5,     6,     7,     8,     8,    11,    11,
       9,     9,     9,    17,    18,    14,    15,    21,    22,    23,
      24,    25,     7,     0,     1,    -1,    30,     4,    -1,    -1,
       4,    -1,     9,    -1,    11,     9,    13,    14,    15,    13,
      14,    15,     4,     5,     6,     7,     8,    -1,    10,     4,
       5,     6,     7,     8,    -1,    10,     4,     5,     6,     7,
       8,    -1,    10,     4,     5,     6,     7,     8,    -1,    10,
       9,     6,     7,     8,    -1,    14,    15
  };

  const signed char
  parser::yystos_[] =
  {
       0,    17,     0,     1,     4,     9,    11,    13,    14,    15,
      18,    19,    20,    11,    20,    20,    19,     9,     9,    14,
      15,     4,     5,     6,     7,     8,    11,    10,    20,    20,
       9,    20,    20,    20,    20,    20,    10,    10,    20,    10
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    16,    17,    17,    18,    18,    18,    19,    19,    19,
      19,    19,    19,    20,    20,    20,    20,    20,    20,    20,
      20,    20
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     0,     2,     1,     2,     2,     1,     4,     3,
       2,     5,     4,     1,     1,     2,     3,     3,     3,     3,
       2,     3
  };


#if FMTDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"=\"", "\"-\"",
  "\"+\"", "\"*\"", "\"/\"", "\"^\"", "\"(\"", "\")\"", "\"\\n\"", "NEG",
  "NUM", "VAR", "FUN", "$accept", "input", "line", "implicit", "exp", YY_NULLPTR
  };
#endif


#if FMTDEBUG
  const signed char
  parser::yyrline_[] =
  {
       0,    60,    60,    61,    65,    66,    67,    71,    72,    73,
      74,    75,    76,    79,    80,    81,    82,    83,    84,    85,
      86,    87
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // FMTDEBUG


} // fmt
#line 981 "src/formatter.tab.cpp"

#line 90 "src/formatter.yy"

void fmt::parser::error(const std::string& m)
{
    std::cerr << m << '\n';
}
