#ifndef COMANDO_RMDISK_H
#define COMANDO_RMDISK_H

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
class comando_rmdisk
{
public:
    comando_rmdisk();
    void ast_rmdisk(Nodo_arbol*);
    //EJECUTA COMANDOS
    void ejecuta_rmdisk(int psize, string pfit, string punit, QString ppath);
};

#endif // COMANDO_RMDISK_H
