#ifndef LISTBLOQUETABLAS_H
#define LISTBLOQUETABLAS_H
#include "bloquetabla.h"

class ListBloqueTablas
{
    public:
        ListBloqueTablas();
        BloqueTabla * inicio;
        BloqueTabla * fin;
        void addBT(BloqueTabla * bt);
        void limpiar();
        BloqueTabla * get(int pos);
        int cantidad;
};

#endif // LISTBLOQUETABLAS_H
