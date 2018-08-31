#include "listbloquetablas.h"
#include "bloquetabla.h"

ListBloqueTablas::ListBloqueTablas()
{
    inicio=0;
    fin=0;
    cantidad=0;
}

void ListBloqueTablas::addBT(BloqueTabla * bt)
{
    if(inicio==0)
        inicio=bt;
    else
        fin->sig=bt;
    fin=bt;
    cantidad++;
}

BloqueTabla * ListBloqueTablas::get(int pos)
{
    if(pos>cantidad)
        return 0;
    int c=0;
    BloqueTabla * tmp=inicio;
    while(c<cantidad)
    {
        if(c==pos)
            return tmp;
        tmp=tmp->sig;
        c++;
    }
    return 0;
}

void ListBloqueTablas::limpiar()
{
    inicio=0;
    fin=0;
}


