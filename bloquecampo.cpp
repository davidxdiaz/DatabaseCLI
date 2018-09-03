#include "bloquecampo.h"
#include "datafile.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "listcampos.h"
#include <iostream>
using namespace std;

BloqueCampo::BloqueCampo(DataFile * file,int numBloque,int t)
{
    nBloque=numBloque;
    tamBloque=t;
    siguiente=-1;
    archivo=file;
    cantidad=0;
    campos=new ListCampos();
}

void BloqueCampo::escribir()
{
    char * data= this->toChar();
    int pos= nBloque * tamBloque+24;
    archivo->escribir(data,pos,tamBloque);
}

void BloqueCampo::cargar()
{
    int pos= nBloque * tamBloque+20;
    char * data=archivo->leer(pos,tamBloque);
    charToBloque(data);
}

void BloqueCampo::charToBloque(char * data)
{
    int pos=0;
    memcpy(&nBloque,&data[pos],4);
    pos+=4;
    memcpy(&tamBloque,&data[pos],4);
    pos+=4;
    memcpy(&siguiente,&data[pos],4);
    pos+=4;
    memcpy(&cantidad,&data[pos],4);
    pos+=4;
    for(int x=0;x<cantidad;x++)
    {
        campo *c= new campo("",0,0);
        c->initFromChar(&data[pos]);
        campos->add(c);
        pos+=28;
    }
}

char * BloqueCampo::toChar()
{
    char * data= new char[tamBloque];
    int pos=0;
    memcpy(&data[pos],&nBloque,4);
    pos+=4;
    memcpy(&data[pos],&tamBloque,4);
    pos+=4;
    memcpy(&data[pos],&siguiente,4);
    pos+=4;
    memcpy(&data[pos],&cantidad,4);
    pos+=4;
    for(int c=0;c<cantidad;c++)
    {
        char * entry_data= campos->get(c)->toChar();

        memcpy(&data[pos],entry_data,28);
        pos+=28;
    }
    //cout<<data[16]<<endl;
    return data;
}




