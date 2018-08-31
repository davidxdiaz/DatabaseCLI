#ifndef LISTCAMPODATOS_H
#define LISTCAMPODATOS_H
#include "campodatos.h"

class ListCampoDatos
{
    public:
        ListCampoDatos();
        CampoDatos * inicio;
        CampoDatos * fin;
        void add(CampoDatos * cd);
        CampoDatos * get(int pos);
        int cantidad;

    protected:

    private:
};

#endif // LISTCAMPODATOS_H
