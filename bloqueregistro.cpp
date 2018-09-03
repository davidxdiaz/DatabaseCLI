#include <cstring>
#include "bloqueregistro.h"
#include <iostream>
using namespace std;

BloqueRegistro::BloqueRegistro(DataFile * archivo,int nBloque,char * r,int t)
{
    this->archivo=archivo;
    this->nBloque=nBloque;
    tamBloque=t;
    siguiente=-1;
    registros= new ListRegistros();
    registro= r;
}
void BloqueRegistro::escribir(char * registro,int longitud)
{
    char * data= this->toChar(registro,longitud);
    int pos= nBloque * tamBloque+24;
    archivo->escribir(data,pos,tamBloque);
}
void BloqueRegistro::cargar(int longitud)
{
    int pos= nBloque * tamBloque+20;
    char * data=archivo->leer(pos,tamBloque);
    charToBloque(data,longitud);
}
void BloqueRegistro::actualizarCantidad()
{
    //this->cantidad++;
}
char *BloqueRegistro::toChar(char * registro,int longitud)
{
    char * data= new char[tamBloque];
    int pos=0;
    memcpy(&data[pos],&nBloque,4);
    pos+=4;
    memcpy(&data[pos],&tamBloque,4);
    pos+=4;
    memcpy(&data[pos],&siguiente,4);
    pos+=4;
    memcpy(&data[pos],registro,longitud);
    pos+=longitud;
    return data;
}
void BloqueRegistro::charToBloque(char *data, int longitud)
{
    int pos=0;
    memcpy(&nBloque,&data[pos],4);
    pos+=4;
    memcpy(&tamBloque,&data[pos],4);
    pos+=4;
    memcpy(&siguiente,&data[pos],4);
    pos+=4;
    memcpy(registro,&data[pos],longitud);
    pos+=longitud;
}

Registro * BloqueRegistro::getRegsitro(int pos,int longitud) {
    this->cargar(longitud);
    Registro * r= registros->get(pos);
    return r;
}
