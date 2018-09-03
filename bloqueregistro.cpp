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
void BloqueRegistro::escribir()
{
    char * data= this->toChar();
    int pos= nBloque * tamBloque+28;
    archivo->escribir(data,pos,tamBloque);
}
void BloqueRegistro::cargar()
{
    int pos= nBloque * tamBloque+28;
    char * data=archivo->leer(pos,tamBloque);
    charToBloque(data);
}
void BloqueRegistro::actualizarCantidad()
{
    //this->cantidad++;
}
char *BloqueRegistro::toChar()
{
    char * data= new char[tamBloque];
    int pos=0;
    memcpy(&data[pos],&nBloque,4);
    pos+=4;
    memcpy(&data[pos],&tamBloque,4);
    pos+=4;
    memcpy(&data[pos],&siguiente,4);
    pos+=4;
    memcpy(&data[pos],&longitudRegistro,4);
    pos+=4;
    memcpy(&data[pos],registro,longitudRegistro);
    pos+=longitudRegistro;
    return data;
}
void BloqueRegistro::charToBloque(char *data)
{
    int pos=0;
    memcpy(&nBloque,&data[pos],4);
    pos+=4;
    memcpy(&tamBloque,&data[pos],4);
    pos+=4;
    memcpy(&siguiente,&data[pos],4);
    pos+=4;
    memcpy(&longitudRegistro,&data[pos],4);
    pos+=4;
    char *r = new char[longitudRegistro];
    memcpy(r,&data[pos],longitudRegistro);
    //registro=r;
    pos+=longitudRegistro;
}

Registro * BloqueRegistro::getRegsitro(int pos,int longitud) {
    this->cargar();
    Registro * r= registros->get(pos);
    return r;
}
