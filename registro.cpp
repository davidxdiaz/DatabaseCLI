#include "registro.h"
#include "listcampodatos.h"
#include <stdio.h>
#include <string.h>
#include "campodatos.h"
#include <iostream>
using namespace std;
Registro::Registro(int longitud,int id)
{
    campoDatos= new ListCampoDatos();
    idRegistro=id;
    sig=0;
    longitudRegistro=longitud;
}

char * Registro::toChar()
{
    int pos=0;
    char * data= new char[longitudRegistro+4]; //Escribire un id registro interno para asi manejar la hashtable
    //cout<<longitudRegistro<<endl;
    memcpy(&data[pos],&idRegistro,4);
    pos+=4;
    for(int c=0;c<campoDatos->cantidad;c++)
    {
        CampoDatos * campoDato= campoDatos->get(c);
        int l=campoDato->defCampos->longitud;
        char * data_entry=campoDato->toChar();
        memcpy(&data[pos],data_entry,l);
        pos=pos+l;
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
    cout<<"Id Registro: "<<idRegistro<<endl;
    for(int c=0;c<campoDatos->cantidad;c++)
    {
        cout<<" "<<campoDatos->get(c)->defCampos->nombre<<": "<<campoDatos->get(c)->valor<<endl;
    }
}


