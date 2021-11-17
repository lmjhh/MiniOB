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
	Selects selects[5];

	int selects_tmp_pool_length;
	Selects selects_tmp_pool[5];
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
  printf(". error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 141 "yacc_sql.tab.c"

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
  YYSYMBOL_NUMBER = 60,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 61,                     /* FLOAT  */
  YYSYMBOL_ID = 62,                        /* ID  */
  YYSYMBOL_PATH = 63,                      /* PATH  */
  YYSYMBOL_DATE = 64,                      /* DATE  */
  YYSYMBOL_SSS = 65,                       /* SSS  */
  YYSYMBOL_STAR = 66,                      /* STAR  */
  YYSYMBOL_STRING_V = 67,                  /* STRING_V  */
  YYSYMBOL_POLYKEY = 68,                   /* POLYKEY  */
  YYSYMBOL_YYACCEPT = 69,                  /* $accept  */
  YYSYMBOL_commands = 70,                  /* commands  */
  YYSYMBOL_command = 71,                   /* command  */
  YYSYMBOL_exit = 72,                      /* exit  */
  YYSYMBOL_help = 73,                      /* help  */
  YYSYMBOL_sync = 74,                      /* sync  */
  YYSYMBOL_begin = 75,                     /* begin  */
  YYSYMBOL_commit = 76,                    /* commit  */
  YYSYMBOL_rollback = 77,                  /* rollback  */
  YYSYMBOL_drop_table = 78,                /* drop_table  */
  YYSYMBOL_show_tables = 79,               /* show_tables  */
  YYSYMBOL_desc_table = 80,                /* desc_table  */
  YYSYMBOL_create_index = 81,              /* create_index  */
  YYSYMBOL_id_list = 82,                   /* id_list  */
  YYSYMBOL_drop_index = 83,                /* drop_index  */
  YYSYMBOL_create_table = 84,              /* create_table  */
  YYSYMBOL_attr_def_list = 85,             /* attr_def_list  */
  YYSYMBOL_attr_def = 86,                  /* attr_def  */
  YYSYMBOL_null = 87,                      /* null  */
  YYSYMBOL_number = 88,                    /* number  */
  YYSYMBOL_type = 89,                      /* type  */
  YYSYMBOL_ID_get = 90,                    /* ID_get  */
  YYSYMBOL_insert = 91,                    /* insert  */
  YYSYMBOL_values_list = 92,               /* values_list  */
  YYSYMBOL_value_list = 93,                /* value_list  */
  YYSYMBOL_value = 94,                     /* value  */
  YYSYMBOL_delete = 95,                    /* delete  */
  YYSYMBOL_update = 96,                    /* update  */
  YYSYMBOL_select = 97,                    /* select  */
  YYSYMBOL_left_brace = 98,                /* left_brace  */
  YYSYMBOL_select_mix = 99,                /* select_mix  */
  YYSYMBOL_mix_list = 100,                 /* mix_list  */
  YYSYMBOL_poly_value = 101,               /* poly_value  */
  YYSYMBOL_rel_list = 102,                 /* rel_list  */
  YYSYMBOL_inner_join = 103,               /* inner_join  */
  YYSYMBOL_inner_join_on = 104,            /* inner_join_on  */
  YYSYMBOL_where = 105,                    /* where  */
  YYSYMBOL_where_key = 106,                /* where_key  */
  YYSYMBOL_condition_list = 107,           /* condition_list  */
  YYSYMBOL_and_key = 108,                  /* and_key  */
  YYSYMBOL_condition = 109,                /* condition  */
  YYSYMBOL_in_or_not_in = 110,             /* in_or_not_in  */
  YYSYMBOL_comOp = 111,                    /* comOp  */
  YYSYMBOL_order_by = 112,                 /* order_by  */
  YYSYMBOL_order_by_list = 113,            /* order_by_list  */
  YYSYMBOL_order_by_attr = 114,            /* order_by_attr  */
  YYSYMBOL_order_by_type = 115,            /* order_by_type  */
  YYSYMBOL_group_by = 116,                 /* group_by  */
  YYSYMBOL_group_by_list = 117,            /* group_by_list  */
  YYSYMBOL_group_by_attr = 118,            /* group_by_attr  */
  YYSYMBOL_load_data = 119                 /* load_data  */
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
#define YYLAST   322

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  144
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  311

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   323


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
      65,    66,    67,    68
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   166,   166,   168,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   192,   197,   202,   208,   214,   220,   226,   232,   238,
     245,   251,   258,   260,   266,   273,   282,   284,   288,   299,
     313,   316,   319,   325,   328,   329,   330,   331,   332,   335,
     344,   360,   362,   370,   374,   379,   383,   386,   389,   393,
     399,   409,   420,   437,   472,   481,   486,   492,   497,   502,
     511,   521,   529,   537,   548,   550,   556,   561,   566,   574,
     584,   592,   600,   746,   753,   760,   833,   835,   840,   842,
     847,   853,   855,   860,   867,   869,   874,   881,   899,   916,
     933,   952,   970,   989,  1005,  1011,  1017,  1024,  1031,  1039,
    1046,  1053,  1061,  1069,  1077,  1091,  1105,  1120,  1135,  1168,
    1201,  1207,  1210,  1216,  1217,  1218,  1219,  1220,  1221,  1225,
    1227,  1231,  1233,  1239,  1244,  1251,  1254,  1257,  1262,  1264,
    1268,  1270,  1276,  1281,  1290
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
  "UNIQUE", "NULLABLE", "NOTNULL", "IS", "GROUPBY", "IN", "NOTIN",
  "NUMBER", "FLOAT", "ID", "PATH", "DATE", "SSS", "STAR", "STRING_V",
  "POLYKEY", "$accept", "commands", "command", "exit", "help", "sync",
  "begin", "commit", "rollback", "drop_table", "show_tables", "desc_table",
  "create_index", "id_list", "drop_index", "create_table", "attr_def_list",
  "attr_def", "null", "number", "type", "ID_get", "insert", "values_list",
  "value_list", "value", "delete", "update", "select", "left_brace",
  "select_mix", "mix_list", "poly_value", "rel_list", "inner_join",
  "inner_join_on", "where", "where_key", "condition_list", "and_key",
  "condition", "in_or_not_in", "comOp", "order_by", "order_by_list",
  "order_by_attr", "order_by_type", "group_by", "group_by_list",
  "group_by_attr", "load_data", YY_NULLPTR
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
     315,   316,   317,   318,   319,   320,   321,   322,   323
};
#endif

#define YYPACT_NINF (-263)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -263,   130,  -263,     8,    33,    55,   -39,    19,    52,    40,
      68,    35,  -263,   111,   122,   123,   133,   135,   109,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,   144,  -263,    92,    93,
     160,   108,   114,    86,  -263,   155,   159,   189,   190,  -263,
     132,   137,   170,  -263,  -263,  -263,  -263,  -263,   167,    55,
     196,   177,   166,   226,   227,    -3,    71,  -263,   142,   171,
    -263,  -263,   201,   202,   172,   174,   204,   178,   179,   206,
    -263,  -263,    89,   228,   225,   225,  -263,  -263,    16,  -263,
     229,   230,   231,   232,  -263,   242,    12,   210,   221,   191,
    -263,   234,   200,   238,   193,    90,  -263,   149,  -263,  -263,
     225,   134,   225,   225,   194,   205,    41,  -263,   203,  -263,
    -263,   119,  -263,  -263,   145,   176,   224,    41,   254,   231,
     178,   244,  -263,  -263,  -263,  -263,  -263,    65,   207,   246,
     225,   225,    61,   247,   248,  -263,   249,   250,  -263,  -263,
     231,   208,   202,  -263,   245,    67,   209,  -263,  -263,  -263,
    -263,  -263,  -263,    -7,  -263,  -263,   100,    21,    -6,    34,
       2,  -263,  -263,    12,   202,   211,   205,   234,   265,  -263,
    -263,   256,   257,   212,  -263,  -263,   225,   165,   225,   225,
     225,   225,  -263,   240,   220,    41,   261,  -263,   251,  -263,
     139,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,   252,
    -263,   253,  -263,   224,   276,   280,   202,  -263,  -263,   233,
     222,   268,   257,  -263,   269,   270,  -263,  -263,  -263,  -263,
    -263,    12,   235,   239,   245,   272,   236,    20,   100,    27,
     237,   241,  -263,  -263,  -263,   220,  -263,   271,   257,   288,
     275,   225,   225,   224,     0,   277,   243,   291,  -263,   284,
     293,  -263,  -263,  -263,  -263,   273,  -263,  -263,  -263,  -263,
     239,  -263,  -263,  -263,   298,  -263,  -263,   205,  -263,   255,
    -263,  -263,   235,  -263,    15,   286,  -263,    41,  -263,   258,
     289,  -263,  -263,     5,   277,   259,  -263,   243,  -263,   245,
    -263,  -263,  -263,  -263,     5,   286,   290,  -263,  -263,   272,
    -263
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
      74,     0,    74,    74,     0,    88,     0,    60,    59,    56,
      57,     0,    55,    58,     0,     0,    94,     0,     0,    86,
       0,     0,    44,    45,    46,    47,    48,    40,     0,     0,
      74,    74,     0,     0,     0,    71,     0,     0,    70,    69,
      86,     0,    91,    59,    53,     0,     0,   123,   124,   125,
     126,   127,   128,     0,   121,   122,     0,     0,     0,     0,
       0,    96,    92,     0,    91,     0,    88,    36,     0,    42,
      41,    39,    32,     0,    76,    77,    74,     0,    74,    74,
      74,    74,    87,     0,   138,     0,     0,   113,   111,   110,
       0,   106,   107,   114,    99,    97,   116,   104,   105,   100,
      98,   118,   120,    94,     0,     0,    91,    37,    35,     0,
       0,     0,    32,    80,     0,     0,    79,    78,    72,    73,
      90,     0,     0,   129,    53,    51,     0,     0,     0,     0,
       0,     0,    95,    61,   144,   138,    43,     0,    32,     0,
       0,    74,    74,    94,   135,   140,     0,     0,    54,     0,
       0,   112,   108,   109,   115,     0,   101,   117,   102,   119,
     129,    38,    33,    30,     0,    81,    82,    88,   137,     0,
     136,   142,     0,   139,   135,   131,    62,     0,    50,     0,
       0,    31,    89,   135,   140,     0,   133,     0,   130,    53,
     103,    63,   143,   141,   135,   131,     0,   134,   132,    51,
      52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,  -198,  -263,  -263,   131,   180,  -263,  -263,
    -263,  -263,  -263,     3,  -231,  -115,  -263,  -263,    -1,  -263,
     260,   -78,   215,   -71,  -174,  -263,  -147,  -263,  -196,  -263,
    -160,   113,  -116,    39,     6,    17,  -262,    70,    22,    36,
    -263
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,   221,    30,    31,   131,   101,   181,   247,
     137,   102,    32,   260,   196,   124,    33,    34,   125,    36,
      46,    67,    91,   115,   152,   231,    95,    96,   172,   173,
     126,   166,   167,   257,   298,   285,   281,   233,   283,   255,
      37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      35,   154,   216,   258,   106,   194,   108,   109,   169,   170,
     278,     5,   174,   213,    38,   278,    39,   242,    12,   201,
     207,     5,   296,    47,   250,   278,    48,   214,    12,   279,
       5,   302,   145,   110,   148,   149,     5,    12,   118,    41,
     199,    42,   307,    12,   295,   111,   262,   153,   202,   208,
     272,   280,   205,   153,   210,    49,   280,   277,   176,    82,
     153,    40,   184,   185,   211,    83,   280,   153,   306,   245,
      50,   253,   119,   120,   121,   263,   122,   123,   186,   192,
     234,   119,   120,   204,   239,   122,   123,   119,   120,   265,
     187,   122,   123,   153,   119,   120,   209,    52,   122,   123,
      51,   119,   120,   292,    65,   122,   123,    65,   223,     5,
     226,   227,   228,   229,    53,    66,    12,    43,   105,   179,
     180,    44,   197,    45,   266,    54,    55,   119,   120,   198,
       2,   122,   123,    84,     3,     4,    56,    85,    57,     5,
       6,     7,     8,     9,    10,    11,    12,    58,   156,    13,
      14,    15,   140,    59,    60,    61,   141,    16,    17,   157,
     158,   159,   160,   161,   162,   203,   206,    18,    62,   212,
      63,    68,   299,   275,   276,   163,    64,   164,   165,   157,
     158,   159,   160,   161,   162,   157,   158,   159,   160,   161,
     162,    69,    70,    71,    72,   237,   146,   164,   165,    73,
     147,   168,    86,    87,    88,    74,    75,    89,    90,    86,
      87,   142,    77,    78,    89,   143,   157,   158,   159,   160,
     161,   162,   132,   133,   134,   135,   136,   224,    79,    80,
      81,   225,    93,    92,    97,    94,    99,   264,   267,    98,
     100,   103,   104,    65,   107,   117,   112,   113,   116,   114,
     127,   128,   130,   129,   138,   139,   150,   151,   171,   155,
     175,   178,   183,   195,   188,   189,   190,   191,   218,   182,
     193,   200,   219,   215,   222,   220,   230,   232,   235,   243,
     236,   240,   241,   244,   248,   249,   251,   252,   271,   256,
     259,   273,   274,   246,   286,   282,   288,   254,   261,   268,
     287,   291,   289,   269,   297,   284,   301,   309,   217,   290,
     177,   308,   310,   238,   305,   270,   303,   293,   294,    76,
     300,   304,   144
};

static const yytype_int16 yycheck[] =
{
       1,   116,   176,   234,    82,   152,    84,    85,   124,   125,
      10,     9,   127,   173,     6,    10,     8,   213,    16,    26,
      26,     9,   284,    62,   222,    10,     7,   174,    16,    29,
       9,   293,   110,    17,   112,   113,     9,    16,    26,     6,
     155,     8,   304,    16,    29,    29,    26,    26,    55,    55,
     248,    51,   167,    26,   169,     3,    51,   253,   129,    62,
      26,    53,   140,   141,    62,    68,    51,    26,   299,   216,
      30,   231,    60,    61,    62,    55,    64,    65,    17,   150,
     195,    60,    61,    62,   200,    64,    65,    60,    61,    62,
      29,    64,    65,    26,    60,    61,    62,    62,    64,    65,
      32,    60,    61,   277,    18,    64,    65,    18,   186,     9,
     188,   189,   190,   191,     3,    29,    16,    62,    29,    54,
      55,    66,    55,    68,   239,     3,     3,    60,    61,    62,
       0,    64,    65,    62,     4,     5,     3,    66,     3,     9,
      10,    11,    12,    13,    14,    15,    16,    38,    29,    19,
      20,    21,    62,     9,    62,    62,    66,    27,    28,    40,
      41,    42,    43,    44,    45,   166,   167,    37,     8,   170,
      62,    16,   287,   251,   252,    56,    62,    58,    59,    40,
      41,    42,    43,    44,    45,    40,    41,    42,    43,    44,
      45,    32,     3,     3,    62,    56,    62,    58,    59,    62,
      66,    56,    60,    61,    62,    35,    39,    65,    66,    60,
      61,    62,    16,    36,    65,    66,    40,    41,    42,    43,
      44,    45,    22,    23,    24,    25,    26,    62,    62,     3,
       3,    66,    31,    62,    62,    33,    32,   238,   239,    65,
      62,    62,    36,    18,    16,     3,    17,    17,    16,    18,
      40,    30,    18,    62,    16,    62,    62,    52,    34,    56,
       6,    17,    16,    18,    17,    17,    17,    17,     3,    62,
      62,    62,    16,    62,    62,    18,    36,    57,    17,     3,
      29,    29,    29,     3,    62,    17,    17,    17,    17,    50,
      18,     3,    17,    60,     3,    18,     3,    62,    62,    62,
      16,     3,    29,    62,    18,    62,    17,    17,   177,   270,
     130,   305,   309,   200,   297,   245,   294,    62,   282,    59,
      62,    62,   107
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    70,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    16,    19,    20,    21,    27,    28,    37,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      83,    84,    91,    95,    96,    97,    98,   119,     6,     8,
      53,     6,     8,    62,    66,    68,    99,    62,     7,     3,
      30,    32,    62,     3,     3,     3,     3,     3,    38,     9,
      62,    62,     8,    62,    62,    18,    29,   100,    16,    32,
       3,     3,    62,    62,    35,    39,    99,    16,    36,    62,
       3,     3,    62,    68,    62,    66,    60,    61,    62,    65,
      66,   101,    62,    31,    33,   105,   106,    62,    65,    32,
      62,    86,    90,    62,    36,    29,   100,    16,   100,   100,
      17,    29,    17,    17,    18,   102,    16,     3,    26,    60,
      61,    62,    64,    65,    94,    97,   109,    40,    30,    62,
      18,    85,    22,    23,    24,    25,    26,    89,    16,    62,
      62,    66,    62,    66,   101,   100,    62,    66,   100,   100,
      62,    52,   103,    26,    94,    56,    29,    40,    41,    42,
      43,    44,    45,    56,    58,    59,   110,   111,    56,   111,
     111,    34,   107,   108,    94,     6,   102,    86,    17,    54,
      55,    87,    62,    16,   100,   100,    17,    29,    17,    17,
      17,    17,   102,    62,   105,    18,    93,    55,    62,    94,
      62,    26,    55,    97,    62,    94,    97,    26,    55,    62,
      94,    62,    97,   109,   105,    62,   103,    85,     3,    16,
      18,    82,    62,   100,    62,    66,   100,   100,   100,   100,
      36,   104,    57,   116,    94,    17,    29,    56,   110,   111,
      29,    29,   107,     3,     3,   105,    60,    88,    62,    17,
      82,    17,    17,   109,    62,   118,    50,   112,    93,    18,
      92,    62,    26,    55,    97,    62,    94,    97,    62,    62,
     116,    17,    82,     3,    17,   100,   100,   107,    10,    29,
      51,   115,    18,   117,    62,   114,     3,    16,     3,    29,
     112,     3,   103,    62,   118,    29,   115,    18,   113,    94,
      62,    17,   115,   117,    62,   114,    93,   115,   113,    17,
      92
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    69,    70,    70,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    81,    82,    82,    83,    84,    85,    85,    86,    86,
      87,    87,    87,    88,    89,    89,    89,    89,    89,    90,
      91,    92,    92,    93,    93,    94,    94,    94,    94,    94,
      95,    96,    97,    97,    98,    99,    99,    99,    99,    99,
      99,    99,    99,    99,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   101,   101,   101,   102,   102,   103,   103,
     104,   105,   105,   106,   107,   107,   108,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   110,   110,   111,   111,   111,   111,   111,   111,   112,
     112,   113,   113,   114,   114,   115,   115,   115,   116,   116,
     117,   117,   118,   118,   119
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
       3,     5,     5,     7,     3,     3,     3,     3,     5,     5,
       3,     3,     5,     3,     3,     5,     3,     5,     3,     5,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       3,     0,     3,     2,     4,     0,     1,     1,     0,     3,
       0,     3,     2,     4,     8
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
#line 192 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1477 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 197 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1485 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 202 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1493 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 208 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1501 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 214 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1509 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 220 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1517 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 226 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1526 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 232 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1534 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 238 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1543 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 246 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
		}
#line 1553 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 252 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));			
		}
#line 1563 "yacc_sql.tab.c"
    break;

  case 33: /* id_list: COMMA ID id_list  */
#line 260 "yacc_sql.y"
                   {
	create_index_append_attribute(&CONTEXT->ssql->sstr.create_index,(yyvsp[-1].string));
}
#line 1571 "yacc_sql.tab.c"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 267 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1580 "yacc_sql.tab.c"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 274 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1592 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 284 "yacc_sql.y"
                                   {    }
#line 1598 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type null LBRACE number RBRACE  */
#line 289 "yacc_sql.y"
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
#line 1613 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type null  */
#line 300 "yacc_sql.y"
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
#line 1628 "yacc_sql.tab.c"
    break;

  case 40: /* null: %empty  */
#line 313 "yacc_sql.y"
                   {
		CONTEXT->nullable = 0;
	}
#line 1636 "yacc_sql.tab.c"
    break;

  case 41: /* null: NOTNULL  */
#line 316 "yacc_sql.y"
                  {
		CONTEXT->nullable = 0;
	}
#line 1644 "yacc_sql.tab.c"
    break;

  case 42: /* null: NULLABLE  */
#line 319 "yacc_sql.y"
                   {
		CONTEXT->nullable = 1;
	}
#line 1652 "yacc_sql.tab.c"
    break;

  case 43: /* number: NUMBER  */
#line 325 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1658 "yacc_sql.tab.c"
    break;

  case 44: /* type: INT_T  */
#line 328 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1664 "yacc_sql.tab.c"
    break;

  case 45: /* type: DATE_T  */
#line 329 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1670 "yacc_sql.tab.c"
    break;

  case 46: /* type: STRING_T  */
#line 330 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1676 "yacc_sql.tab.c"
    break;

  case 47: /* type: FLOAT_T  */
#line 331 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1682 "yacc_sql.tab.c"
    break;

  case 48: /* type: NULL_T  */
#line 332 "yacc_sql.y"
                    {(yyval.number)=NULLS;}
#line 1688 "yacc_sql.tab.c"
    break;

  case 49: /* ID_get: ID  */
#line 336 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1697 "yacc_sql.tab.c"
    break;

  case 50: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE values_list SEMICOLON  */
#line 345 "yacc_sql.y"
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
#line 1715 "yacc_sql.tab.c"
    break;

  case 52: /* values_list: COMMA LBRACE value value_list RBRACE values_list  */
#line 362 "yacc_sql.y"
                                                  {
	//inserts_append_tuple(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
	//临时变量清零
    //CONTEXT->value_length=0;
}
#line 1725 "yacc_sql.tab.c"
    break;

  case 53: /* value_list: %empty  */
#line 370 "yacc_sql.y"
                {
		inserts_append_tuple(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
#line 1734 "yacc_sql.tab.c"
    break;

  case 54: /* value_list: COMMA value value_list  */
#line 374 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1742 "yacc_sql.tab.c"
    break;

  case 55: /* value: DATE  */
#line 379 "yacc_sql.y"
             {
			(yyvsp[0].date) = substr((yyvsp[0].date),1,strlen((yyvsp[0].date))-2);
  		value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].date));
		}
#line 1751 "yacc_sql.tab.c"
    break;

  case 56: /* value: NUMBER  */
#line 383 "yacc_sql.y"
           {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1759 "yacc_sql.tab.c"
    break;

  case 57: /* value: FLOAT  */
#line 386 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1767 "yacc_sql.tab.c"
    break;

  case 58: /* value: SSS  */
#line 389 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1776 "yacc_sql.tab.c"
    break;

  case 59: /* value: NULL_T  */
#line 393 "yacc_sql.y"
                {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++], 0);
	}
#line 1784 "yacc_sql.tab.c"
    break;

  case 60: /* delete: DELETE FROM ID where SEMICOLON  */
#line 400 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1796 "yacc_sql.tab.c"
    break;

  case 61: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 410 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1808 "yacc_sql.tab.c"
    break;

  case 62: /* select: SELECT select_mix FROM ID rel_list inner_join where group_by order_by SEMICOLON  */
#line 421 "yacc_sql.y"
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
#line 1828 "yacc_sql.tab.c"
    break;

  case 63: /* select: left_brace SELECT select_mix FROM ID rel_list inner_join where group_by order_by RBRACE  */
#line 438 "yacc_sql.y"
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


				// selects_copy_with_other(&CONTEXT->selects_tmp_pool[CONTEXT->selects_tmp_pool_length], &CONTEXT->selects[CONTEXT->select_length + 1]);
				CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].right_sub_select = &CONTEXT->selects_tmp_pool[CONTEXT->selects_tmp_pool_length];
				CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].right_sub_select = &CONTEXT->selects[CONTEXT->select_length + 1];
				CONTEXT->selects_tmp_pool_length++;
			}else{
				CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].is_left_sub = 1;
				CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].is_right_sub = 1;

				CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].left_sub_select = CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].right_sub_select;	

				selects_copy_with_other(&CONTEXT->selects_tmp_pool[CONTEXT->selects_tmp_pool_length], &CONTEXT->selects[CONTEXT->select_length + 1]);
				CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].right_sub_select = &CONTEXT->selects_tmp_pool[CONTEXT->selects_tmp_pool_length];			
				CONTEXT->selects_tmp_pool_length++;
			}

			CONTEXT->selects_tmp_pool_length = CONTEXT->selects_tmp_pool_length % (5);
	}
#line 1864 "yacc_sql.tab.c"
    break;

  case 64: /* left_brace: LBRACE  */
#line 472 "yacc_sql.y"
               {
		CONTEXT->condition_length_tmp[CONTEXT->select_length] = CONTEXT->condition_length;
		CONTEXT->value_length_tmp[CONTEXT->select_length] = CONTEXT->value_length;
		CONTEXT->from_length_tmp[CONTEXT->select_length] = CONTEXT->from_length;
		CONTEXT->select_length++;
	}
#line 1875 "yacc_sql.tab.c"
    break;

  case 65: /* select_mix: STAR  */
#line 481 "yacc_sql.y"
             {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 1885 "yacc_sql.tab.c"
    break;

  case 66: /* select_mix: ID mix_list  */
#line 486 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);

		}
#line 1896 "yacc_sql.tab.c"
    break;

  case 67: /* select_mix: ID DOT ID mix_list  */
#line 492 "yacc_sql.y"
                             {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 1906 "yacc_sql.tab.c"
    break;

  case 68: /* select_mix: ID DOT STAR mix_list  */
#line 497 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 1916 "yacc_sql.tab.c"
    break;

  case 69: /* select_mix: POLYKEY LBRACE poly_value RBRACE mix_list  */
#line 502 "yacc_sql.y"
                                                   {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
		//select_append_poly_lsn(&CONTEXT->selects[CONTEXT->select_length]);
		
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		}
#line 1930 "yacc_sql.tab.c"
    break;

  case 70: /* select_mix: POLYKEY LBRACE STAR RBRACE mix_list  */
#line 511 "yacc_sql.y"
                                             {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
#line 1945 "yacc_sql.tab.c"
    break;

  case 71: /* select_mix: POLYKEY LBRACE ID RBRACE mix_list  */
#line 521 "yacc_sql.y"
                                           {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
		}
#line 1958 "yacc_sql.tab.c"
    break;

  case 72: /* select_mix: POLYKEY LBRACE ID DOT ID RBRACE mix_list  */
#line 529 "yacc_sql.y"
                                                  {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-6].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
	}
#line 1971 "yacc_sql.tab.c"
    break;

  case 73: /* select_mix: POLYKEY LBRACE ID DOT STAR RBRACE mix_list  */
#line 537 "yacc_sql.y"
                                                    {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-6].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
	}
#line 1984 "yacc_sql.tab.c"
    break;

  case 75: /* mix_list: COMMA ID mix_list  */
#line 550 "yacc_sql.y"
                             {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);

		}
#line 1995 "yacc_sql.tab.c"
    break;

  case 76: /* mix_list: COMMA ID DOT ID mix_list  */
#line 556 "yacc_sql.y"
                                   {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 2005 "yacc_sql.tab.c"
    break;

  case 77: /* mix_list: COMMA ID DOT STAR mix_list  */
#line 561 "yacc_sql.y"
                                     {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 2015 "yacc_sql.tab.c"
    break;

  case 78: /* mix_list: COMMA POLYKEY LBRACE poly_value RBRACE mix_list  */
#line 566 "yacc_sql.y"
                                                         {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
		
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		}
#line 2028 "yacc_sql.tab.c"
    break;

  case 79: /* mix_list: COMMA POLYKEY LBRACE STAR RBRACE mix_list  */
#line 574 "yacc_sql.y"
                                                   {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
#line 2043 "yacc_sql.tab.c"
    break;

  case 80: /* mix_list: COMMA POLYKEY LBRACE ID RBRACE mix_list  */
#line 584 "yacc_sql.y"
                                                 {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
		}
#line 2056 "yacc_sql.tab.c"
    break;

  case 81: /* mix_list: COMMA POLYKEY LBRACE ID DOT ID RBRACE mix_list  */
#line 592 "yacc_sql.y"
                                                        {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-6].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
	}
#line 2069 "yacc_sql.tab.c"
    break;

  case 82: /* mix_list: COMMA POLYKEY LBRACE ID DOT STAR RBRACE mix_list  */
#line 600 "yacc_sql.y"
                                                          {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-6].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
#line 2083 "yacc_sql.tab.c"
    break;

  case 83: /* poly_value: NUMBER  */
#line 746 "yacc_sql.y"
          {	
		RelAttr attr1;
		relation_attr_init_for_number(&attr1, NULL, (yyvsp[0].number));
		selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr1, 0);

  		//value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
#line 2095 "yacc_sql.tab.c"
    break;

  case 84: /* poly_value: FLOAT  */
#line 753 "yacc_sql.y"
          {
		RelAttr attr1;
		relation_attr_init_for_float(&attr1, NULL, (yyvsp[0].floats));
		selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr1, 0);

  		//value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
#line 2107 "yacc_sql.tab.c"
    break;

  case 85: /* poly_value: SSS  */
#line 760 "yacc_sql.y"
         {
		//$1 = substr($1,1,strlen($1)-2);
  		RelAttr attr1;
		relation_attr_init(&attr1, NULL, (yyvsp[0].string));
		selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr1, 0);

		//value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
#line 2120 "yacc_sql.tab.c"
    break;

  case 87: /* rel_list: COMMA ID rel_list  */
#line 835 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string));
		  }
#line 2128 "yacc_sql.tab.c"
    break;

  case 89: /* inner_join: INNERJOIN ID inner_join_on condition condition_list inner_join  */
#line 842 "yacc_sql.y"
                                                                         {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-4].string));
	}
#line 2136 "yacc_sql.tab.c"
    break;

  case 90: /* inner_join_on: ON  */
#line 847 "yacc_sql.y"
           {
		Condition condition;
		condition_init_with_comp(&condition, NO_OP);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;	
	}
#line 2146 "yacc_sql.tab.c"
    break;

  case 92: /* where: where_key condition condition_list  */
#line 855 "yacc_sql.y"
                                         {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2154 "yacc_sql.tab.c"
    break;

  case 93: /* where_key: WHERE  */
#line 860 "yacc_sql.y"
                     {
			Condition condition;
			condition_init_with_comp(&condition, NO_OP);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		}
#line 2164 "yacc_sql.tab.c"
    break;

  case 95: /* condition_list: and_key condition condition_list  */
#line 869 "yacc_sql.y"
                                       {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2172 "yacc_sql.tab.c"
    break;

  case 96: /* and_key: AND  */
#line 874 "yacc_sql.y"
                    {
			Condition condition;
			condition_init_with_comp(&condition, NO_OP);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		}
#line 2182 "yacc_sql.tab.c"
    break;

  case 97: /* condition: ID comOp value  */
#line 882 "yacc_sql.y"
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
#line 2204 "yacc_sql.tab.c"
    break;

  case 98: /* condition: value comOp value  */
#line 900 "yacc_sql.y"
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
#line 2225 "yacc_sql.tab.c"
    break;

  case 99: /* condition: ID comOp ID  */
#line 917 "yacc_sql.y"
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
#line 2246 "yacc_sql.tab.c"
    break;

  case 100: /* condition: value comOp ID  */
#line 934 "yacc_sql.y"
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
#line 2269 "yacc_sql.tab.c"
    break;

  case 101: /* condition: ID DOT ID comOp value  */
#line 953 "yacc_sql.y"
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
#line 2291 "yacc_sql.tab.c"
    break;

  case 102: /* condition: value comOp ID DOT ID  */
#line 971 "yacc_sql.y"
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
#line 2314 "yacc_sql.tab.c"
    break;

  case 103: /* condition: ID DOT ID comOp ID DOT ID  */
#line 990 "yacc_sql.y"
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
#line 2334 "yacc_sql.tab.c"
    break;

  case 104: /* condition: value IS NULL_T  */
#line 1005 "yacc_sql.y"
                          {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, left_value, 0, NULL, &right_value);
	}
#line 2345 "yacc_sql.tab.c"
    break;

  case 105: /* condition: value IS NOTNULL  */
#line 1011 "yacc_sql.y"
                           {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 0, NULL, left_value, 0, NULL, &right_value);
	}
#line 2356 "yacc_sql.tab.c"
    break;

  case 106: /* condition: ID IS NULL_T  */
#line 1017 "yacc_sql.y"
                       {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 1, &left_attr, NULL, 0, NULL, &right_value);
	}
#line 2368 "yacc_sql.tab.c"
    break;

  case 107: /* condition: ID IS NOTNULL  */
#line 1024 "yacc_sql.y"
                        {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 1, &left_attr, NULL, 0, NULL, &right_value);
	}
#line 2380 "yacc_sql.tab.c"
    break;

  case 108: /* condition: ID DOT ID IS NULL_T  */
#line 1031 "yacc_sql.y"
                              {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 1, &left_attr, NULL, 0, NULL, &right_value);

	}
#line 2393 "yacc_sql.tab.c"
    break;

  case 109: /* condition: ID DOT ID IS NOTNULL  */
#line 1039 "yacc_sql.y"
                               {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
		Value right_value;	
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 1, &left_attr, NULL, 0, NULL, &right_value);
	}
#line 2405 "yacc_sql.tab.c"
    break;

  case 110: /* condition: NULL_T IS value  */
#line 1046 "yacc_sql.y"
                         {
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Value left_value;
		value_init_null(&left_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, &left_value, 0, NULL, right_value);
	}
#line 2416 "yacc_sql.tab.c"
    break;

  case 111: /* condition: NULL_T IS ID  */
#line 1053 "yacc_sql.y"
                       {
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));
		Value left_value;
		value_init_null(&left_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, &left_value, 1, &right_attr, NULL);
	}
#line 2428 "yacc_sql.tab.c"
    break;

  case 112: /* condition: NULL_T IS ID DOT ID  */
#line 1061 "yacc_sql.y"
                             {
		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));
		Value left_value;
		value_init_null(&left_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, &left_value, 1, &right_attr, NULL);
	}
#line 2440 "yacc_sql.tab.c"
    break;

  case 113: /* condition: NULL_T IS NOTNULL  */
#line 1069 "yacc_sql.y"
                            {
		Value left_value;
		value_init_null(&left_value, 0);
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 0, NULL, &left_value, 0, NULL, &right_value);
	}
#line 2452 "yacc_sql.tab.c"
    break;

  case 114: /* condition: ID in_or_not_in select  */
#line 1077 "yacc_sql.y"
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
#line 2470 "yacc_sql.tab.c"
    break;

  case 115: /* condition: ID DOT ID in_or_not_in select  */
#line 1091 "yacc_sql.y"
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
#line 2488 "yacc_sql.tab.c"
    break;

  case 116: /* condition: ID comOp select  */
#line 1105 "yacc_sql.y"
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
#line 2507 "yacc_sql.tab.c"
    break;

  case 117: /* condition: ID DOT ID comOp select  */
#line 1120 "yacc_sql.y"
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
#line 2526 "yacc_sql.tab.c"
    break;

  case 118: /* condition: select comOp ID  */
#line 1135 "yacc_sql.y"
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
#line 2563 "yacc_sql.tab.c"
    break;

  case 119: /* condition: select comOp ID DOT ID  */
#line 1168 "yacc_sql.y"
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
#line 2600 "yacc_sql.tab.c"
    break;

  case 120: /* condition: select comOp select  */
#line 1201 "yacc_sql.y"
                             {
		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = CONTEXT->comp_tmp[CONTEXT->select_length];
	}
#line 2608 "yacc_sql.tab.c"
    break;

  case 121: /* in_or_not_in: IN  */
#line 1207 "yacc_sql.y"
           {
		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = OP_IN;
	}
#line 2616 "yacc_sql.tab.c"
    break;

  case 122: /* in_or_not_in: NOTIN  */
#line 1210 "yacc_sql.y"
                {
		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = OP_NO_IN;
	}
#line 2624 "yacc_sql.tab.c"
    break;

  case 123: /* comOp: EQ  */
#line 1216 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO;  CONTEXT->comp_tmp[CONTEXT->select_length] = EQUAL_TO; }
#line 2630 "yacc_sql.tab.c"
    break;

  case 124: /* comOp: LT  */
#line 1217 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN;  CONTEXT->comp_tmp[CONTEXT->select_length] = LESS_THAN; }
#line 2636 "yacc_sql.tab.c"
    break;

  case 125: /* comOp: GT  */
#line 1218 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN;  CONTEXT->comp_tmp[CONTEXT->select_length] = GREAT_THAN; }
#line 2642 "yacc_sql.tab.c"
    break;

  case 126: /* comOp: LE  */
#line 1219 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL;  CONTEXT->comp_tmp[CONTEXT->select_length] = LESS_EQUAL; }
#line 2648 "yacc_sql.tab.c"
    break;

  case 127: /* comOp: GE  */
#line 1220 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL;  CONTEXT->comp_tmp[CONTEXT->select_length] = GREAT_EQUAL; }
#line 2654 "yacc_sql.tab.c"
    break;

  case 128: /* comOp: NE  */
#line 1221 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; CONTEXT->comp_tmp[CONTEXT->select_length] = NOT_EQUAL; }
#line 2660 "yacc_sql.tab.c"
    break;

  case 130: /* order_by: ORDERBY order_by_attr order_by_list  */
#line 1227 "yacc_sql.y"
                                              {
		
	}
#line 2668 "yacc_sql.tab.c"
    break;

  case 132: /* order_by_list: COMMA order_by_attr order_by_list  */
#line 1233 "yacc_sql.y"
                                            {
			
	}
#line 2676 "yacc_sql.tab.c"
    break;

  case 133: /* order_by_attr: ID order_by_type  */
#line 1239 "yacc_sql.y"
                         {	
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_orderbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
#line 2686 "yacc_sql.tab.c"
    break;

  case 134: /* order_by_attr: ID DOT ID order_by_type  */
#line 1244 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_orderbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
#line 2696 "yacc_sql.tab.c"
    break;

  case 135: /* order_by_type: %empty  */
#line 1251 "yacc_sql.y"
                   {
		CONTEXT->order_by_type = 0;
	}
#line 2704 "yacc_sql.tab.c"
    break;

  case 136: /* order_by_type: ASC  */
#line 1254 "yacc_sql.y"
              {
		CONTEXT->order_by_type = 0;
	}
#line 2712 "yacc_sql.tab.c"
    break;

  case 137: /* order_by_type: DESC  */
#line 1257 "yacc_sql.y"
               {
		CONTEXT->order_by_type = 1;
	}
#line 2720 "yacc_sql.tab.c"
    break;

  case 139: /* group_by: GROUPBY group_by_attr group_by_list  */
#line 1264 "yacc_sql.y"
                                              {

	}
#line 2728 "yacc_sql.tab.c"
    break;

  case 141: /* group_by_list: COMMA group_by_attr group_by_list  */
#line 1270 "yacc_sql.y"
                                            {
			
	}
#line 2736 "yacc_sql.tab.c"
    break;

  case 142: /* group_by_attr: ID order_by_type  */
#line 1276 "yacc_sql.y"
                         {	
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_groupbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
#line 2746 "yacc_sql.tab.c"
    break;

  case 143: /* group_by_attr: ID DOT ID order_by_type  */
#line 1281 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_groupbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
#line 2756 "yacc_sql.tab.c"
    break;

  case 144: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 1291 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2765 "yacc_sql.tab.c"
    break;


#line 2769 "yacc_sql.tab.c"

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

#line 1296 "yacc_sql.y"

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
