#ifndef COMANDO_FDISK_H
#define COMANDO_FDISK_H

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

using namespace std;

class comando_fdisk
{
public:
    comando_fdisk();
    void recibe_lista(Lista_Particiones *lista);
    Lista_Particiones *lista;
    //RECORRIDO DE LOS ARBOLES
    void ast_fdisk(Nodo_arbol*);
    //EJECUTA COMANDOS
    void ejecuta_fdisk_crear_particones(QString ptype, QString ppath, QString pname, int psize, QString pfit, string punit);

    QString obtener_path(QString);
    QString nombre_archivo(QString);

    void crearParticionPrimaria(QString, QString nombre, int size, QString fit, string unit, QString archivo);
    void crearParticionExtendida(QString, QString nombre, int size, QString fit, string unit, QString archivo);
    void crearParticionLogica(QString, QString nombre, int size, QString fit, string unit, QString archivo);
    void agregarQuitarParticion(QString, QString nombre, int add, char unit, QString archivo);

    bool existeParticion(QString direccion, QString nombre);
    int buscarnombrelogica(QString name, int inicioextend, QString path);
    EBR devolversiguienteebr(int inicio, QString path);
    int buscarParticion_L(QString, QString nombre);
    void eliminarParticion(QString, QString nombre, QString typeDelete, QString archivo);

    string ReplaceAll(std::string str, const std::string& from, const std::string& to);
    bool existe_archivo(QString path);

};

#endif // COMANDO_FDISK_H
