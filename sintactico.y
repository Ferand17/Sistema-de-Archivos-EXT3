%{

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
 %}


/************************
  Declaraciones de Bison
*************************/

/*  Especifica la coleccion completa de tipos de datos para poder usar
   varios tipos de datos en los terminales y no terminales*/



%union
{

  char TEXT [256];
  class Nodo_arbol *tipo_nodo;

}
/* Indica la produccion con la que inicia nuestra gramatica*/
%start I

/* Especificacion de termines, podemos especificar tambien su tipo  */
%token <TEXT> tk_igual
%token <TEXT> tk_mkdisk
%token <TEXT> tk_rmdisk
%token <TEXT> tk_fdisk
%token <TEXT> tk_mount
%token <TEXT> tk_unmount
%token <TEXT> tk_rep
%token <TEXT> tk_exec


%token <TEXT> tk_size
%token <TEXT> tk_f
%token <TEXT> tk_u
%token <TEXT> tk_path
%token <TEXT> tk_type
%token <TEXT> tk_fs
%token <TEXT> tk_delete
%token <TEXT> tk_name
%token <TEXT> tk_add
%token <TEXT> tk_id

%token <TEXT> tk_ruta
%token <TEXT> tk_numero
%token <TEXT> tk_identificador
%token <TEXT> tk_cadena

%token <TEXT> tk_primaria
%token <TEXT> tk_extendida
%token <TEXT> tk_logica
%token <TEXT> tk_byte
%token <TEXT> tk_kilo
%token <TEXT> tk_mega
%token <TEXT> tk_bf
%token <TEXT> tk_ff
%token <TEXT> tk_wf
%token <TEXT> tk_fast
%token <TEXT> tk_full
    %token <TEXT> tk_2fs
    %token <TEXT> tk_3fs
%token <TEXT> tk_mbr
%token <TEXT> tk_disk

//FASE2 COMANDOS
%token <TEXT> tk_mkfs
%token <TEXT> tk_login
%token <TEXT> tk_logout
%token <TEXT> tk_mkgrp
%token <TEXT> tk_rmgrp
%token <TEXT> tk_mkusr
%token <TEXT> tk_rmusr
%token <TEXT> tk_chmod
%token <TEXT> tk_mkfile
%token <TEXT> tk_cat
%token <TEXT> tk_rem
%token <TEXT> tk_edit
%token <TEXT> tk_ren
%token <TEXT> tk_mkdir
%token <TEXT> tk_cp
%token <TEXT> tk_mv
%token <TEXT> tk_find
%token <TEXT> tk_chown
%token <TEXT> tk_chgrp
%token <TEXT> tk_pause
//FASE2 PARAMETROS
%token <TEXT> tk_usr
%token <TEXT> tk_pwd
%token <TEXT> tk_grp
%token <TEXT> tk_ugo
%token <TEXT> tk_r
%token <TEXT> tk_p
%token <TEXT> tk_cont
%token <TEXT> tk_pfile
%token <TEXT> tk_dest
%token <TEXT> tk_pruta
%token <TEXT> tk_archivo
    //FASE2 PARAMETROS REP
    %token <TEXT> tk_inode
    %token <TEXT> tk_journaling
    %token <TEXT> tk_block
    %token <TEXT> tk_bm_inode
    %token <TEXT> tk_bm_block
    %token <TEXT> tk_tree
    %token <TEXT> tk_sb
    %token <TEXT> tk_file
    %token <TEXT> tk_ls


/* No Terminales, que tambien podemos especificar su tipo */
%type <tipo_nodo> I
//%type <tipo_nodo> LCONTENIDO
%type <tipo_nodo> CONTENIDO
%type <tipo_nodo> LPARAMETROS PARAMETROS LOPARAMETROS_FDISK OPARAMETROS_FDISK
%type <tipo_nodo> TIPO_PARTICION VALOR_NAME AJUSTE UNIDADES
%type <tipo_nodo> VALORES_DELETE
%type <tipo_nodo> VALORES_FS
%type <tipo_nodo> LC_REP C_REP
    //FASE2
    %type <tipo_nodo> LPLOGIN PLOGIN
    %type <tipo_nodo> TIPO_PWD TIPO_GRP
    %type <tipo_nodo> LPMKUSR PMKUSR
    %type <tipo_nodo> LPCHMOD PCHMOD
    %type <tipo_nodo> LPMKFILE PMKFILE TIPO_RUTA TIPO_NAME_REN
    %type <tipo_nodo> LPCHOWN PCHOWN
%%
/**********************
  Reglas Gramaticales
***********************/


I:	CONTENIDO{ raiz = $$; };
/*
LCONTENIDO: LCONTENIDO CONTENIDO{$$=$1}
  | CONTENIDO{};
*/
  CONTENIDO: tk_mkdisk LPARAMETROS{$$= new Nodo_arbol("MKDISK","");
                                   $$->add(*$2);
                                  }
    | tk_rmdisk tk_path tk_igual tk_ruta{$$= new Nodo_arbol("RMDISK","");
                                         $$->add(*(new Nodo_arbol("path",$4)));
                                        }
    | tk_rmdisk tk_path tk_igual tk_cadena{$$= new Nodo_arbol("RMDISK","");
                                         $$->add(*(new Nodo_arbol("path",$4)));
                                        }
    | tk_fdisk LOPARAMETROS_FDISK{$$= new Nodo_arbol("FDISK","");
                                  $$->add(*$2);
                                 }
    | tk_mount tk_path tk_igual tk_ruta tk_name tk_igual tk_identificador{
        $$= new Nodo_arbol("MOUNT","");
        $$->add(*(new Nodo_arbol("path",$4)));
        $$->add(*(new Nodo_arbol("name",$7)));
    }
    | tk_mount tk_path tk_igual tk_ruta tk_name tk_igual tk_cadena{
        $$= new Nodo_arbol("MOUNT","");
        $$->add(*(new Nodo_arbol("path",$4)));
        $$->add(*(new Nodo_arbol("name",$7)));
    }
    | tk_mount tk_path tk_igual tk_cadena tk_name tk_igual tk_identificador{
        $$= new Nodo_arbol("MOUNT","");
        $$->add(*(new Nodo_arbol("path",$4)));
        $$->add(*(new Nodo_arbol("name",$7)));
    }
    | tk_mount tk_path tk_igual tk_cadena tk_name tk_igual tk_cadena{
        $$= new Nodo_arbol("MOUNT","");
        $$->add(*(new Nodo_arbol("path",$4)));
        $$->add(*(new Nodo_arbol("name",$7)));
    }
    | tk_mount tk_name tk_igual tk_identificador tk_path tk_igual tk_ruta{
        $$= new Nodo_arbol("MOUNT","");
        $$->add(*(new Nodo_arbol("name",$4)));
        $$->add(*(new Nodo_arbol("path",$7)));
    }
    | tk_mount tk_name tk_igual tk_cadena tk_path tk_igual tk_ruta{
        $$= new Nodo_arbol("MOUNT","");
        $$->add(*(new Nodo_arbol("name",$4)));
        $$->add(*(new Nodo_arbol("path",$7)));
    }
    | tk_mount tk_name tk_igual tk_identificador tk_path tk_igual tk_cadena{
        $$= new Nodo_arbol("MOUNT","");
        $$->add(*(new Nodo_arbol("name",$4)));
        $$->add(*(new Nodo_arbol("path",$7)));
    }
    | tk_mount tk_name tk_igual tk_cadena tk_path tk_igual tk_cadena{
        $$= new Nodo_arbol("MOUNT","");
        $$->add(*(new Nodo_arbol("name",$4)));
        $$->add(*(new Nodo_arbol("path",$7)));
    }
    | tk_unmount tk_id tk_igual tk_identificador{
        $$= new Nodo_arbol("UNMOUNT","");
        $$->add(*(new Nodo_arbol("id",$4)));
    }
    | tk_unmount tk_id tk_igual tk_cadena{
        $$= new Nodo_arbol("UNMOUNT","");
        $$->add(*(new Nodo_arbol("id",$4)));
    }
    | tk_rep LC_REP{
        $$= new Nodo_arbol("REP","");
        $$->add(*$2);
    }
    | tk_exec tk_path tk_igual tk_ruta{
        $$= new Nodo_arbol("EXEC","");
        $$->add(*(new Nodo_arbol("path",$4)));
    }
    | tk_exec tk_path tk_igual tk_cadena{
        $$= new Nodo_arbol("EXEC","");
        $$->add(*(new Nodo_arbol("path",$4)));
    }
    //COMANDOS SEGUNDA FASE
    | tk_pause{
        $$= new Nodo_arbol("PAUSE","");
        $$->add(*(new Nodo_arbol("pause","pause")));
    }
    | tk_mkfs tk_id tk_igual tk_identificador tk_type tk_igual VALORES_DELETE{
        $$= new Nodo_arbol("MKFS","");
        $$->add(*(new Nodo_arbol("id",$4)));
        $$->add(*(new Nodo_arbol("type",$7->valor)));
    }
    | tk_mkfs tk_type tk_igual VALORES_DELETE tk_id tk_igual tk_identificador{
        $$= new Nodo_arbol("MKFS","");
        $$->add(*(new Nodo_arbol("type",$4->valor)));
        $$->add(*(new Nodo_arbol("id",$7)));
    }
    | tk_mkfs tk_id tk_igual tk_identificador{
        $$= new Nodo_arbol("MKFS","");
        $$->add(*(new Nodo_arbol("id",$4)));
    }
    | tk_mkfs tk_id tk_igual tk_cadena tk_type tk_igual VALORES_DELETE{
        $$= new Nodo_arbol("MKFS","");
        $$->add(*(new Nodo_arbol("id",$4)));
        $$->add(*(new Nodo_arbol("type",$7->valor)));
    }
    | tk_mkfs tk_id tk_igual tk_cadena tk_type tk_igual VALORES_DELETE tk_fs tk_igual VALORES_FS{
        $$= new Nodo_arbol("MKFS","");
        $$->add(*(new Nodo_arbol("id",$4)));
        $$->add(*(new Nodo_arbol("type",$7->valor)));
        $$->add(*(new Nodo_arbol("fs",$10->valor)));
    }

    | tk_mkfs tk_type tk_igual VALORES_DELETE tk_id tk_igual tk_cadena{
        $$= new Nodo_arbol("MKFS","");
        $$->add(*(new Nodo_arbol("type",$4->valor)));
        $$->add(*(new Nodo_arbol("id",$7)));
    }
    | tk_mkfs tk_id tk_igual tk_cadena{
        $$= new Nodo_arbol("MKFS","");
        $$->add(*(new Nodo_arbol("id",$4)));
    }
    | tk_login LPLOGIN{$$= new Nodo_arbol("LOGIN","");
                       $$->add(*$2);
                      }
    | tk_logout{
        $$= new Nodo_arbol("LOGOUT","");
        $$->add(*(new Nodo_arbol("logout","logout")));
    }
    | tk_mkgrp tk_name tk_igual TIPO_GRP {
        $$= new Nodo_arbol("MKGRP","");
        $$->add(*(new Nodo_arbol("name",$4->valor)));
    }
    | tk_rmgrp tk_name tk_igual TIPO_GRP {
        $$= new Nodo_arbol("RMGRP","");
        $$->add(*(new Nodo_arbol("name",$4->valor)));
    }
    | tk_mkusr LPMKUSR {$$= new Nodo_arbol("MKUSR","");
        $$->add(*$2);
    }
    | tk_rmusr tk_usr tk_igual TIPO_GRP{
        $$= new Nodo_arbol("RMUSR","");
        $$->add(*(new Nodo_arbol("usr",$4->valor)));
    }
    | tk_chmod LPCHMOD{
        $$= new Nodo_arbol("CHMOD","");
        $$->add(*$2);
    }
    | tk_mkfile LPMKFILE{
        $$= new Nodo_arbol("MKFILE","");
        $$->add(*$2);
    }
    | tk_cat tk_pfile tk_igual TIPO_RUTA{
        $$= new Nodo_arbol("CAT","");
        $$->add(*(new Nodo_arbol("file",$4->valor)));
    }
    | tk_rem tk_path tk_igual TIPO_RUTA{
        $$= new Nodo_arbol("REM","");
        $$->add(*(new Nodo_arbol("path",$4->valor)));
    }
    | tk_edit tk_path tk_igual TIPO_RUTA tk_cont tk_igual TIPO_PWD{
        $$= new Nodo_arbol("EDIT","");
        $$->add(*(new Nodo_arbol("path",$4->valor)));
        $$->add(*(new Nodo_arbol("cont",$7->valor)));
    }
    | tk_edit tk_cont tk_igual TIPO_PWD tk_path tk_igual TIPO_RUTA{
        $$= new Nodo_arbol("EDIT","");
        $$->add(*(new Nodo_arbol("cont",$4->valor)));
        $$->add(*(new Nodo_arbol("path",$7->valor)));
    }
    | tk_ren tk_path tk_igual TIPO_RUTA tk_name tk_igual TIPO_NAME_REN{
        $$= new Nodo_arbol("REN","");
        $$->add(*(new Nodo_arbol("path",$4->valor)));
        $$->add(*(new Nodo_arbol("name",$7->valor)));
    }
    | tk_ren tk_name tk_igual TIPO_NAME_REN tk_path tk_igual TIPO_RUTA{
        $$= new Nodo_arbol("REN","");
        $$->add(*(new Nodo_arbol("name",$4->valor)));
        $$->add(*(new Nodo_arbol("path",$7->valor)));
    }
    | tk_mkdir tk_path tk_igual TIPO_RUTA tk_p {
        $$= new Nodo_arbol("MKDIR","");
        $$->add(*(new Nodo_arbol("path",$4->valor)));
        $$->add(*(new Nodo_arbol("p","p")));
    }

    | tk_mkdir tk_p tk_path tk_igual TIPO_RUTA{
        $$= new Nodo_arbol("MKDIR","");
        $$->add(*(new Nodo_arbol("p","p")));
        $$->add(*(new Nodo_arbol("path",$5->valor)));
    }
    | tk_mkdir tk_path tk_igual TIPO_RUTA {
            $$= new Nodo_arbol("MKDIR","");
            $$->add(*(new Nodo_arbol("path",$4->valor)));
    }
    | tk_cp tk_path tk_igual TIPO_RUTA tk_dest tk_igual TIPO_RUTA{
        $$= new Nodo_arbol("CP","");
        $$->add(*(new Nodo_arbol("path",$4->valor)));
        $$->add(*(new Nodo_arbol("dest",$7->valor)));
    }
    | tk_cp tk_dest tk_igual TIPO_RUTA tk_path tk_igual TIPO_RUTA{
        $$= new Nodo_arbol("CP","");
        $$->add(*(new Nodo_arbol("dest",$4->valor)));
        $$->add(*(new Nodo_arbol("path",$7->valor)));
    }
    | tk_mv tk_path tk_igual TIPO_RUTA tk_dest tk_igual TIPO_RUTA{
        $$= new Nodo_arbol("MV","");
        $$->add(*(new Nodo_arbol("path",$4->valor)));
        $$->add(*(new Nodo_arbol("dest",$7->valor)));
    }
    | tk_mv tk_dest tk_igual TIPO_RUTA tk_path tk_igual TIPO_RUTA{
        $$= new Nodo_arbol("MV","");
        $$->add(*(new Nodo_arbol("dest",$4->valor)));
        $$->add(*(new Nodo_arbol("path",$7->valor)));
    }
    | tk_find tk_path tk_igual TIPO_RUTA tk_name tk_igual TIPO_NAME_REN{
        $$= new Nodo_arbol("FIND","");
        $$->add(*(new Nodo_arbol("path",$4->valor)));
        $$->add(*(new Nodo_arbol("name",$7->valor)));
    }
    | tk_find tk_name tk_igual TIPO_NAME_REN tk_path tk_igual TIPO_RUTA{
        $$= new Nodo_arbol("FIND","");
        $$->add(*(new Nodo_arbol("name",$4->valor)));
        $$->add(*(new Nodo_arbol("path",$7->valor)));
    }
    | tk_chown LPCHOWN{
        $$= new Nodo_arbol("CHOWN","");
        $$->add(*$2);
    }
    | tk_chgrp tk_usr tk_igual TIPO_GRP tk_grp tk_igual TIPO_GRP{
        $$= new Nodo_arbol("CHGRP","");
        $$->add(*(new Nodo_arbol("usr",$4->valor)));
        $$->add(*(new Nodo_arbol("grp",$7->valor)));
    }
    | tk_chgrp tk_grp tk_igual TIPO_GRP tk_usr tk_igual TIPO_GRP{
        $$= new Nodo_arbol("CHGRP","");
        $$->add(*(new Nodo_arbol("grp",$4->valor)));
        $$->add(*(new Nodo_arbol("usr",$7->valor)));
    }
    ;

LPCHOWN:LPCHOWN PCHOWN{
      $$=$1;
      $$->add(*$2);
    }
    | PMKFILE{
      $$ = new Nodo_arbol("PARAMETRO","");
      $$->add(*$1);
    }
    ;

PCHOWN: tk_path tk_igual TIPO_RUTA {$$= new Nodo_arbol("path",$3->valor);}
    | tk_r {$$= new Nodo_arbol("r","r");}
    | tk_usr tk_igual TIPO_GRP{$$= new Nodo_arbol("usr",$3->valor);}
    ;


TIPO_NAME_REN: tk_archivo{$$= new Nodo_arbol("tipo",$1);}
    | tk_cadena{$$= new Nodo_arbol("tipo",$1);}
    | tk_identificador {$$= new Nodo_arbol("tipo",$1);}
    ;

TIPO_RUTA: tk_ruta{$$= new Nodo_arbol("tipo",$1);}
    | tk_cadena{$$= new Nodo_arbol("tipo",$1);}
    ;


LPMKFILE:LPMKFILE PMKFILE{
        $$=$1;
        $$->add(*$2);
    }
    | PMKFILE{
        $$ = new Nodo_arbol("PARAMETRO","");
        $$->add(*$1);
    }
    ;

PMKFILE: tk_path tk_igual TIPO_RUTA {$$= new Nodo_arbol("path",$3->valor);}
    | tk_size tk_igual tk_numero{$$= new Nodo_arbol("size",$3);}
    | tk_cont tk_igual TIPO_RUTA{$$= new Nodo_arbol("cont",$3->valor);}
    | tk_r {$$= new Nodo_arbol("r","r");}
    ;


LPCHMOD:LPCHMOD PCHMOD{
        $$=$1;
        $$->add(*$2);
    }
    | PCHMOD{
        $$ = new Nodo_arbol("PARAMETRO","");
        $$->add(*$1);
    }
    ;

PCHMOD: tk_path tk_igual tk_ruta {$$= new Nodo_arbol("path",$3);}
    | tk_path tk_igual tk_cadena {$$= new Nodo_arbol("path",$3);}
    | tk_ugo tk_igual tk_numero {$$= new Nodo_arbol("ugo",$3);}
    | tk_r {$$= new Nodo_arbol("r","r");}
    ;

TIPO_GRP: tk_identificador{$$= new Nodo_arbol("tipo",$1);}
    | tk_cadena{$$= new Nodo_arbol("tipo",$1);}
    ;

LPMKUSR: LPMKUSR PMKUSR{
        $$=$1;
        $$->add(*$2);
    }
    | PMKUSR{
        $$ = new Nodo_arbol("PARAMETRO","");
        $$->add(*$1);
    }
    ;

PMKUSR: tk_usr tk_igual TIPO_GRP {$$= new Nodo_arbol("usr",$3->valor);}
    | tk_pwd tk_igual TIPO_PWD {$$= new Nodo_arbol("pwd",$3->valor);}
    | tk_grp tk_igual TIPO_GRP {$$= new Nodo_arbol("grp",$3->valor);}
    ;
LPLOGIN: LPLOGIN PLOGIN{
        $$=$1;
        $$->add(*$2);
    }
    | PLOGIN{
        $$ = new Nodo_arbol("PARAMETRO","");
        $$->add(*$1);
    }
    ;

PLOGIN: tk_usr tk_igual tk_identificador{$$= new Nodo_arbol("usr",$3);}
    | tk_usr tk_igual tk_cadena{$$= new Nodo_arbol("usr",$3);}
    | tk_pwd tk_igual TIPO_PWD{$$= new Nodo_arbol("pwd",$3->valor);}
    | tk_id tk_igual tk_identificador{$$= new Nodo_arbol("id",$3);}
    | tk_id tk_igual tk_cadena{$$= new Nodo_arbol("id",$3);}
    ;
TIPO_PWD: tk_identificador{$$= new Nodo_arbol("tipo",$1);}
    | tk_numero{$$= new Nodo_arbol("tipo",$1);}
    | tk_cadena{$$= new Nodo_arbol("tipo",$1);}
    ;

LC_REP: LC_REP C_REP{
        $$=$1;
        $$->add(*$2);
       }
  | C_REP{
        $$ = new Nodo_arbol("PARAMETRO","");
        $$->add(*$1);
    }
    ;

C_REP: tk_name tk_igual VALOR_NAME{$$= new Nodo_arbol("name","");
                                    $$->add(*$3);
                                  }
  | tk_path tk_igual tk_ruta{$$= new Nodo_arbol("path",$3);}
  | tk_path tk_igual tk_cadena{$$= new Nodo_arbol("path",$3);}
  | tk_id tk_igual tk_identificador{$$= new Nodo_arbol("id",$3);}
  | tk_id tk_igual tk_cadena{$$= new Nodo_arbol("id",$3);}
  | tk_pruta tk_igual TIPO_RUTA{$$= new Nodo_arbol("ruta",$3->valor);}
    ;

VALOR_NAME: tk_mbr{$$= new Nodo_arbol("tipo","mbr");}
  | tk_disk{$$= new Nodo_arbol("tipo","disk");}
    | tk_inode{$$= new Nodo_arbol("tipo","inode");}
    | tk_journaling{$$= new Nodo_arbol("tipo","journaling");}
    | tk_block{$$= new Nodo_arbol("tipo","block");}
    | tk_bm_inode{$$= new Nodo_arbol("tipo","bm_inode");}
    | tk_bm_block{$$= new Nodo_arbol("tipo","bm_block");}
    | tk_tree{$$= new Nodo_arbol("tipo","tree");}
    | tk_sb{$$= new Nodo_arbol("tipo","sb");}
    | tk_file{$$= new Nodo_arbol("tipo","file");}
    | tk_ls{$$= new Nodo_arbol("tipo","ls");}

    ;

LPARAMETROS: LPARAMETROS PARAMETROS{
                                    $$=$1;
                                    $$->add(*$2);
  }
  | PARAMETROS{
        $$ = new Nodo_arbol("PARAMETRO","");
        $$->add(*$1);
    }
  ;

PARAMETROS: tk_f tk_igual AJUSTE{$$= new Nodo_arbol("f","");
                                    $$->add(*$3);
                                  }
  | tk_u tk_igual UNIDADES{$$= new Nodo_arbol("u","");
                              $$->add(*$3);
                           }
  | tk_size tk_igual tk_numero{$$= new Nodo_arbol("size",$3);}
  | tk_path tk_igual tk_ruta{$$= new Nodo_arbol("path",$3);}
  | tk_path tk_igual tk_cadena{$$= new Nodo_arbol("path",$3);}
  ;

LOPARAMETROS_FDISK:LOPARAMETROS_FDISK OPARAMETROS_FDISK{
        $$=$1;
        $$->add(*$2);
       }
  | OPARAMETROS_FDISK{
        $$ = new Nodo_arbol("PARAMETRO","");
        $$->add(*$1);
    }
    ;

OPARAMETROS_FDISK: tk_size tk_igual tk_numero{$$= new Nodo_arbol("size",$3);}
  | tk_u tk_igual UNIDADES{$$= new Nodo_arbol("u","");
                                $$->add(*$3);
                             }
  | tk_path tk_igual tk_ruta{$$= new Nodo_arbol("path",$3);}
  | tk_path tk_igual tk_cadena{$$= new Nodo_arbol("path",$3);}
  | tk_type tk_igual TIPO_PARTICION{$$= new Nodo_arbol("type","");
                                    $$->add(*$3);
                                   }
  | tk_f tk_igual AJUSTE{$$= new Nodo_arbol("f","");
                            $$->add(*$3);
                          }
  | tk_delete tk_igual VALORES_DELETE{$$= new Nodo_arbol("delete","");
                                        $$->add(*$3);
                                     }
  | tk_name tk_igual tk_identificador{$$= new Nodo_arbol("name",$3);}
  | tk_name tk_igual tk_cadena{$$= new Nodo_arbol("name",$3);}
  | tk_add tk_igual tk_numero{$$= new Nodo_arbol("add",$3);}
    ;


VALORES_DELETE: tk_fast{$$= new Nodo_arbol("tipo","fast");}
  | tk_full{$$= new Nodo_arbol("tipo","full");}
    ;

VALORES_FS: tk_2fs{$$= new Nodo_arbol("tipo","2fs");}
  | tk_3fs{$$= new Nodo_arbol("tipo","3fs");}
    ;


TIPO_PARTICION: tk_primaria{$$= new Nodo_arbol("tipo","primaria");}
  | tk_extendida{$$= new Nodo_arbol("tipo","extendida");}
  | tk_logica{$$= new Nodo_arbol("tipo","logica");}
  ;


AJUSTE: tk_bf{$$=new Nodo_arbol("ajuste","bf");}
  | tk_ff{$$=new Nodo_arbol("ajuste","ff");}
  | tk_wf{$$=new Nodo_arbol("ajuste","wf");}
  ;

UNIDADES: tk_byte{$$=new Nodo_arbol("unidad","b");}
  | tk_kilo{$$=new Nodo_arbol("unidad","k");}
  | tk_mega{$$=new Nodo_arbol("unidad","m");}
    ;




%%
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
