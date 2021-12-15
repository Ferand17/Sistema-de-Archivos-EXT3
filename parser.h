/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    tk_igual = 258,                /* tk_igual  */
    tk_mkdisk = 259,               /* tk_mkdisk  */
    tk_rmdisk = 260,               /* tk_rmdisk  */
    tk_fdisk = 261,                /* tk_fdisk  */
    tk_mount = 262,                /* tk_mount  */
    tk_unmount = 263,              /* tk_unmount  */
    tk_rep = 264,                  /* tk_rep  */
    tk_exec = 265,                 /* tk_exec  */
    tk_size = 266,                 /* tk_size  */
    tk_f = 267,                    /* tk_f  */
    tk_u = 268,                    /* tk_u  */
    tk_path = 269,                 /* tk_path  */
    tk_type = 270,                 /* tk_type  */
    tk_fs = 271,                   /* tk_fs  */
    tk_delete = 272,               /* tk_delete  */
    tk_name = 273,                 /* tk_name  */
    tk_add = 274,                  /* tk_add  */
    tk_id = 275,                   /* tk_id  */
    tk_ruta = 276,                 /* tk_ruta  */
    tk_numero = 277,               /* tk_numero  */
    tk_identificador = 278,        /* tk_identificador  */
    tk_cadena = 279,               /* tk_cadena  */
    tk_primaria = 280,             /* tk_primaria  */
    tk_extendida = 281,            /* tk_extendida  */
    tk_logica = 282,               /* tk_logica  */
    tk_byte = 283,                 /* tk_byte  */
    tk_kilo = 284,                 /* tk_kilo  */
    tk_mega = 285,                 /* tk_mega  */
    tk_bf = 286,                   /* tk_bf  */
    tk_ff = 287,                   /* tk_ff  */
    tk_wf = 288,                   /* tk_wf  */
    tk_fast = 289,                 /* tk_fast  */
    tk_full = 290,                 /* tk_full  */
    tk_2fs = 291,                  /* tk_2fs  */
    tk_3fs = 292,                  /* tk_3fs  */
    tk_mbr = 293,                  /* tk_mbr  */
    tk_disk = 294,                 /* tk_disk  */
    tk_mkfs = 295,                 /* tk_mkfs  */
    tk_login = 296,                /* tk_login  */
    tk_logout = 297,               /* tk_logout  */
    tk_mkgrp = 298,                /* tk_mkgrp  */
    tk_rmgrp = 299,                /* tk_rmgrp  */
    tk_mkusr = 300,                /* tk_mkusr  */
    tk_rmusr = 301,                /* tk_rmusr  */
    tk_chmod = 302,                /* tk_chmod  */
    tk_mkfile = 303,               /* tk_mkfile  */
    tk_cat = 304,                  /* tk_cat  */
    tk_rem = 305,                  /* tk_rem  */
    tk_edit = 306,                 /* tk_edit  */
    tk_ren = 307,                  /* tk_ren  */
    tk_mkdir = 308,                /* tk_mkdir  */
    tk_cp = 309,                   /* tk_cp  */
    tk_mv = 310,                   /* tk_mv  */
    tk_find = 311,                 /* tk_find  */
    tk_chown = 312,                /* tk_chown  */
    tk_chgrp = 313,                /* tk_chgrp  */
    tk_pause = 314,                /* tk_pause  */
    tk_usr = 315,                  /* tk_usr  */
    tk_pwd = 316,                  /* tk_pwd  */
    tk_grp = 317,                  /* tk_grp  */
    tk_ugo = 318,                  /* tk_ugo  */
    tk_r = 319,                    /* tk_r  */
    tk_p = 320,                    /* tk_p  */
    tk_cont = 321,                 /* tk_cont  */
    tk_pfile = 322,                /* tk_pfile  */
    tk_dest = 323,                 /* tk_dest  */
    tk_pruta = 324,                /* tk_pruta  */
    tk_archivo = 325,              /* tk_archivo  */
    tk_inode = 326,                /* tk_inode  */
    tk_journaling = 327,           /* tk_journaling  */
    tk_block = 328,                /* tk_block  */
    tk_bm_inode = 329,             /* tk_bm_inode  */
    tk_bm_block = 330,             /* tk_bm_block  */
    tk_tree = 331,                 /* tk_tree  */
    tk_sb = 332,                   /* tk_sb  */
    tk_file = 333,                 /* tk_file  */
    tk_ls = 334                    /* tk_ls  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 54 "sintactico.y"


  char TEXT [256];
  class Nodo_arbol *tipo_nodo;


#line 150 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
