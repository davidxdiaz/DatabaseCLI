#include "masterblock.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "datafile.h"

using namespace std;
MasterBlock::MasterBlock(DataFile *a,int sigBD,int primerBT,int actualBT,int tamBloque)
{
    sigBloqueDisponible=sigBD;
    tamanoBloque=tamBloque;
    primerBloqueTabla=primerBT;
    actualBloqueTabla=actualBT;
    sizeMasterB=24;
    archivo=a;
    ultimoBloque=1;
}

MasterBlock::MasterBlock(DataFile *a)
{
    archivo=a;
    sizeMasterB=24;
}

char * MasterBlock::toChar()
{
    char * data= new char[sizeMasterB];
    int pos=0;
    memcpy(&data[pos],&sigBloqueDisponible,4);
    pos+=4;
    memcpy(&data[pos],&tamanoBloque,4);
    pos+=4;
    memcpy(&data[pos],&primerBloqueTabla,4);
    pos+=4;
    memcpy(&data[pos],&actualBloqueTabla,4);
    pos+=4;
    memcpy(&data[pos],&sizeMasterB,4);
    pos+=4;
    memcpy(&data[pos],&ultimoBloque,4);
    pos+=4;
    return data;
}

void MasterBlock::charToBloque(char * data)
{
    int pos=0;
    memcpy(&sigBloqueDisponible,&data[pos],4);
    pos+=4;
    memcpy(&tamanoBloque,&data[pos],4);
    pos+=4;
    memcpy(&primerBloqueTabla,&data[pos],4);
    pos+=4;
    memcpy(&actualBloqueTabla,&data[pos],4);
    pos+=4;
    memcpy(&sizeMasterB,&data[pos],4);
    pos+=4;
    memcpy(&ultimoBloque,&data[pos],4);
    pos+=4;
}

void MasterBlock::guardar()
{
    char * data= this->toChar();
    archivo->escribir(data,0,sizeMasterB);
}

void MasterBlock::cargar()
{
    char * data=archivo->leer(0,sizeMasterB);
    charToBloque(data);
}

void MasterBlock::print() {
    cout<<" Imprimiendo MasterBlock "<<endl<<"Siguiente Bloque Disponible "<<sigBloqueDisponible<<" size de los bloques "<<tamanoBloque<<" primer bloque tabla "<<primerBloqueTabla<<" actual bloque tablas "<<actualBloqueTabla<<" size de MB "<<sizeMasterB<<" ultimo bloque "<<ultimoBloque<<endl;
}
