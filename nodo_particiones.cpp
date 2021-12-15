#include "nodo_particiones.h"

using namespace std;
/****FASE2*/
nodo_particiones::nodo_particiones()
{
    path="";
    nombre="";
    letra=0;
    num=0;
    siguiente=nullptr;
    part_type=0;
}
/*****FASE2*/

nodo_particiones::nodo_particiones(QString path, QString nombre, char letra, int num, char part_type)
{
    this->path = path;
    this->nombre = nombre;
    this->letra = letra;
    this->num = num;
    this->siguiente = nullptr;
    this->part_type=part_type;
}


