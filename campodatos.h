#ifndef CAMPODATOS_H
#define CAMPODATOS_H
#include "campo.h"

class CampoDatos
{
    public:
        CampoDatos(char * val,campo * dCampos);
        char *valor;
        campo * defCampos;
        CampoDatos * sig;
        int getIntValue();
        double getDoubleValue();
        char * getCharValue();
        void printValor();
        void toString();
        char * toChar();
        void initFromChar(char * data,int t);

    private:
};

#endif // CAMPODATOS_H
