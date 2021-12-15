#ifndef F2_CHGRP_H
#define F2_CHGRP_H
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

class f2_chgrp
{
public:

    int *idUsuario;
    QString *usuario;
    QString *id_mount;
    QString *grupo;
    int *idGrupo;
    nodo_particiones *part_global;

    Lista_Particiones *lista;

    f2_chgrp();
    f2_chgrp(Lista_Particiones *lista, int *idUsuario, QString *usuario, QString *id_mount, QString *grupo, int *idGrupo, nodo_particiones *part_global);
    void ast_chgrp(QList<Nodo_arbol> *hijos);
    void ejecutar_chgrp(QString pusr, QString pgrp);
    string ReplaceAll(string str, const string& from, const string& to);
};

#endif // F2_CHGRP_H
