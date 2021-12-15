#include "comando_fdisk.h"
#include <algorithm>
#include <string>

using namespace std;

comando_fdisk::comando_fdisk()
{

}
void comando_fdisk::recibe_lista(Lista_Particiones *lista)
{

}

void comando_fdisk::ast_fdisk(Nodo_arbol *raiz)
{
    string log_error="";
    //VALORES DE CADA PARAMETRO
    bool berror=false;
    //PARAMETROS OBLIGATORIOS
    bool bsize=false;
    bool bpath=false;
    bool bname=false;
    bool bfit=false;
    bool btype=false;
    bool badd=false;
    bool bdelete=false;
    //PARAMETROS
    int vsize=0;
    string vunit="k";
    QString vpath="";
    QString vtype="primaria";
    QString vfit="wf";
    QString vdelete="";
    QString vname="";
    int vadd=0;


    for(int c = 0; c < raiz->hijos.count(); c++)
    {
        Nodo_arbol temp = raiz->hijos.at(c);
        if(temp.tipo_==SIZE){
            if(temp.valor.toUInt()>0){
                bsize=true;
                vsize=temp.valor.toUInt();
            }else{
                berror=true;
                log_error+="size= "+ temp.valor.toStdString() +", El parametro size debe ser >=0.\n";
            }
        }
        else if(temp.tipo_==UNIT){
            vunit=temp.hijos.at(0).valor.toStdString();
        }
        else if(temp.tipo_==PATH){
            bpath=true;
            string prueba=temp.valor.toStdString();
            prueba=ReplaceAll(prueba, std::string("\""), std::string(""));
            vpath=QString::fromStdString(prueba);
        }
        else if(temp.tipo_==TYPE){
            btype=true;
            vtype=temp.hijos.at(0).valor;
        }
        else if(temp.tipo_==FIT){
            bfit=true;
            vfit=temp.hijos.at(0).valor;
        }
        else if(temp.tipo_==DELETE){
            bdelete=true;
            vdelete=temp.hijos.at(0).valor;
        }
        else if(temp.tipo_==NAME){
            bname=true;
            string prueba=temp.valor.toStdString();
            prueba=ReplaceAll(prueba, std::string("\""), std::string(""));
            vname=QString::fromStdString(prueba);
        }
        else if(temp.tipo_==ADD){
            badd=true;
            vadd=temp.valor.toInt();
        }
    }


    if(!bpath){
        berror=true;
        log_error+="Parametro -path es Obligatorio.\n";
    }

    if(!bname){
        berror=true;
        log_error+="Parametro -name es Obligatorio.\n";
    }

    if(!berror){


        if(bsize){
            if(bdelete || badd){
                berror=true;
                log_error+="Se esta creando una particion, los Parametros -delete, -add no estan permitidos.\n";
            }
            else{
                    ejecuta_fdisk_crear_particones(vtype,vpath,vname,vsize,vfit,vunit);
            }

        }
        else if(badd){
            if(bdelete || bsize){
                berror=true;
                log_error+="Se esta modificando el tamaño una particion, los Parametros -delete, -size no estas permitidos.\n";
            }
            else{
                char auxUnit=0;
                if(vunit=="b"){
                    auxUnit='b';
                }
                else if(vunit=="k"){
                    auxUnit='k';
                }
                else if(vunit=="m"){
                    auxUnit='m';
                }

                //DISCO
                agregarQuitarParticion(vpath, vname, vadd, auxUnit,"principal");
            }

        }
        else if(bdelete){
            if(bsize || badd || bfit || btype){
                berror=true;
                cout << "Se esta eliminando una particion, los Parametros -size, -add, -f, -type no estan permitidos,\n" << endl;
            }else{
                string opcion = "";
                cout << "¿Seguro que desea eliminar la particion? S/N : " ;
                getline(cin, opcion);
                if(opcion.compare("S") == 0 || opcion.compare("s") == 0){
                    //Archivo principal
                    eliminarParticion(vpath, vname, vdelete,"principal");
                }else if(opcion.compare("N")==0 || opcion.compare("n") == 0){
                    cout << "Operacion Cancelada!!!!!" << endl;;
                }else{
                    berror=true;
                    log_error+="Opcion Incorrecta, Solo se permite S o N.\n";
                }

            }
        }
    }
    if(berror){
        cout<<"\033[31mEL COMANDO CONTIENE ERRORES: "<<endl;
        cout<<log_error<<"\033[0m"<<endl;
    }else{
         //cout<<"COMANDO EJECUTADO CORRECTAMENTE."<<endl;
    }
}

void comando_fdisk::ejecuta_fdisk_crear_particones(QString ptype, QString ppath, QString pname, int psize, QString pfit, string punit)
{
    if(ptype == "primaria"){

        if(existe_archivo(ppath)){
            //Archivo principal
            crearParticionPrimaria(ppath, pname, psize, pfit, punit,"principal");
        }
        else{
            cout<<"\033[31mERROR: No existe el Disco.\033[0m"<<endl;
        }


    }else if(ptype == "extendida"){
       if(existe_archivo(ppath)){
            //Archivo principal
            crearParticionExtendida(ppath, pname, psize, pfit, punit,"principal");
        }
        else{
            cout<<"\033[31mERROR: No existe el Disco.\033[0m"<<endl;
        }
    }else if(ptype == "logica"){
        if(existe_archivo(ppath)){
            //Archivo principal
            crearParticionLogica(ppath, pname, psize, pfit, punit,"principal");
         }
         else{
             cout<<"\033[31mERROR: No existe el Disco.\033[0m"<<endl;
         }



    }
}

QString comando_fdisk::obtener_path(QString path){
    string aux = path.toStdString();
    string delimiter = "/";
    size_t pos = 0;
    string res = "";
    while((pos = aux.find(delimiter))!=string::npos){
        res += aux.substr(0,pos)+"/";
        aux.erase(0,pos + delimiter.length());
    }
    return QString::fromStdString(res);
}

QString comando_fdisk::nombre_archivo(QString path){
    string aux = path.toStdString();
    string delimiter = "/";
    size_t pos = 0;
    string res = "";
    while((pos = aux.find(delimiter))!=string::npos){
        aux.erase(0,pos + delimiter.length());
    }
    delimiter = ".";
    pos = aux.find(delimiter);
    res = aux.substr(0,pos);
    return QString::fromStdString(res);
}

void comando_fdisk::crearParticionPrimaria(QString path, QString nombre, int size, QString fit, string unit, QString archivo){

    char auxFit = 0;
    char auxUnit = 0;
    string auxPath = path.toStdString();
    int size_bytes = 1024;
    char buffer = '1';

    if(fit=="bf"){
        auxFit='B';
    }
    else if(fit=="ff"){
        auxFit='F';
    }
    else if(fit=="wf"){
        auxFit='W';
    }

    if(unit=="b"){
        auxUnit='b';
        size_bytes = size;
    }
    else if(unit=="k"){
        auxUnit='k';
        size_bytes = size * 1024;
    }
    else if(unit=="m"){
        auxUnit='m';
        size_bytes = size*1024*1024;
    }
    //cout<<size<<" "<<size_bytes<<endl;
    FILE *fp;
    MBR masterboot;

    if((fp = fopen(auxPath.c_str(), "rb+"))){
        bool flagParticion = false;//Flag para ver si hay una particion disponible
        int numParticion = 0;//Que numero de particion es
        fseek(fp,0,SEEK_SET);
        fread(&masterboot,sizeof(MBR),1,fp);
        //Verificar si existe una particion disponible
        for(int i = 0; i < 4; i++){
            if(masterboot.mbr_partition[i].part_start == -1 || (masterboot.mbr_partition[i].part_status == '1' && masterboot.mbr_partition[i].part_size>=size_bytes)){
                flagParticion = true;
                numParticion = i;
                break;
            }
        }

        if(flagParticion){
            //Verificar el espacio libre del disco
            int espacioUsado = 0;
            for(int i = 0; i < 4; i++){
                if(masterboot.mbr_partition[i].part_status!='1'){
                    espacioUsado += masterboot.mbr_partition[i].part_size;
                }
            }
            if(archivo == "principal"){
                cout << "Espacio Disponible: " << (masterboot.mbr_size - espacioUsado) << " Bytes" << endl;
                cout << "Espacio Requerido:  " << size_bytes << " Bytes" << endl;
            }
            //Verificar que haya espacio suficiente para crear la particion
            if((masterboot.mbr_size - espacioUsado) >= size_bytes){
                if(!existeParticion(path,nombre)){
                    if(masterboot.mbr_disk_fit == 'F'){//FIRST FIT
                        masterboot.mbr_partition[numParticion].part_type = 'P';
                        masterboot.mbr_partition[numParticion].part_fit = auxFit;
                        //start
                        if(numParticion == 0){
                            masterboot.mbr_partition[numParticion].part_start = sizeof(masterboot);
                        }else{
                            masterboot.mbr_partition[numParticion].part_start = masterboot.mbr_partition[numParticion-1].part_start + masterboot.mbr_partition[numParticion-1].part_size;
                        }
                        masterboot.mbr_partition[numParticion].part_size = size_bytes;
                        masterboot.mbr_partition[numParticion].part_status = '0';
                        strcpy(masterboot.mbr_partition[numParticion].part_name,nombre.toStdString().c_str());
                        //Se guarda de nuevo el MBR
                        fseek(fp,0,SEEK_SET);
                        fwrite(&masterboot,sizeof(MBR),1,fp);
                        //Se guardan los bytes de la particion
                        fseek(fp,masterboot.mbr_partition[numParticion].part_start,SEEK_SET);
                        for(int i = 0; i < size_bytes; i++){
                            fwrite(&buffer,1,1,fp);
                        }
                        if(archivo == "principal") cout << "ejecutando...\n" << "\033[96mParticion primaria creada con exito.\033[0m" <<  endl;
                    }else if(masterboot.mbr_disk_fit == 'B'){//BEST FIT
                        int bestIndex = numParticion;
                        for(int i = 0; i < 4; i++){
                            if(masterboot.mbr_partition[i].part_start == -1 || (masterboot.mbr_partition[i].part_status == '1' && masterboot.mbr_partition[i].part_size>=size_bytes)){
                                if(i != numParticion){
                                    if(masterboot.mbr_partition[bestIndex].part_size > masterboot.mbr_partition[i].part_size){
                                        bestIndex = i;
                                        break;
                                    }
                                }
                            }
                        }
                        masterboot.mbr_partition[bestIndex].part_type = 'P';
                        masterboot.mbr_partition[bestIndex].part_fit = auxFit;
                        //start
                        if(bestIndex == 0){
                            masterboot.mbr_partition[bestIndex].part_start = sizeof(masterboot);
                        }else{
                            masterboot.mbr_partition[bestIndex].part_start = masterboot.mbr_partition[bestIndex-1].part_start + masterboot.mbr_partition[bestIndex-1].part_size;
                        }
                        masterboot.mbr_partition[bestIndex].part_size = size_bytes;
                        masterboot.mbr_partition[bestIndex].part_status = '0';
                        strcpy(masterboot.mbr_partition[bestIndex].part_name,nombre.toStdString().c_str());
                        //Se guarda de nuevo el MBR
                        fseek(fp,0,SEEK_SET);
                        fwrite(&masterboot,sizeof(MBR),1,fp);
                        //Se guardan los bytes de la particion
                        fseek(fp,masterboot.mbr_partition[bestIndex].part_start,SEEK_SET);
                        for(int i = 0; i < size_bytes; i++){
                            fwrite(&buffer,1,1,fp);
                        }
                        if(archivo == "principal") cout << "...\n" << "\033[96mParticion primaria creada con exito.\033[0m" <<  endl;
                    }else if(masterboot.mbr_disk_fit == 'W'){//WORST FIT
                        int  worstIndex= numParticion;
                        for(int i = 0; i < 4; i++){
                            if(masterboot.mbr_partition[i].part_start == -1 || (masterboot.mbr_partition[i].part_status == '1' && masterboot.mbr_partition[i].part_size>=size_bytes)){
                                if(i != numParticion){
                                    if(masterboot.mbr_partition[worstIndex].part_size < masterboot.mbr_partition[i].part_size){
                                        worstIndex = i;
                                        break;
                                    }
                                }
                            }
                        }
                        masterboot.mbr_partition[worstIndex].part_type = 'P';
                        masterboot.mbr_partition[worstIndex].part_fit = auxFit;
                        //start
                        if(worstIndex == 0){
                            masterboot.mbr_partition[worstIndex].part_start = sizeof(masterboot);
                        }else{
                            masterboot.mbr_partition[worstIndex].part_start = masterboot.mbr_partition[worstIndex-1].part_start + masterboot.mbr_partition[worstIndex-1].part_size;
                        }
                        masterboot.mbr_partition[worstIndex].part_size = size_bytes;
                        masterboot.mbr_partition[worstIndex].part_status = '0';
                        strcpy(masterboot.mbr_partition[worstIndex].part_name,nombre.toStdString().c_str());
                        //Se guarda de nuevo el MBR
                        fseek(fp,0,SEEK_SET);
                        fwrite(&masterboot,sizeof(MBR),1,fp);
                        //Se guardan los bytes de la particion
                        fseek(fp,masterboot.mbr_partition[worstIndex].part_start,SEEK_SET);
                        for(int i = 0; i < size_bytes; i++){
                            fwrite(&buffer,1,1,fp);
                        }
                        if(archivo == "principal") cout << "...\n" << "\033[96mParticion primaria creada con exito.\033[0m" <<  endl;
                    }
                }else{
                    cout << "\033[31mERROR: ya existe una particion con ese nombre.\033[0m" << endl;
                }

            }else{
                cout << "\033[31mERROR: la particion a crear excede el espacio libre.\033[0m" << endl;
            }
        }else{
            cout << "\033[31mERROR: Ya existen 4 particiones, no se puede crear otra" << endl;
            cout << "Elimine alguna para poder crear una.\033[0m" << endl;
        }
    fclose(fp);
    }else{
        cout << "\033[31mERROR: no existe el disco.\033[0m" << endl;
    }
}


void comando_fdisk::crearParticionExtendida(QString direccion, QString nombre, int size, QString fit, string unit, QString archivo){
    char auxFit = 0;
    char auxUnit = 0;
    string auxPath = direccion.toStdString();
    int size_bytes = 1024;
    char buffer = '1';

    if(fit=="bf"){
        auxFit='B';
    }
    else if(fit=="ff"){
        auxFit='F';
    }
    else if(fit=="wf"){
        auxFit='W';
    }

    if(unit=="b"){
        auxUnit='b';
        size_bytes = size;
    }
    else if(unit=="k"){
        auxUnit='k';
        size_bytes = size * 1024;
    }
    else if(unit=="m"){
        auxUnit='m';
        size_bytes = size*1024*1024;
    }
    FILE *fp;
    MBR masterboot;
    if((fp = fopen(auxPath.c_str(), "rb+"))){
        bool flagParticion = false;//Flag para ver si hay una particion disponible
        bool flagExtendida = false;//Flag para ver si ya hay una particion extendida
        int numParticion = 0;//Que numero de particion es
        fseek(fp,0,SEEK_SET);
        fread(&masterboot,sizeof(MBR),1,fp);
        for(int i = 0; i < 4; i++){
            if (masterboot.mbr_partition[i].part_type == 'E'){
                flagExtendida = true;
                break;
            }
        }
        if(!flagExtendida){
            //Verificar si existe una particion disponible
            for(int i = 0; i < 4; i++){
                if(masterboot.mbr_partition[i].part_start == -1 || (masterboot.mbr_partition[i].part_status == '1' && masterboot.mbr_partition[i].part_size>=size_bytes)){
                    flagParticion = true;
                    numParticion = i;
                    break;
                }
            }
            if(flagParticion){
                //Verificar el espacio libre del disco
                int espacioUsado = 0;
                for(int i = 0; i < 4; i++){
                    if(masterboot.mbr_partition[i].part_status!='1'){
                       espacioUsado += masterboot.mbr_partition[i].part_size;
                    }
                }
                if(archivo == "principal"){
                    cout << "Espacio disponible: " << (masterboot.mbr_size - espacioUsado) <<" Bytes"<< endl;
                    cout << "Espacio Requerido:  " << size_bytes << " Bytes" << endl;
                }
                //Verificar que haya espacio suficiente para crear la particion
                if((masterboot.mbr_size - espacioUsado) >= size_bytes){
                    if(!(existeParticion(direccion,nombre))){
                        if(masterboot.mbr_disk_fit == 'F'){
                            masterboot.mbr_partition[numParticion].part_type = 'E';
                            masterboot.mbr_partition[numParticion].part_fit = auxFit;
                            //start
                            if(numParticion == 0){
                                masterboot.mbr_partition[numParticion].part_start = sizeof(masterboot);
                            }else{
                                masterboot.mbr_partition[numParticion].part_start =  masterboot.mbr_partition[numParticion-1].part_start + masterboot.mbr_partition[numParticion-1].part_size;
                            }
                            masterboot.mbr_partition[numParticion].part_size = size_bytes;
                            masterboot.mbr_partition[numParticion].part_status = '0';
                            strcpy(masterboot.mbr_partition[numParticion].part_name,nombre.toStdString().c_str());
                            //Se guarda de nuevo el MBR
                            fseek(fp,0,SEEK_SET);
                            fwrite(&masterboot,sizeof(MBR),1,fp);
                            //Se guarda la particion extendida
                            fseek(fp, masterboot.mbr_partition[numParticion].part_start,SEEK_SET);
                            EBR extendedBoot;
                            extendedBoot.part_fit = auxFit;
                            extendedBoot.part_status = '0';
                            extendedBoot.part_start = masterboot.mbr_partition[numParticion].part_start;
                            extendedBoot.part_size = 0;
                            extendedBoot.part_next = -1;
                            strcpy(extendedBoot.part_name, "");
                            fwrite(&extendedBoot,sizeof (EBR),1,fp);
                            for(int i = 0; i < (size_bytes - (int)sizeof(EBR)); i++){
                                fwrite(&buffer,1,1,fp);
                            }
                            if(archivo == "principal") cout << "Ejecutando...\n" << "\033[96mParticion extendida creada con exito.\033[0m"<< endl;
                        }else if(masterboot.mbr_disk_fit == 'B'){
                            int bestIndex = numParticion;
                            for(int i = 0; i < 4; i++){
                                if(masterboot.mbr_partition[i].part_start == -1 || (masterboot.mbr_partition[i].part_status == '1' && masterboot.mbr_partition[i].part_size>=size_bytes)){
                                    if(i != numParticion){
                                        if(masterboot.mbr_partition[bestIndex].part_size > masterboot.mbr_partition[i].part_size){
                                            bestIndex = i;
                                            break;
                                        }
                                    }
                                }
                            }
                            masterboot.mbr_partition[bestIndex].part_type = 'E';
                            masterboot.mbr_partition[bestIndex].part_fit = auxFit;
                            //start
                            if(bestIndex == 0){
                                masterboot.mbr_partition[bestIndex].part_start = sizeof(masterboot);
                            }else{
                                masterboot.mbr_partition[bestIndex].part_start =  masterboot.mbr_partition[bestIndex-1].part_start + masterboot.mbr_partition[bestIndex-1].part_size;
                            }
                            masterboot.mbr_partition[bestIndex].part_size = size_bytes;
                            masterboot.mbr_partition[bestIndex].part_status = '0';
                            strcpy(masterboot.mbr_partition[bestIndex].part_name,nombre.toStdString().c_str());
                            //Se guarda de nuevo el MBR
                            fseek(fp,0,SEEK_SET);
                            fwrite(&masterboot,sizeof(MBR),1,fp);
                            //Se guarda la particion extendida
                            fseek(fp, masterboot.mbr_partition[bestIndex].part_start,SEEK_SET);
                            EBR extendedBoot;
                            extendedBoot.part_fit = auxFit;
                            extendedBoot.part_status = '0';
                            extendedBoot.part_start = masterboot.mbr_partition[bestIndex].part_start;
                            extendedBoot.part_size = 0;
                            extendedBoot.part_next = -1;
                            strcpy(extendedBoot.part_name, "");
                            fwrite(&extendedBoot,sizeof (EBR),1,fp);
                            for(int i = 0; i < (size_bytes - (int)sizeof(EBR)); i++){
                                fwrite(&buffer,1,1,fp);
                            }
                            if(archivo == "principal") cout << "Ejecutando...\n" << "\033[96mParticion extendida creada con exito.\033[0m"<< endl;
                        }else if(masterboot.mbr_disk_fit == 'W'){
                            int  worstIndex= numParticion;
                            for(int i = 0; i < 4; i++){
                                if(masterboot.mbr_partition[i].part_start == -1 || (masterboot.mbr_partition[i].part_status == '1' && masterboot.mbr_partition[i].part_size>=size_bytes)){
                                    if(i != numParticion){
                                        if(masterboot.mbr_partition[worstIndex].part_size < masterboot.mbr_partition[i].part_size){
                                            worstIndex = i;
                                            break;
                                        }
                                    }
                                }
                            }
                            masterboot.mbr_partition[worstIndex].part_type = 'E';
                            masterboot.mbr_partition[worstIndex].part_fit = auxFit;
                            //start
                            if(worstIndex == 0){
                                masterboot.mbr_partition[worstIndex].part_start = sizeof(masterboot);
                            }else{
                                masterboot.mbr_partition[worstIndex].part_start =  masterboot.mbr_partition[worstIndex-1].part_start + masterboot.mbr_partition[worstIndex-1].part_size;
                            }
                            masterboot.mbr_partition[worstIndex].part_size = size_bytes;
                            masterboot.mbr_partition[worstIndex].part_status = '0';
                            strcpy(masterboot.mbr_partition[worstIndex].part_name,nombre.toStdString().c_str());
                            //Se guarda de nuevo el MBR
                            fseek(fp,0,SEEK_SET);
                            fwrite(&masterboot,sizeof(MBR),1,fp);
                            //Se guarda la particion extendida
                            fseek(fp, masterboot.mbr_partition[worstIndex].part_start,SEEK_SET);
                            EBR extendedBoot;
                            extendedBoot.part_fit = auxFit;
                            extendedBoot.part_status = '0';
                            extendedBoot.part_start = masterboot.mbr_partition[worstIndex].part_start;
                            extendedBoot.part_size = 0;
                            extendedBoot.part_next = -1;
                            strcpy(extendedBoot.part_name, "");
                            fwrite(&extendedBoot,sizeof (EBR),1,fp);
                            for(int i = 0; i < (size_bytes - (int)sizeof(EBR)); i++){
                                fwrite(&buffer,1,1,fp);
                            }
                            if(archivo == "principal") cout << "Ejecutando...\n" << "\033[96mParticion extendida creada con exito.\033[0m"<< endl;
                        }
                    }else{
                        cout << "\033[31mERROR: ya existe una particion con ese nombre.\033[0m" << endl;
                    }
                }else{
                    cout << "\033[31mERROR: la particion a crear excede el tamano libre.\033[0m" << endl;
                }
            }else{
                cout << "\033[31mERROR: Ya existen 4 particiones, no se puede crear otra." << endl;
                cout << "Elimine alguna para poder crear una.\033[0m" << endl;
            }
        }else{
            cout << "\033[31mERROR: ya existe una particion extendida en este disco.\033[0m" << endl;
        }
    fclose(fp);
    }else{
        cout << "\033[31mERROR: no existe el disco.\033[0m" << endl;
    }

}



void comando_fdisk::crearParticionLogica(QString direccion, QString nombre, int size, QString fit, string unit, QString archivo){
    char auxFit = 0;
    char auxUnit = 0;
    string auxPath = direccion.toStdString();
    int size_bytes = 1024;
    char buffer = '1';

    if(fit=="bf"){
        auxFit='B';
    }
    else if(fit=="ff"){
        auxFit='F';
    }
    else if(fit=="wf"){
        auxFit='W';
    }

    if(unit=="b"){
        auxUnit='b';
        size_bytes = size;
    }
    else if(unit=="k"){
        auxUnit='k';
        size_bytes = size * 1024;
    }
    else if(unit=="m"){
        auxUnit='m';
        size_bytes = size*1024*1024;
    }

    FILE *fp;
    MBR masterboot;
    if((fp = fopen(auxPath.c_str(), "rb+"))){
        int numExtendida = -1;
        fseek(fp,0,SEEK_SET);
        fread(&masterboot,sizeof(MBR),1,fp);
        //Verificar si existe una particion extendida
        for(int i = 0; i < 4; i++){
            if(masterboot.mbr_partition[i].part_type == 'E'){
                numExtendida = i;
                break;
            }
        }
        if(!existeParticion(direccion,nombre)){
            if(numExtendida != -1){
                EBR extendedBoot;
                int cont = masterboot.mbr_partition[numExtendida].part_start;
                fseek(fp,cont,SEEK_SET);
                fread(&extendedBoot, sizeof(EBR),1,fp);
                if(extendedBoot.part_size == 0){//Si es la primera
                    if(masterboot.mbr_partition[numExtendida].part_size < size_bytes){
                        if(archivo == "principal") cout << "\033[31mERROR: la particion logica a crear excede el espacio disponible de la particion extendida.\033[0m" << endl;
                    }else{
                        extendedBoot.part_status = '0';
                        extendedBoot.part_fit = auxFit;
                        extendedBoot.part_start = ftell(fp) - sizeof(EBR); //Para regresar al inicio de la extendida
                        extendedBoot.part_size = size_bytes;
                        extendedBoot.part_next = -1;
                        strcpy(extendedBoot.part_name, nombre.toStdString().c_str());
                        fseek(fp, masterboot.mbr_partition[numExtendida].part_start ,SEEK_SET);
                        fwrite(&extendedBoot,sizeof(EBR),1,fp);
                        if(archivo == "principal") cout << "Ejecutando...\n\033[96mParticion logica creada con exito.\033[0m"<< endl;
                    }
                }else{
                    while((extendedBoot.part_next != -1) && (ftell(fp) < (masterboot.mbr_partition[numExtendida].part_size + masterboot.mbr_partition[numExtendida].part_start))){
                        fseek(fp,extendedBoot.part_next,SEEK_SET);
                        fread(&extendedBoot,sizeof(EBR),1,fp);
                    }
                    int espacioNecesario = extendedBoot.part_start + extendedBoot.part_size + size_bytes;
                    if(espacioNecesario <= (masterboot.mbr_partition[numExtendida].part_size + masterboot.mbr_partition[numExtendida].part_start)){
                        extendedBoot.part_next = extendedBoot.part_start + extendedBoot.part_size;
                        //Escribimos el next del ultimo EBR
                        fseek(fp,ftell(fp) - sizeof (EBR),SEEK_SET);
                        fwrite(&extendedBoot, sizeof(EBR),1 ,fp);
                        //Escribimos el nuevo EBR
                        fseek(fp,extendedBoot.part_start + extendedBoot.part_size, SEEK_SET);
                        extendedBoot.part_status = 0;
                        extendedBoot.part_fit = auxFit;
                        extendedBoot.part_start = ftell(fp);
                        extendedBoot.part_size = size_bytes;
                        extendedBoot.part_next = -1;
                        strcpy(extendedBoot.part_name,nombre.toStdString().c_str());
                        fwrite(&extendedBoot,sizeof(EBR),1,fp);
                        if(archivo == "principal") cout << "\033[96mParticion logica creada con exito.\033[0m"<< endl;
                    }else{
                        cout << "\033[31mERROR: la particion logica a crear excede el" << endl;
                        cout << "espacio disponible de la particion extendida.\033[0m" << endl;
                    }
                }
            }else{
                cout << "\033[31mERROR: se necesita una particion extendida donde guardar la logica.\033[0m" << endl;
            }
        }else{
            cout << "\033[31mERROR: ya existe una particion con ese nombre.\033[0m" << endl;
        }

    fclose(fp);
    }else{
        cout << "\033[31mERROR: no existe el disco.\033[0m" << endl;
    }


}


void comando_fdisk::agregarQuitarParticion(QString direccion, QString nombre, int add, char unit, QString archivo){
    string auxPath = direccion.toStdString();
    string auxNombre = nombre.toStdString();
    int size_Bytes = 0;
    QString tipo = "";

    if(add > 0)
        tipo = "add";

    if(tipo != "add")
        add = add*(-1);

    if(unit == 'm')
        size_Bytes = add * 1024 * 1024;
    else if(unit == 'k')
        size_Bytes = add * 1024;
    else
        size_Bytes = add;

    FILE *fp;
    if((fp = fopen(auxPath.c_str(), "rb+"))){
        //Verificar que la particion no este montada
        bool mount = lista->buscarNodo(direccion,nombre);
        if(!mount){
            MBR masterboot;
            fseek(fp,0,SEEK_SET);
            fread(&masterboot,sizeof(MBR),1,fp);
            int index = -1;
            int index_Extendida = -1;
            bool flagExtendida = false;
            //Buscamos la particion primaria/extendida
            for(int i = 0; i < 4; i++){
                if((strcmp(masterboot.mbr_partition[i].part_name, auxNombre.c_str())) == 0){
                    index = i;
                    if(masterboot.mbr_partition[i].part_type == 'E')
                        flagExtendida = true;
                    break;
                }else if(masterboot.mbr_partition[i].part_type == 'E'){
                    index_Extendida = i;
                }
            }
            if(index != -1){//Si se encontro en las principales
                if(!flagExtendida){//Primaria
                    if(tipo == "add"){//Agregar
                        //Verificar que exista espacio libre a la derecha
                        if(index!=3){
                            int p1 = masterboot.mbr_partition[index].part_start + masterboot.mbr_partition[index].part_size;
                            int p2 = masterboot.mbr_partition[index+1].part_start;
                            if((p2 - p1) != 0){//Hay fragmentacion
                                int fragmentacion = p2-p1;
                                if(fragmentacion >= size_Bytes){
                                    masterboot.mbr_partition[index].part_size = masterboot.mbr_partition[index].part_size + size_Bytes;
                                    fseek(fp,0,SEEK_SET);
                                    fwrite(&masterboot,sizeof(MBR),1,fp);
                                    if(archivo == "principal") cout << "\033[96mSe agrego espacio a la particion de manera exitosa.\033[0m" << endl;
                                }else{
                                    cout << "\033[31mERROR: no es posible agregar espacio a la particion porque no hay suficiente espacio disponible a su derecha.\033[0m" << endl;
                                }
                            }else{//Espacio no usado
                                if(masterboot.mbr_partition[index + 1].part_status == '1'){
                                    if(masterboot.mbr_partition[index + 1].part_size >= size_Bytes){
                                        masterboot.mbr_partition[index].part_size = masterboot.mbr_partition[index].part_size + size_Bytes;
                                        masterboot.mbr_partition[index + 1].part_size = (masterboot.mbr_partition[index + 1].part_size - size_Bytes);
                                        masterboot.mbr_partition[index + 1].part_start = masterboot.mbr_partition[index + 1].part_start + size_Bytes;
                                        fseek(fp,0,SEEK_SET);
                                        fwrite(&masterboot,sizeof(MBR),1,fp);
                                        if(archivo == "principal") cout << "\033[96mSe agrego espacio a la particion de manera exitosa.\033[0m" << endl;
                                    }else{
                                        cout << "\033[31mERROR: no es posible agregar espacio a la particion porque no hay suficiente espacio disponible a su derecha.\033[0m" << endl;
                                    }
                                }
                            }
                        }else{
                            int p = masterboot.mbr_partition[index].part_start + masterboot.mbr_partition[index].part_size;
                            int total = masterboot.mbr_size + (int)sizeof(MBR);
                            if((total-p) != 0){
                                int fragmentacion = total - p;
                                if(fragmentacion >= size_Bytes){
                                    masterboot.mbr_partition[index].part_size = masterboot.mbr_partition[index].part_size + size_Bytes;
                                    fseek(fp,0,SEEK_SET);
                                    fwrite(&masterboot,sizeof(MBR),1,fp);
                                    if(archivo == "principal") cout << "\033[96mSe agrego espacio a la particion de manera exitosa.\033[0m" << endl;
                                }else{
                                    cout << "\033[31mERROR: no es posible agregar espacio a la particion porque no hay suficiente espacio disponible a su derecha.\033[0m" << endl;
                                }
                            }else{
                                cout << "\033[31mERROR: no es posible agregar espacio a la particion porque no hay espacio disponible a su derecha.\033[0m" << endl;
                            }
                        }
                    }else{//Quitar espacio
                        //Que no borre la particion
                        if(size_Bytes >= masterboot.mbr_partition[index].part_size){
                            cout << "\033[31mERROR: no es posible quitarle esta cantidad de espacio a la particion porque la borraria.\033[0m" << endl;
                        }else{
                            masterboot.mbr_partition[index].part_size = masterboot.mbr_partition[index].part_size - size_Bytes;
                            fseek(fp,0,SEEK_SET);
                            fwrite(&masterboot,sizeof(MBR),1,fp);
                            if(archivo == "principal") cout << "\033[96mSe quito espacio a la particion de manera exitosa.\033[0m" << endl;
                        }
                    }
                }else{//Extendida
                    if(tipo == "add"){//Agregar
                        //Verificar que exista espacio libre a la derecha
                        if(index!=3){
                            int p1 = masterboot.mbr_partition[index].part_start + masterboot.mbr_partition[index].part_size;
                            int p2 = masterboot.mbr_partition[index+1].part_start;
                            if((p2 - p1) != 0){//Hay fragmentacion
                                int fragmentacion = p2-p1;
                                if(fragmentacion >= size_Bytes){
                                    masterboot.mbr_partition[index].part_size = masterboot.mbr_partition[index].part_size + size_Bytes;
                                    fseek(fp,0,SEEK_SET);
                                    fwrite(&masterboot,sizeof(MBR),1,fp);
                                    if(archivo == "principal") cout << "\033[96mSe agrego espacio a la particion de manera exitosa.\033[0m" << endl;
                                }else{
                                    cout << "\033[31mERROR: no es posible agregar espacio a la particion porque no hay suficiente espacio disponible a su derecha.\033[0m" << endl;
                                }
                            }else{
                                if(masterboot.mbr_partition[index + 1].part_status == '1'){
                                    if(masterboot.mbr_partition[index + 1].part_size >= size_Bytes){
                                        masterboot.mbr_partition[index].part_size = masterboot.mbr_partition[index].part_size + size_Bytes;
                                        masterboot.mbr_partition[index + 1].part_size = (masterboot.mbr_partition[index + 1].part_size - size_Bytes);
                                        masterboot.mbr_partition[index + 1].part_start = masterboot.mbr_partition[index + 1].part_start + size_Bytes;
                                        fseek(fp,0,SEEK_SET);
                                        fwrite(&masterboot,sizeof(MBR),1,fp);
                                        if(archivo == "principal") cout << "\033[96mSe agrego espacio a la particion de manera exitosa.\033[0m" << endl;
                                    }else{
                                        cout << "\033[31mERROR: no es posible agregar espacio a la particion porque no hay suficiente espacio disponible a su derecha.\033[0m" << endl;
                                    }
                                }
                            }
                        }else{
                            int p = masterboot.mbr_partition[index].part_start + masterboot.mbr_partition[index].part_size;
                            int total = masterboot.mbr_size + (int)sizeof(MBR);
                            if((total-p) != 0){//Hay fragmentacion
                                int fragmentacion = total - p;
                                if(fragmentacion >= size_Bytes){
                                    masterboot.mbr_partition[index].part_size = masterboot.mbr_partition[index].part_size + size_Bytes;
                                    fseek(fp,0,SEEK_SET);
                                    fwrite(&masterboot,sizeof(MBR),1,fp);
                                    if(archivo == "principal") cout << "\033[96mSe agrego espacio a la particion de manera exitosa.\033[0m" << endl;
                                }else{
                                    cout << "\033[31mERROR: no es posible agregar espacio a la particion porque no hay suficiente espacio disponible a su derecha.\033[0m" << endl;
                                }
                            }else{
                                cout << "\033[31mERROR: no es posible agregar espacio a la particion porque no hay espacio disponible a su derecha.\033[0m" << endl;
                            }
                        }
                    }else{//Quitar espacio
                        //Que no borre la particion
                        if(size_Bytes >= masterboot.mbr_partition[index_Extendida].part_size){
                            cout << "\033[31mERROR: no es posible quitarle esta cantidad de espacio a la particion porque la borraria.\033[0m" << endl;
                        }else{
                            EBR extendedBoot;
                            fseek(fp, masterboot.mbr_partition[index_Extendida].part_start,SEEK_SET);
                            fread(&extendedBoot,sizeof(EBR),1,fp);
                            while((extendedBoot.part_next != -1) && (ftell(fp) < (masterboot.mbr_partition[index_Extendida].part_size + masterboot.mbr_partition[index_Extendida].part_start))){
                                fseek(fp,extendedBoot.part_next,SEEK_SET);
                                fread(&extendedBoot,sizeof(EBR),1,fp);
                            }
                            int ultimaLogica = extendedBoot.part_start+extendedBoot.part_size;
                            int aux = (masterboot.mbr_partition[index_Extendida].part_start + masterboot.mbr_partition[index_Extendida].part_size) - size_Bytes;
                            if(aux > ultimaLogica){//No toca ninguna logica
                                masterboot.mbr_partition[index_Extendida].part_size = masterboot.mbr_partition[index_Extendida].part_size - size_Bytes;
                                fseek(fp,0,SEEK_SET);
                                fwrite(&masterboot,sizeof(MBR),1,fp);
                                if(archivo == "principal") cout << "\033[96mSe quito espacio a la particion de manera exitosa.\033[0m" << endl;
                            }else{
                                cout << "\033[31mERROR: si quita ese espacio danaria una logica.\033[0m" << endl;
                            }
                        }
                    }
                }
            }else{//Posiblemente logica
                if(index_Extendida != -1){
                    int logica = buscarParticion_L(direccion, nombre);
                    if(logica != -1){
                        if(tipo == "add"){
                            //Verificar que exista espacio libre a su derecha
                            EBR extendedBoot;
                            fseek(fp,logica,SEEK_SET);
                            fread(&extendedBoot,sizeof(EBR),1,fp);

                        }else{//Quitar
                            //Verificar que no la elimine
                            EBR extendedBoot;
                            fseek(fp,logica,SEEK_SET);
                            fread(&extendedBoot,sizeof(EBR),1,fp);
                            if(size_Bytes >= extendedBoot.part_size){
                                cout << "\033[31mERROR: si quita ese espacio eliminaria la logica.\033[0m" << endl;
                            }else{
                                extendedBoot.part_size = extendedBoot.part_size - size_Bytes;
                                fseek(fp,logica,SEEK_SET);
                                fwrite(&extendedBoot,sizeof(EBR),1,fp);
                                if(archivo == "principal") cout << "\033[96mSe quito espacio a la particion de manera exitosa.\033[0m" << endl;
                            }
                        }
                    }else{
                        cout << "\033[31mERROR: no se encuentra la particion.\033[0m" << endl;
                    }
                }else{
                    cout << "\033[31mERROR: no se encuentra la particion a redimensionar.\033[0m" << endl;
                }
            }
        }else{
             cout << "\033[31mERROR: desmonte primero la particion para poder redimensionar.\033[0m" << endl;
        }
    fclose(fp);
    }else{
        cout << "\033[31mERROR: el disco donde se desea agregar/quitar unidades no existe.\033[0m" << endl;
    }
}


bool comando_fdisk::existeParticion(QString path, QString name){
    //\'"+aux.toStdString()+"\'
    int extendida = -1;
    FILE *fp;
    if((fp = fopen(path.toStdString().c_str(),"rb+"))){
        MBR masterboot;
        fseek(fp,0,SEEK_SET);
        fread(&masterboot, sizeof(MBR),1,fp);
        for(int i = 0; i < 4; i++){
            if(strcmp(masterboot.mbr_partition[i].part_name,name.toStdString().c_str()) == 0){
                fclose(fp);
                return true;
            }else if(masterboot.mbr_partition[i].part_type == 'E'){
                extendida = i;
            }
        }
        if(extendida != -1){
            fseek(fp, masterboot.mbr_partition[extendida].part_start,SEEK_SET);
            EBR extendedBoot;
            while((fread(&extendedBoot,sizeof(EBR),1,fp))!=0 && (ftell(fp) < (masterboot.mbr_partition[extendida].part_size + masterboot.mbr_partition[extendida].part_start))){
                if(strcmp(extendedBoot.part_name,name.toStdString().c_str()) == 0){
                    fclose(fp);
                    return true;
                }
                if(extendedBoot.part_next == -1){
                    fclose(fp);
                    return false;
                }
            }
        }
    }
    fclose(fp);
    return false;
}

int comando_fdisk::buscarnombrelogica(QString name, int inicioextend, QString path){
    EBR tmp = devolversiguienteebr(inicioextend, path);
    while(tmp.part_name[0] != '\0'){
        if(name.compare(tmp.part_name) == 0)
            return 1;
        if(tmp.part_next == -1){
            //std::cout << "EL PARTNEXT ES -1  ";

            return 0;
        }
         //  std::cout << "Buscar nombre logica inicio del otro ebr es : "<<std::to_string(tmp.part_next);
        //contadorlogicas++;
        tmp = devolversiguienteebr(tmp.part_next, path);
    }
    return 0;
}


EBR comando_fdisk::devolversiguienteebr(int inicio, QString path){
    EBR tmp;//inicializamos este struct por que puede que no entre al disco
    tmp.part_size=-1;
    //buscamos el struct escrito en el disco, este struct simula la particion extendida
    FILE* archivo = fopen(path.toStdString().c_str(), "rb+");
    if(archivo != NULL){
        //nos ubicamos donde inicia la extendida del disco o archivo .disk
        fseek(archivo, inicio, SEEK_SET);
        //el fread recorre el archivo en busca del struct
        fread(&tmp, sizeof(EBR), 1, archivo);
        fclose(archivo);
    }else{
        cout<< "\033[93mNo se puede acceder al disco. \033[0m"<<endl;
        return tmp;
    }
    return tmp;
}


int comando_fdisk::buscarParticion_L(QString direccion, QString nombre){
    string auxPath = direccion.toStdString();
    string auxName = nombre.toStdString();
    FILE *fp;
    if((fp = fopen(auxPath.c_str(),"rb+"))){
        int extendida = -1;
        MBR masterboot;
        fseek(fp,0,SEEK_SET);
        fread(&masterboot,sizeof(MBR),1,fp);
        for(int i = 0; i < 4; i++){
            if(masterboot.mbr_partition[i].part_type == 'E'){
                extendida = i;
                break;
            }
        }
        if(extendida != -1){
            EBR extendedBoot;
            fseek(fp, masterboot.mbr_partition[extendida].part_start,SEEK_SET);
            while(fread(&extendedBoot,sizeof(EBR),1,fp)!=0 && (ftell(fp) < masterboot.mbr_partition[extendida].part_start + masterboot.mbr_partition[extendida].part_size)){
                if(strcmp(extendedBoot.part_name, auxName.c_str()) == 0){
                    return (ftell(fp) - sizeof(EBR));
                }
            }
        }
        fclose(fp);
    }
    return -1;
}

void comando_fdisk::eliminarParticion(QString direccion, QString nombre, QString typeDelete, QString archivo){
    string auxPath = direccion.toStdString();
    string auxNombre = nombre.toStdString();
    FILE *fp;
    if((fp = fopen(auxPath.c_str(), "rb+"))){
        //Verificar que la particion no este montada
        bool mount = lista->buscarNodo(direccion,nombre);
        if(!mount){
            MBR masterboot;
            fseek(fp,0,SEEK_SET);
            fread(&masterboot,sizeof (MBR),1,fp);
            int index = -1;
            int index_Extendida = -1;
            bool flagExtendida = false;
            //string opcion = "";
            char buffer = '\0';
            //Buscamos la particion primaria/extendida
            for(int i = 0; i < 4; i++){
                if((strcmp(masterboot.mbr_partition[i].part_name, auxNombre.c_str())) == 0){
                    index = i;
                    if(masterboot.mbr_partition[i].part_type == 'E')
                        flagExtendida = true;
                    break;
                }else if(masterboot.mbr_partition[i].part_type == 'E'){
                    index_Extendida = i;
                }
            }
            //ELIMINA LAS PARTICIONES SI NO ESTAN MONTADAS
                if(index != -1){//Si se encontro en las principales
                    if(!flagExtendida){//primaria
                        if(typeDelete == "fast"){
                            masterboot.mbr_partition[index].part_status = '1';
                            strcpy(masterboot.mbr_partition[index].part_name,"");
                            fseek(fp,0,SEEK_SET);
                            fwrite(&masterboot,sizeof(MBR),1,fp);
                            if(archivo == "principal") cout << "\033[96mParticion primaria eliminada con exito.\033[0m" << endl;

                        }else{//full
                            masterboot.mbr_partition[index].part_status = '1';
                            strcpy(masterboot.mbr_partition[index].part_name,"");
                            fseek(fp,0,SEEK_SET);
                            fwrite(&masterboot,sizeof(MBR),1,fp);
                            fseek(fp,masterboot.mbr_partition[index].part_start,SEEK_SET);
                            fwrite(&buffer,1,masterboot.mbr_partition[index].part_size,fp);
                            if(archivo == "principal") cout << "\033[96mParticion primaria eliminada con exito.\033[0m" << endl;
                        }
                    }else{//extendida
                        if(typeDelete == "fast"){
                            masterboot.mbr_partition[index].part_status = '1';
                            strcpy(masterboot.mbr_partition[index].part_name,"");
                            fseek(fp,0,SEEK_SET);
                            fwrite(&masterboot,sizeof(MBR),1,fp);
                            if(archivo == "principal") cout << "\033[96mParticion extendida eliminada con exito.\033[0m" << endl;
                        }else{//full
                            masterboot.mbr_partition[index].part_status = '1';
                            strcpy(masterboot.mbr_partition[index].part_name,"");
                            fseek(fp,0,SEEK_SET);
                            fwrite(&masterboot,sizeof(MBR),1,fp);
                            fseek(fp,masterboot.mbr_partition[index].part_start,SEEK_SET);
                            fwrite(&buffer,1,masterboot.mbr_partition[index].part_size,fp);
                            if(archivo == "principal") cout << "\033[96mParticion extendida eliminada con exito.\033[0m" << endl;
                        }
                    }
                }else{//Si es una particion logica
                    if(index_Extendida != -1){
                        bool flag = false;//Bandera para saber si existe
                        EBR extendedBoot;
                        fseek(fp,masterboot.mbr_partition[index_Extendida].part_start, SEEK_SET);
                        fread(&extendedBoot,sizeof(EBR),1,fp);
                        if(extendedBoot.part_size!=0){
                            fseek(fp, masterboot.mbr_partition[index_Extendida].part_start,SEEK_SET);
                            while((fread(&extendedBoot,sizeof(EBR),1,fp))!=0 && (ftell(fp) < (masterboot.mbr_partition[index_Extendida].part_start + masterboot.mbr_partition[index_Extendida].part_size))) {
                                if(strcmp(extendedBoot.part_name,nombre.toStdString().c_str()) == 0 && extendedBoot.part_status != '1'){
                                    flag = true;
                                    break;
                                }else if(extendedBoot.part_next == -1){//Ya es la ultima y no se encontro
                                    break;
                                }
                            }
                        }
                        if(flag){
                            if(typeDelete == "fast"){
                                extendedBoot.part_status = '1';
                                strcpy(extendedBoot.part_name, "");
                                fseek(fp, ftell(fp)-sizeof(EBR),SEEK_SET);
                                fwrite(&extendedBoot,sizeof(EBR),1,fp);
                                if(archivo == "principal") cout << "\033[96mParticion logica eliminada con exito.\033[0m" << endl;
                            }else{//full
                                extendedBoot.part_status = '1';
                                strcpy(extendedBoot.part_name, "");
                                fseek(fp, ftell(fp)-sizeof(EBR),SEEK_SET);
                                fwrite(&extendedBoot,sizeof(EBR),1,fp);
                                fwrite(&buffer,1,extendedBoot.part_size,fp);
                                if(archivo == "principal") cout << "\033[96mParticion logica eliminada con exito.\033[0m" << endl;
                            }
                        }else{
                            cout << "\033[31mERROR: no se encuentra la particion a eliminar.\033[0m" << endl;
                        }
                    }else{
                        cout << "\033[31mERROR: no se encuentra la particion a eliminar.\033[0m" << endl;
                    }
                }


        }else{
            cout << "\033[31mERROR: desmote primero la particion para poder eliminarlo.\033[0m" << endl;
        }
    fclose(fp);
    }else{
        cout << "\033[31mERROR: el disco donde se va a eliminar no existe.\033[0m" << endl;
    }
}




string comando_fdisk::ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

bool comando_fdisk::existe_archivo(QString path){
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}





