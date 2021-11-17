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
  size_t condition_length_tmp[MAX_NUM];
  size_t from_length_tmp[MAX_NUM];
  size_t value_length_tmp[MAX_NUM];
	CompOp comp_tmp[MAX_NUM];

  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
  char id[MAX_NUM];
  int order_by_type;
  int nullable;
	Selects selects[MAX_NUM];

  Exp exp[2];
  int exp_length;
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


#line 142 "yacc_sql.tab.c"

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
  YYSYMBOL_69_ = 69,                       /* '+'  */
  YYSYMBOL_70_ = 70,                       /* '-'  */
  YYSYMBOL_71_ = 71,                       /* '*'  */
  YYSYMBOL_72_ = 72,                       /* '/'  */
  YYSYMBOL_UMINUS = 73,                    /* UMINUS  */
  YYSYMBOL_74_ = 74,                       /* "+"  */
  YYSYMBOL_75_ = 75,                       /* "-"  */
  YYSYMBOL_76_ = 76,                       /* "*"  */
  YYSYMBOL_77_ = 77,                       /* "/"  */
  YYSYMBOL_YYACCEPT = 78,                  /* $accept  */
  YYSYMBOL_commands = 79,                  /* commands  */
  YYSYMBOL_command = 80,                   /* command  */
  YYSYMBOL_exit = 81,                      /* exit  */
  YYSYMBOL_help = 82,                      /* help  */
  YYSYMBOL_sync = 83,                      /* sync  */
  YYSYMBOL_begin = 84,                     /* begin  */
  YYSYMBOL_commit = 85,                    /* commit  */
  YYSYMBOL_rollback = 86,                  /* rollback  */
  YYSYMBOL_drop_table = 87,                /* drop_table  */
  YYSYMBOL_show_tables = 88,               /* show_tables  */
  YYSYMBOL_desc_table = 89,                /* desc_table  */
  YYSYMBOL_create_index = 90,              /* create_index  */
  YYSYMBOL_id_list = 91,                   /* id_list  */
  YYSYMBOL_drop_index = 92,                /* drop_index  */
  YYSYMBOL_create_table = 93,              /* create_table  */
  YYSYMBOL_attr_def_list = 94,             /* attr_def_list  */
  YYSYMBOL_attr_def = 95,                  /* attr_def  */
  YYSYMBOL_null = 96,                      /* null  */
  YYSYMBOL_number = 97,                    /* number  */
  YYSYMBOL_type = 98,                      /* type  */
  YYSYMBOL_ID_get = 99,                    /* ID_get  */
  YYSYMBOL_insert = 100,                   /* insert  */
  YYSYMBOL_values_list = 101,              /* values_list  */
  YYSYMBOL_value_list = 102,               /* value_list  */
  YYSYMBOL_value = 103,                    /* value  */
  YYSYMBOL_delete = 104,                   /* delete  */
  YYSYMBOL_update = 105,                   /* update  */
  YYSYMBOL_select = 106,                   /* select  */
  YYSYMBOL_left_brace = 107,               /* left_brace  */
  YYSYMBOL_select_mix = 108,               /* select_mix  */
  YYSYMBOL_mix_list = 109,                 /* mix_list  */
  YYSYMBOL_poly_value = 110,               /* poly_value  */
  YYSYMBOL_rel_list = 111,                 /* rel_list  */
  YYSYMBOL_inner_join = 112,               /* inner_join  */
  YYSYMBOL_inner_join_on = 113,            /* inner_join_on  */
  YYSYMBOL_where = 114,                    /* where  */
  YYSYMBOL_where_key = 115,                /* where_key  */
  YYSYMBOL_condition_list = 116,           /* condition_list  */
  YYSYMBOL_and_key = 117,                  /* and_key  */
  YYSYMBOL_expression = 118,               /* expression  */
  YYSYMBOL_condition = 119,                /* condition  */
  YYSYMBOL_in_or_not_in = 120,             /* in_or_not_in  */
  YYSYMBOL_comOp = 121,                    /* comOp  */
  YYSYMBOL_order_by = 122,                 /* order_by  */
  YYSYMBOL_order_by_list = 123,            /* order_by_list  */
  YYSYMBOL_order_by_attr = 124,            /* order_by_attr  */
  YYSYMBOL_order_by_type = 125,            /* order_by_type  */
  YYSYMBOL_group_by = 126,                 /* group_by  */
  YYSYMBOL_group_by_list = 127,            /* group_by_list  */
  YYSYMBOL_group_by_attr = 128,            /* group_by_attr  */
  YYSYMBOL_load_data = 129                 /* load_data  */
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
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  154
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  332

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
       2,     2,    71,    69,     2,    70,     2,    72,     2,     2,
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
      65,    66,    67,    68,    73,    74,    75,    76,    77
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   171,   171,   173,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   197,   202,   207,   213,   219,   225,   231,   237,   243,
     250,   256,   263,   265,   271,   278,   287,   289,   293,   304,
     318,   321,   324,   330,   333,   334,   335,   336,   337,   340,
     349,   365,   367,   375,   379,   384,   388,   391,   394,   398,
     404,   414,   425,   441,   449,   458,   463,   469,   474,   479,
     488,   498,   506,   514,   525,   527,   533,   538,   543,   551,
     561,   569,   577,   723,   730,   737,   810,   812,   817,   819,
     824,   830,   832,   837,   844,   846,   851,   859,   866,   874,
     882,   888,   895,   898,   905,   913,   926,   944,   961,   978,
     997,  1015,  1034,  1050,  1058,  1064,  1070,  1077,  1084,  1092,
    1099,  1106,  1114,  1122,  1130,  1145,  1160,  1176,  1192,  1226,
    1260,  1288,  1291,  1298,  1299,  1300,  1301,  1302,  1303,  1306,
    1308,  1312,  1314,  1320,  1325,  1332,  1335,  1338,  1343,  1345,
    1349,  1351,  1357,  1362,  1371
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
  "POLYKEY", "'+'", "'-'", "'*'", "'/'", "UMINUS", "\"+\"", "\"-\"",
  "\"*\"", "\"/\"", "$accept", "commands", "command", "exit", "help",
  "sync", "begin", "commit", "rollback", "drop_table", "show_tables",
  "desc_table", "create_index", "id_list", "drop_index", "create_table",
  "attr_def_list", "attr_def", "null", "number", "type", "ID_get",
  "insert", "values_list", "value_list", "value", "delete", "update",
  "select", "left_brace", "select_mix", "mix_list", "poly_value",
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
     315,   316,   317,   318,   319,   320,   321,   322,   323,    43,
      45,    42,    47,   324,   325,   326,   327,   328
};
#endif

#define YYPACT_NINF (-245)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -245,   170,  -245,    12,   130,    89,   -36,    35,   107,    78,
      83,    58,  -245,   113,   126,   127,   143,   163,    95,  -245,
    -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,
    -245,  -245,  -245,  -245,  -245,  -245,   160,  -245,   106,   114,
     179,   116,   132,     7,  -245,   172,   164,   192,   202,  -245,
     144,   146,   174,  -245,  -245,  -245,  -245,  -245,   173,    89,
     222,   175,   155,   215,   238,   -39,    73,  -245,   154,   180,
    -245,  -245,   213,   220,   200,   189,   247,   218,   219,   246,
    -245,  -245,    76,   267,   266,   266,  -245,  -245,    11,  -245,
     268,   269,   270,   271,  -245,   286,     8,   250,   261,   230,
    -245,   275,   248,   278,   233,    81,  -245,   195,  -245,  -245,
     266,    96,   266,   266,   234,   245,    67,  -245,    -4,   242,
    -245,  -245,   181,  -245,  -245,    -4,   207,   224,   159,   265,
      67,   294,   270,   218,   284,  -245,  -245,  -245,  -245,  -245,
      20,   240,   287,   266,   266,    14,   288,   289,  -245,   290,
     291,  -245,  -245,   270,   249,   220,  -245,   292,    -4,   280,
    -245,    10,    99,   251,  -245,  -245,  -245,  -245,  -245,  -245,
     -10,  -245,  -245,   102,    80,   201,    -7,   -11,    30,    -4,
      -4,    -4,    -4,    -4,  -245,  -245,     8,   220,   252,   245,
     275,   301,  -245,  -245,   296,   297,   254,  -245,  -245,   266,
     105,   266,   266,   266,   266,  -245,   281,   262,    67,   303,
     256,  -245,  -245,   293,  -245,   187,  -245,  -245,  -245,  -245,
    -245,  -245,  -245,  -245,   295,  -245,   298,  -245,   201,   201,
     201,   201,   201,   265,   318,   320,   220,  -245,  -245,   272,
     263,   309,   297,  -245,   311,   312,  -245,  -245,  -245,  -245,
    -245,     8,   273,   283,   292,   313,  -245,   274,    54,   102,
      88,   276,   277,  -245,  -245,  -245,   262,  -245,   317,   297,
     327,   323,   266,   266,   265,    37,   319,   279,   339,  -245,
     328,   340,  -245,  -245,  -245,  -245,   316,  -245,  -245,  -245,
    -245,   283,  -245,  -245,  -245,   343,  -245,  -245,   245,  -245,
     285,  -245,  -245,   273,  -245,    52,   330,  -245,    67,  -245,
     299,   332,  -245,  -245,     1,   319,   300,  -245,   279,  -245,
     292,  -245,  -245,  -245,  -245,     1,   330,   333,  -245,  -245,
     313,  -245
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
      56,    57,   104,    55,    58,     0,   103,     0,     0,    94,
       0,     0,    86,     0,     0,    44,    45,    46,    47,    48,
      40,     0,     0,    74,    74,     0,     0,     0,    71,     0,
       0,    70,    69,    86,     0,    91,    59,    53,     0,   104,
     103,     0,     0,     0,   133,   134,   135,   136,   137,   138,
       0,   131,   132,     0,     0,   101,     0,     0,     0,     0,
       0,     0,     0,     0,    96,    92,     0,    91,     0,    88,
      36,     0,    42,    41,    39,    32,     0,    76,    77,    74,
       0,    74,    74,    74,    74,    87,     0,   148,     0,     0,
       0,   102,   123,   121,   120,   105,   116,   117,   124,   108,
     106,   126,   114,   115,   109,   107,   128,   130,    97,    98,
      99,   100,   113,    94,     0,     0,    91,    37,    35,     0,
       0,     0,    32,    80,     0,     0,    79,    78,    72,    73,
      90,     0,     0,   139,    53,    51,   105,     0,     0,     0,
       0,     0,     0,    95,    61,   154,   148,    43,     0,    32,
       0,     0,    74,    74,    94,   145,   150,     0,     0,    54,
       0,     0,   122,   118,   119,   125,     0,   110,   127,   111,
     129,   139,    38,    33,    30,     0,    81,    82,    88,   147,
       0,   146,   152,     0,   149,   145,   141,    62,     0,    50,
       0,     0,    31,    89,   145,   150,     0,   143,     0,   140,
      53,   112,    63,   153,   151,   145,   141,     0,   144,   142,
      51,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,
    -245,  -245,  -245,  -135,  -245,  -245,   161,   221,  -245,  -245,
    -245,  -245,  -245,    22,  -244,   -95,  -245,  -245,    -1,  -245,
     304,   -80,   253,   -94,  -186,  -245,  -146,  -245,  -219,  -245,
     -81,  -173,   138,  -120,    64,    31,    38,  -188,    92,    44,
      61,  -245
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,   241,    30,    31,   134,   101,   194,   268,
     140,   102,    32,   281,   209,   160,    33,    34,   127,    36,
      46,    67,    91,   115,   155,   251,    95,    96,   185,   186,
     128,   129,   173,   174,   278,   319,   306,   302,   253,   304,
     276,    37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      35,   126,   106,   236,   108,   109,   177,   178,   183,   207,
     279,   299,   158,   233,   263,   156,   216,     5,    38,   222,
      39,   157,   156,    82,   118,    65,    47,   211,   110,    83,
     148,   199,   151,   152,   119,   187,    66,   161,   189,     5,
     111,   234,    48,   200,   175,   217,    12,   299,   223,   120,
     121,   224,   301,   123,   124,   298,   120,   121,   159,   205,
     123,   124,   299,   197,   198,    40,   300,   214,   120,   121,
     122,   125,   123,   124,   192,   193,   327,   161,   274,   220,
     283,   316,   225,   125,   179,   180,   181,   182,   301,     5,
     266,   126,   226,   156,    65,   260,    12,     5,   228,   229,
     230,   231,   232,   301,    12,   105,   156,   271,    50,   284,
      49,     5,   313,   254,   156,    51,    53,   317,    12,   243,
      52,   246,   247,   248,   249,   156,   323,   120,   121,    54,
      55,   123,   124,    58,   293,    84,    41,   328,    42,    85,
     120,   121,   219,   143,   123,   124,    56,   144,   120,   121,
     286,    43,   123,   124,   212,    44,   126,    45,   149,   120,
     121,   213,   150,   123,   124,   287,    57,   244,    60,    59,
       2,   245,   218,   221,     3,     4,    61,   227,    63,     5,
       6,     7,     8,     9,    10,    11,    12,    62,    68,    13,
      14,    15,   296,   297,    64,    70,    69,    16,    17,   164,
     165,   166,   167,   168,   169,    71,    72,    18,    73,    74,
     163,    78,    75,   320,    86,    87,    88,    79,    80,    89,
      90,   164,   165,   166,   167,   168,   169,   164,   165,   166,
     167,   168,   169,   179,   180,   181,   182,   170,    77,   171,
     172,    81,    92,   258,    93,   171,   172,   164,   165,   166,
     167,   168,   169,    94,    98,    86,    87,   145,   285,   288,
      89,   146,    97,   176,   164,   165,   166,   167,   168,   169,
     135,   136,   137,   138,   139,   179,   180,   181,   182,    99,
     100,   103,   104,   107,    65,   112,   113,   116,   114,   117,
     130,   131,   132,   133,   141,   142,   153,   154,   162,   184,
     188,   191,   195,   196,   238,   201,   202,   203,   204,   210,
     208,   206,   239,   215,   235,   240,   242,   250,   256,   252,
     255,   264,   257,   265,   261,   269,   270,   262,   272,   273,
     294,   280,   267,   277,   292,   275,   282,   303,   289,   290,
     295,   305,   307,   309,   308,   310,   312,   314,   318,   322,
     330,   237,   331,   259,   190,   311,   326,   329,   291,   324,
     147,   321,   325,    76,   315
};

static const yytype_int16 yycheck[] =
{
       1,    96,    82,   189,    84,    85,   126,   127,   128,   155,
     254,    10,    16,   186,   233,    26,    26,     9,     6,    26,
       8,   116,    26,    62,    16,    18,    62,    17,    17,    68,
     110,    17,   112,   113,    26,   130,    29,   118,   132,     9,
      29,   187,     7,    29,   125,    55,    16,    10,    55,    60,
      61,    62,    51,    64,    65,   274,    60,    61,    62,   153,
      64,    65,    10,   143,   144,    53,    29,   162,    60,    61,
      62,    75,    64,    65,    54,    55,   320,   158,   251,   174,
      26,    29,   177,    75,    74,    75,    76,    77,    51,     9,
     236,   186,    62,    26,    18,   215,    16,     9,   179,   180,
     181,   182,   183,    51,    16,    29,    26,   242,    30,    55,
       3,     9,   298,   208,    26,    32,     3,   305,    16,   199,
      62,   201,   202,   203,   204,    26,   314,    60,    61,     3,
       3,    64,    65,    38,   269,    62,     6,   325,     8,    66,
      60,    61,    62,    62,    64,    65,     3,    66,    60,    61,
      62,    62,    64,    65,    55,    66,   251,    68,    62,    60,
      61,    62,    66,    64,    65,   260,     3,    62,    62,     9,
       0,    66,   173,   174,     4,     5,    62,   178,    62,     9,
      10,    11,    12,    13,    14,    15,    16,     8,    16,    19,
      20,    21,   272,   273,    62,     3,    32,    27,    28,    40,
      41,    42,    43,    44,    45,     3,    62,    37,    62,    35,
      29,    36,    39,   308,    60,    61,    62,    62,     3,    65,
      66,    40,    41,    42,    43,    44,    45,    40,    41,    42,
      43,    44,    45,    74,    75,    76,    77,    56,    16,    58,
      59,     3,    62,    56,    31,    58,    59,    40,    41,    42,
      43,    44,    45,    33,    65,    60,    61,    62,   259,   260,
      65,    66,    62,    56,    40,    41,    42,    43,    44,    45,
      22,    23,    24,    25,    26,    74,    75,    76,    77,    32,
      62,    62,    36,    16,    18,    17,    17,    16,    18,     3,
      40,    30,    62,    18,    16,    62,    62,    52,    56,    34,
       6,    17,    62,    16,     3,    17,    17,    17,    17,    29,
      18,    62,    16,    62,    62,    18,    62,    36,    62,    57,
      17,     3,    29,     3,    29,    62,    17,    29,    17,    17,
       3,    18,    60,    50,    17,    62,    62,    18,    62,    62,
      17,    62,     3,     3,    16,    29,     3,    62,    18,    17,
      17,   190,   330,   215,   133,   291,   318,   326,   266,   315,
     107,    62,    62,    59,   303
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    79,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    16,    19,    20,    21,    27,    28,    37,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      92,    93,   100,   104,   105,   106,   107,   129,     6,     8,
      53,     6,     8,    62,    66,    68,   108,    62,     7,     3,
      30,    32,    62,     3,     3,     3,     3,     3,    38,     9,
      62,    62,     8,    62,    62,    18,    29,   109,    16,    32,
       3,     3,    62,    62,    35,    39,   108,    16,    36,    62,
       3,     3,    62,    68,    62,    66,    60,    61,    62,    65,
      66,   110,    62,    31,    33,   114,   115,    62,    65,    32,
      62,    95,    99,    62,    36,    29,   109,    16,   109,   109,
      17,    29,    17,    17,    18,   111,    16,     3,    16,    26,
      60,    61,    62,    64,    65,    75,   103,   106,   118,   119,
      40,    30,    62,    18,    94,    22,    23,    24,    25,    26,
      98,    16,    62,    62,    66,    62,    66,   110,   109,    62,
      66,   109,   109,    62,    52,   112,    26,   103,    16,    62,
     103,   118,    56,    29,    40,    41,    42,    43,    44,    45,
      56,    58,    59,   120,   121,   118,    56,   121,   121,    74,
      75,    76,    77,   121,    34,   116,   117,   103,     6,   111,
      95,    17,    54,    55,    96,    62,    16,   109,   109,    17,
      29,    17,    17,    17,    17,   111,    62,   114,    18,   102,
      29,    17,    55,    62,   103,    62,    26,    55,   106,    62,
     103,   106,    26,    55,    62,   103,    62,   106,   118,   118,
     118,   118,   118,   119,   114,    62,   112,    94,     3,    16,
      18,    91,    62,   109,    62,    66,   109,   109,   109,   109,
      36,   113,    57,   126,   103,    17,    62,    29,    56,   120,
     121,    29,    29,   116,     3,     3,   114,    60,    97,    62,
      17,    91,    17,    17,   119,    62,   128,    50,   122,   102,
      18,   101,    62,    26,    55,   106,    62,   103,   106,    62,
      62,   126,    17,    91,     3,    17,   109,   109,   116,    10,
      29,    51,   125,    18,   127,    62,   124,     3,    16,     3,
      29,   122,     3,   112,    62,   128,    29,   125,    18,   123,
     103,    62,    17,   125,   127,    62,   124,   102,   125,   123,
      17,   101
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    78,    79,    79,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    90,    91,    91,    92,    93,    94,    94,    95,    95,
      96,    96,    96,    97,    98,    98,    98,    98,    98,    99,
     100,   101,   101,   102,   102,   103,   103,   103,   103,   103,
     104,   105,   106,   106,   107,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   110,   110,   110,   111,   111,   112,   112,
     113,   114,   114,   115,   116,   116,   117,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   120,   120,   121,   121,   121,   121,   121,   121,   122,
     122,   123,   123,   124,   124,   125,   125,   125,   126,   126,
     127,   127,   128,   128,   129
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
       3,     2,     3,     1,     1,     3,     3,     3,     3,     3,
       5,     5,     7,     3,     3,     3,     3,     3,     5,     5,
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
#line 197 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1507 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 202 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1515 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 207 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1523 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 213 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1531 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 219 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1539 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 225 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1547 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 231 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1556 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 237 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1564 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 243 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1573 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 251 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
		}
#line 1583 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 257 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));			
		}
#line 1593 "yacc_sql.tab.c"
    break;

  case 33: /* id_list: COMMA ID id_list  */
#line 265 "yacc_sql.y"
                   {
	create_index_append_attribute(&CONTEXT->ssql->sstr.create_index,(yyvsp[-1].string));
}
#line 1601 "yacc_sql.tab.c"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 272 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1610 "yacc_sql.tab.c"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 279 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1622 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 289 "yacc_sql.y"
                                   {    }
#line 1628 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type null LBRACE number RBRACE  */
#line 294 "yacc_sql.y"
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
#line 1643 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type null  */
#line 305 "yacc_sql.y"
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
#line 1658 "yacc_sql.tab.c"
    break;

  case 40: /* null: %empty  */
#line 318 "yacc_sql.y"
                   {
		CONTEXT->nullable = 0;
	}
#line 1666 "yacc_sql.tab.c"
    break;

  case 41: /* null: NOTNULL  */
#line 321 "yacc_sql.y"
                  {
		CONTEXT->nullable = 0;
	}
#line 1674 "yacc_sql.tab.c"
    break;

  case 42: /* null: NULLABLE  */
#line 324 "yacc_sql.y"
                   {
		CONTEXT->nullable = 1;
	}
#line 1682 "yacc_sql.tab.c"
    break;

  case 43: /* number: NUMBER  */
#line 330 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1688 "yacc_sql.tab.c"
    break;

  case 44: /* type: INT_T  */
#line 333 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1694 "yacc_sql.tab.c"
    break;

  case 45: /* type: DATE_T  */
#line 334 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1700 "yacc_sql.tab.c"
    break;

  case 46: /* type: STRING_T  */
#line 335 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1706 "yacc_sql.tab.c"
    break;

  case 47: /* type: FLOAT_T  */
#line 336 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1712 "yacc_sql.tab.c"
    break;

  case 48: /* type: NULL_T  */
#line 337 "yacc_sql.y"
                    {(yyval.number)=NULLS;}
#line 1718 "yacc_sql.tab.c"
    break;

  case 49: /* ID_get: ID  */
#line 341 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1727 "yacc_sql.tab.c"
    break;

  case 50: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE values_list SEMICOLON  */
#line 350 "yacc_sql.y"
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
#line 1745 "yacc_sql.tab.c"
    break;

  case 52: /* values_list: COMMA LBRACE value value_list RBRACE values_list  */
#line 367 "yacc_sql.y"
                                                  {
	//inserts_append_tuple(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
	//临时变量清零
    //CONTEXT->value_length=0;
}
#line 1755 "yacc_sql.tab.c"
    break;

  case 53: /* value_list: %empty  */
#line 375 "yacc_sql.y"
                {
		inserts_append_tuple(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
#line 1764 "yacc_sql.tab.c"
    break;

  case 54: /* value_list: COMMA value value_list  */
#line 379 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1772 "yacc_sql.tab.c"
    break;

  case 55: /* value: DATE  */
#line 384 "yacc_sql.y"
             {
			(yyvsp[0].date) = substr((yyvsp[0].date),1,strlen((yyvsp[0].date))-2);
  		value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].date));
		}
#line 1781 "yacc_sql.tab.c"
    break;

  case 56: /* value: NUMBER  */
#line 388 "yacc_sql.y"
           {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1789 "yacc_sql.tab.c"
    break;

  case 57: /* value: FLOAT  */
#line 391 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1797 "yacc_sql.tab.c"
    break;

  case 58: /* value: SSS  */
#line 394 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1806 "yacc_sql.tab.c"
    break;

  case 59: /* value: NULL_T  */
#line 398 "yacc_sql.y"
                {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++], 0);
	}
#line 1814 "yacc_sql.tab.c"
    break;

  case 60: /* delete: DELETE FROM ID where SEMICOLON  */
#line 405 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1826 "yacc_sql.tab.c"
    break;

  case 61: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 415 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1838 "yacc_sql.tab.c"
    break;

  case 62: /* select: SELECT select_mix FROM ID rel_list inner_join where group_by order_by SEMICOLON  */
#line 426 "yacc_sql.y"
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
	}
#line 1857 "yacc_sql.tab.c"
    break;

  case 63: /* select: left_brace SELECT select_mix FROM ID rel_list inner_join where group_by order_by RBRACE  */
#line 442 "yacc_sql.y"
        {
			selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-6].string));
			selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length], CONTEXT->conditions, CONTEXT->condition_length_tmp[CONTEXT->select_length - 1], CONTEXT->condition_length);
	}
#line 1866 "yacc_sql.tab.c"
    break;

  case 64: /* left_brace: LBRACE  */
#line 449 "yacc_sql.y"
               {
		CONTEXT->condition_length_tmp[CONTEXT->select_length] = CONTEXT->condition_length;
		CONTEXT->value_length_tmp[CONTEXT->select_length] = CONTEXT->value_length;
		CONTEXT->from_length_tmp[CONTEXT->select_length] = CONTEXT->from_length;
		CONTEXT->select_length++;
	}
#line 1877 "yacc_sql.tab.c"
    break;

  case 65: /* select_mix: STAR  */
#line 458 "yacc_sql.y"
             {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 1887 "yacc_sql.tab.c"
    break;

  case 66: /* select_mix: ID mix_list  */
#line 463 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);

		}
#line 1898 "yacc_sql.tab.c"
    break;

  case 67: /* select_mix: ID DOT ID mix_list  */
#line 469 "yacc_sql.y"
                             {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 1908 "yacc_sql.tab.c"
    break;

  case 68: /* select_mix: ID DOT STAR mix_list  */
#line 474 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 1918 "yacc_sql.tab.c"
    break;

  case 69: /* select_mix: POLYKEY LBRACE poly_value RBRACE mix_list  */
#line 479 "yacc_sql.y"
                                                   {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
		//select_append_poly_lsn(&CONTEXT->selects[CONTEXT->select_length]);
		
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		}
#line 1932 "yacc_sql.tab.c"
    break;

  case 70: /* select_mix: POLYKEY LBRACE STAR RBRACE mix_list  */
#line 488 "yacc_sql.y"
                                             {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
#line 1947 "yacc_sql.tab.c"
    break;

  case 71: /* select_mix: POLYKEY LBRACE ID RBRACE mix_list  */
#line 498 "yacc_sql.y"
                                           {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
		}
#line 1960 "yacc_sql.tab.c"
    break;

  case 72: /* select_mix: POLYKEY LBRACE ID DOT ID RBRACE mix_list  */
#line 506 "yacc_sql.y"
                                                  {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-6].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
	}
#line 1973 "yacc_sql.tab.c"
    break;

  case 73: /* select_mix: POLYKEY LBRACE ID DOT STAR RBRACE mix_list  */
#line 514 "yacc_sql.y"
                                                    {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-6].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
	}
#line 1986 "yacc_sql.tab.c"
    break;

  case 75: /* mix_list: COMMA ID mix_list  */
#line 527 "yacc_sql.y"
                             {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);

		}
#line 1997 "yacc_sql.tab.c"
    break;

  case 76: /* mix_list: COMMA ID DOT ID mix_list  */
#line 533 "yacc_sql.y"
                                   {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 2007 "yacc_sql.tab.c"
    break;

  case 77: /* mix_list: COMMA ID DOT STAR mix_list  */
#line 538 "yacc_sql.y"
                                     {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
		}
#line 2017 "yacc_sql.tab.c"
    break;

  case 78: /* mix_list: COMMA POLYKEY LBRACE poly_value RBRACE mix_list  */
#line 543 "yacc_sql.y"
                                                         {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
		
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		}
#line 2030 "yacc_sql.tab.c"
    break;

  case 79: /* mix_list: COMMA POLYKEY LBRACE STAR RBRACE mix_list  */
#line 551 "yacc_sql.y"
                                                   {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
#line 2045 "yacc_sql.tab.c"
    break;

  case 80: /* mix_list: COMMA POLYKEY LBRACE ID RBRACE mix_list  */
#line 561 "yacc_sql.y"
                                                 {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-4].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
		}
#line 2058 "yacc_sql.tab.c"
    break;

  case 81: /* mix_list: COMMA POLYKEY LBRACE ID DOT ID RBRACE mix_list  */
#line 569 "yacc_sql.y"
                                                        {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-6].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);
	}
#line 2071 "yacc_sql.tab.c"
    break;

  case 82: /* mix_list: COMMA POLYKEY LBRACE ID DOT STAR RBRACE mix_list  */
#line 577 "yacc_sql.y"
                                                          {
		Poly poly_tmp;
		poly_init(&poly_tmp, (yyvsp[-6].string));
		selects_append_poly(&CONTEXT->selects[CONTEXT->select_length], &poly_tmp);
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), "*");
			selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr, 1);

	}
#line 2085 "yacc_sql.tab.c"
    break;

  case 83: /* poly_value: NUMBER  */
#line 723 "yacc_sql.y"
          {	
		RelAttr attr1;
		relation_attr_init_for_number(&attr1, NULL, (yyvsp[0].number));
		selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr1, 0);

  		//value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
#line 2097 "yacc_sql.tab.c"
    break;

  case 84: /* poly_value: FLOAT  */
#line 730 "yacc_sql.y"
          {
		RelAttr attr1;
		relation_attr_init_for_float(&attr1, NULL, (yyvsp[0].floats));
		selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr1, 0);

  		//value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
#line 2109 "yacc_sql.tab.c"
    break;

  case 85: /* poly_value: SSS  */
#line 737 "yacc_sql.y"
         {
		//$1 = substr($1,1,strlen($1)-2);
  		RelAttr attr1;
		relation_attr_init(&attr1, NULL, (yyvsp[0].string));
		selects_append_poly_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr1, 0);

		//value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
#line 2122 "yacc_sql.tab.c"
    break;

  case 87: /* rel_list: COMMA ID rel_list  */
#line 812 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string));
		  }
#line 2130 "yacc_sql.tab.c"
    break;

  case 89: /* inner_join: INNERJOIN ID inner_join_on condition condition_list inner_join  */
#line 819 "yacc_sql.y"
                                                                         {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-4].string));
	}
#line 2138 "yacc_sql.tab.c"
    break;

  case 90: /* inner_join_on: ON  */
#line 824 "yacc_sql.y"
           {
		Condition condition;
		condition_init_with_comp(&condition, NO_OP);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;	
	}
#line 2148 "yacc_sql.tab.c"
    break;

  case 92: /* where: where_key condition condition_list  */
#line 832 "yacc_sql.y"
                                         {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2156 "yacc_sql.tab.c"
    break;

  case 93: /* where_key: WHERE  */
#line 837 "yacc_sql.y"
                     {
			Condition condition;
			condition_init_with_comp(&condition, NO_OP);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		}
#line 2166 "yacc_sql.tab.c"
    break;

  case 95: /* condition_list: and_key condition condition_list  */
#line 846 "yacc_sql.y"
                                       {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2174 "yacc_sql.tab.c"
    break;

  case 96: /* and_key: AND  */
#line 851 "yacc_sql.y"
                    {
			Condition condition;
			condition_init_with_comp(&condition, NO_OP);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		}
#line 2184 "yacc_sql.tab.c"
    break;

  case 97: /* expression: expression "+" expression  */
#line 859 "yacc_sql.y"
                                 { 
		ExpNode expnode;
		expnode_init(&expnode, 2, NULL, NULL, "+");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
		//$$=$1+$3; 
		}
#line 2196 "yacc_sql.tab.c"
    break;

  case 98: /* expression: expression "-" expression  */
#line 866 "yacc_sql.y"
                                 { 
		ExpNode expnode;
		expnode_init(&expnode, 2, NULL, NULL, "-");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);

		//$$=$1-$3; 
		}
#line 2209 "yacc_sql.tab.c"
    break;

  case 99: /* expression: expression "*" expression  */
#line 874 "yacc_sql.y"
                                 { 
		ExpNode expnode;
		expnode_init(&expnode, 2, NULL, NULL, "*");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);

		//$$=$1*$3; 
		}
#line 2222 "yacc_sql.tab.c"
    break;

  case 100: /* expression: expression "/" expression  */
#line 882 "yacc_sql.y"
                                {
		ExpNode expnode;
		expnode_init(&expnode, 2, NULL, NULL, "/");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
        }
#line 2233 "yacc_sql.tab.c"
    break;

  case 101: /* expression: "-" expression  */
#line 888 "yacc_sql.y"
                                  { 
		ExpNode expnode;
		expnode_init(&expnode, 2, NULL, NULL, "-");
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
		//$$=-$2; 
		}
#line 2245 "yacc_sql.tab.c"
    break;

  case 102: /* expression: LBRACE expression RBRACE  */
#line 895 "yacc_sql.y"
                               {
		//$$=$2; 
		}
#line 2253 "yacc_sql.tab.c"
    break;

  case 103: /* expression: value  */
#line 898 "yacc_sql.y"
            { 
		ExpNode expnode;
		expnode_init(&expnode, 0, (yyvsp[0].value1), NULL, NULL);
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
		//$$=$1; 
		}
#line 2265 "yacc_sql.tab.c"
    break;

  case 104: /* expression: ID  */
#line 905 "yacc_sql.y"
             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		ExpNode expnode;
		expnode_init(&expnode,1, NULL, &attr, NULL);
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);
	}
#line 2278 "yacc_sql.tab.c"
    break;

  case 105: /* expression: ID DOT ID  */
#line 913 "yacc_sql.y"
                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		ExpNode expnode;
		expnode_init(&expnode,1, NULL, &attr, NULL);
		// 入当前栈
		push_to_exp(&CONTEXT->exp[CONTEXT->exp_length], &expnode);

	}
#line 2292 "yacc_sql.tab.c"
    break;

  case 106: /* condition: ID comOp value  */
#line 927 "yacc_sql.y"
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
#line 2314 "yacc_sql.tab.c"
    break;

  case 107: /* condition: value comOp value  */
#line 945 "yacc_sql.y"
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
#line 2335 "yacc_sql.tab.c"
    break;

  case 108: /* condition: ID comOp ID  */
#line 962 "yacc_sql.y"
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
#line 2356 "yacc_sql.tab.c"
    break;

  case 109: /* condition: value comOp ID  */
#line 979 "yacc_sql.y"
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
#line 2379 "yacc_sql.tab.c"
    break;

  case 110: /* condition: ID DOT ID comOp value  */
#line 998 "yacc_sql.y"
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
#line 2401 "yacc_sql.tab.c"
    break;

  case 111: /* condition: value comOp ID DOT ID  */
#line 1016 "yacc_sql.y"
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
#line 2424 "yacc_sql.tab.c"
    break;

  case 112: /* condition: ID DOT ID comOp ID DOT ID  */
#line 1035 "yacc_sql.y"
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
#line 2444 "yacc_sql.tab.c"
    break;

  case 113: /* condition: expression comOp expression  */
#line 1050 "yacc_sql.y"
                                      {
		condition_init_exp(&CONTEXT->conditions[CONTEXT->condition_length - 1], CONTEXT->comp, 1, &CONTEXT->exp[0], 1, &CONTEXT->exp[1]);

		// 将临时变量清空
		exp_destroy(&CONTEXT->exp[0]);
		exp_destroy(&CONTEXT->exp[1]);
		CONTEXT->exp_length = 0;
	}
#line 2457 "yacc_sql.tab.c"
    break;

  case 114: /* condition: value IS NULL_T  */
#line 1058 "yacc_sql.y"
                          {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, left_value, 0, NULL, &right_value);
	}
#line 2468 "yacc_sql.tab.c"
    break;

  case 115: /* condition: value IS NOTNULL  */
#line 1064 "yacc_sql.y"
                           {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 0, NULL, left_value, 0, NULL, &right_value);
	}
#line 2479 "yacc_sql.tab.c"
    break;

  case 116: /* condition: ID IS NULL_T  */
#line 1070 "yacc_sql.y"
                       {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 1, &left_attr, NULL, 0, NULL, &right_value);
	}
#line 2491 "yacc_sql.tab.c"
    break;

  case 117: /* condition: ID IS NOTNULL  */
#line 1077 "yacc_sql.y"
                        {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 1, &left_attr, NULL, 0, NULL, &right_value);
	}
#line 2503 "yacc_sql.tab.c"
    break;

  case 118: /* condition: ID DOT ID IS NULL_T  */
#line 1084 "yacc_sql.y"
                              {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 1, &left_attr, NULL, 0, NULL, &right_value);

	}
#line 2516 "yacc_sql.tab.c"
    break;

  case 119: /* condition: ID DOT ID IS NOTNULL  */
#line 1092 "yacc_sql.y"
                               {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
		Value right_value;	
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 1, &left_attr, NULL, 0, NULL, &right_value);
	}
#line 2528 "yacc_sql.tab.c"
    break;

  case 120: /* condition: NULL_T IS value  */
#line 1099 "yacc_sql.y"
                         {
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Value left_value;
		value_init_null(&left_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, &left_value, 0, NULL, right_value);
	}
#line 2539 "yacc_sql.tab.c"
    break;

  case 121: /* condition: NULL_T IS ID  */
#line 1106 "yacc_sql.y"
                       {
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));
		Value left_value;
		value_init_null(&left_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, &left_value, 1, &right_attr, NULL);
	}
#line 2551 "yacc_sql.tab.c"
    break;

  case 122: /* condition: NULL_T IS ID DOT ID  */
#line 1114 "yacc_sql.y"
                             {
		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));
		Value left_value;
		value_init_null(&left_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_IS, 0, NULL, &left_value, 1, &right_attr, NULL);
	}
#line 2563 "yacc_sql.tab.c"
    break;

  case 123: /* condition: NULL_T IS NOTNULL  */
#line 1122 "yacc_sql.y"
                            {
		Value left_value;
		value_init_null(&left_value, 0);
		Value right_value;
		value_init_null(&right_value, 0);
		condition_init(&CONTEXT->conditions[CONTEXT->condition_length - 1], OP_NO_IS, 0, NULL, &left_value, 0, NULL, &right_value);
	}
#line 2575 "yacc_sql.tab.c"
    break;

  case 124: /* condition: ID in_or_not_in select  */
#line 1130 "yacc_sql.y"
                                 {

		//临时变量退栈
		CONTEXT->select_length--;
		CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
		CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
		CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

		CONTEXT->conditions[CONTEXT->condition_length - 1].left_is_attr = 1;
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));	
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_attr = 	left_attr;
		CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].right_sub_select = &CONTEXT->selects[CONTEXT->select_length + 1];
	}
#line 2594 "yacc_sql.tab.c"
    break;

  case 125: /* condition: ID DOT ID in_or_not_in select  */
#line 1145 "yacc_sql.y"
                                       {

		//临时变量退栈
		CONTEXT->select_length--;
		CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
		CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
		CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

		CONTEXT->conditions[CONTEXT->condition_length - 1].left_is_attr = 1;
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));	
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_attr = 	left_attr;
		CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].right_sub_select = &CONTEXT->selects[CONTEXT->select_length + 1];
	}
#line 2613 "yacc_sql.tab.c"
    break;

  case 126: /* condition: ID comOp select  */
#line 1160 "yacc_sql.y"
                         {

		//临时变量退栈
		CONTEXT->select_length--;
		CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
		CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
		CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = CONTEXT->comp_tmp[CONTEXT->select_length];
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_is_attr = 1;
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));	
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_attr = left_attr;
		CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].right_sub_select = &CONTEXT->selects[CONTEXT->select_length + 1];
	}
#line 2633 "yacc_sql.tab.c"
    break;

  case 127: /* condition: ID DOT ID comOp select  */
#line 1176 "yacc_sql.y"
                                {

		//临时变量退栈
		CONTEXT->select_length--;
		CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
		CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
		CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = CONTEXT->comp_tmp[CONTEXT->select_length];
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_is_attr = 1;
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));	
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_attr = left_attr;
		CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].right_sub_select = &CONTEXT->selects[CONTEXT->select_length + 1];
	}
#line 2653 "yacc_sql.tab.c"
    break;

  case 128: /* condition: select comOp ID  */
#line 1192 "yacc_sql.y"
                         {		//放 condition 左边了 改一下符号

		//临时变量退栈
		CONTEXT->select_length--;
		CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
		CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
		CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

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
		CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].right_sub_select = &CONTEXT->selects[CONTEXT->select_length + 1];

	}
#line 2691 "yacc_sql.tab.c"
    break;

  case 129: /* condition: select comOp ID DOT ID  */
#line 1226 "yacc_sql.y"
                                 {

		//临时变量退栈
		CONTEXT->select_length--;
		CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
		CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
		CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

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
		CONTEXT->conditions[CONTEXT->condition_length_tmp[CONTEXT->select_length] - 1].right_sub_select = &CONTEXT->selects[CONTEXT->select_length + 1];
	}
#line 2729 "yacc_sql.tab.c"
    break;

  case 130: /* condition: select comOp select  */
#line 1260 "yacc_sql.y"
                             {

		printf("当前selects = %d \n", CONTEXT->select_length);
		printf("当前condition = %d, comp = %d \n", CONTEXT->condition_length_tmp[CONTEXT->select_length], CONTEXT->comp);
		CONTEXT->conditions[CONTEXT->condition_length - 1].right_sub_select = &CONTEXT->selects[CONTEXT->select_length];
		//临时变量退栈
		CONTEXT->select_length--;
		CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
		CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
		CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

		printf("当前selects = %d \n", CONTEXT->select_length);
		printf("当前condition = %d, comp = %d \n", CONTEXT->condition_length_tmp[CONTEXT->select_length], CONTEXT->comp);
		CONTEXT->conditions[CONTEXT->condition_length - 1].left_sub_select = &CONTEXT->selects[CONTEXT->select_length];
		//临时变量退栈
		CONTEXT->select_length--;
		CONTEXT->condition_length = CONTEXT->condition_length_tmp[CONTEXT->select_length];
		CONTEXT->from_length = CONTEXT->from_length_tmp[CONTEXT->select_length];
		CONTEXT->value_length = CONTEXT->value_length_tmp[CONTEXT->select_length];

		printf("当前selects = %d \n", CONTEXT->select_length);
		printf("当前condition = %d, comp = %d \n", CONTEXT->condition_length_tmp[CONTEXT->select_length], CONTEXT->comp);

		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = CONTEXT->comp_tmp[CONTEXT->select_length + 1];
	}
#line 2759 "yacc_sql.tab.c"
    break;

  case 131: /* in_or_not_in: IN  */
#line 1288 "yacc_sql.y"
           {
		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = OP_IN;
	}
#line 2767 "yacc_sql.tab.c"
    break;

  case 132: /* in_or_not_in: NOTIN  */
#line 1291 "yacc_sql.y"
                {
		CONTEXT->conditions[CONTEXT->condition_length - 1].comp = OP_NO_IN;
	}
#line 2775 "yacc_sql.tab.c"
    break;

  case 133: /* comOp: EQ  */
#line 1298 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; CONTEXT->exp_length++; printf("当前 select %d 最后一condition : = \n", CONTEXT->select_length); CONTEXT->comp_tmp[CONTEXT->select_length] = EQUAL_TO; }
#line 2781 "yacc_sql.tab.c"
    break;

  case 134: /* comOp: LT  */
#line 1299 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; CONTEXT->exp_length++; printf("当前 select %d 最后一condition : < \n", CONTEXT->select_length); CONTEXT->comp_tmp[CONTEXT->select_length] = LESS_THAN; }
#line 2787 "yacc_sql.tab.c"
    break;

  case 135: /* comOp: GT  */
#line 1300 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; CONTEXT->exp_length++; printf("当前 select %d 最后一condition : > \n", CONTEXT->select_length); CONTEXT->comp_tmp[CONTEXT->select_length] = GREAT_THAN; }
#line 2793 "yacc_sql.tab.c"
    break;

  case 136: /* comOp: LE  */
#line 1301 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; CONTEXT->exp_length++; printf("当前 select %d 最后一condition : <= \n", CONTEXT->select_length); CONTEXT->comp_tmp[CONTEXT->select_length] = LESS_EQUAL; }
#line 2799 "yacc_sql.tab.c"
    break;

  case 137: /* comOp: GE  */
#line 1302 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; CONTEXT->exp_length++; printf("当前 select %d 最后一condition : >= \n", CONTEXT->select_length); CONTEXT->comp_tmp[CONTEXT->select_length] = GREAT_EQUAL; }
#line 2805 "yacc_sql.tab.c"
    break;

  case 138: /* comOp: NE  */
#line 1303 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; CONTEXT->exp_length++; printf("当前 select %d 最后一condition : != \n", CONTEXT->select_length); CONTEXT->comp_tmp[CONTEXT->select_length] = NOT_EQUAL; }
#line 2811 "yacc_sql.tab.c"
    break;

  case 140: /* order_by: ORDERBY order_by_attr order_by_list  */
#line 1308 "yacc_sql.y"
                                              {
		
	}
#line 2819 "yacc_sql.tab.c"
    break;

  case 142: /* order_by_list: COMMA order_by_attr order_by_list  */
#line 1314 "yacc_sql.y"
                                            {
			
	}
#line 2827 "yacc_sql.tab.c"
    break;

  case 143: /* order_by_attr: ID order_by_type  */
#line 1320 "yacc_sql.y"
                         {	
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_orderbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
#line 2837 "yacc_sql.tab.c"
    break;

  case 144: /* order_by_attr: ID DOT ID order_by_type  */
#line 1325 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_orderbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
#line 2847 "yacc_sql.tab.c"
    break;

  case 145: /* order_by_type: %empty  */
#line 1332 "yacc_sql.y"
                   {
		CONTEXT->order_by_type = 0;
	}
#line 2855 "yacc_sql.tab.c"
    break;

  case 146: /* order_by_type: ASC  */
#line 1335 "yacc_sql.y"
              {
		CONTEXT->order_by_type = 0;
	}
#line 2863 "yacc_sql.tab.c"
    break;

  case 147: /* order_by_type: DESC  */
#line 1338 "yacc_sql.y"
               {
		CONTEXT->order_by_type = 1;
	}
#line 2871 "yacc_sql.tab.c"
    break;

  case 149: /* group_by: GROUPBY group_by_attr group_by_list  */
#line 1345 "yacc_sql.y"
                                              {

	}
#line 2879 "yacc_sql.tab.c"
    break;

  case 151: /* group_by_list: COMMA group_by_attr group_by_list  */
#line 1351 "yacc_sql.y"
                                            {
			
	}
#line 2887 "yacc_sql.tab.c"
    break;

  case 152: /* group_by_attr: ID order_by_type  */
#line 1357 "yacc_sql.y"
                         {	
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_groupbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
#line 2897 "yacc_sql.tab.c"
    break;

  case 153: /* group_by_attr: ID DOT ID order_by_type  */
#line 1362 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_groupbyAttr(&CONTEXT->selects[CONTEXT->select_length], &attr, CONTEXT->order_by_type);
		}
#line 2907 "yacc_sql.tab.c"
    break;

  case 154: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 1372 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2916 "yacc_sql.tab.c"
    break;


#line 2920 "yacc_sql.tab.c"

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

#line 1377 "yacc_sql.y"

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
