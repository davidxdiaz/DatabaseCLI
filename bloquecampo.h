#ifndef BLOQUECAMPO_H
#define BLOQUECAMPO_H
#include "datafile.h"
#include "listcampos.h"

class BloqueCampo
{
    public:
        BloqueCampo(DataFile * a,int numBloque);
        int nBloque;
        int tamBloque;
        void escribir();
        void cargar();
        char * toChar();
        void charToBloque(char * data);
        DataFile * archivo;
        int siguiente;
        int cantidad;
        ListCampos * campos;

};

#endif // BLOQUECAMPO_H
