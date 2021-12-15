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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "sintactico.y"


/********************
  Declaraciones en C
**********************/
    #include "scanner.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <QString>
    #include <iostream>
    #include <string>
    #include <string.h>
    #include <cstring>
    #include <vector>
    //#include "lista_simple.h"
    #include "estructuras.h"

    #include "nodo_arbol.h"

    extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
    extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
    extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON

    extern Nodo_arbol *raiz; // Raiz del arbol

    //extern Lista_Simple *lista = new Lista_Simple(); // Raiz del arbol
    //extern int yylex(void);
    //extern char *yytext;
    //extern int linea;
    //extern FILE *yyin;
    string expresion;
    string cadena;
    using namespace std;






    void yyerror(char *s);
 

#line 114 "parser.cpp"

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

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_tk_igual = 3,                   /* tk_igual  */
  YYSYMBOL_tk_mkdisk = 4,                  /* tk_mkdisk  */
  YYSYMBOL_tk_rmdisk = 5,                  /* tk_rmdisk  */
  YYSYMBOL_tk_fdisk = 6,                   /* tk_fdisk  */
  YYSYMBOL_tk_mount = 7,                   /* tk_mount  */
  YYSYMBOL_tk_unmount = 8,                 /* tk_unmount  */
  YYSYMBOL_tk_rep = 9,                     /* tk_rep  */
  YYSYMBOL_tk_exec = 10,                   /* tk_exec  */
  YYSYMBOL_tk_size = 11,                   /* tk_size  */
  YYSYMBOL_tk_f = 12,                      /* tk_f  */
  YYSYMBOL_tk_u = 13,                      /* tk_u  */
  YYSYMBOL_tk_path = 14,                   /* tk_path  */
  YYSYMBOL_tk_type = 15,                   /* tk_type  */
  YYSYMBOL_tk_fs = 16,                     /* tk_fs  */
  YYSYMBOL_tk_delete = 17,                 /* tk_delete  */
  YYSYMBOL_tk_name = 18,                   /* tk_name  */
  YYSYMBOL_tk_add = 19,                    /* tk_add  */
  YYSYMBOL_tk_id = 20,                     /* tk_id  */
  YYSYMBOL_tk_ruta = 21,                   /* tk_ruta  */
  YYSYMBOL_tk_numero = 22,                 /* tk_numero  */
  YYSYMBOL_tk_identificador = 23,          /* tk_identificador  */
  YYSYMBOL_tk_cadena = 24,                 /* tk_cadena  */
  YYSYMBOL_tk_primaria = 25,               /* tk_primaria  */
  YYSYMBOL_tk_extendida = 26,              /* tk_extendida  */
  YYSYMBOL_tk_logica = 27,                 /* tk_logica  */
  YYSYMBOL_tk_byte = 28,                   /* tk_byte  */
  YYSYMBOL_tk_kilo = 29,                   /* tk_kilo  */
  YYSYMBOL_tk_mega = 30,                   /* tk_mega  */
  YYSYMBOL_tk_bf = 31,                     /* tk_bf  */
  YYSYMBOL_tk_ff = 32,                     /* tk_ff  */
  YYSYMBOL_tk_wf = 33,                     /* tk_wf  */
  YYSYMBOL_tk_fast = 34,                   /* tk_fast  */
  YYSYMBOL_tk_full = 35,                   /* tk_full  */
  YYSYMBOL_tk_2fs = 36,                    /* tk_2fs  */
  YYSYMBOL_tk_3fs = 37,                    /* tk_3fs  */
  YYSYMBOL_tk_mbr = 38,                    /* tk_mbr  */
  YYSYMBOL_tk_disk = 39,                   /* tk_disk  */
  YYSYMBOL_tk_mkfs = 40,                   /* tk_mkfs  */
  YYSYMBOL_tk_login = 41,                  /* tk_login  */
  YYSYMBOL_tk_logout = 42,                 /* tk_logout  */
  YYSYMBOL_tk_mkgrp = 43,                  /* tk_mkgrp  */
  YYSYMBOL_tk_rmgrp = 44,                  /* tk_rmgrp  */
  YYSYMBOL_tk_mkusr = 45,                  /* tk_mkusr  */
  YYSYMBOL_tk_rmusr = 46,                  /* tk_rmusr  */
  YYSYMBOL_tk_chmod = 47,                  /* tk_chmod  */
  YYSYMBOL_tk_mkfile = 48,                 /* tk_mkfile  */
  YYSYMBOL_tk_cat = 49,                    /* tk_cat  */
  YYSYMBOL_tk_rem = 50,                    /* tk_rem  */
  YYSYMBOL_tk_edit = 51,                   /* tk_edit  */
  YYSYMBOL_tk_ren = 52,                    /* tk_ren  */
  YYSYMBOL_tk_mkdir = 53,                  /* tk_mkdir  */
  YYSYMBOL_tk_cp = 54,                     /* tk_cp  */
  YYSYMBOL_tk_mv = 55,                     /* tk_mv  */
  YYSYMBOL_tk_find = 56,                   /* tk_find  */
  YYSYMBOL_tk_chown = 57,                  /* tk_chown  */
  YYSYMBOL_tk_chgrp = 58,                  /* tk_chgrp  */
  YYSYMBOL_tk_pause = 59,                  /* tk_pause  */
  YYSYMBOL_tk_usr = 60,                    /* tk_usr  */
  YYSYMBOL_tk_pwd = 61,                    /* tk_pwd  */
  YYSYMBOL_tk_grp = 62,                    /* tk_grp  */
  YYSYMBOL_tk_ugo = 63,                    /* tk_ugo  */
  YYSYMBOL_tk_r = 64,                      /* tk_r  */
  YYSYMBOL_tk_p = 65,                      /* tk_p  */
  YYSYMBOL_tk_cont = 66,                   /* tk_cont  */
  YYSYMBOL_tk_pfile = 67,                  /* tk_pfile  */
  YYSYMBOL_tk_dest = 68,                   /* tk_dest  */
  YYSYMBOL_tk_pruta = 69,                  /* tk_pruta  */
  YYSYMBOL_tk_archivo = 70,                /* tk_archivo  */
  YYSYMBOL_tk_inode = 71,                  /* tk_inode  */
  YYSYMBOL_tk_journaling = 72,             /* tk_journaling  */
  YYSYMBOL_tk_block = 73,                  /* tk_block  */
  YYSYMBOL_tk_bm_inode = 74,               /* tk_bm_inode  */
  YYSYMBOL_tk_bm_block = 75,               /* tk_bm_block  */
  YYSYMBOL_tk_tree = 76,                   /* tk_tree  */
  YYSYMBOL_tk_sb = 77,                     /* tk_sb  */
  YYSYMBOL_tk_file = 78,                   /* tk_file  */
  YYSYMBOL_tk_ls = 79,                     /* tk_ls  */
  YYSYMBOL_YYACCEPT = 80,                  /* $accept  */
  YYSYMBOL_I = 81,                         /* I  */
  YYSYMBOL_CONTENIDO = 82,                 /* CONTENIDO  */
  YYSYMBOL_LPCHOWN = 83,                   /* LPCHOWN  */
  YYSYMBOL_PCHOWN = 84,                    /* PCHOWN  */
  YYSYMBOL_TIPO_NAME_REN = 85,             /* TIPO_NAME_REN  */
  YYSYMBOL_TIPO_RUTA = 86,                 /* TIPO_RUTA  */
  YYSYMBOL_LPMKFILE = 87,                  /* LPMKFILE  */
  YYSYMBOL_PMKFILE = 88,                   /* PMKFILE  */
  YYSYMBOL_LPCHMOD = 89,                   /* LPCHMOD  */
  YYSYMBOL_PCHMOD = 90,                    /* PCHMOD  */
  YYSYMBOL_TIPO_GRP = 91,                  /* TIPO_GRP  */
  YYSYMBOL_LPMKUSR = 92,                   /* LPMKUSR  */
  YYSYMBOL_PMKUSR = 93,                    /* PMKUSR  */
  YYSYMBOL_LPLOGIN = 94,                   /* LPLOGIN  */
  YYSYMBOL_PLOGIN = 95,                    /* PLOGIN  */
  YYSYMBOL_TIPO_PWD = 96,                  /* TIPO_PWD  */
  YYSYMBOL_LC_REP = 97,                    /* LC_REP  */
  YYSYMBOL_C_REP = 98,                     /* C_REP  */
  YYSYMBOL_VALOR_NAME = 99,                /* VALOR_NAME  */
  YYSYMBOL_LPARAMETROS = 100,              /* LPARAMETROS  */
  YYSYMBOL_PARAMETROS = 101,               /* PARAMETROS  */
  YYSYMBOL_LOPARAMETROS_FDISK = 102,       /* LOPARAMETROS_FDISK  */
  YYSYMBOL_OPARAMETROS_FDISK = 103,        /* OPARAMETROS_FDISK  */
  YYSYMBOL_VALORES_DELETE = 104,           /* VALORES_DELETE  */
  YYSYMBOL_VALORES_FS = 105,               /* VALORES_FS  */
  YYSYMBOL_TIPO_PARTICION = 106,           /* TIPO_PARTICION  */
  YYSYMBOL_AJUSTE = 107,                   /* AJUSTE  */
  YYSYMBOL_UNIDADES = 108                  /* UNIDADES  */
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
#define YYFINAL  101
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   337

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  143
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  338

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   334


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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   173,   173,   178,   181,   184,   187,   190,   195,   200,
     205,   210,   215,   220,   225,   230,   234,   238,   242,   246,
     251,   255,   260,   265,   269,   274,   281,   286,   290,   293,
     297,   301,   305,   308,   312,   316,   320,   324,   328,   333,
     338,   343,   348,   354,   359,   363,   368,   373,   378,   383,
     388,   393,   397,   402,   409,   413,   419,   420,   421,   425,
     426,   427,   430,   431,   435,   439,   445,   446,   447,   448,
     452,   456,   462,   463,   464,   465,   468,   469,   472,   476,
     482,   483,   484,   486,   490,   496,   497,   498,   499,   500,
     502,   503,   504,   507,   511,   517,   520,   521,   522,   523,
     524,   527,   528,   529,   530,   531,   532,   533,   534,   535,
     536,   537,   541,   545,   551,   554,   557,   558,   559,   562,
     566,   572,   573,   576,   577,   578,   581,   584,   587,   588,
     589,   593,   594,   597,   598,   602,   603,   604,   608,   609,
     610,   613,   614,   615
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
  "\"end of file\"", "error", "\"invalid token\"", "tk_igual",
  "tk_mkdisk", "tk_rmdisk", "tk_fdisk", "tk_mount", "tk_unmount", "tk_rep",
  "tk_exec", "tk_size", "tk_f", "tk_u", "tk_path", "tk_type", "tk_fs",
  "tk_delete", "tk_name", "tk_add", "tk_id", "tk_ruta", "tk_numero",
  "tk_identificador", "tk_cadena", "tk_primaria", "tk_extendida",
  "tk_logica", "tk_byte", "tk_kilo", "tk_mega", "tk_bf", "tk_ff", "tk_wf",
  "tk_fast", "tk_full", "tk_2fs", "tk_3fs", "tk_mbr", "tk_disk", "tk_mkfs",
  "tk_login", "tk_logout", "tk_mkgrp", "tk_rmgrp", "tk_mkusr", "tk_rmusr",
  "tk_chmod", "tk_mkfile", "tk_cat", "tk_rem", "tk_edit", "tk_ren",
  "tk_mkdir", "tk_cp", "tk_mv", "tk_find", "tk_chown", "tk_chgrp",
  "tk_pause", "tk_usr", "tk_pwd", "tk_grp", "tk_ugo", "tk_r", "tk_p",
  "tk_cont", "tk_pfile", "tk_dest", "tk_pruta", "tk_archivo", "tk_inode",
  "tk_journaling", "tk_block", "tk_bm_inode", "tk_bm_block", "tk_tree",
  "tk_sb", "tk_file", "tk_ls", "$accept", "I", "CONTENIDO", "LPCHOWN",
  "PCHOWN", "TIPO_NAME_REN", "TIPO_RUTA", "LPMKFILE", "PMKFILE", "LPCHMOD",
  "PCHMOD", "TIPO_GRP", "LPMKUSR", "PMKUSR", "LPLOGIN", "PLOGIN",
  "TIPO_PWD", "LC_REP", "C_REP", "VALOR_NAME", "LPARAMETROS", "PARAMETROS",
  "LOPARAMETROS_FDISK", "OPARAMETROS_FDISK", "VALORES_DELETE",
  "VALORES_FS", "TIPO_PARTICION", "AJUSTE", "UNIDADES", YY_NULLPTR
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
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334
};
#endif

#define YYPACT_NINF (-156)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      29,   102,    35,    93,    12,    23,    26,    78,     8,    69,
    -156,    76,    91,    85,    63,    27,    34,    61,   146,     0,
      36,     2,    28,    33,    79,    34,   -33,  -156,   173,  -156,
     159,   165,   198,   199,   102,  -156,   200,   201,   202,   203,
     204,   205,   206,   207,   208,    93,  -156,   209,   210,   211,
     212,   213,   214,   215,    26,  -156,   216,   217,   218,   219,
     220,   221,    69,  -156,   222,   223,   224,   225,   226,    85,
    -156,   227,   228,   229,  -156,    27,  -156,   230,   231,  -156,
     232,    34,  -156,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,    39,  -156,   247,
     248,  -156,   249,   120,   126,    96,  -156,    97,   250,   120,
     126,   101,   132,    17,   125,   251,  -156,   103,   156,   158,
     111,   -14,   160,   112,  -156,   113,    17,   162,   164,   166,
     154,  -156,   168,   168,   168,   154,   168,  -156,   168,   117,
     252,  -156,   253,   112,   112,  -156,   112,   112,   112,   154,
     112,    32,   112,   254,   112,   112,   112,   112,   112,    32,
     255,   256,  -156,  -156,   168,   168,  -156,  -156,  -156,  -156,
    -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,
    -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,
    -156,  -156,  -156,  -156,   258,   259,   264,   265,  -156,  -156,
    -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,
    -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,
    -156,   260,   266,   267,  -156,  -156,  -156,  -156,  -156,  -156,
    -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,
    -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,   177,   269,
     268,  -156,  -156,  -156,   270,   187,   112,   185,   271,   188,
     273,   272,   274,   112,   168,   193,   257,   261,   262,   263,
     286,   288,   289,   290,   291,   292,   293,   294,  -156,  -156,
     295,   296,   297,   298,   299,   300,  -156,  -156,   301,   302,
     170,   172,   118,   119,   174,    17,    17,   154,   112,    32,
     112,   112,   112,   112,   112,    32,   112,   168,   168,  -156,
    -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,
     303,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,
    -156,  -156,  -156,   304,   163,  -156,  -156,  -156
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      29,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,     0,     2,
       0,     0,     0,     0,     3,   113,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,   120,     0,     0,     0,
       0,     0,     0,     0,    17,    94,     0,     0,     0,     0,
       0,     0,    28,    84,     0,     0,     0,     0,     0,    32,
      79,     0,     0,     0,    75,    34,    71,     0,     0,    69,
       0,    35,    65,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,    55,     0,
       0,     1,     0,     0,     0,     0,   112,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   119,     0,     0,     0,
       0,     0,     0,     0,    93,     0,     0,     0,     0,     0,
       0,    83,     0,     0,     0,     0,     0,    78,     0,     0,
       0,    70,     0,     0,     0,    64,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    57,    54,     0,     0,   116,   138,   139,   140,
     114,   141,   142,   143,   115,   117,   118,     4,     5,   121,
     126,   122,   123,   124,   135,   136,   137,   125,   131,   132,
     127,   128,   129,   130,     0,     0,     0,     0,    15,    16,
      96,    97,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,    95,    98,    99,    62,    63,   100,    18,
      19,     0,    23,    27,    88,    89,    85,    86,    91,    90,
      92,    87,    76,    77,    30,    31,    80,    81,    82,    33,
      72,    73,    74,    67,    66,    68,    36,    37,     0,     0,
       0,    61,    60,    59,     0,    44,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    42,    43,
       0,     0,     0,     0,     0,     0,    56,    58,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     7,
       8,     9,    10,    11,    13,    12,    14,    22,    26,    21,
      24,    38,    39,    40,    41,    45,    46,    47,    48,    49,
      50,    52,    53,     0,     0,   133,   134,    25
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -156,  -156,  -156,  -156,  -156,  -155,  -137,  -156,   -13,  -156,
     186,  -133,  -156,   191,  -156,   275,  -127,  -156,   276,  -156,
    -156,   277,  -156,   278,  -124,  -156,  -156,   153,   157
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    28,    29,    97,   163,   254,   218,    81,    82,    75,
      76,   234,    69,    70,    62,    63,   231,    54,    55,   213,
      34,    35,    45,    46,   190,   337,   187,   170,   174
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     235,   236,   221,   238,   262,   239,   244,   245,   237,   246,
     247,   248,    98,   250,    85,   255,    89,   257,   258,   259,
     260,   261,   249,    57,   202,   203,    47,    99,    58,   100,
      48,   265,   266,     1,     2,     3,     4,     5,     6,     7,
      50,    72,    91,    49,    51,    77,    52,    93,    78,    36,
      87,   188,   189,   160,    88,   251,   252,   204,   205,   206,
     207,   208,   209,   210,   211,   212,    86,    90,   145,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    59,
      73,    74,    56,    95,    64,    53,    92,    96,    79,   161,
      80,    94,   253,   162,    37,    38,    39,    40,    41,    65,
      42,    43,    44,    30,    31,    32,    33,   175,   177,   279,
     176,   178,   182,    71,   194,   183,   286,   195,    83,    60,
      61,   287,   200,   216,   219,   201,   217,   220,   240,   313,
     315,   241,   314,   316,   323,    66,    67,    68,   191,   192,
     329,   167,   168,   169,   171,   172,   173,   184,   185,   186,
      84,   322,   102,   324,   325,   326,   327,   328,   103,   330,
     321,   319,   320,   101,   331,   332,   228,   229,   230,   196,
     197,   198,   199,   214,   215,   222,   223,   224,   225,   226,
     227,   232,   233,   309,   310,   311,   312,   317,   318,   335,
     336,   104,   105,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   117,   118,   119,   120,   121,   122,   123,   125,
     126,   127,   128,   129,   130,   132,   133,   134,   135,   136,
     138,   139,   140,   142,   143,   144,   146,   147,   148,   149,
     150,   151,   152,   274,   154,   155,   156,   157,   158,   159,
     164,   165,   278,   280,   153,   288,   282,   256,   263,   264,
     137,   141,   180,     0,   290,   291,   292,   181,     0,     0,
       0,   166,   179,   193,   242,   243,   267,   268,   269,   270,
     271,   272,   273,   275,   277,   281,   276,   283,   285,   293,
     284,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,     0,   334,     0,     0,
       0,   106,     0,     0,     0,     0,     0,   289,     0,   333,
       0,     0,     0,   116,     0,     0,     0,     0,     0,     0,
     124,     0,     0,     0,     0,     0,     0,   131
};

static const yytype_int16 yycheck[] =
{
     133,   134,   126,   136,   159,   138,   143,   144,   135,   146,
     147,   148,    25,   150,    14,   152,    14,   154,   155,   156,
     157,   158,   149,    15,    38,    39,    14,    60,    20,    62,
      18,   164,   165,     4,     5,     6,     7,     8,     9,    10,
      14,    14,    14,    20,    18,    11,    20,    14,    14,    14,
      14,    34,    35,    14,    18,    23,    24,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    66,    65,    81,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    20,
      63,    64,    14,    14,    18,    69,    68,    18,    64,    60,
      66,    68,    70,    64,    11,    12,    13,    14,    15,    18,
      17,    18,    19,    11,    12,    13,    14,    21,    21,   256,
      24,    24,    21,    60,    21,    24,   263,    24,    67,    60,
      61,   264,    21,    21,    21,    24,    24,    24,    21,    21,
      21,    24,    24,    24,   299,    60,    61,    62,    23,    24,
     305,    31,    32,    33,    28,    29,    30,    25,    26,    27,
      14,   298,     3,   300,   301,   302,   303,   304,     3,   306,
     297,   295,   296,     0,   307,   308,    22,    23,    24,    23,
      24,    23,    24,    23,    24,    23,    24,    23,    24,    23,
      24,    23,    24,    23,    24,    23,    24,    23,    24,    36,
      37,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,    66,     3,     3,     3,     3,     3,     3,
       3,     3,    65,    68,    14,    62,    68,     3,     3,     3,
      69,    75,   109,    -1,     3,     3,     3,   110,    -1,    -1,
      -1,    22,    22,    22,    22,    22,    18,    18,    14,    14,
      20,    15,    15,    14,    14,    14,    18,    14,    14,     3,
      18,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,    -1,     3,    -1,    -1,
      -1,    34,    -1,    -1,    -1,    -1,    -1,    60,    -1,    16,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    62
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     6,     7,     8,     9,    10,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    81,    82,
      11,    12,    13,    14,   100,   101,    14,    11,    12,    13,
      14,    15,    17,    18,    19,   102,   103,    14,    18,    20,
      14,    18,    20,    69,    97,    98,    14,    15,    20,    20,
      60,    61,    94,    95,    18,    18,    60,    61,    62,    92,
      93,    60,    14,    63,    64,    89,    90,    11,    14,    64,
      66,    87,    88,    67,    14,    14,    66,    14,    18,    14,
      65,    14,    68,    14,    68,    14,    18,    83,    88,    60,
      62,     0,     3,     3,     3,     3,   101,     3,     3,     3,
       3,     3,     3,     3,     3,     3,   103,     3,     3,     3,
       3,     3,     3,     3,    98,     3,     3,     3,     3,     3,
       3,    95,     3,     3,     3,     3,     3,    93,     3,     3,
       3,    90,     3,     3,     3,    88,     3,     3,     3,     3,
       3,     3,     3,    14,     3,     3,     3,     3,     3,     3,
      14,    60,    64,    84,     3,     3,    22,    31,    32,    33,
     107,    28,    29,    30,   108,    21,    24,    21,    24,    22,
     107,   108,    21,    24,    25,    26,    27,   106,    34,    35,
     104,    23,    24,    22,    21,    24,    23,    24,    23,    24,
      21,    24,    38,    39,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    99,    23,    24,    21,    24,    86,    21,
      24,   104,    23,    24,    23,    24,    23,    24,    22,    23,
      24,    96,    23,    24,    91,    91,    91,    96,    91,    91,
      21,    24,    22,    22,    86,    86,    86,    86,    86,    96,
      86,    23,    24,    70,    85,    86,     3,    86,    86,    86,
      86,    86,    85,     3,     3,    91,    91,    18,    18,    14,
      14,    20,    15,    15,    66,    14,    18,    14,    65,    86,
      68,    14,    68,    14,    18,    14,    86,    91,    62,    60,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,    23,
      24,    23,    24,    21,    24,    21,    24,    23,    24,   104,
     104,    96,    86,    85,    86,    86,    86,    86,    86,    85,
      86,    91,    91,    16,     3,    36,    37,   105
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    80,    81,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    83,    83,    84,    84,    84,    85,
      85,    85,    86,    86,    87,    87,    88,    88,    88,    88,
      89,    89,    90,    90,    90,    90,    91,    91,    92,    92,
      93,    93,    93,    94,    94,    95,    95,    95,    95,    95,
      96,    96,    96,    97,    97,    98,    98,    98,    98,    98,
      98,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,   100,   100,   101,   101,   101,   101,   101,   102,
     102,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   104,   104,   105,   105,   106,   106,   106,   107,   107,
     107,   108,   108,   108
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     4,     4,     2,     7,     7,     7,
       7,     7,     7,     7,     7,     4,     4,     2,     4,     4,
       1,     7,     7,     4,     7,    10,     7,     4,     2,     1,
       4,     4,     2,     4,     2,     2,     4,     4,     7,     7,
       7,     7,     5,     5,     4,     7,     7,     7,     7,     7,
       7,     2,     7,     7,     2,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     2,     1,     3,     3,     3,     1,
       2,     1,     3,     3,     3,     1,     1,     1,     2,     1,
       3,     3,     3,     2,     1,     3,     3,     3,     3,     3,
       1,     1,     1,     2,     1,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     3,     3,     3,     3,     3,     2,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1
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
        yyerror (YY_("syntax error: cannot back up")); \
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
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
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
      yychar = yylex ();
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
  case 2: /* I: CONTENIDO  */
#line 173 "sintactico.y"
                 { raiz = (yyval.tipo_nodo); }
#line 1433 "parser.cpp"
    break;

  case 3: /* CONTENIDO: tk_mkdisk LPARAMETROS  */
#line 178 "sintactico.y"
                                  {(yyval.tipo_nodo)= new Nodo_arbol("MKDISK","");
                                   (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
                                  }
#line 1441 "parser.cpp"
    break;

  case 4: /* CONTENIDO: tk_rmdisk tk_path tk_igual tk_ruta  */
#line 181 "sintactico.y"
                                        {(yyval.tipo_nodo)= new Nodo_arbol("RMDISK","");
                                         (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[0].TEXT))));
                                        }
#line 1449 "parser.cpp"
    break;

  case 5: /* CONTENIDO: tk_rmdisk tk_path tk_igual tk_cadena  */
#line 184 "sintactico.y"
                                          {(yyval.tipo_nodo)= new Nodo_arbol("RMDISK","");
                                         (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[0].TEXT))));
                                        }
#line 1457 "parser.cpp"
    break;

  case 6: /* CONTENIDO: tk_fdisk LOPARAMETROS_FDISK  */
#line 187 "sintactico.y"
                                 {(yyval.tipo_nodo)= new Nodo_arbol("FDISK","");
                                  (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
                                 }
#line 1465 "parser.cpp"
    break;

  case 7: /* CONTENIDO: tk_mount tk_path tk_igual tk_ruta tk_name tk_igual tk_identificador  */
#line 190 "sintactico.y"
                                                                         {
        (yyval.tipo_nodo)= new Nodo_arbol("MOUNT","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[-3].TEXT))));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("name",(yyvsp[0].TEXT))));
    }
#line 1475 "parser.cpp"
    break;

  case 8: /* CONTENIDO: tk_mount tk_path tk_igual tk_ruta tk_name tk_igual tk_cadena  */
#line 195 "sintactico.y"
                                                                  {
        (yyval.tipo_nodo)= new Nodo_arbol("MOUNT","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[-3].TEXT))));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("name",(yyvsp[0].TEXT))));
    }
#line 1485 "parser.cpp"
    break;

  case 9: /* CONTENIDO: tk_mount tk_path tk_igual tk_cadena tk_name tk_igual tk_identificador  */
#line 200 "sintactico.y"
                                                                           {
        (yyval.tipo_nodo)= new Nodo_arbol("MOUNT","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[-3].TEXT))));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("name",(yyvsp[0].TEXT))));
    }
#line 1495 "parser.cpp"
    break;

  case 10: /* CONTENIDO: tk_mount tk_path tk_igual tk_cadena tk_name tk_igual tk_cadena  */
#line 205 "sintactico.y"
                                                                    {
        (yyval.tipo_nodo)= new Nodo_arbol("MOUNT","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[-3].TEXT))));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("name",(yyvsp[0].TEXT))));
    }
#line 1505 "parser.cpp"
    break;

  case 11: /* CONTENIDO: tk_mount tk_name tk_igual tk_identificador tk_path tk_igual tk_ruta  */
#line 210 "sintactico.y"
                                                                         {
        (yyval.tipo_nodo)= new Nodo_arbol("MOUNT","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("name",(yyvsp[-3].TEXT))));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[0].TEXT))));
    }
#line 1515 "parser.cpp"
    break;

  case 12: /* CONTENIDO: tk_mount tk_name tk_igual tk_cadena tk_path tk_igual tk_ruta  */
#line 215 "sintactico.y"
                                                                  {
        (yyval.tipo_nodo)= new Nodo_arbol("MOUNT","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("name",(yyvsp[-3].TEXT))));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[0].TEXT))));
    }
#line 1525 "parser.cpp"
    break;

  case 13: /* CONTENIDO: tk_mount tk_name tk_igual tk_identificador tk_path tk_igual tk_cadena  */
#line 220 "sintactico.y"
                                                                           {
        (yyval.tipo_nodo)= new Nodo_arbol("MOUNT","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("name",(yyvsp[-3].TEXT))));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[0].TEXT))));
    }
#line 1535 "parser.cpp"
    break;

  case 14: /* CONTENIDO: tk_mount tk_name tk_igual tk_cadena tk_path tk_igual tk_cadena  */
#line 225 "sintactico.y"
                                                                    {
        (yyval.tipo_nodo)= new Nodo_arbol("MOUNT","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("name",(yyvsp[-3].TEXT))));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[0].TEXT))));
    }
#line 1545 "parser.cpp"
    break;

  case 15: /* CONTENIDO: tk_unmount tk_id tk_igual tk_identificador  */
#line 230 "sintactico.y"
                                                {
        (yyval.tipo_nodo)= new Nodo_arbol("UNMOUNT","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("id",(yyvsp[0].TEXT))));
    }
#line 1554 "parser.cpp"
    break;

  case 16: /* CONTENIDO: tk_unmount tk_id tk_igual tk_cadena  */
#line 234 "sintactico.y"
                                         {
        (yyval.tipo_nodo)= new Nodo_arbol("UNMOUNT","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("id",(yyvsp[0].TEXT))));
    }
#line 1563 "parser.cpp"
    break;

  case 17: /* CONTENIDO: tk_rep LC_REP  */
#line 238 "sintactico.y"
                   {
        (yyval.tipo_nodo)= new Nodo_arbol("REP","");
        (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
    }
#line 1572 "parser.cpp"
    break;

  case 18: /* CONTENIDO: tk_exec tk_path tk_igual tk_ruta  */
#line 242 "sintactico.y"
                                      {
        (yyval.tipo_nodo)= new Nodo_arbol("EXEC","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[0].TEXT))));
    }
#line 1581 "parser.cpp"
    break;

  case 19: /* CONTENIDO: tk_exec tk_path tk_igual tk_cadena  */
#line 246 "sintactico.y"
                                        {
        (yyval.tipo_nodo)= new Nodo_arbol("EXEC","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[0].TEXT))));
    }
#line 1590 "parser.cpp"
    break;

  case 20: /* CONTENIDO: tk_pause  */
#line 251 "sintactico.y"
              {
        (yyval.tipo_nodo)= new Nodo_arbol("PAUSE","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("pause","pause")));
    }
#line 1599 "parser.cpp"
    break;

  case 21: /* CONTENIDO: tk_mkfs tk_id tk_igual tk_identificador tk_type tk_igual VALORES_DELETE  */
#line 255 "sintactico.y"
                                                                             {
        (yyval.tipo_nodo)= new Nodo_arbol("MKFS","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("id",(yyvsp[-3].TEXT))));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("type",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1609 "parser.cpp"
    break;

  case 22: /* CONTENIDO: tk_mkfs tk_type tk_igual VALORES_DELETE tk_id tk_igual tk_identificador  */
#line 260 "sintactico.y"
                                                                             {
        (yyval.tipo_nodo)= new Nodo_arbol("MKFS","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("type",(yyvsp[-3].tipo_nodo)->valor)));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("id",(yyvsp[0].TEXT))));
    }
#line 1619 "parser.cpp"
    break;

  case 23: /* CONTENIDO: tk_mkfs tk_id tk_igual tk_identificador  */
#line 265 "sintactico.y"
                                             {
        (yyval.tipo_nodo)= new Nodo_arbol("MKFS","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("id",(yyvsp[0].TEXT))));
    }
#line 1628 "parser.cpp"
    break;

  case 24: /* CONTENIDO: tk_mkfs tk_id tk_igual tk_cadena tk_type tk_igual VALORES_DELETE  */
#line 269 "sintactico.y"
                                                                      {
        (yyval.tipo_nodo)= new Nodo_arbol("MKFS","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("id",(yyvsp[-3].TEXT))));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("type",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1638 "parser.cpp"
    break;

  case 25: /* CONTENIDO: tk_mkfs tk_id tk_igual tk_cadena tk_type tk_igual VALORES_DELETE tk_fs tk_igual VALORES_FS  */
#line 274 "sintactico.y"
                                                                                                {
        (yyval.tipo_nodo)= new Nodo_arbol("MKFS","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("id",(yyvsp[-6].TEXT))));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("type",(yyvsp[-3].tipo_nodo)->valor)));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("fs",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1649 "parser.cpp"
    break;

  case 26: /* CONTENIDO: tk_mkfs tk_type tk_igual VALORES_DELETE tk_id tk_igual tk_cadena  */
#line 281 "sintactico.y"
                                                                      {
        (yyval.tipo_nodo)= new Nodo_arbol("MKFS","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("type",(yyvsp[-3].tipo_nodo)->valor)));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("id",(yyvsp[0].TEXT))));
    }
#line 1659 "parser.cpp"
    break;

  case 27: /* CONTENIDO: tk_mkfs tk_id tk_igual tk_cadena  */
#line 286 "sintactico.y"
                                      {
        (yyval.tipo_nodo)= new Nodo_arbol("MKFS","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("id",(yyvsp[0].TEXT))));
    }
#line 1668 "parser.cpp"
    break;

  case 28: /* CONTENIDO: tk_login LPLOGIN  */
#line 290 "sintactico.y"
                      {(yyval.tipo_nodo)= new Nodo_arbol("LOGIN","");
                       (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
                      }
#line 1676 "parser.cpp"
    break;

  case 29: /* CONTENIDO: tk_logout  */
#line 293 "sintactico.y"
               {
        (yyval.tipo_nodo)= new Nodo_arbol("LOGOUT","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("logout","logout")));
    }
#line 1685 "parser.cpp"
    break;

  case 30: /* CONTENIDO: tk_mkgrp tk_name tk_igual TIPO_GRP  */
#line 297 "sintactico.y"
                                         {
        (yyval.tipo_nodo)= new Nodo_arbol("MKGRP","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("name",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1694 "parser.cpp"
    break;

  case 31: /* CONTENIDO: tk_rmgrp tk_name tk_igual TIPO_GRP  */
#line 301 "sintactico.y"
                                         {
        (yyval.tipo_nodo)= new Nodo_arbol("RMGRP","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("name",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1703 "parser.cpp"
    break;

  case 32: /* CONTENIDO: tk_mkusr LPMKUSR  */
#line 305 "sintactico.y"
                       {(yyval.tipo_nodo)= new Nodo_arbol("MKUSR","");
        (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
    }
#line 1711 "parser.cpp"
    break;

  case 33: /* CONTENIDO: tk_rmusr tk_usr tk_igual TIPO_GRP  */
#line 308 "sintactico.y"
                                       {
        (yyval.tipo_nodo)= new Nodo_arbol("RMUSR","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("usr",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1720 "parser.cpp"
    break;

  case 34: /* CONTENIDO: tk_chmod LPCHMOD  */
#line 312 "sintactico.y"
                      {
        (yyval.tipo_nodo)= new Nodo_arbol("CHMOD","");
        (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
    }
#line 1729 "parser.cpp"
    break;

  case 35: /* CONTENIDO: tk_mkfile LPMKFILE  */
#line 316 "sintactico.y"
                        {
        (yyval.tipo_nodo)= new Nodo_arbol("MKFILE","");
        (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
    }
#line 1738 "parser.cpp"
    break;

  case 36: /* CONTENIDO: tk_cat tk_pfile tk_igual TIPO_RUTA  */
#line 320 "sintactico.y"
                                        {
        (yyval.tipo_nodo)= new Nodo_arbol("CAT","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("file",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1747 "parser.cpp"
    break;

  case 37: /* CONTENIDO: tk_rem tk_path tk_igual TIPO_RUTA  */
#line 324 "sintactico.y"
                                       {
        (yyval.tipo_nodo)= new Nodo_arbol("REM","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1756 "parser.cpp"
    break;

  case 38: /* CONTENIDO: tk_edit tk_path tk_igual TIPO_RUTA tk_cont tk_igual TIPO_PWD  */
#line 328 "sintactico.y"
                                                                  {
        (yyval.tipo_nodo)= new Nodo_arbol("EDIT","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[-3].tipo_nodo)->valor)));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("cont",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1766 "parser.cpp"
    break;

  case 39: /* CONTENIDO: tk_edit tk_cont tk_igual TIPO_PWD tk_path tk_igual TIPO_RUTA  */
#line 333 "sintactico.y"
                                                                  {
        (yyval.tipo_nodo)= new Nodo_arbol("EDIT","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("cont",(yyvsp[-3].tipo_nodo)->valor)));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1776 "parser.cpp"
    break;

  case 40: /* CONTENIDO: tk_ren tk_path tk_igual TIPO_RUTA tk_name tk_igual TIPO_NAME_REN  */
#line 338 "sintactico.y"
                                                                      {
        (yyval.tipo_nodo)= new Nodo_arbol("REN","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[-3].tipo_nodo)->valor)));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("name",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1786 "parser.cpp"
    break;

  case 41: /* CONTENIDO: tk_ren tk_name tk_igual TIPO_NAME_REN tk_path tk_igual TIPO_RUTA  */
#line 343 "sintactico.y"
                                                                      {
        (yyval.tipo_nodo)= new Nodo_arbol("REN","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("name",(yyvsp[-3].tipo_nodo)->valor)));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1796 "parser.cpp"
    break;

  case 42: /* CONTENIDO: tk_mkdir tk_path tk_igual TIPO_RUTA tk_p  */
#line 348 "sintactico.y"
                                               {
        (yyval.tipo_nodo)= new Nodo_arbol("MKDIR","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[-1].tipo_nodo)->valor)));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("p","p")));
    }
#line 1806 "parser.cpp"
    break;

  case 43: /* CONTENIDO: tk_mkdir tk_p tk_path tk_igual TIPO_RUTA  */
#line 354 "sintactico.y"
                                              {
        (yyval.tipo_nodo)= new Nodo_arbol("MKDIR","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("p","p")));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1816 "parser.cpp"
    break;

  case 44: /* CONTENIDO: tk_mkdir tk_path tk_igual TIPO_RUTA  */
#line 359 "sintactico.y"
                                          {
            (yyval.tipo_nodo)= new Nodo_arbol("MKDIR","");
            (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1825 "parser.cpp"
    break;

  case 45: /* CONTENIDO: tk_cp tk_path tk_igual TIPO_RUTA tk_dest tk_igual TIPO_RUTA  */
#line 363 "sintactico.y"
                                                                 {
        (yyval.tipo_nodo)= new Nodo_arbol("CP","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[-3].tipo_nodo)->valor)));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("dest",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1835 "parser.cpp"
    break;

  case 46: /* CONTENIDO: tk_cp tk_dest tk_igual TIPO_RUTA tk_path tk_igual TIPO_RUTA  */
#line 368 "sintactico.y"
                                                                 {
        (yyval.tipo_nodo)= new Nodo_arbol("CP","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("dest",(yyvsp[-3].tipo_nodo)->valor)));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1845 "parser.cpp"
    break;

  case 47: /* CONTENIDO: tk_mv tk_path tk_igual TIPO_RUTA tk_dest tk_igual TIPO_RUTA  */
#line 373 "sintactico.y"
                                                                 {
        (yyval.tipo_nodo)= new Nodo_arbol("MV","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[-3].tipo_nodo)->valor)));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("dest",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1855 "parser.cpp"
    break;

  case 48: /* CONTENIDO: tk_mv tk_dest tk_igual TIPO_RUTA tk_path tk_igual TIPO_RUTA  */
#line 378 "sintactico.y"
                                                                 {
        (yyval.tipo_nodo)= new Nodo_arbol("MV","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("dest",(yyvsp[-3].tipo_nodo)->valor)));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1865 "parser.cpp"
    break;

  case 49: /* CONTENIDO: tk_find tk_path tk_igual TIPO_RUTA tk_name tk_igual TIPO_NAME_REN  */
#line 383 "sintactico.y"
                                                                       {
        (yyval.tipo_nodo)= new Nodo_arbol("FIND","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[-3].tipo_nodo)->valor)));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("name",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1875 "parser.cpp"
    break;

  case 50: /* CONTENIDO: tk_find tk_name tk_igual TIPO_NAME_REN tk_path tk_igual TIPO_RUTA  */
#line 388 "sintactico.y"
                                                                       {
        (yyval.tipo_nodo)= new Nodo_arbol("FIND","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("name",(yyvsp[-3].tipo_nodo)->valor)));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("path",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1885 "parser.cpp"
    break;

  case 51: /* CONTENIDO: tk_chown LPCHOWN  */
#line 393 "sintactico.y"
                      {
        (yyval.tipo_nodo)= new Nodo_arbol("CHOWN","");
        (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
    }
#line 1894 "parser.cpp"
    break;

  case 52: /* CONTENIDO: tk_chgrp tk_usr tk_igual TIPO_GRP tk_grp tk_igual TIPO_GRP  */
#line 397 "sintactico.y"
                                                                {
        (yyval.tipo_nodo)= new Nodo_arbol("CHGRP","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("usr",(yyvsp[-3].tipo_nodo)->valor)));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("grp",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1904 "parser.cpp"
    break;

  case 53: /* CONTENIDO: tk_chgrp tk_grp tk_igual TIPO_GRP tk_usr tk_igual TIPO_GRP  */
#line 402 "sintactico.y"
                                                                {
        (yyval.tipo_nodo)= new Nodo_arbol("CHGRP","");
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("grp",(yyvsp[-3].tipo_nodo)->valor)));
        (yyval.tipo_nodo)->add(*(new Nodo_arbol("usr",(yyvsp[0].tipo_nodo)->valor)));
    }
#line 1914 "parser.cpp"
    break;

  case 54: /* LPCHOWN: LPCHOWN PCHOWN  */
#line 409 "sintactico.y"
                      {
      (yyval.tipo_nodo)=(yyvsp[-1].tipo_nodo);
      (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
    }
#line 1923 "parser.cpp"
    break;

  case 55: /* LPCHOWN: PMKFILE  */
#line 413 "sintactico.y"
             {
      (yyval.tipo_nodo) = new Nodo_arbol("PARAMETRO","");
      (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
    }
#line 1932 "parser.cpp"
    break;

  case 56: /* PCHOWN: tk_path tk_igual TIPO_RUTA  */
#line 419 "sintactico.y"
                                   {(yyval.tipo_nodo)= new Nodo_arbol("path",(yyvsp[0].tipo_nodo)->valor);}
#line 1938 "parser.cpp"
    break;

  case 57: /* PCHOWN: tk_r  */
#line 420 "sintactico.y"
           {(yyval.tipo_nodo)= new Nodo_arbol("r","r");}
#line 1944 "parser.cpp"
    break;

  case 58: /* PCHOWN: tk_usr tk_igual TIPO_GRP  */
#line 421 "sintactico.y"
                              {(yyval.tipo_nodo)= new Nodo_arbol("usr",(yyvsp[0].tipo_nodo)->valor);}
#line 1950 "parser.cpp"
    break;

  case 59: /* TIPO_NAME_REN: tk_archivo  */
#line 425 "sintactico.y"
                         {(yyval.tipo_nodo)= new Nodo_arbol("tipo",(yyvsp[0].TEXT));}
#line 1956 "parser.cpp"
    break;

  case 60: /* TIPO_NAME_REN: tk_cadena  */
#line 426 "sintactico.y"
               {(yyval.tipo_nodo)= new Nodo_arbol("tipo",(yyvsp[0].TEXT));}
#line 1962 "parser.cpp"
    break;

  case 61: /* TIPO_NAME_REN: tk_identificador  */
#line 427 "sintactico.y"
                       {(yyval.tipo_nodo)= new Nodo_arbol("tipo",(yyvsp[0].TEXT));}
#line 1968 "parser.cpp"
    break;

  case 62: /* TIPO_RUTA: tk_ruta  */
#line 430 "sintactico.y"
                  {(yyval.tipo_nodo)= new Nodo_arbol("tipo",(yyvsp[0].TEXT));}
#line 1974 "parser.cpp"
    break;

  case 63: /* TIPO_RUTA: tk_cadena  */
#line 431 "sintactico.y"
               {(yyval.tipo_nodo)= new Nodo_arbol("tipo",(yyvsp[0].TEXT));}
#line 1980 "parser.cpp"
    break;

  case 64: /* LPMKFILE: LPMKFILE PMKFILE  */
#line 435 "sintactico.y"
                         {
        (yyval.tipo_nodo)=(yyvsp[-1].tipo_nodo);
        (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
    }
#line 1989 "parser.cpp"
    break;

  case 65: /* LPMKFILE: PMKFILE  */
#line 439 "sintactico.y"
             {
        (yyval.tipo_nodo) = new Nodo_arbol("PARAMETRO","");
        (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
    }
#line 1998 "parser.cpp"
    break;

  case 66: /* PMKFILE: tk_path tk_igual TIPO_RUTA  */
#line 445 "sintactico.y"
                                    {(yyval.tipo_nodo)= new Nodo_arbol("path",(yyvsp[0].tipo_nodo)->valor);}
#line 2004 "parser.cpp"
    break;

  case 67: /* PMKFILE: tk_size tk_igual tk_numero  */
#line 446 "sintactico.y"
                                {(yyval.tipo_nodo)= new Nodo_arbol("size",(yyvsp[0].TEXT));}
#line 2010 "parser.cpp"
    break;

  case 68: /* PMKFILE: tk_cont tk_igual TIPO_RUTA  */
#line 447 "sintactico.y"
                                {(yyval.tipo_nodo)= new Nodo_arbol("cont",(yyvsp[0].tipo_nodo)->valor);}
#line 2016 "parser.cpp"
    break;

  case 69: /* PMKFILE: tk_r  */
#line 448 "sintactico.y"
           {(yyval.tipo_nodo)= new Nodo_arbol("r","r");}
#line 2022 "parser.cpp"
    break;

  case 70: /* LPCHMOD: LPCHMOD PCHMOD  */
#line 452 "sintactico.y"
                      {
        (yyval.tipo_nodo)=(yyvsp[-1].tipo_nodo);
        (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
    }
#line 2031 "parser.cpp"
    break;

  case 71: /* LPCHMOD: PCHMOD  */
#line 456 "sintactico.y"
            {
        (yyval.tipo_nodo) = new Nodo_arbol("PARAMETRO","");
        (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
    }
#line 2040 "parser.cpp"
    break;

  case 72: /* PCHMOD: tk_path tk_igual tk_ruta  */
#line 462 "sintactico.y"
                                 {(yyval.tipo_nodo)= new Nodo_arbol("path",(yyvsp[0].TEXT));}
#line 2046 "parser.cpp"
    break;

  case 73: /* PCHMOD: tk_path tk_igual tk_cadena  */
#line 463 "sintactico.y"
                                 {(yyval.tipo_nodo)= new Nodo_arbol("path",(yyvsp[0].TEXT));}
#line 2052 "parser.cpp"
    break;

  case 74: /* PCHMOD: tk_ugo tk_igual tk_numero  */
#line 464 "sintactico.y"
                                {(yyval.tipo_nodo)= new Nodo_arbol("ugo",(yyvsp[0].TEXT));}
#line 2058 "parser.cpp"
    break;

  case 75: /* PCHMOD: tk_r  */
#line 465 "sintactico.y"
           {(yyval.tipo_nodo)= new Nodo_arbol("r","r");}
#line 2064 "parser.cpp"
    break;

  case 76: /* TIPO_GRP: tk_identificador  */
#line 468 "sintactico.y"
                          {(yyval.tipo_nodo)= new Nodo_arbol("tipo",(yyvsp[0].TEXT));}
#line 2070 "parser.cpp"
    break;

  case 77: /* TIPO_GRP: tk_cadena  */
#line 469 "sintactico.y"
               {(yyval.tipo_nodo)= new Nodo_arbol("tipo",(yyvsp[0].TEXT));}
#line 2076 "parser.cpp"
    break;

  case 78: /* LPMKUSR: LPMKUSR PMKUSR  */
#line 472 "sintactico.y"
                       {
        (yyval.tipo_nodo)=(yyvsp[-1].tipo_nodo);
        (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
    }
#line 2085 "parser.cpp"
    break;

  case 79: /* LPMKUSR: PMKUSR  */
#line 476 "sintactico.y"
            {
        (yyval.tipo_nodo) = new Nodo_arbol("PARAMETRO","");
        (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
    }
#line 2094 "parser.cpp"
    break;

  case 80: /* PMKUSR: tk_usr tk_igual TIPO_GRP  */
#line 482 "sintactico.y"
                                 {(yyval.tipo_nodo)= new Nodo_arbol("usr",(yyvsp[0].tipo_nodo)->valor);}
#line 2100 "parser.cpp"
    break;

  case 81: /* PMKUSR: tk_pwd tk_igual TIPO_PWD  */
#line 483 "sintactico.y"
                               {(yyval.tipo_nodo)= new Nodo_arbol("pwd",(yyvsp[0].tipo_nodo)->valor);}
#line 2106 "parser.cpp"
    break;

  case 82: /* PMKUSR: tk_grp tk_igual TIPO_GRP  */
#line 484 "sintactico.y"
                               {(yyval.tipo_nodo)= new Nodo_arbol("grp",(yyvsp[0].tipo_nodo)->valor);}
#line 2112 "parser.cpp"
    break;

  case 83: /* LPLOGIN: LPLOGIN PLOGIN  */
#line 486 "sintactico.y"
                       {
        (yyval.tipo_nodo)=(yyvsp[-1].tipo_nodo);
        (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
    }
#line 2121 "parser.cpp"
    break;

  case 84: /* LPLOGIN: PLOGIN  */
#line 490 "sintactico.y"
            {
        (yyval.tipo_nodo) = new Nodo_arbol("PARAMETRO","");
        (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
    }
#line 2130 "parser.cpp"
    break;

  case 85: /* PLOGIN: tk_usr tk_igual tk_identificador  */
#line 496 "sintactico.y"
                                        {(yyval.tipo_nodo)= new Nodo_arbol("usr",(yyvsp[0].TEXT));}
#line 2136 "parser.cpp"
    break;

  case 86: /* PLOGIN: tk_usr tk_igual tk_cadena  */
#line 497 "sintactico.y"
                               {(yyval.tipo_nodo)= new Nodo_arbol("usr",(yyvsp[0].TEXT));}
#line 2142 "parser.cpp"
    break;

  case 87: /* PLOGIN: tk_pwd tk_igual TIPO_PWD  */
#line 498 "sintactico.y"
                              {(yyval.tipo_nodo)= new Nodo_arbol("pwd",(yyvsp[0].tipo_nodo)->valor);}
#line 2148 "parser.cpp"
    break;

  case 88: /* PLOGIN: tk_id tk_igual tk_identificador  */
#line 499 "sintactico.y"
                                     {(yyval.tipo_nodo)= new Nodo_arbol("id",(yyvsp[0].TEXT));}
#line 2154 "parser.cpp"
    break;

  case 89: /* PLOGIN: tk_id tk_igual tk_cadena  */
#line 500 "sintactico.y"
                              {(yyval.tipo_nodo)= new Nodo_arbol("id",(yyvsp[0].TEXT));}
#line 2160 "parser.cpp"
    break;

  case 90: /* TIPO_PWD: tk_identificador  */
#line 502 "sintactico.y"
                          {(yyval.tipo_nodo)= new Nodo_arbol("tipo",(yyvsp[0].TEXT));}
#line 2166 "parser.cpp"
    break;

  case 91: /* TIPO_PWD: tk_numero  */
#line 503 "sintactico.y"
               {(yyval.tipo_nodo)= new Nodo_arbol("tipo",(yyvsp[0].TEXT));}
#line 2172 "parser.cpp"
    break;

  case 92: /* TIPO_PWD: tk_cadena  */
#line 504 "sintactico.y"
               {(yyval.tipo_nodo)= new Nodo_arbol("tipo",(yyvsp[0].TEXT));}
#line 2178 "parser.cpp"
    break;

  case 93: /* LC_REP: LC_REP C_REP  */
#line 507 "sintactico.y"
                    {
        (yyval.tipo_nodo)=(yyvsp[-1].tipo_nodo);
        (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
       }
#line 2187 "parser.cpp"
    break;

  case 94: /* LC_REP: C_REP  */
#line 511 "sintactico.y"
         {
        (yyval.tipo_nodo) = new Nodo_arbol("PARAMETRO","");
        (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
    }
#line 2196 "parser.cpp"
    break;

  case 95: /* C_REP: tk_name tk_igual VALOR_NAME  */
#line 517 "sintactico.y"
                                  {(yyval.tipo_nodo)= new Nodo_arbol("name","");
                                    (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
                                  }
#line 2204 "parser.cpp"
    break;

  case 96: /* C_REP: tk_path tk_igual tk_ruta  */
#line 520 "sintactico.y"
                            {(yyval.tipo_nodo)= new Nodo_arbol("path",(yyvsp[0].TEXT));}
#line 2210 "parser.cpp"
    break;

  case 97: /* C_REP: tk_path tk_igual tk_cadena  */
#line 521 "sintactico.y"
                              {(yyval.tipo_nodo)= new Nodo_arbol("path",(yyvsp[0].TEXT));}
#line 2216 "parser.cpp"
    break;

  case 98: /* C_REP: tk_id tk_igual tk_identificador  */
#line 522 "sintactico.y"
                                   {(yyval.tipo_nodo)= new Nodo_arbol("id",(yyvsp[0].TEXT));}
#line 2222 "parser.cpp"
    break;

  case 99: /* C_REP: tk_id tk_igual tk_cadena  */
#line 523 "sintactico.y"
                            {(yyval.tipo_nodo)= new Nodo_arbol("id",(yyvsp[0].TEXT));}
#line 2228 "parser.cpp"
    break;

  case 100: /* C_REP: tk_pruta tk_igual TIPO_RUTA  */
#line 524 "sintactico.y"
                               {(yyval.tipo_nodo)= new Nodo_arbol("ruta",(yyvsp[0].tipo_nodo)->valor);}
#line 2234 "parser.cpp"
    break;

  case 101: /* VALOR_NAME: tk_mbr  */
#line 527 "sintactico.y"
                  {(yyval.tipo_nodo)= new Nodo_arbol("tipo","mbr");}
#line 2240 "parser.cpp"
    break;

  case 102: /* VALOR_NAME: tk_disk  */
#line 528 "sintactico.y"
           {(yyval.tipo_nodo)= new Nodo_arbol("tipo","disk");}
#line 2246 "parser.cpp"
    break;

  case 103: /* VALOR_NAME: tk_inode  */
#line 529 "sintactico.y"
              {(yyval.tipo_nodo)= new Nodo_arbol("tipo","inode");}
#line 2252 "parser.cpp"
    break;

  case 104: /* VALOR_NAME: tk_journaling  */
#line 530 "sintactico.y"
                   {(yyval.tipo_nodo)= new Nodo_arbol("tipo","journaling");}
#line 2258 "parser.cpp"
    break;

  case 105: /* VALOR_NAME: tk_block  */
#line 531 "sintactico.y"
              {(yyval.tipo_nodo)= new Nodo_arbol("tipo","block");}
#line 2264 "parser.cpp"
    break;

  case 106: /* VALOR_NAME: tk_bm_inode  */
#line 532 "sintactico.y"
                 {(yyval.tipo_nodo)= new Nodo_arbol("tipo","bm_inode");}
#line 2270 "parser.cpp"
    break;

  case 107: /* VALOR_NAME: tk_bm_block  */
#line 533 "sintactico.y"
                 {(yyval.tipo_nodo)= new Nodo_arbol("tipo","bm_block");}
#line 2276 "parser.cpp"
    break;

  case 108: /* VALOR_NAME: tk_tree  */
#line 534 "sintactico.y"
             {(yyval.tipo_nodo)= new Nodo_arbol("tipo","tree");}
#line 2282 "parser.cpp"
    break;

  case 109: /* VALOR_NAME: tk_sb  */
#line 535 "sintactico.y"
           {(yyval.tipo_nodo)= new Nodo_arbol("tipo","sb");}
#line 2288 "parser.cpp"
    break;

  case 110: /* VALOR_NAME: tk_file  */
#line 536 "sintactico.y"
             {(yyval.tipo_nodo)= new Nodo_arbol("tipo","file");}
#line 2294 "parser.cpp"
    break;

  case 111: /* VALOR_NAME: tk_ls  */
#line 537 "sintactico.y"
           {(yyval.tipo_nodo)= new Nodo_arbol("tipo","ls");}
#line 2300 "parser.cpp"
    break;

  case 112: /* LPARAMETROS: LPARAMETROS PARAMETROS  */
#line 541 "sintactico.y"
                                   {
                                    (yyval.tipo_nodo)=(yyvsp[-1].tipo_nodo);
                                    (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
  }
#line 2309 "parser.cpp"
    break;

  case 113: /* LPARAMETROS: PARAMETROS  */
#line 545 "sintactico.y"
              {
        (yyval.tipo_nodo) = new Nodo_arbol("PARAMETRO","");
        (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
    }
#line 2318 "parser.cpp"
    break;

  case 114: /* PARAMETROS: tk_f tk_igual AJUSTE  */
#line 551 "sintactico.y"
                                {(yyval.tipo_nodo)= new Nodo_arbol("f","");
                                    (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
                                  }
#line 2326 "parser.cpp"
    break;

  case 115: /* PARAMETROS: tk_u tk_igual UNIDADES  */
#line 554 "sintactico.y"
                          {(yyval.tipo_nodo)= new Nodo_arbol("u","");
                              (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
                           }
#line 2334 "parser.cpp"
    break;

  case 116: /* PARAMETROS: tk_size tk_igual tk_numero  */
#line 557 "sintactico.y"
                              {(yyval.tipo_nodo)= new Nodo_arbol("size",(yyvsp[0].TEXT));}
#line 2340 "parser.cpp"
    break;

  case 117: /* PARAMETROS: tk_path tk_igual tk_ruta  */
#line 558 "sintactico.y"
                            {(yyval.tipo_nodo)= new Nodo_arbol("path",(yyvsp[0].TEXT));}
#line 2346 "parser.cpp"
    break;

  case 118: /* PARAMETROS: tk_path tk_igual tk_cadena  */
#line 559 "sintactico.y"
                              {(yyval.tipo_nodo)= new Nodo_arbol("path",(yyvsp[0].TEXT));}
#line 2352 "parser.cpp"
    break;

  case 119: /* LOPARAMETROS_FDISK: LOPARAMETROS_FDISK OPARAMETROS_FDISK  */
#line 562 "sintactico.y"
                                                       {
        (yyval.tipo_nodo)=(yyvsp[-1].tipo_nodo);
        (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
       }
#line 2361 "parser.cpp"
    break;

  case 120: /* LOPARAMETROS_FDISK: OPARAMETROS_FDISK  */
#line 566 "sintactico.y"
                     {
        (yyval.tipo_nodo) = new Nodo_arbol("PARAMETRO","");
        (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
    }
#line 2370 "parser.cpp"
    break;

  case 121: /* OPARAMETROS_FDISK: tk_size tk_igual tk_numero  */
#line 572 "sintactico.y"
                                             {(yyval.tipo_nodo)= new Nodo_arbol("size",(yyvsp[0].TEXT));}
#line 2376 "parser.cpp"
    break;

  case 122: /* OPARAMETROS_FDISK: tk_u tk_igual UNIDADES  */
#line 573 "sintactico.y"
                          {(yyval.tipo_nodo)= new Nodo_arbol("u","");
                                (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
                             }
#line 2384 "parser.cpp"
    break;

  case 123: /* OPARAMETROS_FDISK: tk_path tk_igual tk_ruta  */
#line 576 "sintactico.y"
                            {(yyval.tipo_nodo)= new Nodo_arbol("path",(yyvsp[0].TEXT));}
#line 2390 "parser.cpp"
    break;

  case 124: /* OPARAMETROS_FDISK: tk_path tk_igual tk_cadena  */
#line 577 "sintactico.y"
                              {(yyval.tipo_nodo)= new Nodo_arbol("path",(yyvsp[0].TEXT));}
#line 2396 "parser.cpp"
    break;

  case 125: /* OPARAMETROS_FDISK: tk_type tk_igual TIPO_PARTICION  */
#line 578 "sintactico.y"
                                   {(yyval.tipo_nodo)= new Nodo_arbol("type","");
                                    (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
                                   }
#line 2404 "parser.cpp"
    break;

  case 126: /* OPARAMETROS_FDISK: tk_f tk_igual AJUSTE  */
#line 581 "sintactico.y"
                        {(yyval.tipo_nodo)= new Nodo_arbol("f","");
                            (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
                          }
#line 2412 "parser.cpp"
    break;

  case 127: /* OPARAMETROS_FDISK: tk_delete tk_igual VALORES_DELETE  */
#line 584 "sintactico.y"
                                     {(yyval.tipo_nodo)= new Nodo_arbol("delete","");
                                        (yyval.tipo_nodo)->add(*(yyvsp[0].tipo_nodo));
                                     }
#line 2420 "parser.cpp"
    break;

  case 128: /* OPARAMETROS_FDISK: tk_name tk_igual tk_identificador  */
#line 587 "sintactico.y"
                                     {(yyval.tipo_nodo)= new Nodo_arbol("name",(yyvsp[0].TEXT));}
#line 2426 "parser.cpp"
    break;

  case 129: /* OPARAMETROS_FDISK: tk_name tk_igual tk_cadena  */
#line 588 "sintactico.y"
                              {(yyval.tipo_nodo)= new Nodo_arbol("name",(yyvsp[0].TEXT));}
#line 2432 "parser.cpp"
    break;

  case 130: /* OPARAMETROS_FDISK: tk_add tk_igual tk_numero  */
#line 589 "sintactico.y"
                             {(yyval.tipo_nodo)= new Nodo_arbol("add",(yyvsp[0].TEXT));}
#line 2438 "parser.cpp"
    break;

  case 131: /* VALORES_DELETE: tk_fast  */
#line 593 "sintactico.y"
                       {(yyval.tipo_nodo)= new Nodo_arbol("tipo","fast");}
#line 2444 "parser.cpp"
    break;

  case 132: /* VALORES_DELETE: tk_full  */
#line 594 "sintactico.y"
           {(yyval.tipo_nodo)= new Nodo_arbol("tipo","full");}
#line 2450 "parser.cpp"
    break;

  case 133: /* VALORES_FS: tk_2fs  */
#line 597 "sintactico.y"
                  {(yyval.tipo_nodo)= new Nodo_arbol("tipo","2fs");}
#line 2456 "parser.cpp"
    break;

  case 134: /* VALORES_FS: tk_3fs  */
#line 598 "sintactico.y"
          {(yyval.tipo_nodo)= new Nodo_arbol("tipo","3fs");}
#line 2462 "parser.cpp"
    break;

  case 135: /* TIPO_PARTICION: tk_primaria  */
#line 602 "sintactico.y"
                           {(yyval.tipo_nodo)= new Nodo_arbol("tipo","primaria");}
#line 2468 "parser.cpp"
    break;

  case 136: /* TIPO_PARTICION: tk_extendida  */
#line 603 "sintactico.y"
                {(yyval.tipo_nodo)= new Nodo_arbol("tipo","extendida");}
#line 2474 "parser.cpp"
    break;

  case 137: /* TIPO_PARTICION: tk_logica  */
#line 604 "sintactico.y"
             {(yyval.tipo_nodo)= new Nodo_arbol("tipo","logica");}
#line 2480 "parser.cpp"
    break;

  case 138: /* AJUSTE: tk_bf  */
#line 608 "sintactico.y"
             {(yyval.tipo_nodo)=new Nodo_arbol("ajuste","bf");}
#line 2486 "parser.cpp"
    break;

  case 139: /* AJUSTE: tk_ff  */
#line 609 "sintactico.y"
         {(yyval.tipo_nodo)=new Nodo_arbol("ajuste","ff");}
#line 2492 "parser.cpp"
    break;

  case 140: /* AJUSTE: tk_wf  */
#line 610 "sintactico.y"
         {(yyval.tipo_nodo)=new Nodo_arbol("ajuste","wf");}
#line 2498 "parser.cpp"
    break;

  case 141: /* UNIDADES: tk_byte  */
#line 613 "sintactico.y"
                 {(yyval.tipo_nodo)=new Nodo_arbol("unidad","b");}
#line 2504 "parser.cpp"
    break;

  case 142: /* UNIDADES: tk_kilo  */
#line 614 "sintactico.y"
           {(yyval.tipo_nodo)=new Nodo_arbol("unidad","k");}
#line 2510 "parser.cpp"
    break;

  case 143: /* UNIDADES: tk_mega  */
#line 615 "sintactico.y"
           {(yyval.tipo_nodo)=new Nodo_arbol("unidad","m");}
#line 2516 "parser.cpp"
    break;


#line 2520 "parser.cpp"

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
      yyerror (YY_("syntax error"));
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
                      yytoken, &yylval);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 621 "sintactico.y"

/********************
  Codigo C o C++ Adicional
**********************/
void yyerror(char *s)
{
  printf("\033[31mError sintactico %s",s);
  cout<<" token no reconocido: ";
  cout<<yytext<<" En la Linea: "<<yylineno<<"\033[0m"<<endl;;

  expresion="Error Sintactico";
}
