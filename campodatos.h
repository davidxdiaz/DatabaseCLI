#ifndef CAMPODATOS_H
#define CAMPODATOS_H
#include "campo.h"

class CampoDatos
{
    public:
        CampoDatos(char val[20],campo * dCampos);
        char valor[20];
        campo * defCampos;
        CampoDatos * sig;
        int getIntValue();
        double getDoubleValue();
        char * getCharValue();
        void printValor();
        void toString();
        char * toChar();
        void initFromChar(char * data);

    private:
};

#endif // CAMPODATOS_H
