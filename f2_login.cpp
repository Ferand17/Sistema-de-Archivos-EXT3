#include "f2_login.h"

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
#include "f2_archivo.h"
#include "comando_mount.h"
using namespace std;

f2_login::f2_login()
{

}

f2_login::f2_login(Lista_Particiones *lista, int *idUsuario, QString *usuario, QString *id_mount, QString *grupo, int *idGrupo, nodo_particiones *part_global){
    this->lista=lista;
    this->idUsuario=idUsuario;
    this->usuario=usuario;
    this->id_mount=id_mount;
    this->grupo=grupo;
    this->idGrupo=idGrupo;
    this->part_global=part_global;
}

void f2_login::ast_login(Nodo_arbol *raiz){
    string log_error;
    //VALORES DE CADA PARAMETRO
    bool berror=false;

    bool busr=false;
    bool bpwd=false;
    bool bid=false;

    QString vusr="bf";
    QString vpwd="m";
    QString vid="";
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
        else if(temp.tipo_==ID){
            bid=true;
            string prueba=temp.valor.toStdString();
            prueba=ReplaceAll(prueba, std::string("\""), std::string(""));
            vid=QString::fromStdString(prueba);
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
    if(!bid){
        berror=true;
        log_error+="Parametro -id es Obligatorio.\n";
    }
    if(!berror){
        ejecutar_login(vusr,vpwd,vid);

        //cout<<vusr.toStdString()<<" "<<vpwd.toStdString()<<" "<<vid.toStdString()<<endl;
    }else{
        cout<<"\033[31mEL COMANDO CONTIENE ERRORES: "<<endl;
        cout<<log_error<<"\033[0m"<<endl;
    }
}
void f2_login::ejecutar_login(QString usr, QString pwd, QString id){
    if(*idUsuario == -1){
        nodo_particiones encontrado = lista->getParticionMontada(id);
        if(encontrado.path.size() > 0){
            *part_global = encontrado;
            FILE* disco = fopen(part_global->path.toStdString().c_str(), "rb+");
            if (disco != NULL){
                //Enviar disco, particion,type, fs
                int inicioByte = 0;
                if( part_global->part_type == 'P'){
                    inicioByte = part_global->particion.part_start;
                    f2_archivo archivo(disco, part_global, inicioByte);
                    int id_user = archivo.iniciarSesion(usr, pwd);
                    if(id_user > 0 ){

                        *this->idUsuario = id_user;
                        *this->usuario = usr;
                        *this->id_mount = id.toStdString().c_str();
                        *this->grupo = archivo.group;
                        *this->idGrupo = archivo.group_id;
                        cout<<"\033[96mSe ha iniciado sesion con el Usuario: "<<this->usuario->toStdString()<<" Id: "<<*idUsuario<<" Id_Grupo: "<< *idGrupo<<"\033[0m"<<endl<<endl;
                    }
                    else{part_global->path = "";cout<<"\033[31mERROR: User o password no existen.\033[0m"<<endl<<endl;}
                }
                else if(part_global->part_type == 'l'){
                    inicioByte = part_global->particion_logica.part_start + sizeof (EBR);
                    f2_archivo archivo(disco, part_global, inicioByte);
                    int id_user = archivo.iniciarSesion(usr, pwd);
                    if(id_user > 0 ){
                        *this->idUsuario = id_user;
                        *this->usuario = usr;
                        *this->id_mount = id.toStdString().c_str();
                        *this->grupo = archivo.group;
                        *this->idGrupo = archivo.group_id;
                        cout<<"\033[96mSe ha iniciado sesion con el Usuario: "<<(*this->usuario).toStdString()<<" Id: "<<*idUsuario<<" Id_Grupo: "<< *idGrupo<<"\033[0m"<<endl<<endl;
                    }
                    else{part_global->path = "";cout<<"\033[31mERROR: User o password no existen.\033[0m"<<endl<<endl;}
                }
                else{ cout<<"\033[31mERROR: Partición no existe.\033[0m"<<endl<<endl;  }
                fclose(disco);
            }
            else{ cout<<"\033[31mERROR: Disco no encontrado.\033[0m"<<endl<<endl; }
        }else{ cout<<"\033[31mERROR: El id ingresado no existe.\033[0m"<<endl<<endl;}
    }
    else{
        cout<<"\033[31mERROR: Ya hay una sesión iniciada, para iniciar otra, cierre esta sesión con el comando logout.\033[0m"<<endl<<endl;
    }

}

string f2_login::ReplaceAll(string str, const string& from, const string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}
