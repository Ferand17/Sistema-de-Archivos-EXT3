#include "comando_mount.h"
#include <algorithm>
#include <string>

using namespace std;
comando_mount::comando_mount()
{

}
void comando_mount::ast_mount(QList<Nodo_arbol> *hijos)
{
    bool bpath=false;
    bool bname=false;
    QString vpath="";
    QString vname="";
    string prueba="";
    for(int c=0;c<hijos->length();c++){
        if(hijos->at(c).tipo.toStdString().compare("path")==0){
            bpath=true;
            prueba=hijos->at(c).valor.toStdString();
            prueba=ReplaceAll(prueba, std::string("\""), std::string(""));
            vpath=QString::fromStdString(prueba);
        }
        else if(hijos->at(c).tipo.toStdString().compare("name")==0){
            bname=true;
            prueba=hijos->at(c).valor.toStdString();
            prueba=ReplaceAll(prueba, std::string("\""), std::string(""));
            vname=QString::fromStdString(prueba);

        }

    }
    if(bpath && bname){
        ejecutar_mount(vname,vpath);
    }else{
        cout<<"\033[31mERROR: Los Parametros -name, -path son Obligatorios.\033[0m"<<endl;
    }

}



void comando_mount::ejecutar_mount(QString name, QString path){
                    int indexP = buscarParticion_P_E(path,name);
                    if(indexP != -1){
                        FILE *fp;
                        if((fp = fopen(path.toStdString().c_str(),"rb+"))){
                            MBR masterboot;
                            fseek(fp, 0, SEEK_SET);
                            fread(&masterboot, sizeof(MBR),1,fp);
                            masterboot.mbr_partition[indexP].part_status = '2';
                            //cout<<masterboot.mbr_partition[indexP].part_type<<endl;
                            /*FASE 2*/
                            char temp_type = masterboot.mbr_partition[indexP].part_type;
                            Partition temp_part = masterboot.mbr_partition[indexP];
                            /*FASE 2*/
                            fseek(fp,0,SEEK_SET);
                            fwrite(&masterboot,sizeof(MBR),1,fp);
                            fclose(fp);
                            int letra = lista->buscarLetra(path,name);
                            if(letra == -1){
                                cout << "\033[31mERROR: la particion ya esta montada.\033[0m" << endl;
                            }else{
                                int num = lista->buscarNumero(path, name);
                                char auxLetra = static_cast<char>(letra);
                                string id = "vd";
                                id += auxLetra+to_string(num);
                                nodo_particiones *n = new nodo_particiones(path,name,auxLetra,num, temp_type);
                                /*FASE2*/
                                n->particion=temp_part;
                                /*FASE2*/
                                lista->insertarNodo(n);
                                cout << "\033[96mParticion montada con exito.\033[0m" << endl;
                                //lista->mostrarLista();
                            }
                        }else{
                            cout << "\033[31mERROR: no se encuentra el disco.\033[0m" << endl;
                        }
                    }else{//Posiblemente logica
                        int indexP = buscarParticion_L(path,name);
                        if(indexP != -1){
                            FILE *fp;
                            if((fp = fopen(path.toStdString().c_str(), "rb+"))){
                                EBR extendedBoot;
                                fseek(fp, indexP, SEEK_SET);
                                fread(&extendedBoot, sizeof(EBR),1,fp);
                                extendedBoot.part_status = '2';
                                /*FASE 2*/
                                EBR temp_part = extendedBoot;
                                /*FASE 2*/
                                fseek(fp,indexP,SEEK_SET);
                                fwrite(&extendedBoot,sizeof(EBR),1, fp);
                                fclose(fp);

                                int letra = lista->buscarLetra(path,name);
                                if(letra == -1){
                                    cout << "\033[31mERROR: La particion ya esta montada.\033[0m" << endl;
                                }else{
                                    int num = lista->buscarNumero(path,name);
                                    char auxLetra = static_cast<char>(letra);
                                    string id = "vd";
                                    id += auxLetra+to_string(num);
                                    nodo_particiones *n = new nodo_particiones(path, name, auxLetra, num,'l');
                                    /*FASE2*/
                                    n->particion_logica=temp_part;
                                    /*FASE2 */
                                    lista->insertarNodo(n);
                                    cout << "\033[96mParticion montada con exito.\033[0m" << endl;
                                    //lista->mostrarLista();
                                }
                            }else{
                                cout << "\033[31mERROR: no se encuentra el disco.\033[0m" << endl;
                            }
                        }else{
                            cout << "\033[31mERROR: no se encuentra la particion a montar.\033[0m" << endl;
                        }
                    }
}




string comando_mount::ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

int comando_mount::buscarParticion_P_E(QString direccion, QString nombre){
    string auxPath = direccion.toStdString();
    string auxName = nombre.toStdString();
    FILE *fp;
    if((fp = fopen(auxPath.c_str(),"rb+"))){
        MBR masterboot;
        fseek(fp,0,SEEK_SET);
        fread(&masterboot,sizeof(MBR),1,fp);
        for(int i = 0; i < 4; i++){
            if(masterboot.mbr_partition[i].part_status != '1'){
                if(strcmp(masterboot.mbr_partition[i].part_name,auxName.c_str()) == 0){
                    return i;
                }
            }
        }

    }
    return -1;
}


int comando_mount::buscarParticion_L(QString direccion, QString nombre){
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

