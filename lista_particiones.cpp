#include "lista_particiones.h"
using namespace std;
Lista_Particiones::Lista_Particiones(){
    primero = nullptr;
}


void Lista_Particiones::insertarNodo(nodo_particiones *nuevo){
    nodo_particiones *aux = primero;
    if(primero == nullptr){
        primero = nuevo;
    }else{
        while(aux->siguiente!=nullptr){
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
    }

}


int Lista_Particiones::eliminarNodo(QString ID){
    nodo_particiones *aux = primero;
    QString tempID = "vd";
    tempID += aux->letra+QString::number(aux->num);
    if(ID == tempID){
        primero = aux->siguiente;
        free(aux);
        return 1;
    }else{
        nodo_particiones *aux2 = nullptr;
        while(aux!=nullptr){
            tempID = "vd";
            tempID += aux->letra+QString::number(aux->num);
            if(ID == tempID){
                aux2->siguiente = aux->siguiente;
                return 1;
            }
            aux2 = aux;
            aux = aux->siguiente;
        }
    }
    return 0;
}


/*
int Lista_Particiones::buscarLetra(QString path, QString nombre){
    nodo_particiones *aux = primero;
    int retorno = 'a';
    while(aux!=NULL){
        if((path == aux->path) && (nombre == aux->nombre)){
            return -1;
        }else{
            if(path == aux->path){
                return aux->letra;
            }else if(retorno <= aux->letra){
                retorno++;
            }
        }
        aux = aux->siguiente;
    }
    return retorno;
}


int Lista_Particiones::buscarNumero(QString path, QString nombre){
    int retorno = 1;
    nodo_particiones *aux = primero;
    while(aux!=nullptr){
        if((path == aux->path) && (retorno == aux->num)){
            retorno++;
        }
        aux = aux->siguiente;
    }
    return retorno;
}
*/

int Lista_Particiones::buscarLetra(QString path, QString nombre){
    nodo_particiones *aux = primero;
    int retorno = 'a';
    while(aux!=NULL){
        if((path == aux->path) && (nombre == aux->nombre)){
            return -1;
        }else{
            if(path == aux->path){
                return aux->letra;
            }else if(retorno <= aux->letra){
                retorno++;
            }
        }
        aux = aux->siguiente;
    }
    return retorno;
}


int Lista_Particiones::buscarNumero(QString path, QString nombre){
    int retorno = 1;
    nodo_particiones *aux = primero;
    while(aux!=nullptr){
        if((path == aux->path) && (retorno == aux->num)){
            retorno++;
        }
        aux = aux->siguiente;
    }
    return retorno;
}


QString Lista_Particiones::getDireccion(QString id){
    nodo_particiones *aux = primero;
    while(aux!=nullptr){
        QString tempID = "vd";
        tempID +=  aux->letra+QString::number(aux->num);
        if(id == tempID){
            return aux->path;
        }
        aux = aux->siguiente;
    }
    return "null";
}


bool Lista_Particiones::buscarNodo(QString path, QString nombre){
    nodo_particiones *aux = primero;
    while(aux!=nullptr){
        if((aux->path == path) && (aux->nombre == nombre)){
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}

/* Metodo para desplegar las particiones montadas
*/
void Lista_Particiones::mostrarLista(){
    cout << "*********************************" << endl;
    cout << "*       LISTA DE PARTICIONES    *" << endl;
    cout << "*********************************" << endl;
    cout << "*      NOMBRE    |    ID        *" << endl;
    cout << "*********************************" << endl;
    nodo_particiones *aux = primero;
    while(aux!=nullptr){
        cout << "     "<< aux->nombre.toStdString() << "          " << "vd"<<aux->letra<<aux->num << endl;
        cout << "*********************************" << endl;
        aux = aux->siguiente;
    }
}

nodo_particiones Lista_Particiones::getParticionMontada(QString pid){
    nodo_particiones *aux = primero;
    while(aux!=nullptr){
        QString ntemp= "vd";
        ntemp.append(aux->letra);
        ntemp.append(QString::number(aux->num));
        if(ntemp==pid){
            return *aux;
        }
        aux = aux->siguiente;
    }
    nodo_particiones *temp = new nodo_particiones();
    return *temp;
}

bool Lista_Particiones::estavacio(){
    if(primero==nullptr){
        return true;
    }
    return false;
}
