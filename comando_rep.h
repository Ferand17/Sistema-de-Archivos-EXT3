#ifndef COMANDO_REP_H
#define COMANDO_REP_H

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
#include "nodo_particiones.h"
using namespace std;


class comando_rep
{
public:
    comando_rep();
    Lista_Particiones *lista;
    //RECORRIDO DE LOS ARBOLES
    void ast_rep(Nodo_arbol* raiz);
    string ReplaceAll(std::string str, const std::string& from, const std::string& to);
    void ejecutar_rep(QString pname, QString ppath, QString pid, QString pruta);
    QString obtener_extension(QString path);
    QString obtener_path(QString path);
    void graficarDisco(QString path, QString destino, QString extension);
    void graficarMBR(QString path, QString destino, QString extension);
    void graficarINODE(nodo_particiones encontrado, QString ppath);
    void graficarJOURNAL(nodo_particiones encontrado, QString ppath);
    void graficarBLOCK(nodo_particiones encontrado, QString ppath);
    void graficarBMINODE(nodo_particiones encontrado, QString ppath);
    void graficarBMBLOCK(nodo_particiones encontrado, QString ppath);
    void graficarFILE(nodo_particiones encontrado, QString ppath, QString pruta);
    void graficarLS(nodo_particiones encontrado, QString ppath, QString pruta);
};

#endif // COMANDO_REP_H
