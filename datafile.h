#ifndef DATAFILE_H
#define DATAFILE_H
#include <stdio.h>

class DataFile
{
    public:
        DataFile(char * p);
        char * path;
        FILE * archivo;
        void abrir();
        void cerrar();
        void escribir(char * data,int pos,int longitud);
        char * leer(int pos,int longitud);
        bool isVacio();
        int longitud;
        bool tieneBTabla();

    protected:

    private:
};

#endif // DATAFILE_H
