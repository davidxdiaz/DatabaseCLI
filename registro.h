#ifndef REGISTRO_H
#define REGISTRO_H
#include "listcampodatos.h"
#include "listcampos.h"

class Registro
{
    public:
        Registro(int longitud,int id);
        ListCampoDatos * campoDatos;
        ListCampos * listaCampos;
        int longitudRegistro;
        int idRegistro;
        Registro * sig;
        char * toChar();
        void initFromChar(char * data);
        void printRegistro();

    private:
};

#endif // REGISTRO_H
