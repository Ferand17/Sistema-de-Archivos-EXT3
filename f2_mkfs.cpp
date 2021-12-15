#include "f2_mkfs.h"
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

using namespace std;
f2_mkfs::f2_mkfs()
{

}

void f2_mkfs::ast_mkfs(QList<Nodo_arbol> *hijos)
{
    QString vid = ""; //obligatorio
    QString vtype = "full";
    QString vfs = "3fs";
    string prueba="";
    bool bid=false;

    for(int c=0;c<hijos->length();c++){
        if(hijos->at(c).tipo.toStdString().compare("id")==0){
            bid=true;
            prueba=hijos->at(c).valor.toStdString();
            prueba=ReplaceAll(prueba, std::string("\""), std::string(""));
            vid=QString::fromStdString(prueba);
        }
        else if(hijos->at(c).tipo.toStdString().compare("type")==0){
            vtype=hijos->at(c).valor;
        }else if(hijos->at(c).tipo.toStdString().compare("fs")==0){
           // vfs=hijos->at(c).valor;
        cout<<"id "<<vid.toStdString()<<" type "<<vtype.toStdString()<<" fs "<<vfs.toStdString()<<endl;
        }
    }


    if(bid){
        ejecutar_mkfs(vid,vtype, vfs);
        //cout<<"id "<<vid.toStdString()<<" type "<<vtype.toStdString()<<endl;
    }else{
        cout<<"\033[31mERROR: El Parametro -id es Obligatorio.\033[0m"<<endl;
    }

}
void f2_mkfs::ejecutar_mkfs(QString id, QString type, QString fs){
    nodo_particiones encontrado= lista->getParticionMontada(id);
    if(encontrado.path.size()>0){
        FILE* discoArchivo = fopen(encontrado.path.toStdString().c_str(), "rb+");
        if (discoArchivo != NULL){
            if(encontrado.part_type == 'P'){
                    f2_archivo::formatearParticion(discoArchivo, encontrado.particion, type.toStdString(), fs.toStdString());

                    int inicioByte = encontrado.particion.part_start;
                    f2_archivo archivo(discoArchivo, &encontrado, inicioByte);
                    archivo.setUserInformation("root", 1,"root",1);
                    QStringList contenido;
                    contenido.append("1, G, root\n1, U, root, root, 123\n");
                    QStringList file_name;
                    file_name.append("users.txt");
                    Inodo actual = f2_archivo::getInodo(discoArchivo, archivo.super.s_inode_start, 0);//raiz está en la posicion 0
                    archivo.crearArchivo_(actual, contenido, file_name, 0, false);
                    archivo.actualizarSuperBloque();
                    cout<<"\033[96mEDD creadas correctamente.\033[0m"<<endl;
                    /*if(id.compare(this->id_mount, Qt::CaseInsensitive)== 0){
                        logout();
                    }*/
            }
            else if(encontrado.part_type == 'l'){
                                f2_archivo::formatearPar_logica(discoArchivo, encontrado.particion_logica, type.toStdString(), fs.toStdString());

                                int inicioByte = encontrado.particion_logica.part_start + sizeof (EBR);
                                f2_archivo archivo(discoArchivo, &encontrado, inicioByte);
                                archivo.setUserInformation("root", 1,"root",1);
                                QStringList contenido;
                                contenido.append("1, G,root\n1, U, root, root, 123");
                                QStringList file_name;
                                file_name.append("users.txt");
                                Inodo actual = f2_archivo::getInodo(discoArchivo, archivo.super.s_inode_start, 0);//raiz está en la posicion 0
                                archivo.crearArchivo_(actual, contenido, file_name, 0, false);
                                archivo.actualizarSuperBloque();
                                /*if(id.compare(this->id_mount, Qt::CaseInsensitive)== 0){
                                    logout();
                                }*/
                            }
            else{ cout<<"\033[31mERROR: Partición no existe.\033[0m"<<endl<<endl;  }
            fclose(discoArchivo);
        }
    }else{
        cout<<"\033[31mERROR: No se encontro la particion.\033[0m"<<endl;
    }

}

string f2_mkfs::ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

