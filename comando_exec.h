#ifndef COMANDO_EXEC_H
#define COMANDO_EXEC_H

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


class comando_exec
{
public:
    comando_exec();
    void ast_exec(QList<Nodo_arbol> *hijos);
    string ReplaceAll(std::string str, const std::string& from, const std::string& to);
    void ejecutar_exec(QString path);
};

#endif // COMANDO_EXEC_H
