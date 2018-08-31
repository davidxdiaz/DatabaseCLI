//
// Created by David on 17/9/2017.
//

#include "BloqueIndice.h"
#include <iostream>
using namespace std;

BloqueIndice::BloqueIndice(DataFile * a,int nB)
{
    nBloque=nB;
    siguiente=-1;
    tamano=512;
    cantidad=0;
    for(int c=0;c<62;c++)
        indice[c]=new HashTableEntry(-1,-1);


    archivo=a;
}


void BloqueIndice::actualizarCantidad()
{
    cantidad++;
}

char * BloqueIndice::toChar()
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
    for(int c=0;c<62;c++)
    {
        char * dataEntry= indice[c]->toChar();
        memcpy(&data[pos],dataEntry,8);
        pos+=8;
    }
    return data;
}

void BloqueIndice::initFromChar(char * data)
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
    for(int c=0;c<62;c++)
    {
        char * dataEntry= new char[8];
        memcpy(dataEntry,&data[pos],8);
        HashTableEntry * h= new HashTableEntry(-1,-1);
        h->initFromChar(dataEntry);
        indice[c]= h;
        pos+=8;
    }
}

void BloqueIndice::listarElementos() {
    for(int c=0;c<62;c++)
    {
        cout<<"Elemento "<<c<<endl;
        cout<<indice[c]->primerBloqueLLave<<endl<<indice[c]->actualBloqueLLave<<endl<<endl;

    }

}

void BloqueIndice::escribir()
{
    char * data= this->toChar();
    int pos= nBloque * tamano+20;
    archivo->escribir(data,pos,tamano);
}

void BloqueIndice::cargar()
{
    int pos= nBloque * tamano+20;
    char * data= archivo->leer(pos,tamano);
    initFromChar(data);
}

HashTableEntry * BloqueIndice::getEntrada(int p)
{
    return indice[p];
}