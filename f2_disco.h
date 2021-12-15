#ifndef F2_DISCO_H
#define F2_DISCO_H

#include <QObject>
#include "estructuras_fase2.h"
#include "estructuras.h"
#include  "cmath"
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

class f2_disco
{
        public:

            static const int MKDISK = 1;
            static const int REP = 2;
            f2_disco();
            static char getFit(QString fit);
            static int tamanioBytes(int size, QString unit);
            static bool crearDisco(QString size, QString fit, QString unit, QString path);
            static MBR getMbr(FILE * archivo);
            static bool crearDisco_(MBR mbr, QString path);
            static bool eliminarDisco(QString path);
            static void agregarMbr(MBR mbr, QString path);
            static void crearParticion(QString size, QString unit, QString path, QString type, QString fit, QString name);
            static void eliminarParticion(QString name, QString path, QString pdelete);
            static void agregarEspacio(QString name, QString size, QString unit, QString path);
            // Se necesita size, path, name, -  unit
            static void reporteMbr(QString disc_path, QString save_path);
            static void reporteDisk(QString disc_path, QString save_path);
            static QStringList evaluarDirectorio(QString path, int id_comando);
            static void generarReporte(stringstream &data, stringstream &data2, QString save_path);

        private:

            static int getPorcentaje(int total_size, int value);


        };
#endif // F2_DISCO_H
