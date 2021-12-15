#ifndef F2_MKGRP_RMGRP_H
#define F2_MKGRP_RMGRP_H
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

class f2_mkgrp_rmgrp
{
public:
    int *idUsuario;
    QString *usuario;
    QString *id_mount;
    QString *grupo;
    int *idGrupo;
    nodo_particiones *part_global;
    Lista_Particiones *lista;
    f2_mkgrp_rmgrp(Lista_Particiones *lista, int *idUsuario, QString *usuario, QString *id_mount, QString *grupo, int *idGrupo, nodo_particiones *part_global);


    f2_mkgrp_rmgrp();
    void ast_mkgrp_rmgrp(Nodo_arbol *raiz, bool ptipo);
    void ejecutar_mkgrp_rmgrp(QString pname, bool ptipo);
    string ReplaceAll(string str, const string& from, const string& to);

};

#endif // F2_MKGRP_MKUSR_H
