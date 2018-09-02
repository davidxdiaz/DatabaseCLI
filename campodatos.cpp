#include "campodatos.h"
#include "campo.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
CampoDatos::CampoDatos(char val[20],campo *dCampos)
{
    strncpy(valor,val,20);
    defCampos=dCampos,
    sig=0;
}

int CampoDatos::getIntValue()
{
    return (int)(valor-48);
}

double CampoDatos::getDoubleValue() {
    double val;
    memcpy(&val,&valor[0],8);
    return val;
}

char * CampoDatos::getCharValue()
{
    return valor;
}

void CampoDatos::printValor()
{
    int tipo = defCampos->tipo;
    if(tipo==0)
        cout<<getIntValue();
    else if(tipo==1)
        cout<<getDoubleValue();
    else
        cout<<getCharValue();
}

void CampoDatos::toString()
{
    cout<<"Campo: "<<defCampos->nombre<<" Valor: ";
    printValor();
    cout<<endl;
}

char * CampoDatos::toChar()
{
    int pos=0;
    char * data= new char[20];
    memcpy(&data[pos],valor,20);
    pos+=20;
    return data;
}

void CampoDatos::initFromChar(char * data)
{
    int pos=0;
    memcpy(valor,&data[pos],20);
    pos+=20;
}



