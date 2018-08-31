#ifndef LISTTABLA_H
#define LISTTABLA_H
#include "tabla.h"

class ListTabla
{
    public:
        ListTabla();
        tabla * inicio;
        tabla * fin;
        void addTabla(tabla * t);
        tabla * get(int pos);
        int cantidad;

};

#endif // LISTTABLA_H
