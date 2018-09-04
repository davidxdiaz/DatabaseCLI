#include "registro.h"
#include "listcampodatos.h"
#include <stdio.h>
#include <string.h>
#include "campodatos.h"
#include <iostream>
#include "listcampos.h"
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
    char * data= new char[longitudRegistro]; //Escribire un id registro interno para asi manejar la hashtable
    //cout<<longitudRegistro<<endl;
    memcpy(&data[pos],&idRegistro,20);
    pos+=20;
    for(int c=0;c<campoDatos->cantidad;c++)
    {
        CampoDatos * campoDato= campoDatos->get(c);
        int l=campoDato->defCampos->longitud;
        char * data_entry = campoDato->toChar();
        memcpy(&data[pos],data_entry,l);
        pos=pos+l;
    }
    return data;
}

void Registro::initFromChar(char * data,ListCampos * campos)
{
    int pos=0;
    for(int c=0;c<longitudRegistro;c++)
    {
        campo * ca = campos->get(c);
        CampoDatos * cam= new CampoDatos("",0);
        cam->initFromChar(&data[pos],ca->longitud);
        campoDatos->add(cam);
        pos+=ca->longitud;
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


