#ifndef COMANDO_MKDISK_H
#define COMANDO_MKDISK_H

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
using namespace std;
class comando_mkdisk
{
public:
    comando_mkdisk();
    //RECORRIDO DE LOS ARBOLES
    void ast_mkdisk(Nodo_arbol*);
    //EJECUTA COMANDOS
    void ejecuta_mkdisk(int psize, string pfit, string punit, QString ppath);

    void crear_disco(QString ppath);
    QString obtener_path(QString);
    QString nombre_archivo(QString);
    string ReplaceAll(std::string str, const std::string& from, const std::string& to);
};

#endif // COMANDO_MKDISK_H
