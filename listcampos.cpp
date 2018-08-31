#include "listcampos.h"

ListCampos::ListCampos()
{
    inicio=0;
    fin=0;
    cantidad=0;
}

void ListCampos::add(campo * c)
{
    if(inicio==0)
        inicio=c;
    else
        fin->sig=c;
    fin=c;
    cantidad++;
}

campo * ListCampos::get(int pos)
{
    if(pos>cantidad)
        return 0;
    int c=0;
    campo * tmp=inicio;
    while(c<cantidad)
    {
        if(c==pos)
            return tmp;
        tmp=tmp->sig;
        c++;
    }
    return 0;
}

void ListCampos::limpiar()
{
    inicio=0;
    fin=0;
}
