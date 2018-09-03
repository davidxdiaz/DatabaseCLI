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
        void escribir(char * registro,int longitud);
        void cargar(int longitud);
        void actualizarCantidad();
        char * toChar(char * registro,int longitud);
        void charToBloque(char * data,int longitud);
        ListRegistros * registros;

        Registro * getRegsitro(int pos,int longitud);
};

#endif // BLOQUEREGISTRO_H
