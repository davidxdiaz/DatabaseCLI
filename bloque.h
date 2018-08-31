#ifndef BLOQUE_H
#define BLOQUE_H
#include "datafile.h"

class Bloque
{
    public:
        Bloque(DataFile * file,int numBloque,int tamanoBloque,int s);
        Bloque(int num,int tam);
        int nBloque;
        int tamBloque;
        void escribir();
        void cargar();
        char * toChar();
        void charToBloque(char * data);
        DataFile * archivo;
        int siguiente;

    protected:

    private:
};

#endif // BLOQUE_H
