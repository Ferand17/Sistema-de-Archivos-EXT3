#include "comando_rep.h"
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
#include "f2_archivo.h"
using namespace std;

comando_rep::comando_rep()
{

}
void comando_rep::ast_rep(Nodo_arbol *raiz){
    string log_error="";
    //VALORES DE CADA PARAMETRO
    bool berror=false;
    //PARAMETROS OBLIGATORIOS
    bool bid=false;
    bool bpath=false;
    bool bname=false;
    //PARAMETROS
    bool bruta=false;
    bool bruta1=false;

    QString vpath="";
    QString vname="";
    QString vid="";
    QString vruta="";


    for(int c = 0; c < raiz->hijos.count(); c++)
    {
        Nodo_arbol temp = raiz->hijos.at(c);
        if(temp.tipo_==PATH){
            bpath=true;
            //cout<<temp.valor.toStdString()<<endl;
            string prueba=temp.valor.toStdString();
            prueba=ReplaceAll(prueba, string("\""), string(""));
            vpath=QString::fromStdString(prueba);
        }
        else if(temp.tipo_==NAME){
            bname=true;
            string prueba=temp.hijos.at(0).valor.toStdString();
            prueba=ReplaceAll(prueba, string("\""), string(""));
            vname=QString::fromStdString(prueba);
            if(vname=="file"){
                bruta=true;
            }
            else if(vname=="ls"){
                bruta=true;
            }
        }
        else if(temp.tipo_==ID){
            bid=true;
            string prueba=temp.valor.toStdString();
            prueba=ReplaceAll(prueba, string("\""), string(""));
            vid=QString::fromStdString(prueba);
        }
        else if (temp.tipo_==RUTA) {
            bruta1=true;
            //cout<<temp.valor.toStdString()<<endl;
            string prueba=temp.valor.toStdString();
            prueba=ReplaceAll(prueba, string("\""), string(""));
            vruta=QString::fromStdString(prueba);
        }
    }


    if(!bname){
        log_error+="El parametro -name es Obligatorio.\n";
        berror=true;
    }
    if(!bpath){
        log_error+="El parametro -path es Obligatorio.\n";
        berror=true;
    }
    if(!bid){
        log_error+="El parametro -id es Obligatorio.\n";
        berror=true;
    }
    if(bruta && !bruta1){
        log_error+="El parametro -ruta es Obligatorio.\n";
        berror=true;
    }
    if(!berror){
        ejecutar_rep(vname,vpath,vid,vruta);
    }
    else{
        cout<<"\033[31mEL COMANDO CONTIENE ERRORES: "<<endl;
        cout<<log_error<<"\033[0m"<<endl;
    }
    //cout<<"id "<<vid.toStdString()<<" name "<<vname.toStdString()<<" path "<<vpath.toStdString()<<endl;


}
string comando_rep::ReplaceAll(string str, const string& from, const string& to){
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

void comando_rep::ejecutar_rep(QString pname, QString ppath, QString pid,QString pruta){
    QString path = lista->getDireccion(pid);
    QString ext = obtener_extension(ppath);
    if(path != "null"){
        /*FASE2*/
        nodo_particiones encontrado=lista->getParticionMontada(pid);
        /*FASE2*/
        QString directorio = obtener_path(ppath);
        string comando = "sudo mkdir -p \'"+directorio.toStdString()+"\'";
        system(comando.c_str());
        string comando2 = "sudo chmod -R 777 \'"+directorio.toStdString()+"\'";
        system(comando2.c_str());
        if(pname == "mbr"){
            graficarMBR(path,ppath,ext);
        }else if(pname=="disk"){
            graficarDisco(path,ppath,ext);
        }
        else if(pname=="inode"){
            graficarINODE(encontrado,ppath);
        }
        else if(pname=="journaling"){
            graficarJOURNAL(encontrado,ppath);
        }
        else if(pname=="block"){
            graficarBLOCK(encontrado,ppath);
        }
        else if(pname=="bm_inode"){
            graficarBMINODE(encontrado,ppath);
        }
        else if(pname=="bm_block"){
            graficarBMBLOCK(encontrado,ppath);
        }
        else if(pname=="tree"){
            f2_archivo::reporteArbol(encontrado,ppath);
        }
        else if(pname=="sb"){
            f2_archivo::reporteSuperBloque(encontrado, ppath);
        }
        else if(pname=="file"){
            graficarFILE(encontrado,ppath,pruta);
        }
        else if(pname=="ls"){
            graficarLS(encontrado,ppath,pruta);
        }
    }else{
        cout << "\033[31mERROR: no se encuentra la particion.\033[0m" << endl;
    }

}

void comando_rep::graficarLS(nodo_particiones encontrado, QString ppath, QString pruta){
    if(encontrado.path.size()>0){
        FILE* discoArchivo = fopen(encontrado.path.toStdString().c_str(), "rb+");
        if (discoArchivo != NULL){
            //Enviar disco, particion,type, fs
            if(encontrado.part_type == 'P'){
                int inicioByte = encontrado.particion.part_start;
                f2_archivo archivo(discoArchivo, &encontrado, inicioByte);
                archivo.setUserInformation("root", 1, "root", 1);
                archivo.reporteLs(ppath, pruta);
            }
            else if(encontrado.part_type == 'l'){
                int inicioByte = encontrado.particion_logica.part_start + sizeof (EBR);
                f2_archivo archivo(discoArchivo, &encontrado, inicioByte);
                archivo.setUserInformation("root", 1, "root", 1);
                archivo.reporteLs(ppath, pruta);
            }
            else{ cout<<"Error: Partición no existe"<<endl<<endl;  }
            fclose(discoArchivo);
        }
        else{ cout<<"Error: Disco no encontrado"<<endl<<endl; }
    }else{ cout<<"Error: Partición no existe"<<endl<<endl;}
}

void comando_rep::graficarFILE(nodo_particiones encontrado, QString ppath, QString pruta){
    if(encontrado.path.size()>0){
        FILE* discoArchivo = fopen(encontrado.path.toStdString().c_str(), "rb+");
        if (discoArchivo != NULL){
            //Enviar disco, particion,type, fs
            if(encontrado.part_type == 'P'){
                int inicioByte = encontrado.particion.part_start;
                f2_archivo archivo(discoArchivo, &encontrado, inicioByte);
                archivo.setUserInformation("root", 1, "root", 1);
                archivo.reporteFile(ppath, pruta);
            }
            else if(encontrado.part_type == 'l'){
                int inicioByte = encontrado.particion_logica.part_start + sizeof (EBR);
                f2_archivo archivo(discoArchivo, &encontrado, inicioByte);
                archivo.setUserInformation("root", 1, "root", 1);
                archivo.reporteFile(ppath, pruta);
            }
            else{ cout<<"Error: Partición no existe"<<endl<<endl;  }
            fclose(discoArchivo);
        }
        else{ cout<<"Error: Disco no encontrado"<<endl<<endl; }
    }else{ cout<<"Error: Partición no existe"<<endl<<endl;}
}

void comando_rep::graficarBMBLOCK(nodo_particiones encontrado, QString ppath){
    if(encontrado.path.size()>0){
        FILE* discoArchivo = fopen(encontrado.path.toStdString().c_str(), "rb+");
        if (discoArchivo != NULL){
            //Enviar disco, particion,type, fs
            if(encontrado.part_type == 'P'){
                int inicioByte = encontrado.particion.part_start;
                f2_archivo archivo(discoArchivo, &encontrado, inicioByte);
                archivo.reporteBtmBlock(ppath);
            }
            else if(encontrado.part_type == 'l'){
                int inicioByte = encontrado.particion_logica.part_start + sizeof (EBR);
                f2_archivo archivo(discoArchivo, &encontrado, inicioByte);
                archivo.reporteBtmBlock(ppath);
            }
            else{ cout<<"Error: Partición no existe"<<endl<<endl;  }
            fclose(discoArchivo);
        }
        else{ cout<<"Error: Disco no encontrado"<<endl<<endl; }
    }else{ cout<<"Error: Partición no existe"<<endl<<endl;}
}

void comando_rep::graficarBMINODE(nodo_particiones encontrado, QString ppath){
    if(encontrado.path.size()>0){
        FILE* discoArchivo = fopen(encontrado.path.toStdString().c_str(), "rb+");
        if (discoArchivo != NULL){
            //Enviar disco, particion,type, fs
            if(encontrado.part_type == 'P'){
                int inicioByte = encontrado.particion.part_start;
                f2_archivo archivo(discoArchivo, &encontrado, inicioByte);
                archivo.reporteBtmInodo(ppath);
            }
            else if(encontrado.part_type == 'l'){
                int inicioByte = encontrado.particion_logica.part_start + sizeof (EBR);
                f2_archivo archivo(discoArchivo, &encontrado, inicioByte);
                archivo.reporteBtmInodo(ppath);
            }
            else{ cout<<"Error: Partición no existe"<<endl<<endl;  }
            fclose(discoArchivo);
        }
        else{ cout<<"Error: Disco no encontrado"<<endl<<endl; }
    }else{ cout<<"Error: Partición no existe"<<endl<<endl;}
}

void comando_rep::graficarBLOCK(nodo_particiones encontrado, QString ppath){
    //cout<<ppath.toStdString()<<endl;
    //cout<<encontrado.path.toStdString()<<endl;
    if(encontrado.path.size()>0){
        FILE* discoArchivo = fopen(encontrado.path.toStdString().c_str(), "rb+");
        if (discoArchivo != NULL){
            //Enviar disco, particion,type, fs
            if(encontrado.part_type == 'P'){
                int inicioByte = encontrado.particion.part_start;
                f2_archivo archivo(discoArchivo, &encontrado, inicioByte);
                archivo.reporteBloque(ppath);
            }
            else if(encontrado.part_type == 'l'){
                int inicioByte = encontrado.particion_logica.part_start + sizeof (EBR);
                f2_archivo archivo(discoArchivo, &encontrado, inicioByte);
                archivo.reporteBloque(ppath);
            }
            else{ cout<<"Error: Partición no existe"<<endl<<endl;  }
            fclose(discoArchivo);
        }
        else{ cout<<"Error: Disco no encontrado"<<endl<<endl; }
    }else{ cout<<"Error: Partición no existe"<<endl<<endl;}
}

void comando_rep::graficarJOURNAL(nodo_particiones encontrado, QString ppath){
    if(encontrado.path.size()>0){
        FILE* discoArchivo = fopen(encontrado.path.toStdString().c_str(), "rb+");
        if (discoArchivo != NULL){
            //Enviar disco, particion,type, fs
            if(encontrado.part_type == 'P'){
                int inicioByte = encontrado.particion.part_start;
                f2_archivo archivo(discoArchivo, &encontrado, inicioByte);
                archivo.reporteJournal(ppath);
            }
            else if(encontrado.part_type == 'l'){
                int inicioByte = encontrado.particion_logica.part_start + sizeof (EBR);
                f2_archivo archivo(discoArchivo, &encontrado, inicioByte);
                archivo.reporteJournal(ppath);
            }
            else{ cout<<"Error: Partición no existe"<<endl<<endl;  }
            fclose(discoArchivo);
        }
        else{ cout<<"Error: Disco no encontrado"<<endl<<endl; }
    }else{ cout<<"Error: Partición no existe"<<endl<<endl;}
}

void comando_rep::graficarINODE(nodo_particiones encontrado, QString ppath){
    if(encontrado.path.size()>0){
        FILE* discoArchivo = fopen(encontrado.path.toStdString().c_str(), "rb+");
        if (discoArchivo != NULL){
            //Enviar disco, particion,type, fs
            if(encontrado.part_type == 'P'){
                int inicioByte = encontrado.particion.part_start;
                f2_archivo archivo(discoArchivo, &encontrado, inicioByte);
                archivo.reporteInodo(ppath);
            }
            else if(encontrado.part_type == 'l'){
                int inicioByte = encontrado.particion_logica.part_start + sizeof (EBR);
                f2_archivo archivo(discoArchivo, &encontrado, inicioByte);
                archivo.reporteInodo(ppath);
            }
            else{ cout<<"Error: Partición no existe"<<endl<<endl;  }
            fclose(discoArchivo);
        }
        else{ cout<<"Error: Disco no encontrado"<<endl<<endl; }
    }else{ cout<<"Error: Partición no existe"<<endl<<endl;}
}

QString comando_rep::obtener_extension(QString path){
    string aux = path.toStdString();
    string delimiter = ".";
    size_t pos = 0;
    while((pos = aux.find(delimiter))!=string::npos){
        aux.erase(0,pos+delimiter.length());
    }
    return QString::fromStdString(aux);
}
QString comando_rep::obtener_path(QString path){
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

/* Metodo para graficar un disco con su estructura de las particiones */
void comando_rep::graficarDisco(QString path, QString destino, QString extension){
    string auxDir = path.toStdString();
    FILE *fp;
    FILE *graphDot;
    if((fp = fopen(auxDir.c_str(),"r"))){
        graphDot = fopen("grafica.dot","w");
        fprintf(graphDot,"digraph G{\n\n");
        fprintf(graphDot, "  tbl [\n    shape=box\n    label=<\n");
        fprintf(graphDot, "     <table border=\'0\' cellborder=\'2\' width=\'600\' height=\"200\" color=\'blue\'>\n");
        fprintf(graphDot, "     <tr>\n");
        fprintf(graphDot, "     <td height=\'200\' width=\'100\'> MBR </td>\n");
        MBR masterboot;
        fseek(fp,0,SEEK_SET);
        fread(&masterboot,sizeof(MBR),1,fp);
        int total = masterboot.mbr_size;
        double espacioUsado = 0;
        for(int i = 0; i < 4; i++){
            int parcial = masterboot.mbr_partition[i].part_size;
            if(masterboot.mbr_partition[i].part_start != -1){//Particion vacia
                double porcentaje_real = (parcial*100)/total;
                double porcentaje_aux = (porcentaje_real*500)/100;
                espacioUsado += porcentaje_real;
                if(masterboot.mbr_partition[i].part_status != '1'){
                    if(masterboot.mbr_partition[i].part_type == 'P'){
                        fprintf(graphDot, "     <td height=\'200\' width=\'%.1f\'>PRIMARIA <br/>%.1f%c</td>\n",porcentaje_aux,porcentaje_real,'%');
                        //Verificar que no haya espacio fragmentado
                        if(i!=3){
                            int p1 = masterboot.mbr_partition[i].part_start + masterboot.mbr_partition[i].part_size;
                            int p2 = masterboot.mbr_partition[i+1].part_start;
                            if(masterboot.mbr_partition[i+1].part_start != -1){
                                if((p2-p1)!=0){//Hay fragmentacion
                                    int fragmentacion = p2-p1;
                                    double porcentaje_real = (fragmentacion*100)/total;
                                    double porcentaje_aux = (porcentaje_real*500)/100;
                                    fprintf(graphDot,"     <td height=\'200\' width=\'%.1f\'>LIBRE<br/>%.1f%c</td>\n",porcentaje_aux,porcentaje_real,'%');
                                }
                            }

                        }else{
                            int p1 = masterboot.mbr_partition[i].part_start + masterboot.mbr_partition[i].part_size;
                            int mbr_size = total + (int)sizeof(MBR);
                            if((mbr_size-p1)!=0){//Libre
                                double libre = (mbr_size - p1) + sizeof(MBR);
                                double porcentaje_real = (libre*100)/total;
                                double porcentaje_aux = (porcentaje_real*500)/100;
                                fprintf(graphDot, "     <td height=\'200\' width=\'%.1f\'>LIBRE<br/>%.1f%c</td>\n",porcentaje_aux, porcentaje_real, '%');
                            }
                        }
                    }else{//Extendida
                        EBR extendedBoot;
                        fprintf(graphDot,"     <td  height=\'200\' width=\'%.1f\'>\n     <table border=\'0\'  height=\'200\' WIDTH=\'%.1f\' cellborder=\'1\'>\n",porcentaje_real,porcentaje_real);
                        fprintf(graphDot,"     <tr>  <td height=\'60\' colspan=\'15\'>EXTENDIDA</td>  </tr>\n     <tr>\n");
                        fseek(fp, masterboot.mbr_partition[i].part_start,SEEK_SET);
                        fread(&extendedBoot,sizeof(EBR),1,fp);
                        if(extendedBoot.part_size != 0){//Si hay mas de alguna logica
                            fseek(fp, masterboot.mbr_partition[i].part_start,SEEK_SET);
                            while(fread(&extendedBoot,sizeof (EBR),1,fp)!=0 && (ftell(fp) < (masterboot.mbr_partition[i].part_start + masterboot.mbr_partition[i].part_size))){
                                parcial = extendedBoot.part_size;
                                porcentaje_real = (parcial*100)/total;
                                if(porcentaje_real!=0){
                                    if(extendedBoot.part_status != '1'){
                                        fprintf(graphDot, "     <td height=\'140\'>EBR</td>\n");
                                        fprintf(graphDot, "     <td height=\'140\'>LOGICA<br/>%.1f%c</td>\n",porcentaje_real,'%');
                                    }else{//Espacio no asignado
                                        fprintf(graphDot, "      <td height=\'150\'>LIBRE 1 <br/> %.1f%c</td>\n",porcentaje_real,'%');
                                    }
                                    if(extendedBoot.part_next==-1){
                                        parcial = (masterboot.mbr_partition[i].part_start + masterboot.mbr_partition[i].part_size) - (extendedBoot.part_start + extendedBoot.part_size);
                                        porcentaje_real = (parcial*100)/total;
                                        if(porcentaje_real!=0){
                                            fprintf(graphDot, "     <td height=\'150\'>LIBRE 2<br/> %.1f%c </td>\n",porcentaje_real,'%');
                                        }
                                        break;
                                    }else
                                        fseek(fp,extendedBoot.part_next,SEEK_SET);
                                }
                            }
                        }else{
                            fprintf(graphDot,"     <td height=\'140\'> Ocupado %.1f%c</td>",porcentaje_real,'%');
                        }
                        fprintf(graphDot,"     </tr>\n     </table>\n     </td>\n");
                        //Verificar que no haya espacio fragmentado
                        if(i!=3){
                            int p1 = masterboot.mbr_partition[i].part_start + masterboot.mbr_partition[i].part_size;
                            int p2 = masterboot.mbr_partition[i+1].part_start;
                            if(masterboot.mbr_partition[i+1].part_start != -1){
                                if((p2-p1)!=0){//Hay fragmentacion
                                    int fragmentacion = p2-p1;
                                    double porcentaje_real = (fragmentacion*100)/total;
                                    double porcentaje_aux = (porcentaje_real*500)/100;
                                    fprintf(graphDot,"     <td height=\'200\' width=\'%.1f\'>LIBRE<br/> %.1f%c</td>\n",porcentaje_aux,porcentaje_real,'%');
                                }
                            }
                        }else{
                            int p1 = masterboot.mbr_partition[i].part_start + masterboot.mbr_partition[i].part_size;
                            int mbr_size = total + (int)sizeof(MBR);
                            if((mbr_size-p1)!=0){//Libre
                                double libre = (mbr_size - p1) + sizeof(MBR);
                                double porcentaje_real = (libre*100)/total;
                                double porcentaje_aux = (porcentaje_real*500)/100;
                                fprintf(graphDot, "     <td height=\'200\' width=\'%.1f\'>LIBRE<br/> %.1f%c</td>\n",porcentaje_aux, porcentaje_real, '%');
                            }
                        }
                    }
                }else{//Espacio no asignado
                     fprintf(graphDot,"     <td height=\'200\' width=\'%.1f\'>LIBRE <br/> %.1f%c</td>\n",porcentaje_aux,porcentaje_real,'%');
                }
            }
        }

        //fprintf(graphDot,"     <td height='200'> ESPACIO LIBRE <br/> %.1f%c\n     </td>",(100-espacioUsado),'%');


        fprintf(graphDot,"     </tr> \n     </table>        \n>];\n\n}");
        fclose(graphDot);
        fclose(fp);
        string comando = "dot -T"+extension.toStdString()+" grafica.dot -o "+destino.toStdString();
        system(comando.c_str());
        cout << "\033[96mReporte generado con exito.\033[0m " << endl;
    }else{
        cout << "\033[31mERROR: Al crear reporte, disco no encontrado.\033[0m" << endl;
    }
}

/* Metodo para generar un reporte del MBR de un disco */
void comando_rep::graficarMBR(QString path, QString destino, QString extension){
    string auxDir = path.toStdString();
    FILE *fp;
    FILE *graphDot;
    if((fp = fopen(auxDir.c_str(),"r"))){
        graphDot = fopen("grafica.dot", "w");
        fprintf(graphDot,"digraph G{ \n");
        fprintf(graphDot,"subgraph cluster{\n label=\"MBR\"");
        fprintf(graphDot,"\ntbl[shape=box,label=<\n");
        fprintf(graphDot,"<table color=\'blue\'  border=\'0\' cellborder=\'1\' cellspacing=\'0\' width=\'300\'  height=\'200\' >\n");
        fprintf(graphDot, "<tr>  <td width=\'150\'> <b>Nombre</b> </td> <td width=\'150\'> <b>Valor</b> </td>  </tr>\n");
        MBR masterBoot;
        fseek(fp,0,SEEK_SET);
        fread(&masterBoot,sizeof(MBR),1,fp);
        int tamano = masterBoot.mbr_size;
        fprintf(graphDot,"<tr>  <td><b>mbr_tamaño</b></td><td><font color='red'>%d</font></td>  </tr>\n",tamano);
        struct tm *tm;
        char fecha[100];
        tm = localtime(&masterBoot.mbr_date_created);
        strftime(fecha,100,"%d/%m/%y %H:%S",tm);
        fprintf(graphDot,"<tr>  <td><b>mbr_fecha_creacion</b></td> <td><font color='red'>%s</font></td>  </tr>\n",fecha);
        fprintf(graphDot,"<tr>  <td><b>mbr_disk_signature</b></td> <td><font color='red'>%d</font></td>  </tr>\n",masterBoot.mbr_disk_signature);
        fprintf(graphDot,"<tr>  <td><b>Disk_fit</b></td> <td><font color='red'>%c</font></td>  </tr>\n",masterBoot.mbr_disk_fit);

        int index_Extendida = -1;
        for (int i = 0; i < 4; i++){
            if(masterBoot.mbr_partition[i].part_start!=-1 && masterBoot.mbr_partition[i].part_status!='1'){
                if(masterBoot.mbr_partition[i].part_type == 'E'){
                    index_Extendida = i;
                }
                char status[3];
                if(masterBoot.mbr_partition[i].part_status == '0')
                    strcpy(status,"0");
                else if(masterBoot.mbr_partition[i].part_status == '2')
                    strcpy(status,"2");
                fprintf(graphDot,"<tr>  <td><b>part_status_%d</b></td> <td><font color='red'>%s</font></td>  </tr>\n",(i+1),status);
                fprintf(graphDot,"<tr>  <td><b>part_type_%d</b></td> <td><font color='red'>%c</font></td>  </tr>\n",(i+1),masterBoot.mbr_partition[i].part_type);
                fprintf(graphDot,"<tr>  <td><b>part_fit_%d</b></td> <td><font color='red'>%c</font></td>  </tr>\n",(i+1),masterBoot.mbr_partition[i].part_fit);
                fprintf(graphDot,"<tr>  <td><b>part_start_%d</b></td> <td><font color='red'>%d</font></td>  </tr>\n",(i+1),masterBoot.mbr_partition[i].part_start);
                fprintf(graphDot,"<tr>  <td><b>part_size_%d</b></td> <td><font color='red'>%d</font></td>  </tr>\n",(i+1),masterBoot.mbr_partition[i].part_size);
                fprintf(graphDot,"<tr>  <td><b>part_name_%d</b></td> <td><font color='red'>%s</font></td>  </tr>\n",(i+1),masterBoot.mbr_partition[i].part_name);
            }
        }

        fprintf(graphDot,"</table>\n");
        fprintf(graphDot, ">];\n}\n");

        if(index_Extendida != -1){
            int index_ebr = 1;
            EBR extendedBoot;
            fseek(fp,masterBoot.mbr_partition[index_Extendida].part_start,SEEK_SET);
            while(fread(&extendedBoot,sizeof(EBR),1,fp)!=0 && (ftell(fp) < masterBoot.mbr_partition[index_Extendida].part_start + masterBoot.mbr_partition[index_Extendida].part_size)) {
                if(extendedBoot.part_status != '1'){
                    fprintf(graphDot,"subgraph cluster_%d{\n label=\"EBR_%d\"\n",index_ebr,index_ebr);
                    fprintf(graphDot,"\ntbl_%d[shape=box, label=<\n ",index_ebr);
                    fprintf(graphDot, "<table color=\'blue\' border=\'0\' cellborder=\'1\' cellspacing=\'0\'  width=\'300\' height=\'160\' >\n ");
                    fprintf(graphDot, "<tr>  <td width=\'150\'><b>Nombre</b></td> <td width=\'150\'><b>Valor</b></td>  </tr>\n");
                    char status[3];
                    if(extendedBoot.part_status == '0')
                        strcpy(status,"0");
                    else if(extendedBoot.part_status == '2')
                        strcpy(status,"2");
                    fprintf(graphDot, "<tr>  <td><b>part_status_1</b></td> <td><font color='red'>%s</font></td>  </tr>\n",status);
                    fprintf(graphDot, "<tr>  <td><b>part_fit_1</b></td> <td><font color='red'>%c</font></td>  </tr>\n",extendedBoot.part_fit);
                    fprintf(graphDot, "<tr>  <td><b>part_start_1</b></td> <td><font color='red'>%d</font></td>  </tr>\n",extendedBoot.part_start);
                    fprintf(graphDot, "<tr>  <td><b>part_size_1</b></td> <td><font color='red'>%d</font></td>  </tr>\n",extendedBoot.part_size);
                    fprintf(graphDot, "<tr>  <td><b>part_next_1</b></td> <td><font color='red'>%d</font></td>  </tr>\n",extendedBoot.part_next);
                    fprintf(graphDot, "<tr>  <td><b>part_name_1</b></td> <td><font color='red'>%s</font></td>  </tr>\n",extendedBoot.part_name);
                    fprintf(graphDot, "</table>\n");
                    fprintf(graphDot, ">];\n}\n");
                    index_ebr++;
                }

                if(extendedBoot.part_next == -1)
                    break;
                else
                    fseek(fp,extendedBoot.part_next,SEEK_SET);
            }
        }
        fprintf(graphDot,"}\n");
        fclose(graphDot);
        fclose(fp);
        string comando = "dot -T"+extension.toStdString()+" grafica.dot -o "+destino.toStdString();
        system(comando.c_str());
        cout << "\033[96mReporte generado con exito.\033[0m " << endl;
    }
}







