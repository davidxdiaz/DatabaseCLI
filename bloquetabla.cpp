#include "bloquetabla.h"
#include "listtabla.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "tabla.h"
#include "datafile.h"
#include "datafile.h"
#include <iostream>
using namespace std;

BloqueTabla::BloqueTabla(DataFile * a,int nB)
{
    nBloque=nB;
    siguiente=-1;
    tamano=512;
    cantidad=0;
    tablas=new ListTabla();

    archivo=a;
    sig=0;
}

BloqueTabla::BloqueTabla(int n)
{
    nBloque=n;
    tamano=512;
    tablas=new ListTabla();
}

void BloqueTabla::actualizarCantidad()
{
    cantidad++;
}

char * BloqueTabla::toChar()
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

        char * entry_data= tablas->get(c)->toChar();
        memcpy(&data[pos],entry_data,56);
        pos+=56;
    }
    return data;
}

void BloqueTabla::initFromChar(char * data)
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
        tabla *t= new tabla("",0,0,0,0,0,0,archivo,0,0,0);
        t->charToTabla(&data[pos]);
        tablas->addTabla(t);
        pos+=56;
    }
}

void BloqueTabla::escribir()
{
    char * data= this->toChar();
    int pos= nBloque * tamano+20;
    archivo->escribir(data,pos,tamano);
}

void BloqueTabla::cargar()
{
    int pos= nBloque * tamano+20;
    char * data= archivo->leer(pos,tamano);
    initFromChar(data);
}


