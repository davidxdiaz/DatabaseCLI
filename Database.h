//
// Created by David Diaz on 31/08/2018.
//

#ifndef PROYECTOED2_MASTER_DATABASE_H
#define PROYECTOED2_MASTER_DATABASE_H

#include "datafile.h"
#include "manejadordebloques.h"
#include "manejadrotablas.h"
#include <iostream>
using namespace std;
class Database {
    public:
        Database(string name);
        DataFile * archivo;
        char* dataName;
        char * path;
        ManejadordeBloques * mBloques;
        ManejadroTablas * mTablas;
        bool dropDatabase();
        void cerrarConexion();
        void iniciarConexion();
        //Debe de tener funciones de proyeccion
};


#endif //PROYECTOED2_MASTER_DATABASE_H
