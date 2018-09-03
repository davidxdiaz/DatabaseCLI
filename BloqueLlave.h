//
// Created by David on 17/9/2017.
//

#ifndef PROYECTOED2_MASTER_BLOQUELLAVE_H
#define PROYECTOED2_MASTER_BLOQUELLAVE_H

#include "Idx_Entry.h"
#include "datafile.h"

class BloqueLlave {
public:
    BloqueLlave(DataFile *a,int nB,int t);

    int nBloque;
    int siguiente;
    int tamano;
    int cantidad;
    void actualizarCantidad();
    Idx_Entry * llaves[17];
    char * toChar();
    void initFromChar(char * data);
    void escribir();
    void cargar();
    DataFile * archivo;
};


#endif //PROYECTOED2_MASTER_BLOQUELLAVE_H
