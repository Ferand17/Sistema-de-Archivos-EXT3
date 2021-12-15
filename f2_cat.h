#ifndef F2_CAT_H
#define F2_CAT_H
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

class f2_cat
{
public:
    int *idUsuario;
    QString *usuario;
    QString *id_mount;
    QString *grupo;
    int *idGrupo;
    nodo_particiones *part_global;
    Lista_Particiones *lista;

    f2_cat();
    f2_cat(Lista_Particiones *lista, int *idUsuario, QString *usuario, QString *id_mount, QString *grupo, int *idGrupo, nodo_particiones *part_global);
    void ast_cat(Nodo_arbol *raiz);
    void ejecutar_cat(QString ppath);
    string ReplaceAll(string str, const string& from, const string& to);
};

#endif // F2_CAT_H
