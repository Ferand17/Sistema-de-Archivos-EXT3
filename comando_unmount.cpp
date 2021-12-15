#include "comando_unmount.h"
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
comando_unmount::comando_unmount()
{

}
void comando_unmount::ast_unmount(Nodo_arbol *arbol){
    ejecutar_unmount(arbol->valor);
}
void comando_unmount::ejecutar_unmount(QString id){
    if(lista->primero!=nullptr){

        int eliminado = lista->eliminarNodo(id);
        if(eliminado == 1)
            cout << "\033[94mUnidad desmontada con exito.\033[0m" << endl;
        else
            cout << "\033[93mALERTA: la unidad "<<id.toStdString()<<" No esta Montada.\033[0m"<<endl;
    }else{
        cout<<"\033[93mALERTA: No hay ninguna unidad montada.\033[0m"<<endl;
    }

}
