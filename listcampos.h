#ifndef LISTCAMPOS_H
#define LISTCAMPOS_H
#include "campo.h"

class ListCampos
{
    public:
        ListCampos();
        campo * inicio;
        campo * fin;
        void add(campo * c);
        void limpiar();
        campo * get(int pos);
        int cantidad;

    private:
};

#endif // LISTCAMPOS_H
