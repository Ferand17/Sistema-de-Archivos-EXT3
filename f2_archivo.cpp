#include "f2_archivo.h"
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
#include "f2_disco.h"
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

using namespace std;

f2_archivo::f2_archivo()
{

}


void f2_archivo::setUserInformation(QString usr_name, int usr_id, QString usr_grp,int usr_grp_id){
    this->usr_name = usr_name;
    this->usr_id = usr_id;
    this->usr_grp = usr_grp;
    this->usr_grp_id = usr_grp_id;
}

int f2_archivo::calNoEstructuras(int size_particion, char part_type, string fs){
    if(QString::compare(fs.c_str(), "2fs",Qt::CaseInsensitive)==0){
        switch (part_type) {
            case'P'://Primaria
            return floor((double)(size_particion - sizeof(SuperBlock))/(double)(4+sizeof(Inodo)+(3*SIZE_BLOCKS)));
            case 'L'://Logica : Al tamaño total de la partición se le resta el tamaño del ebr
            return floor((double)(size_particion - sizeof(SuperBlock)- sizeof(EBR))/(double)(4+sizeof(Inodo)+(3*SIZE_BLOCKS)));
            default:
            return 0;
        }
    }if(QString::compare(fs.c_str(), "3fs",Qt::CaseInsensitive)==0){
        switch (part_type) {
            case'P'://Primaria
            return floor((double)(size_particion - sizeof(SuperBlock))/(double)(4+sizeof(Journal)+sizeof(Inodo)+(3*SIZE_BLOCKS)));
            case 'L'://Logica : Al tamaño total de la partición se le resta el tamaño del ebr
            return floor((double)(size_particion - sizeof(SuperBlock)- sizeof(EBR))/(double)(4+sizeof(Journal)+sizeof(Inodo)+(3*SIZE_BLOCKS)));
            default:
            return 0;
        }
    }
    else{return 0;}
}

void f2_archivo::escribirInodo(FILE *disco, Inodo inodo, int inode_start, int posicion){
    //Posicionamos el puntero respecto donde inician los inodos en la particion
    fseek(disco, inode_start + (sizeof(Inodo) * posicion), SEEK_SET);
    //Escribimos el inodo en la particion
    fwrite(&inodo, sizeof(Inodo), 1, disco);
}

Inodo f2_archivo::getInodo(FILE *disco, int inode_start, int posicion){
    Inodo inodo;
    fseek(disco, inode_start + (sizeof(Inodo) * posicion), SEEK_SET);//Posicionamos el puntero al inicio del archivo
    fread(&inodo, sizeof(Inodo), 1, disco);
    return inodo;
}

void f2_archivo::escribirBloque(FILE *disco, BCarpeta block, int block_start, int posicion){
    //Posicionamos el puntero respecto donde inician los bloques en la particion
    fseek(disco, block_start + (SIZE_BLOCKS * posicion), SEEK_SET);
    //Escribimos el bloque en la particion
    fwrite(&block, sizeof(BCarpeta), 1, disco);
}

BCarpeta f2_archivo::getBloqueCarpeta(FILE *disco, int block_start, int posicion){
    BCarpeta bloque;
    fseek(disco, block_start + (SIZE_BLOCKS * posicion), SEEK_SET);//Posicionamos el puntero al inicio del archivo
    fread(&bloque, sizeof(BCarpeta), 1, disco);
    return bloque;
}

void f2_archivo::escribirBloque(FILE *disco, BArchivo block, int block_start, int posicion){
    //Posicionamos el puntero respecto donde inician los bloques en la particion
    fseek(disco, block_start + (SIZE_BLOCKS * posicion), SEEK_SET);
    //Escribimos el bloque en la particion
    fwrite(&block, 1, SIZE_BLOCKS, disco);
}

BArchivo f2_archivo::getBloqueArchivo(FILE *disco, int block_start, int posicion){
    BArchivo bloque;
    fseek(disco, block_start + (SIZE_BLOCKS * posicion), SEEK_SET);//Posicionamos el puntero al inicio del archivo
    fread(&bloque, 64, 1, disco);
    //cout<<endl<<"Bloque Get: "<<bloque.b_content[64]<<bloque.b_content[65]<<bloque.b_content[66]<<endl;
    return bloque;
}

void f2_archivo::escribirBloque(FILE *disco, BApuntador block, int block_start, int posicion){
    //Posicionamos el puntero respecto donde inician los bloques en la particion
    fseek(disco, block_start + (SIZE_BLOCKS * posicion), SEEK_SET);
    //Escribimos el bloque en la particion
    fwrite(&block, SIZE_BLOCKS, 1, disco);
}

BApuntador f2_archivo::getBloqueApuntador(FILE *disco, int block_start, int posicion){
    BApuntador bloque;
    fseek(disco, block_start + (SIZE_BLOCKS * posicion), SEEK_SET);//Posicionamos el puntero al inicio del archivo
    fread(&bloque, sizeof(BApuntador), 1, disco);
    return bloque;
}

void f2_archivo::crearCarpetaRaiz(FILE *disco, SuperBlock &s_block, int inicio_byte){
    int no_struct = s_block.s_inodes_count;
    //Bitmap inodos
    char bitmap_inodos[no_struct];
    for(int i= 0; i < no_struct; i++){
        bitmap_inodos[i] = '0';
    }
    //Bitmap bloques
    char bitmap_blocks[(no_struct * 3)];
    for(int i= 0; i < (no_struct * 3); i++){
        bitmap_blocks[i] = '0';
    }

    //Crear Carpeta raiz
    Inodo inodo;
    inodo.i_uid = 1;
    inodo.i_gid = 1;
    inodo.i_size = 0;
    inodo.i_atime = time(NULL);
    inodo.i_ctime = time(NULL);
    inodo.i_mtime = time(NULL);
    inodo.i_block = 0;
    inodo.i_type = '0';//Carpeta
    inodo.i_perm = 000;
    //Ocupamos el bloque 0 en el bitmap inodos
    bitmap_inodos[0] = '1';
    s_block.s_free_inodes_count--;

    //Crear Nodo apuntador----------------------------------------------
    BApuntador apuntador0;
    bitmap_blocks[0] = '1';//Ocupamos el primer espacio en bitmap bloques
    s_block.s_free_blocks_count--;
    //Ocupamos el primer espacio del bloque apuntador
    //y lo apuntamos a el bloque carpeta(bloque 1)
    apuntador0.b_pointers[0] = 1;
    for(int i= 1; i < 16 ; i++){
        apuntador0.b_pointers[i] = -1;
    }
    //Crer Bloque carpeta------------------------------------------------
    BCarpeta carpeta1;
    bitmap_blocks[1] = '1';//Ocupamos el segundo espacio en bitmap bloques
    s_block.s_free_blocks_count--;
    for (int i=0; i < 4; i++) {
        carpeta1.b_content[i].b_inodo = -1;
    }

    //Escribir el primer inodo en la posicion 0
    escribirInodo(disco, inodo, s_block.s_inode_start, 0);
    //Escribir bloques
    escribirBloque(disco, apuntador0, s_block.s_block_start, 0);
    escribirBloque(disco, carpeta1, s_block.s_block_start, 1);

    //Escribir bitmap_inodos
    fseek(disco, s_block.s_bm_inode_start, SEEK_SET);//Posicionamos el puntero al inicio de espacio bitmap inodos
    fwrite(&bitmap_inodos, 1, s_block.s_inodes_count, disco);//Escribimos el Bitmap inodos
    //Escribir bitmap_bloques
    fseek(disco, s_block.s_bm_block_start, SEEK_SET);//Posicionamos el puntero al inicio de espacio bitmap blocks
    fwrite(&bitmap_blocks, 1, s_block.s_blocks_count, disco);//Escribimos el Bitmap blocks
    //Escribir super bloque
    fseek(disco, inicio_byte, SEEK_SET);//Posicionamos el puntero al inicio de la particion
    fwrite(&s_block, sizeof(SuperBlock), 1, disco);//Escribimos el Superbloque
}

void f2_archivo::formatearParticion(FILE *disco, Partition particion, string type, string fs){
        int no_struct = calNoEstructuras(particion.part_size, particion.part_type, fs);
        if(no_struct > 0){
            int inicio_byte = particion.part_start;
            SuperBlock s_bloque;
            //s_bloque.s_filesystem_type = 1;
            s_bloque.s_inodes_count = no_struct;
            s_bloque.s_blocks_count = (no_struct * 3);
            s_bloque.s_free_blocks_count = (no_struct * 3);
            s_bloque.s_free_inodes_count = no_struct;
            s_bloque.s_mtime = time(NULL);
            s_bloque.s_umtime = time(NULL);
            s_bloque.s_mnt_count = 1;
            s_bloque.s_magic = 0xEF53;
            s_bloque.s_inode_size = sizeof(Inodo);
            s_bloque.s_block_size = SIZE_BLOCKS;
            s_bloque.s_firts_ino = 0;
            s_bloque.s_first_blo = 0;
            //s_bloque.s_bm_inode_start = (inicio_byte + sizeof(SuperBlock));
            //s_bloque.s_bm_block_start = (inicio_byte + sizeof(SuperBlock) + no_struct);
            //s_bloque.s_inode_start = (inicio_byte + sizeof(SuperBlock) + no_struct + (3*no_struct));
            //s_bloque.s_block_start = (inicio_byte + sizeof(SuperBlock) + no_struct + (3*no_struct) + (no_struct * sizeof(Inodo)));
            int fileSystem = 0;
            if(QString::compare(fs.c_str(), "3fs", Qt::CaseInsensitive)==0){
                fileSystem = 3;
            }else{
                fileSystem = 2;
            }

            switch (fileSystem) {
                case 2:
                    s_bloque.s_filesystem_type = 2;
                    s_bloque.s_bm_inode_start = (inicio_byte + sizeof(SuperBlock));
                    s_bloque.s_bm_block_start = (inicio_byte + sizeof(SuperBlock) + no_struct);
                    s_bloque.s_inode_start = (inicio_byte + sizeof(SuperBlock) + no_struct + (3*no_struct));
                    s_bloque.s_block_start = (inicio_byte + sizeof(SuperBlock) + no_struct + (3*no_struct) + (no_struct * sizeof(Inodo)));
                break;
                case 3:
                    s_bloque.s_filesystem_type = 3;
                    s_bloque.s_bm_inode_start = (inicio_byte + sizeof(SuperBlock) + (no_struct * sizeof(Journal)) );
                    s_bloque.s_bm_block_start = (inicio_byte + sizeof(SuperBlock) + (no_struct * sizeof(Journal)) +  no_struct);
                    s_bloque.s_inode_start = (inicio_byte + sizeof(SuperBlock) + (no_struct * sizeof(Journal)) + no_struct + (3*no_struct));
                    s_bloque.s_block_start = (inicio_byte + sizeof(SuperBlock) + (no_struct * sizeof(Journal)) + no_struct + (3*no_struct) + (no_struct * sizeof(Inodo)));

                    Info_journal init;
                    init.max = no_struct;
                    init.last = 1;

                    Journal first;
                    first.tipo = '0';//Carpeta

                    /*EDITADO*/



                    first.date = time(NULL);
                    first.next = -1;

                    strcpy(first.nombre,"/");
                    strcpy(first.operacion,"mkdir");
                    strcpy(first.content,"-----");
                    fseek(disco, inicio_byte + sizeof(SuperBlock), SEEK_SET);//Posicionamos el puntero despues del superbloque
                    fwrite(&init, sizeof(Info_journal), 1, disco);//Escribimos el inicio del journal

                    fseek(disco, inicio_byte + sizeof(SuperBlock) + sizeof(Journal), SEEK_SET);//Posicionamos el puntero despues del superbloque
                    fwrite(&first, sizeof(Journal), 1, disco);//Escribimos el inicio del journal
                break;
            }
            //Crear Carpeta Raiz
            crearCarpetaRaiz(disco, s_bloque, inicio_byte);
            //Crear Archivo users.txt

            cout<<"\033[96mSe ha formateado la partición correctamente.\033[0m"<<endl<<endl;
        }else{cout<<"\033[31mERROR:  La particion o el -fs no es correcto.\033[0m"<<endl<< endl;}
}

void f2_archivo::formatearPar_logica(FILE *disco, EBR particion, string type, string fs){
        int no_struct = calNoEstructuras(particion.part_size, 'L', fs);
        if(no_struct > 0){
            int inicio_byte = particion.part_start + sizeof(EBR);
            SuperBlock s_bloque;
            //s_bloque.s_filesystem_type = 1;
            s_bloque.s_inodes_count = no_struct;
            s_bloque.s_blocks_count = (no_struct * 3);
            s_bloque.s_free_blocks_count = (no_struct * 3);
            s_bloque.s_free_inodes_count = no_struct;
            s_bloque.s_mtime = time(NULL);
            s_bloque.s_umtime = time(NULL);
            s_bloque.s_mnt_count = 1;
            s_bloque.s_magic = 0xEF53;
            s_bloque.s_inode_size = sizeof(Inodo);
            s_bloque.s_block_size = SIZE_BLOCKS;
            s_bloque.s_firts_ino = 0;
            s_bloque.s_first_blo = 0;
            //s_bloque.s_bm_inode_start = (inicio_byte + sizeof(SuperBlock));
            //s_bloque.s_bm_block_start = (inicio_byte + sizeof(SuperBlock) + no_struct);
            //s_bloque.s_inode_start = (inicio_byte + sizeof(SuperBlock) + no_struct + (3*no_struct));
            //s_bloque.s_block_start = (inicio_byte + sizeof(SuperBlock) + no_struct + (3*no_struct) + (no_struct * sizeof(Inodo)));

            int fileSystem = 0;
            if(QString::compare(fs.c_str(), "3fs", Qt::CaseInsensitive)==0){
                fileSystem = 3;
            }else{
                fileSystem = 2;
            }

            switch (fileSystem) {
                case 2:
                    s_bloque.s_filesystem_type = 2;
                    s_bloque.s_bm_inode_start = (inicio_byte + sizeof(SuperBlock));
                    s_bloque.s_bm_block_start = (inicio_byte + sizeof(SuperBlock) + no_struct);
                    s_bloque.s_inode_start = (inicio_byte + sizeof(SuperBlock) + no_struct + (3*no_struct));
                    s_bloque.s_block_start = (inicio_byte + sizeof(SuperBlock) + no_struct + (3*no_struct) + (no_struct * sizeof(Inodo)));
                break;
                case 3:
                    s_bloque.s_filesystem_type = 3;
                    s_bloque.s_bm_inode_start = (inicio_byte + sizeof(SuperBlock) + (no_struct * sizeof(Journal)) );
                    s_bloque.s_bm_block_start = (inicio_byte + sizeof(SuperBlock) + (no_struct * sizeof(Journal)) +  no_struct);
                    s_bloque.s_inode_start = (inicio_byte + sizeof(SuperBlock) + (no_struct * sizeof(Journal)) + no_struct + (3*no_struct));
                    s_bloque.s_block_start = (inicio_byte + sizeof(SuperBlock) + (no_struct * sizeof(Journal)) + no_struct + (3*no_struct) + (no_struct * sizeof(Inodo)));

                    Info_journal init;
                    init.max = no_struct;
                    init.last = 1;

                    Journal first;
                    first.tipo = '0';//Carpeta
                    //EDITADO
                    //time_t tiempo = time(0);
                    //struct tm *tlocal = localtime(&tiempo);
                    //strftime(first.date,16,"%d/%m/%y %H:%M",tlocal);


                    first.date = time(NULL);
                    first.next = -1;
                    strcpy(first.nombre,"/");
                    strcpy(first.operacion,"mkdir");
                    strcpy(first.content,"-----");
                    fseek(disco, inicio_byte + sizeof(SuperBlock), SEEK_SET);//Posicionamos el puntero despues del superbloque
                    fwrite(&init, sizeof(Info_journal), 1, disco);//Escribimos el inicio del journal

                    fseek(disco, inicio_byte + sizeof(SuperBlock) + sizeof(Journal), SEEK_SET);//Posicionamos el puntero despues del superbloque
                    fwrite(&first, sizeof(Journal), 1, disco);//Escribimos el inicio del journal
                break;
            }
            crearCarpetaRaiz(disco, s_bloque, inicio_byte);
            //Crear Archivo users.txt
            cout<<"\033[96mSe ha formateado la partición correctamente.\033[0m"<<endl<<endl;
        }else{cout<<"\033[31mERROR:  La particion o el -fs no es correcto.\033[0m"<<endl<< endl;}
}
/*##################################################################################################################################
                                    METODOS PARA CREAR CARPETAS
##################################################################################################################################*/

f2_archivo::f2_archivo(FILE*disco, nodo_particiones *particion, int iniciobyte){
    this->disco = disco;
    this->inicio_byte = iniciobyte;
    getSuperBlock(particion);
    getBitmaps();
    getJournal();
}

void f2_archivo::getSuperBlock(FILE* disco, nodo_particiones part_montada, SuperBlock &superBlock){
    if(part_montada.part_type == 'p' || part_montada.part_type == 'P'){
        Partition particion = part_montada.particion;
        fseek(disco, particion.part_start, SEEK_SET);//Posicionamos el puntero al inicio de la particion
        fread(&superBlock, sizeof (SuperBlock), 1, disco);

    }
    else if(part_montada.part_type == 'l' || part_montada.part_type == 'L'){
        EBR logica = part_montada.particion_logica;
        fseek(disco, logica.part_start + sizeof (EBR), SEEK_SET);//Posicionamos el puntero al inicio de la particion
        fread(&superBlock, sizeof (SuperBlock), 1, disco);
    }else{
        SuperBlock empty;
        empty.s_filesystem_type = -1;
        superBlock = empty;
    }
}

void f2_archivo::getSuperBlock(nodo_particiones *part_montada){
    if(part_montada->part_type == 'p' || part_montada->part_type == 'P'){
        Partition particion = part_montada->particion;
        fseek(disco, particion.part_start, SEEK_SET);//Posicionamos el puntero al inicio de la particion
        fread(&this->super, sizeof (SuperBlock), 1, disco);

    }
    else if(part_montada->part_type == 'l' || part_montada->part_type == 'L'){
        EBR logica = part_montada->particion_logica;
        fseek(disco, logica.part_start + sizeof (EBR), SEEK_SET);//Posicionamos el puntero al inicio de la particion
        fread(&this->super, sizeof (SuperBlock), 1, disco);
    }else{
        SuperBlock empty;
        empty.s_filesystem_type = -1;
        this->super = empty;
    }
}

void f2_archivo::actualizarSuperBloque(){
    actualizarSB();
    actualizarBitmaps();
    actualizarJournal();
}

void f2_archivo::actualizarSB(){
    int first_ino = getFreeIndexBitmapInodo();
    int first_blo = getFreeIndexBitmapBlock();
    liberarBitmapBlock(first_blo);
    liberarBitmapInodo(first_ino);
    super.s_first_blo = first_blo;
    super.s_firts_ino = first_ino;

    fseek(disco, inicio_byte, SEEK_SET);//Posicionamos el puntero al inicio de la particion
    fwrite(&super, sizeof(SuperBlock), 1, disco);//Escribimos el Superbloque
}

void f2_archivo::actualizarBitmaps(){
    //Escribir bitmap_inodos
    fseek(disco, super.s_bm_inode_start, SEEK_SET);//Posicionamos el puntero al inicio de espacio bitmap inodos
    fwrite(bitmap_inodo.data(), 1, super.s_inodes_count, disco);//Escribimos el Bitmap inodos
    //Escribir bitmap_bloques
    fseek(disco, super.s_bm_block_start, SEEK_SET);//Posicionamos el puntero al inicio de espacio bitmap blocks
    fwrite(bitmap_block.data(), 1, super.s_blocks_count, disco);//Escribimos el Bitmap blocks
}

void f2_archivo::actualizarJournal(){
    if(super.s_filesystem_type == 3){
        int inicio_journaling = this->inicio_byte + sizeof (SuperBlock);
        int new_last = journal_info.last;
        int old_last = journal_info.last;
        foreach (Journal aux, journaling) {
            new_last++;
            if(new_last > journal_info.max){break;}
            fseek(disco, inicio_journaling + (new_last * sizeof(Journal)), SEEK_SET);//Posicionamos el puntero al inicio de bitmaps
            fwrite(&aux, sizeof(Journal), 1, disco);

        }
        journal_info.last = new_last;
        fseek(disco, inicio_journaling + (0 * sizeof(Journal)), SEEK_SET);//Posicionamos el puntero al inicio de bitmaps
        fwrite(&journal_info, sizeof(Info_journal), 1, disco);

        fseek(disco, inicio_journaling + (old_last * sizeof(Journal)), SEEK_SET);//Posicionamos el puntero al inicio de bitmaps
        fwrite(&journal_last, sizeof(Journal), 1, disco);
    }
}

void f2_archivo::agregarJournal(QString comando, QString nombre, QString contenido, char tipo){
    Journal nuevo_journal;
    nuevo_journal.tipo = tipo;
    strcpy(nuevo_journal.operacion, comando.toStdString().c_str());
    strcpy(nuevo_journal.nombre, nombre.toStdString().c_str());
    strcpy(nuevo_journal.content, contenido.mid(0,230).toStdString().c_str());

    //EDITADO
    //time_t tiempo = time(0);
    //struct tm *tlocal = localtime(&tiempo);
    //strftime(nuevo_journal.date,16,"%d/%m/%y %H:%M",tlocal);



    nuevo_journal.date = time(NULL);



    nuevo_journal.next = -1;
    /*MODIFICACION PARA EL USUARIO*/
    strcpy(nuevo_journal.usuario, usr_name.toStdString().c_str());

    if(journaling.size() == 0){
        journal_last.next = journal_info.last + 1;
    }
    else{
        journaling.last().next = journal_info.last + journaling.size() + 1;
    }
    journaling.append(nuevo_journal);
}

void f2_archivo::getBitmaps(){
    //Obtener bitmaps inodos
    char bit_inodos[super.s_inodes_count];
    char bit_blocks[super.s_blocks_count];
    fseek(disco, this->super.s_bm_inode_start, SEEK_SET);//Posicionamos el puntero al inicio de bitmaps
    fread(&bit_inodos, 1, super.s_inodes_count, disco);
    //Obtener bitmaps bloques
    fseek(disco, this->super.s_bm_block_start, SEEK_SET);//Posicionamos el puntero al inicio de bitmaps
    fread(&bit_blocks, 1, super.s_blocks_count, disco);
    QByteArray bm_inodos(bit_inodos);
    QByteArray bm_bloques(bit_blocks);
    this->bitmap_block = bm_bloques;
    this->bitmap_inodo = bm_inodos;
}

void f2_archivo::getJournal(){
    if(super.s_filesystem_type == 3){
        int inicio_journaling = this->inicio_byte + sizeof (SuperBlock);
        //Obtenemos el info journal
        fseek(disco, inicio_journaling, SEEK_SET);//Posicionamos el puntero al inicio de bitmaps
        fread(&this->journal_info, sizeof (Info_journal), 1, disco);
        //Obtenemos el ultimo Journal
        fseek(disco, inicio_journaling + (journal_info.last * sizeof(Journal)), SEEK_SET);//Posicionamos el puntero al inicio de bitmaps
        fread(&this->journal_last, sizeof(Journal), 1, disco);
        //cout<<" LastJounal: tipo=" <<journal_last.tipo<<" nombre="<<journal_last.nombre<<" content="<<journal_last.content<<" Operacion="<<journal_last.operacion<<" Next="<<journal_last.next<<endl;
    }
}

Journal f2_archivo::getJournal(int posicion){
    Journal find;
    find.next = -1;
    int inicio_journaling = this->inicio_byte + sizeof (SuperBlock);
    //Obtenemos el ultimo Journal
    fseek(disco, inicio_journaling + (posicion * sizeof(Journal)), SEEK_SET);//Posicionamos el puntero al inicio de bitmaps
    fread(&find, sizeof(Journal), 1, disco);
    return find;
}

int f2_archivo::getFreeIndexBitmapInodo(){
    for (int i = 0; i < this->bitmap_inodo.size(); i ++) {
        if(bitmap_inodo[i] == '0'){
            bitmap_inodo[i] = '1';
            super.s_free_inodes_count--;
            return i;
        }
    }
    return -1;
}

void f2_archivo::liberarBitmapInodo(int posInodo){
    this->bitmap_inodo[posInodo] = '0';
    super.s_inodes_count++;
}

int f2_archivo::getFreeIndexBitmapBlock(){
    for (int i = 0; i < this->bitmap_block.size(); i ++) {
        if(bitmap_block[i] == '0'){
            bitmap_block[i] = '1';
            super.s_free_blocks_count--;
            return i;
        }
    }
    return -1;
}

void f2_archivo::liberarBitmapBlock(int posBlock){
    this->bitmap_block[posBlock] = '0';
    super.s_free_blocks_count++;
}

QStringList f2_archivo::getPath(QString path){
    QStringList lista = path.split('/');
    QStringList retornar;
    foreach (QString item, lista) {
        if(item.size() > 0){

            retornar.append(item);
        }
    }

    return retornar;
}

int f2_archivo::getPositionInodobyName(QString name_file_direc, BApuntador b_apuntador,int nivel_puntero_indirecto){
/* Retorna la posición de un inodo ya sea archivo o carpeta, si no existe retornará -1
 * El metodo hará una busqueda en los bloques apuntadores, y dependerá del nivel especificado
 */
    if(nivel_puntero_indirecto >0 && nivel_puntero_indirecto <= 3){
        if(nivel_puntero_indirecto == 1){
            //Nivel indirecto  simple Hijos son bloques carptesa y archivos
            for (int i = 0; i < 16; i++) {
                int indice_b_carpeta = b_apuntador.b_pointers[i];
                if(indice_b_carpeta >= 0){
                    BCarpeta b_carpeta = getBloqueCarpeta(disco, super.s_inode_start, indice_b_carpeta);
                    for(int k = 0; k < 4; k++){
                        if( b_carpeta.b_content[k].b_inodo >= 0){
                            if(QString::compare(b_carpeta.b_content[k].b_name, name_file_direc, Qt::CaseSensitive)==0){
                                //Si el nombre es igual retornar el numero de inodo
                                return b_carpeta.b_content[k].b_inodo;
                            }
                        }
                    }
                }
            }
        }else if(nivel_puntero_indirecto == 2){
            //Nivel indirecto doble, Hijos son punteros indirectos simples
            //Recorriendo punteros dobles
            for (int i = 0; i < 16; i++) {
                int ind_b_indi_simple = b_apuntador.b_pointers[i];
                if(ind_b_indi_simple >= 0){
                    BApuntador b_apunt_simple = getBloqueApuntador(disco, super.s_inode_start, ind_b_indi_simple);
                    int resultado = getPositionInodobyName(name_file_direc, b_apunt_simple, 1);
                    if(resultado >= 0){
                        return resultado;
                    }
                }
            }

        }else{
            //Nivel indirecto triple, Hijos son punteros indirectos dobles
            //Recorriendo punteros triples
            for (int i = 0; i < 16; i++) {
                int ind_b_indi_doble = b_apuntador.b_pointers[i];
                if(ind_b_indi_doble >= 0){
                    BApuntador b_apunt_doble = getBloqueApuntador(disco, super.s_inode_start, ind_b_indi_doble);
                    int resultado = getPositionInodobyName(name_file_direc, b_apunt_doble, 2);
                    if(resultado >= 0){
                        return resultado;
                    }
                }
            }
        }
    }
    return -1;
}

//Todos los 16 se vuelven 15 Rango de los for
//Todos los 15 se vuelven 14 Nivel 3
//Todos los 14 se vuelven 13 Nivel 2
//Todos los 13 se vuelven 12 Nivel 1
//Todos los 12 se vuelven 11 el primer if despues del for

int f2_archivo::existInodobyName( Inodo inodo_current, QString name_file_direc){
/* Retorna el indice(Mayor a 0) del inodo(Carpeta o archivo) que corresponde al nombre ingresado)
 * recorre todos los indices directos e indices indirectos.
 * Retorna -1 si no encontró algun inodo correspondiete al nombre
*/
    BApuntador inodo_apuntador = getBloqueApuntador(disco, super.s_block_start, inodo_current.i_block);
    for (int i = 0; i < 16; i++) {
        if(i <= 12){
            if(inodo_apuntador.b_pointers[i] >= 0){
                //Sacamos el bloque carpeta
                BCarpeta b_carpeta = getBloqueCarpeta(disco, super.s_block_start, inodo_apuntador.b_pointers[i]);
                for(int c = 0; c < 4; c++){
                    if(b_carpeta.b_content[c].b_inodo >= 0){
                        if(QString::compare(b_carpeta.b_content[c].b_name, name_file_direc,Qt::CaseSensitive) == 0){
                            return b_carpeta.b_content[c].b_inodo;
                        }
                    }
                }
            }
        }
        else if(i == 13){
            //Aparecen bloques apuntadores
            if(inodo_apuntador.b_pointers[i] >= 0){
                //Sacamos el bloque carpeta
                BApuntador b_apuntador = getBloqueApuntador(disco, super.s_block_start, inodo_apuntador.b_pointers[i]);
                int indice_inodo = getPositionInodobyName(name_file_direc, b_apuntador, 1);
                if(indice_inodo >= 0){
                    return indice_inodo;
                }

            }
        }
        else if(i == 14){
            //Aparecen bloques apuntadores
            if(inodo_apuntador.b_pointers[i] >= 0){
                //Sacamos el bloque carpeta
                BApuntador b_apuntador = getBloqueApuntador(disco, super.s_block_start, inodo_apuntador.b_pointers[i]);
                int indice_inodo = getPositionInodobyName(name_file_direc, b_apuntador, 2);
                if(indice_inodo >= 0){
                     return indice_inodo;
                }
            }

        }
        else if(i == 15){
            //Aparecen bloques apuntadores
            if(inodo_apuntador.b_pointers[i] >= 0){
                //Sacamos el bloque carpeta
                BApuntador b_apuntador = getBloqueApuntador(disco, super.s_block_start, inodo_apuntador.b_pointers[i]);
                int indice_inodo = getPositionInodobyName(name_file_direc, b_apuntador, 3);
                if(indice_inodo >= 0){
                     return indice_inodo;
                }
            }
        }
    }
    return -1;
}

/*##################################################################################################################################
                                    METODOS PARA CREAR CARPETA
##################################################################################################################################*/

QString f2_archivo::getPathString(QStringList path){
    QString txt;
    foreach (QString directory, path) {
        txt += "/"+directory;
    }
    return txt;
}

QString f2_archivo::getcontentString(QStringList content){
    QString txt;
    foreach (QString directory, content) {
        txt += directory;
        if(txt.size() > 130){break;}
    }
    return txt;
}

int f2_archivo::escribirCarpeta(){
/* Crea un inodod carpeta, su bloque apuntador y su bloque carpeta,
 * escribe las 3 estructuras en el archivo(disco)
 * Retorna el indice del inodo creado
 * Retorna -1 si hay error
*/
    int libre_inodo = getFreeIndexBitmapInodo();
    int bloque_apuntador_libre = getFreeIndexBitmapBlock();
    int bloque_carpeta_libre = getFreeIndexBitmapBlock();
    if(libre_inodo >= 0 && bloque_apuntador_libre >= 0 && bloque_carpeta_libre > 0){
        //Crear Carpeta raiz
        Inodo inodo;
        inodo.i_uid = usr_id;
        inodo.i_gid = usr_grp_id;
        inodo.i_size = 0;
        inodo.i_atime = time(NULL);
        inodo.i_ctime = time(NULL);
        inodo.i_mtime = time(NULL);
        inodo.i_block = bloque_apuntador_libre;//enlazamos inodo con blooque apuntador
        inodo.i_type = '0';//Carpeta
        inodo.i_perm = 664;

        //Crear Nodo apuntador----------------------------------------------
        BApuntador apuntador;
        //Ocupamos el primer espacio del bloque apuntador
        //y lo apuntamos a el bloque carpeta(bloque 1)
        apuntador.b_pointers[0] = bloque_carpeta_libre;
        for(int i= 1; i < 16 ; i++){
            apuntador.b_pointers[i] = -1;
        }
        //Crer Bloque carpeta------------------------------------------------
        BCarpeta carpeta;
        for (int i=0; i < 4; i++) {
            carpeta.b_content[i].b_inodo = -1;
        }

        //Escribir el inodo
        escribirInodo(disco, inodo, this->super.s_inode_start, libre_inodo);
        //Escribir bloques
        escribirBloque(disco, apuntador, this->super.s_block_start, bloque_apuntador_libre);
        escribirBloque(disco, carpeta, this->super.s_block_start, bloque_carpeta_libre);

        return libre_inodo;

    }else{cout<<"\033[31mERROR: Ya no hay espacio para crear carpetas o archivos.\033[0m"<<endl<<endl; return -1;}
}

int f2_archivo::escribirCarpeta_(int puntero_actual, QString nombre_carpeta, int nivel_puntero_indirecto){
/*
 * Busca un espacio entre puntadores directos e indirectos
 * retorna un numero mayor igual 0 si se necesita enlazar
 * retorna -1 si la carpeta se creo
 * retorna -2 ecurrio un error no se creo la carpeta(Posiblemente no haya espacio para mas bloques)
 */

    if(nivel_puntero_indirecto >= 0 && nivel_puntero_indirecto <= 3){
        if(nivel_puntero_indirecto == 0){
            //Puntero directo
            if(puntero_actual == -1){

                int libre_bloque = getFreeIndexBitmapBlock();
                int libre_inodo = escribirCarpeta();
                if(libre_inodo >= 0){
                    BCarpeta carpeta;
                    carpeta.b_content[0].b_inodo = libre_inodo;
                    strcpy(carpeta.b_content[0].b_name, nombre_carpeta.toStdString().c_str());
                    for (int i=1; i < 4; i++) {
                        carpeta.b_content[i].b_inodo = -1;
                    }
                    escribirBloque(disco, carpeta, super.s_block_start, libre_bloque);
                    //cout<<"Carpeta creada correctamente"<<endl<<endl;
                    return libre_bloque;//para enlazar con puntero actual
                }
            }else{
                //Sacamos el bloque carpeta
                BCarpeta b_carpeta = getBloqueCarpeta(disco, super.s_block_start, puntero_actual);
                for(int i = 0; i < 4; i++){
                    if(b_carpeta.b_content[i].b_inodo == -1){
                        int libre_inodo = escribirCarpeta();
                        if(libre_inodo >= 0){
                            b_carpeta.b_content[i].b_inodo = libre_inodo;
                            strcpy(b_carpeta.b_content[i].b_name, nombre_carpeta.toStdString().c_str());
                            escribirBloque(disco, b_carpeta, super.s_block_start,puntero_actual);
                            //cout<<"Carpeta creada correctamente"<<endl<<endl;
                            return -1;
                        }
                    }
                }
            }
        }else{
            //puntero indirecto simple
            if(puntero_actual == -1){
                //Crear Bloques nivel 1 y crear carpeta
                int indice_nuevo = getFreeIndexBitmapBlock();
                BApuntador b_nuevo;
                for (int i = 0; i < 16; i++) {
                    b_nuevo.b_pointers[i] = -1;
                }
                int resultado = escribirCarpeta_(-1, nombre_carpeta, nivel_puntero_indirecto-1);
                if(resultado > 0){
                    b_nuevo.b_pointers[0] = resultado;
                    escribirBloque(disco, b_nuevo, super.s_block_start, indice_nuevo);
                    return indice_nuevo;
                }
            }else{
                //Recorrer bloques nivel 1, buscar espacio vacio(-1)
                //Nivel indirecto  simple Hijos son bloques carptesa y archivos
                BApuntador b_apuntador = getBloqueApuntador(disco, super.s_block_start, puntero_actual);
                for (int i = 0; i < 16; i++) {
                    int indice_b_carpeta = b_apuntador.b_pointers[i];
                    int resultado = escribirCarpeta_(indice_b_carpeta, nombre_carpeta, nivel_puntero_indirecto -1);
                    if(resultado > 0){
                        b_apuntador.b_pointers[i] = resultado;
                        escribirBloque(disco, b_apuntador, super.s_block_start, puntero_actual);
                        return -1;
                    }
                }
            }
        }
    }
    return -2;
}

int f2_archivo::crearCarpeta_(Inodo inodo_current, QStringList &path, int pos_actual, bool p){
    /*
     * Retorna 0 si se guardó la carpeta
     * Retorna 1 con error
     * Retorna 2 no existen carpetas padres
     * Retorna 3 si el nombre ya existe
    */
    if((path.size() - pos_actual) == 1){
        //verificar si se tiene permiso de escritura del inodo actual
        //lectura, escritura, ejecucion
        if(usr_id != 1){
            Permiso p = verificarPermiso(inodo_current);
            if(p.escritura == 0){
                cout<<"\033[31mERROR: No tiene permisos para crear la carpeta.\033[0m"<<endl<<endl;
                return 1;
            }
        }
        int nombre_existe =existInodobyName(inodo_current, path.value(pos_actual));
        if(nombre_existe > 0){return 3;}
        //En este caso estoy en el ultima carpeta del path
        //Por ello es la carpeta que se guarda y se buscará el espacio
        //Obtengo los apuntadores del inodo, el numero del bloque apuntador está en su variable i_block
        BApuntador inodo_apuntador = getBloqueApuntador(disco, super.s_block_start, inodo_current.i_block);
        //Recorremos los espacios de los apuntadores
        for(int b =0; b < 16; b++){
            int indice_puntero = inodo_apuntador.b_pointers[b];
            if(b <= 12 ){
                // De 0 a 12 es apuntador directo
                int resultado = escribirCarpeta_(indice_puntero, path.value(pos_actual),0);
                if(resultado > 0){
                    inodo_apuntador.b_pointers[b] = resultado;
                    escribirBloque(disco, inodo_apuntador, super.s_block_start, inodo_current.i_block);
                    agregarJournal("mkdir", getPathString(path), "-----", '0');
                    return 0;
                }else if(resultado == -1){
                    agregarJournal("mkdir", getPathString(path), "-----", '0');
                    return 0;
                }
            }
            else if(b == 13){
                //Aparecen bloques apuntadores nivel 1
                int resultado = escribirCarpeta_(indice_puntero, path.value(pos_actual),1);
                if(resultado > 0){
                    inodo_apuntador.b_pointers[b] = resultado;
                    escribirBloque(disco, inodo_apuntador, super.s_block_start, inodo_current.i_block);
                    agregarJournal("mkdir", getPathString(path), "-----", '0');
                    return 0;
                }else if(resultado == -1){
                    agregarJournal("mkdir", getPathString(path), "-----", '0');
                    return 0;
                }
            }
            else if(b == 14){
                //Aparecen bloques apuntadores nivel 2
                int resultado = escribirCarpeta_(indice_puntero, path.value(pos_actual),2);
                if(resultado > 0){
                    inodo_apuntador.b_pointers[b] = resultado;
                    escribirBloque(disco, inodo_apuntador, super.s_block_start, inodo_current.i_block);
                    agregarJournal("mkdir", getPathString(path), "-----", '0');
                    return 0;
                }else if(resultado == -1){
                    agregarJournal("mkdir", getPathString(path), "-----", '0');
                    return 0;
                }
            }
            else if(b == 15){
                //Aparecen bloques apuntadores nivel 3
                int resultado = escribirCarpeta_(indice_puntero, path.value(pos_actual),3);
                if(resultado > 0){
                    inodo_apuntador.b_pointers[b] = resultado;
                    escribirBloque(disco, inodo_apuntador, super.s_block_start, inodo_current.i_block);
                    agregarJournal("mkdir", getPathString(path), "-----", '0');
                    return 0;
                }else if(resultado == -1){
                    agregarJournal("mkdir", getPathString(path), "-----", '0');
                    return 0;
                }
            }
        }
        return 1;
    }else{
        //En este caso aun tengo que llegar al final del path

        int indice_inodo_next = existInodobyName(inodo_current, path.value(pos_actual));
        int existeCarpeta = 2;
        if(indice_inodo_next > 0){
            Inodo siguiente = getInodo(disco, super.s_inode_start, indice_inodo_next);
            if(siguiente.i_type == '0'){
                //Si el inodo es carpeta
                return crearCarpeta_(siguiente, path, pos_actual+1, p);
            }
        }
        if(existeCarpeta == 2 && p){
            //Si no existe carptea y p = true crear todas las carpetas del path
            QStringList ruta;
            int resultado = 1;
            for(int i = 0; i < pos_actual; i++){
                ruta.append(path.value(i));
            }
            for (int i = pos_actual; i < path.size(); i++) {
                ruta.append(path.value(i));
                resultado = crearCarpeta_(inodo_current, ruta, pos_actual,false);
            }
            return resultado;
        }
        return 2;//Retorna cuando no existe las carpetas padres
    }
}

void f2_archivo::crearCarpeta(QString path, bool p){
    if(super.s_filesystem_type > 0){
        QStringList list_path = getPath(path);
        if(list_path.size() > 0){//Carpeta dentro de otra carpeta
            Inodo actual = getInodo(disco, super.s_inode_start, 0);//raiz está en la posicion 0
            int resultado = crearCarpeta_(actual, list_path, 0, p);
            switch (resultado) {
                case 0: actualizarSuperBloque(); cout<<"\033[96mLa carpeta se ha creado correctamente.\033[0m"<<endl<<endl; break;
                case 1:cout<<"\033[31mERROR: No se pudo crear la carpeta.\033[0m"<<endl<<endl;break;
                case 2:cout<<"\033[31mERROR: La ruta ingresada no existe.\033[0m"<<endl<<endl;break;
                case 3:cout<<"\033[31mERROR: El nombre ya existe.\033[0m"<<endl<<endl;break;
                default: cout<<"\033[31mERROR: No se pudo crear la carpeta.\033[0m"<<endl<<endl;;break;
            }
        }
        else{cout<<"\033[31mERROR: No se especificó una carpeta.\033[0m"<<endl<<endl;}
    }
    else{cout<<"\033[31mERROR: La partición no tiene formato.\033[0m"<<endl<<endl;}
}

/*##################################################################################################################################
                                    METODOS PARA CREAR ARCHIVOS
##################################################################################################################################*/
Permiso f2_archivo::getPermisoInodo(int permiso, char categoria){
    int digito = 0;
    switch (categoria) {
        case 'u': case 'U':
            digito = (float)permiso/(float)100;//resultado ultimo digito
        break;
        case 'g': case 'G':
            digito = (float)permiso/(float)10;
            digito = digito % 10;
        break;
        case 'o': case 'O':
            digito = permiso % 10;
        break;
        default:
            digito = 0;
    }
    Permiso r;
    switch (digito) {
        case 0://000
            r.lectura = 0; r.escritura = 0; r.ejecucion = 0;
        break;
        case 1:
            r.lectura = 0; r.escritura = 0; r.ejecucion = 1;
        break;
        case 2:
            r.lectura = 0; r.escritura = 1; r.ejecucion = 0;
        break;
        case 3:
            r.lectura = 0; r.escritura = 1; r.ejecucion = 1;
        break;
        case 4:
            r.lectura = 1; r.escritura = 0; r.ejecucion = 0;
        break;
        case 5:
            r.lectura = 1; r.escritura = 0; r.ejecucion = 1;
        break;
        case 6:
            r.lectura = 1; r.escritura = 1; r.ejecucion = 0;
        break;
        case 7:
            r.lectura = 1; r.escritura = 1; r.ejecucion = 1;
        break;
        default:
            r.lectura = 0; r.escritura = 0; r.ejecucion = 0;
        break;
    }
    return r;
}

Permiso f2_archivo::verificarPermiso(Inodo inodo){
    //Si no es un usuario root
    int permisos = inodo.i_perm;
    if(inodo.i_uid == usr_id){
        //La carpeta es propiedad del usuario(U)
        return getPermisoInodo(permisos, 'u');
    }
    else{
        //La carpeta no es propiedad del usuario
        if(inodo.i_gid == usr_grp_id){
            return getPermisoInodo(permisos, 'g');
        }else{
            //Es otro usuario (O)
            return getPermisoInodo(permisos, 'o');
        }
    }
}

int f2_archivo::escribirContenidos(QListIterator<QString> &content, int espacio_actual, int nivel){
    /*
     * Busca un espacio entre puntadores directos e indirectos
     * retorna un numero mayor igual 0 si se necesita enlazar
     * retorna -1 si la carpeta se creo
     * retorna -2 ecurrio un error no se creo la carpeta(Posiblemente no haya espacio para mas bloques)
     */
        if(nivel >= 0 && nivel <= 3){
            if(nivel == 0){
                //Puntero directo
                if(espacio_actual == -1){
                    if(content.hasNext()){
                        int libre_bloque = getFreeIndexBitmapBlock();
                        BArchivo nuevo;
                        //QString write = content.next();
                        strcpy(nuevo.b_content, content.next().toStdString().c_str());
                        //cout<<nuevo.b_content<<endl;
                        escribirBloque(disco, nuevo, super.s_block_start, libre_bloque);
                        //cout<<"Carpeta creada correctamente"<<endl<<endl;
                        return libre_bloque;//para enlazar con puntero actual
                    }
                }
                return -1;

            }else{
                if(espacio_actual == -1){
                    //Crear Bloques nivel 1 y crear carpeta
                    if(content.hasNext()){
                        int indice_nuevo = getFreeIndexBitmapBlock();
                        BApuntador b_nuevo;
                        for (int i = 0; i < 16; i++) {
                            b_nuevo.b_pointers[i] = -1;
                        }
                        escribirBloque(disco, b_nuevo, super.s_block_start, indice_nuevo);
                        escribirContenidos(content, indice_nuevo , nivel);
                        return indice_nuevo;
                    }
                    return -1;
                }else{
                    //Recorrer bloques nivel 1, buscar espacio vacio(-1)
                    //Nivel indirecto  simple Hijos son bloques carptesa y archivos
                    if(content.hasNext()){
                        BApuntador b_apuntador = getBloqueApuntador(disco, super.s_block_start, espacio_actual);
                        for (int i = 0; i < 16; i++) {
                            int indice_b_carpeta = b_apuntador.b_pointers[i];
                            int resultado = escribirContenidos(content, indice_b_carpeta, nivel -1);
                            if(resultado > 0){
                                b_apuntador.b_pointers[i] = resultado;
                            }
                            else if(resultado == -2){return -2;}
                        }
                        escribirBloque(disco, b_apuntador, super.s_block_start, espacio_actual);
                    }
                    return -1;
                }
            }
        }
        return -2;
}

int f2_archivo::crearBloquesArchivo(QListIterator<QString> &content, BApuntador& b_apuntador){
//retorna -1 si hay error
    for (int i = 0; i < 16;i++) {
        if(!content.hasNext()){break;}
        if(i >= 0 && i <=12){
            int resultado = escribirContenidos(content, b_apuntador.b_pointers[i], 0);
            if(resultado >= 0 ){
                b_apuntador.b_pointers[i] = resultado;
            }else if(resultado == -2){break;}
        }else if(i == 13){
            int resultado = escribirContenidos(content, b_apuntador.b_pointers[i], 1);
            if(resultado >= 0 ){
                b_apuntador.b_pointers[i] = resultado;
            }else if(resultado == -2){break;}
        }else if(i == 14){
            int resultado = escribirContenidos(content, b_apuntador.b_pointers[i], 2);
            if(resultado >= 0 ){
                b_apuntador.b_pointers[i] = resultado;
            }else if(resultado == -2){break;}
        }else if(i == 15){
            int resultado = escribirContenidos(content, b_apuntador.b_pointers[i], 3);
            if(resultado >= 0 ){
                b_apuntador.b_pointers[i] = resultado;
            }else if(resultado == -2){break;}
        }
    }
    if(content.hasNext()){
        //Si el contenido tiene datos sin agregar, se retorna con error
        return -1;
    }else{
        //Si el contenido ya no tiene datos entonces se retorna sin error
        return 0;
    }
}

int f2_archivo::escribirArchivo(QStringList contenido){
/* Crea un inodod carpeta, su bloque apuntador y su bloque carpeta,
 * escribe las 3 estructuras en el archivo(disco)
 * Retorna el indice del inodo creado
 * Retorna -1 si hay error
*/

    int libre_inodo = getFreeIndexBitmapInodo();
    int bloque_apuntador_libre = getFreeIndexBitmapBlock();
    if(libre_inodo >= 0 && bloque_apuntador_libre >= 0 ){
        //Crear Carpeta raiz
        Inodo inodo;
        inodo.i_uid = usr_id;
        inodo.i_gid = usr_grp_id;
        inodo.i_size = (contenido.size()*64);
        inodo.i_atime = time(NULL);
        inodo.i_ctime = time(NULL);
        inodo.i_mtime = time(NULL);
        inodo.i_block = bloque_apuntador_libre;//enlazamos inodo con blooque apuntador
        inodo.i_type = '1';//Archivo
        inodo.i_perm = 664;

        //Crear Nodo apuntador----------------------------------------------
        BApuntador apuntador;
        //Ocupamos el primer espacio del bloque apuntador
        //y lo apuntamos a el bloque carpeta(bloque 1)
        //apuntador.b_pointers[0] = bloque_carpeta_libre;

        for(int i= 0; i < 16 ; i++){
            apuntador.b_pointers[i] = -1;
        }

        if(contenido.size() > 0){
            //Si hay contenido lo crea
            int resultado = 0;
            QListIterator<QString> iter(contenido);
            resultado = crearBloquesArchivo(iter, apuntador);
            if(resultado != 0 ){return -1;}
        }
        //Escribir el inodo
        escribirInodo(disco, inodo, this->super.s_inode_start, libre_inodo);
        //Escribir bloques
        escribirBloque(disco, apuntador, this->super.s_block_start, bloque_apuntador_libre);
        return libre_inodo;

    }else{cout<<"\033[31mERROR: Ya no hay espacio para crear carpetas o archivos.\033[0m"<<endl<<endl; return -1;}
}

int f2_archivo::escribirArchivo_(int puntero_actual, QString nombre_archivo, QStringList contenido, int nivel_puntero_indirecto){
/*
 * Busca un espacio entre puntadores directos e indirectos
 * retorna un numero mayor igual 0 si se necesita enlazar
 * retorna -1 si el archivo se creo
 * retorna -2 ecurrio un error no se creo la carpeta(Posiblemente no haya espacio para mas bloques)
 */

    if(nivel_puntero_indirecto >= 0 && nivel_puntero_indirecto <= 3){
        if(nivel_puntero_indirecto == 0){

            //Puntero directo
            if(puntero_actual == -1){

                int libre_bloque = getFreeIndexBitmapBlock();
                int libre_inodo = escribirArchivo(contenido);
                if(libre_inodo >= 0){
                    BCarpeta carpeta;
                    carpeta.b_content[0].b_inodo = libre_inodo;
                    strcpy(carpeta.b_content[0].b_name, nombre_archivo.toStdString().c_str());
                    for (int i=1; i < 4; i++) {
                        carpeta.b_content[i].b_inodo = -1;
                    }
                    escribirBloque(disco, carpeta, super.s_block_start, libre_bloque);
                    //cout<<"Carpeta creada correctamente"<<endl<<endl;
                    return libre_bloque;//para enlazar con puntero actual
                }
            }else{
                //Sacamos el bloque carpeta
                BCarpeta b_carpeta = getBloqueCarpeta(disco, super.s_block_start, puntero_actual);
                for(int i = 0; i < 4; i++){
                    if(b_carpeta.b_content[i].b_inodo == -1){
                        int libre_inodo = escribirArchivo(contenido);
                        if(libre_inodo >= 0){
                            strcpy(b_carpeta.b_content[i].b_name, nombre_archivo.mid(0,12).toStdString().c_str());
                            b_carpeta.b_content[i].b_inodo = libre_inodo;
                            escribirBloque(disco, b_carpeta, super.s_block_start,puntero_actual);
                            //cout<<"Carpeta creada correctamente"<<endl<<endl;
                            return -1;
                        }
                    }
                }
            }
        }else{
            //puntero indirecto simple
            if(puntero_actual == -1){
                //Crear Bloques nivel 1 y crear carpeta
                int indice_nuevo = getFreeIndexBitmapBlock();
                BApuntador b_nuevo;
                for (int i = 0; i < 16; i++) {
                    b_nuevo.b_pointers[i] = -1;
                }
                int resultado = escribirArchivo_(-1, nombre_archivo, contenido,nivel_puntero_indirecto-1);
                if(resultado > 0){
                    b_nuevo.b_pointers[0] = resultado;
                    escribirBloque(disco, b_nuevo, super.s_block_start, indice_nuevo);
                    return indice_nuevo;
                }
            }else{
                //Recorrer bloques nivel 1, buscar espacio vacio(-1)
                //Nivel indirecto  simple Hijos son bloques carptesa y archivos
                BApuntador b_apuntador = getBloqueApuntador(disco, super.s_block_start, puntero_actual);
                for (int i = 0; i < 16; i++) {
                    int indice_b_carpeta = b_apuntador.b_pointers[i];
                    int resultado = escribirArchivo_(indice_b_carpeta, nombre_archivo, contenido, nivel_puntero_indirecto -1);
                    if(resultado > 0){
                        b_apuntador.b_pointers[i] = resultado;
                        escribirBloque(disco, b_apuntador, super.s_block_start, puntero_actual);
                        return -1;
                    }
                }
            }
        }
    }
    return -2;
}

int f2_archivo::crearArchivo_(Inodo inodo_current, QStringList contenido, QStringList &path, int pos_actual, bool p){
    /*
     * Retorna 0 si se guardó la carpeta
     * Retorna 1 con error
     * Retorna 2 no existen carpetas padres
     * Retorna 3 si el nombre ya existe
    */
    if((path.size() - pos_actual) == 1){
        //verificar si se tiene permiso de escritura del inodo actual
        //lectura, escritura, ejecucion
        if(usr_id != 1){
            Permiso p = verificarPermiso(inodo_current);
            if(p.escritura == 0){
                cout<<"\033[31mERROR: No tiene permisos para crear el archivo.\033[0m"<<endl<<endl;
                return 1;
            }
        }
        //Elimina si existe un archivo
        if(removeCarpeta_Archivo(inodo_current, path.value(pos_actual)) == 2){
            cout<<"\033[31mERROR: El archivo ya existe y no tiene permisos para sobreescribirlo.\033[0m"<<endl<<endl;
            return 1;
        }

        //En este caso estoy en el ultima carpeta del path
        //Por ello es la carpeta que se guarda y se buscará el espacio
        //Obtengo los apuntadores del inodo, el numero del bloque apuntador está en su variable i_block
        BApuntador inodo_apuntador = getBloqueApuntador(disco, super.s_block_start, inodo_current.i_block);
        //Recorremos los espacios de los apuntadores
        for(int b =0; b < 16; b++){
            int indice_puntero = inodo_apuntador.b_pointers[b];
            if(b <= 12 ){
                // De 0 a 12 es apuntador directo
                int resultado = escribirArchivo_(indice_puntero, path.value(pos_actual), contenido,0);
                if(resultado > 0){
                    inodo_apuntador.b_pointers[b] = resultado;
                    escribirBloque(disco, inodo_apuntador, super.s_block_start, inodo_current.i_block);
                    inodo_current.i_size += (contenido.size()*64);
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }else if(resultado == -1){
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }
            }
            else if(b == 13){
                //Aparecen bloques apuntadores nivel 1
                int resultado = escribirArchivo_(indice_puntero, path.value(pos_actual), contenido,1);
                if(resultado > 0){
                    inodo_apuntador.b_pointers[b] = resultado;
                    escribirBloque(disco, inodo_apuntador, super.s_block_start, inodo_current.i_block);
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }else if(resultado == -1){
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }
            }
            else if(b == 14){
                //Aparecen bloques apuntadores nivel 2
                int resultado = escribirArchivo_(indice_puntero, path.value(pos_actual), contenido,2);
                if(resultado > 0){
                    inodo_apuntador.b_pointers[b] = resultado;
                    escribirBloque(disco, inodo_apuntador, super.s_block_start, inodo_current.i_block);
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }else if(resultado == -1){
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }
            }
            else if(b == 15){
                //Aparecen bloques apuntadores nivel 3
                int resultado = escribirArchivo_(indice_puntero, path.value(pos_actual), contenido,3);
                if(resultado > 0){
                    inodo_apuntador.b_pointers[b] = resultado;
                    escribirBloque(disco, inodo_apuntador, super.s_block_start, inodo_current.i_block);
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }else if(resultado == -1){
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }
            }
        }
        return 1;
    }else{
        //En este caso aun tengo que llegar al final del path
        int indice_inodo_next = existInodobyName(inodo_current, path.value(pos_actual));
        int existeCarpeta = 2;
        if(indice_inodo_next > 0){
            Inodo siguiente = getInodo(disco, super.s_inode_start, indice_inodo_next);
            if(siguiente.i_type == '0'){
                //Si el inodo es carpeta
                return crearArchivo_(siguiente, contenido, path, pos_actual+1, p);
            }
        }
        if(existeCarpeta == 2 && p){
            //Si no existe carptea y p = true crear todas las carpetas del path
            QStringList ruta;
            int resultado = 1;
            for(int i = 0; i < pos_actual; i++){
                ruta.append(path.value(i));
            }
            for (int i = pos_actual; i < path.size() ; i++) {
                ruta.append(path.value(i));
                if(i == path.size() -1){
                    resultado = crearArchivo_(inodo_current, contenido, ruta, pos_actual, false);
                }else{
                    resultado = crearCarpeta_(inodo_current, ruta, pos_actual,false);
                }
            }
            return resultado;
        }
        return 2;//Retorna cuando no existe las carpetas padres


    }
    return 0;
}

void f2_archivo::crearArchivo(QString path, QStringList contenido, bool p){
    if(super.s_filesystem_type > 0){
        QStringList list_path = getPath(path);
        if(list_path.size() > 0){//Carpeta dentro de otra carpeta
            Inodo actual = getInodo(disco, super.s_inode_start, 0);//raiz está en la posicion 0
            int resultado = crearArchivo_(actual, contenido, list_path, 0, p);
            switch (resultado) {
                case 0: actualizarSuperBloque(); cout<<"\033[96mEl archivo se ha creado correctamente.\033[0m"<<endl<<endl; break;
                case 1:cout<<"\033[31mERROR: No se pudo crear el archivo.\033[0m"<<endl<<endl;break;
                case 2:cout<<"\033[31mERROR: La ruta ingresada no existe.\033[0m"<<endl<<endl;break;
                case 3:cout<<"\033[31mERROR: El nombre ya existe.\033[0m"<<endl<<endl;break;
                default: cout<<"\033[31mERROR: No se pudo crear el archivo.\033[0m"<<endl<<endl;;break;
            }
        }
        else{cout<<"\033[31mERROR: No se especificó una carpeta.\033[0m"<<endl<<endl;}
    }
    else{cout<<"\033[31mERROR: La partición no tiene formato.\033[0m"<<endl<<endl;}
}

int f2_archivo::createFile(QString path, QStringList contenido, bool p){
    if(super.s_filesystem_type > 0){
        QStringList list_path = getPath(path);
        if(list_path.size() > 0){//Carpeta dentro de otra carpeta
            Inodo actual = getInodo(disco, super.s_inode_start, 0);//raiz está en la posicion 0
            int resultado = crearArchivo_(actual, contenido, list_path, 0, p);
            if(resultado == 0){actualizarSuperBloque();}
            return resultado;
            /*switch (resultado) {
                case 0: actualizarSuperBloque(); cout<<"El archivo se ha creado correctamente"<<endl<<endl; break;
                case 1:cout<<"\033[31mERROR: No se pudo crear el archivo"<<endl<<endl;break;
                case 2:cout<<"\033[31mERROR: La ruta ingresada no existe"<<endl<<endl;break;
                case 3:cout<<"\033[31mERROR: El nombre ya existe"<<endl<<endl;break;
                default: cout<<"\033[31mERROR: No se pudo crear el archivo"<<endl<<endl;;break;
            }*/
        }
        else{cout<<"\033[31mERROR: No se especificó una carpeta.\033[0m"<<endl<<endl;}
    }
    else{cout<<"\033[31mERROR: La partición no tiene formato.\033[0m"<<endl<<endl;}
    return 1;
}

/*##################################################################################################################################
                                    METODOS ELIMINAR CARPETAS Y ARCHIVOS
##################################################################################################################################*/

void f2_archivo::removeFileChilds(int espacio_apuntador, int nivel){
    //Retorna 0 si encontró y elimino la carpeta y archivo
    //Retorna 1 si no eliminó nada
    if(nivel >= 0 && nivel <= 3){
        if(nivel == 0){
            if(espacio_apuntador >= 0){
                //Hay bloques contenidos
                //Eliminamos el bloque del espacio inodo
                liberarBitmapBlock(espacio_apuntador);
            }
        }
        else{
            if(espacio_apuntador >= 0){
                //Sacamos el bloque carpeta
                BApuntador b_apuntador = getBloqueApuntador(disco, super.s_block_start, espacio_apuntador);
                //Eliminamos el bloque apuntador de los apuntadores indirectos
                liberarBitmapBlock(espacio_apuntador);
                for (int i = 0; i < 16; i++) {
                    int verificar_espacio = b_apuntador.b_pointers[i];
                    if(verificar_espacio == -1){break;}
                    removeFileChilds(verificar_espacio, nivel-1);
                }
            }
        }
    }
}

int f2_archivo::removeCarpetaChilds(int espacio_apuntador, int nivel){
//Las carpetas tienen hijos carpetas y archivos
//Retorna 0 si se elimino correcto
//Retorna 1 si no elimino nada
//Retorna 2 si no tiene permiso de eliminar
    if(nivel >= 0 && nivel <= 3){
        if(nivel == 0){
            //Cuanndo es nivel 0 tiene un bloque carpeta
            if(espacio_apuntador >= 0){
                //Sacamos el bloque carpeta
                BCarpeta b_carpeta = getBloqueCarpeta(disco, super.s_block_start, espacio_apuntador);
                //Eliminamos el bloque carpeta
                liberarBitmapBlock(espacio_apuntador);
                //Buscamos en bloque carpeta si el nombre existe
                int indice_inodo =-1;
                for(int c = 0; c < 4; c++){
                    indice_inodo = b_carpeta.b_content[c].b_inodo;
                    if(indice_inodo >= 0){
                        Inodo encontrado = getInodo(disco, super.s_inode_start, indice_inodo);
                        if(usr_id != 1){
                            Permiso p = verificarPermiso(encontrado);
                            if(p.escritura == 0){ return 2;}
                        }
                        //Eliminamos todos los hijos bloques e hijos inodos
                        if(removeInodoChilds(encontrado) == 2){ return 2;}
                        //Eliminamos el inodo
                        liberarBitmapInodo(indice_inodo);
                        //Eliminamos el bloque apuntadores indirectos y directos
                        liberarBitmapBlock(encontrado.i_block);
                    }
                }
                return 0;
            }
        }
        else{
            if(espacio_apuntador >= 0){
                //Sacamos el bloque carpeta
                BApuntador b_apuntador = getBloqueApuntador(disco, super.s_block_start, espacio_apuntador);
                //Eliminamos el bloque apuntador de los apuntadores indirectos
                liberarBitmapBlock(espacio_apuntador);
                int result = 0 ;
                for (int i = 0; i < 16; i++) {
                    int verificar_espacio = b_apuntador.b_pointers[i];
                    result = removeCarpetaChilds(verificar_espacio, nivel-1);
                    if(result == 2){return 2;}
                }
                return result;
            }
        }
    }
    return 1;
}

int f2_archivo::removeInodoChilds(Inodo inodo){
//Retorna 0 si elimino
//Retorna 1 no se eliminó nada
//Retorna 2 si no tiene permisos de eliminar
    BApuntador inodo_apuntador = getBloqueApuntador(disco, super.s_block_start, inodo.i_block);
    //Inodo Carpeta
    if(inodo.i_type == '0'){
        int result = 0;
        for (int i = 0; i < 16; i++) {
            if(i <= 12){
                result = removeCarpetaChilds(inodo_apuntador.b_pointers[i], 0);
            }
            else if(i == 13){
                result = removeCarpetaChilds(inodo_apuntador.b_pointers[i], 1);
            }
            else if(i == 14){
                result = removeCarpetaChilds(inodo_apuntador.b_pointers[i], 2);
            }
            else if(i == 15){
                result = removeCarpetaChilds(inodo_apuntador.b_pointers[i], 3);
            }
            if(result == 2){return 2;}
        }
        return 0;
    }
    //Inodo Archivo
    else if(inodo.i_type == '1'){
        for (int i = 0; i < 16; i++) {
            if(inodo_apuntador.b_pointers[i] == -1){break;}
            if(i <= 12){
                removeFileChilds(inodo_apuntador.b_pointers[i], 0);
            }
            else if(i == 13){
                removeFileChilds(inodo_apuntador.b_pointers[i], 1);
            }
            else if(i == 14){
                removeFileChilds(inodo_apuntador.b_pointers[i], 2);
            }
            else if(i == 15){
                removeFileChilds(inodo_apuntador.b_pointers[i], 3);
            }
        }
        return 0;
    }
    return 1;
}

int f2_archivo::removeCarpeta_Archivo_(QString name_file_direc, int espacio_apuntador,int nivel_puntero_indirecto){
    //Retorna 0 si encontró y elimino la carpeta y archivo
    //Retorna 1 si no eliminó nada
    //Retorna 2 si no tiene permiso de eliminar
    if(nivel_puntero_indirecto >= 0 && nivel_puntero_indirecto <= 3){
        if(nivel_puntero_indirecto == 0){
            if(espacio_apuntador >= 0){
                //Sacamos el bloque carpeta
                BCarpeta b_carpeta = getBloqueCarpeta(disco, super.s_block_start, espacio_apuntador);
                //Buscamos en bloque carpeta si el nombre existe
                for(int c = 0; c < 4; c++){
                    if(b_carpeta.b_content[c].b_inodo >= 0){
                        if(QString::compare(b_carpeta.b_content[c].b_name, name_file_direc,Qt::CaseSensitive) == 0){
                            //Si el nombre de la carpeta o archivo existe entonces
                            //Eliminamos el inodo del bloque carpeta y el bitmap inodo
                            int indice_inodo = b_carpeta.b_content[c].b_inodo;
                            Inodo encontrado = getInodo(disco, super.s_inode_start, indice_inodo);
                            if(usr_id != 1){
                                Permiso p = verificarPermiso(encontrado);
                                if(p.escritura == 0){  return 2; }
                            }
                            //Eliminamos todos los bloques e inodos
                            if(removeInodoChilds(encontrado) == 2){return 2;}
                            //Eliminamos el inodo del bloque carpeta
                            b_carpeta.b_content[c].b_inodo = -1;
                            //Eliminamos el inodo del bitmapInodo
                            liberarBitmapInodo(indice_inodo);
                             //Eliminamos el bloque apuntadores indirectos y directos
                            liberarBitmapBlock(encontrado.i_block);
                            //Actualizamos el bloque
                            escribirBloque(disco, b_carpeta,super.s_block_start, espacio_apuntador);
                            return 0;
                        }
                    }
                }
            }
        }
        else{
            if(espacio_apuntador >= 0){
                //Sacamos el bloque carpeta
                BApuntador b_apuntador = getBloqueApuntador(disco, super.s_block_start, espacio_apuntador);
                int result = 0;
                for (int i = 0; i < 16; i++) {
                    int verificar_espacio = b_apuntador.b_pointers[i];
                    result = removeCarpeta_Archivo_(name_file_direc, verificar_espacio, nivel_puntero_indirecto -1 );
                    if(result == 2){ return 2;}
                }
            }
        }
    }
    return 1;
}

int f2_archivo::removeCarpeta_Archivo(Inodo inodo_current, QString name_file_direc){
//Retorna 0 si encontró y elimino la carpeta y archivo
//Retorna 1 si no eliminó nada
    //Obtenemos los 16 apuntadores del inodo actual
    BApuntador inodo_apuntador = getBloqueApuntador(disco, super.s_block_start, inodo_current.i_block);
    int resultado = -1;
    //Buscamos espacios ocupados en los 16 apuntadores
    for (int i = 0; i < 16; i++) {
        if(resultado == 0){break;}
        if(i <= 12){
            resultado = removeCarpeta_Archivo_(name_file_direc, inodo_apuntador.b_pointers[i], 0);
        }
        else if(i == 13){
            resultado = removeCarpeta_Archivo_(name_file_direc, inodo_apuntador.b_pointers[i], 1);
        }
        else if(i == 14){
            resultado = removeCarpeta_Archivo_(name_file_direc, inodo_apuntador.b_pointers[i], 2);
        }
        else if(i == 15){
            resultado = removeCarpeta_Archivo_(name_file_direc, inodo_apuntador.b_pointers[i], 3);
        }
    }
    return resultado;
}

int f2_archivo::rem(QString path){
// retorna 0 si el archivo/carpeta se eliminó
// retorna 1 si el archivo/carpeta no existe
// retorna 2 si no tiene permiso para eliminar el archivo/carpeta
    Inodo_dato find = getInodoByPath(path);
    if(find.inodo > 0){

        //cout<<"Inodo:"<<find.inodo<<"  Bloque Padre:"<<find.bloque_padre<<" Posicion:"<<find.posicion<<endl<<endl;
        Inodo inodo = getInodo(disco, super.s_inode_start, find.inodo);
        Permiso p = verificarPermiso(inodo);
        if(p.escritura == 1 || usr_id == 1){
            //Eliminamos todos los bloques e inodos hijos
            agregarJournal("rem", path, "-----", inodo.i_type);
            if(removeInodoChilds(inodo) == 2){return 2;}
            BCarpeta padre = getBloqueCarpeta(disco, super.s_block_start, find.bloque_padre);
            //Eliminamos el inodo del bloque carpeta padre
            padre.b_content[find.posicion].b_inodo = -1;
            //Eliminamos el inodo del bitmapInodo
            liberarBitmapInodo(find.inodo);
            //Eliminamos el bloque apuntadores indirectos y directos
            liberarBitmapBlock(inodo.i_block);
            //Actualizamos el bloque carpeta padre
            escribirBloque(disco, padre, super.s_block_start, find.bloque_padre);
            //Actualizamos el super bloque
            actualizarSuperBloque();
            return 0;
        }else{return 2;}
    }else{ return  1;}
}

int f2_archivo::reRem(QString path){
// retorna 0 si el archivo/carpeta se eliminó
// retorna 1 si el archivo/carpeta no existe
// retorna 2 si no tiene permiso para eliminar el archivo/carpeta
    Inodo_dato find = getInodoByPath(path);
    if(find.inodo > 0){

        //cout<<"Inodo:"<<find.inodo<<"  Bloque Padre:"<<find.bloque_padre<<" Posicion:"<<find.posicion<<endl<<endl;
        Inodo inodo = getInodo(disco, super.s_inode_start, find.inodo);
        Permiso p = verificarPermiso(inodo);
        if(p.escritura == 1 || usr_id == 1){
            //Eliminamos todos los bloques e inodos hijos
            //agregarJournal("rem", path, "-----", inodo.i_type);
            if(removeInodoChilds(inodo) == 2){return 2;}
            BCarpeta padre = getBloqueCarpeta(disco, super.s_block_start, find.bloque_padre);
            //Eliminamos el inodo del bloque carpeta padre
            padre.b_content[find.posicion].b_inodo = -1;
            //Eliminamos el inodo del bitmapInodo
            liberarBitmapInodo(find.inodo);
            //Eliminamos el bloque apuntadores indirectos y directos
            liberarBitmapBlock(inodo.i_block);
            //Actualizamos el bloque carpeta padre
            escribirBloque(disco, padre, super.s_block_start, find.bloque_padre);
            //Actualizamos el super bloque
            //actualizarSuperBloque();
            cout<<"\033[96mSe ha eliminado el archivo/carpeta correctamente.\033[0m"<<endl<<endl;
            return 0;
        }else{return 2;}
    }else{ return  1;}
}

/*##################################################################################################################################
                                    METODOS PARA ENCONTRAR INODOS(CARPETA O ARCHIVO)
##################################################################################################################################*/
Inodo_dato f2_archivo::searchIndoByName_(QString name_file_direc, int espacio_apuntador,int nivel){
/* @name_file_direc: Nombre del archivo o carpeta buscado.
 * @espacio_apuntador: Apuntador directo o indirecto, si su valor es mayor a 0, apunta a un bloque
 * @nivel: Indica el tipo de apuntador es @espacio_apuntador,
 *          0 si es apuntador directo, 1 si es indirecto simple, 2 si es indirecto doble,
 *          3 si es indirecto triple.
 * Retorna Inodo_Dato
 */
    Inodo_dato retornar = {-1, -1, -1};
    if(nivel >= 0 && nivel <= 3){
        if(nivel == 0){
            //Puntero directo
            if(espacio_apuntador >= 0){
                //Sacamos el bloque carpeta
                BCarpeta b_carpeta = getBloqueCarpeta(disco, super.s_block_start, espacio_apuntador);
                for(int c = 0; c < 4; c++){
                    if(b_carpeta.b_content[c].b_inodo >= 0){
                        if(QString::compare(b_carpeta.b_content[c].b_name, name_file_direc,Qt::CaseSensitive) == 0){
                            retornar.bloque_padre = espacio_apuntador; //No bloque carpeta
                            retornar.posicion = c; //Posicion del inodo en bloque
                            retornar.inodo = b_carpeta.b_content[c].b_inodo; //No Inodo
                            return retornar;
                        }
                    }
                }
            }

        }else{
            if(espacio_apuntador >= 0){
                BApuntador b_apuntador = getBloqueApuntador(disco, super.s_inode_start, espacio_apuntador);
                for(int i = 0; i < 16; i ++){
                    Inodo_dato resultado = searchIndoByName_(name_file_direc, b_apuntador.b_pointers[i], nivel -1);
                    if(resultado.inodo >= 0){
                        return resultado;
                    }
                }
            }
        }
    }
    return retornar;
}

Inodo_dato f2_archivo::getInodoByPath_(Inodo inodo_current, QListIterator<QString> &path){
    /* @inodo_current: Inodo actual donde se busca.
     * @path: Ruta donde está la carpeta o archivo buscado.
     * Retorna Inodo_Dato
     */
    QString carpeta_actual = path.next();
    Inodo_dato resultado = {-1, -1, -1};
    if(!path.hasNext()){
        //En este caso se llego al ultimo elemento del path, el cual contiene el nombre de la carpeta o archivo
        BApuntador inodo_apuntador = getBloqueApuntador(disco, super.s_block_start, inodo_current.i_block);

        for (int i = 0; i < 16; i++) {
            if(i <= 12){
                resultado = searchIndoByName_(carpeta_actual, inodo_apuntador.b_pointers[i], 0);
                if(resultado.inodo >= 0){
                    return resultado;
                }
            }
            else if(i == 13){
                resultado = searchIndoByName_(carpeta_actual, inodo_apuntador.b_pointers[i], 1);
                if(resultado.inodo >= 0){
                    return resultado;
                }
            }
            else if(i == 14){
                //Aparecen bloques apuntadores
                resultado = searchIndoByName_(carpeta_actual, inodo_apuntador.b_pointers[i], 2);
                if(resultado.inodo >= 0){
                    return resultado;
                }

            }
            else if(i == 15){
                //Aparecen bloques apuntadores
                resultado = searchIndoByName_(carpeta_actual, inodo_apuntador.b_pointers[i], 3);
                if(resultado.inodo >= 0){
                    return resultado;
                }
            }
        }
    }else{
        //En este caso no se ha llegado al final(se busca llegar donde se encuentra el nombre de la carpeta o archivo)
        QStringList lista;
        lista.append(carpeta_actual);
        QListIterator<QString> iterador(lista);
        Inodo_dato dato_inodo_next = getInodoByPath_(inodo_current, iterador);
        if(dato_inodo_next.inodo >= 0){
            Inodo siguiente = getInodo(disco, super.s_inode_start, dato_inodo_next.inodo);
            if(siguiente.i_type == '0'){
                //Si el inodo es carpeta
                resultado = getInodoByPath_(siguiente, path);
                if(resultado.inodo >= 0){
                    return resultado;
                }
            }
        }

    }
    return resultado;
}

Inodo_dato f2_archivo::getInodoByPath(QString path){
    //Busca un inodo desde la raiz, mediante el path del archivo o carpeta buscado
    Inodo raiz = getInodo(disco, super.s_inode_start, 0);
    QListIterator<QString>  iterador(getPath(path));
    return getInodoByPath_(raiz, iterador);
}

/*##################################################################################################################################
                                    METODOS OBTENER DATOS DE ARCHIVOS
##################################################################################################################################*/

QString f2_archivo::getFileContent_(int espacio_apuntador, int nivel){
    //Retorna 0 si encontró y elimino la carpeta y archivo
    //Retorna 1 si no eliminó nada
    QString retornar = "";
    if(nivel >= 0 && nivel <= 3){
        if(nivel == 0){
            if(espacio_apuntador >= 0){
                //Hay bloques contenidos
                BArchivo contenido = getBloqueArchivo(disco, super.s_block_start, espacio_apuntador);
                QString addcontent(contenido.b_content);
                retornar += addcontent.mid(0,64);
                //cout<<"<INIT>"<<addcontent.toStdString()<<"<END>"<<endl<<endl;
            }
        }
        else{
            if(espacio_apuntador >= 0){
                //Sacamos el bloque carpeta
                BApuntador b_apuntador = getBloqueApuntador(disco, super.s_block_start, espacio_apuntador);
                for (int i = 0; i < 16; i++) {
                    int verificar_espacio = b_apuntador.b_pointers[i];
                    if(verificar_espacio == -1){break;}
                    retornar += getFileContent_(verificar_espacio, nivel-1);
                }
            }
        }
    }
    return retornar;
}

QString f2_archivo:: getFileContent(Inodo inodo){
    if(inodo.i_type == '0'){return "";}
    //Obtenemos los 16 apuntadores del inodo actual
    BApuntador inodo_apuntador = getBloqueApuntador(disco, super.s_block_start, inodo.i_block);
    QString resultado = "";
    //Buscamos espacios ocupados en los 16 apuntadores
    for (int i = 0; i < 16; i++) {
        if(i <= 12){
            resultado += getFileContent_(inodo_apuntador.b_pointers[i], 0);
        }
        else if(i == 13){
            resultado += getFileContent_(inodo_apuntador.b_pointers[i], 1);
        }
        else if(i == 14){
            resultado += getFileContent_(inodo_apuntador.b_pointers[i], 2);
        }
        else if(i == 15){
            resultado += getFileContent_(inodo_apuntador.b_pointers[i], 3);
        }
    }
    return resultado;
}

QListIterator<QString> f2_archivo::getDatosUsers(){
    Inodo inodo_users = getInodo(disco, super.s_inode_start, 1);//El archivo users.txt es el inodo 1
    QString content = getFileContent(inodo_users);
    QListIterator<QString> rows(content.split('\n'));
    return rows;
}

QStringList f2_archivo::contentList (QString contenido){
    QStringList lista;
    for(int i = 0; i < contenido.size(); i+= 64){
        QString aux = contenido.mid(i, 64);
        //cout<<"<begin>"<<aux.toStdString()<<"<end>"<<endl<<endl;
        lista.append(aux);
    }
    return  lista;
}

/*##################################################################################################################################
                                    METODOS INICIAR SESION
##################################################################################################################################*/

int f2_archivo::iniciarSesion(QString user, QString psw){
    QListIterator<QString> rows = getDatosUsers();
    QHash<QString, int> grupos;
    while (rows.hasNext()) {
        QString dato = rows.next();
        if(dato.size() == 0){break;}
        QStringList lista = dato.split(',');
        if(QString::compare(lista.value(1).trimmed(), "u", Qt::CaseInsensitive) == 0){
            int id = lista.value(0).trimmed().toInt();
            if(user.compare(lista.value(3).trimmed(), Qt::CaseSensitive) == 0 &&
               psw.compare(lista.value(4).trimmed(), Qt::CaseSensitive) == 0 &&  id > 0){
                group = lista.value(2).trimmed();
                group_id = grupos[lista.value(2).trimmed()];
                return id;
            }
        }
        else{
            grupos[lista.value(2).trimmed()] = lista.value(0).trimmed().toInt();
        }
    }
    return -1;
}

/*##################################################################################################################################
                                    METODOS CREAR Y ELIMINAR GRUPOS Y USUARIOS
##################################################################################################################################*/

void f2_archivo::chown(QString path, QString usr_new, bool r){
    //Retorna 0 si se cambió el propietario correctamente
    //Retorna 1 si el nombre no existe
    //Retorna 2 si la ruta no existe
    //Retorna 3 si no es propietario del archivo
    QListIterator<QString> rows = getDatosUsers();
    int current_id = 0;
    bool existe = false;
    QString grp;
    while (rows.hasNext()) {
        QString row = rows.next();
        if(row.size() > 0){
            QStringList lista = row.split(',');
            if(QString::compare(lista.value(1).trimmed(),"u", Qt::CaseInsensitive) == 0){
                current_id = lista.value(0).trimmed().toInt();//obtenemos el ultimo id del usuario
                if(usr_new.compare(lista.value(3).trimmed(), Qt::CaseSensitive) == 0 && current_id > 0){
                    //cout<<"USUARIO: "<<lista.value(0).trimmed().toStdString()<<" "<<lista.value(1).trimmed().toStdString()<<endl;
                    //cout<<lista.value(2).trimmed().toStdString()<<" "<<lista.value(3).trimmed().toStdString()<<endl;
                    grp = lista.value(2).trimmed();
                    existe = true;
                    break;
                }
            }
        }
    }
    if(existe){
        int grp_id =0;
        while (rows.hasPrevious()) {
            QString row = rows.previous();
            if(row.size() > 0){
                QStringList lista = row.split(',');
                if(QString::compare(lista.value(1).trimmed(),"g", Qt::CaseInsensitive) == 0){
                    grp_id = lista.value(0).trimmed().toInt();//obtenemos el ultimo id del usuario
                    if(grp.compare(lista.value(2).trimmed(), Qt::CaseSensitive) == 0 && grp_id > 0){
                        break;
                    }
                }
            }
        }
        Inodo_dato find = getInodoByPath(path);
        if(find.inodo > 0){
            Inodo inodo = getInodo(disco, super.s_inode_start, find.inodo);
            if(usr_id == 1 || inodo.i_uid == usr_id){
                //Aqui se tiene el permiso para cambiar el propietario
                //cambiamos el propietario
                inodo.i_uid = current_id;
                inodo.i_gid = grp_id;
                inodo.i_mtime = time(NULL);
                //Actualizamos el inodo
                escribirInodo(disco, inodo,super.s_inode_start,find.inodo );
                cout<<"\033[96mSe cambió el propietario correctamente.\033[0m"<<endl<<endl;
            }else{cout<<"\033[31mERROR: El usuario actual no es propietario del archivo/carpeta.\033[0m"<<endl<<endl;}
        }else{cout<<"\033[31mERROR: No existe la ruta ingresada.\033[0m"<<endl<<endl;}
    }else{cout<<"\033[31mERROR: El usuario ingresado no existe.\033[0m" <<endl<<endl;}
}

int f2_archivo::crearGrupo(QString name_grp){
    //Retorna 0 si se creo el grupo
    //Retorna 1 si el nombre ya existe
    //Retorna 2 si ocurrio un error
    QListIterator<QString> rows = getDatosUsers();
    QString newData;
    int ultimo_id = 0;
    int current_id = 0;
    bool existe_nombre = false;
    while (rows.hasNext()) {
        QString row = rows.next();
        if(row.size() > 0){
            newData += row + "\n";
            QStringList lista = row.split(',');
            if(QString::compare(lista.value(1).trimmed(),"g", Qt::CaseInsensitive) == 0){
                current_id = lista.value(0).trimmed().toInt();//obtenemos el ultimo id del grupo
                ultimo_id++;
                if(name_grp.compare(lista.value(2).trimmed(), Qt::CaseSensitive) == 0 &&
                   current_id > 0){
                    existe_nombre = true;
                    break;
                }
            }
        }
    }
    if(!existe_nombre){
        ultimo_id++;
        newData += QString::number(ultimo_id)+", G, "+name_grp;
        //cout<<"<INIT>"<<newData.toStdString()<<"<END>"<<endl<<endl;
        int resp = createFile("users.txt", f2_archivo::contentList(newData), false);
        if(resp == 0){ return 0;}
    }else{return 1;}
    return 2;
}

int f2_archivo::cambiarGrupo(QString usr_name, QString grp_name){
    //Retorna 0 si cambio el grupo al usuario
    //Retorna 1 si no existe el grupo
    //Retorna 2 si no existe el usuario
    //Retorna 3 si ocurrio un error
    QListIterator<QString> rows = getDatosUsers();
    QString newData;
    int current_id_grupo = 0;
    int current_id_usuario = 0;
    bool existe_grupo = false;
    bool existe_usuario = false;
    while (rows.hasNext()) {
        QString row = rows.next();
        if(row.size() > 0){
            //newData += row + "\n";
            QStringList lista = row.split(',');
            if(QString::compare(lista.value(1).trimmed(),"g", Qt::CaseInsensitive) == 0){
                current_id_grupo = lista.value(0).trimmed().toInt();//obtenemos el ultimo id del grupo
                if(grp_name.compare(lista.value(2).trimmed(), Qt::CaseSensitive) == 0 && current_id_grupo > 0){
                    existe_grupo = true;
                }
                newData += row + "\n";
            }else{
                current_id_usuario = lista.value(0).trimmed().toInt();//obtenemos el ultimo id del grupo
                if(usr_name.compare(lista.value(3).trimmed(), Qt::CaseSensitive) == 0 && current_id_usuario > 0){
                    newData += QString::number(current_id_usuario)+", U, "+grp_name+ ", "+usr_name+", "+lista.value(4).trimmed()+"\n";
                    existe_usuario = true;
                }else{newData += row + "\n";}
            }
        }
    }
    if(existe_grupo && existe_usuario){
        //cout<<"<INIT>"<<newData.toStdString()<<"<END>"<<endl<<endl;
        int resp = createFile("users.txt", f2_archivo::contentList(newData), false);
        if(resp == 0){ return 0;}
    }else{
        if(!existe_grupo){
            return 1;
        }
        else{return 2;}
    }
    return 3;
}

int f2_archivo::crearUsuario(QString usr, QString pwd, QString grp){
    //Retorna 0 si se creo el grupo
    //Retorna 1 si el usuario ya existe
    //Retorna 2 si el grupo no existe
    //Retoran 3 si hay error
    QListIterator<QString> rows = getDatosUsers();
    QString newData;
    int current_id_grp = 0;
    int ultimo_id_usr = 0;
    int current_id_usr = 0;
    bool existe_group = false;
    bool existe_usr = false;
    while (rows.hasNext()) {
        QString row = rows.next();
        if(row.size() > 0){
            newData += row + "\n";
            QStringList lista = row.split(',');
            if(QString::compare(lista.value(1).trimmed(),"g", Qt::CaseInsensitive) == 0){
                current_id_grp = lista.value(0).trimmed().toInt();//obtenemos el ultimo id del grupo
                if(grp.compare(lista.value(2).trimmed(), Qt::CaseSensitive) == 0 && current_id_grp > 0){
                    existe_group = true;
                }
            }
            else if (QString::compare(lista.value(1).trimmed(),"u", Qt::CaseInsensitive) == 0){
                current_id_usr = lista.value(0).trimmed().toInt();//obtenemos el ultimo id del grupo
                ultimo_id_usr++;
                if(usr.compare(lista.value(3).trimmed(), Qt::CaseSensitive) == 0 && current_id_usr > 0){
                    existe_usr = true;
                }
            }
        }
    }
    if(existe_group && !existe_usr){
        ultimo_id_usr++;
        newData += QString::number(ultimo_id_usr)+", U, "+grp+ ", "+usr+", "+pwd+"\n";
        //cout<<"<INIT>"<<newData.toStdString()<<"<END>"<<endl<<endl;
        int resp = createFile("users.txt", f2_archivo::contentList(newData), false);
        if(resp == 0){ return 0;}
    }else{
        if(existe_usr){ return 1; }
        else {return 2;}
    }
    return 3;
}

int f2_archivo::eliminarGrupo(QString name_grp){
    //Retorna 0 si se eliminó el grupo
    //Retorna 1 si el nombre no existe
    //Retorna 2 si ocurrio un error
    QListIterator<QString> rows = getDatosUsers();
    QString newData;
    int current_id = 0;
    bool eliminado = false;
    while (rows.hasNext()) {
        QString row = rows.next();
        if(row.size() > 0){
            //newData += row + "\n";
            QStringList lista = row.split(',');
            if(QString::compare(lista.value(1).trimmed(),"g", Qt::CaseInsensitive) == 0){
                current_id = lista.value(0).trimmed().toInt();//obtenemos el ultimo id del grupo
                if(name_grp.compare(lista.value(2).trimmed(), Qt::CaseSensitive) == 0 &&
                   current_id > 0){
                    newData += "0, G,"+name_grp+"\n";
                    eliminado = true;
                }
                else{newData += row + "\n";}
            }else{newData += row + "\n";}
        }
    }
    if(eliminado){
        //cout<<"<INIT>"<<newData.toStdString()<<"<END>"<<endl<<endl;
        int resp = createFile("users.txt", f2_archivo::contentList(newData), false);
        if(resp == 0){ return 0;}
    }else{return 1;}
    return 2;
}

int f2_archivo::eliminarUsuario(QString usr){
    //Retorna 0 si se eliminó el grupo
    //Retorna 1 si el nombre no existe
    //Retorna 2 si ocurrio un error
    QListIterator<QString> rows = getDatosUsers();
    QString newData;
    int current_id = 0;
    bool eliminado = false;
    while (rows.hasNext()) {
        QString row = rows.next();
        if(row.size() > 0){
            //newData += row + "\n";
            QStringList lista = row.split(',');
            if(QString::compare(lista.value(1).trimmed(),"u", Qt::CaseInsensitive) == 0){
                current_id = lista.value(0).trimmed().toInt();//obtenemos el ultimo id del usuario
                if(usr.compare(lista.value(3).trimmed(), Qt::CaseSensitive) == 0 &&
                   current_id > 0){
                    newData += "0, U, "+lista.value(2)+", "+usr+", "+lista.value(4) +"\n";
                    eliminado = true;
                }
                else{newData += row + "\n";}
            }else{newData += row + "\n";}
        }
    }
    if(eliminado){
        //cout<<"<INIT>"<<newData.toStdString()<<"<END>"<<endl<<endl;
        int resp = createFile("users.txt", f2_archivo::contentList(newData), false);
        if(resp == 0){ return 0;}
    }else{return 1;}
    return 2;
}

/*##################################################################################################################################
                                    METODOS MANIPULACION ARCHIVOS Y CARPETAS
##################################################################################################################################*/

int f2_archivo::chmod(QString path, int ugo, bool r){
    //Retorna 0 si se completo la instruccion
    //Retorna 1 si no se encontro el archivo
    //Retorna 2 si no se es propietario del archivo
    Inodo_dato encontrado =  getInodoByPath(path);
    //cout<<"inodo"<<endl;
    if(encontrado.inodo > 0){
        Inodo inodo = getInodo(disco, super.s_inode_start, encontrado.inodo);
        if(usr_id == 1){
            //El usuario es root
            inodo.i_perm = ugo;//Se cambia los permisos
            //Se actualiza el inodo
            escribirInodo(disco, inodo, super.s_inode_start, encontrado.inodo);
            return 0;
        }
        else{
            if(usr_id == inodo.i_uid){
                //El usuario es root
                inodo.i_perm = ugo;//Se cambia los permisos
                //Se actualiza el inodo
                escribirInodo(disco, inodo, super.s_inode_start, encontrado.inodo);
                return 0;
            }
            else{return 2;}
        }
    }
    else{return 1;}
}

bool encontrado=false;
QString tabular="";
int ctab=0;
QString imprimir="";
bool concatenar=false;

void f2_archivo::tm_buscar(QString ppath, QString pname){
    encontrado=false;
    tabular="";
    ctab=0;
    imprimir="";
    concatenar=false;

    if(ppath=="/"){
        cout<<"/"<<endl;
        Inodo inodo0= getInodo(disco, super.s_inode_start, 0);
        //Permiso p = verificarPermiso(inodo0);
        //if(p.lectura == 1){
            tm_recorre_inodos(ppath,pname,inodo0);
        //}else{cout<<"\033[31mERROR: No cuenta con el permiso lectura archivo/carpeta.\033[0m"<<endl<<endl;}
    }else{

        QStringList lista = getPath(ppath);//Obtenemos lista path
        if(lista.value(lista.length()).toStdString()==""){
            cout<<lista.value(lista.length()-1).toStdString()<<"/"<<endl;
        }else{
            cout<<lista.value(lista.length()).toStdString()<<"/"<<endl;
        }

        Inodo_dato prueba= getInodoByPath(ppath);
        Inodo inodo0= getInodo(disco, super.s_inode_start, prueba.inodo);

        //Permiso p = verificarPermiso(inodo0);
        //if(p.lectura == 1){
            tm_recorre_inodos(ppath,pname,inodo0);
        //}else{cout<<"\033[31mERROR: No cuenta con el permiso lectura archivo/carpeta.\033[0m"<<endl<<endl;}
    }

    if(encontrado){
        cout<<imprimir.toStdString()<<endl;
        cout<<"\033[96mBUSQUEDA REALIZADA CON EXITO.\033[0m"<<endl;
    }else{
        cout<<"\033[93mNO SE ENCONTRO EL ARCHIVO O CARPETA BUSCADA.\033[0m"<<endl;
    }
}

void f2_archivo::tm_recorre_inodos(QString ppath, QString pname, Inodo actual){

    int nivel=0;
    //bool encontrado=false;
    for (int ap = 0; ap < 16; ap++) {
        BApuntador i_block = getBloqueApuntador(disco, super.s_block_start, actual.i_block);
        //cout<<i_block.b_pointers[ap]<<endl;
        if(i_block.b_pointers[ap]>0){
            BCarpeta lista_carpeta = getBloqueCarpeta(disco,super.s_block_start,i_block.b_pointers[ap]);
            for(int i = 0; i < 4; i++){
                if(lista_carpeta.b_content[i].b_inodo>0){
                    tabular="";
                    for(int ct=0;ct<=ctab;ct++){
                        tabular+="\t";
                    }
                    Inodo temp = getInodo(disco,super.s_inode_start,lista_carpeta.b_content[i].b_inodo);
                    if(lista_carpeta.b_content[i].b_name==pname.toStdString()){
                        ctab++;
                        encontrado=true;
                        //cout<<tabular.toStdString()<<lista_carpeta.b_content[i].b_name<<endl;
                        imprimir+=QString::fromStdString(tabular.toStdString()+"\033[96m"+lista_carpeta.b_content[i].b_name+"\033[0m\n");
                        ctab--;
                        break;
                    }
                    else if(temp.i_type=='0' && !encontrado){
                        ctab++;
                        //cout<<tabular.toStdString()<<lista_carpeta.b_content[i].b_name<<"/"<<endl;
                        imprimir+=QString::fromStdString(tabular.toStdString()+lista_carpeta.b_content[i].b_name+"/\n");
                        tm_recorre_inodos(ppath,pname,temp);
                        ctab--;
                    }
                }
                if(encontrado==true){
                    break;
                }


            }
            if(encontrado==true){
                break;
            }
        }
    }

}
Inodo_dato f2_archivo::tm_buscar_inodo(QString name_file_direc, int espacio_apuntador,int nivel){

    Inodo_dato retornar = {-1, -1, -1};

    return retornar;
}

void f2_archivo::verArchivo(QString path){
    Inodo_dato find = getInodoByPath(path);
    if(find.inodo >= 0){
        Inodo inodo = getInodo(disco, super.s_inode_start, find.inodo);
        if(inodo.i_type == '1'){
            Permiso p = verificarPermiso(inodo);
            if(p.lectura == 1){
                cout<<"\033[96mContenido:"<<endl<<getFileContent(inodo).toStdString()<<"\033[0m"<<endl<<endl;
            }else{cout<<"\033[31mERROR: El usuario actual no posee permiso de lectura del archivo.\033[0m"<<endl<<endl;}
        }else{cout<<"\033[31mERROR: No se indicó el nombre del archivo.\033[0m"<<endl<<endl;}
    }else{cout<<"\033[31mERROR: No existe el archivo en la ruta especificada.\033[0m"<<endl<<endl;}
}

void f2_archivo::editArchivo(QString path, QString content){
    Inodo_dato find = getInodoByPath(path);
    if(find.inodo > 0){
        Inodo inodo = getInodo(disco, super.s_inode_start, find.inodo);
        if(inodo.i_type == '1'){
            Permiso p = verificarPermiso(inodo);
            if(p.escritura == 1 && p.lectura){
                //Obtenemos el contenido
                QString dato_actual= getFileContent(inodo);
                //Eliminamos todos los bloques e inodos hijos
                removeInodoChilds(inodo);
                QStringList listContent;
                dato_actual += content;
                for (int i = 0; i < dato_actual.size(); i+=64) {
                    listContent.append(dato_actual.mid(i, 64));
                }
                QListIterator<QString> iterator(listContent);
                inodo.i_size = listContent.size()*64;
                inodo.i_mtime = time(NULL);
                BApuntador bloque;
                //= getBloqueApuntador(disco, super.s_block_start, inodo.i_block);
                for(int i = 0 ; i< 16; i++){
                    bloque.b_pointers[i] = -1;
                }
                int result = crearBloquesArchivo(iterator, bloque);
                if(result == 0){
                    agregarJournal("edit", path, content, '1');
                    //Actualizar inodo
                    escribirInodo(disco, inodo, super.s_inode_start, find.inodo);
                    //Actualizar bloque apuntador del inodo
                    escribirBloque(disco, bloque ,super.s_block_start, inodo.i_block);
                    //Actualizamos el super bloque
                    actualizarSuperBloque();
                    cout<<"\033[96mSe editó el archivo correctamente.\033[0m"<<endl<<endl;
                }else{cout<<"\033[31mERROR: No se pudo editar el archivo.\033[0m"<<endl<<endl;}
            }else{cout<<"\033[31mERROR: El usuario actual no cuenta con los permisos para editar el archivo.\033[0m"<<endl<<endl;}
        }else{cout<<"\033[31mERROR: La ruta especificada no es un archivo.\033[0m"<<endl<<endl;}
    }else{ cout<<"\033[31mERROR: No se encontró el archivo indicado.\033[0m"<<endl<<endl;}
}

void f2_archivo::reEditArchivo(QString path, QString content){
    Inodo_dato find = getInodoByPath(path);
    if(find.inodo > 0){
        Inodo inodo = getInodo(disco, super.s_inode_start, find.inodo);
        if(inodo.i_type == '1'){
            Permiso p = verificarPermiso(inodo);
            if(p.escritura == 1 && p.lectura){
                //Obtenemos el contenido
                QString dato_actual= getFileContent(inodo);
                //Eliminamos todos los bloques e inodos hijos
                removeInodoChilds(inodo);
                QStringList listContent;
                dato_actual += content;
                for (int i = 0; i < dato_actual.size(); i+=64) {
                    listContent.append(dato_actual.mid(i, 64));
                }
                QListIterator<QString> iterator(listContent);
                inodo.i_size = listContent.size()*64;
                inodo.i_mtime = time(NULL);
                BApuntador bloque;
                //= getBloqueApuntador(disco, super.s_block_start, inodo.i_block);
                for(int i = 0 ; i< 16; i++){
                    bloque.b_pointers[i] = -1;
                }
                int result = crearBloquesArchivo(iterator, bloque);
                if(result == 0){
                    //agregarJournal("edit", path, content, '1');
                    //Actualizar inodo
                    escribirInodo(disco, inodo, super.s_inode_start, find.inodo);
                    //Actualizar bloque apuntador del inodo
                    escribirBloque(disco, bloque ,super.s_block_start, inodo.i_block);
                    //Actualizamos el super bloque
                    //actualizarSuperBloque();
                    cout<<"\033[96mSe editó el archivo correctamente.\033[0m"<<endl<<endl;
                }else{cout<<"\033[31mERROR: No se pudo editar el archivo.\033[0m"<<endl<<endl;}
            }else{cout<<"\033[31mERROR: El usuario actual no cuenta con los permisos para editar el archivo.\033[0m"<<endl<<endl;}
        }else{cout<<"\033[31mERROR: La ruta especificada no es un archivo.\033[0m"<<endl<<endl;}
    }else{ cout<<"\033[31mERROR: No se encontró el archivo indicado.\033[0m"<<endl<<endl;}
}

void f2_archivo::rename(QString path, QString newName){
    QStringList lista = getPath(path);//Obtenemos lista path
    lista.removeLast();//eliminamos el ultimo elemento(nombre actual del archivo)

    lista.append(newName);//Agregamos el nuevo nombre(se reemplaza el antiguo por el nuevo)
    QListIterator<QString> iter(lista);//Obtenemos iterador del nuevo path


    Inodo root = getInodo(disco, super.s_inode_start, 0);//Obtenemos inodo root
    Inodo_dato existe = getInodoByPath_(root, iter);//buscamos si existe el nuevo nombre

    if(existe.inodo < 0){
        Inodo_dato find = getInodoByPath(path);
        if(find.inodo > 0){
            Inodo inodo = getInodo(disco, super.s_inode_start, find.inodo);
            Permiso p = verificarPermiso(inodo);
            if(p.escritura == 1 || usr_id == 1){
                BCarpeta padre = getBloqueCarpeta(disco, super.s_block_start, find.bloque_padre);
                //Modificamos el nombre
                strcpy(padre.b_content[find.posicion].b_name, newName.mid(0,12).toStdString().c_str());
                escribirBloque(disco, padre, super.s_block_start, find.bloque_padre);
                agregarJournal("ren", path, newName, inodo.i_type);
                actualizarSuperBloque();
                cout<<"\033[96mSe ha cambiado el nombre correctamente.\033[0m"<<endl<<endl;
            }else{cout<<"\033[31mERROR: No cuenta con el permiso para modificar el archivo/carpeta.\033[0m"<<endl<<endl;}
        }else{cout<<"\033[31mERROR: El archivo no existe.\033[0m"<<endl<<endl;}
    }else{cout<<"\033[31mERROR: El nuevo nombre ya existe.\033[0m"<<endl<<endl;}
}

void f2_archivo::reRename(QString path, QString newName){
    QStringList lista = getPath(path);//Obtenemos lista path
    lista.removeLast();//eliminamos el ultimo elemento(nombre actual del archivo)
    lista.append(newName);//Agregamos el nuevo nombre(se reemplaza el antiguo por el nuevo)
    QListIterator<QString> iter(lista);//Obtenemos iterador del nuevo path
    Inodo root = getInodo(disco, super.s_inode_start, 0);//Obtenemos inodo root
    Inodo_dato existe = getInodoByPath_(root, iter);//buscamos si existe el nuevo nombre

    if(existe.inodo < 0){
        Inodo_dato find = getInodoByPath(path);
        if(find.inodo > 0){
            Inodo inodo = getInodo(disco, super.s_inode_start, find.inodo);
            Permiso p = verificarPermiso(inodo);
            if(p.escritura == 1 || usr_id == 1){
                BCarpeta padre = getBloqueCarpeta(disco, super.s_block_start, find.bloque_padre);
                //Modificamos el nombre
                strcpy(padre.b_content[find.posicion].b_name, newName.mid(0,12).toStdString().c_str());
                escribirBloque(disco, padre, super.s_block_start, find.bloque_padre);
                //agregarJournal("ren", path, newName, inodo.i_type);
                //actualizarSuperBloque();
                cout<<"\033[96mSe ha cambiado el nombre correctamente.\033[0m"<<endl<<endl;
            }else{cout<<"\033[31mERROR: No cuenta con el permiso para modificar el archivo/carpeta.\033[0m"<<endl<<endl;}
        }else{cout<<"\033[31mERROR: El archivo no existe.\033[0m"<<endl<<endl;}
    }else{cout<<"\033[31mERROR: El nuevo nombre ya existe.\033[0m"<<endl<<endl;}
}


/*##################################################################################################################################
                                    METODOS PARA SIMULAR PERDIDA Y RECUPERACION
##################################################################################################################################*/

void f2_archivo::loss(){
    Inodo empty;
    BApuntador empty_block;
    int sizeInodo = bitmap_inodo.size();
    if(sizeInodo > 1000){ sizeInodo = 1000;}
    int sizeBlock = bitmap_block.size();
    if(sizeBlock > 1000){ sizeBlock = 1000;}
    for (int i = 0; i < sizeInodo; i++) {
        bitmap_inodo[i] = '\0';
        escribirInodo(disco, empty, super.s_inode_start, i);
    }
    for (int i = 0; i < sizeBlock; i++) {
        bitmap_block[i] = '\0';
        escribirBloque(disco, empty_block, super.s_block_start, i);
    }
    super.s_first_blo = 0;
    super.s_firts_ino = 0;
    super.s_free_blocks_count = super.s_blocks_count;
    super.s_free_inodes_count = super.s_inodes_count;
    //Escribir bitmap_inodos
    fseek(disco, super.s_bm_inode_start, SEEK_SET);//Posicionamos el puntero al inicio de espacio bitmap inodos
    fwrite(bitmap_inodo.data(), 1, super.s_inodes_count, disco);//Escribimos el Bitmap inodos
    //Escribir bitmap_bloques
    fseek(disco, super.s_bm_block_start, SEEK_SET);//Posicionamos el puntero al inicio de espacio bitmap blocks
    fwrite(bitmap_block.data(), 1, super.s_blocks_count, disco);//Escribimos el Bitmap blocks

    fseek(disco, inicio_byte, SEEK_SET);//Posicionamos el puntero al inicio de la particion
    fwrite(&super, sizeof(SuperBlock), 1, disco);//Escribimos el Superbloque
    cout<<"\033[96mSe ha borrado la informacion.\033[0m"<<endl<<endl;
}

void f2_archivo::recover(){
    if(super.s_filesystem_type == 3){
        if(journal_info.last >= 1){

            Journal journal = getJournal(1);
            if(QString::compare(journal.nombre, "/", Qt::CaseInsensitive) == 0){
                cout<< "--> mkdir -path=/"<<endl;
                cout<<"Se creó la carpeta raiz"<<endl<<endl;
                crearCarpetaRaiz(disco, super, inicio_byte);
                getBitmaps();
            }
            while (journal.next > 1) {
                journal = getJournal(journal.next);
                if(QString::compare(journal.operacion, "mkdir",Qt::CaseInsensitive) == 0){
                    cout<< "--> mkdir -path="<<journal.nombre<<endl;
                    Inodo actual = getInodo(disco, super.s_inode_start, 0);//raiz está en la posicion 0
                    QStringList list_path = getPath(journal.nombre);
                    int resultado = crearCarpeta_(actual, list_path, 0, false);
                    switch (resultado) {
                        case 0:cout<<"\033[96mLa carpeta se ha creado correctamente.\033[0m"<<endl<<endl; break;
                        case 1:cout<<"\033[31mERROR: No se pudo crear la carpeta.\033[0m"<<endl<<endl;break;
                        case 2:cout<<"\033[31mERROR: La ruta ingresada no existe.\033[0m"<<endl<<endl;break;
                        case 3:cout<<"\033[31mERROR: El nombre ya existe.\033[0m"<<endl<<endl;break;
                        default: cout<<"\033[31mERROR: No se pudo crear la carpeta.\033[0m"<<endl<<endl;;break;
                    }
                }
                else if(QString::compare(journal.operacion, "mkfile",Qt::CaseInsensitive) == 0){
                    cout<< "--> mkfile -path="<<journal.nombre<<endl;
                    QStringList listContent;
                    QString dato_actual = journal.content;
                    for (int i = 0; i < 230; i+=64) {
                        QString Txt = dato_actual.mid(i, 64);
                        if(Txt.size()> 0){
                            listContent.append(Txt);
                        }
                    }
                    Inodo actual = getInodo(disco, super.s_inode_start, 0);//raiz está en la posicion 0
                    QStringList list_path = getPath(journal.nombre);
                    int resultado = crearArchivo_(actual,listContent, list_path, 0, false);
                    switch (resultado) {
                        case 0:cout<<"\033[96mEl archivo se ha creado correctamente.\033[0m"<<endl<<endl; break;
                        case 1:cout<<"\033[31mERROR: No se pudo crear el archivo.\033[0m"<<endl<<endl;break;
                        case 2:cout<<"\033[31mERROR: La ruta ingresada no existe.\033[0m"<<endl<<endl;break;
                        case 3:cout<<"\033[31mERROR: El nombre ya existe.\033[0m"<<endl<<endl;break;
                        default: cout<<"\033[31mERROR: No se pudo crear el archivo.\033[0m"<<endl<<endl;;break;
                    }
                }
                if(QString::compare(journal.operacion, "ren",Qt::CaseInsensitive) == 0){
                    cout<< "--> ren -path="<<journal.nombre<<" -name="<<journal.content<<endl;
                    reRename(journal.nombre, journal.content);
                }
                if(QString::compare(journal.operacion, "edit",Qt::CaseInsensitive) == 0){
                    cout<< "--> edit -path="<<journal.nombre<<" -content="<<journal.content<<endl;
                    reEditArchivo(journal.nombre, journal.content);
                }
                if(QString::compare(journal.operacion, "rem",Qt::CaseInsensitive) == 0){
                    cout<< "--> rem -path="<<journal.nombre<<endl;
                    reRem(journal.nombre);
                }
            }
            actualizarBitmaps();
            actualizarSB();
            cout<<"\033[96mSe completo la recuperacion de archivos.\033[0m"<<endl<<endl;
        }else{cout<<"\033[31mERROR: No hay registros.\033[0m"<<endl<<endl;}
    }else{cout<<"\033[31mERROR: Recovery solo se ejecuta sobre una particion con formato EXT3.\033[0m"<<endl<<endl;}
}

/*##################################################################################################################################
                                    METODOS PARA CREAR REPORTES
##################################################################################################################################*/

// REPORTE INODOS ----------------------------------------------------------------------------------------
void f2_archivo::reporteInodo(QString save_path){
    stringstream data;
    stringstream links;
    data << "digraph G {\n";
    data << "graph [pad=\"0.5\", nodesep=\"0.5\", ranksep=\"2\"];\n";
    data << "node [shape=plain]\n";
    data << "rankdir=LR;\n\n";
    int cont = 0;
    int tam = bitmap_inodo.size()-1;
    int anterior = 0;
    if(tam >1000){tam = 1000;}
    for(int i = 0; i < tam ; i++){
        if(bitmap_inodo[i] == '1'){
            //Inodo existe
            Inodo inodo = getInodo(disco, super.s_inode_start, i);
            if(inodo.i_type == '0' || inodo.i_type == '1'){
                cont++;
                data<<"Inodo"<<i<<" [label=<\n";
                data<< "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">\n";
                data<< "<tr><td colspan=\"2\">Inodo "<<i<<" </td></tr>\n";
                //Generamos el string para excribir -------------------------------------------------------------------------
                char i_atime[20];
                char i_ctime[20];
                char i_mtime[20];
                strftime(i_atime, 20, "%d/%m/%Y", localtime(&inodo.i_atime));
                strftime(i_ctime, 20, "%d/%m/%Y", localtime(&inodo.i_ctime));
                strftime(i_mtime, 20, "%d/%m/%Y", localtime(&inodo.i_mtime));
                //i_atime = ctime(&inodoActual.i_atime);
                //i_ctime = ctime(&inodoActual.i_ctime);
                //i_mtime = ctime(&inodoActual.i_mtime);
                data<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">i_uid</font></td><td>"<<inodo.i_uid<<"</td></tr>\n";
                data<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">i_gid</font></td><td>"<<inodo.i_gid<<"</td></tr>\n";
                data<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">i_size</font></td><td>"<<inodo.i_size<<"</td></tr>\n";
                data<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">i_atime</font></td><td>"<<i_atime<<"</td></tr>\n";
                data<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">i_ctime</font></td><td>"<<i_ctime<<"</td></tr>\n";
                data<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">i_mtime</font></td><td>"<<i_mtime<<"</td></tr>\n";
                data<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">i_type</font></td><td>"<<inodo.i_type<<"</td></tr>\n";
                data<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">i_perm</font></td><td>"<<inodo.i_perm<<"</td></tr>\n";
                data<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">i_block</font></td><td>"<<inodo.i_block<<"</td></tr>\n";
                data <<"</table>>];\n\n";
                if(cont > 1 && cont <= 10){
                    //Enlazar
                    links<< "Inodo"<<anterior<<" -> "<<"Inodo"<<i<<endl;
                }
                if(cont == 10){cont = 0;}
                anterior = i;

            }
        }
    }

    QStringList nuevoPath = f2_disco::evaluarDirectorio(save_path, f2_disco::REP);
    if(nuevoPath.size() == 3){
        QString new_path = nuevoPath[0]+"/"+nuevoPath[1];
        try {
            ofstream file;
            file.open((new_path+".dot").toStdString().c_str());
            file<<data.str();
            file<<links.str();
            file<<"}";
            file.close();
            QString r = "dot -T"+nuevoPath[2]+" \""+new_path+".dot\"  -o  \""+new_path+"."+nuevoPath[2]+"\"";
            if(system(r.toStdString().c_str()) == 0){
                cout<<"\033[96mReporte creado correctamente.\033[0m"<<endl<<endl;
            }
        }catch(exception& e) {
            cout << e.what() << endl;
        }
    }
    else{
        cout<<"\033[31mERROR: No se indicó el nombre con la extención para el reporte en el -path.\033[0m"<<endl<<endl;
    }
}

// REPORTE JOURNAL ---------------------------------------------------------------------------------------
void f2_archivo::reporteJournal(QString save_path){
    if(super.s_filesystem_type == 3){
        if(journal_info.last >= 1){
            QStringList nuevoPath = f2_disco::evaluarDirectorio(save_path, f2_disco::REP);
            if(nuevoPath.size() == 3){
                QString new_path = nuevoPath[0]+"/"+nuevoPath[1];
                try {
                    ofstream file;
                    file.open((new_path+".dot").toStdString().c_str());
                    file << "digraph G {\n";
                    file << "graph [pad=\"0.5\", nodesep=\"0.5\", ranksep=\"2\"];\n";
                    file << "node [shape=plain]\n";
                    file << "rankdir=LR;\n\n";
                    Journal journal = getJournal(1);
                    QString tipo;
                    if(journal.tipo == '0'){tipo = "Carpeta";}
                    else{tipo = "Archivo";}

                    //EDITADO
                    //char fecha[16];
                    //strcmp(fecha, journal.date);


                    char fecha[20];
                    strftime(fecha, 20, "%d/%m/%Y", localtime(&journal.date));
                    file<<"Journals [label=<\n";
                    file<< "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">\n";

                    //file<< "<tr><td> COMANDO </td><td> TIPO </td><td> NOMBRE </td><td> CONTENIDO </td><td> FECHA </td></tr>\n";
                    file<< "<tr><td> COMANDO </td><td> TIPO </td><td> USUARIO </td><td> NOMBRE </td><td> CONTENIDO </td><td> FECHA </td></tr>\n";

                    file<< "<tr><td>"<<journal.operacion;
                    file<< "</td><td>"<<tipo.toStdString();

                    file<< "</td><td>"<<"root";


                    file<< "</td><td>"<<journal.nombre;
                    QString cont = journal.content;
                    file<< "</td><td>"<<cont.mid(0,230).toStdString();
                    file<< " </td><td> "<<fecha;
                    file<< "</td></tr>\n";
                    while (journal.next > 1) {
                        journal = getJournal(journal.next);
                        if(journal.tipo == '0'){tipo = "Carpeta";}
                        else{tipo = "Archivo";}
                        //EDITADO
                        //char date[16];
                        //strcmp(fecha, journal.date);
                        //cout<<journal.date<<endl;
                        char date[20];
                        strftime(date, 20, "%d/%m/%Y", localtime(&journal.date));
                        file<< "<tr><td>"<<journal.operacion;
                        file<< "</td><td>"<<tipo.toStdString();
                        file<< "</td><td>"<<journal.usuario;
                        file<< "</td><td>"<<journal.nombre;
                        QString conten = journal.content;
                        file<< "</td><td>"<<conten.mid(0,230).toStdString();
                        file<< " </td><td> "<<date;
                        file<< "</td></tr>\n";
                    }
                    file <<"</table>>];\n\n";
                    file<<"}";
                    file.close();
                    QString r = "dot -T"+nuevoPath[2]+" \""+new_path+".dot\"  -o  \""+new_path+"."+nuevoPath[2]+"\"";
                    if(system(r.toStdString().c_str()) == 0){
                        cout<<"\033[96mReporte creado correctamente.\033[0m"<<endl<<endl;
                    }
                }catch(exception& e) {
                    cout << e.what() << endl;
                }
            }
            else{
                cout<<"\033[31mERROR: No se indicó el nombre con la extención para el reporte en el -path.\033[0m"<<endl<<endl;
            }
        }else{cout<<"\033[31mERROR: No hay registros.\033[0m"<<endl<<endl;}
    }else{cout<<"\033[31mERROR: Este reporte se genera sobre una particion formato EXT3.\033[0m"<<endl<<endl;}
}


// REPORTE BLOQUES ---------------------------------------------------------------------------------------
void f2_archivo::tablaBloqueApuntador(BApuntador apuntador, int no_block, stringstream &data){
    data<<"Bloque"<<no_block<<" [label=<\n";
    data<< "<table border=\"0\" bgcolor=\"#50fff7\"   cellborder=\"1\" cellspacing=\"3\">\n";
    data<< "<tr><td>Bloque "<<no_block<<" </td></tr>\n";
    for (int i = 0; i < 16; i++) {
        if(apuntador.b_pointers[i] >= 0){
            data<< "<tr><td>"<<apuntador.b_pointers[i]<<" </td></tr>\n";
        }
        else{
            data<< "<tr><td> -1 </td></tr>\n";
        }
    }
    data <<"</table>>];\n\n";
}

void f2_archivo::tablaBloqueCarpeta(BCarpeta carpeta, int no_block, stringstream &data){
    data<<"Bloque"<<no_block<<" [label=<\n";
    data<< "<table border=\"0\" bgcolor=\"#fff555\"   cellborder=\"1\" cellspacing=\"3\">\n";
    data<< "<tr><td colspan=\"2\">Bloque "<<no_block<<" </td></tr>\n";
    data<< "<tr><td>Nombre</td><td>Inodo</td></tr>\n";

    for(int i = 0; i < 4; i++){
        QString nom = carpeta.b_content[i].b_name;
        if(carpeta.b_content[i].b_inodo > 0){
            //Se crea bloque carpeta
            data<< "<tr><td>"<<nom.mid(0,12).toStdString()<<"</td><td>"<<carpeta.b_content[i].b_inodo<<"</td></tr>\n";
        }else{data<< "<tr><td> --- </td><td>-1</td></tr>\n";}
    }
    data <<"</table>>];\n\n";
}

void f2_archivo::tablaBloqueArchivo(BArchivo archivo, int no_block, stringstream &data){
    QString content = archivo.b_content;
    content += "\0";
    data<<"Bloque"<<no_block<<" [label=<\n";
    data<< "<table border=\"0\" bgcolor=\"#4bd517\"   cellborder=\"1\" cellspacing=\"3\">\n";
    data<< "<tr><td>Bloque "<<no_block<<" </td></tr>\n";
    data<< "<tr><td>Contenido</td></tr>\n";
    data<< "<tr><td>"<<content.mid(0,64).toStdString()<<"</td></tr>\n";
    //cout<<ar_contenido.b_content<<endl;
    data <<"</table>>];\n\n";
}

void f2_archivo::txtCarpeta(int espacio, stringstream &data, QList<int> &block_list, int nivel){
    if(espacio >= 0){
        if(nivel == 0){
            BCarpeta carpeta = getBloqueCarpeta(disco, super.s_block_start, espacio);
            tablaBloqueCarpeta(carpeta, espacio, data);
            block_list.append(espacio);
        }else{
            BApuntador apuntador = getBloqueApuntador(disco, super.s_block_start, espacio);
            tablaBloqueApuntador(apuntador, espacio, data);
            block_list.append(espacio);
            for (int i = 0; i < 16; i++) {
                txtCarpeta(apuntador.b_pointers[i], data, block_list, nivel-1);
            }
        }
    }
}

void f2_archivo::txtFile(int espacio, stringstream &data, QList<int> &block_list, int nivel){
    if(espacio >= 0){
        if(nivel == 0){
            BArchivo archivo = getBloqueArchivo(disco, super.s_block_start, espacio);
            tablaBloqueArchivo(archivo, espacio, data);
            block_list.append(espacio);
        }else{
            BApuntador apuntador = getBloqueApuntador(disco, super.s_block_start, espacio);
            tablaBloqueApuntador(apuntador, espacio, data);
            block_list.append(espacio);
            for (int i = 0; i < 16; i++) {
                txtFile(apuntador.b_pointers[i], data, block_list,nivel-1);
            }
        }
    }
}

void f2_archivo::reporteBloque(QString save_path){
    stringstream data;
    stringstream links;
    data << "digraph G {\n";
    data << "graph [pad=\"0.5\", nodesep=\"0.5\", ranksep=\"2\"];\n";
    data << "node [shape=plain]\n";
    data << "rankdir=LR;\n\n";
    int tam = bitmap_inodo.size()-1;
    if(tam >3000){tam = 3000;}
    QList<int> block_list;
    for(int i = 0; i < tam ; i++){
        if(bitmap_inodo[i] == '1'){
            //Inodo existe
            Inodo inodo = getInodo(disco, super.s_inode_start, i);
            if(inodo.i_type == '0' || inodo.i_type == '1'){
                BApuntador i_block = getBloqueApuntador(disco, super.s_block_start, inodo.i_block);
                tablaBloqueApuntador(i_block, inodo.i_block, data);
                block_list.append(inodo.i_block);
                if(inodo.i_type == '0'){
                    //Carpeta
                    for (int a = 0 ; a < 16; a++) {
                        int space = i_block.b_pointers[a];
                        if(a <=12 && space >= 0){
                            txtCarpeta(space, data,block_list, 0);
                        }
                        else if (a == 13 && space >= 0){
                            txtCarpeta(space, data,block_list, 1);
                        }
                        else if (a == 14 && space >= 0){
                            txtCarpeta(space, data,block_list, 2);
                        }
                        else if (a == 15 && space >= 0){
                            txtCarpeta(space, data,block_list, 3);
                        }
                    }
                }
                else{
                    //i_type = 1 ;  archivo
                    for (int a = 0 ; a < 16; a++) {
                        int space = i_block.b_pointers[a];
                        if(a <=12 && space >= 0){
                            txtFile(space, data,block_list, 0);
                        }
                        else if (a == 13 && space >= 0){
                            txtFile(space, data,block_list, 1);
                        }
                        else if (a == 14 && space >= 0){
                            txtFile(space, data,block_list, 2);
                        }
                        else if (a == 15 && space >= 0){
                            txtFile(space, data,block_list, 3);
                        }
                    }
                }
            }
        }
    }

    int cont = 0;
    int b_anterior = 0;
    foreach (int no_block, block_list) {
        cont++;
        if(cont > 1 && cont <= 10){
            //Enlazar
            links<< "Bloque"<<b_anterior<<" -> "<<"Bloque"<<no_block<<endl;
        }
        if(cont == 10){cont = 0;}
        b_anterior = no_block;

    }

    QStringList nuevoPath = f2_disco::evaluarDirectorio(save_path, f2_disco::REP);
    if(nuevoPath.size() == 3){
        QString new_path = nuevoPath[0]+"/"+nuevoPath[1];
        try {
            ofstream file;
            file.open((new_path+".dot").toStdString().c_str());
            file<<data.str();
            file<<links.str();
            file<<"}";
            file.close();
            //QString r = "dot -T"+nuevoPath[2]+" \""+new_path+".dot\"  -o  \""+new_path+"."+nuevoPath[2]+"\"";
            QString r = "dot -Tpdf \""+new_path+".dot\"  -o  \""+new_path+".pdf\"";
//                    QString r = "dot -T"+nuevoPath[2]+" \""+new_path+".dot\"  -o  \""+new_path+"."+nuevoPath[2]+"\"";

         //   QString r = "dot -T"+nuevoPath[2]+" \""+new_path+".dot\"  -o  \""+new_path+"."+nuevoPath[2]+"\"";
            if(system(r.toStdString().c_str()) == 0){
                cout<<"\033[96mReporte creado correctamente.\033[0m"<<endl<<endl;
            }
        }catch(exception& e) {
            cout << e.what() << endl;
        }
    }
    else{
        cout<<"\033[31mERROR: No se indicó el nombre con la extención para el reporte en el -path.\033[0m"<<endl<<endl;
    }
}

// REPORTE BITMAPS
void f2_archivo::reporteBtmInodo(QString save_path){
    stringstream data;
    int tam = bitmap_inodo.size()-1;
    int cont =0;
    for(int i = 0; i < tam ; i++){
        cont ++;
        if(bitmap_inodo[i] == '1'){
            //Inodo existe
            Inodo inodo = getInodo(disco, super.s_inode_start, i);
            if(inodo.i_type == '0' || inodo.i_type == '1'){
                data<<"1    ";
            }else{
                data<<"0    ";
            }
        }else{
            data<<"0    ";
        }
        if(cont == 20){cont = 0; data<<"\n";}
    }
    QStringList nuevoPath = f2_disco::evaluarDirectorio(save_path, f2_disco::REP);
    if(nuevoPath.size() == 3){
        QString new_path = nuevoPath[0]+"/"+nuevoPath[1];
        try {
            ofstream file;
            file.open((new_path+".txt").toStdString().c_str());
            file<<data.str();
            file.close();
            cout<<"\033[96mReporte creado correctamente.\033[0m"<<endl<<endl;
        }catch(exception& e) {
            cout << e.what() << endl;
        }
    }
    else{
        cout<<"\033[31mERROR: No se indicó el nombre con la extención para el reporte en el -path.\033[0m"<<endl<<endl;
    }
}

void f2_archivo::reporteBtmBlock(QString save_path){
    stringstream data;
    int tam = bitmap_block.size()-1;
    int cont =0;
    for(int i = 0; i < tam ; i++){
        cont ++;
        if(bitmap_block[i] == '1'){
            data<<"1    ";
        }else{
            data<<"0    ";
        }
        if(cont == 20){cont = 0; data<<"\n";}
    }
    QStringList nuevoPath = f2_disco::evaluarDirectorio(save_path, f2_disco::REP);
    if(nuevoPath.size() == 3){
        QString new_path = nuevoPath[0]+"/"+nuevoPath[1];
        try {
            ofstream file;
            file.open((new_path+".txt").toStdString().c_str());
            file<<data.str();
            file.close();
            cout<<"\033[96mReporte creado correctamente.\033[0m"<<endl<<endl;
        }catch(exception& e) {
            cout << e.what() << endl;
        }
    }
    else{
        cout<<"\033[31mERROR: No se indicó el nombre con la extención para el reporte en el -path.\033[0m"<<endl<<endl;
    }
}

// REPORTE ARBOLES ----------------------------------------------------------------------------------------
void f2_archivo::generarTxtBloques_(FILE *disco, stringstream &data, stringstream &links, int no_bloque, SuperBlock super, int nivel){
    if(nivel >= 0 && nivel <= 3){
        if(nivel == 0){
            BCarpeta lista_carpeta = getBloqueCarpeta(disco, super.s_block_start, no_bloque);
            data<<"Bloque"<<no_bloque<<" [label=<\n";
            data<< "<table border=\"0\" bgcolor=\"#fff555\"   cellborder=\"1\" cellspacing=\"3\">\n";
            data<< "<tr><td colspan=\"2\">Bloque "<<no_bloque<<" </td></tr>\n";
            data<< "<tr><td>Nombre</td><td>Inodo</td></tr>\n";

            for(int i = 0; i < 4; i++){
                QString nom = lista_carpeta.b_content[i].b_name;
                if(lista_carpeta.b_content[i].b_inodo > 0){
                    //Se crea bloque carpeta
                    links << "Bloque"<<no_bloque<<":"<<i<<" -> Inodo"<<lista_carpeta.b_content[i].b_inodo<<"\n";
                    data<< "<tr><td>"<<nom.mid(0,12).toStdString()<<"</td><td port='"<<i<<"'>"<<lista_carpeta.b_content[i].b_inodo<<"</td></tr>\n";
                }else{data<< "<tr><td> --- </td><td>-1</td></tr>\n";}
            }
            data <<"</table>>];\n\n";

            for (int i = 0;i < 4; i++) {
                if(lista_carpeta.b_content[i].b_inodo > 0){
                    Inodo inodo = getInodo(disco, super.s_inode_start, lista_carpeta.b_content[i].b_inodo);
                    generarTxtInodos_(disco, data, links, inodo, lista_carpeta.b_content[i].b_inodo, super);
                }
            }
        }else{
            BApuntador lista_bloques = getBloqueApuntador(disco, super.s_block_start, no_bloque);
            data<<"Bloque"<<no_bloque<<" [label=<\n";
            data<< "<table border=\"0\" bgcolor=\"#50fff7\"   cellborder=\"1\" cellspacing=\"3\">\n";
            data<< "<tr><td>Bloque "<<no_bloque<<" </td></tr>\n";

            for (int i = 0; i < 16; i++) {
                if(lista_bloques.b_pointers[i]> 0){
                    links << "Bloque"<<no_bloque<<":"<<i<<" -> Bloque"<<lista_bloques.b_pointers[i]<<"\n";
                    data<< "<tr><td port='"<<i<<"'>"<<lista_bloques.b_pointers[i]<<" </td></tr>\n";
                }
                else{
                    data<< "<tr><td> -1 </td></tr>\n";
                }
            }
            data <<"</table>>];\n\n";
            for (int i = 0; i < 16; i++) {
                if(lista_bloques.b_pointers[i]> 0){
                    generarTxtBloques_(disco, data, links,lista_bloques.b_pointers[i], super, nivel - 1);
                }
            }
        }
    }
}

void f2_archivo::generarTxtBloquesArchivos_(FILE *disco, stringstream &data, stringstream &links, int no_bloque, SuperBlock super, int nivel){
    if(nivel >= 0 && nivel <= 3){
        if(nivel == 0){
            BArchivo ar_contenido = getBloqueArchivo(disco, super.s_block_start, no_bloque);
            QString content = ar_contenido.b_content;
            content += "\0";
            data<<"Bloque"<<no_bloque<<" [label=<\n";
            data<< "<table border=\"0\" bgcolor=\"#4bd517\"   cellborder=\"1\" cellspacing=\"3\">\n";
            data<< "<tr><td>Bloque "<<no_bloque<<" </td></tr>\n";
            data<< "<tr><td>Contenido</td></tr>\n";
            data<< "<tr><td>"<<content.mid(0,64).toStdString()<<"</td></tr>\n";
            //cout<<ar_contenido.b_content<<endl;
            data <<"</table>>];\n\n";
        }else{
            BApuntador lista_bloques = getBloqueApuntador(disco, super.s_block_start, no_bloque);
            data<<"Bloque"<<no_bloque<<" [label=<\n";
            data<< "<table border=\"0\" bgcolor=\"#50fff7\"   cellborder=\"1\" cellspacing=\"3\">\n";
            data<< "<tr><td>Bloque "<<no_bloque<<" </td></tr>\n";

            for (int i = 0; i < 16; i++) {
                if(lista_bloques.b_pointers[i]> 0){
                    links << "Bloque"<<no_bloque<<":"<<i<<" -> Bloque"<<lista_bloques.b_pointers[i]<<"\n";
                    data<< "<tr><td port='"<<i<<"'>"<<lista_bloques.b_pointers[i]<<" </td></tr>\n";
                }
                else{
                    data<< "<tr><td> -1 </td></tr>\n";
                }
            }
            data <<"</table>>];\n\n";
            for (int i = 0; i < 16; i++) {
                if(lista_bloques.b_pointers[i]> 0){
                    generarTxtBloquesArchivos_(disco, data, links,lista_bloques.b_pointers[i], super, nivel - 1);
                }
            }
        }
    }
}

void f2_archivo::generarTxtInodos_(FILE* disco, stringstream &data,stringstream &link, Inodo inodoActual, int no_inodo, SuperBlock super){
    data<<"Inodo"<<no_inodo<<" [label=<\n";
    data<< "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">\n";
    data<< "<tr><td colspan=\"2\">Inodo "<<no_inodo<<" </td></tr>\n";
    //Generamos el string para excribir -------------------------------------------------------------------------
    char i_atime[20];
    char i_ctime[20];
    char i_mtime[20];
    strftime(i_atime, 20, "%d/%m/%Y", localtime(&inodoActual.i_atime));
    strftime(i_ctime, 20, "%d/%m/%Y", localtime(&inodoActual.i_ctime));
    strftime(i_mtime, 20, "%d/%m/%Y", localtime(&inodoActual.i_mtime));
    //i_atime = ctime(&inodoActual.i_atime);
    //i_ctime = ctime(&inodoActual.i_ctime);
    //i_mtime = ctime(&inodoActual.i_mtime);
    data<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">i_uid</font></td><td>"<<inodoActual.i_uid<<"</td></tr>\n";
    data<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">i_gid</font></td><td>"<<inodoActual.i_gid<<"</td></tr>\n";
    data<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">i_size</font></td><td>"<<inodoActual.i_size<<"</td></tr>\n";
    data<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">i_atime</font></td><td>"<<i_atime<<"</td></tr>\n";
    data<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">i_ctime</font></td><td>"<<i_ctime<<"</td></tr>\n";
    data<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">i_mtime</font></td><td>"<<i_mtime<<"</td></tr>\n";
    data<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">i_type</font></td><td>"<<inodoActual.i_type<<"</td></tr>\n";
    data<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">i_perm</font></td><td>"<<inodoActual.i_perm<<"</td></tr>\n";
    data<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">i_block</font></td><td>"<<inodoActual.i_block<<"</td></tr>\n";
    BApuntador i_block = getBloqueApuntador(disco, super.s_block_start, inodoActual.i_block);
    for (int i = 0; i < 16; i++) {
        data<< "<tr><td bgcolor=\"#FE2E2E\"><font color=\"#f7f7f7\">i_block_"<<i<<"</font></td><td port='"<<i<<"'>"<<i_block.b_pointers[i]<<"</td></tr>\n";
        if(i_block.b_pointers[i] > 0){
            link<< "Inodo"<<no_inodo<<":"<<i<<" -> Bloque"<<i_block.b_pointers[i]<<" \n";
        }
    }
    data <<"</table>>];\n\n";

    for (int i = 0; i < 16; i++) {
        //Enlazar inodo con bloques
        if(i_block.b_pointers[i] > 0){
            if(i <= 12){
                if(inodoActual.i_type == '0'){
                    generarTxtBloques_(disco, data, link,i_block.b_pointers[i],super, 0);
                }else{
                    generarTxtBloquesArchivos_(disco, data, link,i_block.b_pointers[i],super, 0);
                }
            }
            else if(i== 13){
                if(inodoActual.i_type == '0'){
                    generarTxtBloques_(disco, data, link,i_block.b_pointers[i],super, 1);
                }else{
                    generarTxtBloquesArchivos_(disco, data, link,i_block.b_pointers[i],super, 1);
                }
            }
            else if(i== 14){
                if(inodoActual.i_type == '0'){
                    generarTxtBloques_(disco, data, link,i_block.b_pointers[i],super, 2);
                }else{
                    generarTxtBloquesArchivos_(disco, data, link,i_block.b_pointers[i],super, 2);
                }
            }
            else if(i== 15){
                if(inodoActual.i_type == '0'){
                    generarTxtBloques_(disco, data, link,i_block.b_pointers[i],super, 3);
                }else{
                    generarTxtBloquesArchivos_(disco, data, link,i_block.b_pointers[i],super, 3);
                }
            }
        }
    }
}

void f2_archivo::reporteArbol(nodo_particiones particion, QString save_path){
    FILE* disco = fopen(particion.path.toStdString().c_str(), "rb+");
    if (disco!=NULL){

        SuperBlock super;
        getSuperBlock( disco, particion, super);
        Inodo inodo0= getInodo(disco, super.s_inode_start, 0);
        if(inodo0.i_type == '0' || inodo0.i_type == '1'){
            stringstream data;
            stringstream links;
            data << "digraph G {\n";
            data << "graph [pad=\"0.5\", nodesep=\"0.5\", ranksep=\"2\"];\n";
            data << "node [shape=plain]\n";
            data << "rankdir=LR;\n\n";
            generarTxtInodos_(disco, data, links, inodo0, 0, super);
            cout<<save_path.toStdString()<<endl;
            QStringList nuevoPath = f2_disco::evaluarDirectorio(save_path, f2_disco::REP);
            if(nuevoPath.size() == 3){
                QString new_path = nuevoPath[0]+"/"+nuevoPath[1];
                try {
                    ofstream file;
                    file.open((new_path+".dot").toStdString().c_str());
                    file<<data.str();
                    file<<links.str();
                    file<<"}";
                    file.close();
                    //QString r = "dot -T"+nuevoPath[2]+" \""+new_path+".dot\"  -o  \""+new_path+"."+nuevoPath[2]+"\"";
                    QString r = "dot -Tpdf \""+new_path+".dot\"  -o  \""+new_path+".pdf\"";
//                    QString r = "dot -T"+nuevoPath[2]+" \""+new_path+".dot\"  -o  \""+new_path+"."+nuevoPath[2]+"\"";
                    if(system(r.toStdString().c_str()) == 0){
                        cout<<"\033[96mReporte creado correctamente.\033[0m"<<endl<<endl;
                    }
                }catch(exception& e) {
                    cout << e.what() << endl;
                }
            }
            else{
                cout<<"\033[31mERROR: No se indicó el nombre con la extención para el reporte en el -path.\033[0m"<<endl<<endl;
            }
        }else{cout<<"\033[31mERROR: No se encontró la carpeta raiz.\033[0m"<<endl<<endl;}
        fclose(disco);//Cerramos el archivo
    }
    else{ cout<<"\033[31mERROR: No se pudo encontrar el archivo.\033[0m"<<endl<<endl;}
}

// REPORTE SUPERBLOQUE
void f2_archivo::reporteSuperBloque(nodo_particiones particion, QString save_path){
    FILE* disco = fopen(particion.path.toStdString().c_str(), "rb+");
    if (disco!=NULL){
        SuperBlock super;
        getSuperBlock( disco, particion, super);
        QStringList nuevoPath = f2_disco::evaluarDirectorio(save_path, f2_disco::REP);
        if(nuevoPath.size() == 3){
            QString new_path = nuevoPath[0]+"/"+nuevoPath[1];
            try {
                ofstream file;
                file.open((new_path+".dot").toStdString().c_str());
                file << "digraph G {\n";
                file << "graph [pad=\"0.5\", nodesep=\"0.5\", ranksep=\"2\"];\n";
                file << "node [shape=plain]\n";
                file << "rankdir=LR;\n\n";
                file<<"SuperBloque [label=<\n";
                file<< "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">\n";
                file<< "<tr><td colspan=\"2\"> Super Bloque </td></tr>\n";
                //Generamos el string para excribir -------------------------------------------------------------------------
                char s_mtime[20];
                char s_umtime[20];
                strftime(s_mtime, 20, "%d/%m/%Y  %H:%M", localtime(&super.s_mtime));
                strftime(s_umtime, 20, "%d/%m/%Y  %H:%M", localtime(&super.s_umtime));
                //i_atime = ctime(&inodoActual.i_atime);
                //i_ctime = ctime(&inodoActual.i_ctime);
                //i_mtime = ctime(&inodoActual.i_mtime);
                file<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">NOMBRE</font></td><td>VALOR</td></tr>\n";
                file<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">s_filesystem_type</font></td><td>"<<super.s_filesystem_type<<"</td></tr>\n";
                file<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">s_inodes_count</font></td><td>"<<super.s_inodes_count<<"</td></tr>\n";
                file<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">s_blocks_count</font></td><td>"<<super.s_blocks_count<<"</td></tr>\n";
                file<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">s_free_blocks_count</font></td><td>"<<super.s_free_blocks_count<<"</td></tr>\n";
                file<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">s_free_inodes_count</font></td><td>"<<super.s_free_inodes_count<<"</td></tr>\n";
                file<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">s_mtime</font></td><td>"<<s_mtime<<"</td></tr>\n";
                file<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">s_umtime</font></td><td>"<<s_umtime<<"</td></tr>\n";
                file<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">s_mnt_count</font></td><td>"<<super.s_mnt_count<<"</td></tr>\n";
                file<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">s_magic</font></td><td>0xEF53</td></tr>\n";
                file<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">s_inode_size</font></td><td>"<<super.s_inode_size<<"</td></tr>\n";
                file<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">s_block_size</font></td><td>"<<super.s_block_size<<"</td></tr>\n";
                file<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">s_first_ino</font></td><td>"<<super.s_firts_ino<<"</td></tr>\n";
                file<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">s_firts_blo</font></td><td>"<<super.s_first_blo<<"</td></tr>\n";
                file<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">s_bm_inode_start</font></td><td>"<<super.s_bm_inode_start<<"</td></tr>\n";
                file<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">s_bm_block_start</font></td><td>"<<super.s_bm_block_start<<"</td></tr>\n";
                file<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">s_inode_start</font></td><td>"<<super.s_inode_start<<"</td></tr>\n";
                file<< "<tr><td bgcolor=\"#0040FF\"><font color=\"#d7d7d7\">s_block_start</font></td><td>"<<super.s_block_start<<"</td></tr>\n";
                file <<"</table>>];\n\n";
                file<<"}";
                file.close();
                QString r = "dot -T"+nuevoPath[2]+" \""+new_path+".dot\"  -o  \""+new_path+"."+nuevoPath[2]+"\"";

                if(system(r.toStdString().c_str()) == 0){
                    cout<<"\033[96mReporte creado correctamente.\033[0m"<<endl<<endl;
                }
            }catch(exception& e) {
                cout << e.what() << endl;
            }
        }
        else{
            cout<<"\033[31mERROR: No se indicó el nombre con la extención para el reporte en el -path.\033[0m"<<endl<<endl;
        }
        fclose(disco);//Cerramos el archivo
    }
    else{ cout<<"\033[31mERROR: No se pudo encontrar el archivo.\033[0m"<<endl<<endl;}
}

// REPORTE FILE

void f2_archivo::reporteFile(QString path, QString ruta){
    Inodo_dato find = getInodoByPath(ruta);
    if(find.inodo >= 0){
        Inodo inodo = getInodo(disco, super.s_inode_start, find.inodo);
        BCarpeta blo = getBloqueCarpeta(disco, super.s_block_start, find.bloque_padre);
        QString nom = blo.b_content[find.posicion].b_name;
        if(inodo.i_type == '1'){
            QString dato = getFileContent(inodo);
            QStringList nuevoPath = f2_disco::evaluarDirectorio(path, f2_disco::REP);
            if(nuevoPath.size() == 3){
                QString new_path = nuevoPath[0]+"/"+nuevoPath[1];
                try {
                    ofstream file;
                    file.open((new_path+".dot").toStdString().c_str());
                    file << "digraph G {\n";
                    file << " node [shape=box]\n";
                    file << " rankdir=LR;\n\n";
                    file << " node1 [label=\""<<dato.toStdString()<<"\"] \n";
                    file << " name [label=\""<<nom.mid(0,12).toStdString()<<"\" color=white]\n";
                    file << "}";
                    file.close();
                    QString r = "dot -T"+nuevoPath[2]+" \""+new_path+".dot\"  -o  \""+new_path+"."+nuevoPath[2]+"\"";
                    if(system(r.toStdString().c_str()) == 0){
                        cout<<"\033[96mReporte creado correctamente.\033[0m"<<endl<<endl;
                    }
                }catch(exception& e) {
                    cout << e.what() << endl;
                }
            }
            else{
                cout<<"\033[31mERROR: No se indicó el nombre con la extención para el reporte en el -path.\033[0m"<<endl<<endl;
            }


        }else{cout<<"\033[31mERROR: No se especifico el archivo en la ruta.\033[0m"<<endl<<endl;}
    }else{cout<<"\033[31mERROR: No se encontró el archivo.\033[0m"<<endl<<endl;}
}

QString f2_archivo::lsPermisos(Inodo inodo){
    QString permiso;
    Permiso u = getPermisoInodo(inodo.i_perm, 'u');
    Permiso g = getPermisoInodo(inodo.i_perm, 'g');
    Permiso o = getPermisoInodo(inodo.i_perm, 'o');
    QString aux = "";
    if(u.lectura == 1){aux += "r";}else{aux += "-";}
    if(u.escritura == 1){aux += "w";}else{aux += "-";}
    if(u.ejecucion == 1){aux += "x";}else{aux += "-";}
    permiso += aux+" ";
    aux = "";
    if(g.lectura == 1){aux += "r";}else{aux += "-";}
    if(g.escritura == 1){aux += "w";}else{aux += "-";}
    if(g.ejecucion == 1){aux += "x";}else{aux += "-";}
    permiso += aux+" ";
    aux = "";
    if(o.lectura == 1){aux += "r";}else{aux += "-";}
    if(o.escritura == 1){aux += "w";}else{aux += "-";}
    if(o.ejecucion == 1){aux += "x";}else{aux += "-";}
    permiso += aux+" ";
    return permiso;
}

void f2_archivo::lsTxtInodo(Inodo inodo, QString name, QString owner, QString grp, stringstream &data){
    QString permisos = lsPermisos(inodo);
    string tipo;
    if(inodo.i_type == '0'){ tipo = "Carpeta";}
    else{ tipo = "Archivo";}
    char fecha[20];
    char hora[20];
    strftime(fecha, 20, "%d/%m/%Y", localtime(&inodo.i_mtime));
    strftime(hora, 20, "%H:%M", localtime(&inodo.i_mtime));
    data<< "<tr><td>"<<permisos.toStdString()<<"</td>";
    data<<"<td> "<<owner.toStdString()<<" </td>";
    data<<"<td> "<<grp.toStdString()<<"</td>";
    data<<"<td> "<<inodo.i_size<<" </td>";
    data<<"<td> "<<fecha<<" </td>";
    data<<"<td> "<<hora<<" </td>";
    data<<"<td> "<<tipo<<" </td>";
    data<<"<td> "<<name.toStdString()<<" </td></tr>\n";
}

void f2_archivo::lsCarpetaChilds(int espacio, stringstream &data,QHash<int, QString> usr, QHash<int, QString> grp, int nivel){
    if(espacio >= 0){
        if(nivel == 0){
            BCarpeta carp = getBloqueCarpeta(disco, super.s_block_start, espacio);
            int id_inodo;
            for (int i = 0; i < 4; i++) {
                id_inodo = carp.b_content[i].b_inodo;
                if(id_inodo >= 0){
                    Inodo inodo = getInodo(disco, super.s_inode_start, id_inodo);
                    lsTxtInodo(inodo, carp.b_content[i].b_name, usr[inodo.i_uid], grp[inodo.i_gid], data);
                    if(inodo.i_type == '0'){
                        BApuntador ap = getBloqueApuntador(disco, super.s_block_start, inodo.i_block);
                        for (int n = 0; n < 16; n++) {
                            int new_espacio = ap.b_pointers[n];
                            if(new_espacio < 0){continue;}
                            if(n <= 12){
                                lsCarpetaChilds(new_espacio, data, usr, grp, 0);
                            }else if( n == 13){
                                lsCarpetaChilds(new_espacio, data, usr, grp, 1);
                            }else if( n == 14){
                                lsCarpetaChilds(new_espacio, data, usr, grp, 2);
                            }else if( n == 15){
                                lsCarpetaChilds(new_espacio, data, usr, grp, 3);
                            }
                        }
                    }
                }
            }

        }else{
            BApuntador apuntador = getBloqueApuntador(disco, super.s_block_start, espacio);
            for (int i = 0; i < 16; i++) {
                int space = apuntador.b_pointers[i];
                if(space < 0){continue;}
                lsCarpetaChilds(space, data, usr, grp, nivel -1);
            }
        }
    }
}

void f2_archivo::reporteLs(QString path, QString ruta){
    Inodo_dato find = getInodoByPath(ruta);
    stringstream data;
    if(find.inodo >= 0){
        QListIterator<QString> users = getDatosUsers();
        QHash<int,QString> list_users;
        QHash<int,QString> list_groups;

        while (users.hasNext()) {
            QString row = users.next();
            if(row.size() > 0){
                QStringList lista = row.split(',');
                if(QString::compare(lista.value(1).trimmed(),"u", Qt::CaseInsensitive) == 0){
                    list_users[lista.value(0).trimmed().toInt()] = lista.value(3).trimmed();
                    //cout<<lista.value(0).trimmed().toInt()<<endl;
                }
                else{
                    list_groups[lista.value(0).trimmed().toInt()] = lista.value(2).trimmed();
                }
            }
        }
        data << "digraph G {\n";
        data << "graph [pad=\"0.5\", nodesep=\"0.5\", ranksep=\"2\"];\n";
        data << "node [shape=plain]\n";
        data << "rankdir=LR;\n\n";
        Inodo inodo = getInodo(disco, super.s_inode_start, find.inodo);
        data<<"Tabla [label=<\n";
        data<< "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">\n";
        data<< "<tr><td> PERMISOS </td><td> OWNER </td><td> GRUPO </td><td> SIZE(bytes) </td><td> FECHA </td><td> HORA </td><td> TIPO </td><td> NAME </td></tr>\n";
        BCarpeta padre = getBloqueCarpeta(disco, super.s_block_start, find.bloque_padre);
        //lsTxtInodo(inodo, padre.b_content[find.posicion].b_name, list_groups[inodo.i_uid], list_groups[inodo.i_gid], data);
        /***************************ACA SE ARREGLO**********************************************************/
        lsTxtInodo(inodo, padre.b_content[find.posicion].b_name, list_users[inodo.i_uid], list_groups[inodo.i_gid], data);
        if(inodo.i_type == '0'){
            BApuntador ap = getBloqueApuntador(disco, super.s_block_start, inodo.i_block);
            for (int i = 0; i < 16; i++) {
                int espacio = ap.b_pointers[i];
                if(espacio < 0){continue;}
                if(i <= 12){
                    lsCarpetaChilds(espacio, data, list_users, list_groups, 0);
                }else if( i == 13){
                    lsCarpetaChilds(espacio, data, list_users, list_groups, 1);
                }else if( i == 14){
                    lsCarpetaChilds(espacio, data, list_users, list_groups, 2);
                }else if( i == 15){
                    lsCarpetaChilds(espacio, data, list_users, list_groups, 3);
                }
            }
        }
        data <<"</table>>];\n\n";
        QStringList nuevoPath = f2_disco::evaluarDirectorio(path, f2_disco::REP);
        if(nuevoPath.size() == 3){
            QString new_path = nuevoPath[0]+"/"+nuevoPath[1];
            try {
                ofstream file;
                file.open((new_path+".dot").toStdString().c_str());
                file<<data.str();
                file<<"}";
                file.close();
                QString r = "dot -T"+nuevoPath[2]+" \""+new_path+".dot\"  -o  \""+new_path+"."+nuevoPath[2]+"\"";
                if(system(r.toStdString().c_str()) == 0){
                    cout<<"\033[96mReporte creado correctamente.\033[0m"<<endl<<endl;
                }
            }catch(exception& e) {
                cout << e.what() << endl;
            }
        }
        else{
            cout<<"\033[31mERROR: No se indicó el nombre con la extención para el reporte en el -path.\033[0m"<<endl<<endl;
        }

    }else{cout<<"\033[31mERROR: No se encontró el archivo.\033[0m"<<endl<<endl;}

}
