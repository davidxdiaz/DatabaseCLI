#include "campo.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

campo::campo(char name[20],int t)
{
    strncpy(nombre,name,20);
    tipo=t;
    longitud=20;
    sig=0;

}

char * campo::toChar()
{
    int pos=0;
    char * data= new char[28];
    memcpy(&data[pos],nombre,20);
    pos+=20;
    memcpy(&data[pos],&tipo,4);
    pos+=4;
    memcpy(&data[pos],&longitud,4);
    pos+=4;
    return data;
}

void campo::initFromChar(char * data)
{
    int pos=0;
    memcpy(nombre,&data[pos],20);
    pos+=20;
    memcpy(&tipo,&data[pos],4);
    pos+=4;
    memcpy(&longitud,&data[pos],4);
    pos+=4;
}




