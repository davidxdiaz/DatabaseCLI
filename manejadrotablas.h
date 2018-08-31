#ifndef MANEJADROTABLAS_H
#define MANEJADROTABLAS_H
#include "listbloquetablas.h"
#include "tabla.h"
#include "datafile.h"
#include "manejadordebloques.h"
#include "masterblock.h"
#include "bloquetabla.h"
#include "registro.h"
#include "manejadorjson.h"
class ManejadroTablas
{
    public:
        ManejadroTablas(DataFile *a,MasterBlock *masterBlock);
        void listarTablas();
        tabla * buscarTabla(int id);
        BloqueTabla * buscarBloqueTabla(int n);
        ListBloqueTablas * listaBT;
        void cargarBT();
        void crearTabla(char name[20],int id,ManejadordeBloques * manejador);
        void crearCampo(int id,char nombreCampo[20],int tipo,ManejadordeBloques * manejador);
        void addRegistro(int id,ManejadordeBloques * manejador,Registro *r);
        DataFile * archivo;
        ManejadorJson * mj;
        MasterBlock * mb;
        void importar(ManejadordeBloques *mb,int sig);
        void exportar(int n);
};

#endif // MANEJADROTABLAS_H
