#ifndef COMANDO_MOUNT_H
#define COMANDO_MOUNT_H

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

class comando_mount
{
public:
    comando_mount();
    Lista_Particiones *lista;
    //RECORRIDO DE LOS ARBOLES
    void ast_mount(QList<Nodo_arbol> *hijos);
    string ReplaceAll(std::string str, const std::string& from, const std::string& to);
    void ejecutar_mount(QString name, QString path);
    int buscarParticion_P_E(QString direccion, QString nombre);
    int buscarParticion_L(QString direccion, QString nombre);
};

#endif // COMANDO_MOUNT_H
