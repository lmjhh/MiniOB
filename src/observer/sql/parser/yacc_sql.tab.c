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
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
  char id[MAX_NUM];
  int order_by_type;
  int nullable;
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
  context->ssql->sstr.insertion.tuple_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 130 "yacc_sql.tab.c"

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
  YYSYMBOL_NUMBER = 57,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 58,                     /* FLOAT  */
  YYSYMBOL_ID = 59,                        /* ID  */
  YYSYMBOL_PATH = 60,                      /* PATH  */
  YYSYMBOL_DATE = 61,                      /* DATE  */
  YYSYMBOL_SSS = 62,                       /* SSS  */
  YYSYMBOL_STAR = 63,                      /* STAR  */
  YYSYMBOL_STRING_V = 64,                  /* STRING_V  */
  YYSYMBOL_POLYKEY = 65,                   /* POLYKEY  */
  YYSYMBOL_YYACCEPT = 66,                  /* $accept  */
  YYSYMBOL_commands = 67,                  /* commands  */
  YYSYMBOL_command = 68,                   /* command  */
  YYSYMBOL_exit = 69,                      /* exit  */
  YYSYMBOL_help = 70,                      /* help  */
  YYSYMBOL_sync = 71,                      /* sync  */
  YYSYMBOL_begin = 72,                     /* begin  */
  YYSYMBOL_commit = 73,                    /* commit  */
  YYSYMBOL_rollback = 74,                  /* rollback  */
  YYSYMBOL_drop_table = 75,                /* drop_table  */
  YYSYMBOL_show_tables = 76,               /* show_tables  */
  YYSYMBOL_desc_table = 77,                /* desc_table  */
  YYSYMBOL_create_index = 78,              /* create_index  */
  YYSYMBOL_id_list = 79,                   /* id_list  */
  YYSYMBOL_drop_index = 80,                /* drop_index  */
  YYSYMBOL_create_table = 81,              /* create_table  */
  YYSYMBOL_attr_def_list = 82,             /* attr_def_list  */
  YYSYMBOL_attr_def = 83,                  /* attr_def  */
  YYSYMBOL_null = 84,                      /* null  */
  YYSYMBOL_number = 85,                    /* number  */
  YYSYMBOL_type = 86,                      /* type  */
  YYSYMBOL_ID_get = 87,                    /* ID_get  */
  YYSYMBOL_insert = 88,                    /* insert  */
  YYSYMBOL_values_list = 89,               /* values_list  */
  YYSYMBOL_value_list = 90,                /* value_list  */
  YYSYMBOL_value = 91,                     /* value  */
  YYSYMBOL_delete = 92,                    /* delete  */
  YYSYMBOL_update = 93,                    /* update  */
  YYSYMBOL_select = 94,                    /* select  */
  YYSYMBOL_select_attr = 95,               /* select_attr  */
  YYSYMBOL_select_poly = 96,               /* select_poly  */
  YYSYMBOL_poly_key = 97,                  /* poly_key  */
  YYSYMBOL_poly_list = 98,                 /* poly_list  */
  YYSYMBOL_poly_value = 99,                /* poly_value  */
  YYSYMBOL_select_attr_poly = 100,         /* select_attr_poly  */
  YYSYMBOL_attr_list = 101,                /* attr_list  */
  YYSYMBOL_attr_list_poly = 102,           /* attr_list_poly  */
  YYSYMBOL_rel_list = 103,                 /* rel_list  */
  YYSYMBOL_inner_join = 104,               /* inner_join  */
  YYSYMBOL_where = 105,                    /* where  */
  YYSYMBOL_condition_list = 106,           /* condition_list  */
  YYSYMBOL_condition = 107,                /* condition  */
  YYSYMBOL_comOp = 108,                    /* comOp  */
  YYSYMBOL_order_by = 109,                 /* order_by  */
  YYSYMBOL_order_by_list = 110,            /* order_by_list  */
  YYSYMBOL_order_by_attr = 111,            /* order_by_attr  */
  YYSYMBOL_order_by_type = 112,            /* order_by_type  */
  YYSYMBOL_load_data = 113                 /* load_data  */
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
#define YYLAST   252

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  262

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   320


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
      65
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   152,   152,   154,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   178,   183,   188,   194,   200,   206,   212,   218,   224,
     231,   237,   244,   246,   252,   259,   268,   270,   274,   285,
     299,   302,   305,   311,   314,   315,   316,   317,   318,   321,
     330,   346,   348,   356,   360,   365,   369,   372,   375,   379,
     385,   395,   405,   422,   442,   447,   452,   457,   465,   476,
     483,   485,   493,   500,   507,   519,   524,   530,   536,   542,
     550,   552,   559,   566,   575,   577,   585,   593,   604,   606,
     611,   613,   618,   620,   624,   626,   631,   652,   672,   692,
     714,   735,   756,   775,   785,   795,   804,   813,   822,   834,
     835,   836,   837,   838,   839,   842,   844,   848,   850,   856,
     861,   868,   871,   874,   881
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
  "UNIQUE", "NULLABLE", "NOTNULL", "IS", "NUMBER", "FLOAT", "ID", "PATH",
  "DATE", "SSS", "STAR", "STRING_V", "POLYKEY", "$accept", "commands",
  "command", "exit", "help", "sync", "begin", "commit", "rollback",
  "drop_table", "show_tables", "desc_table", "create_index", "id_list",
  "drop_index", "create_table", "attr_def_list", "attr_def", "null",
  "number", "type", "ID_get", "insert", "values_list", "value_list",
  "value", "delete", "update", "select", "select_attr", "select_poly",
  "poly_key", "poly_list", "poly_value", "select_attr_poly", "attr_list",
  "attr_list_poly", "rel_list", "inner_join", "where", "condition_list",
  "condition", "comOp", "order_by", "order_by_list", "order_by_attr",
  "order_by_type", "load_data", YY_NULLPTR
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
     315,   316,   317,   318,   319,   320
};
#endif

#define YYPACT_NINF (-200)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -200,    70,  -200,     5,    31,    90,   -33,    24,    33,    15,
      14,    19,    68,    85,   100,   103,   111,    35,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,  -200,    67,    73,   140,    92,
      97,     9,  -200,  -200,   125,   132,   149,   163,   164,  -200,
     109,   110,   135,  -200,  -200,  -200,  -200,  -200,   133,   155,
     138,   114,   172,   173,   118,    36,  -200,   119,   120,    72,
    -200,  -200,   150,   147,   123,   121,   126,   127,   148,  -200,
    -200,    11,   169,   169,   170,   170,  -200,  -200,    12,  -200,
    -200,  -200,   174,   176,    -9,   186,   153,   160,  -200,   177,
     137,   178,   139,    52,  -200,  -200,  -200,   141,   144,   147,
     142,    57,  -200,   179,    66,  -200,  -200,  -200,    96,  -200,
    -200,   -21,   165,  -200,    66,   196,   126,   187,  -200,  -200,
    -200,  -200,  -200,    39,   146,   190,   169,   169,   170,   151,
     147,   200,    58,   189,   189,   143,  -200,   191,   152,  -200,
    -200,  -200,  -200,  -200,  -200,    -1,    43,     2,    51,    -9,
    -200,   147,   154,   177,   209,  -200,  -200,   198,   197,   157,
    -200,  -200,  -200,   181,   168,  -200,    91,  -200,  -200,  -200,
     203,    66,   204,   102,  -200,  -200,  -200,  -200,  -200,  -200,
     193,  -200,   165,   217,   220,  -200,  -200,   167,   166,   210,
     197,    -9,   171,   223,   189,   189,    72,   191,   211,    17,
      60,   175,  -200,  -200,  -200,  -200,   214,   197,   225,   215,
     165,     4,   218,  -200,  -200,  -200,   216,  -200,   219,   234,
    -200,  -200,   212,  -200,  -200,  -200,  -200,  -200,   235,   144,
    -200,   180,  -200,  -200,   171,  -200,   179,    66,  -200,   183,
    -200,  -200,     8,   218,  -200,   191,  -200,  -200,  -200,   226,
     211,  -200
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,    18,     0,     0,     0,     0,
       0,    80,    64,    69,     0,     0,     0,     0,     0,    23,
       0,     0,     0,    24,    25,    26,    22,    21,     0,     0,
       0,     0,     0,     0,     0,     0,    65,     0,     0,     0,
      29,    28,     0,    92,     0,     0,     0,     0,     0,    27,
      34,    80,    80,    80,    88,    88,    72,    73,    84,    74,
      76,    75,     0,     0,     0,     0,     0,     0,    49,    36,
       0,     0,     0,     0,    81,    66,    67,     0,    90,    92,
       0,     0,    77,    70,     0,    59,    56,    57,     0,    55,
      58,     0,    94,    60,     0,     0,     0,     0,    44,    45,
      46,    47,    48,    40,     0,     0,    80,    80,    88,     0,
      92,     0,    84,    84,    84,     0,    68,    53,     0,   109,
     110,   111,   112,   113,   114,     0,     0,     0,     0,     0,
      93,    92,     0,    36,     0,    42,    41,    39,    32,     0,
      82,    83,    89,     0,   115,    63,     0,    85,    78,    79,
       0,     0,     0,     0,   105,   106,    98,    96,   103,   104,
      99,    97,    94,     0,     0,    37,    35,     0,     0,     0,
      32,     0,     0,     0,    84,    84,     0,    53,    51,     0,
       0,     0,    95,    61,   124,    43,     0,    32,     0,     0,
      94,   121,   117,    62,    86,    87,     0,    54,     0,     0,
     107,   108,     0,   100,   101,    38,    33,    30,     0,    90,
     123,     0,   122,   119,     0,   116,    70,     0,    50,     0,
      31,    91,   121,   117,    71,    53,   102,   120,   118,     0,
      51,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,  -200,  -200,  -185,  -200,  -200,    77,   122,  -200,  -200,
    -200,  -200,  -200,   -16,  -199,  -114,  -200,  -200,  -200,  -200,
    -200,   101,     1,  -200,    44,   -76,  -141,   -73,     6,   -93,
    -158,  -150,  -117,  -200,    -4,     7,     0,  -200
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   199,    29,    30,   127,    99,   167,   216,
     133,   100,    31,   229,   182,   121,    32,    33,    34,    44,
      45,    46,   146,    91,    92,    66,   112,   108,   140,    95,
     160,   122,   156,   203,   245,   222,   243,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     147,   177,   178,   179,   158,   104,   105,   106,   227,   192,
     161,    36,   109,    37,   240,   219,   141,   115,   240,   149,
     150,   151,   152,   153,   154,   184,    47,    64,   188,    64,
     110,    48,   236,   241,   212,   157,    49,    39,    65,    40,
     103,   111,   187,   230,   191,    50,    51,   174,   116,   117,
     118,   220,   119,   120,   185,   242,   259,   189,    38,   242,
     170,   171,   239,   224,   225,   172,   210,   207,   193,   115,
       2,    53,   231,    58,     3,     4,   110,   115,    52,     5,
       6,     7,     8,     9,    10,    11,   115,   176,    54,    12,
      13,    14,   115,   165,   166,    82,   233,    15,    16,    83,
     116,   117,   186,    55,   119,   120,    56,    17,   116,   117,
     190,   136,   119,   120,    57,   137,   143,   116,   117,   232,
     144,   119,   120,   116,   117,   148,    59,   119,   120,    86,
      87,    88,    60,   255,    89,    90,   149,   150,   151,   152,
     153,   154,   149,   150,   151,   152,   153,   154,    61,    41,
     204,    62,   155,    42,   205,    43,    63,    67,   209,   128,
     129,   130,   131,   132,    68,    69,    70,    71,    72,    73,
      74,    76,    75,    78,    77,    79,    80,    81,    84,    85,
      94,    93,    96,    97,   102,    98,   101,    64,   107,   123,
     125,   113,   114,   124,   134,   126,   139,   145,   135,   159,
     138,   142,   162,   175,   164,   168,   169,   110,    43,   181,
     173,   183,   196,   194,   197,   198,   200,   201,   202,   206,
     213,   208,   211,   214,   215,   217,   223,   218,   237,   228,
     221,   235,   238,   246,   234,   247,   244,   248,   250,   252,
     195,   249,   256,   260,   261,   251,   180,   254,   163,   258,
     226,   253,   257
};

static const yytype_int16 yycheck[] =
{
     114,   142,   143,   144,   121,    81,    82,    83,   207,   159,
     124,     6,    85,     8,    10,   200,   109,    26,    10,    40,
      41,    42,    43,    44,    45,    26,    59,    18,    26,    18,
      18,     7,   217,    29,   192,    56,     3,     6,    29,     8,
      29,    29,   156,    26,   158,    30,    32,   140,    57,    58,
      59,   201,    61,    62,    55,    51,   255,    55,    53,    51,
     136,   137,   220,   204,   205,   138,   183,   181,   161,    26,
       0,     3,    55,    38,     4,     5,    18,    26,    59,     9,
      10,    11,    12,    13,    14,    15,    26,    29,     3,    19,
      20,    21,    26,    54,    55,    59,   210,    27,    28,    63,
      57,    58,    59,     3,    61,    62,     3,    37,    57,    58,
      59,    59,    61,    62,     3,    63,    59,    57,    58,    59,
      63,    61,    62,    57,    58,    29,    59,    61,    62,    57,
      58,    59,    59,   247,    62,    63,    40,    41,    42,    43,
      44,    45,    40,    41,    42,    43,    44,    45,     8,    59,
      59,    59,    56,    63,    63,    65,    59,    32,    56,    22,
      23,    24,    25,    26,    32,    16,     3,     3,    59,    59,
      35,    16,    39,    59,    36,     3,     3,    59,    59,    59,
      33,    31,    59,    62,    36,    59,    59,    18,    18,     3,
      30,    17,    16,    40,    16,    18,    52,    18,    59,    34,
      59,    59,     6,     3,    17,    59,    16,    18,    65,    18,
      59,    59,     3,    59,    16,    18,    59,    36,    50,    16,
       3,    17,    29,     3,    57,    59,     3,    17,     3,    18,
      59,    17,    17,    17,    59,    16,    18,     3,     3,    59,
     163,    29,    59,    17,   260,   239,   145,   246,   126,   253,
     206,   244,   252
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    67,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    27,    28,    37,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    80,
      81,    88,    92,    93,    94,   113,     6,     8,    53,     6,
       8,    59,    63,    65,    95,    96,    97,    59,     7,     3,
      30,    32,    59,     3,     3,     3,     3,     3,    38,    59,
      59,     8,    59,    59,    18,    29,   101,    32,    32,    16,
       3,     3,    59,    59,    35,    39,    16,    36,    59,     3,
       3,    59,    59,    63,    59,    59,    57,    58,    59,    62,
      63,    99,   100,    31,    33,   105,    59,    62,    59,    83,
      87,    59,    36,    29,   101,   101,   101,    18,   103,   103,
      18,    29,   102,    17,    16,    26,    57,    58,    59,    61,
      62,    91,   107,     3,    40,    30,    18,    82,    22,    23,
      24,    25,    26,    86,    16,    59,    59,    63,    59,    52,
     104,   105,    59,    59,    63,    18,    98,    91,    29,    40,
      41,    42,    43,    44,    45,    56,   108,    56,   108,    34,
     106,    91,     6,    83,    17,    54,    55,    84,    59,    16,
     101,   101,   103,    59,   105,     3,    29,   102,   102,   102,
      97,    18,    90,    59,    26,    55,    59,    91,    26,    55,
      59,    91,   107,   105,    59,    82,     3,    16,    18,    79,
      59,    36,    50,   109,    59,    63,    16,    91,    17,    56,
     108,    29,   106,     3,     3,    57,    85,    59,    17,    79,
     107,    59,   111,     3,   102,   102,   100,    90,    18,    89,
      26,    55,    59,    91,    59,    17,    79,     3,    17,   106,
      10,    29,    51,   112,    18,   110,    17,    16,     3,    29,
       3,   104,    59,   111,    98,    91,    59,   112,   110,    90,
      17,    89
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    66,    67,    67,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    78,    79,    79,    80,    81,    82,    82,    83,    83,
      84,    84,    84,    85,    86,    86,    86,    86,    86,    87,
      88,    89,    89,    90,    90,    91,    91,    91,    91,    91,
      92,    93,    94,    94,    95,    95,    95,    95,    96,    97,
      98,    98,    99,    99,    99,   100,   100,   100,   100,   100,
     101,   101,   101,   101,   102,   102,   102,   102,   103,   103,
     104,   104,   105,   105,   106,   106,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   108,
     108,   108,   108,   108,   108,   109,   109,   110,   110,   111,
     111,   112,   112,   112,   113
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
       5,     8,     9,     7,     1,     2,     4,     4,     5,     1,
       0,     6,     1,     1,     1,     1,     1,     2,     4,     4,
       0,     3,     5,     5,     0,     3,     5,     5,     0,     3,
       0,     6,     0,     3,     0,     3,     3,     3,     3,     3,
       5,     5,     7,     3,     3,     3,     3,     5,     5,     1,
       1,     1,     1,     1,     1,     0,     3,     0,     3,     2,
       4,     0,     1,     1,     8
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
#line 178 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1422 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 183 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1430 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 188 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1438 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 194 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1446 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 200 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1454 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 206 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1462 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 212 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1471 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 218 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1479 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 224 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1488 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 232 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
		}
#line 1498 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 238 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));			
		}
#line 1508 "yacc_sql.tab.c"
    break;

  case 33: /* id_list: COMMA ID id_list  */
#line 246 "yacc_sql.y"
                   {
	create_index_append_attribute(&CONTEXT->ssql->sstr.create_index,(yyvsp[-1].string));
}
#line 1516 "yacc_sql.tab.c"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 253 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1525 "yacc_sql.tab.c"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 260 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1537 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 270 "yacc_sql.y"
                                   {    }
#line 1543 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type null LBRACE number RBRACE  */
#line 275 "yacc_sql.y"
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
#line 1558 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type null  */
#line 286 "yacc_sql.y"
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
#line 1573 "yacc_sql.tab.c"
    break;

  case 40: /* null: %empty  */
#line 299 "yacc_sql.y"
                   {
		CONTEXT->nullable = 0;
	}
#line 1581 "yacc_sql.tab.c"
    break;

  case 41: /* null: NOTNULL  */
#line 302 "yacc_sql.y"
                  {
		CONTEXT->nullable = 0;
	}
#line 1589 "yacc_sql.tab.c"
    break;

  case 42: /* null: NULLABLE  */
#line 305 "yacc_sql.y"
                   {
		CONTEXT->nullable = 1;
	}
#line 1597 "yacc_sql.tab.c"
    break;

  case 43: /* number: NUMBER  */
#line 311 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1603 "yacc_sql.tab.c"
    break;

  case 44: /* type: INT_T  */
#line 314 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1609 "yacc_sql.tab.c"
    break;

  case 45: /* type: DATE_T  */
#line 315 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1615 "yacc_sql.tab.c"
    break;

  case 46: /* type: STRING_T  */
#line 316 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1621 "yacc_sql.tab.c"
    break;

  case 47: /* type: FLOAT_T  */
#line 317 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1627 "yacc_sql.tab.c"
    break;

  case 48: /* type: NULL_T  */
#line 318 "yacc_sql.y"
                    {(yyval.number)=NULLS;}
#line 1633 "yacc_sql.tab.c"
    break;

  case 49: /* ID_get: ID  */
#line 322 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1642 "yacc_sql.tab.c"
    break;

  case 50: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE values_list SEMICOLON  */
#line 331 "yacc_sql.y"
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
#line 1660 "yacc_sql.tab.c"
    break;

  case 52: /* values_list: COMMA LBRACE value value_list RBRACE values_list  */
#line 348 "yacc_sql.y"
                                                  {
	//inserts_append_tuple(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
	//临时变量清零
    //CONTEXT->value_length=0;
}
#line 1670 "yacc_sql.tab.c"
    break;

  case 53: /* value_list: %empty  */
#line 356 "yacc_sql.y"
                {
		inserts_append_tuple(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
#line 1679 "yacc_sql.tab.c"
    break;

  case 54: /* value_list: COMMA value value_list  */
#line 360 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1687 "yacc_sql.tab.c"
    break;

  case 55: /* value: DATE  */
#line 365 "yacc_sql.y"
             {
			(yyvsp[0].date) = substr((yyvsp[0].date),1,strlen((yyvsp[0].date))-2);
  		value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].date));
		}
#line 1696 "yacc_sql.tab.c"
    break;

  case 56: /* value: NUMBER  */
#line 369 "yacc_sql.y"
           {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1704 "yacc_sql.tab.c"
    break;

  case 57: /* value: FLOAT  */
#line 372 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1712 "yacc_sql.tab.c"
    break;

  case 58: /* value: SSS  */
#line 375 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1721 "yacc_sql.tab.c"
    break;

  case 59: /* value: NULL_T  */
#line 379 "yacc_sql.y"
                {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++], 0);
	}
#line 1729 "yacc_sql.tab.c"
    break;

  case 60: /* delete: DELETE FROM ID where SEMICOLON  */
#line 386 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1741 "yacc_sql.tab.c"
    break;

  case 61: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 396 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1753 "yacc_sql.tab.c"
    break;

  case 62: /* select: SELECT select_attr FROM ID rel_list inner_join where order_by SEMICOLON  */
#line 406 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-5].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
			CONTEXT->order_by_type = 0;
	}
#line 1774 "yacc_sql.tab.c"
    break;

  case 63: /* select: SELECT select_poly FROM ID rel_list where SEMICOLON  */
#line 423 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
			CONTEXT->order_by_type = 0;
	}
#line 1795 "yacc_sql.tab.c"
    break;

  case 64: /* select_attr: STAR  */
#line 442 "yacc_sql.y"
         {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1805 "yacc_sql.tab.c"
    break;

  case 65: /* select_attr: ID attr_list  */
#line 447 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1815 "yacc_sql.tab.c"
    break;

  case 66: /* select_attr: ID DOT ID attr_list  */
#line 452 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1825 "yacc_sql.tab.c"
    break;

  case 67: /* select_attr: ID DOT STAR attr_list  */
#line 457 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1835 "yacc_sql.tab.c"
    break;

  case 68: /* select_poly: poly_key LBRACE select_attr_poly RBRACE poly_list  */
#line 465 "yacc_sql.y"
                                                         {
		//Poly poly_tmp;
		//poly_init(&poly_tmp, $1);
		//selects_append_poly(&CONTEXT->ssql->sstr.selection, &poly_tmp);

		// need to add a flag to mark max()
		// selects_set_poly(&CONTEXT->ssql->sstr.selection,1);
		}
#line 1848 "yacc_sql.tab.c"
    break;

  case 69: /* poly_key: POLYKEY  */
#line 476 "yacc_sql.y"
                {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[0].string));
		selects_append_poly(&CONTEXT->ssql->sstr.selection, &poly_tmp);
	}
#line 1858 "yacc_sql.tab.c"
    break;

  case 71: /* poly_list: COMMA poly_key LBRACE select_attr_poly RBRACE poly_list  */
#line 485 "yacc_sql.y"
                                                                  {
		//Poly poly_tmp;
		//poly_init(&poly_tmp, $2);
		//selects_append_poly(&CONTEXT->ssql->sstr.selection, &poly_tmp);
		}
#line 1868 "yacc_sql.tab.c"
    break;

  case 72: /* poly_value: NUMBER  */
#line 493 "yacc_sql.y"
          {	
		RelAttr attr1;
		relation_attr_init_for_number(&attr1, NULL, (yyvsp[0].number));
		selects_append_poly_attribute(&CONTEXT->ssql->sstr.selection, &attr1);

  		//value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
#line 1880 "yacc_sql.tab.c"
    break;

  case 73: /* poly_value: FLOAT  */
#line 500 "yacc_sql.y"
          {
		RelAttr attr1;
		relation_attr_init_for_float(&attr1, NULL, (yyvsp[0].floats));
		selects_append_poly_attribute(&CONTEXT->ssql->sstr.selection, &attr1);

  		//value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
#line 1892 "yacc_sql.tab.c"
    break;

  case 74: /* poly_value: SSS  */
#line 507 "yacc_sql.y"
         {
		//$1 = substr($1,1,strlen($1)-2);
  		RelAttr attr1;
		relation_attr_init(&attr1, NULL, (yyvsp[0].string));
		selects_append_poly_attribute(&CONTEXT->ssql->sstr.selection, &attr1);

		//value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
#line 1905 "yacc_sql.tab.c"
    break;

  case 75: /* select_attr_poly: poly_value  */
#line 519 "yacc_sql.y"
                  {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1915 "yacc_sql.tab.c"
    break;

  case 76: /* select_attr_poly: STAR  */
#line 524 "yacc_sql.y"
               {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			selects_append_poly_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1926 "yacc_sql.tab.c"
    break;

  case 77: /* select_attr_poly: ID attr_list_poly  */
#line 530 "yacc_sql.y"
                        {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			selects_append_poly_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1937 "yacc_sql.tab.c"
    break;

  case 78: /* select_attr_poly: ID DOT ID attr_list_poly  */
#line 536 "yacc_sql.y"
                                   {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			selects_append_poly_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1948 "yacc_sql.tab.c"
    break;

  case 79: /* select_attr_poly: ID DOT STAR attr_list_poly  */
#line 542 "yacc_sql.y"
                                     {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			selects_append_poly_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1959 "yacc_sql.tab.c"
    break;

  case 81: /* attr_list: COMMA ID attr_list  */
#line 552 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 1971 "yacc_sql.tab.c"
    break;

  case 82: /* attr_list: COMMA ID DOT ID attr_list  */
#line 559 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 1983 "yacc_sql.tab.c"
    break;

  case 83: /* attr_list: COMMA ID DOT STAR attr_list  */
#line 566 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 1995 "yacc_sql.tab.c"
    break;

  case 85: /* attr_list_poly: COMMA ID attr_list_poly  */
#line 577 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			selects_append_poly_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2008 "yacc_sql.tab.c"
    break;

  case 86: /* attr_list_poly: COMMA ID DOT ID attr_list_poly  */
#line 585 "yacc_sql.y"
                                     {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			selects_append_poly_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2021 "yacc_sql.tab.c"
    break;

  case 87: /* attr_list_poly: COMMA ID DOT STAR attr_list_poly  */
#line 593 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			selects_append_poly_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2034 "yacc_sql.tab.c"
    break;

  case 89: /* rel_list: COMMA ID rel_list  */
#line 606 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2042 "yacc_sql.tab.c"
    break;

  case 91: /* inner_join: INNERJOIN ID ON condition condition_list inner_join  */
#line 613 "yacc_sql.y"
                                                              {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string));
	}
#line 2050 "yacc_sql.tab.c"
    break;

  case 93: /* where: WHERE condition condition_list  */
#line 620 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2058 "yacc_sql.tab.c"
    break;

  case 95: /* condition_list: AND condition condition_list  */
#line 626 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2066 "yacc_sql.tab.c"
    break;

  case 96: /* condition: ID comOp value  */
#line 632 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
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
#line 2091 "yacc_sql.tab.c"
    break;

  case 97: /* condition: value comOp value  */
#line 653 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
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
#line 2115 "yacc_sql.tab.c"
    break;

  case 98: /* condition: ID comOp ID  */
#line 673 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 2139 "yacc_sql.tab.c"
    break;

  case 99: /* condition: value comOp ID  */
#line 693 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

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
#line 2165 "yacc_sql.tab.c"
    break;

  case 100: /* condition: ID DOT ID comOp value  */
#line 715 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

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
#line 2190 "yacc_sql.tab.c"
    break;

  case 101: /* condition: value comOp ID DOT ID  */
#line 736 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
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
#line 2215 "yacc_sql.tab.c"
    break;

  case 102: /* condition: ID DOT ID comOp ID DOT ID  */
#line 757 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 2238 "yacc_sql.tab.c"
    break;

  case 103: /* condition: value IS NULL_T  */
#line 775 "yacc_sql.y"
                          {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Value right_value;
		value_init_null(&right_value, 0);
		

		Condition condition;
		condition_init(&condition, EQUAL_TO, 0, NULL, left_value, 0, NULL, &right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2253 "yacc_sql.tab.c"
    break;

  case 104: /* condition: value IS NOTNULL  */
#line 785 "yacc_sql.y"
                           {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Value right_value;
		value_init_null(&right_value, 0);
		

		Condition condition;
		condition_init(&condition, NOT_EQUAL, 0, NULL, left_value, 0, NULL, &right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2268 "yacc_sql.tab.c"
    break;

  case 105: /* condition: ID IS NULL_T  */
#line 795 "yacc_sql.y"
                       {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		Value right_value;
		value_init_null(&right_value, 0);
		Condition condition;
		condition_init(&condition, EQUAL_TO, 1, &left_attr, NULL, 0, NULL, &right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2282 "yacc_sql.tab.c"
    break;

  case 106: /* condition: ID IS NOTNULL  */
#line 804 "yacc_sql.y"
                        {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		Value right_value;
		value_init_null(&right_value, 0);
		Condition condition;
		condition_init(&condition, NOT_EQUAL, 1, &left_attr, NULL, 0, NULL, &right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2296 "yacc_sql.tab.c"
    break;

  case 107: /* condition: ID DOT ID IS NULL_T  */
#line 813 "yacc_sql.y"
                              {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
		Value right_value;
		value_init_null(&right_value, 0);
		Condition condition;
		condition_init(&condition, EQUAL_TO, 1, &left_attr, NULL, 0, NULL, &right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2310 "yacc_sql.tab.c"
    break;

  case 108: /* condition: ID DOT ID IS NOTNULL  */
#line 822 "yacc_sql.y"
                               {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
		Value right_value;	
		value_init_null(&right_value, 0);
		Condition condition;
		condition_init(&condition, NOT_EQUAL, 1, &left_attr, NULL, 0, NULL, &right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2324 "yacc_sql.tab.c"
    break;

  case 109: /* comOp: EQ  */
#line 834 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2330 "yacc_sql.tab.c"
    break;

  case 110: /* comOp: LT  */
#line 835 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2336 "yacc_sql.tab.c"
    break;

  case 111: /* comOp: GT  */
#line 836 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2342 "yacc_sql.tab.c"
    break;

  case 112: /* comOp: LE  */
#line 837 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2348 "yacc_sql.tab.c"
    break;

  case 113: /* comOp: GE  */
#line 838 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2354 "yacc_sql.tab.c"
    break;

  case 114: /* comOp: NE  */
#line 839 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2360 "yacc_sql.tab.c"
    break;

  case 116: /* order_by: ORDERBY order_by_attr order_by_list  */
#line 844 "yacc_sql.y"
                                              {

	}
#line 2368 "yacc_sql.tab.c"
    break;

  case 118: /* order_by_list: COMMA order_by_attr order_by_list  */
#line 850 "yacc_sql.y"
                                            {
			
	}
#line 2376 "yacc_sql.tab.c"
    break;

  case 119: /* order_by_attr: ID order_by_type  */
#line 856 "yacc_sql.y"
                         {	
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_orderbyAttr(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->order_by_type);
		}
#line 2386 "yacc_sql.tab.c"
    break;

  case 120: /* order_by_attr: ID DOT ID order_by_type  */
#line 861 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_orderbyAttr(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->order_by_type);
		}
#line 2396 "yacc_sql.tab.c"
    break;

  case 121: /* order_by_type: %empty  */
#line 868 "yacc_sql.y"
                   {
		CONTEXT->order_by_type = 0;
	}
#line 2404 "yacc_sql.tab.c"
    break;

  case 122: /* order_by_type: ASC  */
#line 871 "yacc_sql.y"
              {
		CONTEXT->order_by_type = 0;
	}
#line 2412 "yacc_sql.tab.c"
    break;

  case 123: /* order_by_type: DESC  */
#line 874 "yacc_sql.y"
               {
		CONTEXT->order_by_type = 1;
	}
#line 2420 "yacc_sql.tab.c"
    break;

  case 124: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 882 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2429 "yacc_sql.tab.c"
    break;


#line 2433 "yacc_sql.tab.c"

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

#line 887 "yacc_sql.y"

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
