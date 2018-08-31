#include "listtabla.h"
#include "tabla.h"
#include <iostream>
using namespace std;

ListTabla::ListTabla()
{
    inicio=0;
    fin=0;
    cantidad=0;
}

void ListTabla::addTabla(tabla *t)
{
    if(inicio==0)
        inicio=t;
    else
        fin->sig=t;
    fin=t;
    cantidad++;
}

tabla * ListTabla::get(int pos)
{
    if(pos>cantidad)
        return 0;
    int c=0;
    tabla * tmp=inicio;
    while(c<cantidad)
    {
        if(c==pos)
            return tmp;
        tmp=tmp->sig;
        c++;
    }
    return 0;
}


