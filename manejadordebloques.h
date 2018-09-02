#ifndef MANEJADORDEBLOQUES_H
#define MANEJADORDEBLOQUES_H
#include "datafile.h"
#include "bloque.h"
#include "masterblock.h"

class ManejadordeBloques
{
    public:
        ManejadordeBloques(DataFile *a,int t);
        void formatearDataFile(int t);
        DataFile * archivo;
        Bloque * asignarNueboBloque();
        void actualizarMasterBlock();
        void createDataBase(int tam,int n);
        MasterBlock * masterBlock;
        Bloque * cargarBloque(int numeroBloque);
};

#endif // MANEJADORDEBLOQUES_H
