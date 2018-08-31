#include "listcampodatos.h"
#include "campodatos.h"
ListCampoDatos::ListCampoDatos()
{
    inicio=0;
    fin=0;
    cantidad=0;
}

void ListCampoDatos::add(CampoDatos *cd)
{
    if(inicio==0)
        inicio=cd;
    else
        fin->sig=cd;
    fin=cd;
    cantidad++;
}

CampoDatos * ListCampoDatos::get(int pos)
{
    if(pos>cantidad)
        return 0;
    int c=0;
    CampoDatos * tmp=inicio;
    while(c<cantidad)
    {
        if(c==pos)
            return tmp;
        tmp=tmp->sig;
        c++;
    }
    return 0;
}
