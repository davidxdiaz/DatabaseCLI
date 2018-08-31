//
// Created by David on 17/9/2017.
//

#ifndef PROYECTOED2_MASTER_BLOQUEINDICE_H
#define PROYECTOED2_MASTER_BLOQUEINDICE_H

#include "datafile.h"
#include <string.h>
#include "HashTableEntry.h"

class BloqueIndice {
public:
    BloqueIndice(DataFile * archivo,int nBloque);
    int nBloque;
    int siguiente;
    int tamano;
    int cantidad;
    void actualizarCantidad();
    HashTableEntry * indice[62];
    char * toChar();
    void initFromChar(char * data);
    void escribir();
    void cargar();
    DataFile * archivo;
    HashTableEntry * getEntrada(int pos);
    void listarElementos();

};


#endif //PROYECTOED2_MASTER_BLOQUEINDICE_H
