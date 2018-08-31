#ifndef BLOQUETABLA_H
#define BLOQUETABLA_H
#include "listtabla.h"
#include "datafile.h"
//#include <tabla.h>
#include <vector>
class BloqueTabla
{
    public:
        BloqueTabla(DataFile * archivo,int nB);
        BloqueTabla(int nB);
        int nBloque;
        int siguiente;
        int tamano;
        int cantidad;
        void actualizarCantidad();
        ListTabla * tablas;
        char * toChar();
        void initFromChar(char * data);
        void escribir();
        void cargar();
        DataFile * archivo;
        BloqueTabla * sig;
        //vector<tabla>tablas;



    protected:

    private:
};

#endif // BLOQUETABLA_H
