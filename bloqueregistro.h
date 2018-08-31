#ifndef BLOQUEREGISTRO_H
#define BLOQUEREGISTRO_H
#include "datafile.h"
#include "listregistros.h"

class BloqueRegistro
{
    public:
        BloqueRegistro(DataFile * archivo,int nBloque);
        int nBloque;
        DataFile * archivo;
        int cantidad;
        int tamBloque;
        int siguiente;
        int longitudRegistro;
        void escribir();
        void cargar(int longitud);
        void actualizarCantidad();
        char * toChar();
        void charToBloque(char * data,int longitud);
        ListRegistros * registros;
        Registro * getRegsitro(int pos,int longitud);
};

#endif // BLOQUEREGISTRO_H
