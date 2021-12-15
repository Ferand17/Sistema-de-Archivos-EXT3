#include "nodo_arbol.h"
#include<stdlib.h>
#include<iostream>


using namespace std;

Nodo_arbol::Nodo_arbol(QString ptipo, QString pvalor)
{
    tipo =ptipo;
    valor = pvalor;
    tipo_ = getTipo();
    hijos = QList<Nodo_arbol>();
}

//aqui permitimos saber que es cada nodo del arborl
int Nodo_arbol::getTipo()
{
    if(this->tipo=="MKDISK")return 1;
    if(this->tipo=="RMDISK")return 2;
    if(this->tipo=="FDISK")return 3;
    if(this->tipo=="MOUNT")return 4;
    if(this->tipo=="UNMOUNT")return 5;
    if(this->tipo=="REP")return 6;
    if(this->tipo=="EXEC")return 7;
    if(this->tipo=="PARAMETRO")return 8;

    if(this->tipo=="path")return 9;
    if(this->tipo == "id")return 10;
    if(this->tipo=="name")return 11;
    if(this->tipo=="tipo")return 12;
    if(this->tipo=="f")return 13;
    if(this->tipo=="u")return 14;
    if(this->tipo=="size")return 15;
    if(this->tipo=="type")return 16;
    if(this->tipo=="delete")return 17;
    if(this->tipo=="add")return 18;
    if(this->tipo=="ajuste")return 19;
    if(this->tipo=="unidad")return 20;

    if(this->tipo=="MKFS")return 21;
    if(this->tipo=="LOGIN")return 22;
    if(this->tipo=="LOGOUT")return 23;
    if(this->tipo=="MKGRP")return 24;
    if(this->tipo=="RMGRP")return 25;
    if(this->tipo=="MKUSR")return 26;
    if(this->tipo=="RMUSR")return 27;
    if(this->tipo=="CHMOD")return 28;
    if(this->tipo=="MKFILE")return 29;
    if(this->tipo=="CAT")return 30;
    if(this->tipo=="REM")return 31;
    if(this->tipo=="EDIT")return 32;
    if(this->tipo=="REN")return 33;
    if(this->tipo=="MKDIR")return 34;
    if(this->tipo=="CP")return 35;
    if(this->tipo=="MV")return 36;
    if(this->tipo=="FIND")return 37;
    if(this->tipo=="CHOWN")return 38;
    if(this->tipo=="CHGRP")return 39;
    if(this->tipo=="PAUSE")return 40;

    if(this->tipo=="ruta")return 41;

    if(this->tipo=="usr")return 42;
    if(this->tipo=="pwd")return 43;
    if(this->tipo=="grp")return 44;
    if(this->tipo=="ugo")return 45;
    if(this->tipo=="r")return 46;
    if(this->tipo=="p")return 47;
    if(this->tipo=="cont")return 48;
    if(this->tipo=="file")return 49;

    return 0;
}

void Nodo_arbol::add(Nodo_arbol n){
    hijos.append(n);
}

