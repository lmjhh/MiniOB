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
	size_t value_length_exp;

	//做一个快照
  size_t condition_length_tmp[5];
  size_t from_length_tmp[5];
  size_t value_length_tmp[5];
	CompOp comp_tmp[5];

  Value values[MAX_NUM];
	Value values_exp[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
  char id[MAX_NUM];
  int order_by_type;
  int nullable;
  Exp exp[MAX_EXP_TMP_NUM];
  int exp_length;
  
	Selects selects[5];

	int selects_tmp_pool_length;
	Selects selects_tmp_pool[6];

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
	context->value_length_exp = 0;
  context->exp_length = 0;
  context->ssql->sstr.insertion.tuple_num = 0;
  printf(". error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 149 "yacc_sql.tab.c"

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
  YYSYMBOL_value_exp = 100,                /* value_exp  */
  YYSYMBOL_delete = 101,                   /* delete  */
  YYSYMBOL_update = 102,                   /* update  */
  YYSYMBOL_select = 103,                   /* select  */
  YYSYMBOL_left_brace = 104,               /* left_brace  */
  YYSYMBOL_select_mix = 105,               /* select_mix  */
  YYSYMBOL_mix_list = 106,                 /* mix_list  */
  YYSYMBOL_expression_attr = 107,          /* expression_attr  */
  YYSYMBOL_poly_value = 108,               /* poly_value  */
  YYSYMBOL_rel_list = 109,                 /* rel_list  */
  YYSYMBOL_inner_join = 110,               /* inner_join  */
  YYSYMBOL_inner_join_on = 111,            /* inner_join_on  */
  YYSYMBOL_where = 112,                    /* where  */
  YYSYMBOL_where_key = 113,                /* where_key  */
  YYSYMBOL_condition_list = 114,           /* condition_list  */
  YYSYMBOL_and_key = 115,                  /* and_key  */
  YYSYMBOL_expression_with_op = 116,       /* expression_with_op  */
  YYSYMBOL_expression = 117,               /* expression  */
  YYSYMBOL_condition = 118,                /* condition  */
  YYSYMBOL_in_or_not_in = 119,             /* in_or_not_in  */
  YYSYMBOL_comOp = 120,                    /* comOp  */
  YYSYMBOL_order_by = 121,                 /* order_by  */
  YYSYMBOL_order_by_list = 122,            /* order_by_list  */
  YYSYMBOL_order_by_attr = 123,            /* order_by_attr  */
  YYSYMBOL_order_by_type = 124,            /* order_by_type  */
  YYSYMBOL_group_by = 125,                 /* group_by  */
  YYSYMBOL_group_by_list = 126,            /* group_by_list  */
  YYSYMBOL_group_by_attr = 127,            /* group_by_attr  */
  YYSYMBOL_load_data = 128                 /* load_data  */
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
#define YYLAST   554

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  174
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  365

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
       0,   184,   184,   186,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   210,   215,   220,   226,   232,   238,   244,   250,   256,
     263,   269,   276,   278,   284,   291,   300,   302,   306,   317,
     331,   334,   337,   343,   346,   347,   348,   349,   350,   351,
     354,   363,   379,   381,   389,   393,   398,   402,   405,   408,
     412,   418,   421,   426,   436,   447,   465,   499,   508,   513,
     519,   524,   529,   538,   548,   556,   564,   572,   581,   583,
     589,   594,   599,   607,   617,   625,   633,   642,   651,   793,
     800,   807,   880,   882,   887,   889,   894,   900,   902,   907,
     914,   916,   921,   929,   940,   952,   964,   974,   984,   991,
    1005,  1016,  1028,  1040,  1051,  1061,  1068,  1079,  1113,  1125,
    1145,  1163,  1180,  1197,  1216,  1234,  1253,  1269,  1275,  1280,
    1286,  1292,  1298,  1303,  1316,  1322,  1328,  1335,  1342,  1350,
    1357,  1364,  1372,  1380,  1388,  1402,  1416,  1431,  1446,  1479,
    1512,  1518,  1521,  1527,  1528,  1529,  1530,  1531,  1532,  1536,
    1538,  1542,  1544,  1550,  1555,  1562,  1565,  1568,  1573,  1575,
    1579,  1581,  1587,  1592,  1601
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
  "value_list", "value", "value_exp", "delete", "update", "select",
  "left_brace", "select_mix", "mix_list", "expression_attr", "poly_value",
  "rel_list", "inner_join", "inner_join_on", "where", "where_key",
  "condition_list", "and_key", "expression_with_op", "expression",
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
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328
};
#endif

#define YYPACT_NINF (-309)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-131)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -309,   472,  -309,     4,    23,    75,   -32,    30,    48,    25,
      39,   -26,  -309,   102,   107,   110,   112,   125,    88,  -309,
    -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,  -309,  -309,  -309,   120,  -309,    68,    69,
     123,    72,    78,   394,   394,  -309,  -309,    65,  -309,   130,
    -309,   115,   149,  -309,   134,   166,   169,  -309,   113,   114,
     146,  -309,  -309,  -309,  -309,  -309,   147,    75,   172,   152,
     127,   198,   199,   394,   394,   176,   175,   271,    96,   -38,
    -309,   477,   139,  -309,   394,   394,   394,   394,   282,  -309,
    -309,   177,   184,   155,   153,   195,   163,   168,   205,  -309,
    -309,   261,   196,   183,   292,   394,   394,   394,   394,   282,
     124,   219,   149,     9,   149,  -309,  -309,     6,  -309,   215,
     238,   239,   302,   312,   322,   333,   240,  -309,   256,    55,
     222,   242,   204,  -309,   254,   512,   264,   218,  -309,  -309,
     100,   363,   196,   196,     7,  -309,   484,  -309,  -309,  -309,
     149,    34,   149,   149,   224,   228,   398,  -309,   394,   225,
     343,   353,   473,  -309,  -309,   483,   453,   453,   258,   398,
     289,   239,   163,   283,  -309,  -309,  -309,  -309,  -309,  -309,
      37,   237,   290,     9,   149,    24,   288,   293,  -309,   294,
     295,  -309,  -309,   239,   248,   184,  -309,  -309,  -309,   298,
     405,   253,  -309,  -309,  -309,  -309,  -309,  -309,   -13,  -309,
    -309,    81,    87,   -10,   373,    10,   385,  -309,  -309,    55,
     184,   255,   228,   254,   304,  -309,  -309,   301,   311,   273,
    -309,  -309,   149,    56,   149,   149,   149,   149,  -309,   303,
     272,   398,   325,  -309,   320,  -309,   463,  -309,  -309,  -309,
     173,  -309,  -309,  -309,  -309,  -309,   213,  -309,  -309,   321,
    -309,   216,  -309,  -309,   258,   357,   358,   184,  -309,  -309,
     306,   305,   364,   311,  -309,   374,   376,  -309,  -309,  -309,
    -309,  -309,    55,   314,   339,   298,   384,   345,    -7,    81,
     109,   354,   355,   356,  -309,  -309,  -309,   272,  -309,   407,
     311,   427,   414,   149,   149,   258,     5,   416,   370,   437,
    -309,   428,   440,  -309,  -309,  -309,  -309,   415,  -309,  -309,
    -309,   241,  -309,   251,   339,  -309,  -309,  -309,   443,  -309,
    -309,   228,  -309,   382,  -309,  -309,   314,  -309,     8,   434,
    -309,   398,  -309,   389,   447,  -309,  -309,    14,   416,   391,
    -309,   370,  -309,   298,   262,  -309,  -309,  -309,    14,   434,
     448,  -309,  -309,   384,  -309
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    67,     0,     0,     0,     0,     0,     0,     3,
      20,    19,    14,    15,    16,    17,     9,    10,    11,    12,
      13,     8,     5,     7,     6,     4,     0,    18,     0,     0,
       0,     0,     0,     0,     0,    61,    62,   118,    68,     0,
     117,     0,    78,    88,     0,     0,     0,    23,     0,     0,
       0,    24,    25,    26,    22,    21,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   118,     0,   107,     0,     0,
      69,     0,     0,    77,     0,     0,     0,     0,   109,    29,
      28,     0,    97,     0,     0,     0,     0,     0,     0,    27,
      34,     0,   114,     0,   108,     0,     0,     0,     0,   116,
     118,     0,    78,   119,    78,    89,    90,     0,    91,     0,
       0,    92,   103,   104,   106,   105,     0,    99,     0,     0,
       0,     0,     0,    50,    36,     0,     0,     0,   115,   119,
     110,   111,   113,   112,     0,    79,     0,    87,    70,    71,
      78,     0,    78,    78,     0,    94,     0,    63,    67,    60,
      57,    58,   118,    56,    59,     0,     0,     0,   100,     0,
       0,    92,     0,     0,    44,    45,    49,    46,    47,    48,
      40,     0,     0,   119,    78,     0,     0,     0,    74,     0,
       0,    73,    72,    92,     0,    97,    60,    57,    58,    54,
       0,     0,   153,   154,   155,   156,   157,   158,     0,   151,
     152,     0,     0,     0,     0,     0,     0,   102,    98,     0,
      97,     0,    94,    36,     0,    42,    41,    39,    32,     0,
      80,    81,    78,     0,    78,    78,    78,    78,    93,     0,
     168,     0,     0,   143,   141,   140,   119,   136,   137,   144,
     118,   120,   146,   127,   134,   135,   118,   121,   131,   148,
     150,   118,   132,   133,   100,     0,     0,    97,    37,    35,
       0,     0,     0,    32,    84,     0,     0,    83,    82,    75,
      76,    96,     0,     0,   159,    54,    52,     0,     0,     0,
       0,     0,     0,     0,   101,    64,   174,   168,    43,     0,
      32,     0,     0,    78,    78,   100,   165,   170,     0,     0,
      55,     0,     0,   142,   138,   139,   145,   118,   124,   147,
     129,   119,   149,   119,   159,    38,    33,    30,     0,    85,
      86,    94,   167,     0,   166,   172,     0,   169,   165,   161,
      65,     0,    51,     0,     0,    31,    95,   165,   170,     0,
     163,     0,   160,    54,   119,    66,   173,   171,   165,   161,
       0,   164,   162,    52,    53
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,  -252,  -309,  -309,   245,   307,  -309,  -309,
    -309,  -309,  -309,   117,  -272,  -147,  -309,  -309,  -309,    -1,
    -309,   408,   -51,    11,   332,  -146,  -220,  -309,  -187,  -309,
    -253,  -309,  -309,     1,  -212,   243,  -162,   178,   131,   160,
    -308,   234,   164,   185,  -309
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,   272,    30,    31,   173,   134,   227,   299,
     180,   135,    32,   312,   242,   165,    50,    33,    34,   166,
      36,    51,    80,   167,   120,   155,   195,   282,   128,   129,
     218,   219,    53,   109,   168,   211,   212,   309,   352,   339,
     335,   284,   337,   307,    37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      35,    83,   267,   214,   215,   216,    54,   264,   240,   199,
      38,   294,    39,   310,   247,   332,    52,   254,   332,     5,
     314,   302,   220,   150,   332,   222,    12,    78,   113,    41,
     350,    42,   114,   265,    55,   333,   151,    56,   349,   356,
      60,   232,   -78,   248,    76,    77,   255,   238,   326,   315,
     361,    57,   331,   245,   233,    88,    58,   334,    40,   145,
     334,   147,   148,   149,     5,   251,   334,   257,    54,   262,
     305,   158,    59,   183,   101,   102,   259,   184,    52,    54,
     297,   360,   159,    78,   290,   122,   123,   124,   125,   112,
       5,    43,   225,   226,   285,    79,     5,    12,   -78,   188,
     189,   191,   192,   158,   190,    61,   140,   141,   142,   143,
      62,   346,    43,    63,   196,    64,    73,    44,     5,   160,
     161,   162,   275,   163,   164,   158,   276,    66,    65,    67,
      54,    70,   230,   231,    68,    69,   196,    44,    71,    45,
      46,    47,    78,   318,    72,    48,    81,    49,    82,    44,
      73,   160,   161,   250,   144,   163,   164,   -78,    44,    76,
      45,    46,   110,   107,    45,    46,    75,    78,   111,    89,
     108,    44,    90,   160,   161,   317,  -122,   163,   164,    91,
      92,   274,    93,   277,   278,   279,   280,    94,    96,    97,
    -122,    73,   104,    98,   353,    84,    85,    86,    45,    46,
      75,    99,   100,   103,    87,   121,   103,  -122,  -122,   126,
     249,   252,    73,    54,   260,    54,  -123,    54,   127,  -128,
      54,   130,   131,   253,  -122,   258,  -122,   263,   132,   133,
    -123,  -122,   152,  -128,   136,   146,   105,   106,   107,    45,
      46,    75,   137,   291,  -125,   108,   293,  -123,  -123,   139,
    -128,  -128,   329,   330,  -130,   153,   156,   154,  -125,   157,
      45,    46,    75,   169,  -123,  -126,  -123,  -128,  -130,  -128,
     171,  -123,   172,   170,  -128,  -125,  -125,    73,   138,  -126,
     181,   194,   200,    54,   182,  -130,  -130,    73,   316,   319,
     193,    54,  -125,   217,  -125,   221,  -126,  -126,    73,  -125,
     224,   320,  -130,   228,  -130,   234,   229,   269,  -115,  -130,
     235,   236,   237,  -126,   239,  -126,   241,   270,    73,   246,
    -126,   266,   105,   106,   107,    45,    46,    75,    73,   271,
     283,   108,  -114,  -114,  -114,    45,    46,    75,    73,   273,
     281,  -114,   286,   105,   106,   107,    45,    46,    75,    73,
     287,   292,   108,  -115,  -115,  -115,  -115,  -115,  -115,   -61,
     295,   296,  -115,  -110,  -110,   107,    45,    46,    75,   -62,
     298,   300,   108,  -111,  -111,  -114,    45,    46,    75,    73,
     306,   301,  -114,  -113,  -113,  -113,    45,    46,    75,    43,
     308,   303,  -113,   304,  -112,  -112,  -112,    45,    46,    75,
     196,    43,   311,  -112,   -61,   -61,   -61,   -61,   -61,   -61,
      73,   313,   196,   -61,   -62,   -62,   -62,   -62,   -62,   -62,
     321,   322,   323,   -62,   325,   196,  -114,    45,    46,    75,
     327,   328,   196,  -114,   336,    44,   338,   160,   161,   256,
     340,   163,   164,   342,   341,   343,   345,    44,   347,   160,
     161,   261,   351,   163,   164,   354,    74,   358,    45,    46,
      75,   243,   197,   198,   355,   363,   163,   164,   268,   197,
     198,   244,     2,   163,   164,    95,     3,     4,   187,   223,
     364,     5,     6,     7,     8,     9,    10,    11,    12,   289,
     362,    13,    14,    15,   202,   203,   204,   205,   206,   207,
      16,    17,   344,   201,   202,   203,   204,   205,   206,   207,
      18,   359,   357,     0,   202,   203,   204,   205,   206,   207,
     288,   348,   209,   210,   202,   203,   204,   205,   206,   207,
     208,   324,   209,   210,   174,   175,   176,   177,   178,   179,
     213,   115,   116,   117,     0,     0,   118,   119,   115,   116,
     185,     0,     0,   118,   186
};

static const yytype_int16 yycheck[] =
{
       1,    52,   222,   165,   166,   167,     5,   219,   195,   156,
       6,   264,     8,   285,    27,    10,     5,    27,    10,     9,
      27,   273,   169,    17,    10,   171,    16,    18,    66,     6,
     338,     8,    70,   220,    66,    30,    30,     7,    30,   347,
      66,    17,    33,    56,    43,    44,    56,   193,   300,    56,
     358,     3,   305,   200,    30,    54,    31,    52,    54,   110,
      52,   112,   113,   114,     9,   212,    52,   214,    67,   216,
     282,    16,    33,    66,    73,    74,    66,    70,    67,    78,
     267,   353,    27,    18,   246,    84,    85,    86,    87,    78,
       9,    16,    55,    56,   241,    30,     9,    16,    33,   150,
      66,   152,   153,    16,    70,     3,   105,   106,   107,   108,
       3,   331,    16,     3,    27,     3,    16,    62,     9,    64,
      65,    66,    66,    68,    69,    16,    70,    39,     3,     9,
     129,     8,   183,   184,    66,    66,    27,    62,    66,    64,
      65,    66,    18,   290,    66,    70,    16,    72,    33,    62,
      16,    64,    65,    66,    30,    68,    69,    33,    62,   158,
      64,    65,    66,    63,    64,    65,    66,    18,    72,     3,
      70,    62,     3,    64,    65,    66,     3,    68,    69,    66,
      66,   232,    36,   234,   235,   236,   237,    40,    16,    37,
      17,    16,    17,    66,   341,    61,    62,    63,    64,    65,
      66,     3,     3,    30,    70,    66,    30,    34,    35,    32,
     211,   212,    16,   212,   215,   214,     3,   216,    34,     3,
     219,    66,    69,   212,    51,   214,    53,   216,    33,    66,
      17,    58,    17,    17,    66,    16,    61,    62,    63,    64,
      65,    66,    37,    30,     3,    70,    30,    34,    35,    66,
      34,    35,   303,   304,     3,    17,    16,    18,    17,     3,
      64,    65,    66,    41,    51,     3,    53,    51,    17,    53,
      66,    58,    18,    31,    58,    34,    35,    16,    17,    17,
      16,    53,    57,   282,    66,    34,    35,    16,   289,   290,
      66,   290,    51,    35,    53,     6,    34,    35,    16,    58,
      17,   290,    51,    66,    53,    17,    16,     3,    16,    58,
      17,    17,    17,    51,    66,    53,    18,    16,    16,    66,
      58,    66,    61,    62,    63,    64,    65,    66,    16,    18,
      58,    70,    61,    62,    63,    64,    65,    66,    16,    66,
      37,    70,    17,    61,    62,    63,    64,    65,    66,    16,
      30,    30,    70,    61,    62,    63,    64,    65,    66,    16,
       3,     3,    70,    61,    62,    63,    64,    65,    66,    16,
      64,    66,    70,    61,    62,    63,    64,    65,    66,    16,
      66,    17,    70,    61,    62,    63,    64,    65,    66,    16,
      51,    17,    70,    17,    61,    62,    63,    64,    65,    66,
      27,    16,    18,    70,    61,    62,    63,    64,    65,    66,
      16,    66,    27,    70,    61,    62,    63,    64,    65,    66,
      66,    66,    66,    70,    17,    27,    63,    64,    65,    66,
       3,    17,    27,    70,    18,    62,    66,    64,    65,    66,
       3,    68,    69,     3,    16,    30,     3,    62,    66,    64,
      65,    66,    18,    68,    69,    66,    62,    66,    64,    65,
      66,    56,    64,    65,    17,    17,    68,    69,   223,    64,
      65,    66,     0,    68,    69,    67,     4,     5,   146,   172,
     363,     9,    10,    11,    12,    13,    14,    15,    16,   246,
     359,    19,    20,    21,    41,    42,    43,    44,    45,    46,
      28,    29,   324,    30,    41,    42,    43,    44,    45,    46,
      38,   351,   348,    -1,    41,    42,    43,    44,    45,    46,
      57,   336,    59,    60,    41,    42,    43,    44,    45,    46,
      57,   297,    59,    60,    22,    23,    24,    25,    26,    27,
      57,    64,    65,    66,    -1,    -1,    69,    70,    64,    65,
      66,    -1,    -1,    69,    70
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    75,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    16,    19,    20,    21,    28,    29,    38,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      88,    89,    96,   101,   102,   103,   104,   128,     6,     8,
      54,     6,     8,    16,    62,    64,    65,    66,    70,    72,
     100,   105,   107,   116,   117,    66,     7,     3,    31,    33,
      66,     3,     3,     3,     3,     3,    39,     9,    66,    66,
       8,    66,    66,    16,    62,    66,   117,   117,    18,    30,
     106,    16,    33,   106,    61,    62,    63,    70,   117,     3,
       3,    66,    66,    36,    40,   105,    16,    37,    66,     3,
       3,   117,   117,    30,    17,    61,    62,    63,    70,   117,
      66,    72,   107,    66,    70,    64,    65,    66,    69,    70,
     108,    66,   117,   117,   117,   117,    32,    34,   112,   113,
      66,    69,    33,    66,    91,    95,    66,    37,    17,    66,
     117,   117,   117,   117,    30,   106,    16,   106,   106,   106,
      17,    30,    17,    17,    18,   109,    16,     3,    16,    27,
      64,    65,    66,    68,    69,    99,   103,   107,   118,    41,
      31,    66,    18,    90,    22,    23,    24,    25,    26,    27,
      94,    16,    66,    66,    70,    66,    70,   108,   106,    66,
      70,   106,   106,    66,    53,   110,    27,    64,    65,    99,
      57,    30,    41,    42,    43,    44,    45,    46,    57,    59,
      60,   119,   120,    57,   120,   120,   120,    35,   114,   115,
      99,     6,   109,    91,    17,    55,    56,    92,    66,    16,
     106,   106,    17,    30,    17,    17,    17,    17,   109,    66,
     112,    18,    98,    56,    66,    99,    66,    27,    56,   103,
      66,    99,   103,   107,    27,    56,    66,    99,   107,    66,
     103,    66,    99,   107,   118,   112,    66,   110,    90,     3,
      16,    18,    87,    66,   106,    66,    70,   106,   106,   106,
     106,    37,   111,    58,   125,    99,    17,    30,    57,   119,
     120,    30,    30,    30,   114,     3,     3,   112,    64,    93,
      66,    17,    87,    17,    17,   118,    66,   127,    51,   121,
      98,    18,    97,    66,    27,    56,   103,    66,    99,   103,
     107,    66,    66,    66,   125,    17,    87,     3,    17,   106,
     106,   114,    10,    30,    52,   124,    18,   126,    66,   123,
       3,    16,     3,    30,   121,     3,   110,    66,   127,    30,
     124,    18,   122,    99,    66,    17,   124,   126,    66,   123,
      98,   124,   122,    17,    97
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    75,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    86,    87,    87,    88,    89,    90,    90,    91,    91,
      92,    92,    92,    93,    94,    94,    94,    94,    94,    94,
      95,    96,    97,    97,    98,    98,    99,    99,    99,    99,
      99,   100,   100,   101,   102,   103,   103,   104,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   107,   108,
     108,   108,   109,   109,   110,   110,   111,   112,   112,   113,
     114,   114,   115,   116,   116,   116,   116,   116,   116,   116,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   119,   119,   120,   120,   120,   120,   120,   120,   121,
     121,   122,   122,   123,   123,   124,   124,   124,   125,   125,
     126,   126,   127,   127,   128
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
       1,     1,     1,     5,     8,    10,    11,     1,     1,     2,
       4,     4,     5,     5,     5,     7,     7,     2,     0,     3,
       5,     5,     6,     6,     6,     8,     8,     3,     1,     1,
       1,     1,     0,     3,     0,     6,     1,     0,     3,     1,
       0,     3,     1,     3,     3,     3,     3,     2,     3,     2,
       3,     3,     3,     3,     2,     3,     2,     1,     1,     3,
       3,     3,     3,     3,     5,     5,     7,     3,     3,     5,
       5,     3,     3,     3,     3,     3,     3,     3,     5,     5,
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
#line 210 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1567 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 215 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1575 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 220 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1583 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 226 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1591 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 232 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1599 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 238 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1607 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 244 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1616 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 250 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1624 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 256 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1633 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 264 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
		}
#line 1643 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 270 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));			
		}
#line 1653 "yacc_sql.tab.c"
    break;

  case 33: /* id_list: COMMA ID id_list  */
#line 278 "yacc_sql.y"
                   {
	create_index_append_attribute(&CONTEXT->ssql->sstr.create_index,(yyvsp[-1].string));
}
#line 1661 "yacc_sql.tab.c"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 285 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1670 "yacc_sql.tab.c"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 292 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1682 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 302 "yacc_sql.y"
                                   {    }
#line 1688 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type null LBRACE number RBRACE  */
#line 307 "yacc_sql.y"
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
#line 1703 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type null  */
#line 318 "yacc_sql.y"
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
#line 1718 "yacc_sql.tab.c"
    break;

  case 40: /* null: %empty  */
#line 331 "yacc_sql.y"
                   {
		CONTEXT->nullable = 0;
	}
#line 1726 "yacc_sql.tab.c"
    break;

  case 41: /* null: NOTNULL  */
#line 334 "yacc_sql.y"
                  {
		CONTEXT->nullable = 0;
	}
#line 1734 "yacc_sql.tab.c"
    break;

  case 42: /* null: NULLABLE  */
#line 337 "yacc_sql.y"
                   {
		CONTEXT->nullable = 1;
	}
#line 1742 "yacc_sql.tab.c"
    break;

  case 43: /* number: NUMBER  */
#line 343 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1748 "yacc_sql.tab.c"
    break;

  case 44: /* type: INT_T  */
#line 346 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1754 "yacc_sql.tab.c"
    break;

  case 45: /* type: DATE_T  */
#line 347 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1760 "yacc_sql.tab.c"
    break;

  case 46: /* type: STRING_T  */
#line 348 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1766 "yacc_sql.tab.c"
    break;

  case 47: /* type: FLOAT_T  */
#line 349 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1772 "yacc_sql.tab.c"
    break;

  case 48: /* type: NULL_T  */
#line 350 "yacc_sql.y"
                    {(yyval.number)=NULLS;}
#line 1778 "yacc_sql.tab.c"
    break;

  case 49: /* type: TEXT_T  */
#line 351 "yacc_sql.y"
                    { (yyval.number)=TEXTS; }
#line 1784 "yacc_sql.tab.c"
    break;

  case 50: /* ID_get: ID  */
#line 355 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1793 "yacc_sql.tab.c"
    break;

  case 51: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE values_list SEMICOLON  */
#line 364 "yacc_sql.y"
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
#line 1811 "yacc_sql.tab.c"
    break;

  case 53: /* values_list: COMMA LBRACE value value_list RBRACE values_list  */
#line 381 "yacc_sql.y"
                                                  {
	//inserts_append_tuple(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
	//临时变量清零
    //CONTEXT->value_length=0;
}
#line 1821 "yacc_sql.tab.c"
    break;

  case 54: /* value_list: %empty  */
#line 389 "yacc_sql.y"
                {
		inserts_append_tuple(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
#line 1830 "yacc_sql.tab.c"
    break;

  case 55: /* value_list: COMMA value value_list  */
#line 393 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1838 "yacc_sql.tab.c"
    break;

  case 56: /* value: DATE  */
#line 398 "yacc_sql.y"
             {
			(yyvsp[0].date) = substr((yyvsp[0].date),1,strlen((yyvsp[0].date))-2);
  		value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].date));
		}
#line 1847 "yacc_sql.tab.c"
    break;

  case 57: /* value: NUMBER  */
#line 402 "yacc_sql.y"
           {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1855 "yacc_sql.tab.c"
    break;

  case 58: /* value: FLOAT  */
#line 405 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1863 "yacc_sql.tab.c"
    break;

  case 59: /* value: SSS  */
#line 408 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1872 "yacc_sql.tab.c"
    break;

  case 60: /* value: NULL_T  */
#line 412 "yacc_sql.y"
                {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++], 0);
		}
#line 1880 "yacc_sql.tab.c"
    break;

  case 61: /* value_exp: NUMBER  */
#line 418 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values_exp[CONTEXT->value_length_exp++], (yyvsp[0].number));
		}
#line 1888 "yacc_sql.tab.c"
    break;

  case 62: /* value_exp: FLOAT  */
#line 421 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values_exp[CONTEXT->value_length_exp++], (yyvsp[0].floats));
		}
#line 1896 "yacc_sql.tab.c"
    break;

  case 63: /* delete: DELETE FROM ID where SEMICOLON  */
#line 427 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1908 "yacc_sql.tab.c"
    break;

  case 64: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 437 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1920 "yacc_sql.tab.c"
    break;

  case 65: /* select: SELECT select_mix FROM ID rel_list inner_join where group_by order_by SEMICOLON  */
#line 448 "yacc_sql.y"
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
			CONTEXT->value_length_exp = 0;
			CONTEXT->selects_tmp_pool_length=0;
	}
#line 1941 "yacc_sql.tab.c"
    break;

  case 66: /* select: left_brace SELECT select_mix FROM ID rel_list inner_join where group_by order_by RBRACE  */
#line 466 "yacc_sql.y"
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

			CONTEXT->selects_tmp_pool_length = CONTEXT->selects_tmp_pool_length % (6);
	}
#line 1976 "yacc_sql.tab.c"
    break;

  case 67: /* left_brace: LBRACE  */
#line 499 "yacc_sql.y"
               {
		CONTEXT->condition_length_tmp[CONTEXT->select_length] = CONTEXT->condition_length;
		CONTEXT->value_length_tmp[CONTEXT->select_length] = CONTEXT->value_length;
		CONTEXT->from_length_tmp[CONTEXT->select_length] = CONTEXT->from_length;
		CONTEXT->select_length++;
	}
#line 1987 "yacc_sql.tab.c"
    break;

  case 68: /* select_mix: STAR  */
#line 508 "yacc_sql.y"
             {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 1997 "yacc_sql.tab.c"
    break;

  case 69: /* select_mix: ID mix_list  */
#line 513 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);

		}
#line 2008 "yacc_sql.tab.c"
    break;

  case 70: /* select_mix: ID DOT ID mix_list  */
#line 519 "yacc_sql.y"
                             {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 2018 "yacc_sql.tab.c"
    break;

  case 71: /* select_mix: ID DOT STAR mix_list  */
#line 524 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 2028 "yacc_sql.tab.c"
    break;

  case 72: /* select_mix: POLYKEY LBRACE poly_value RBRACE mix_list  */
#line 529 "yacc_sql.y"
                                                   {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
		//select_append_poly_lsn(&CONTEXT->selects[CONTEXT->select_length]);
		
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		}
#line 2042 "yacc_sql.tab.c"
    break;

  case 73: /* select_mix: POLYKEY LBRACE STAR RBRACE mix_list  */
#line 538 "yacc_sql.y"
                                             {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
#line 2057 "yacc_sql.tab.c"
    break;

  case 74: /* select_mix: POLYKEY LBRACE ID RBRACE mix_list  */
#line 548 "yacc_sql.y"
                                           {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
		}
#line 2070 "yacc_sql.tab.c"
    break;

  case 75: /* select_mix: POLYKEY LBRACE ID DOT ID RBRACE mix_list  */
#line 556 "yacc_sql.y"
                                                  {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-6].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
	}
#line 2083 "yacc_sql.tab.c"
    break;

  case 76: /* select_mix: POLYKEY LBRACE ID DOT STAR RBRACE mix_list  */
#line 564 "yacc_sql.y"
                                                    {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-6].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
	}
#line 2096 "yacc_sql.tab.c"
    break;

  case 77: /* select_mix: expression_attr mix_list  */
#line 572 "yacc_sql.y"
                                  {
		selects_append_exp(&CONTEXT->selects[CONTEXT->select_length],&CONTEXT->exp[CONTEXT->exp_length-1]);
		exp_destroy( &CONTEXT->exp[CONTEXT->exp_length-1] );
		CONTEXT->exp_length = 0 ;

	}
#line 2107 "yacc_sql.tab.c"
    break;

  case 79: /* mix_list: COMMA ID mix_list  */
#line 583 "yacc_sql.y"
                             {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);

		}
#line 2118 "yacc_sql.tab.c"
    break;

  case 80: /* mix_list: COMMA ID DOT ID mix_list  */
#line 589 "yacc_sql.y"
                                   {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 2128 "yacc_sql.tab.c"
    break;

  case 81: /* mix_list: COMMA ID DOT STAR mix_list  */
#line 594 "yacc_sql.y"
                                     {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 2138 "yacc_sql.tab.c"
    break;

  case 82: /* mix_list: COMMA POLYKEY LBRACE poly_value RBRACE mix_list  */
#line 599 "yacc_sql.y"
                                                         {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
		
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		}
#line 2151 "yacc_sql.tab.c"
    break;

  case 83: /* mix_list: COMMA POLYKEY LBRACE STAR RBRACE mix_list  */
#line 607 "yacc_sql.y"
                                                   {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
#line 2166 "yacc_sql.tab.c"
    break;

  case 84: /* mix_list: COMMA POLYKEY LBRACE ID RBRACE mix_list  */
#line 617 "yacc_sql.y"
                                                 {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
		}
#line 2179 "yacc_sql.tab.c"
    break;

  case 85: /* mix_list: COMMA POLYKEY LBRACE ID DOT ID RBRACE mix_list  */
#line 625 "yacc_sql.y"
                                                        {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-6].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
	}
#line 2192 "yacc_sql.tab.c"
    break;

  case 86: /* mix_list: COMMA POLYKEY LBRACE ID DOT STAR RBRACE mix_list  */
#line 633 "yacc_sql.y"
                                                          {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-6].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
#line 2206 "yacc_sql.tab.c"
    break;

  case 87: /* mix_list: COMMA expression_attr mix_list  */
#line 642 "yacc_sql.y"
                                        {
		selects_append_exp(&CONTEXT->selects[CONTEXT->select_length],&CONTEXT->exp[CONTEXT->exp_length-1]);
		exp_destroy( &CONTEXT->exp[CONTEXT->exp_length-1] );
		CONTEXT->exp_length-- ;

	}
#line 2217 "yacc_sql.tab.c"
    break;

  case 88: /* expression_attr: expression_with_op  */
#line 651 "yacc_sql.y"
                          {
		//记录当前exp的名称
		set_exp_name(&CONTEXT->exp[CONTEXT->exp_length], (yyvsp[0].string));
		CONTEXT->exp_length++ ;
		
	}
#line 2228 "yacc_sql.tab.c"
    break;

  case 89: /* poly_value: NUMBER  */
#line 793 "yacc_sql.y"
          {	
		RelAttr attr1;
		relation_attr_init_for_number(&attr1, NULL, (yyvsp[0].number));
		selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr1, 0);

  		//value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
#line 2240 "yacc_sql.tab.c"
    break;

  case 90: /* poly_value: FLOAT  */
#line 800 "yacc_sql.y"
          {
		RelAttr attr1;
		relation_attr_init_for_float(&attr1, NULL, (yyvsp[0].floats));
		selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr1, 0);

  		//value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
#line 2252 "yacc_sql.tab.c"
    break;

  case 91: /* poly_value: SSS  */
#line 807 "yacc_sql.y"
         {
		//$1 = substr($1,1,strlen($1)-2);
  		RelAttr attr1;
		relation_attr_init(&attr1, NULL, (yyvsp[0].string));
		selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr1, 0);

		//value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
#line 2265 "yacc_sql.tab.c"
    break;

  case 93: /* rel_list: COMMA ID rel_list  */
#line 882 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string));
		  }
#line 2273 "yacc_sql.tab.c"
    break;

  case 95: /* inner_join: INNERJOIN ID inner_join_on condition condition_list inner_join  */
#line 889 "yacc_sql.y"
                                                                         {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-4].string));
	}
#line 2281 "yacc_sql.tab.c"
    break;

  case 96: /* inner_join_on: ON  */
#line 894 "yacc_sql.y"
           {
		Condition condition;
		condition_init_with_comp(&condition, NO_OP);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;	
	}
#line 2291 "yacc_sql.tab.c"
    break;

  case 98: /* where: where_key condition condition_list  */
#line 902 "yacc_sql.y"
                                         {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2299 "yacc_sql.tab.c"
    break;

  case 99: /* where_key: WHERE  */
#line 907 "yacc_sql.y"
                     {
			Condition condition;
			condition_init_with_comp(&condition, NO_OP);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		}
#line 2309 "yacc_sql.tab.c"
    break;

  case 101: /* condition_list: and_key condition condition_list  */
#line 916 "yacc_sql.y"
                                       {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2317 "yacc_sql.tab.c"
    break;

  case 102: /* and_key: AND  */
#line 921 "yacc_sql.y"
                    {
			Condition condition;
			condition_init_with_comp(&condition, NO_OP);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		}
#line 2327 "yacc_sql.tab.c"
    break;

  case 103: /* expression_with_op: expression PLUS expression  */
#line 929 "yacc_sql.y"
                                  { 
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "+");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
		//$$=$1+$3; 
		(yyval.string)=(char*)malloc(50*sizeof(char)); 
		strcpy((yyval.string),(yyvsp[-2].string));
		strcat((yyval.string),"+");
		strcat((yyval.string),(yyvsp[0].string));
		}
#line 2343 "yacc_sql.tab.c"
    break;

  case 104: /* expression_with_op: expression MINUS expression  */
#line 940 "yacc_sql.y"
                                   { 
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "-");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);

		//$$=$1-$3; 
		(yyval.string)=(char*)malloc(50*sizeof(char)); 
		strcpy((yyval.string),(yyvsp[-2].string));
		strcat((yyval.string),"-");
		strcat((yyval.string),(yyvsp[0].string));
		}
#line 2360 "yacc_sql.tab.c"
    break;

  case 105: /* expression_with_op: expression STAR expression  */
#line 952 "yacc_sql.y"
                                  { 
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "*");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);

		//$$=$1*$3; 
		(yyval.string)=(char*)malloc(50*sizeof(char)); 
		strcpy((yyval.string),(yyvsp[-2].string));
		strcat((yyval.string),"*");
		strcat((yyval.string),(yyvsp[0].string));
		}
#line 2377 "yacc_sql.tab.c"
    break;

  case 106: /* expression_with_op: expression DIVE expression  */
#line 964 "yacc_sql.y"
                                 {
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "/");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
		(yyval.string)=(char*)malloc(50*sizeof(char)); 
		strcpy((yyval.string),(yyvsp[-2].string));
		strcat((yyval.string),"/");
		strcat((yyval.string),(yyvsp[0].string));
        }
#line 2392 "yacc_sql.tab.c"
    break;

  case 107: /* expression_with_op: MINUS expression  */
#line 974 "yacc_sql.y"
                                        { 
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "u");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
		//$$=-$2; 
		(yyval.string)=(char*)malloc(50*sizeof(char)); 
		strcpy((yyval.string),"-");
		strcat((yyval.string),(yyvsp[0].string));
		}
#line 2407 "yacc_sql.tab.c"
    break;

  case 108: /* expression_with_op: LBRACE expression RBRACE  */
#line 984 "yacc_sql.y"
                               {
		//$$=$2; 
		(yyval.string)=(char*)malloc(50*sizeof(char)); 
		strcpy((yyval.string),"(");
		strcat((yyval.string),(yyvsp[-1].string));
		strcat((yyval.string),")");
	}
#line 2419 "yacc_sql.tab.c"
    break;

  case 109: /* expression_with_op: expression expression  */
#line 991 "yacc_sql.y"
                               {
			ExpNode expnode;
			expnode_init(&expnode, 3, NULL, NULL, "+");
			// 入当前栈
			push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
			//$$=$1+$3; 
			(yyval.string)=(char*)malloc(50*sizeof(char)); 
			strcpy((yyval.string),(yyvsp[-1].string));
			// strcat($$,"+");
			strcat((yyval.string),(yyvsp[0].string));
		}
#line 2435 "yacc_sql.tab.c"
    break;

  case 110: /* expression: expression PLUS expression  */
#line 1005 "yacc_sql.y"
                                  { 
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "+");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
		//$$=$1+$3; 
		(yyval.string)=(char*)malloc(50*sizeof(char)); 
		strcpy((yyval.string),(yyvsp[-2].string));
		strcat((yyval.string),"+");
		strcat((yyval.string),(yyvsp[0].string));
		}
#line 2451 "yacc_sql.tab.c"
    break;

  case 111: /* expression: expression MINUS expression  */
#line 1016 "yacc_sql.y"
                                   { 
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "-");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);

		//$$=$1-$3; 
		(yyval.string)=(char*)malloc(50*sizeof(char)); 
		strcpy((yyval.string),(yyvsp[-2].string));
		strcat((yyval.string),"-");
		strcat((yyval.string),(yyvsp[0].string));
		}
#line 2468 "yacc_sql.tab.c"
    break;

  case 112: /* expression: expression STAR expression  */
#line 1028 "yacc_sql.y"
                                  { 
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "*");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);

		//$$=$1*$3; 
		(yyval.string)=(char*)malloc(50*sizeof(char)); 
		strcpy((yyval.string),(yyvsp[-2].string));
		strcat((yyval.string),"*");
		strcat((yyval.string),(yyvsp[0].string));
		}
#line 2485 "yacc_sql.tab.c"
    break;

  case 113: /* expression: expression DIVE expression  */
#line 1040 "yacc_sql.y"
                                 {
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "/");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);

		(yyval.string)=(char*)malloc(50*sizeof(char)); 
		strcpy((yyval.string),(yyvsp[-2].string));
		strcat((yyval.string),"/");
		strcat((yyval.string),(yyvsp[0].string));
        }
#line 2501 "yacc_sql.tab.c"
    break;

  case 114: /* expression: MINUS expression  */
#line 1051 "yacc_sql.y"
                                        { 
		ExpNode expnode;
		expnode_init(&expnode, 3, NULL, NULL, "u");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
		//$$=-$2; 
		(yyval.string)=(char*)malloc(50*sizeof(char)); 
		strcpy((yyval.string),"-");
		strcat((yyval.string),(yyvsp[0].string));
		}
#line 2516 "yacc_sql.tab.c"
    break;

  case 115: /* expression: LBRACE expression RBRACE  */
#line 1061 "yacc_sql.y"
                               {
		//$$=$2; 
		(yyval.string)=(char*)malloc(50*sizeof(char)); 
		strcpy((yyval.string),"(");
		strcat((yyval.string),(yyvsp[-1].string));
		strcat((yyval.string),")");
		}
#line 2528 "yacc_sql.tab.c"
    break;

  case 116: /* expression: expression expression  */
#line 1068 "yacc_sql.y"
                                       {
			ExpNode expnode;
			expnode_init(&expnode, 3, NULL, NULL, "+");
			// 入当前栈
			push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
			//$$=$1+$3; 
			(yyval.string)=(char*)malloc(50*sizeof(char)); 
			strcpy((yyval.string),(yyvsp[-1].string));
			// strcat($$,"+");
			strcat((yyval.string),(yyvsp[0].string));
		}
#line 2544 "yacc_sql.tab.c"
    break;

  case 117: /* expression: value_exp  */
#line 1079 "yacc_sql.y"
                { 
		Value *value = &CONTEXT->values_exp[CONTEXT->value_length_exp - 1];
		ExpNode expnode;
		expnode_init(&expnode, 1, value, NULL, NULL);
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
		//$$=$1; 
		
		(yyval.string)=(char*)malloc(50*sizeof(char)); 
		if(value->type == INTS){sprintf((yyval.string), "%d", *(int *)value->data);}

		if(value->type == FLOATS){
			char fomatValueStr[10];
			sprintf(fomatValueStr, "%.2f", *(float *)value->data);
			if (NULL != strchr(fomatValueStr, '.')){
				int length = strlen(fomatValueStr);
				for (int i = length - 1; i > 0; i--) {
					if ('\0' == fomatValueStr[i]) {
						continue;
					}else if ('0' == fomatValueStr[i]) {
						fomatValueStr[i] = '\0';
					}else if ('.' == fomatValueStr[i]) {
						fomatValueStr[i] = '\0';
						break;
					}else{
						break;
					}
				}
      		}
			strcpy((yyval.string),fomatValueStr);
		}
		// strcpy($$,*(int *)value->data);
		// strcat($$," ");
		}
#line 2583 "yacc_sql.tab.c"
    break;

  case 118: /* expression: ID  */
#line 1113 "yacc_sql.y"
             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		ExpNode expnode;
		expnode_init(&expnode,2, NULL, &attr, NULL);
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);

		(yyval.string)=(char*)malloc(50*sizeof(char)); 
		strcpy((yyval.string),(yyvsp[0].string));
		// strcat($$," ");
	}
#line 2600 "yacc_sql.tab.c"
    break;

  case 119: /* expression: ID DOT ID  */
#line 1125 "yacc_sql.y"
                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		ExpNode expnode;
		expnode_init(&expnode,2, NULL, &attr, NULL);
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);

		(yyval.string)=(char*)malloc(50*sizeof(char)); 
		strcpy((yyval.string),(yyvsp[-2].string));
		strcat((yyval.string),".");
		strcat((yyval.string),(yyvsp[0].string));
		// strcat($$," ");
	}
#line 2619 "yacc_sql.tab.c"
    break;

  case 120: /* condition: ID comOp value  */
#line 1146 "yacc_sql.y"
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
#line 2641 "yacc_sql.tab.c"
    break;

  case 121: /* condition: value comOp value  */
#line 1164 "yacc_sql.y"
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
#line 2662 "yacc_sql.tab.c"
    break;

  case 122: /* condition: ID comOp ID  */
#line 1181 "yacc_sql.y"
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
#line 2683 "yacc_sql.tab.c"
    break;

  case 123: /* condition: value comOp ID  */
#line 1198 "yacc_sql.y"
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
#line 2706 "yacc_sql.tab.c"
    break;

  case 124: /* condition: ID DOT ID comOp value  */
#line 1217 "yacc_sql.y"
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
#line 2728 "yacc_sql.tab.c"
    break;

  case 125: /* condition: value comOp ID DOT ID  */
#line 1235 "yacc_sql.y"
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
#line 2751 "yacc_sql.tab.c"
    break;

  case 126: /* condition: ID DOT ID comOp ID DOT ID  */
#line 1254 "yacc_sql.y"
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
#line 2771 "yacc_sql.tab.c"
    break;

  case 127: /* condition: ID comOp expression_attr  */
#line 1269 "yacc_sql.y"
                                  {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		condition_init_exp(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 1, &left_attr, NULL, NULL, 2, NULL, NULL, &CONTEXT->exp[CONTEXT->exp_length-1]);

	}
#line 2782 "yacc_sql.tab.c"
    break;

  case 128: /* condition: expression_attr comOp ID  */
#line 1275 "yacc_sql.y"
                                  {
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));
		condition_init_exp(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 2, NULL, NULL, &CONTEXT->exp[CONTEXT->exp_length-1], 1, &right_attr, NULL, NULL);
	}
#line 2792 "yacc_sql.tab.c"
    break;

  case 129: /* condition: ID DOT ID comOp expression_attr  */
#line 1280 "yacc_sql.y"
                                         {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
		condition_init_exp(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 1, &left_attr, NULL, NULL, 2, NULL, NULL, &CONTEXT->exp[CONTEXT->exp_length-1]);

	}
#line 2803 "yacc_sql.tab.c"
    break;

  case 130: /* condition: expression_attr comOp ID DOT ID  */
#line 1286 "yacc_sql.y"
                                          {
		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));
		condition_init_exp(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 2, NULL, NULL, &CONTEXT->exp[CONTEXT->exp_length-1], 1, &right_attr, NULL, NULL);

	}
#line 2814 "yacc_sql.tab.c"
    break;

  case 131: /* condition: value comOp expression_attr  */
#line 1292 "yacc_sql.y"
                                     {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		condition_init_exp(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 0, NULL, left_value, NULL, 2, NULL, NULL, &CONTEXT->exp[CONTEXT->exp_length-1]);


	}
#line 2825 "yacc_sql.tab.c"
    break;

  case 132: /* condition: expression_attr comOp value  */
#line 1298 "yacc_sql.y"
                                     {
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
		condition_init_exp(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 2, NULL, NULL, &CONTEXT->exp[CONTEXT->exp_length-1], 0, NULL, right_value, NULL);

	}
#line 2835 "yacc_sql.tab.c"
    break;

  case 133: /* condition: expression_attr comOp expression_attr  */
#line 1303 "yacc_sql.y"
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
#line 2853 "yacc_sql.tab.c"
    break;

  case 134: /* condition: value IS NULL_T  */
#line 1316 "yacc_sql.y"
                          {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, left_value, 0, NULL, &right_value);
	}
#line 2864 "yacc_sql.tab.c"
    break;

  case 135: /* condition: value IS NOTNULL  */
#line 1322 "yacc_sql.y"
                           {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 0, NULL, left_value, 0, NULL, &right_value);
	}
#line 2875 "yacc_sql.tab.c"
    break;

  case 136: /* condition: ID IS NULL_T  */
#line 1328 "yacc_sql.y"
                       {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 1, &left_attr, NULL, 0, NULL, &right_value);
	}
#line 2887 "yacc_sql.tab.c"
    break;

  case 137: /* condition: ID IS NOTNULL  */
#line 1335 "yacc_sql.y"
                        {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 1, &left_attr, NULL, 0, NULL, &right_value);
	}
#line 2899 "yacc_sql.tab.c"
    break;

  case 138: /* condition: ID DOT ID IS NULL_T  */
#line 1342 "yacc_sql.y"
                              {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 1, &left_attr, NULL, 0, NULL, &right_value);

	}
#line 2912 "yacc_sql.tab.c"
    break;

  case 139: /* condition: ID DOT ID IS NOTNULL  */
#line 1350 "yacc_sql.y"
                               {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
		Value right_value;	
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 1, &left_attr, NULL, 0, NULL, &right_value);
	}
#line 2924 "yacc_sql.tab.c"
    break;

  case 140: /* condition: NULL_T IS value  */
#line 1357 "yacc_sql.y"
                         {
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Value left_value;
		value_init_null(&left_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, &left_value, 0, NULL, right_value);
	}
#line 2935 "yacc_sql.tab.c"
    break;

  case 141: /* condition: NULL_T IS ID  */
#line 1364 "yacc_sql.y"
                       {
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));
		Value left_value;
		value_init_null(&left_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, &left_value, 1, &right_attr, NULL);
	}
#line 2947 "yacc_sql.tab.c"
    break;

  case 142: /* condition: NULL_T IS ID DOT ID  */
#line 1372 "yacc_sql.y"
                             {
		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));
		Value left_value;
		value_init_null(&left_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, &left_value, 1, &right_attr, NULL);
	}
#line 2959 "yacc_sql.tab.c"
    break;

  case 143: /* condition: NULL_T IS NOTNULL  */
#line 1380 "yacc_sql.y"
                            {
		Value left_value;
		value_init_null(&left_value, 0);
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 0, NULL, &left_value, 0, NULL, &right_value);
	}
#line 2971 "yacc_sql.tab.c"
    break;

  case 144: /* condition: ID in_or_not_in select  */
#line 1388 "yacc_sql.y"
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
#line 2989 "yacc_sql.tab.c"
    break;

  case 145: /* condition: ID DOT ID in_or_not_in select  */
#line 1402 "yacc_sql.y"
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
#line 3007 "yacc_sql.tab.c"
    break;

  case 146: /* condition: ID comOp select  */
#line 1416 "yacc_sql.y"
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
#line 3026 "yacc_sql.tab.c"
    break;

  case 147: /* condition: ID DOT ID comOp select  */
#line 1431 "yacc_sql.y"
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
#line 3045 "yacc_sql.tab.c"
    break;

  case 148: /* condition: select comOp ID  */
#line 1446 "yacc_sql.y"
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
#line 3082 "yacc_sql.tab.c"
    break;

  case 149: /* condition: select comOp ID DOT ID  */
#line 1479 "yacc_sql.y"
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
#line 3119 "yacc_sql.tab.c"
    break;

  case 150: /* condition: select comOp select  */
#line 1512 "yacc_sql.y"
                             {
		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = CONTEXT->comp_tmp[CONTEXT->select_length];
	}
#line 3127 "yacc_sql.tab.c"
    break;

  case 151: /* in_or_not_in: IN  */
#line 1518 "yacc_sql.y"
           {
		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = OP_IN;
	}
#line 3135 "yacc_sql.tab.c"
    break;

  case 152: /* in_or_not_in: NOTIN  */
#line 1521 "yacc_sql.y"
                {
		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = OP_NO_IN;
	}
#line 3143 "yacc_sql.tab.c"
    break;

  case 153: /* comOp: EQ  */
#line 1527 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO;   CONTEXT->comp_tmp[CONTEXT->select_length] = EQUAL_TO; }
#line 3149 "yacc_sql.tab.c"
    break;

  case 154: /* comOp: LT  */
#line 1528 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN;   CONTEXT->comp_tmp[CONTEXT->select_length] = LESS_THAN; }
#line 3155 "yacc_sql.tab.c"
    break;

  case 155: /* comOp: GT  */
#line 1529 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN;   CONTEXT->comp_tmp[CONTEXT->select_length] = GREAT_THAN; }
#line 3161 "yacc_sql.tab.c"
    break;

  case 156: /* comOp: LE  */
#line 1530 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL;   CONTEXT->comp_tmp[CONTEXT->select_length] = LESS_EQUAL; }
#line 3167 "yacc_sql.tab.c"
    break;

  case 157: /* comOp: GE  */
#line 1531 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL;   CONTEXT->comp_tmp[CONTEXT->select_length] = GREAT_EQUAL; }
#line 3173 "yacc_sql.tab.c"
    break;

  case 158: /* comOp: NE  */
#line 1532 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL;  CONTEXT->comp_tmp[CONTEXT->select_length] = NOT_EQUAL; }
#line 3179 "yacc_sql.tab.c"
    break;

  case 160: /* order_by: ORDERBY order_by_attr order_by_list  */
#line 1538 "yacc_sql.y"
                                              {
		
	}
#line 3187 "yacc_sql.tab.c"
    break;

  case 162: /* order_by_list: COMMA order_by_attr order_by_list  */
#line 1544 "yacc_sql.y"
                                            {
			
	}
#line 3195 "yacc_sql.tab.c"
    break;

  case 163: /* order_by_attr: ID order_by_type  */
#line 1550 "yacc_sql.y"
                         {	
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_orderbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
#line 3205 "yacc_sql.tab.c"
    break;

  case 164: /* order_by_attr: ID DOT ID order_by_type  */
#line 1555 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_orderbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
#line 3215 "yacc_sql.tab.c"
    break;

  case 165: /* order_by_type: %empty  */
#line 1562 "yacc_sql.y"
                   {
		CONTEXT->order_by_type = 0;
	}
#line 3223 "yacc_sql.tab.c"
    break;

  case 166: /* order_by_type: ASC  */
#line 1565 "yacc_sql.y"
              {
		CONTEXT->order_by_type = 0;
	}
#line 3231 "yacc_sql.tab.c"
    break;

  case 167: /* order_by_type: DESC  */
#line 1568 "yacc_sql.y"
               {
		CONTEXT->order_by_type = 1;
	}
#line 3239 "yacc_sql.tab.c"
    break;

  case 169: /* group_by: GROUPBY group_by_attr group_by_list  */
#line 1575 "yacc_sql.y"
                                              {

	}
#line 3247 "yacc_sql.tab.c"
    break;

  case 171: /* group_by_list: COMMA group_by_attr group_by_list  */
#line 1581 "yacc_sql.y"
                                            {
			
	}
#line 3255 "yacc_sql.tab.c"
    break;

  case 172: /* group_by_attr: ID order_by_type  */
#line 1587 "yacc_sql.y"
                         {	
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_groupbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
#line 3265 "yacc_sql.tab.c"
    break;

  case 173: /* group_by_attr: ID DOT ID order_by_type  */
#line 1592 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_groupbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
#line 3275 "yacc_sql.tab.c"
    break;

  case 174: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 1602 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 3284 "yacc_sql.tab.c"
    break;


#line 3288 "yacc_sql.tab.c"

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

#line 1607 "yacc_sql.y"

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
