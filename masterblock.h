#ifndef MASTERBLOCK_H
#define MASTERBLOCK_H
#include "datafile.h"

class MasterBlock
{
    public:
        MasterBlock(DataFile *archivo,int sigBD,int primerBT,int actualBT,int tamBloque,int tChar);
        MasterBlock(DataFile *a);
        int sigBloqueDisponible;
        int tamanoBloque;
        int primerBloqueTabla;
        int actualBloqueTabla;
        int sizeMasterB;
        int ultimoBloque;
        int tamChar;
        char * toChar();
        void charToBloque(char * data);
        void guardar();
        void cargar();
        void print();
        DataFile * archivo;
};

#endif // MASTERBLOCK_H
