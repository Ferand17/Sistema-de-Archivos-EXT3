#ifndef F2_LOGIN_H
#define F2_LOGIN_H


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

class f2_login
{
public:
    int *idUsuario;
    QString *usuario;
    QString *id_mount;
    QString *grupo;
    int *idGrupo;
    nodo_particiones *part_global;

    f2_login();
    f2_login(Lista_Particiones *lista, int *idUsuario, QString *usuario, QString *id_mount, QString *grupo, int *idGrupo, nodo_particiones *part_global);


    Lista_Particiones *lista;
    void ast_login(Nodo_arbol *raiz);
    void ejecutar_login(QString usr, QString pwd, QString id);
    string ReplaceAll(std::string str, const std::string& from, const std::string& to);
};

#endif // F2_LOGIN_H
