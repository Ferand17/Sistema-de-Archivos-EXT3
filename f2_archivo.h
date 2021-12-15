#ifndef F2_ARCHIVO_H
#define F2_ARCHIVO_H

#include "estructuras_fase2.h"
#include "estructuras.h"
#include  "cmath"
#include <QObject>
#include <stdio.h>
#include <QtCore>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <QObject>
#include "nodo_arbol.h"
#include "estructuras.h"
#include "lista_particiones.h"
#include "nodo_particiones.h"

using namespace std;

class f2_archivo
{
public:

    f2_archivo();
    static const int SIZE_BLOCKS = 64;//bytes
    //datos Usuario
    int usr_id = -1;
    int usr_grp_id = -1;
    QString usr_grp = "";
    QString usr_name = "";

    SuperBlock super;
    Info_journal journal_info;
    Journal journal_last;
    QList<Journal> journaling;
    QByteArray bitmap_inodo;
    QByteArray bitmap_block;
    int inicio_byte;
    QString group;
    int group_id;
    FILE *disco;

    /*BUSCAR*/
    void tm_buscar(QString ppath, QString pname);
    Inodo_dato tm_buscar_inodo(QString name_file_direc, int espacio_apuntador,int nivel);
    void tm_recorre_inodos(QString ppath, QString pname, Inodo actual);

    f2_archivo(FILE*disco, nodo_particiones *particion, int iniciobyte);

    void setUserInformation(QString usr_name, int usr_id, QString usr_grp,int usr_grp_id);
    static void getSuperBlock(FILE*disco, nodo_particiones part_montada, SuperBlock &superBlock);
    void actualizarSuperBloque();
    void actualizarSB();
    void actualizarBitmaps();
    void actualizarJournal();
    void agregarJournal(QString comando, QString nombre, QString contenido, char tipo);
    Journal getJournal(int posicion);
    static Inodo getInodo(FILE *disco, int inode_start, int posicion);
    static void formatearParticion(FILE *disco, Partition particion, string type, string fs);
    static void formatearPar_logica(FILE *disco, EBR particion, string type, string fs);
    static QString getPathString(QStringList path);
    static QString getcontentString(QStringList content);
    void crearCarpeta(QString path, bool p);

    //METODOS ELIMINAR CARPETAS - ARCHIVOS
    void liberarBitmapInodo(int posInodo);
    void liberarBitmapBlock(int posBlock);
    int removeCarpeta_Archivo( Inodo inodo_current, QString name_file_direc);
    int removeCarpeta_Archivo_(QString name_file_direc, int b_apuntador,int nivel_puntero_indirecto);
    int removeInodoChilds(Inodo inodo);
    void removeFileChilds(int espacio, int nivel);
    int removeCarpetaChilds(int espacio, int nivel);
    int rem(QString path);
    int reRem(QString path);

    //METODOS PARA CREAR ARCHIVOS
    Permiso getPermisoInodo(int permiso, char categoria);
    Permiso verificarPermiso(Inodo inodo);
    int createFile(QString path, QStringList contenido, bool p);
    void crearArchivo(QString path, QStringList contenido,bool p);
    int crearArchivo_(Inodo inodo_current, QStringList contenido, QStringList &path, int pos_actual, bool p);
    int escribirArchivo_(int puntero_actual, QString nombre_archivo, QStringList contenido,int nivel_puntero_indirecto);
    int escribirArchivo(QStringList contenido);
    int crearBloquesArchivo(QListIterator<QString> &content, BApuntador& b_apuntador);
    int escribirContenidos(QListIterator<QString> &content, int espacio_actual, int nivel);

    //METODOS BUSCAR INODOS POR PATH
    Inodo_dato searchIndoByName_(QString name_file_direc, int espacio_apuntador,int nivel);
    Inodo_dato getInodoByPath_(Inodo inodo_current, QListIterator<QString> &path);
    Inodo_dato getInodoByPath(QString path);

    //METODOS PARA OBTENER DATOS ARCHIVOS
    QListIterator<QString> getDatosUsers();
    QString getFileContent_(int espacio_apuntador, int nivel);
    QString getFileContent(Inodo inodo);
    static QStringList contentList(QString contenido);

    //METODO INICIAR SESION
    int iniciarSesion(QString user, QString psw);

    //METODO CREAR Y ELIMINAR GRUPOS Y USUARIOS
    void chown(QString path, QString usr_new, bool r);
    int crearGrupo(QString name_grp);
    int cambiarGrupo(QString usr_name, QString grp_name);
    int eliminarGrupo(QString name_grp);
    int crearUsuario(QString usr, QString pwd, QString grp);
    int eliminarUsuario(QString usr);

    //METRODOS MANIPULACION ARCHIVOS Y CARPETAS
    int chmod(QString path, int ugo, bool r);
    void verArchivo(QString path);
    void editArchivo(QString path, QString content);
    void reEditArchivo(QString path, QString content);
    void rename(QString path, QString newName);
    void reRename(QString path, QString newName);

    //METODOS PERDIDA Y RECUPERACION
    void loss();
    void recover();


    //METODOS REPORTES

    // REPORTE INODO
    void reporteInodo(QString save_path);

    // REPORTE JOURNAL
    void reporteJournal(QString save_path);

    // REPORTE BLOQUE
    void reporteBloque(QString save_path);
    void tablaBloqueApuntador(BApuntador apuntador, int no_block, stringstream &data);
    void tablaBloqueCarpeta(BCarpeta carpeta, int no_block, stringstream &data);
    void tablaBloqueArchivo(BArchivo archivo, int no_block, stringstream &data);
    void txtCarpeta(int espacio, stringstream &data, QList<int> &block_list, int nivel);
    void txtFile(int espacio, stringstream &data, QList<int> &block_list, int nivel);

    //REPORTE BITMAPS
    void reporteBtmInodo(QString save_path);
    void reporteBtmBlock(QString save_path);

    // REPORTE ARBOL
    static void reporteArbol(nodo_particiones particion, QString save_path);
    static void generarTxtInodos_(FILE *disco, stringstream &data, stringstream &links, Inodo inodoActual,int no_inodo, SuperBlock super);
    static void generarTxtBloques_(FILE *disco, stringstream &data, stringstream &links, int no_bloque, SuperBlock super, int nivel);
    static void generarTxtBloquesArchivos_(FILE *disco, stringstream &data, stringstream &links, int no_bloque, SuperBlock super, int nivel);

    // REPORTE SUPERBLOQUE
    static void reporteSuperBloque(nodo_particiones particion, QString save_path);

    // REPORTE FILE Y LS
    void reporteFile(QString path, QString ruta);
    QString lsPermisos(Inodo inodo);
    void lsTxtInodo(Inodo inodo, QString name, QString owner, QString grp, stringstream &data);
    void lsCarpetaChilds(int espacio, stringstream &data, QHash<int,QString> usr, QHash<int,QString> grp, int nivel);
    void reporteLs(QString path, QString ruta);



private:
    static int calNoEstructuras(int size_particion, char part_type, string fs);
    static BApuntador getBloqueApuntador(FILE *disco, int block_start, int posicion);
    static BCarpeta getBloqueCarpeta(FILE *disco, int block_start, int posicion);
    static BArchivo getBloqueArchivo(FILE *disco, int block_start, int posicion);
    static void escribirInodo(FILE *disco, Inodo inodo, int inode_start, int posicion);
    static void escribirBloque(FILE *disco, BCarpeta block, int block_start, int posicion);
    static void escribirBloque(FILE *disco, BApuntador block, int block_start, int posicion);
    static void escribirBloque(FILE *disco, BArchivo block, int block_start, int posicion);
    static void crearCarpetaRaiz(FILE *disco, SuperBlock &s_block, int inicio_byte);

    //METODOS PARA CREAR CARPETAS
    void getSuperBlock(nodo_particiones *part_montada);
    void getBitmaps();
    void getJournal();
    int getFreeIndexBitmapInodo();
    int getFreeIndexBitmapBlock();
    static QStringList getPath(QString path);
    int getPositionInodobyName(QString name_file_direc, BApuntador b_apuntador, int nivel_puntero_indirecto);
    int existInodobyName(Inodo inodo_current, QString name_file_direc);
    int crearCarpeta_(Inodo inodo_current, QStringList &path, int pos_actual, bool p);
    int escribirCarpeta_(int puntero_actual, QString nombre_carpeta, int nivel_puntero_indirecto);
    int escribirCarpeta();

};

#endif // F2_ARCHIVO_H
