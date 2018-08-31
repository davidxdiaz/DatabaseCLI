#ifndef LISTREGISTROS_H
#define LISTREGISTROS_H
#include "registro.h"

class ListRegistros
{
    public:
        ListRegistros();
        Registro * inicio;
        Registro * fin;
        void add(Registro * r);
        Registro * get(int pos);
        int cantidad;
};

#endif // LISTREGISTROS_H
