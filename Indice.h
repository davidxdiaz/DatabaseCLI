//
// Created by David on 17/9/2017.
//

#ifndef PROYECTOED2_MASTER_INDICE_H
#define PROYECTOED2_MASTER_INDICE_H
#include "Idx_Entry.h"
#include "datafile.h"
#include "manejadordebloques.h"
#include "BloqueIndice.h"

class Indice {
public:
    Indice(DataFile * a,int primerBIndice,int actualBIndice,int maximo);
    int primerBIndice;
    int actualBIndice;
    bool insertar(Idx_Entry *e,ManejadordeBloques * mb);
    Idx_Entry * buscar(char * id,ManejadordeBloques * mB);
    void reHash(ManejadordeBloques * mB);
    BloqueIndice * clonar();
    void manejadorBIndice(ManejadordeBloques * mB);
    int hash(char *id);
    int M;
    void actualizarIndice(int p,int a,int m);

    DataFile * archivo;
};


#endif //PROYECTOED2_MASTER_INDICE_H
