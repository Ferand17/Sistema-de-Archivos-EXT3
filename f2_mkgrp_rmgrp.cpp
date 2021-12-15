#include "f2_mkgrp_rmgrp.h"
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

f2_mkgrp_rmgrp::f2_mkgrp_rmgrp()
{

}

f2_mkgrp_rmgrp::f2_mkgrp_rmgrp(Lista_Particiones *lista, int *idUsuario, QString *usuario, QString *id_mount, QString *grupo, int *idGrupo, nodo_particiones *part_global){
    this->lista=lista;
    this->idUsuario=idUsuario;
    this->usuario=usuario;
    this->id_mount=id_mount;
    this->grupo=grupo;
    this->idGrupo=idGrupo;
    this->part_global=part_global;
}

void f2_mkgrp_rmgrp::ast_mkgrp_rmgrp(Nodo_arbol *raiz, bool ptipo){
    QString vname = ""; //obligatorio
    bool bname=false;
    if(raiz->tipo.toStdString().compare("name")==0){
        bname=true;
        string prueba=raiz->valor.toStdString();
        prueba=ReplaceAll(prueba, string("\""), string(""));
        vname=QString::fromStdString(prueba);
    }

    if(bname){
        ejecutar_mkgrp_rmgrp(vname,ptipo);
    }else{
        cout<<"\033[31mERROR: El Parametro -name es Obligatorio.\033[0m"<<endl;
    }
}
void f2_mkgrp_rmgrp::ejecutar_mkgrp_rmgrp(QString pname, bool ptipo){
    if(ptipo){
        //Ejecutar mkgrp
        if(*idUsuario == 1){
            FILE* disco = fopen(part_global->path.toStdString().c_str(), "rb+");
            if (disco != NULL){
                //Enviar disco, particion,type, fs
                int inicioByte = 0;
                if( part_global->part_type == 'P'){
                    inicioByte = part_global->particion.part_start;
                    f2_archivo archivo(disco, part_global, inicioByte);
                    archivo.setUserInformation("root", 1, "root", 1);
                    int resp = archivo.crearGrupo(pname);
                    if(resp ==  0 ){cout<<"\033[96mSe creó el grupo correctamente.\033[0m"<<endl<<endl;}
                    else if(resp == 1){cout<<"\033[31mERROR: El nombre del grupo ya existe.\033[0m"<<endl<<endl;}
                    else{cout<<"\033[31mERROR: No se pudo crear el grupo.\033[0m"<<endl<<endl;}

                }
                else if(part_global->part_type == 'l'){
                    inicioByte = part_global->particion_logica.part_start + sizeof (EBR);
                    f2_archivo archivo(disco, part_global, inicioByte);
                    archivo.setUserInformation("root", 1, "root", 1);
                    int resp = archivo.crearGrupo(pname);
                    if(resp ==  0 ){ cout<<"\033[96mSe creó el grupo correctamente.\033[0m"<<endl<<endl;}
                    else if(resp == 1){cout<<"\033[31mERROR: El nombre del grupo ya existe.\033[0m"<<endl<<endl;}
                    else{cout<<"\033[31mERROR: No se pudo crear el grupo.\033[0m"<<endl<<endl;}
                }
                else{ cout<<"\033[31mERROR: Partición no existe.\033[0m"<<endl<<endl;  }
                fclose(disco);
            }
            else{ cout<<"\033[31mERROR: Disco no encontrado.\033[0m"<<endl<<endl; }
        }else{
            if(idUsuario > 0){cout<<"\033[31mERROR: Debe de iniciar sesion con el usuario root.\033[0m"<<endl<<endl;}
            else{cout<<"\033[31mERROR: No se ha iniciado sesión.\033[0m"<<endl<<endl;}
        }
    }
    else{

        if(QString::compare(pname, "root",Qt::CaseSensitive)== 0 ){
                cout<<"\033[31mERROR: No se puede eliminar el grupo raiz(root).\033[0m"<<endl<<endl;
                //correcto = false;
        }
        //Ejecutar rmgrp
        //if(idUsuario == 1 && correcto){
        if(*idUsuario == 1){
            FILE* disco = fopen(part_global->path.toStdString().c_str(), "rb+");
            if (disco != NULL){
                //Enviar disco, particion,type, fs
                int inicioByte = 0;
                if(part_global->part_type == 'e' || part_global->part_type == 'P'){
                    inicioByte = part_global->particion.part_start;
                    f2_archivo archivo(disco, part_global, inicioByte);
                    archivo.setUserInformation("root", 1, "root", 1);
                    int resp = archivo.eliminarGrupo(pname);
                    if(resp ==  0 ){cout<<"\033[96mEl grupo se eliminó correctamente.\033[0m"<<endl<<endl;}
                    else if(resp == 1){cout<<"\033[31mERROR: El nombre del grupo no existe.\033[0m"<<endl<<endl;}
                    else{cout<<"\033[31mERROR: No se pudo eliminar el grupo.\033[0m"<<endl<<endl;}
                }
                else if(part_global->part_type == 'l'){
                    inicioByte = part_global->particion.part_start + sizeof (EBR);
                    f2_archivo archivo(disco, part_global, inicioByte);
                    archivo.setUserInformation("root", 1, "root", 1);
                    int resp = archivo.eliminarGrupo(pname);
                    if(resp ==  0 ){cout<<"\033[96mEl grupo se eliminó correctamente.\033[0m"<<endl<<endl;}
                    else if(resp == 1){cout<<"\033[31mERROR: El nombre del grupo no existe.\033[0m"<<endl<<endl;}
                    else{cout<<"\033[31mERROR: No se pudo eliminar el grupo.\033[0m"<<endl<<endl;}
                }
                else{ cout<<"\033[31mERROR: Partición no existe.\033[0m"<<endl<<endl;  }
                fclose(disco);
            }
            else{ cout<<"\033[31mERROR: Disco no encontrado.\033[0m"<<endl<<endl; }
        }else{
            //if(correcto){
                if(*idUsuario > 0){cout<<"\033[31mERROR: Debe de iniciar sesion con el usuario root.\033[0m"<<endl<<endl;}
                else{cout<<"\033[31mERROR: No se ha iniciado sesión.\033[0m"<<endl<<endl;}
            //}
        }
    }
}


string f2_mkgrp_rmgrp::ReplaceAll(string str, const string& from, const string& to){
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}
