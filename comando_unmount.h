#ifndef COMANDO_UNMOUNT_H
#define COMANDO_UNMOUNT_H

#include <QObject>
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
class comando_unmount
{
public:
    comando_unmount();
    Lista_Particiones *lista;
    void ast_unmount(Nodo_arbol*);
    void ejecutar_unmount(QString id);
};

#endif // COMANDO_UNMOUNT_H
