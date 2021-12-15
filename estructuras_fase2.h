#ifndef ESTRUCTURAS_FASE2_H
#define ESTRUCTURAS_FASE2_H
#include <sys/stat.h>//obtiene la fecha del sistema
#include <QString>
#include <QObject>
#include <string>

using namespace std;

//Super bloque
typedef struct{
    int s_filesystem_type;
    int s_inodes_count;
    int s_blocks_count;
    int s_free_blocks_count;
    int s_free_inodes_count;
    time_t s_mtime;
    time_t s_umtime;
    int s_mnt_count;
    int s_magic;
    int s_inode_size;
    int s_block_size;
    int s_firts_ino;
    int s_first_blo;
    int s_bm_inode_start;
    int s_bm_block_start;
    int s_inode_start;
    int s_block_start;
}SuperBlock;

//Tabla de inodos
typedef struct{
    int i_uid;
    int i_gid;
    int i_size;
    time_t i_atime;
    time_t i_ctime;
    time_t i_mtime;
    int i_block; //este i_block debe llegar a 15
    char i_type;
    int i_perm;
}Inodo;

//Bloques Carpetas
typedef struct{
    // 12+4 = 16
    char b_name [12];
    int b_inodo;
}BContent;

typedef struct{ // 4*16= 64 --Bloque
    BContent b_content [4];
}BCarpeta;

//Bloques Archivos = 64 --Bloque
typedef struct{
    char b_content[64];
}BArchivo;

//Bloques Apuntadores 16*4 --Bloque
typedef struct{
    int b_pointers[16];  //16
}BApuntador;


//Tabla Journal
typedef struct{
    char operacion[16];//comando que se ejecutó
    int next;
    char usuario[16];
    char tipo;//Carpeta o archivo
    char nombre[150]; //nombre del archivo o carpeta
    char content[230];
    //char date[16];
    time_t date;
    //time_t date;
}Journal;

typedef struct{
    int last;//ultimo Journal
    int max;//Maximo Journals
}Info_journal;

//Datos Inodo
typedef struct{
    int bloque_padre;//No Bloque carpeta que contiene el inodo
    int posicion;//Posicion Inodo en bloque
    int inodo;//No Inodo
}Inodo_dato;

//Permisos
typedef struct{
    short lectura;
    short escritura;
    short ejecucion;
}Permiso;


#endif // ESTRUCTURAS_FASE2_H
