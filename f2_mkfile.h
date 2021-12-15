#ifndef F2_MKFILE_H
#define F2_MKFILE_H
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

class f2_mkfile
{
public:
    int *idUsuario;
    QString *usuario;
    QString *id_mount;
    QString *grupo;
    int *idGrupo;
    nodo_particiones *part_global;

    Lista_Particiones *lista;

    f2_mkfile();
    f2_mkfile(Lista_Particiones *lista, int *idUsuario, QString *usuario, QString *id_mount, QString *grupo, int *idGrupo, nodo_particiones *part_global);


    void ast_mkfile(Nodo_arbol *raiz);
    void ejecutar_mkfile(QString ppath, bool pp, QString psize, QString pcont);

    QStringList getContent(QString size, QString cont);

    string ReplaceAll(string str, const string& from, const string& to);
};

#endif // F2_MKFILE_H
