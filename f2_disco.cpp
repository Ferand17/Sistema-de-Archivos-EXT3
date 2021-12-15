 #include "f2_disco.h"

#include <QObject>
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


f2_disco::f2_disco(){

}


char f2_disco::getFit(QString fit){
    if(QString::compare(fit, "wf", Qt::CaseInsensitive)==0){
        return 'w';
    }
    else if(QString::compare(fit, "ff", Qt::CaseInsensitive)==0){
        return 'f';
    }
    else{
        return 'b';
    }
}

MBR f2_disco::getMbr(FILE *archivo){
    MBR disco;//Variable que contendrá el mbr(Master Boot Record) obtenida del archivo
    fseek(archivo, 0, SEEK_SET);//Se posiciona el puntero al inicio del archivo
    fread(&disco, sizeof(MBR), 1, archivo);//Obtenemos el mbr(Master Boot Record) del disco(archivo)
    return disco;
}

//-------------------------------------METODOS PARA CREAR DISCO --------------------------------------------------------------------------
int f2_disco::tamanioBytes(int size, QString units){
    if(QString::compare(units, "k", Qt::CaseInsensitive) == 0){
        return size * 1024;
    }
    else if(QString::compare(units, "m", Qt::CaseInsensitive) == 0){
        return size * 1024 * 1024;
    }
    else{
        return size;
    }
}

bool f2_disco::crearDisco(QString size, QString fit, QString unit, QString path){
    int tam = size.toInt();
    if(tam > 0){
        //Se crea la estructura del nuevo disco y se agrega la información

        MBR  nuevoDisco;
        nuevoDisco.mbr_size = tamanioBytes(tam, unit);
        nuevoDisco.mbr_date_created = time(NULL);
        nuevoDisco.mbr_disk_signature = rand();
        nuevoDisco.mbr_disk_fit = getFit(fit);
        for(int i = 0; i < 4; i++){
            nuevoDisco.mbr_partition[i].part_status = '0';
            nuevoDisco.mbr_partition[i].part_start = -1;
            nuevoDisco.mbr_partition[i].part_size = 0;
        }

        //Se crea el disco(archivo) con el tamaño especificado
        if(crearDisco_(nuevoDisco, path)){
            //Se agrega el struct al disco(archivo) recien creado
            agregarMbr(nuevoDisco,path);
            cout<<"\033[96mDisco creado correctamente en: "<<path.toStdString()<<"\033[0m"<<endl<<endl;
            return true;
        }
        cout<<"\033[31mERROR: No se pudo crear el disco.\033[0m"<<endl<<endl;
        return false;
    }else{
        cout<<"\033[31mERROR: El tamaño del disco debe ser mayor a 0.\033[0m"<<endl<<endl;
        return false;
    }
}

QStringList f2_disco::evaluarDirectorio(QString path, int id_comand){
    //Crear un disco(archivo) con el tamaño y en la ruta especificada


    QStringList directorios;
    QStringList nuevo;
    directorios = path.split('/');
    QStringList archivo = directorios[directorios.size()-1].split(".");
    if(archivo.size() == 2){
        QString dir_path = "";
        for(int i = 0; i < (directorios.size()-1) ; i++){
            if(directorios[i].size() >0){
                dir_path += "/"+directorios[i];
            }
        }
        //El path incluye el nombre del archivo y su extencion
        if(MKDISK == id_comand && QString::compare(archivo[1], "disk",Qt::CaseInsensitive) == 0){
            QDir dir(dir_path);
            if (!dir.exists()) {
                dir.mkpath(".");
            }
            nuevo <<dir_path<<archivo[0]<<archivo[1];
            return nuevo;
        }
        else if(REP == id_comand &&
                (QString::compare(archivo[1], "pdf",Qt::CaseInsensitive) == 0 ||
                 QString::compare(archivo[1], "jpg",Qt::CaseInsensitive) == 0 ||
                 QString::compare(archivo[1], "png",Qt::CaseInsensitive) == 0 ||
                 QString::compare(archivo[1], "txt",Qt::CaseInsensitive) == 0 )){
            QDir dir(dir_path);
            if (!dir.exists()) {
                dir.mkpath(".");
            }

            nuevo <<dir_path<<archivo[0]<<archivo[1];
            return nuevo;
        }
    }
    return nuevo;
}

bool f2_disco::crearDisco_(MBR mbr,QString path){
    QStringList exten = evaluarDirectorio(path, MKDISK);
    if(exten.size() != 3){
        cout<<"\033[31mERROR: No se especificó el nombre del disco(*.disk) dentro del -path.\033[0m"<<endl<<endl;
        return false;
    }
    FILE* fileDisco = fopen(path.toStdString().c_str(), "ab");
    if (fileDisco != NULL){
        int numero_kb = (mbr.mbr_size/1024);
        char buffer[1024]; //este arreglo es 1Kb de info
        for(int i=0 ; i < 1024; i++){
            buffer[i]='\0';
        }
        int j = 0;
        while(j != numero_kb){
            fwrite(&buffer, 1024 , 1, fileDisco);
            j++;
        }
        fclose(fileDisco);
        return true;
    }
    else{
        return false;
    }
}

void f2_disco::agregarMbr(MBR mbr, QString path){
    //Agrega el mbr(Master Boot Record) al inicio de un archivo
    FILE *fileDisco = fopen(path.toStdString().c_str(), "rb+");
    if (fileDisco!=NULL){
         fseek(fileDisco, 0, SEEK_SET);
         fwrite(&mbr, sizeof(mbr), 1, fileDisco);
         fclose(fileDisco);
    }
}

//----------------------------------- METODO PARA ELIMINAR DISCO ---------------------------------------------------------------------
bool f2_disco::eliminarDisco(QString path){
    if (FILE *file = fopen(path.toStdString().c_str(), "r")) {
        fclose(file);
        QString op = "0";
        cout<<"¿Desea eliminar el disco? (S/N): ";
        string str;
        getline(std::cin, str);
        if(QString::compare(str.c_str(),"s",Qt::CaseInsensitive)==0){
            string s = path.toStdString();
            remove(s.c_str());
            char co[500];
            strcat(co,"rm  ");
            strcat(co,"'"+path.toLatin1()+"'");
            system(co);
            return true;
         }
    }
    return false;
}

