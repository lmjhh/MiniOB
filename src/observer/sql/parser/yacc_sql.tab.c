/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length; //Select 栈的深度
  size_t condition_length;
  size_t from_length;
  size_t value_length;

	//做一个快照
  size_t condition_length_tmp[5];
  size_t from_length_tmp[5];
  size_t value_length_tmp[5];
	CompOp comp_tmp[5];

  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
  char id[MAX_NUM];
  int order_by_type;
  int nullable;
  Exp exp[MAX_EXP_TMP_NUM];
  int exp_length;
  
	Selects selects[3];

	int selects_tmp_pool_length;
	Selects selects_tmp_pool[5];
	// Exp exp_pool[6];
	// int exp_pool_length;
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->exp_length = 0;
  context->ssql->sstr.insertion.tuple_num = 0;
  printf(". error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 147 "yacc_sql.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_SELECT = 9,                     /* SELECT  */
  YYSYMBOL_DESC = 10,                      /* DESC  */
  YYSYMBOL_SHOW = 11,                      /* SHOW  */
  YYSYMBOL_SYNC = 12,                      /* SYNC  */
  YYSYMBOL_INSERT = 13,                    /* INSERT  */
  YYSYMBOL_DELETE = 14,                    /* DELETE  */
  YYSYMBOL_UPDATE = 15,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 16,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 17,                    /* RBRACE  */
  YYSYMBOL_COMMA = 18,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 19,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 20,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 21,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 22,                     /* INT_T  */
  YYSYMBOL_DATE_T = 23,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 24,                    /* TEXT_T  */
  YYSYMBOL_STRING_T = 25,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 26,                   /* FLOAT_T  */
  YYSYMBOL_NULL_T = 27,                    /* NULL_T  */
  YYSYMBOL_HELP = 28,                      /* HELP  */
  YYSYMBOL_EXIT = 29,                      /* EXIT  */
  YYSYMBOL_DOT = 30,                       /* DOT  */
  YYSYMBOL_INTO = 31,                      /* INTO  */
  YYSYMBOL_VALUES = 32,                    /* VALUES  */
  YYSYMBOL_FROM = 33,                      /* FROM  */
  YYSYMBOL_WHERE = 34,                     /* WHERE  */
  YYSYMBOL_AND = 35,                       /* AND  */
  YYSYMBOL_SET = 36,                       /* SET  */
  YYSYMBOL_ON = 37,                        /* ON  */
  YYSYMBOL_LOAD = 38,                      /* LOAD  */
  YYSYMBOL_DATA = 39,                      /* DATA  */
  YYSYMBOL_INFILE = 40,                    /* INFILE  */
  YYSYMBOL_EQ = 41,                        /* EQ  */
  YYSYMBOL_LT = 42,                        /* LT  */
  YYSYMBOL_GT = 43,                        /* GT  */
  YYSYMBOL_LE = 44,                        /* LE  */
  YYSYMBOL_GE = 45,                        /* GE  */
  YYSYMBOL_NE = 46,                        /* NE  */
  YYSYMBOL_MAX = 47,                       /* MAX  */
  YYSYMBOL_MIN = 48,                       /* MIN  */
  YYSYMBOL_COUNT = 49,                     /* COUNT  */
  YYSYMBOL_AVG = 50,                       /* AVG  */
  YYSYMBOL_ORDERBY = 51,                   /* ORDERBY  */
  YYSYMBOL_ASC = 52,                       /* ASC  */
  YYSYMBOL_INNERJOIN = 53,                 /* INNERJOIN  */
  YYSYMBOL_UNIQUE = 54,                    /* UNIQUE  */
  YYSYMBOL_NULLABLE = 55,                  /* NULLABLE  */
  YYSYMBOL_NOTNULL = 56,                   /* NOTNULL  */
  YYSYMBOL_IS = 57,                        /* IS  */
  YYSYMBOL_GROUPBY = 58,                   /* GROUPBY  */
  YYSYMBOL_IN = 59,                        /* IN  */
  YYSYMBOL_NOTIN = 60,                     /* NOTIN  */
  YYSYMBOL_PLUS = 61,                      /* PLUS  */
  YYSYMBOL_MINUS = 62,                     /* MINUS  */
  YYSYMBOL_DIVE = 63,                      /* DIVE  */
  YYSYMBOL_NUMBER = 64,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 65,                     /* FLOAT  */
  YYSYMBOL_ID = 66,                        /* ID  */
  YYSYMBOL_PATH = 67,                      /* PATH  */
  YYSYMBOL_DATE = 68,                      /* DATE  */
  YYSYMBOL_SSS = 69,                       /* SSS  */
  YYSYMBOL_STAR = 70,                      /* STAR  */
  YYSYMBOL_STRING_V = 71,                  /* STRING_V  */
  YYSYMBOL_POLYKEY = 72,                   /* POLYKEY  */
  YYSYMBOL_UMINUS = 73,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 74,                  /* $accept  */
  YYSYMBOL_commands = 75,                  /* commands  */
  YYSYMBOL_command = 76,                   /* command  */
  YYSYMBOL_exit = 77,                      /* exit  */
  YYSYMBOL_help = 78,                      /* help  */
  YYSYMBOL_sync = 79,                      /* sync  */
  YYSYMBOL_begin = 80,                     /* begin  */
  YYSYMBOL_commit = 81,                    /* commit  */
  YYSYMBOL_rollback = 82,                  /* rollback  */
  YYSYMBOL_drop_table = 83,                /* drop_table  */
  YYSYMBOL_show_tables = 84,               /* show_tables  */
  YYSYMBOL_desc_table = 85,                /* desc_table  */
  YYSYMBOL_create_index = 86,              /* create_index  */
  YYSYMBOL_id_list = 87,                   /* id_list  */
  YYSYMBOL_drop_index = 88,                /* drop_index  */
  YYSYMBOL_create_table = 89,              /* create_table  */
  YYSYMBOL_attr_def_list = 90,             /* attr_def_list  */
  YYSYMBOL_attr_def = 91,                  /* attr_def  */
  YYSYMBOL_null = 92,                      /* null  */
  YYSYMBOL_number = 93,                    /* number  */
  YYSYMBOL_type = 94,                      /* type  */
  YYSYMBOL_ID_get = 95,                    /* ID_get  */
  YYSYMBOL_insert = 96,                    /* insert  */
  YYSYMBOL_values_list = 97,               /* values_list  */
  YYSYMBOL_value_list = 98,                /* value_list  */
  YYSYMBOL_value = 99,                     /* value  */
  YYSYMBOL_delete = 100,                   /* delete  */
  YYSYMBOL_update = 101,                   /* update  */
  YYSYMBOL_select = 102,                   /* select  */
  YYSYMBOL_left_brace = 103,               /* left_brace  */
  YYSYMBOL_select_mix = 104,               /* select_mix  */
  YYSYMBOL_mix_list = 105,                 /* mix_list  */
  YYSYMBOL_expression_attr = 106,          /* expression_attr  */
  YYSYMBOL_poly_value = 107,               /* poly_value  */
  YYSYMBOL_rel_list = 108,                 /* rel_list  */
  YYSYMBOL_inner_join = 109,               /* inner_join  */
  YYSYMBOL_inner_join_on = 110,            /* inner_join_on  */
  YYSYMBOL_where = 111,                    /* where  */
  YYSYMBOL_where_key = 112,                /* where_key  */
  YYSYMBOL_condition_list = 113,           /* condition_list  */
  YYSYMBOL_and_key = 114,                  /* and_key  */
  YYSYMBOL_expression = 115,               /* expression  */
  YYSYMBOL_condition = 116,                /* condition  */
  YYSYMBOL_in_or_not_in = 117,             /* in_or_not_in  */
  YYSYMBOL_comOp = 118,                    /* comOp  */
  YYSYMBOL_order_by = 119,                 /* order_by  */
  YYSYMBOL_order_by_list = 120,            /* order_by_list  */
  YYSYMBOL_order_by_attr = 121,            /* order_by_attr  */
  YYSYMBOL_order_by_type = 122,            /* order_by_type  */
  YYSYMBOL_group_by = 123,                 /* group_by  */
  YYSYMBOL_group_by_list = 124,            /* group_by_list  */
  YYSYMBOL_group_by_attr = 125,            /* group_by_attr  */
  YYSYMBOL_load_data = 126                 /* load_data  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   389

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  161
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  341

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   328


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   180,   180,   182,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   206,   211,   216,   222,   228,   234,   240,   246,   252,
     259,   265,   272,   274,   280,   287,   296,   298,   302,   313,
     327,   330,   333,   339,   342,   343,   344,   345,   346,   347,
     350,   359,   375,   377,   385,   389,   394,   398,   401,   404,
     408,   414,   424,   435,   452,   486,   495,   500,   506,   511,
     516,   525,   535,   543,   551,   559,   568,   570,   576,   581,
     586,   594,   604,   612,   620,   629,   638,   777,   784,   791,
     864,   866,   871,   873,   878,   884,   886,   891,   898,   900,
     905,   913,   920,   928,   936,   942,   949,   952,   960,   968,
     981,   999,  1016,  1033,  1052,  1070,  1089,  1105,  1111,  1117,
    1123,  1136,  1142,  1148,  1155,  1162,  1170,  1177,  1184,  1192,
    1200,  1208,  1222,  1236,  1251,  1266,  1299,  1332,  1338,  1341,
    1347,  1348,  1349,  1350,  1351,  1352,  1356,  1358,  1362,  1364,
    1370,  1375,  1382,  1385,  1388,  1393,  1395,  1399,  1401,  1407,
    1412,  1421
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "SELECT", "DESC", "SHOW", "SYNC",
  "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "DATE_T", "TEXT_T", "STRING_T",
  "FLOAT_T", "NULL_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM",
  "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT",
  "LE", "GE", "NE", "MAX", "MIN", "COUNT", "AVG", "ORDERBY", "ASC",
  "INNERJOIN", "UNIQUE", "NULLABLE", "NOTNULL", "IS", "GROUPBY", "IN",
  "NOTIN", "PLUS", "MINUS", "DIVE", "NUMBER", "FLOAT", "ID", "PATH",
  "DATE", "SSS", "STAR", "STRING_V", "POLYKEY", "UMINUS", "$accept",
  "commands", "command", "exit", "help", "sync", "begin", "commit",
  "rollback", "drop_table", "show_tables", "desc_table", "create_index",
  "id_list", "drop_index", "create_table", "attr_def_list", "attr_def",
  "null", "number", "type", "ID_get", "insert", "values_list",
  "value_list", "value", "delete", "update", "select", "left_brace",
  "select_mix", "mix_list", "expression_attr", "poly_value", "rel_list",
  "inner_join", "inner_join_on", "where", "where_key", "condition_list",
  "and_key", "expression", "condition", "in_or_not_in", "comOp",
  "order_by", "order_by_list", "order_by_attr", "order_by_type",
  "group_by", "group_by_list", "group_by_attr", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328
};
#endif

#define YYPACT_NINF (-256)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-77)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -256,   232,  -256,    10,    76,    62,   -32,    33,    34,    79,
      60,    39,  -256,   120,   132,   134,   142,   145,   130,  -256,
    -256,  -256,  -256,  -256,  -256,  -256,  -256,  -256,  -256,  -256,
    -256,  -256,  -256,  -256,  -256,  -256,   150,  -256,   109,   136,
     195,   141,   146,   117,  -256,   117,  -256,  -256,    11,  -256,
    -256,  -256,   200,  -256,   186,   202,   126,   219,   220,  -256,
     158,   159,   192,  -256,  -256,  -256,  -256,  -256,   198,    62,
     223,   203,   169,   246,   247,   234,   138,  -256,    74,   -34,
    -256,   108,   196,  -256,   117,   117,   117,   117,  -256,  -256,
     236,   231,   205,   204,   253,   206,   221,   251,  -256,  -256,
     225,  -256,    89,   273,   202,    70,   202,  -256,  -256,     0,
    -256,   277,   278,   279,   -35,   -35,  -256,  -256,   296,  -256,
     310,    30,   274,   283,   252,  -256,   299,   284,   303,   254,
    -256,    55,  -256,   140,  -256,  -256,  -256,   202,    81,   202,
     202,   255,   269,    -6,  -256,   117,   266,   233,   259,   213,
     213,   289,    -6,   319,   279,   206,   309,  -256,  -256,  -256,
    -256,  -256,  -256,    61,   261,   312,    70,   202,    51,   313,
     314,  -256,   315,   316,  -256,  -256,   279,   263,   231,   317,
     165,   268,  -256,  -256,  -256,  -256,  -256,  -256,   -14,  -256,
    -256,    22,    88,    20,   149,     6,   117,  -256,  -256,    30,
     231,   270,   269,   299,   334,  -256,  -256,   322,   321,   275,
    -256,  -256,   202,   114,   202,   202,   202,   202,  -256,   305,
     282,    -6,   326,  -256,   318,  -256,   239,  -256,  -256,  -256,
     234,  -256,  -256,  -256,  -256,  -256,   320,  -256,  -256,   323,
    -256,  -256,   289,   341,   342,   231,  -256,  -256,   285,   280,
     330,   321,  -256,   335,   337,  -256,  -256,  -256,  -256,  -256,
      30,   290,   300,   317,   339,   292,    50,    22,   102,   293,
     294,  -256,  -256,  -256,   282,  -256,   338,   321,   358,   345,
     202,   202,   289,    -3,   346,   297,   362,  -256,   350,   364,
    -256,  -256,  -256,  -256,   340,  -256,  -256,  -256,  -256,  -256,
     300,  -256,  -256,  -256,   365,  -256,  -256,   269,  -256,   306,
    -256,  -256,   290,  -256,    13,   351,  -256,    -6,  -256,   307,
     354,  -256,  -256,    15,   346,   308,  -256,   297,  -256,   317,
    -256,  -256,  -256,  -256,    15,   351,   359,  -256,  -256,   339,
    -256
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    65,     0,     0,     0,     0,     0,     0,     3,
      20,    19,    14,    15,    16,    17,     9,    10,    11,    12,
      13,     8,     5,     7,     6,     4,     0,    18,     0,     0,
       0,     0,     0,     0,    60,     0,    57,    58,   108,    56,
      59,    66,     0,   107,     0,    76,    86,     0,     0,    23,
       0,     0,     0,    24,    25,    26,    22,    21,     0,     0,
       0,     0,     0,     0,     0,   108,     0,   105,     0,     0,
      67,     0,     0,    75,     0,     0,     0,     0,    29,    28,
       0,    95,     0,     0,     0,     0,     0,     0,    27,    34,
       0,   106,   108,     0,    76,   109,    76,    87,    88,     0,
      89,     0,     0,    90,   101,   102,   104,   103,     0,    97,
       0,     0,     0,     0,     0,    50,    36,     0,     0,     0,
     109,     0,    77,     0,    85,    68,    69,    76,     0,    76,
      76,     0,    92,     0,    61,    65,    60,   108,   107,     0,
       0,    98,     0,     0,    90,     0,     0,    44,    45,    49,
      46,    47,    48,    40,     0,     0,   109,    76,     0,     0,
       0,    72,     0,     0,    71,    70,    90,     0,    95,    54,
       0,     0,   140,   141,   142,   143,   144,   145,     0,   138,
     139,     0,     0,     0,     0,     0,     0,   100,    96,     0,
      95,     0,    92,    36,     0,    42,    41,    39,    32,     0,
      78,    79,    76,     0,    76,    76,    76,    76,    91,     0,
     155,     0,     0,   130,   128,   127,   109,   123,   124,   131,
     108,   107,   133,   117,   121,   122,   108,   107,   119,   135,
     137,   120,    98,     0,     0,    95,    37,    35,     0,     0,
       0,    32,    82,     0,     0,    81,    80,    73,    74,    94,
       0,     0,   146,    54,    52,     0,     0,     0,     0,     0,
       0,    99,    62,   161,   155,    43,     0,    32,     0,     0,
      76,    76,    98,   152,   157,     0,     0,    55,     0,     0,
     129,   125,   126,   132,   108,   107,   134,   118,   109,   136,
     146,    38,    33,    30,     0,    83,    84,    92,   154,     0,
     153,   159,     0,   156,   152,   148,    63,     0,    51,     0,
       0,    31,    93,   152,   157,     0,   150,     0,   147,    54,
     109,    64,   160,   158,   152,   148,     0,   151,   149,    52,
      53
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -256,  -256,  -256,  -256,  -256,  -256,  -256,  -256,  -256,  -256,
    -256,  -256,  -256,  -232,  -256,  -256,   172,   222,  -256,  -256,
    -256,  -256,  -256,    40,  -255,  -119,  -256,  -256,    -1,  -256,
     311,   -54,     1,   245,   -85,  -199,  -256,  -174,  -256,  -222,
    -256,   -31,  -194,   155,  -139,    82,    48,    57,  -214,   111,
      63,    77,  -256
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,   250,    30,    31,   156,   126,   207,   276,
     163,   127,    32,   289,   222,    53,    33,    34,   149,    36,
      54,    80,   150,   112,   142,   178,   260,   120,   121,   198,
     199,    56,   151,   191,   192,   286,   328,   315,   311,   262,
     313,   284,    37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      35,    83,   148,   245,   220,   242,    55,   308,   287,   194,
     195,   196,    76,   227,    77,     5,    38,   137,    39,   279,
     271,    44,    12,   308,   179,   308,   243,   309,    86,    78,
     138,     5,   105,   200,    57,    87,   106,    59,    12,     5,
      58,    79,   228,   325,   -76,   302,   145,   234,   132,   310,
     134,   135,   136,   114,   115,   116,   117,   146,    46,    47,
     307,   225,    49,    50,    40,   310,   282,   310,   212,   202,
      55,   274,   239,   231,   336,   237,   235,   291,    43,   104,
     148,   213,    41,   171,    42,   174,   175,   268,    78,    44,
      43,   218,    45,    61,    46,    47,   147,     5,    49,    50,
     326,    44,   263,   -76,   145,    62,   292,    78,   322,   332,
      60,     5,   210,   211,    76,    44,   205,   206,   145,   131,
     337,   166,   -76,    63,    45,   167,    46,    47,    48,    44,
      49,    50,    51,    43,    52,    64,    45,    65,    46,    47,
     102,   148,    49,    50,    44,    66,   103,   172,    67,   295,
      45,   173,    46,    47,   230,   101,    49,    50,   252,    69,
     255,   256,   257,   258,    45,    43,    46,    47,   294,    68,
      49,    50,   107,   108,   109,    70,    44,   110,   111,    45,
     253,    46,    47,    75,   254,    49,    50,    84,    85,    86,
     229,   232,    44,   233,   240,   238,    87,   241,   329,    84,
      85,    86,    71,    72,   107,   108,   168,    73,    87,   110,
     169,    45,    74,    46,    47,   236,    81,    49,    50,    82,
      78,   223,    88,    89,    90,    91,   305,   306,    92,    46,
      47,   224,     2,    49,    50,    97,     3,     4,    93,    95,
      96,     5,     6,     7,     8,     9,    10,    11,    12,    98,
      99,    13,    14,    15,   182,   183,   184,   185,   186,   187,
      16,    17,   113,   181,   100,   119,   293,   296,   118,   297,
      18,   122,   125,   123,   182,   183,   184,   185,   186,   187,
     182,   183,   184,   185,   186,   187,   124,   128,   129,   133,
     188,   130,   189,   190,   139,   140,   266,   141,   189,   190,
     182,   183,   184,   185,   186,   187,   157,   158,   159,   160,
     161,   162,   143,   144,   153,   152,   193,   155,   154,   164,
     165,   176,   177,   180,   197,   201,   204,   208,   209,   219,
     214,   215,   216,   217,   226,   221,   244,   247,   248,   249,
     261,   251,   259,   264,   272,   273,   277,   278,   265,   275,
     269,   285,   280,   270,   281,   301,   283,   288,   290,   298,
     299,   303,   304,   314,   312,   316,   317,   318,   321,   327,
     319,   331,   323,   330,   334,   246,   339,   203,   170,   340,
      94,   267,   320,   338,   335,   300,     0,   333,     0,   324
};

static const yytype_int16 yycheck[] =
{
       1,    55,   121,   202,   178,   199,     5,    10,   263,   148,
     149,   150,    43,    27,    45,     9,     6,    17,     8,   251,
     242,    27,    16,    10,   143,    10,   200,    30,    63,    18,
      30,     9,    66,   152,    66,    70,    70,     3,    16,     9,
       7,    30,    56,    30,    33,   277,    16,    27,   102,    52,
     104,   105,   106,    84,    85,    86,    87,    27,    64,    65,
     282,   180,    68,    69,    54,    52,   260,    52,    17,   154,
      69,   245,    66,   192,   329,   194,    56,    27,    16,    78,
     199,    30,     6,   137,     8,   139,   140,   226,    18,    27,
      16,   176,    62,    33,    64,    65,    66,     9,    68,    69,
     314,    27,   221,    33,    16,    66,    56,    18,   307,   323,
      31,     9,   166,   167,   145,    27,    55,    56,    16,    30,
     334,    66,    33,     3,    62,    70,    64,    65,    66,    27,
      68,    69,    70,    16,    72,     3,    62,     3,    64,    65,
      66,   260,    68,    69,    27,     3,    72,    66,     3,   268,
      62,    70,    64,    65,    66,    17,    68,    69,   212,     9,
     214,   215,   216,   217,    62,    16,    64,    65,    66,    39,
      68,    69,    64,    65,    66,    66,    27,    69,    70,    62,
      66,    64,    65,    66,    70,    68,    69,    61,    62,    63,
     191,   192,    27,   192,   195,   194,    70,   196,   317,    61,
      62,    63,    66,     8,    64,    65,    66,    66,    70,    69,
      70,    62,    66,    64,    65,    66,    16,    68,    69,    33,
      18,    56,     3,     3,    66,    66,   280,   281,    36,    64,
      65,    66,     0,    68,    69,    66,     4,     5,    40,    16,
      37,     9,    10,    11,    12,    13,    14,    15,    16,     3,
       3,    19,    20,    21,    41,    42,    43,    44,    45,    46,
      28,    29,    66,    30,    30,    34,   267,   268,    32,   268,
      38,    66,    66,    69,    41,    42,    43,    44,    45,    46,
      41,    42,    43,    44,    45,    46,    33,    66,    37,    16,
      57,    66,    59,    60,    17,    17,    57,    18,    59,    60,
      41,    42,    43,    44,    45,    46,    22,    23,    24,    25,
      26,    27,    16,     3,    31,    41,    57,    18,    66,    16,
      66,    66,    53,    57,    35,     6,    17,    66,    16,    66,
      17,    17,    17,    17,    66,    18,    66,     3,    16,    18,
      58,    66,    37,    17,     3,     3,    66,    17,    30,    64,
      30,    51,    17,    30,    17,    17,    66,    18,    66,    66,
      66,     3,    17,    66,    18,     3,    16,     3,     3,    18,
      30,    17,    66,    66,    66,   203,    17,   155,   133,   339,
      69,   226,   300,   335,   327,   274,    -1,   324,    -1,   312
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    75,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    16,    19,    20,    21,    28,    29,    38,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      88,    89,    96,   100,   101,   102,   103,   126,     6,     8,
      54,     6,     8,    16,    27,    62,    64,    65,    66,    68,
      69,    70,    72,    99,   104,   106,   115,    66,     7,     3,
      31,    33,    66,     3,     3,     3,     3,     3,    39,     9,
      66,    66,     8,    66,    66,    66,   115,   115,    18,    30,
     105,    16,    33,   105,    61,    62,    63,    70,     3,     3,
      66,    66,    36,    40,   104,    16,    37,    66,     3,     3,
      30,    17,    66,    72,   106,    66,    70,    64,    65,    66,
      69,    70,   107,    66,   115,   115,   115,   115,    32,    34,
     111,   112,    66,    69,    33,    66,    91,    95,    66,    37,
      66,    30,   105,    16,   105,   105,   105,    17,    30,    17,
      17,    18,   108,    16,     3,    16,    27,    66,    99,   102,
     106,   116,    41,    31,    66,    18,    90,    22,    23,    24,
      25,    26,    27,    94,    16,    66,    66,    70,    66,    70,
     107,   105,    66,    70,   105,   105,    66,    53,   109,    99,
      57,    30,    41,    42,    43,    44,    45,    46,    57,    59,
      60,   117,   118,    57,   118,   118,   118,    35,   113,   114,
      99,     6,   108,    91,    17,    55,    56,    92,    66,    16,
     105,   105,    17,    30,    17,    17,    17,    17,   108,    66,
     111,    18,    98,    56,    66,    99,    66,    27,    56,   102,
      66,    99,   102,   106,    27,    56,    66,    99,   106,    66,
     102,   106,   116,   111,    66,   109,    90,     3,    16,    18,
      87,    66,   105,    66,    70,   105,   105,   105,   105,    37,
     110,    58,   123,    99,    17,    30,    57,   117,   118,    30,
      30,   113,     3,     3,   111,    64,    93,    66,    17,    87,
      17,    17,   116,    66,   125,    51,   119,    98,    18,    97,
      66,    27,    56,   102,    66,    99,   102,   106,    66,    66,
     123,    17,    87,     3,    17,   105,   105,   113,    10,    30,
      52,   122,    18,   124,    66,   121,     3,    16,     3,    30,
     119,     3,   109,    66,   125,    30,   122,    18,   120,    99,
      66,    17,   122,   124,    66,   121,    98,   122,   120,    17,
      97
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    74,    75,    75,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    86,    87,    87,    88,    89,    90,    90,    91,    91,
      92,    92,    92,    93,    94,    94,    94,    94,    94,    94,
      95,    96,    97,    97,    98,    98,    99,    99,    99,    99,
      99,   100,   101,   102,   102,   103,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   106,   107,   107,   107,
     108,   108,   109,   109,   110,   111,   111,   112,   113,   113,
     114,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   117,   117,
     118,   118,   118,   118,   118,   118,   119,   119,   120,   120,
     121,   121,   122,   122,   122,   123,   123,   124,   124,   125,
     125,   126
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
      10,    11,     0,     3,     4,     8,     0,     3,     6,     3,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,    10,     0,     6,     0,     3,     1,     1,     1,     1,
       1,     5,     8,    10,    11,     1,     1,     2,     4,     4,
       5,     5,     5,     7,     7,     2,     0,     3,     5,     5,
       6,     6,     6,     8,     8,     3,     1,     1,     1,     1,
       0,     3,     0,     6,     1,     0,     3,     1,     0,     3,
       1,     3,     3,     3,     3,     2,     3,     1,     1,     3,
       3,     3,     3,     3,     5,     5,     7,     3,     5,     3,
       3,     3,     3,     3,     3,     5,     5,     3,     3,     5,
       3,     3,     5,     3,     5,     3,     5,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     3,     0,     3,
       2,     4,     0,     1,     1,     0,     3,     0,     3,     2,
       4,     8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, void *scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 21: /* exit: EXIT SEMICOLON  */
#line 206 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1519 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 211 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1527 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 216 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1535 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 222 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1543 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 228 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1551 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 234 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1559 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 240 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1568 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 246 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1576 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 252 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1585 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 260 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
		}
#line 1595 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 266 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));			
		}
#line 1605 "yacc_sql.tab.c"
    break;

  case 33: /* id_list: COMMA ID id_list  */
#line 274 "yacc_sql.y"
                   {
	create_index_append_attribute(&CONTEXT->ssql->sstr.create_index,(yyvsp[-1].string));
}
#line 1613 "yacc_sql.tab.c"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 281 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1622 "yacc_sql.tab.c"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 288 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1634 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 298 "yacc_sql.y"
                                   {    }
#line 1640 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type null LBRACE number RBRACE  */
#line 303 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-1].number), CONTEXT->nullable);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
#line 1655 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type null  */
#line 314 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, CONTEXT->nullable);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1670 "yacc_sql.tab.c"
    break;

  case 40: /* null: %empty  */
#line 327 "yacc_sql.y"
                   {
		CONTEXT->nullable = 0;
	}
#line 1678 "yacc_sql.tab.c"
    break;

  case 41: /* null: NOTNULL  */
#line 330 "yacc_sql.y"
                  {
		CONTEXT->nullable = 0;
	}
#line 1686 "yacc_sql.tab.c"
    break;

  case 42: /* null: NULLABLE  */
#line 333 "yacc_sql.y"
                   {
		CONTEXT->nullable = 1;
	}
#line 1694 "yacc_sql.tab.c"
    break;

  case 43: /* number: NUMBER  */
#line 339 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1700 "yacc_sql.tab.c"
    break;

  case 44: /* type: INT_T  */
#line 342 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1706 "yacc_sql.tab.c"
    break;

  case 45: /* type: DATE_T  */
#line 343 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1712 "yacc_sql.tab.c"
    break;

  case 46: /* type: STRING_T  */
#line 344 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1718 "yacc_sql.tab.c"
    break;

  case 47: /* type: FLOAT_T  */
#line 345 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1724 "yacc_sql.tab.c"
    break;

  case 48: /* type: NULL_T  */
#line 346 "yacc_sql.y"
                    {(yyval.number)=NULLS;}
#line 1730 "yacc_sql.tab.c"
    break;

  case 49: /* type: TEXT_T  */
#line 347 "yacc_sql.y"
                    { (yyval.number)=TEXTS; }
#line 1736 "yacc_sql.tab.c"
    break;

  case 50: /* ID_get: ID  */
#line 351 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1745 "yacc_sql.tab.c"
    break;

  case 51: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE values_list SEMICOLON  */
#line 360 "yacc_sql.y"
                {
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
	  		//inserts_append_tuple(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-7].string));
			CONTEXT->value_length=0;
    }
#line 1763 "yacc_sql.tab.c"
    break;

  case 53: /* values_list: COMMA LBRACE value value_list RBRACE values_list  */
#line 377 "yacc_sql.y"
                                                  {
	//inserts_append_tuple(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
	//临时变量清零
    //CONTEXT->value_length=0;
}
#line 1773 "yacc_sql.tab.c"
    break;

  case 54: /* value_list: %empty  */
#line 385 "yacc_sql.y"
                {
		inserts_append_tuple(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
#line 1782 "yacc_sql.tab.c"
    break;

  case 55: /* value_list: COMMA value value_list  */
#line 389 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1790 "yacc_sql.tab.c"
    break;

  case 56: /* value: DATE  */
#line 394 "yacc_sql.y"
             {
			(yyvsp[0].date) = substr((yyvsp[0].date),1,strlen((yyvsp[0].date))-2);
  		value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].date));
		}
#line 1799 "yacc_sql.tab.c"
    break;

  case 57: /* value: NUMBER  */
#line 398 "yacc_sql.y"
           {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1807 "yacc_sql.tab.c"
    break;

  case 58: /* value: FLOAT  */
#line 401 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1815 "yacc_sql.tab.c"
    break;

  case 59: /* value: SSS  */
#line 404 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1824 "yacc_sql.tab.c"
    break;

  case 60: /* value: NULL_T  */
#line 408 "yacc_sql.y"
                {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++], 0);
		}
#line 1832 "yacc_sql.tab.c"
    break;

  case 61: /* delete: DELETE FROM ID where SEMICOLON  */
#line 415 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1844 "yacc_sql.tab.c"
    break;

  case 62: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 425 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1856 "yacc_sql.tab.c"
    break;

  case 63: /* select: SELECT select_mix FROM ID rel_list inner_join where group_by order_by SEMICOLON  */
#line 436 "yacc_sql.y"
                {

			selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-6].string));
			selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length], CONTEXT->conditions,0, CONTEXT->condition_length);
			CONTEXT->ssql->sstr.selection = CONTEXT->selects[CONTEXT->select_length];
			CONTEXT->ssql->flag = SCF_SELECT;
			
			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length = 0;
			CONTEXT->value_length = 0;
			CONTEXT->order_by_type = 0;
			CONTEXT->selects_tmp_pool_length=0;
	}
#line 1876 "yacc_sql.tab.c"
    break;

  case 64: /* select: left_brace SELECT select_mix FROM ID rel_list inner_join where group_by order_by RBRACE  */
#line 453 "yacc_sql.y"
        {
			selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-6].string));
			selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length], CONTEXT->conditions, CONTEXT->condition_length_tmp[CONTEXT->select_length - 1], CONTEXT->condition_length);
			
			//临时变量退栈
			CONTEXT->select_length--;
			CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
			CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
			CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

			if(CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].is_right_sub == 0){
				CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].is_right_sub = 1;


				selects_swap_with_other(&CONTEXT->selects_tmp_pool[CONTEXT->selects_tmp_pool_length], &CONTEXT->selects[CONTEXT->select_length + 1]);
				CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].right_sub_select = &CONTEXT->selects_tmp_pool[CONTEXT->selects_tmp_pool_length];
				CONTEXT->selects_tmp_pool_length++;
			}else{
				CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].is_left_sub = 1;
				CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].is_right_sub = 1;

				CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].left_sub_select = CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].right_sub_select;	

				selects_swap_with_other(&CONTEXT->selects_tmp_pool[CONTEXT->selects_tmp_pool_length], &CONTEXT->selects[CONTEXT->select_length + 1]);
				CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].right_sub_select = &CONTEXT->selects_tmp_pool[CONTEXT->selects_tmp_pool_length];			
				CONTEXT->selects_tmp_pool_length++;
			}

			CONTEXT->selects_tmp_pool_length = CONTEXT->selects_tmp_pool_length % (5);
	}
#line 1911 "yacc_sql.tab.c"
    break;

  case 65: /* left_brace: LBRACE  */
#line 486 "yacc_sql.y"
               {
		CONTEXT->condition_length_tmp[CONTEXT->select_length] = CONTEXT->condition_length;
		CONTEXT->value_length_tmp[CONTEXT->select_length] = CONTEXT->value_length;
		CONTEXT->from_length_tmp[CONTEXT->select_length] = CONTEXT->from_length;
		CONTEXT->select_length++;
	}
#line 1922 "yacc_sql.tab.c"
    break;

  case 66: /* select_mix: STAR  */
#line 495 "yacc_sql.y"
             {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 1932 "yacc_sql.tab.c"
    break;

  case 67: /* select_mix: ID mix_list  */
#line 500 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);

		}
#line 1943 "yacc_sql.tab.c"
    break;

  case 68: /* select_mix: ID DOT ID mix_list  */
#line 506 "yacc_sql.y"
                             {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 1953 "yacc_sql.tab.c"
    break;

  case 69: /* select_mix: ID DOT STAR mix_list  */
#line 511 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 1963 "yacc_sql.tab.c"
    break;

  case 70: /* select_mix: POLYKEY LBRACE poly_value RBRACE mix_list  */
#line 516 "yacc_sql.y"
                                                   {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
		//select_append_poly_lsn(&CONTEXT->selects[CONTEXT->select_length]);
		
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		}
#line 1977 "yacc_sql.tab.c"
    break;

  case 71: /* select_mix: POLYKEY LBRACE STAR RBRACE mix_list  */
#line 525 "yacc_sql.y"
                                             {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
#line 1992 "yacc_sql.tab.c"
    break;

  case 72: /* select_mix: POLYKEY LBRACE ID RBRACE mix_list  */
#line 535 "yacc_sql.y"
                                           {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
		}
#line 2005 "yacc_sql.tab.c"
    break;

  case 73: /* select_mix: POLYKEY LBRACE ID DOT ID RBRACE mix_list  */
#line 543 "yacc_sql.y"
                                                  {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-6].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
	}
#line 2018 "yacc_sql.tab.c"
    break;

  case 74: /* select_mix: POLYKEY LBRACE ID DOT STAR RBRACE mix_list  */
#line 551 "yacc_sql.y"
                                                    {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-6].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
	}
#line 2031 "yacc_sql.tab.c"
    break;

  case 75: /* select_mix: expression_attr mix_list  */
#line 559 "yacc_sql.y"
                                  {
		selects_append_exp(&CONTEXT->selects[CONTEXT->select_length],&CONTEXT->exp[CONTEXT->exp_length-1]);
		exp_destroy( &CONTEXT->exp[CONTEXT->exp_length-1] );
		CONTEXT->exp_length = 0 ;

	}
#line 2042 "yacc_sql.tab.c"
    break;

  case 77: /* mix_list: COMMA ID mix_list  */
#line 570 "yacc_sql.y"
                             {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);

		}
#line 2053 "yacc_sql.tab.c"
    break;

  case 78: /* mix_list: COMMA ID DOT ID mix_list  */
#line 576 "yacc_sql.y"
                                   {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 2063 "yacc_sql.tab.c"
    break;

  case 79: /* mix_list: COMMA ID DOT STAR mix_list  */
#line 581 "yacc_sql.y"
                                     {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 2073 "yacc_sql.tab.c"
    break;

  case 80: /* mix_list: COMMA POLYKEY LBRACE poly_value RBRACE mix_list  */
#line 586 "yacc_sql.y"
                                                         {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
		
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		}
#line 2086 "yacc_sql.tab.c"
    break;

  case 81: /* mix_list: COMMA POLYKEY LBRACE STAR RBRACE mix_list  */
#line 594 "yacc_sql.y"
                                                   {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
#line 2101 "yacc_sql.tab.c"
    break;

  case 82: /* mix_list: COMMA POLYKEY LBRACE ID RBRACE mix_list  */
#line 604 "yacc_sql.y"
                                                 {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
		}
#line 2114 "yacc_sql.tab.c"
    break;

  case 83: /* mix_list: COMMA POLYKEY LBRACE ID DOT ID RBRACE mix_list  */
#line 612 "yacc_sql.y"
                                                        {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-6].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
	}
#line 2127 "yacc_sql.tab.c"
    break;

  case 84: /* mix_list: COMMA POLYKEY LBRACE ID DOT STAR RBRACE mix_list  */
#line 620 "yacc_sql.y"
                                                          {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-6].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
#line 2141 "yacc_sql.tab.c"
    break;

  case 85: /* mix_list: COMMA expression_attr mix_list  */
#line 629 "yacc_sql.y"
                                        {
		selects_append_exp(&CONTEXT->selects[CONTEXT->select_length],&CONTEXT->exp[CONTEXT->exp_length-1]);
		exp_destroy( &CONTEXT->exp[CONTEXT->exp_length-1] );
		CONTEXT->exp_length-- ;

	}
#line 2152 "yacc_sql.tab.c"
    break;

  case 86: /* expression_attr: expression  */
#line 638 "yacc_sql.y"
                  {
		CONTEXT->exp_length++ ;
	}
#line 2160 "yacc_sql.tab.c"
    break;

  case 87: /* poly_value: NUMBER  */
#line 777 "yacc_sql.y"
          {	
		RelAttr attr1;
		relation_attr_init_for_number(&attr1, NULL, (yyvsp[0].number));
		selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr1, 0);

  		//value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
#line 2172 "yacc_sql.tab.c"
    break;

  case 88: /* poly_value: FLOAT  */
#line 784 "yacc_sql.y"
          {
		RelAttr attr1;
		relation_attr_init_for_float(&attr1, NULL, (yyvsp[0].floats));
		selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr1, 0);

  		//value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
#line 2184 "yacc_sql.tab.c"
    break;

  case 89: /* poly_value: SSS  */
#line 791 "yacc_sql.y"
         {
		//$1 = substr($1,1,strlen($1)-2);
  		RelAttr attr1;
		relation_attr_init(&attr1, NULL, (yyvsp[0].string));
		selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr1, 0);

		//value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
#line 2197 "yacc_sql.tab.c"
    break;

  case 91: /* rel_list: COMMA ID rel_list  */
#line 866 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string));
		  }
#line 2205 "yacc_sql.tab.c"
    break;

  case 93: /* inner_join: INNERJOIN ID inner_join_on condition condition_list inner_join  */
#line 873 "yacc_sql.y"
                                                                         {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-4].string));
	}
#line 2213 "yacc_sql.tab.c"
    break;

  case 94: /* inner_join_on: ON  */
#line 878 "yacc_sql.y"
           {
		Condition condition;
		condition_init_with_comp(&condition, NO_OP);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;	
	}
#line 2223 "yacc_sql.tab.c"
    break;

  case 96: /* where: where_key condition condition_list  */
#line 886 "yacc_sql.y"
                                         {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2231 "yacc_sql.tab.c"
    break;

  case 97: /* where_key: WHERE  */
#line 891 "yacc_sql.y"
                     {
			Condition condition;
			condition_init_with_comp(&condition, NO_OP);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		}
#line 2241 "yacc_sql.tab.c"
    break;

  case 99: /* condition_list: and_key condition condition_list  */
#line 900 "yacc_sql.y"
                                       {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2249 "yacc_sql.tab.c"
    break;

  case 100: /* and_key: AND  */
#line 905 "yacc_sql.y"
                    {
			Condition condition;
			condition_init_with_comp(&condition, NO_OP);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		}
#line 2259 "yacc_sql.tab.c"
    break;

  case 101: /* expression: expression PLUS expression  */
#line 913 "yacc_sql.y"
                                  { 
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "+");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
		//$$=$1+$3; 
		}
#line 2271 "yacc_sql.tab.c"
    break;

  case 102: /* expression: expression MINUS expression  */
#line 920 "yacc_sql.y"
                                   { 
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "-");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);

		//$$=$1-$3; 
		}
#line 2284 "yacc_sql.tab.c"
    break;

  case 103: /* expression: expression STAR expression  */
#line 928 "yacc_sql.y"
                                  { 
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "*");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);

		//$$=$1*$3; 
		}
#line 2297 "yacc_sql.tab.c"
    break;

  case 104: /* expression: expression DIVE expression  */
#line 936 "yacc_sql.y"
                                 {
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "/");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
        }
#line 2308 "yacc_sql.tab.c"
    break;

  case 105: /* expression: MINUS expression  */
#line 942 "yacc_sql.y"
                                        { 
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "u");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
		//$$=-$2; 
		}
#line 2320 "yacc_sql.tab.c"
    break;

  case 106: /* expression: LBRACE expression RBRACE  */
#line 949 "yacc_sql.y"
                               {
		//$$=$2; 
		}
#line 2328 "yacc_sql.tab.c"
    break;

  case 107: /* expression: value  */
#line 952 "yacc_sql.y"
            { 
		Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
		ExpNode expnode;
		expnode_init(&expnode, 1, value, NULL, NULL);
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
		//$$=$1; 
		}
#line 2341 "yacc_sql.tab.c"
    break;

  case 108: /* expression: ID  */
#line 960 "yacc_sql.y"
             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		ExpNode expnode;
		expnode_init(&expnode,2, NULL, &attr, NULL);
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
	}
#line 2354 "yacc_sql.tab.c"
    break;

  case 109: /* expression: ID DOT ID  */
#line 968 "yacc_sql.y"
                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		ExpNode expnode;
		expnode_init(&expnode,2, NULL, &attr, NULL);
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);

	}
#line 2368 "yacc_sql.tab.c"
    break;

  case 110: /* condition: ID comOp value  */
#line 982 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);

			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2390 "yacc_sql.tab.c"
    break;

  case 111: /* condition: value comOp value  */
#line 1000 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2411 "yacc_sql.tab.c"
    break;

  case 112: /* condition: ID comOp ID  */
#line 1017 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));
			condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 2432 "yacc_sql.tab.c"
    break;

  case 113: /* condition: value comOp ID  */
#line 1034 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));
			condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
#line 2455 "yacc_sql.tab.c"
    break;

  case 114: /* condition: ID DOT ID comOp value  */
#line 1053 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
#line 2477 "yacc_sql.tab.c"
    break;

  case 115: /* condition: value comOp ID DOT ID  */
#line 1071 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
#line 2500 "yacc_sql.tab.c"
    break;

  case 116: /* condition: ID DOT ID comOp ID DOT ID  */
#line 1090 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));
			condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 2520 "yacc_sql.tab.c"
    break;

  case 117: /* condition: ID comOp expression_attr  */
#line 1105 "yacc_sql.y"
                                  {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		condition_init_exp(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 1, &left_attr, NULL, NULL, 2, NULL, NULL, &CONTEXT->exp[CONTEXT->exp_length-1]);

	}
#line 2531 "yacc_sql.tab.c"
    break;

  case 118: /* condition: ID DOT ID comOp expression_attr  */
#line 1111 "yacc_sql.y"
                                         {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
		condition_init_exp(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 1, &left_attr, NULL, NULL, 2, NULL, NULL, &CONTEXT->exp[CONTEXT->exp_length-1]);

	}
#line 2542 "yacc_sql.tab.c"
    break;

  case 119: /* condition: value comOp expression_attr  */
#line 1117 "yacc_sql.y"
                                     {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		condition_init_exp(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 0, NULL, left_value, NULL, 2, NULL, NULL, &CONTEXT->exp[CONTEXT->exp_length-1]);


	}
#line 2553 "yacc_sql.tab.c"
    break;

  case 120: /* condition: expression_attr comOp expression_attr  */
#line 1123 "yacc_sql.y"
                                                {
		// exp_swap_with_other(&CONTEXT->exp_pool[CONTEXT->exp_pool_length], &CONTEXT->exp[0]);
		// CONTEXT->exp_pool_length++ ;
		// exp_swap_with_other(&CONTEXT->exp_pool[CONTEXT->exp_pool_length], &CONTEXT->exp[1]);

		condition_init_exp(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 2, NULL, NULL, &CONTEXT->exp[CONTEXT->exp_length-2], 2, NULL, NULL, &CONTEXT->exp[CONTEXT->exp_length-1]);
		// CONTEXT->exp_length++;
		CONTEXT->exp_length = CONTEXT->exp_length % MAX_EXP_TMP_NUM;
		// 将临时变量清空
		//  exp_destroy(&CONTEXT->exp[0]);
		//  exp_destroy(&CONTEXT->exp[1]);
		
	}
#line 2571 "yacc_sql.tab.c"
    break;

  case 121: /* condition: value IS NULL_T  */
#line 1136 "yacc_sql.y"
                          {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, left_value, 0, NULL, &right_value);
	}
#line 2582 "yacc_sql.tab.c"
    break;

  case 122: /* condition: value IS NOTNULL  */
#line 1142 "yacc_sql.y"
                           {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 0, NULL, left_value, 0, NULL, &right_value);
	}
#line 2593 "yacc_sql.tab.c"
    break;

  case 123: /* condition: ID IS NULL_T  */
#line 1148 "yacc_sql.y"
                       {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 1, &left_attr, NULL, 0, NULL, &right_value);
	}
#line 2605 "yacc_sql.tab.c"
    break;

  case 124: /* condition: ID IS NOTNULL  */
#line 1155 "yacc_sql.y"
                        {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 1, &left_attr, NULL, 0, NULL, &right_value);
	}
#line 2617 "yacc_sql.tab.c"
    break;

  case 125: /* condition: ID DOT ID IS NULL_T  */
#line 1162 "yacc_sql.y"
                              {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 1, &left_attr, NULL, 0, NULL, &right_value);

	}
#line 2630 "yacc_sql.tab.c"
    break;

  case 126: /* condition: ID DOT ID IS NOTNULL  */
#line 1170 "yacc_sql.y"
                               {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
		Value right_value;	
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 1, &left_attr, NULL, 0, NULL, &right_value);
	}
#line 2642 "yacc_sql.tab.c"
    break;

  case 127: /* condition: NULL_T IS value  */
#line 1177 "yacc_sql.y"
                         {
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Value left_value;
		value_init_null(&left_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, &left_value, 0, NULL, right_value);
	}
#line 2653 "yacc_sql.tab.c"
    break;

  case 128: /* condition: NULL_T IS ID  */
#line 1184 "yacc_sql.y"
                       {
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));
		Value left_value;
		value_init_null(&left_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, &left_value, 1, &right_attr, NULL);
	}
#line 2665 "yacc_sql.tab.c"
    break;

  case 129: /* condition: NULL_T IS ID DOT ID  */
#line 1192 "yacc_sql.y"
                             {
		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));
		Value left_value;
		value_init_null(&left_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, &left_value, 1, &right_attr, NULL);
	}
#line 2677 "yacc_sql.tab.c"
    break;

  case 130: /* condition: NULL_T IS NOTNULL  */
#line 1200 "yacc_sql.y"
                            {
		Value left_value;
		value_init_null(&left_value, 0);
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 0, NULL, &left_value, 0, NULL, &right_value);
	}
#line 2689 "yacc_sql.tab.c"
    break;

  case 131: /* condition: ID in_or_not_in select  */
#line 1208 "yacc_sql.y"
                                 {

		// //临时变量退栈
		// CONTEXT->select_length--;
		// CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
		// CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
		// CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

		CONTEXT->conditions[CONTEXT->condition_length - 1].left_is_attr = 1;
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));	
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_attr = 	left_attr;
	}
#line 2707 "yacc_sql.tab.c"
    break;

  case 132: /* condition: ID DOT ID in_or_not_in select  */
#line 1222 "yacc_sql.y"
                                       {

		//临时变量退栈
		// CONTEXT->select_length--;
		// CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
		// CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
		// CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

		CONTEXT->conditions[CONTEXT->condition_length - 1].left_is_attr = 1;
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));	
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_attr = 	left_attr;
	}
#line 2725 "yacc_sql.tab.c"
    break;

  case 133: /* condition: ID comOp select  */
#line 1236 "yacc_sql.y"
                         {

		//临时变量退栈
		// CONTEXT->select_length--;
		// CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
		// CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
		// CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = CONTEXT->comp_tmp[CONTEXT->select_length];
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_is_attr = 1;
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));	
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_attr = left_attr;
	}
#line 2744 "yacc_sql.tab.c"
    break;

  case 134: /* condition: ID DOT ID comOp select  */
#line 1251 "yacc_sql.y"
                                {

		//临时变量退栈
		// CONTEXT->select_length--;
		// CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
		// CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
		// CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = CONTEXT->comp_tmp[CONTEXT->select_length];
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_is_attr = 1;
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));	
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_attr = left_attr;
	}
#line 2763 "yacc_sql.tab.c"
    break;

  case 135: /* condition: select comOp ID  */
#line 1266 "yacc_sql.y"
                         {		//放 condition 左边了 改一下符号

		//临时变量退栈
		// CONTEXT->select_length--;
		// CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
		// CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
		// CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

		switch(CONTEXT->comp_tmp[CONTEXT->select_length]){
			case LESS_THAN:
			CONTEXT->comp_tmp[CONTEXT->select_length] = GREAT_THAN;
			break;
			case LESS_EQUAL:
			CONTEXT->comp_tmp[CONTEXT->select_length] = GREAT_EQUAL;
			break;
			case GREAT_THAN:
			CONTEXT->comp_tmp[CONTEXT->select_length] = LESS_THAN;
			break;
			case GREAT_EQUAL:
			CONTEXT->comp_tmp[CONTEXT->select_length] = LESS_EQUAL;
			break;
			default:
			break;
		}

		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = CONTEXT->comp_tmp[CONTEXT->select_length];
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_is_attr = 1;
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[0].string));	
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_attr = left_attr;

	}
#line 2800 "yacc_sql.tab.c"
    break;

  case 136: /* condition: select comOp ID DOT ID  */
#line 1299 "yacc_sql.y"
                                 {

		//临时变量退栈
		// CONTEXT->select_length--;
		// CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
		// CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
		// CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

		//放 condition 左边了 改一下符号
		switch(CONTEXT->comp_tmp[CONTEXT->select_length]){
			case LESS_THAN:
			CONTEXT->comp_tmp[CONTEXT->select_length] = GREAT_THAN;
			break;
			case LESS_EQUAL:
			CONTEXT->comp_tmp[CONTEXT->select_length] = GREAT_EQUAL;
			break;
			case GREAT_THAN:
			CONTEXT->comp_tmp[CONTEXT->select_length] = LESS_THAN;
			break;
			case GREAT_EQUAL:
			CONTEXT->comp_tmp[CONTEXT->select_length] = LESS_EQUAL;
			break;
			default:
			break;
		}

		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = CONTEXT->comp_tmp[CONTEXT->select_length];
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_is_attr = 1;
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-2].string), (yyvsp[0].string));	
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_attr = left_attr;
	}
#line 2837 "yacc_sql.tab.c"
    break;

  case 137: /* condition: select comOp select  */
#line 1332 "yacc_sql.y"
                             {
		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = CONTEXT->comp_tmp[CONTEXT->select_length];
	}
#line 2845 "yacc_sql.tab.c"
    break;

  case 138: /* in_or_not_in: IN  */
#line 1338 "yacc_sql.y"
           {
		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = OP_IN;
	}
#line 2853 "yacc_sql.tab.c"
    break;

  case 139: /* in_or_not_in: NOTIN  */
#line 1341 "yacc_sql.y"
                {
		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = OP_NO_IN;
	}
#line 2861 "yacc_sql.tab.c"
    break;

  case 140: /* comOp: EQ  */
#line 1347 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO;   CONTEXT->comp_tmp[CONTEXT->select_length] = EQUAL_TO; }
#line 2867 "yacc_sql.tab.c"
    break;

  case 141: /* comOp: LT  */
#line 1348 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN;   CONTEXT->comp_tmp[CONTEXT->select_length] = LESS_THAN; }
#line 2873 "yacc_sql.tab.c"
    break;

  case 142: /* comOp: GT  */
#line 1349 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN;   CONTEXT->comp_tmp[CONTEXT->select_length] = GREAT_THAN; }
#line 2879 "yacc_sql.tab.c"
    break;

  case 143: /* comOp: LE  */
#line 1350 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL;   CONTEXT->comp_tmp[CONTEXT->select_length] = LESS_EQUAL; }
#line 2885 "yacc_sql.tab.c"
    break;

  case 144: /* comOp: GE  */
#line 1351 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL;   CONTEXT->comp_tmp[CONTEXT->select_length] = GREAT_EQUAL; }
#line 2891 "yacc_sql.tab.c"
    break;

  case 145: /* comOp: NE  */
#line 1352 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL;  CONTEXT->comp_tmp[CONTEXT->select_length] = NOT_EQUAL; }
#line 2897 "yacc_sql.tab.c"
    break;

  case 147: /* order_by: ORDERBY order_by_attr order_by_list  */
#line 1358 "yacc_sql.y"
                                              {
		
	}
#line 2905 "yacc_sql.tab.c"
    break;

  case 149: /* order_by_list: COMMA order_by_attr order_by_list  */
#line 1364 "yacc_sql.y"
                                            {
			
	}
#line 2913 "yacc_sql.tab.c"
    break;

  case 150: /* order_by_attr: ID order_by_type  */
#line 1370 "yacc_sql.y"
                         {	
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_orderbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
#line 2923 "yacc_sql.tab.c"
    break;

  case 151: /* order_by_attr: ID DOT ID order_by_type  */
#line 1375 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_orderbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
#line 2933 "yacc_sql.tab.c"
    break;

  case 152: /* order_by_type: %empty  */
#line 1382 "yacc_sql.y"
                   {
		CONTEXT->order_by_type = 0;
	}
#line 2941 "yacc_sql.tab.c"
    break;

  case 153: /* order_by_type: ASC  */
#line 1385 "yacc_sql.y"
              {
		CONTEXT->order_by_type = 0;
	}
#line 2949 "yacc_sql.tab.c"
    break;

  case 154: /* order_by_type: DESC  */
#line 1388 "yacc_sql.y"
               {
		CONTEXT->order_by_type = 1;
	}
#line 2957 "yacc_sql.tab.c"
    break;

  case 156: /* group_by: GROUPBY group_by_attr group_by_list  */
#line 1395 "yacc_sql.y"
                                              {

	}
#line 2965 "yacc_sql.tab.c"
    break;

  case 158: /* group_by_list: COMMA group_by_attr group_by_list  */
#line 1401 "yacc_sql.y"
                                            {
			
	}
#line 2973 "yacc_sql.tab.c"
    break;

  case 159: /* group_by_attr: ID order_by_type  */
#line 1407 "yacc_sql.y"
                         {	
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_groupbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
#line 2983 "yacc_sql.tab.c"
    break;

  case 160: /* group_by_attr: ID DOT ID order_by_type  */
#line 1412 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_groupbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
#line 2993 "yacc_sql.tab.c"
    break;

  case 161: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 1422 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 3002 "yacc_sql.tab.c"
    break;


#line 3006 "yacc_sql.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (scanner, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1427 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));
	printf("context size = %d B\n",sizeof(context));
	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
