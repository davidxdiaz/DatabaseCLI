#include "datafile.h"
#include <io.h>
#include <stdlib.h>
#include <cstring>
#include <stdio.h>
#include <iostream>
using namespace std;

DataFile::DataFile(char * p)
{
    path=p;
    //Me aseguro de que se cree y no se reemplaze
    if( (_access( path, 0 )) == -1 )
    {
        archivo=fopen(path,"wb+");
        cerrar();
    }

}

void DataFile::abrir()
{
    archivo=fopen(path,"rb+");
}

void DataFile::cerrar()
{
    fclose(archivo);
}

void DataFile::escribir(char * data,int pos,int longitud)
{
    //Me muevo a la posicion
    fseek(archivo,pos,SEEK_SET);
    //Escribo en eñ archivo
    fwrite(data, 1,longitud,archivo);
}

char * DataFile::leer(int pos,int longitud)
{
    // Creo la data vacia con tamaño de longitud
    char *data=new char[longitud];
    // Me muevo a la posicion
    fseek(archivo,pos,SEEK_SET);
    //Leo lo que hay en esa posicion y lo escribo en la variable data
    fread(data,1, longitud,archivo);
    return data;
}

bool DataFile::isVacio()
{
    fseek(archivo,0,SEEK_END);
    return ftell(archivo)>0 ? false:true;
}

bool DataFile::tieneBTabla()
{
    fseek(archivo,0,SEEK_END);
    return ftell(archivo)>532? true:false;
}

