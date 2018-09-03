#ifndef REGISTRO_H
#define REGISTRO_H
#include "listcampodatos.h"
#include "listcampos.h"

class Registro
{
    public:
        Registro(int longitud);
        ListCampoDatos * campoDatos;
        ListCampos * listaCampos;
        int longitudRegistro;
        char idRegistro[20];
        Registro * sig;
        char * toChar();
        void initFromChar(char * data);
        void printRegistro();

    private:
};

#endif // REGISTRO_H
