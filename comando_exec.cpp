#include "comando_exec.h"
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

using namespace std;

comando_exec::comando_exec()
{

}
void comando_exec::ast_exec(QList<Nodo_arbol> *hijos)
{

    QString vpath="";
    string prueba=hijos->at(0).valor.toStdString();
    prueba=ReplaceAll(prueba, std::string("\""), std::string(""));
    vpath=QString::fromStdString(prueba);
    ejecutar_exec(vpath);
}
void comando_exec::ejecutar_exec(QString path)
{
    string auxPath = path.toStdString();
    string line;
    FILE *fp;
    if((fp = fopen(auxPath.c_str(),"r"))){
        char line[400]="";
        memset(line,0,sizeof(line));
        while(fgets(line,sizeof line,fp)){
            if(line[0]!='\n'){
                //line=TRIM(line);
                cout << line << endl;
                //leerComando(line);
            }
            memset(line,0,sizeof(line));
        }
        fclose(fp);
    }else{
        cout << "ERROR: No se Encontro el Archivo de entrada" << endl;
    }

}
string comando_exec::ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}
