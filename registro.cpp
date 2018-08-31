#include "registro.h"
#include "listcampodatos.h"
#include <stdio.h>
#include <string.h>
#include "campodatos.h"
#include <iostream>
using namespace std;
Registro::Registro(int longitud)
{
    campoDatos= new ListCampoDatos();
    sig=0;
    longitudRegistro=longitud;
}

char * Registro::toChar()
{
    int pos=0;
    char * data= new char[longitudRegistro];
    //cout<<longitudRegistro<<endl;
    for(int c=0;c<campoDatos->cantidad;c++)
    {
        char * data_entry=campoDatos->get(c)->toChar();
        memcpy(&data[pos],data_entry,strlen(data_entry));
        pos=pos+20;
    }
    return data;
}

void Registro::initFromChar(char * data)
{
    int pos=0;
    for(int c=0;c<longitudRegistro;c+=20)
    {
        CampoDatos * cam= new CampoDatos("",0);
        cam->initFromChar(&data[pos]);
        campoDatos->add(cam);
        pos+=20;
    }
}

void Registro::printRegistro()
{
    for(int c=0;c<campoDatos->cantidad;c++)
    {
        cout<<" "<<campoDatos->get(c)->defCampos->nombre<<": "<<campoDatos->get(c)->valor<<endl;
    }
}


