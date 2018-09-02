#include <cstring>
#include "bloqueregistro.h"
#include <iostream>
using namespace std;

BloqueRegistro::BloqueRegistro(DataFile * archivo,int nBloque)
{
    this->archivo=archivo;
    this->nBloque=nBloque;
    tamBloque=512;
    siguiente=-1;
    this->cantidad=0;
    registros= new ListRegistros();
}
void BloqueRegistro::escribir()
{
    char * data= this->toChar();
    int pos= nBloque * tamBloque+20;
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
    this->cantidad++;
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
    memcpy(&data[pos],&cantidad,4);
    pos+=4;
    for(int c=0;c<cantidad;c++)
    {
        Registro * r=registros->get(c);
        int x=r->longitudRegistro;
        char * entry_data= r->toChar();
        memcpy(&data[pos],entry_data,x);
        pos+=x;
    }
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
    memcpy(&cantidad,&data[pos],4);
    pos+=4;
    for(int c=0;c<cantidad;c++)
    {
        Registro * r= new Registro(longitud,0);
        r->initFromChar(&data[pos]);
        registros->add(r);
        pos+=longitud;
    }
}

Registro * BloqueRegistro::getRegsitro(int pos,int longitud) {
    this->cargar(longitud);
    Registro * r= registros->get(pos);
    return r;
}
