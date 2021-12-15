#include "comando_rmdisk.h"

comando_rmdisk::comando_rmdisk()
{

}

void comando_rmdisk::ast_rmdisk(Nodo_arbol *raiz){
    QString path = raiz->valor;
    path = path.replace("\"","");
    FILE *archivo;
    if((archivo=fopen(path.toStdString().c_str(),"r"))){
        string opcion = "";
        cout << "¿Esta seguro que desea eliminar el disco? S/N : ";
        getline(cin,opcion);
        if(opcion.compare("S") == 0 || opcion.compare("s") == 0){
            string comando = "rm \""+path.toStdString()+"\"";
            system(comando.c_str());
            cout <<"\033[94mDisco eliminado con exito.\033[0m" << endl;
        }else if(opcion.compare("N") || opcion.compare("n") == 0){
            cout << "\033[94mOperacion Cancelada.\033[0m" << endl;;
        }else{
            cout << "\033[31mERROR: No existe la opcion seleccionada.\033[0m" << endl;
        }
        fclose(archivo);
    }else{
        cout << "\033[31mERROR: No existe el Disco que desea eliminar.\033[0m" << endl;
    }
}
