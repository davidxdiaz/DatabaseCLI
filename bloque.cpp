#include "bloque.h"
#include "datafile.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

Bloque::Bloque(DataFile * file,int numBloque,int tamanoBloque,int s)
{
    nBloque=numBloque;
    tamBloque=tamanoBloque;
    siguiente=s;
    archivo=file;
}

Bloque::Bloque(int num,int tam)
{
    nBloque=num;
    tamBloque=tam;
}

void Bloque::escribir()
{
    char * data= this->toChar();
    int pos= nBloque * tamBloque+20;
    archivo->escribir(data,pos,tamBloque);
}

void Bloque::cargar()
{
    int pos= nBloque * tamBloque+20;
    char * data=archivo->leer(pos,tamBloque);
    charToBloque(data);
}

void Bloque::charToBloque(char * data)
{
    int pos=0;
    memcpy(&nBloque,&data[pos],4);
    pos+=4;
    memcpy(&tamBloque,&data[pos],4);
    pos+=4;
    memcpy(&siguiente,&data[pos],4);
    pos+=4;
}

char * Bloque::toChar()
{
    char * data= new char[tamBloque];
    int pos=0;
    memcpy(&data[pos],&nBloque,4);
    pos+=4;
    memcpy(&data[pos],&tamBloque,4);
    pos+=4;
    memcpy(&data[pos],&siguiente,4);
    pos+=4;
    return data;
}


