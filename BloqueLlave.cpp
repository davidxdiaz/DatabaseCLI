//
// Created by David on 17/9/2017.
//

#include "BloqueLlave.h"
#include "string.h"

BloqueLlave::BloqueLlave(DataFile * a,int nB,int t)
{
    nBloque=nB;
    siguiente=-1;
    tamano=t;
    cantidad=0;
    archivo=a;
}


void BloqueLlave::actualizarCantidad()
{
    cantidad++;
}

char * BloqueLlave::toChar()
{
    int pos=0;
    char * data= new char[tamano];
    memcpy(&data[pos],&nBloque,4);
    pos+=4;
    memcpy(&data[pos],&tamano,4);
    pos+=4;
    memcpy(&data[pos],&siguiente,4);
    pos+=4;
    memcpy(&data[pos],&cantidad,4);
    pos+=4;
    for(int c=0;c<cantidad;c++)
    {
        memcpy(&data[pos],llaves[c]->toChar(),28);
        pos+=28;
    }
    return data;
}

void BloqueLlave::initFromChar(char * data)
{
    int pos=0;
    memcpy(&nBloque,&data[pos],4);
    pos+=4;
    memcpy(&tamano,&data[pos],4);
    pos+=4;
    memcpy(&siguiente,&data[pos],4);
    pos+=4;
    memcpy(&cantidad,&data[pos],4);
    pos+=4;
    for(int c=0;c<cantidad;c++)
    {
        char * id= new char[20];
        int nB;
        int nRR;
        memcpy(id,&data[pos],20);
        pos+=20;
        memcpy(&nB,&data[pos],4);
        pos+=4;
        memcpy(&nRR,&data[pos],4);
        pos+=4;
        Idx_Entry * entrada= new  Idx_Entry(id,nB,nRR);
        llaves[c]=entrada;
    }
}

void BloqueLlave::escribir()
{
    char * data= this->toChar();
    int pos= nBloque * tamano+28;
    archivo->escribir(data,pos,tamano);
}

void BloqueLlave::cargar()
{
    int pos= nBloque * tamano+28;
    char * data= archivo->leer(pos,tamano);
    initFromChar(data);
}