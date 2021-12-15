#include "f2_mkusr.h"
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

f2_mkusr::f2_mkusr()
{

}

f2_mkusr::f2_mkusr(Lista_Particiones *lista, int *idUsuario, QString *usuario, QString *id_mount, QString *grupo, int *idGrupo, nodo_particiones *part_global){
    this->lista=lista;
    this->idUsuario=idUsuario;
    this->usuario=usuario;
    this->id_mount=id_mount;
    this->grupo=grupo;
    this->idGrupo=idGrupo;
    this->part_global=part_global;
}

void f2_mkusr::ast_mkusr(Nodo_arbol *raiz){
    string log_error="";
    //VALORES DE CADA PARAMETRO
    bool berror=false;

    bool busr=false;
    bool bpwd=false;
    bool bgrp=false;

    QString vusr="";
    QString vpwd="";
    QString vgrp="";
    for(int c = 0; c < raiz->hijos.count(); c++)
    {
        Nodo_arbol temp = raiz->hijos.at(c);
        if(temp.tipo_==USR){
            busr=true;
            string prueba=temp.valor.toStdString();
            prueba=ReplaceAll(prueba, std::string("\""), std::string(""));
            vusr=QString::fromStdString(prueba);
        }
        else if(temp.tipo_==PWD){
            bpwd=true;
            string prueba=temp.valor.toStdString();
            prueba=ReplaceAll(prueba, std::string("\""), std::string(""));
            vpwd=QString::fromStdString(prueba);
        }
        else if(temp.tipo_==GRP){
            bgrp=true;
            string prueba=temp.valor.toStdString();
            prueba=ReplaceAll(prueba, std::string("\""), std::string(""));
            vgrp=QString::fromStdString(prueba);
        }
    }
    if(!busr){
        berror=true;
        log_error+="Parametro -usr es Obligatorio.\n";
    }
    if(!bpwd){
        berror=true;
        log_error+="Parametro -pwd es Obligatorio.\n";
    }
    if(!bgrp){
        berror=true;
        log_error+="Parametro -grp es Obligatorio.\n";
    }
    if(!berror){
        //cout<<"COMANDO EJECUTADO CORRECTAMENTE."<<endl;
        //cout<<vsize<<" "<<vfit<<" "<<vunit<<" "<<vpath<<endl;
        ejecutar_mkusr(vusr,vpwd,vgrp);


    }else{
        cout<<"\033[31mEL COMANDO CONTIENE ERRORES: "<<endl;
        cout<<log_error<<"\033[0m"<<endl;
    }
}


void f2_mkusr::ejecutar_mkusr(QString pusr, QString ppwd,QString pgrp){
    if(*idUsuario == 1){
                FILE* disco = fopen(part_global->path.toStdString().c_str(), "rb+");
                if (disco != NULL){
                    //Enviar disco, particion,type, fs
                    int inicioByte = 0;
                    if(part_global->part_type == 'P'){
                        inicioByte = part_global->particion.part_start;
                        f2_archivo archivo(disco, part_global, inicioByte);
                        archivo.setUserInformation("root", 1, "root", 1);
                        int resp = archivo.crearUsuario(pusr, ppwd, pgrp);
                        if(resp ==  0 ){cout<<"\033[96mSe creó el usuario correctamente.\033[0m"<<endl<<endl;}
                        else if(resp == 1){cout<<"\033[31mERROR: El nombre del usuario ya existe.\033[0m"<<endl<<endl;}
                        else if(resp == 2){cout<<"\033[31mERROR: El grupo no existe.\033[0m"<<endl<<endl;}
                        else{cout<<"\033[31mERROR: No se pudo crear el Usuario.\033[0m"<<endl<<endl;}

                    }
                    else if(part_global->part_type == 'l'){
                        inicioByte = part_global->particion_logica.part_start + sizeof (EBR);
                        f2_archivo archivo(disco, part_global, inicioByte);
                        archivo.setUserInformation("root", 1, "root", 1);
                        int resp = archivo.crearUsuario(pusr, ppwd, pgrp);
                        if(resp ==  0 ){cout<<"\033[96mSe creó el usuario correctamente.\033[0m"<<endl<<endl;}
                        else if(resp == 1){cout<<"\033[31mERROR: El nombre del usuario ya existe.\033[0m"<<endl<<endl;}
                        else if(resp == 2){cout<<"\033[31mERROR: El grupo no existe.\033[0m"<<endl<<endl;}
                        else{cout<<"\033[31mERROR: No se pudo crear el Usuario.\033[0m"<<endl<<endl;}
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

string f2_mkusr::ReplaceAll(string str, const string& from, const string& to){
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}
