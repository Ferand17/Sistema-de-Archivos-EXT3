#ifndef F2_MKUSR_H
#define F2_MKUSR_H
#include <QObject>
#include <stdio.h>
#include <QtCore>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <string.h>
//#include <QObject>
#include "nodo_arbol.h"
#include "estructuras.h"
#include "lista_particiones.h"
#include "f2_archivo.h"
using namespace std;

class f2_mkusr
{
public:
    int *idUsuario;
    QString *usuario;
    QString *id_mount;
    QString *grupo;
    int *idGrupo;
    nodo_particiones *part_global;
    Lista_Particiones *lista;
    f2_mkusr(Lista_Particiones *lista, int *idUsuario, QString *usuario, QString *id_mount, QString *grupo, int *idGrupo, nodo_particiones *part_global);

    f2_mkusr();





    void ast_mkusr(Nodo_arbol *raiz);
    void ejecutar_mkusr(QString pusr, QString ppwd,QString pgrp);
    string ReplaceAll(string str, const string& from, const string& to);
};

#endif // F2_MKUSR_H
