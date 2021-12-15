#ifndef F2_EDIT_H
#define F2_EDIT_H

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

class f2_edit
{
public:
    int *idUsuario;
    QString *usuario;
    QString *id_mount;
    QString *grupo;
    int *idGrupo;
    nodo_particiones *part_global;
    Lista_Particiones *lista;

    f2_edit();
    f2_edit(Lista_Particiones *lista, int *idUsuario, QString *usuario, QString *id_mount, QString *grupo, int *idGrupo, nodo_particiones *part_global);
    void ast_edit(QList<Nodo_arbol> *hijos);
    void ejecutar_edit(QString ppath, QString pcont);
    string ReplaceAll(string str, const string& from, const string& to);
};

#endif // F2_EDIT_H
