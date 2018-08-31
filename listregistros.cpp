#include "listregistros.h"
#include "registro.h"
ListRegistros::ListRegistros()
{
    inicio=0;
    fin=0;
    cantidad=0;
}

void ListRegistros::add(Registro *r)
{
    if(inicio==0)
        inicio=r;
    else
        fin->sig=r;
    fin=r;
    cantidad++;
}

Registro * ListRegistros::get(int pos)
{
    if(pos>cantidad)
        return 0;
    int c=0;
    Registro * tmp=inicio;
    while(c<cantidad)
    {
        if(c==pos)
            return tmp;
        tmp=tmp->sig;
        c++;
    }
    return 0;
}



