#ifndef LISTA_PARTICIONES_H
#define LISTA_PARTICIONES_H

#include <QObject>
#include <iostream>
#include "nodo_particiones.h"

using namespace std;
class Lista_Particiones
{
public:
    Lista_Particiones();
    nodo_particiones *primero;
    int buscarLetra(QString path, QString nombre);
    int buscarNumero(QString path, QString nombre);
//    int buscarNumero(QString path, QString nombre);
//    int buscarLetra(QString path, QString nombre);
    void mostrarLista();
    void insertarNodo(nodo_particiones*);
    int eliminarNodo(QString ID);
    bool buscarNodo(QString path, QString nombre);
    QString getDireccion(QString id);

    //FASE2
    nodo_particiones getParticionMontada(QString pid);
    bool estavacio();
};

#endif // LISTA_PARTICIONES_H
