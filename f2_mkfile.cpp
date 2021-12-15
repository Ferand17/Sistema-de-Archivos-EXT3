#include "f2_mkfile.h"
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

f2_mkfile::f2_mkfile()
{

}
f2_mkfile::f2_mkfile(Lista_Particiones *lista, int *idUsuario, QString *usuario, QString *id_mount, QString *grupo, int *idGrupo, nodo_particiones *part_global){
    this->lista=lista;
    this->idUsuario=idUsuario;
    this->usuario=usuario;
    this->id_mount=id_mount;
    this->grupo=grupo;
    this->idGrupo=idGrupo;
    this->part_global=part_global;
}

void f2_mkfile::ast_mkfile(Nodo_arbol *raiz){
    string log_error="";
    //VALORES DE CADA PARAMETRO
    bool berror=false;

    bool bpath=false;
    //bool bcont=true;


    QString vpath="";
    QString vsize="";
    QString vcont="null";
    bool vp=false;
    for(int c = 0; c < raiz->hijos.count(); c++)
    {
        Nodo_arbol temp = raiz->hijos.at(c);
        if(temp.tipo_==PATH){
            bpath=true;
            string prueba=temp.valor.toStdString();
            prueba=ReplaceAll(prueba, std::string("\""), std::string(""));
            vpath=QString::fromStdString(prueba);
        }
        else if(temp.tipo_==R){
            vp=true;
        }
        else if(temp.tipo_==SIZE){
            vsize=temp.valor;
            if(vsize.toUInt()>=0){
            }else{
                berror=true;
                log_error+="Parametro -size su valor solo puede ser >= 0.\n";
            }
        }
        else if(temp.tipo_==CONT){
            string prueba=temp.valor.toStdString();
            prueba=ReplaceAll(prueba, std::string("\""), std::string(""));
            vcont=QString::fromStdString(prueba);
            vsize="";
        }
    }
    if(!bpath){
        berror=true;
        log_error+="Parametro -path es Obligatorio.\n";
    }

    if(!berror){
        ejecutar_mkfile(vpath, vp, vsize, vcont);


    }else{
        cout<<"\033[31mEL COMANDO CONTIENE ERRORES: "<<endl;
        cout<<log_error<<"\033[0m"<<endl;
    }
}


void f2_mkfile::ejecutar_mkfile(QString ppath, bool pp, QString psize, QString pcont){
    //cout<<ppath.toStdString()<<" "<<pp<<" "<<psize.toStdString()<<" "<<pcont.toStdString();
    if(idUsuario > 0){
        FILE* disco = fopen(part_global->path.toStdString().c_str(), "rb+");
        if (disco != NULL){
            //Enviar disco, particion,type, fs
            int inicioByte = 0;
            if(part_global->part_type == 'P'){
                inicioByte = part_global->particion.part_start;
                f2_archivo archivo(disco, part_global, inicioByte);
                archivo.setUserInformation(*usuario, *idUsuario, *grupo, *idGrupo);
                QStringList contenido = getContent(psize, pcont);
                if(contenido.size() >= 0){
                    archivo.crearArchivo(ppath, contenido, pp);
                }
            }
            else if(part_global->part_type == 'l'){
                inicioByte = part_global->particion_logica.part_start + sizeof (EBR);
                f2_archivo archivo(disco, part_global, inicioByte);
                archivo.setUserInformation(*usuario, *idUsuario, *grupo, *idGrupo);
                QStringList contenido = getContent(psize, pcont);
                if(contenido.size() >= 0){
                    archivo.crearArchivo(ppath, contenido, pp);
                }
            }
            else{ cout<<"\033[31mERROR: Partición no existe.\033[0m"<<endl<<endl;  }
            fclose(disco);
        }
        else{ cout<<"\033[31mERROR: Disco no encontrado.\033[0m"<<endl<<endl; }
    }else{ cout<<"\033[31mERROR: No se ha iniciado sesión.\033[0m"<<endl<<endl;}
}

QStringList f2_mkfile::getContent(QString size, QString cont){
    QStringList lista;
    QString data;
    int size_int = size.toInt();
    if(cont.compare("null",Qt::CaseInsensitive) == 0){
        if(size.size() == 0){
            lista.append("");
            return lista;
        }

        int cont = 0;
        int cant_info = 1;
        for(int i = 0; i < size_int ; i++){
            if(cont == 10){ cont = 0;}
            data += QString::number(cont);
            if(cant_info == 64){
                lista.append(data);
                cant_info = 0;
                data = "";
            }
            cant_info++;
            cont++;
        }
        if(data.size()>0){
            lista.append(data);
        }
        return lista;
    }else{
        FILE *archivo;
        char caracteres[65];
        archivo = fopen(cont.toStdString().c_str(),"r");
        if (archivo == NULL)
            cout<<"\033[31mERROR: No se encontró el archivo con la ruta ingresada en -cont.\033[0m"<<endl<<endl;
        else{
            while (!feof(archivo)){
                memset(caracteres,'\0', 65);
                fread(&caracteres , 1, 64, archivo);
                lista.append(caracteres);
            }
            fclose(archivo);
        }

    }
    return lista;
}



string f2_mkfile::ReplaceAll(string str, const string& from, const string& to){
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}
