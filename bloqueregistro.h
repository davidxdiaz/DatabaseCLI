#ifndef BLOQUEREGISTRO_H
#define BLOQUEREGISTRO_H
#include "datafile.h"
#include "listregistros.h"

class BloqueRegistro
{
    public:
        BloqueRegistro(DataFile * archivo,int nBloque,char * r,int t);
        int nBloque;
        DataFile * archivo;
        int tamBloque;
        int siguiente;
        int longitudRegistro;
        char * registro;
        void escribir();
        void cargar();
        void actualizarCantidad();
        char * toChar();
        void charToBloque(char * data);
        ListRegistros * registros;

        Registro * getRegsitro(int pos,int longitud);
};

#endif // BLOQUEREGISTRO_H
