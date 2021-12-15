#include "comando_mkdisk.h"

#include <algorithm>
#include <string>

using namespace std;
comando_mkdisk::comando_mkdisk()
{

}

void comando_mkdisk::ast_mkdisk(Nodo_arbol *raiz){
    string log_error="";
    //VALORES DE CADA PARAMETRO
    bool berror=false;

    bool bsize=false;
    bool bpath=false;
    int vsize=0;
    string vfit="bf";
    string vunit="m";
    QString vpath="";
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
        else if(temp.tipo_==FIT){
            vfit=temp.hijos.at(0).valor.toStdString();
        }
        else if(temp.tipo_==UNIT){
            vunit=temp.hijos.at(0).valor.toStdString();
            if(vunit.compare("b")==0){
                berror=true;
                log_error+="-unit="+vunit + ", Las unidades permitidas son k y m.";
            }
        }
        else if(temp.tipo_==PATH){
            bpath=true;
            string prueba=temp.valor.toStdString();
            prueba=ReplaceAll(prueba, std::string("\""), std::string(""));
            vpath=QString::fromStdString(prueba);
            //vpath=temp.valor;
        }
    }
    if(!bsize){
        berror=true;
        log_error+="Parametro size es Obligatorio.\n";
    }
    if(!bpath){
        berror=true;
        log_error+="Parametro path es Obligatorio.\n";
    }
    if(!berror){
        //cout<<"COMANDO EJECUTADO CORRECTAMENTE."<<endl;
        //cout<<vsize<<" "<<vfit<<" "<<vunit<<" "<<vpath<<endl;
        ejecuta_mkdisk(vsize,vfit,vunit,vpath);


    }else{
        cout<<"\033[31mEL COMANDO CONTIENE ERRORES: "<<endl;
        cout<<log_error<<"\033[0m"<<endl;
    }

}

void comando_mkdisk::ejecuta_mkdisk(int psize, string pfit, string punit, QString ppath){



    MBR masterboot;
    int total_size = 1024;
    //CREAR DISCO PRINCIPAL
    crear_disco(ppath);
    //INSERTAR FECHA EN EL MBR
    masterboot.mbr_date_created = time(nullptr);//-------
    masterboot.mbr_disk_signature = (int)time(nullptr);//--------
    //LLENAR STRUCT MBR
    //UNIT
    if(punit=="m"){
        masterboot.mbr_size = psize*1048576;
        total_size = psize * 1024;
    }else{
        masterboot.mbr_size = psize * 1024;
        total_size = psize;
    }

    char auxFit=0;
    if(pfit=="bf"){
        auxFit='B';
    }
    else if(pfit=="ff"){
        auxFit='F';
    }
    else if(pfit=="wf"){
        auxFit='W';
    }

    //FIT
    masterboot.mbr_disk_fit = auxFit;
    //INICIALIZAR las mbr_partition en el MBR
    for(int p = 0; p < 4; p++){
        masterboot.mbr_partition[p].part_status = '0';
        masterboot.mbr_partition[p].part_type = '0';
        masterboot.mbr_partition[p].part_fit = '0';
        masterboot.mbr_partition[p].part_size = 0;
        masterboot.mbr_partition[p].part_start = -1;
        strcpy(masterboot.mbr_partition[p].part_name,"");
    }

    //DISCO PRINCIPAL
    //Comando para genera un archivo de cierto tamano
    string comando = "dd if=/dev/zero of=\""+ppath.toStdString()+"\" bs=1024 count="+to_string(total_size);
    system(comando.c_str());
    FILE *archivo = fopen(ppath.toStdString().c_str(),"rb+");
    fseek(archivo,0,SEEK_SET);
    fwrite(&masterboot,sizeof(MBR),1,archivo);
    fclose(archivo);


    cout << endl;
    cout << "\033[96mDisco creado Exitosamente.\033[0m" << endl;


}

void comando_mkdisk::crear_disco(QString ppath){
    QString aux = obtener_path(ppath);
    string comando = "sudo mkdir -p \'"+aux.toStdString()+"\'";
    system(comando.c_str());
    string comando2 = "sudo chmod -R 777 \'"+aux.toStdString()+"\'";
    system(comando2.c_str());
    string arch = ppath.toStdString();
    FILE *archivo = fopen(arch.c_str(),"wb");
    if((archivo = fopen(arch.c_str(),"wb")))
        fclose(archivo);
    else
        cout << "\033[31mERROR: Al crear el Disco.\033[0m" << endl;
}

QString comando_mkdisk::obtener_path(QString path){
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

QString comando_mkdisk::nombre_archivo(QString path){
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
string comando_mkdisk::ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

