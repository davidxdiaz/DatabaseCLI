#include "manejadordebloques.h"
#include "bloque.h"
#include "datafile.h"
#include <iostream>
using namespace std;

ManejadordeBloques::ManejadordeBloques(DataFile *a)
{
    archivo=a;
    if(archivo->isVacio()==true)
    {
        formatearDataFile();
        asignarNueboBloque();
        actualizarMasterBlock();
    }else
    {
        masterBlock= new MasterBlock(archivo,0,-1,-1);
        masterBlock->cargar();
    }
}

void ManejadordeBloques::formatearDataFile()
{
    masterBlock= new MasterBlock(archivo,0,-1,-1);
    masterBlock->guardar();
}

Bloque * ManejadordeBloques::asignarNueboBloque()
{
    Bloque * bloque = new Bloque(archivo,masterBlock->sigBloqueDisponible,masterBlock->tamanoBloque,-1);
    masterBlock->sigBloqueDisponible++;
    bloque->escribir();
    masterBlock->guardar();
    return bloque;
}

Bloque * ManejadordeBloques::cargarBloque(int numeroBloque)
{
    Bloque * bloque= new Bloque(numeroBloque,masterBlock->tamanoBloque);
    bloque->cargar();
    return bloque;
}

void ManejadordeBloques::actualizarMasterBlock()
{
    //cout<<"BloqueTabla"<<masterBlock->primerBloqueTabla<<endl;
    masterBlock->guardar();
}

