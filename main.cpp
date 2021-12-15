#include <QCoreApplication>
#include <stdio.h>
#include <QtCore>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <string.h>
//LINEA POR LINEA
#include <sstream>
#include <string>
#include <fstream>
#include <QFileInfo>
#include <QObject>


//COMPILADOR
#include "scanner.h"
#include "parser.h"

#include "estructuras.h"
#include "graficar_ast.h"

#include "lista_particiones.h"

//COMANDO MKDISK
#include "comando_mkdisk.h"
//COMANDO RMDISK
#include "comando_rmdisk.h"
//COMANDO FDISK
#include "comando_fdisk.h"
//COMANDO MOUNT
#include "comando_mount.h"
//COMANDO UMOUNT
#include "comando_unmount.h"
//COMANDO REP
#include "comando_rep.h"
//COMANDO EXEC
#include "comando_exec.h"

//COMANDOS SEGUNDA FASE
#include "f2_mkfs.h"
#include "f2_login.h"
#include "f2_mkgrp_rmgrp.h"
#include "f2_mkusr.h"
#include "f2_rmusr.h"
#include "f2_chmod.h"
#include "f2_mkfile.h"
#include "f2_cat.h"
#include "f2_rem.h"
#include "f2_edit.h"
#include "f2_ren.h"
#include "f2_mkdir.h"
#include "f2_chown.h"
#include "f2_chgrp.h"
#include "f2_find.h"

using namespace std;

/*LOGIN*/
int idUsuario=-1;
QString usuario = "";
QString id_mount = "";
QString grupo = "";
int idGrupo = -1;
nodo_particiones part_global;
int *prueba = new int(2);

/*FIN LOGIN*/



//COMPILADOR
extern int yyparse();
extern FILE *yyin;
extern Nodo_arbol *raiz; // Raiz del arbol
extern int columna;

void obtener_comando(char*);
void recorrer_ast(Nodo_arbol*);
void ast_exec(QList<Nodo_arbol> *hijos);
void ejecutar_exec(QString path);
string ReplaceAll(std::string str, const std::string& from, const std::string& to);
bool existe_archivo(QString path);
void logout();

Lista_Particiones *lista = new Lista_Particiones();


int main()
{
    // Texto del menú que se verá cada vez
    cout<<"Universidad de San Carlos de Guatemala"<<endl;
    cout<<"Facultad de Ingenieria"<<endl;
    cout<<"201700858"<<endl;
    char input[500];
    string input2;
    string output;
    do {
        //system("cls");        // Para limpiar la pantalla


        cout<<"201700858:";
        printf(">> ");
        fgets(input,sizeof (input),stdin);
        input2=input;
        //strtok(input, "\n");
        input2=input2.substr(0, input2.size()-1);
       // cout<<"a"<<(input2.length()==0)<<"a"<<endl;

        if(input2.length()==0){

        }
        else if(input2!="exit"){
            obtener_comando(input);
        }


        cout<<endl;

    } while (input2!="exit");            // En vez de 5 pones el número de la opción de SALIDA




    //yyin=fopen("entrada.txt","rt");
    //if (!yyin)
    //cout<<"error al abrir"<<endl;

    //yyparse();
    //cout<<endl;
    return 0;
}

void obtener_comando(char comando[400]){
    if(comando[0] != '#'){
        YY_BUFFER_STATE buffer = yy_scan_string(comando);
        if(yyparse() == 0){
            if(raiz!=nullptr){
                graficar_ast *g = new graficar_ast(raiz);
                g->generarImagen();
                recorrer_ast(raiz);
            }
        }else{
            cout<<"\033[41mERROR: Comando no Reconocido.\033[0m"<<endl;
        }
    }
}

void recorrer_ast(Nodo_arbol *raiz)
{
    //cout<<raiz->tipo_<<endl;
    switch (raiz->tipo_)
    {
    case MKDISK:
    {
        Nodo_arbol temp = raiz->hijos.at(0);
        comando_mkdisk *mkdisk = new comando_mkdisk();
        mkdisk->ast_mkdisk(&temp);
        break;
    }
    case RMDISK:
    {
        Nodo_arbol temp = raiz->hijos.at(0);
        comando_rmdisk *rmdisk = new comando_rmdisk();
        rmdisk->ast_rmdisk(&temp);
        break;
    }
    case FDISK:
    {
        Nodo_arbol temp = raiz->hijos.at(0);
        comando_fdisk *fdisk = new comando_fdisk();
        fdisk->lista=lista;
        fdisk->ast_fdisk(&temp);
        break;
    }
    case MOUNT:
    {
        QList<Nodo_arbol> temp = raiz->hijos;
        comando_mount *mount = new comando_mount();
        mount->lista=lista;
        mount->ast_mount(&temp);
        lista->mostrarLista();
        break;
    }
    case UNMOUNT:
    {
        Nodo_arbol temp = raiz->hijos.at(0);
        comando_unmount *unmount = new comando_unmount();
        unmount->lista=lista;
        unmount->ast_unmount(&temp);
        lista->mostrarLista();
        break;
    }
    case REP:
    {
        Nodo_arbol temp = raiz->hijos.at(0);
        comando_rep *rep = new comando_rep();
        rep->lista=lista;
        rep->ast_rep(&temp);
        break;
    }
    case EXEC:
    {
        QList<Nodo_arbol> temp = raiz->hijos;
        ast_exec(&temp);
        break;
    }
    case PAUSE:
    {
        char c;
        puts ("\033[96mPresione Una Tecla para Continuar.\033[0m");
        c=getchar();
        break;

    }
    case MKFS:
    {
        QList<Nodo_arbol> temp = raiz->hijos;
        f2_mkfs *mkfs = new f2_mkfs();
        mkfs->lista=lista;
        mkfs->ast_mkfs(&temp);
        break;
    }
        /*COMANDOS 2DA FASE*/
    case LOGIN:
    {
        Nodo_arbol temp = raiz->hijos.at(0);
        f2_login *login = new f2_login(lista, &idUsuario, &usuario, &id_mount, &grupo, &idGrupo, &part_global);
        login->ast_login(&temp);
        break;
    }
    case LOGOUT:
    {
        logout();
        break;
    }
    case MKGRP:
    {
        Nodo_arbol temp = raiz->hijos.at(0);
        f2_mkgrp_rmgrp *mkgrp = new f2_mkgrp_rmgrp(lista, &idUsuario, &usuario, &id_mount, &grupo, &idGrupo, &part_global);
        mkgrp->ast_mkgrp_rmgrp(&temp,true);
        break;
    }
    case RMGRP:
    {
        Nodo_arbol temp = raiz->hijos.at(0);
        f2_mkgrp_rmgrp *mkgrp = new f2_mkgrp_rmgrp(lista, &idUsuario, &usuario, &id_mount, &grupo, &idGrupo, &part_global);
        mkgrp->ast_mkgrp_rmgrp(&temp,false);
        break;
    }
    case MKUSR:
    {
        Nodo_arbol temp = raiz->hijos.at(0);
        f2_mkusr *mkusr = new f2_mkusr(lista, &idUsuario, &usuario, &id_mount, &grupo, &idGrupo, &part_global);
        mkusr->ast_mkusr(&temp);
        break;
    }
    case RMUSR:
    {
        Nodo_arbol temp = raiz->hijos.at(0);
        f2_rmusr *rmusr = new f2_rmusr(lista, &idUsuario, &usuario, &id_mount, &grupo, &idGrupo, &part_global);
        rmusr->ast_rmusr(&temp);
        break;
    }
    case CHMOD:
    {
        Nodo_arbol temp = raiz->hijos.at(0);
        f2_chmod *chmod = new f2_chmod(lista, &idUsuario, &usuario, &id_mount, &grupo, &idGrupo, &part_global);
        chmod->ast_chmod(&temp);
        break;
    }
    case MKFILE:
    {
        Nodo_arbol temp = raiz->hijos.at(0);
        f2_mkfile *mkfile = new f2_mkfile(lista, &idUsuario, &usuario, &id_mount, &grupo, &idGrupo, &part_global);
        mkfile->ast_mkfile(&temp);
        break;
    }
    case CAT:
    {
        Nodo_arbol temp = raiz->hijos.at(0);
        f2_cat *cat = new f2_cat(lista, &idUsuario, &usuario, &id_mount, &grupo, &idGrupo, &part_global);
        cat->ast_cat(&temp);
        break;
    }
    case REM:
    {
        Nodo_arbol temp = raiz->hijos.at(0);
        f2_rem *rem = new f2_rem(lista, &idUsuario, &usuario, &id_mount, &grupo, &idGrupo, &part_global);
        rem->ast_rem(&temp);
        break;
    }
    case EDIT:
    {
        QList<Nodo_arbol> temp = raiz->hijos;
        f2_edit *edit = new f2_edit(lista, &idUsuario, &usuario, &id_mount, &grupo, &idGrupo, &part_global);
        edit->ast_edit(&temp);
        break;
    }
    case REN:
    {
        QList<Nodo_arbol> temp = raiz->hijos;
        f2_ren *ren = new f2_ren(lista, &idUsuario, &usuario, &id_mount, &grupo, &idGrupo, &part_global);
        ren->ast_ren(&temp);
        break;
    }
    case MKDIR:
    {
        QList<Nodo_arbol> temp = raiz->hijos;
        f2_mkdir *mkdir = new f2_mkdir(lista, &idUsuario, &usuario, &id_mount, &grupo, &idGrupo, &part_global);
        mkdir->ast_mkdir(&temp);
        break;
    }
    case CHOWN:
    {
        Nodo_arbol temp = raiz->hijos.at(0);
        f2_chown *chown = new f2_chown(lista, &idUsuario, &usuario, &id_mount, &grupo, &idGrupo, &part_global);
        chown->ast_chown(&temp);
        break;
    }
    case CHGRP:
    {
        QList<Nodo_arbol> temp = raiz->hijos;
        f2_chgrp *chgrp = new f2_chgrp(lista, &idUsuario, &usuario, &id_mount, &grupo, &idGrupo, &part_global);
        chgrp->ast_chgrp(&temp);
        break;
    }
    case FIND:
    {
        QList<Nodo_arbol> temp = raiz->hijos;
        f2_find *find = new f2_find(lista, &idUsuario, &usuario, &id_mount, &grupo, &idGrupo, &part_global);
        find->ast_find(&temp);
        break;
    }
    default:
        cout<<"\033[41mERROR: Comando no Reconocido.\033[0m"<<endl;
        break;
    }

}

void ast_exec(QList<Nodo_arbol> *hijos)
{

    QString vpath="";
    string prueba=hijos->at(0).valor.toStdString();
    prueba=ReplaceAll(prueba, std::string("\""), std::string(""));
    vpath=QString::fromStdString(prueba);
    if(existe_archivo(vpath)){
        ejecutar_exec(vpath);
    }else{
        cout<<"\033[93mALERTA: No existe el archivo.\033[0m"<<endl;
    }

}


void ejecutar_exec(QString path)
{
    ifstream archivo_entrada(path.toStdString());;
    string linea;
    QString aux_linea;
    int contador = 0;
    columna=0;

    while(getline(archivo_entrada, linea))
    {
        contador++;
        if(linea.length()>1){


            aux_linea=QString::fromStdString(linea);
            QByteArray ba = aux_linea.toLocal8Bit();
            char *c_str2 = ba.data();
            if(c_str2[0]=='#'){

            }
            else{
                cout<<"\n-------------------------------------------------------"<<endl;


                cout<<"\033[92mLinea: "+ to_string(contador) + " Comando:\033[0m " + linea<<endl;
                //cout<<linea<<endl;
                obtener_comando(c_str2);
            }
        }

    }
    /*
    ifstream archivo_entrada;
    string linea;

    archivo_entrada.open(path.toStdString());
    getline(archivo_entrada, linea);
    cout << linea << endl;
    getline(archivo_entrada, linea);
    cout << linea << endl;
    */
    /*
    string auxPath = path.toStdString();
    string line;
    FILE *fp;
    if((fp = fopen(auxPath.c_str(),"r"))){
        char line[400]="";
        memset(line,0,sizeof(line));
        int contador=1;
        while(fgets(line,sizeof line,fp)){

            if(line[0]!='\n'){
                cout << line << endl;
                //obtener_comando(line);
            }
            contador++;
            memset(line,0,sizeof(line));
        }
        fclose(fp);
    }else{
        cout << "ERROR: No se Encontro el Archivo de entrada" << endl;
    }
    */

}

string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

bool existe_archivo(QString path){
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}

void logout(){
    if(idUsuario==-1){
        cout<<"\033[93mALERTA: No hay ninguna sesion iniciada.\033[0m"<<endl<<endl;
    }else{
        part_global.path = "";
        idUsuario = -1;
        usuario = "";
        id_mount = "";
        cout<<"\033[96mSe ha terminado la sesion correctamente.\033[0m"<<endl<<endl;
    }

}


