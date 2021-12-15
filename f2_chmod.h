#ifndef F2_CHMOD_H
#define F2_CHMOD_H

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

class f2_chmod
{
public:
    int *idUsuario;
    QString *usuario;
    QString *id_mount;
    QString *grupo;
    int *idGrupo;
    nodo_particiones *part_global;
    Lista_Particiones *lista;

    f2_chmod();
    f2_chmod(Lista_Particiones *lista, int *idUsuario, QString *usuario, QString *id_mount, QString *grupo, int *idGrupo, nodo_particiones *part_global);


    void ast_chmod(Nodo_arbol *raiz);
    void ejecutar_chmod(QString ppath, QString pugo, bool pr);
    string ReplaceAll(string str, const string& from, const string& to);
    //void setUserInformation(QString usr_name, int usr_id, QString usr_grp,int usr_grp_id);
};

#endif // F2_CHMOD_H
