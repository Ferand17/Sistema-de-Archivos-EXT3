#include "f2_chmod.h"
#include <QObject>
#include <stdio.h>
#include <QtCore>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <string.h>
//#include <QObject>
#include "nodo_arbol.h"
#include "estructuras.h"
#include "lista_particiones.h"
#include "f2_archivo.h"
using namespace std;

f2_chmod::f2_chmod()
{

}
f2_chmod::f2_chmod(Lista_Particiones *lista, int *idUsuario, QString *usuario, QString *id_mount, QString *grupo, int *idGrupo, nodo_particiones *part_global){
    this->lista=lista;
    this->idUsuario=idUsuario;
    this->usuario=usuario;
    this->id_mount=id_mount;
    this->grupo=grupo;
    this->idGrupo=idGrupo;
    this->part_global=part_global;
}
void f2_chmod::ast_chmod(Nodo_arbol *raiz){
    string log_error="";
    //VALORES DE CADA PARAMETRO
    bool berror=false;

    bool bpath=false;
    bool bugo=false;
    //bool br=false;

    QString vpath="";
    QString vugo="";
    bool vr=false;
    for(int c = 0; c < raiz->hijos.count(); c++)
    {
        Nodo_arbol temp = raiz->hijos.at(c);
        if(temp.tipo_==PATH){
            bpath=true;
            string prueba=temp.valor.toStdString();
            prueba=ReplaceAll(prueba, std::string("\""), std::string(""));
            vpath=QString::fromStdString(prueba);
        }
        else if(temp.tipo_==UGO){
            bugo=true;
            vugo=temp.valor;
            if(vugo.count()>3){
                berror=true;
                log_error+="Parametro -ugo su valor solo pueden ser numeros de 3 digitos.\n";
            }
        }
        else if(temp.tipo_==R){
            vr=true;;
        }
    }
    if(!bpath){
        berror=true;
        log_error+="Parametro -path es Obligatorio.\n";
    }
    if(!bugo){
        berror=true;
        log_error+="Parametro -ugo es Obligatorio.\n";
    }

    if(!berror){
        cout<<"llega "<<vpath.toStdString()<<" "<<vugo.toStdString()<<" "<<vr<<endl;
        ejecutar_chmod(vpath,vugo,vr);


    }else{
        cout<<"\033[31mEL COMANDO CONTIENE ERRORES: "<<endl;
        cout<<log_error<<"\033[0m"<<endl;
    }
}


void f2_chmod::ejecutar_chmod(QString ppath, QString pugo,bool pr){
    //cout<<ppath.toStdString()<<" "<<pugo.toStdString()<<" "<<pr.toStdString()<<endl;
    if(idUsuario > 0){
        FILE* disco = fopen(part_global->path.toStdString().c_str(), "rb+");
        if (disco != NULL){
            //Enviar disco, particion,type, fs
            int inicioByte = 0;
            if(part_global->part_type == 'P'){
                inicioByte = part_global->particion.part_start;
                f2_archivo archivo(disco, part_global, inicioByte);

                archivo.setUserInformation(*usuario, *idUsuario, *grupo, *idGrupo);
                //cout<<"paso1"<<endl;
                int resp = archivo.chmod(ppath, pugo.toInt(), pr);
                //cout<<"paso2"<<endl;
                //Imprimir Resultado
                if(resp ==  0 ){cout<<"\033[96mSe cambiaron los permisos correctamente.\033[0m"<<endl<<endl;}
                else if(resp == 1){cout<<"\033[31mERROR: No se encontro el archivo o carpeta.\033[0m"<<endl<<endl;}
                else{cout<<"\033[31mERROR: No se puede cambiar los permisos porque no es propietario del archivo o carpeta.\033[0m"<<endl<<endl;}
            }
            else if(part_global->part_type == 'l'){
                inicioByte = part_global->particion_logica.part_start + sizeof (EBR);
                f2_archivo archivo(disco, part_global, inicioByte);
                archivo.setUserInformation(*usuario, *idUsuario, *grupo, *idGrupo);
                int resp = archivo.chmod(ppath, pugo.toInt(), pr);
                //Imprimir Resultado
                if(resp ==  0 ){cout<<"\033[96mSe cambiaron los permisos correctamente.\033[0m"<<endl<<endl;}
                else if(resp == 1){cout<<"\033[31mERROR: No se encontro el archivo o carpeta.\033[0m"<<endl<<endl;}
                else{cout<<"\033[31mERROR: No se puede cambiar los permisos porque no es propietario del archivo o carpeta.\033[0m"<<endl<<endl;}
            }
            else{ cout<<"\033[31mERROR: Partición no existe.\033[0m"<<endl<<endl;  }
            fclose(disco);
        }
        else{ cout<<"\033[31mERROR: Disco no encontrado.\033[0m"<<endl<<endl; }
    }else{cout<<"\033[31mERROR: No se ha iniciado sesión.\033[0m"<<endl<<endl;}
}

string f2_chmod::ReplaceAll(string str, const string& from, const string& to){
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}


