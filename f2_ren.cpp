#include "f2_ren.h"

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


f2_ren::f2_ren()
{

}

f2_ren::f2_ren(Lista_Particiones *lista, int *idUsuario, QString *usuario, QString *id_mount, QString *grupo, int *idGrupo, nodo_particiones *part_global){
    this->lista=lista;
    this->idUsuario=idUsuario;
    this->usuario=usuario;
    this->id_mount=id_mount;
    this->grupo=grupo;
    this->idGrupo=idGrupo;
    this->part_global=part_global;
}

void f2_ren::ast_ren(QList<Nodo_arbol> *hijos){
    string log_error="";
    //VALORES DE CADA PARAMETRO
    bool berror=false;

    bool bpath=false;
    bool bname=false;

    QString vpath="";
    QString vname="";
    for(int c=0;c<hijos->length();c++){
        if(hijos->at(c).tipo.toStdString().compare("path")==0){
            bpath=true;
            string prueba=hijos->at(c).valor.toStdString();
            prueba=ReplaceAll(prueba, std::string("\""), std::string(""));
            vpath=QString::fromStdString(prueba);
        }
        else if(hijos->at(c).tipo.toStdString().compare("name")==0){
            bname=true;
            string prueba=hijos->at(c).valor.toStdString();
            prueba=ReplaceAll(prueba, std::string("\""), std::string(""));
            vname=QString::fromStdString(prueba);
            if(vname.count()>11){
                berror=true;
                log_error+= "El nombre excede el tamaño de 11 caracteres.\n";
            }
        }

    }

    if(!bpath){
        berror=true;
        log_error+="Parametro -path es Obligatorio.\n";
    }
    if(!bname){
        berror=true;
        log_error+="Parametro -name es Obligatorio.\n";
    }

    if(!berror){
        //ejecutar_edit(vpath, vp, vsize, vname);
        ejecutar_ren(vpath, vname);

    }else{
        cout<<"\033[31mEL COMANDO CONTIENE ERRORES: "<<endl;
        cout<<log_error<<"\033[0m"<<endl;
    }

}


void f2_ren::ejecutar_ren(QString ppath, QString pname){
    //cout<<ppath.toStdString()<<" "<<pname.toStdString()<<endl;
    if(*idUsuario > 0){
        FILE* disco = fopen(part_global->path.toStdString().c_str(), "rb+");
        if (disco != NULL){
            //Enviar disco, particion,type, fs
            int inicioByte = 0;
            if(part_global->part_type == 'P'){
                inicioByte = part_global->particion.part_start;
                f2_archivo archivo(disco, part_global, inicioByte);
                archivo.setUserInformation(*usuario, *idUsuario, *grupo, *idGrupo);
                archivo.rename(ppath, pname);
            }
            else if(part_global->part_type == 'l'){
                inicioByte = part_global->particion_logica.part_start + sizeof (EBR);
                f2_archivo archivo(disco, part_global, inicioByte);
                archivo.setUserInformation(*usuario, *idUsuario, *grupo, *idGrupo);
                archivo.rename(ppath, pname);
            }
            else{ cout<<"\033[31mERROR: Partición no existe.\033[0m"<<endl<<endl;  }
            fclose(disco);
        }
        else{ cout<<"\033[31mERROR: Disco no encontrado.\033[0m"<<endl<<endl; }
    }else{ cout<<"\033[31mERROR: No se ha iniciado sesión.\033[0m"<<endl<<endl;}
}

string f2_ren::ReplaceAll(string str, const string& from, const string& to){
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}
