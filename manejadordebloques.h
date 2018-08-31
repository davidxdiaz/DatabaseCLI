#ifndef MANEJADORDEBLOQUES_H
#define MANEJADORDEBLOQUES_H
#include "datafile.h"
#include "bloque.h"
#include "masterblock.h"

class ManejadordeBloques
{
    public:
        ManejadordeBloques(DataFile *a);
        void formatearDataFile();
        DataFile * archivo;
        Bloque * asignarNueboBloque();
        void actualizarMasterBlock();
        MasterBlock * masterBlock;
        Bloque * cargarBloque(int numeroBloque);
};

#endif // MANEJADORDEBLOQUES_H
