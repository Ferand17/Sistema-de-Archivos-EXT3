#ifndef NODO_PARTICIONES_H
#define NODO_PARTICIONES_H

#include <QObject>
#include "estructuras.h"
using namespace std;

class nodo_particiones
{
public:
    nodo_particiones();
    nodo_particiones(QString path, QString nombre, char, int, char part_type);
    QString path;
    QString nombre;
    char letra;
    int num;
    nodo_particiones *siguiente;
    /*FASE 2*/
    char part_type; //Tipo de particion: Primaria(p), Extendida(e) o Logica(l)

    Partition particion; //La partición se guardará aquí, si es de tipo 'p' o 'e'
    EBR particion_logica; //La partición se guardará aquí, si es de tipo 'l'
};

#endif // NODO_PARTICIONES_H
