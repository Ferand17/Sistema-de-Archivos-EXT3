#ifndef F2_MKFS_H
#define F2_MKFS_H

#include <QObject>
#include <stdio.h>
#include <QtCore>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <QObject>
#include "nodo_arbol.h"
#include "estructuras.h"
#include "lista_particiones.h"
#include <QList>

using namespace std;

class f2_mkfs
{
public:
    Lista_Particiones *lista;
    f2_mkfs();
    void ast_mkfs(QList<Nodo_arbol> *hijos);
    void ejecutar_mkfs(QString id, QString type, QString fs);
    string ReplaceAll(std::string str, const std::string& from, const std::string& to);
    //void setUserInformation(QString usr_name, int usr_id, QString usr_grp,int usr_grp_id);
};

#endif // F2_MKFS_H
