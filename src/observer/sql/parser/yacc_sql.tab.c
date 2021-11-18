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
  Exp exp[2];
  int exp_length;
	Selects selects[5];

	int selects_tmp_pool_length;
	Selects selects_tmp_pool[5];
	Exp exp_pool[5];
	int exp_pool_length;
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


#line 146 "yacc_sql.tab.c"

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
  YYSYMBOL_STRING_T = 24,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 25,                   /* FLOAT_T  */
  YYSYMBOL_NULL_T = 26,                    /* NULL_T  */
  YYSYMBOL_HELP = 27,                      /* HELP  */
  YYSYMBOL_EXIT = 28,                      /* EXIT  */
  YYSYMBOL_DOT = 29,                       /* DOT  */
  YYSYMBOL_INTO = 30,                      /* INTO  */
  YYSYMBOL_VALUES = 31,                    /* VALUES  */
  YYSYMBOL_FROM = 32,                      /* FROM  */
  YYSYMBOL_WHERE = 33,                     /* WHERE  */
  YYSYMBOL_AND = 34,                       /* AND  */
  YYSYMBOL_SET = 35,                       /* SET  */
  YYSYMBOL_ON = 36,                        /* ON  */
  YYSYMBOL_LOAD = 37,                      /* LOAD  */
  YYSYMBOL_DATA = 38,                      /* DATA  */
  YYSYMBOL_INFILE = 39,                    /* INFILE  */
  YYSYMBOL_EQ = 40,                        /* EQ  */
  YYSYMBOL_LT = 41,                        /* LT  */
  YYSYMBOL_GT = 42,                        /* GT  */
  YYSYMBOL_LE = 43,                        /* LE  */
  YYSYMBOL_GE = 44,                        /* GE  */
  YYSYMBOL_NE = 45,                        /* NE  */
  YYSYMBOL_MAX = 46,                       /* MAX  */
  YYSYMBOL_MIN = 47,                       /* MIN  */
  YYSYMBOL_COUNT = 48,                     /* COUNT  */
  YYSYMBOL_AVG = 49,                       /* AVG  */
  YYSYMBOL_ORDERBY = 50,                   /* ORDERBY  */
  YYSYMBOL_ASC = 51,                       /* ASC  */
  YYSYMBOL_INNERJOIN = 52,                 /* INNERJOIN  */
  YYSYMBOL_UNIQUE = 53,                    /* UNIQUE  */
  YYSYMBOL_NULLABLE = 54,                  /* NULLABLE  */
  YYSYMBOL_NOTNULL = 55,                   /* NOTNULL  */
  YYSYMBOL_IS = 56,                        /* IS  */
  YYSYMBOL_GROUPBY = 57,                   /* GROUPBY  */
  YYSYMBOL_IN = 58,                        /* IN  */
  YYSYMBOL_NOTIN = 59,                     /* NOTIN  */
  YYSYMBOL_PLUS = 60,                      /* PLUS  */
  YYSYMBOL_MINUS = 61,                     /* MINUS  */
  YYSYMBOL_DIVE = 62,                      /* DIVE  */
  YYSYMBOL_NUMBER = 63,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 64,                     /* FLOAT  */
  YYSYMBOL_ID = 65,                        /* ID  */
  YYSYMBOL_PATH = 66,                      /* PATH  */
  YYSYMBOL_DATE = 67,                      /* DATE  */
  YYSYMBOL_SSS = 68,                       /* SSS  */
  YYSYMBOL_STAR = 69,                      /* STAR  */
  YYSYMBOL_STRING_V = 70,                  /* STRING_V  */
  YYSYMBOL_POLYKEY = 71,                   /* POLYKEY  */
  YYSYMBOL_UMINUS = 72,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 73,                  /* $accept  */
  YYSYMBOL_commands = 74,                  /* commands  */
  YYSYMBOL_command = 75,                   /* command  */
  YYSYMBOL_exit = 76,                      /* exit  */
  YYSYMBOL_help = 77,                      /* help  */
  YYSYMBOL_sync = 78,                      /* sync  */
  YYSYMBOL_begin = 79,                     /* begin  */
  YYSYMBOL_commit = 80,                    /* commit  */
  YYSYMBOL_rollback = 81,                  /* rollback  */
  YYSYMBOL_drop_table = 82,                /* drop_table  */
  YYSYMBOL_show_tables = 83,               /* show_tables  */
  YYSYMBOL_desc_table = 84,                /* desc_table  */
  YYSYMBOL_create_index = 85,              /* create_index  */
  YYSYMBOL_id_list = 86,                   /* id_list  */
  YYSYMBOL_drop_index = 87,                /* drop_index  */
  YYSYMBOL_create_table = 88,              /* create_table  */
  YYSYMBOL_attr_def_list = 89,             /* attr_def_list  */
  YYSYMBOL_attr_def = 90,                  /* attr_def  */
  YYSYMBOL_null = 91,                      /* null  */
  YYSYMBOL_number = 92,                    /* number  */
  YYSYMBOL_type = 93,                      /* type  */
  YYSYMBOL_ID_get = 94,                    /* ID_get  */
  YYSYMBOL_insert = 95,                    /* insert  */
  YYSYMBOL_values_list = 96,               /* values_list  */
  YYSYMBOL_value_list = 97,                /* value_list  */
  YYSYMBOL_value = 98,                     /* value  */
  YYSYMBOL_delete = 99,                    /* delete  */
  YYSYMBOL_update = 100,                   /* update  */
  YYSYMBOL_select = 101,                   /* select  */
  YYSYMBOL_left_brace = 102,               /* left_brace  */
  YYSYMBOL_select_mix = 103,               /* select_mix  */
  YYSYMBOL_mix_list = 104,                 /* mix_list  */
  YYSYMBOL_poly_value = 105,               /* poly_value  */
  YYSYMBOL_rel_list = 106,                 /* rel_list  */
  YYSYMBOL_inner_join = 107,               /* inner_join  */
  YYSYMBOL_inner_join_on = 108,            /* inner_join_on  */
  YYSYMBOL_where = 109,                    /* where  */
  YYSYMBOL_where_key = 110,                /* where_key  */
  YYSYMBOL_condition_list = 111,           /* condition_list  */
  YYSYMBOL_and_key = 112,                  /* and_key  */
  YYSYMBOL_expression = 113,               /* expression  */
  YYSYMBOL_condition = 114,                /* condition  */
  YYSYMBOL_in_or_not_in = 115,             /* in_or_not_in  */
  YYSYMBOL_comOp = 116,                    /* comOp  */
  YYSYMBOL_order_by = 117,                 /* order_by  */
  YYSYMBOL_order_by_list = 118,            /* order_by_list  */
  YYSYMBOL_order_by_attr = 119,            /* order_by_attr  */
  YYSYMBOL_order_by_type = 120,            /* order_by_type  */
  YYSYMBOL_group_by = 121,                 /* group_by  */
  YYSYMBOL_group_by_list = 122,            /* group_by_list  */
  YYSYMBOL_group_by_attr = 123,            /* group_by_attr  */
  YYSYMBOL_load_data = 124                 /* load_data  */
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
#define YYLAST   364

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  153
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  330

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   327


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
      65,    66,    67,    68,    69,    70,    71,    72
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   178,   178,   180,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   204,   209,   214,   220,   226,   232,   238,   244,   250,
     257,   263,   270,   272,   278,   285,   294,   296,   300,   311,
     325,   328,   331,   337,   340,   341,   342,   343,   344,   347,
     356,   372,   374,   382,   386,   391,   395,   398,   401,   405,
     411,   421,   432,   449,   483,   492,   497,   503,   508,   513,
     522,   532,   540,   548,   559,   561,   567,   572,   577,   585,
     595,   603,   611,   757,   764,   771,   844,   846,   851,   853,
     858,   864,   866,   871,   878,   880,   885,   893,   900,   908,
     916,   922,   925,   933,   941,   954,   972,   989,  1006,  1025,
    1043,  1062,  1078,  1090,  1096,  1102,  1109,  1116,  1124,  1131,
    1138,  1146,  1154,  1162,  1176,  1190,  1205,  1220,  1253,  1286,
    1292,  1295,  1301,  1302,  1303,  1304,  1305,  1306,  1310,  1312,
    1316,  1318,  1324,  1329,  1336,  1339,  1342,  1347,  1349,  1353,
    1355,  1361,  1366,  1375
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
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "DATE_T", "STRING_T", "FLOAT_T",
  "NULL_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE",
  "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT", "LE",
  "GE", "NE", "MAX", "MIN", "COUNT", "AVG", "ORDERBY", "ASC", "INNERJOIN",
  "UNIQUE", "NULLABLE", "NOTNULL", "IS", "GROUPBY", "IN", "NOTIN", "PLUS",
  "MINUS", "DIVE", "NUMBER", "FLOAT", "ID", "PATH", "DATE", "SSS", "STAR",
  "STRING_V", "POLYKEY", "UMINUS", "$accept", "commands", "command",
  "exit", "help", "sync", "begin", "commit", "rollback", "drop_table",
  "show_tables", "desc_table", "create_index", "id_list", "drop_index",
  "create_table", "attr_def_list", "attr_def", "null", "number", "type",
  "ID_get", "insert", "values_list", "value_list", "value", "delete",
  "update", "select", "left_brace", "select_mix", "mix_list", "poly_value",
  "rel_list", "inner_join", "inner_join_on", "where", "where_key",
  "condition_list", "and_key", "expression", "condition", "in_or_not_in",
  "comOp", "order_by", "order_by_list", "order_by_attr", "order_by_type",
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
     325,   326,   327
};
#endif

#define YYPACT_NINF (-277)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -277,   173,  -277,    17,    23,   133,   -49,    32,    70,    58,
      81,    51,  -277,   115,   127,   128,   130,   143,   110,  -277,
    -277,  -277,  -277,  -277,  -277,  -277,  -277,  -277,  -277,  -277,
    -277,  -277,  -277,  -277,  -277,  -277,   148,  -277,   114,   131,
     151,   132,   141,    20,  -277,   164,   163,   223,   225,  -277,
     186,   189,   220,  -277,  -277,  -277,  -277,  -277,   190,   133,
     245,   226,   205,   268,   269,   134,    78,  -277,   144,   208,
    -277,  -277,   244,   241,   211,   209,   246,   214,   215,   247,
    -277,  -277,    86,   265,   264,   264,  -277,  -277,    11,  -277,
     267,   270,   271,   272,  -277,   282,    28,   250,   256,   227,
    -277,   273,   243,   277,   229,    93,  -277,   195,  -277,  -277,
     264,   101,   264,   264,   230,   248,    97,  -277,    61,   240,
    -277,  -277,   174,  -277,  -277,    94,   203,   180,   263,    97,
     292,   271,   214,   284,  -277,  -277,  -277,  -277,  -277,    -2,
     234,   286,   264,   264,    57,   287,   288,  -277,   289,   290,
    -277,  -277,   271,   238,   241,  -277,   291,    61,   279,  -277,
      -5,    77,   249,  -277,  -277,  -277,  -277,  -277,  -277,    -9,
    -277,  -277,    63,    34,    -7,    88,     4,    61,    61,    61,
      61,    61,  -277,  -277,    28,   241,   251,   248,   273,   307,
    -277,  -277,   295,   294,   252,  -277,  -277,   264,   162,   264,
     264,   264,   264,  -277,   283,   258,    97,   296,   253,  -277,
    -277,   293,  -277,   194,  -277,  -277,  -277,  -277,  -277,  -277,
    -277,  -277,   297,  -277,   298,  -277,   112,   112,  -277,  -277,
     107,   263,   317,   318,   241,  -277,  -277,   260,   259,   308,
     294,  -277,   311,   312,  -277,  -277,  -277,  -277,  -277,    28,
     266,   280,   291,   314,  -277,   274,    45,    63,    42,   275,
     276,  -277,  -277,  -277,   258,  -277,   316,   294,   331,   319,
     264,   264,   263,    16,   320,   278,   332,  -277,   321,   339,
    -277,  -277,  -277,  -277,   315,  -277,  -277,  -277,  -277,   280,
    -277,  -277,  -277,   342,  -277,  -277,   248,  -277,   281,  -277,
    -277,   266,  -277,    98,   329,  -277,    97,  -277,   285,   334,
    -277,  -277,     8,   320,   299,  -277,   278,  -277,   291,  -277,
    -277,  -277,  -277,     8,   329,   335,  -277,  -277,   314,  -277
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    64,     0,     0,     0,     0,     0,     0,     3,
      20,    19,    14,    15,    16,    17,     9,    10,    11,    12,
      13,     8,     5,     7,     6,     4,     0,    18,     0,     0,
       0,     0,     0,    74,    65,     0,     0,     0,     0,    23,
       0,     0,     0,    24,    25,    26,    22,    21,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    66,     0,     0,
      29,    28,     0,    91,     0,     0,     0,     0,     0,     0,
      27,    34,    74,     0,    74,    74,    83,    84,     0,    85,
       0,     0,    86,     0,    93,     0,     0,     0,     0,     0,
      49,    36,     0,     0,     0,     0,    75,     0,    67,    68,
      74,     0,    74,    74,     0,    88,     0,    60,    64,    59,
      56,    57,   103,    55,    58,   102,     0,     0,    94,     0,
       0,    86,     0,     0,    44,    45,    46,    47,    48,    40,
       0,     0,    74,    74,     0,     0,     0,    71,     0,     0,
      70,    69,    86,     0,    91,    59,    53,     0,   103,   102,
       0,     0,     0,   132,   133,   134,   135,   136,   137,     0,
     130,   131,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    96,    92,     0,    91,     0,    88,    36,     0,
      42,    41,    39,    32,     0,    76,    77,    74,     0,    74,
      74,    74,    74,    87,     0,   147,     0,     0,     0,   101,
     122,   120,   119,   104,   115,   116,   123,   107,   105,   125,
     113,   114,   108,   106,   127,   129,    97,    98,   100,    99,
     112,    94,     0,     0,    91,    37,    35,     0,     0,     0,
      32,    80,     0,     0,    79,    78,    72,    73,    90,     0,
       0,   138,    53,    51,   104,     0,     0,     0,     0,     0,
       0,    95,    61,   153,   147,    43,     0,    32,     0,     0,
      74,    74,    94,   144,   149,     0,     0,    54,     0,     0,
     121,   117,   118,   124,     0,   109,   126,   110,   128,   138,
      38,    33,    30,     0,    81,    82,    88,   146,     0,   145,
     151,     0,   148,   144,   140,    62,     0,    50,     0,     0,
      31,    89,   144,   149,     0,   142,     0,   139,    53,   111,
      63,   152,   150,   144,   140,     0,   143,   141,    51,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -277,  -277,  -277,  -277,  -277,  -277,  -277,  -277,  -277,  -277,
    -277,  -277,  -277,  -225,  -277,  -277,   160,   217,  -277,  -277,
    -277,  -277,  -277,    25,  -243,   -95,  -277,  -277,    -1,  -277,
     300,   -80,   254,  -117,  -184,  -277,  -144,  -277,  -207,  -277,
     -96,  -173,   142,  -119,    65,    33,    40,  -276,    96,    49,
      62,  -277
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,   239,    30,    31,   133,   101,   192,   266,
     139,   102,    32,   279,   207,   159,    33,    34,   126,    36,
      46,    67,    91,   115,   154,   249,    95,    96,   183,   184,
     127,   128,   172,   173,   276,   317,   304,   300,   251,   302,
     274,    37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      35,   125,   106,   234,   108,   109,   175,   176,   181,   277,
     205,   231,   209,     5,   187,   269,    47,   214,   297,   220,
      12,   156,   160,    38,   261,    39,   297,   315,   110,    41,
     147,    42,   150,   151,   185,   203,   321,     5,    65,    48,
     111,   232,   291,     5,   118,   298,   215,   326,   221,    66,
      12,     5,   190,   191,   119,   177,   178,   179,    12,   299,
     155,   160,   195,   196,   180,   296,   212,   299,   155,   224,
      40,   281,     5,    49,   197,   325,   272,   157,   218,    12,
     223,   226,   227,   228,   229,   230,   198,   155,    50,   125,
     264,   120,   121,   122,   258,   123,   124,   120,   121,   217,
     282,   123,   124,   155,    65,   120,   121,   284,   297,   123,
     124,   252,   311,    51,   155,   105,    52,   241,    53,   244,
     245,   246,   247,   155,   120,   121,   158,   314,   123,   124,
      54,    55,   210,    56,   163,   164,   165,   166,   167,   168,
     120,   121,   211,    84,   123,   124,    57,    85,    58,   299,
     174,   120,   121,   222,   125,   123,   124,    59,   142,    62,
     120,   121,   143,   285,   123,   124,   148,   177,   178,   179,
     149,   216,   219,     2,   179,   225,   180,     3,     4,    60,
      68,   180,     5,     6,     7,     8,     9,    10,    11,    12,
     294,   295,    13,    14,    15,    69,    61,    63,    43,    82,
      16,    17,    44,   162,    45,    83,    64,    86,    87,    88,
      18,   318,    89,    90,   163,   164,   165,   166,   167,   168,
     163,   164,   165,   166,   167,   168,    70,   242,    71,    75,
     169,   243,   170,   171,   163,   164,   165,   166,   167,   168,
     177,   178,   179,   163,   164,   165,   166,   167,   168,   180,
     256,    72,   170,   171,    73,    74,   283,   286,    86,    87,
     144,    77,    78,    89,   145,   134,   135,   136,   137,   138,
      79,    80,    81,    92,    94,    93,    97,    98,    99,   100,
     103,   107,    65,   104,   112,   117,   130,   113,   116,   114,
     129,   132,   131,   140,   141,   152,   161,   182,   186,   193,
     153,   189,   194,   204,   199,   200,   201,   202,   208,   206,
     236,   237,   238,   253,   213,   250,   233,   240,   254,   248,
     262,   263,   255,   265,   267,   268,   259,   260,   270,   271,
     275,   273,   278,   290,   292,   305,   293,   306,   301,   280,
     287,   288,   307,   303,   308,   310,   312,   316,   235,   188,
     319,   320,   328,   329,   309,   257,   324,   327,     0,    76,
     289,   146,   322,   313,   323
};

static const yytype_int16 yycheck[] =
{
       1,    96,    82,   187,    84,    85,   125,   126,   127,   252,
     154,   184,    17,     9,   131,   240,    65,    26,    10,    26,
      16,   116,   118,     6,   231,     8,    10,   303,    17,     6,
     110,     8,   112,   113,   129,   152,   312,     9,    18,     7,
      29,   185,   267,     9,    16,    29,    55,   323,    55,    29,
      16,     9,    54,    55,    26,    60,    61,    62,    16,    51,
      26,   157,   142,   143,    69,   272,   161,    51,    26,    65,
      53,    26,     9,     3,    17,   318,   249,    16,   173,    16,
     175,   177,   178,   179,   180,   181,    29,    26,    30,   184,
     234,    63,    64,    65,   213,    67,    68,    63,    64,    65,
      55,    67,    68,    26,    18,    63,    64,    65,    10,    67,
      68,   206,   296,    32,    26,    29,    65,   197,     3,   199,
     200,   201,   202,    26,    63,    64,    65,    29,    67,    68,
       3,     3,    55,     3,    40,    41,    42,    43,    44,    45,
      63,    64,    65,    65,    67,    68,     3,    69,    38,    51,
      56,    63,    64,    65,   249,    67,    68,     9,    65,     8,
      63,    64,    69,   258,    67,    68,    65,    60,    61,    62,
      69,   172,   173,     0,    62,   176,    69,     4,     5,    65,
      16,    69,     9,    10,    11,    12,    13,    14,    15,    16,
     270,   271,    19,    20,    21,    32,    65,    65,    65,    65,
      27,    28,    69,    29,    71,    71,    65,    63,    64,    65,
      37,   306,    68,    69,    40,    41,    42,    43,    44,    45,
      40,    41,    42,    43,    44,    45,     3,    65,     3,    39,
      56,    69,    58,    59,    40,    41,    42,    43,    44,    45,
      60,    61,    62,    40,    41,    42,    43,    44,    45,    69,
      56,    65,    58,    59,    65,    35,   257,   258,    63,    64,
      65,    16,    36,    68,    69,    22,    23,    24,    25,    26,
      65,     3,     3,    65,    33,    31,    65,    68,    32,    65,
      65,    16,    18,    36,    17,     3,    30,    17,    16,    18,
      40,    18,    65,    16,    65,    65,    56,    34,     6,    65,
      52,    17,    16,    65,    17,    17,    17,    17,    29,    18,
       3,    16,    18,    17,    65,    57,    65,    65,    65,    36,
       3,     3,    29,    63,    65,    17,    29,    29,    17,    17,
      50,    65,    18,    17,     3,     3,    17,    16,    18,    65,
      65,    65,     3,    65,    29,     3,    65,    18,   188,   132,
      65,    17,    17,   328,   289,   213,   316,   324,    -1,    59,
     264,   107,   313,   301,    65
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    74,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    16,    19,    20,    21,    27,    28,    37,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      87,    88,    95,    99,   100,   101,   102,   124,     6,     8,
      53,     6,     8,    65,    69,    71,   103,    65,     7,     3,
      30,    32,    65,     3,     3,     3,     3,     3,    38,     9,
      65,    65,     8,    65,    65,    18,    29,   104,    16,    32,
       3,     3,    65,    65,    35,    39,   103,    16,    36,    65,
       3,     3,    65,    71,    65,    69,    63,    64,    65,    68,
      69,   105,    65,    31,    33,   109,   110,    65,    68,    32,
      65,    90,    94,    65,    36,    29,   104,    16,   104,   104,
      17,    29,    17,    17,    18,   106,    16,     3,    16,    26,
      63,    64,    65,    67,    68,    98,   101,   113,   114,    40,
      30,    65,    18,    89,    22,    23,    24,    25,    26,    93,
      16,    65,    65,    69,    65,    69,   105,   104,    65,    69,
     104,   104,    65,    52,   107,    26,    98,    16,    65,    98,
     113,    56,    29,    40,    41,    42,    43,    44,    45,    56,
      58,    59,   115,   116,    56,   116,   116,    60,    61,    62,
      69,   116,    34,   111,   112,    98,     6,   106,    90,    17,
      54,    55,    91,    65,    16,   104,   104,    17,    29,    17,
      17,    17,    17,   106,    65,   109,    18,    97,    29,    17,
      55,    65,    98,    65,    26,    55,   101,    65,    98,   101,
      26,    55,    65,    98,    65,   101,   113,   113,   113,   113,
     113,   114,   109,    65,   107,    89,     3,    16,    18,    86,
      65,   104,    65,    69,   104,   104,   104,   104,    36,   108,
      57,   121,    98,    17,    65,    29,    56,   115,   116,    29,
      29,   111,     3,     3,   109,    63,    92,    65,    17,    86,
      17,    17,   114,    65,   123,    50,   117,    97,    18,    96,
      65,    26,    55,   101,    65,    98,   101,    65,    65,   121,
      17,    86,     3,    17,   104,   104,   111,    10,    29,    51,
     120,    18,   122,    65,   119,     3,    16,     3,    29,   117,
       3,   107,    65,   123,    29,   120,    18,   118,    98,    65,
      17,   120,   122,    65,   119,    97,   120,   118,    17,    96
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    73,    74,    74,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    85,    86,    86,    87,    88,    89,    89,    90,    90,
      91,    91,    91,    92,    93,    93,    93,    93,    93,    94,
      95,    96,    96,    97,    97,    98,    98,    98,    98,    98,
      99,   100,   101,   101,   102,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   105,   105,   105,   106,   106,   107,   107,
     108,   109,   109,   110,   111,   111,   112,   113,   113,   113,
     113,   113,   113,   113,   113,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     115,   115,   116,   116,   116,   116,   116,   116,   117,   117,
     118,   118,   119,   119,   120,   120,   120,   121,   121,   122,
     122,   123,   123,   124
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
      10,    11,     0,     3,     4,     8,     0,     3,     6,     3,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
      10,     0,     6,     0,     3,     1,     1,     1,     1,     1,
       5,     8,    10,    11,     1,     1,     2,     4,     4,     5,
       5,     5,     7,     7,     0,     3,     5,     5,     6,     6,
       6,     8,     8,     1,     1,     1,     0,     3,     0,     6,
       1,     0,     3,     1,     0,     3,     1,     3,     3,     3,
       3,     3,     1,     1,     3,     3,     3,     3,     3,     5,
       5,     7,     3,     3,     3,     3,     3,     5,     5,     3,
       3,     5,     3,     3,     5,     3,     5,     3,     5,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     3,
       0,     3,     2,     4,     0,     1,     1,     0,     3,     0,
       3,     2,     4,     8
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
#line 204 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1502 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 209 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1510 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 214 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1518 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 220 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1526 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 226 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1534 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 232 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1542 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 238 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1551 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 244 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1559 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 250 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1568 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 258 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
		}
#line 1578 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 264 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));			
		}
#line 1588 "yacc_sql.tab.c"
    break;

  case 33: /* id_list: COMMA ID id_list  */
#line 272 "yacc_sql.y"
                   {
	create_index_append_attribute(&CONTEXT->ssql->sstr.create_index,(yyvsp[-1].string));
}
#line 1596 "yacc_sql.tab.c"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 279 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1605 "yacc_sql.tab.c"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 286 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1617 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 296 "yacc_sql.y"
                                   {    }
#line 1623 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type null LBRACE number RBRACE  */
#line 301 "yacc_sql.y"
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
#line 1638 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type null  */
#line 312 "yacc_sql.y"
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
#line 1653 "yacc_sql.tab.c"
    break;

  case 40: /* null: %empty  */
#line 325 "yacc_sql.y"
                   {
		CONTEXT->nullable = 0;
	}
#line 1661 "yacc_sql.tab.c"
    break;

  case 41: /* null: NOTNULL  */
#line 328 "yacc_sql.y"
                  {
		CONTEXT->nullable = 0;
	}
#line 1669 "yacc_sql.tab.c"
    break;

  case 42: /* null: NULLABLE  */
#line 331 "yacc_sql.y"
                   {
		CONTEXT->nullable = 1;
	}
#line 1677 "yacc_sql.tab.c"
    break;

  case 43: /* number: NUMBER  */
#line 337 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1683 "yacc_sql.tab.c"
    break;

  case 44: /* type: INT_T  */
#line 340 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1689 "yacc_sql.tab.c"
    break;

  case 45: /* type: DATE_T  */
#line 341 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1695 "yacc_sql.tab.c"
    break;

  case 46: /* type: STRING_T  */
#line 342 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1701 "yacc_sql.tab.c"
    break;

  case 47: /* type: FLOAT_T  */
#line 343 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1707 "yacc_sql.tab.c"
    break;

  case 48: /* type: NULL_T  */
#line 344 "yacc_sql.y"
                    {(yyval.number)=NULLS;}
#line 1713 "yacc_sql.tab.c"
    break;

  case 49: /* ID_get: ID  */
#line 348 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1722 "yacc_sql.tab.c"
    break;

  case 50: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE values_list SEMICOLON  */
#line 357 "yacc_sql.y"
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
#line 1740 "yacc_sql.tab.c"
    break;

  case 52: /* values_list: COMMA LBRACE value value_list RBRACE values_list  */
#line 374 "yacc_sql.y"
                                                  {
	//inserts_append_tuple(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
	//临时变量清零
    //CONTEXT->value_length=0;
}
#line 1750 "yacc_sql.tab.c"
    break;

  case 53: /* value_list: %empty  */
#line 382 "yacc_sql.y"
                {
		inserts_append_tuple(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
#line 1759 "yacc_sql.tab.c"
    break;

  case 54: /* value_list: COMMA value value_list  */
#line 386 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1767 "yacc_sql.tab.c"
    break;

  case 55: /* value: DATE  */
#line 391 "yacc_sql.y"
             {
			(yyvsp[0].date) = substr((yyvsp[0].date),1,strlen((yyvsp[0].date))-2);
  		value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].date));
		}
#line 1776 "yacc_sql.tab.c"
    break;

  case 56: /* value: NUMBER  */
#line 395 "yacc_sql.y"
           {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1784 "yacc_sql.tab.c"
    break;

  case 57: /* value: FLOAT  */
#line 398 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1792 "yacc_sql.tab.c"
    break;

  case 58: /* value: SSS  */
#line 401 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1801 "yacc_sql.tab.c"
    break;

  case 59: /* value: NULL_T  */
#line 405 "yacc_sql.y"
                {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++], 0);
	}
#line 1809 "yacc_sql.tab.c"
    break;

  case 60: /* delete: DELETE FROM ID where SEMICOLON  */
#line 412 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1821 "yacc_sql.tab.c"
    break;

  case 61: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 422 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1833 "yacc_sql.tab.c"
    break;

  case 62: /* select: SELECT select_mix FROM ID rel_list inner_join where group_by order_by SEMICOLON  */
#line 433 "yacc_sql.y"
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
#line 1853 "yacc_sql.tab.c"
    break;

  case 63: /* select: left_brace SELECT select_mix FROM ID rel_list inner_join where group_by order_by RBRACE  */
#line 450 "yacc_sql.y"
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
#line 1888 "yacc_sql.tab.c"
    break;

  case 64: /* left_brace: LBRACE  */
#line 483 "yacc_sql.y"
               {
		CONTEXT->condition_length_tmp[CONTEXT->select_length] = CONTEXT->condition_length;
		CONTEXT->value_length_tmp[CONTEXT->select_length] = CONTEXT->value_length;
		CONTEXT->from_length_tmp[CONTEXT->select_length] = CONTEXT->from_length;
		CONTEXT->select_length++;
	}
#line 1899 "yacc_sql.tab.c"
    break;

  case 65: /* select_mix: STAR  */
#line 492 "yacc_sql.y"
             {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 1909 "yacc_sql.tab.c"
    break;

  case 66: /* select_mix: ID mix_list  */
#line 497 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);

		}
#line 1920 "yacc_sql.tab.c"
    break;

  case 67: /* select_mix: ID DOT ID mix_list  */
#line 503 "yacc_sql.y"
                             {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 1930 "yacc_sql.tab.c"
    break;

  case 68: /* select_mix: ID DOT STAR mix_list  */
#line 508 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 1940 "yacc_sql.tab.c"
    break;

  case 69: /* select_mix: POLYKEY LBRACE poly_value RBRACE mix_list  */
#line 513 "yacc_sql.y"
                                                   {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
		//select_append_poly_lsn(&CONTEXT->selects[CONTEXT->select_length]);
		
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		}
#line 1954 "yacc_sql.tab.c"
    break;

  case 70: /* select_mix: POLYKEY LBRACE STAR RBRACE mix_list  */
#line 522 "yacc_sql.y"
                                             {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
#line 1969 "yacc_sql.tab.c"
    break;

  case 71: /* select_mix: POLYKEY LBRACE ID RBRACE mix_list  */
#line 532 "yacc_sql.y"
                                           {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
		}
#line 1982 "yacc_sql.tab.c"
    break;

  case 72: /* select_mix: POLYKEY LBRACE ID DOT ID RBRACE mix_list  */
#line 540 "yacc_sql.y"
                                                  {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-6].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
	}
#line 1995 "yacc_sql.tab.c"
    break;

  case 73: /* select_mix: POLYKEY LBRACE ID DOT STAR RBRACE mix_list  */
#line 548 "yacc_sql.y"
                                                    {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-6].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
	}
#line 2008 "yacc_sql.tab.c"
    break;

  case 75: /* mix_list: COMMA ID mix_list  */
#line 561 "yacc_sql.y"
                             {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);

		}
#line 2019 "yacc_sql.tab.c"
    break;

  case 76: /* mix_list: COMMA ID DOT ID mix_list  */
#line 567 "yacc_sql.y"
                                   {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 2029 "yacc_sql.tab.c"
    break;

  case 77: /* mix_list: COMMA ID DOT STAR mix_list  */
#line 572 "yacc_sql.y"
                                     {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 2039 "yacc_sql.tab.c"
    break;

  case 78: /* mix_list: COMMA POLYKEY LBRACE poly_value RBRACE mix_list  */
#line 577 "yacc_sql.y"
                                                         {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
		
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		}
#line 2052 "yacc_sql.tab.c"
    break;

  case 79: /* mix_list: COMMA POLYKEY LBRACE STAR RBRACE mix_list  */
#line 585 "yacc_sql.y"
                                                   {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
#line 2067 "yacc_sql.tab.c"
    break;

  case 80: /* mix_list: COMMA POLYKEY LBRACE ID RBRACE mix_list  */
#line 595 "yacc_sql.y"
                                                 {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
		}
#line 2080 "yacc_sql.tab.c"
    break;

  case 81: /* mix_list: COMMA POLYKEY LBRACE ID DOT ID RBRACE mix_list  */
#line 603 "yacc_sql.y"
                                                        {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-6].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
	}
#line 2093 "yacc_sql.tab.c"
    break;

  case 82: /* mix_list: COMMA POLYKEY LBRACE ID DOT STAR RBRACE mix_list  */
#line 611 "yacc_sql.y"
                                                          {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-6].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
#line 2107 "yacc_sql.tab.c"
    break;

  case 83: /* poly_value: NUMBER  */
#line 757 "yacc_sql.y"
          {	
		RelAttr attr1;
		relation_attr_init_for_number(&attr1, NULL, (yyvsp[0].number));
		selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr1, 0);

  		//value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
#line 2119 "yacc_sql.tab.c"
    break;

  case 84: /* poly_value: FLOAT  */
#line 764 "yacc_sql.y"
          {
		RelAttr attr1;
		relation_attr_init_for_float(&attr1, NULL, (yyvsp[0].floats));
		selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr1, 0);

  		//value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
#line 2131 "yacc_sql.tab.c"
    break;

  case 85: /* poly_value: SSS  */
#line 771 "yacc_sql.y"
         {
		//$1 = substr($1,1,strlen($1)-2);
  		RelAttr attr1;
		relation_attr_init(&attr1, NULL, (yyvsp[0].string));
		selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr1, 0);

		//value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
#line 2144 "yacc_sql.tab.c"
    break;

  case 87: /* rel_list: COMMA ID rel_list  */
#line 846 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string));
		  }
#line 2152 "yacc_sql.tab.c"
    break;

  case 89: /* inner_join: INNERJOIN ID inner_join_on condition condition_list inner_join  */
#line 853 "yacc_sql.y"
                                                                         {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-4].string));
	}
#line 2160 "yacc_sql.tab.c"
    break;

  case 90: /* inner_join_on: ON  */
#line 858 "yacc_sql.y"
           {
		Condition condition;
		condition_init_with_comp(&condition, NO_OP);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;	
	}
#line 2170 "yacc_sql.tab.c"
    break;

  case 92: /* where: where_key condition condition_list  */
#line 866 "yacc_sql.y"
                                         {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2178 "yacc_sql.tab.c"
    break;

  case 93: /* where_key: WHERE  */
#line 871 "yacc_sql.y"
                     {
			Condition condition;
			condition_init_with_comp(&condition, NO_OP);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		}
#line 2188 "yacc_sql.tab.c"
    break;

  case 95: /* condition_list: and_key condition condition_list  */
#line 880 "yacc_sql.y"
                                       {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2196 "yacc_sql.tab.c"
    break;

  case 96: /* and_key: AND  */
#line 885 "yacc_sql.y"
                    {
			Condition condition;
			condition_init_with_comp(&condition, NO_OP);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		}
#line 2206 "yacc_sql.tab.c"
    break;

  case 97: /* expression: expression PLUS expression  */
#line 893 "yacc_sql.y"
                                  { 
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "+");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
		//$$=$1+$3; 
		}
#line 2218 "yacc_sql.tab.c"
    break;

  case 98: /* expression: expression MINUS expression  */
#line 900 "yacc_sql.y"
                                   { 
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "-");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);

		//$$=$1-$3; 
		}
#line 2231 "yacc_sql.tab.c"
    break;

  case 99: /* expression: expression STAR expression  */
#line 908 "yacc_sql.y"
                                  { 
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "*");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);

		//$$=$1*$3; 
		}
#line 2244 "yacc_sql.tab.c"
    break;

  case 100: /* expression: expression DIVE expression  */
#line 916 "yacc_sql.y"
                                 {
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "/");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
        }
#line 2255 "yacc_sql.tab.c"
    break;

  case 101: /* expression: LBRACE expression RBRACE  */
#line 922 "yacc_sql.y"
                               {
		//$$=$2; 
		}
#line 2263 "yacc_sql.tab.c"
    break;

  case 102: /* expression: value  */
#line 925 "yacc_sql.y"
            { 
		Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
		ExpNode expnode;
		expnode_init(&expnode, 1, value, NULL, NULL);
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
		//$$=$1; 
		}
#line 2276 "yacc_sql.tab.c"
    break;

  case 103: /* expression: ID  */
#line 933 "yacc_sql.y"
             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		ExpNode expnode;
		expnode_init(&expnode,2, NULL, &attr, NULL);
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
	}
#line 2289 "yacc_sql.tab.c"
    break;

  case 104: /* expression: ID DOT ID  */
#line 941 "yacc_sql.y"
                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		ExpNode expnode;
		expnode_init(&expnode,2, NULL, &attr, NULL);
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);

	}
#line 2303 "yacc_sql.tab.c"
    break;

  case 105: /* condition: ID comOp value  */
#line 955 "yacc_sql.y"
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
#line 2325 "yacc_sql.tab.c"
    break;

  case 106: /* condition: value comOp value  */
#line 973 "yacc_sql.y"
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
#line 2346 "yacc_sql.tab.c"
    break;

  case 107: /* condition: ID comOp ID  */
#line 990 "yacc_sql.y"
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
#line 2367 "yacc_sql.tab.c"
    break;

  case 108: /* condition: value comOp ID  */
#line 1007 "yacc_sql.y"
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
#line 2390 "yacc_sql.tab.c"
    break;

  case 109: /* condition: ID DOT ID comOp value  */
#line 1026 "yacc_sql.y"
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
#line 2412 "yacc_sql.tab.c"
    break;

  case 110: /* condition: value comOp ID DOT ID  */
#line 1044 "yacc_sql.y"
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
#line 2435 "yacc_sql.tab.c"
    break;

  case 111: /* condition: ID DOT ID comOp ID DOT ID  */
#line 1063 "yacc_sql.y"
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
#line 2455 "yacc_sql.tab.c"
    break;

  case 112: /* condition: expression comOp expression  */
#line 1078 "yacc_sql.y"
                                      {
		exp_swap_with_other(&CONTEXT->exp_pool[CONTEXT->exp_pool_length], &CONTEXT->exp[0]);
		CONTEXT->exp_pool_length++ ;
		exp_swap_with_other(&CONTEXT->exp_pool[CONTEXT->exp_pool_length], &CONTEXT->exp[1]);

		condition_init_exp(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 1, &CONTEXT->exp_pool[CONTEXT->exp_pool_length-1], 1, &CONTEXT->exp_pool[CONTEXT->exp_pool_length]);
		CONTEXT->exp_pool_length = CONTEXT->exp_pool_length % MAX_NUM;
		// 将临时变量清空
		 exp_destroy(&CONTEXT->exp[0]);
		 exp_destroy(&CONTEXT->exp[1]);
		CONTEXT->exp_length = 0;
	}
#line 2472 "yacc_sql.tab.c"
    break;

  case 113: /* condition: value IS NULL_T  */
#line 1090 "yacc_sql.y"
                          {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, left_value, 0, NULL, &right_value);
	}
#line 2483 "yacc_sql.tab.c"
    break;

  case 114: /* condition: value IS NOTNULL  */
#line 1096 "yacc_sql.y"
                           {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 0, NULL, left_value, 0, NULL, &right_value);
	}
#line 2494 "yacc_sql.tab.c"
    break;

  case 115: /* condition: ID IS NULL_T  */
#line 1102 "yacc_sql.y"
                       {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 1, &left_attr, NULL, 0, NULL, &right_value);
	}
#line 2506 "yacc_sql.tab.c"
    break;

  case 116: /* condition: ID IS NOTNULL  */
#line 1109 "yacc_sql.y"
                        {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 1, &left_attr, NULL, 0, NULL, &right_value);
	}
#line 2518 "yacc_sql.tab.c"
    break;

  case 117: /* condition: ID DOT ID IS NULL_T  */
#line 1116 "yacc_sql.y"
                              {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 1, &left_attr, NULL, 0, NULL, &right_value);

	}
#line 2531 "yacc_sql.tab.c"
    break;

  case 118: /* condition: ID DOT ID IS NOTNULL  */
#line 1124 "yacc_sql.y"
                               {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
		Value right_value;	
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 1, &left_attr, NULL, 0, NULL, &right_value);
	}
#line 2543 "yacc_sql.tab.c"
    break;

  case 119: /* condition: NULL_T IS value  */
#line 1131 "yacc_sql.y"
                         {
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Value left_value;
		value_init_null(&left_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, &left_value, 0, NULL, right_value);
	}
#line 2554 "yacc_sql.tab.c"
    break;

  case 120: /* condition: NULL_T IS ID  */
#line 1138 "yacc_sql.y"
                       {
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));
		Value left_value;
		value_init_null(&left_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, &left_value, 1, &right_attr, NULL);
	}
#line 2566 "yacc_sql.tab.c"
    break;

  case 121: /* condition: NULL_T IS ID DOT ID  */
#line 1146 "yacc_sql.y"
                             {
		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));
		Value left_value;
		value_init_null(&left_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, &left_value, 1, &right_attr, NULL);
	}
#line 2578 "yacc_sql.tab.c"
    break;

  case 122: /* condition: NULL_T IS NOTNULL  */
#line 1154 "yacc_sql.y"
                            {
		Value left_value;
		value_init_null(&left_value, 0);
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 0, NULL, &left_value, 0, NULL, &right_value);
	}
#line 2590 "yacc_sql.tab.c"
    break;

  case 123: /* condition: ID in_or_not_in select  */
#line 1162 "yacc_sql.y"
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
#line 2608 "yacc_sql.tab.c"
    break;

  case 124: /* condition: ID DOT ID in_or_not_in select  */
#line 1176 "yacc_sql.y"
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
#line 2626 "yacc_sql.tab.c"
    break;

  case 125: /* condition: ID comOp select  */
#line 1190 "yacc_sql.y"
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
#line 2645 "yacc_sql.tab.c"
    break;

  case 126: /* condition: ID DOT ID comOp select  */
#line 1205 "yacc_sql.y"
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
#line 2664 "yacc_sql.tab.c"
    break;

  case 127: /* condition: select comOp ID  */
#line 1220 "yacc_sql.y"
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
#line 2701 "yacc_sql.tab.c"
    break;

  case 128: /* condition: select comOp ID DOT ID  */
#line 1253 "yacc_sql.y"
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
#line 2738 "yacc_sql.tab.c"
    break;

  case 129: /* condition: select comOp select  */
#line 1286 "yacc_sql.y"
                             {
		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = CONTEXT->comp_tmp[CONTEXT->select_length];
	}
#line 2746 "yacc_sql.tab.c"
    break;

  case 130: /* in_or_not_in: IN  */
#line 1292 "yacc_sql.y"
           {
		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = OP_IN;
	}
#line 2754 "yacc_sql.tab.c"
    break;

  case 131: /* in_or_not_in: NOTIN  */
#line 1295 "yacc_sql.y"
                {
		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = OP_NO_IN;
	}
#line 2762 "yacc_sql.tab.c"
    break;

  case 132: /* comOp: EQ  */
#line 1301 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; CONTEXT->exp_length++;  CONTEXT->comp_tmp[CONTEXT->select_length] = EQUAL_TO; }
#line 2768 "yacc_sql.tab.c"
    break;

  case 133: /* comOp: LT  */
#line 1302 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; CONTEXT->exp_length++;  CONTEXT->comp_tmp[CONTEXT->select_length] = LESS_THAN; }
#line 2774 "yacc_sql.tab.c"
    break;

  case 134: /* comOp: GT  */
#line 1303 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; CONTEXT->exp_length++;  CONTEXT->comp_tmp[CONTEXT->select_length] = GREAT_THAN; }
#line 2780 "yacc_sql.tab.c"
    break;

  case 135: /* comOp: LE  */
#line 1304 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; CONTEXT->exp_length++;  CONTEXT->comp_tmp[CONTEXT->select_length] = LESS_EQUAL; }
#line 2786 "yacc_sql.tab.c"
    break;

  case 136: /* comOp: GE  */
#line 1305 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; CONTEXT->exp_length++;  CONTEXT->comp_tmp[CONTEXT->select_length] = GREAT_EQUAL; }
#line 2792 "yacc_sql.tab.c"
    break;

  case 137: /* comOp: NE  */
#line 1306 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; CONTEXT->exp_length++; CONTEXT->comp_tmp[CONTEXT->select_length] = NOT_EQUAL; }
#line 2798 "yacc_sql.tab.c"
    break;

  case 139: /* order_by: ORDERBY order_by_attr order_by_list  */
#line 1312 "yacc_sql.y"
                                              {
		
	}
#line 2806 "yacc_sql.tab.c"
    break;

  case 141: /* order_by_list: COMMA order_by_attr order_by_list  */
#line 1318 "yacc_sql.y"
                                            {
			
	}
#line 2814 "yacc_sql.tab.c"
    break;

  case 142: /* order_by_attr: ID order_by_type  */
#line 1324 "yacc_sql.y"
                         {	
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_orderbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
#line 2824 "yacc_sql.tab.c"
    break;

  case 143: /* order_by_attr: ID DOT ID order_by_type  */
#line 1329 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_orderbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
#line 2834 "yacc_sql.tab.c"
    break;

  case 144: /* order_by_type: %empty  */
#line 1336 "yacc_sql.y"
                   {
		CONTEXT->order_by_type = 0;
	}
#line 2842 "yacc_sql.tab.c"
    break;

  case 145: /* order_by_type: ASC  */
#line 1339 "yacc_sql.y"
              {
		CONTEXT->order_by_type = 0;
	}
#line 2850 "yacc_sql.tab.c"
    break;

  case 146: /* order_by_type: DESC  */
#line 1342 "yacc_sql.y"
               {
		CONTEXT->order_by_type = 1;
	}
#line 2858 "yacc_sql.tab.c"
    break;

  case 148: /* group_by: GROUPBY group_by_attr group_by_list  */
#line 1349 "yacc_sql.y"
                                              {

	}
#line 2866 "yacc_sql.tab.c"
    break;

  case 150: /* group_by_list: COMMA group_by_attr group_by_list  */
#line 1355 "yacc_sql.y"
                                            {
			
	}
#line 2874 "yacc_sql.tab.c"
    break;

  case 151: /* group_by_attr: ID order_by_type  */
#line 1361 "yacc_sql.y"
                         {	
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_groupbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
#line 2884 "yacc_sql.tab.c"
    break;

  case 152: /* group_by_attr: ID DOT ID order_by_type  */
#line 1366 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_groupbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
#line 2894 "yacc_sql.tab.c"
    break;

  case 153: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 1376 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2903 "yacc_sql.tab.c"
    break;


#line 2907 "yacc_sql.tab.c"

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

#line 1381 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
