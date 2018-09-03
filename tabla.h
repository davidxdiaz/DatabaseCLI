#ifndef TABLA_H
#define TABLA_H
#include "listcampos.h"
#include "datafile.h"
#include  "registro.h"
#include "listregistros.h"
#include "manejadordebloques.h"
#include "Indice.h"

class tabla
{
    public:
        tabla(char name[20],int i,int pBCampos,int actualBCampos,int pBDatos,int actualBDatos,int nB,DataFile * a,int primerBIndice,int actualBIndice,int tChar,int tamBloque);
        DataFile * archivo;
        char nombre[20];
        int id;
        int primerBloqueCampos;
        int actualBloqueCampos;
        int primerBloqueDatos;
        int actualBloqueDatos;
        int primerBloqueIndice;
        int actualBloqueIndice;
        int nBloque;
        int tamChar;
        int contRegistros;
        int eliminado;
        ListCampos * campos;
        ListRegistros * registros;
        char * toChar();
        void charToTabla(char * data,int t);
        tabla * sig;
        void toString();
        void cargarCampos(int t);
        void cargarRegistros(ManejadordeBloques * mbloques);
        void crearCampo(ManejadordeBloques * mbloques, char name[20],int tipo);
        void crearRegistro(ManejadordeBloques * mbloques,Registro *r);
        Registro * interpretarRegistro(char * data,int longitud);
        int getLongitudRegistros();
        void printTabla();
        Indice * indice;
        int getTamanoHashTable(int t);
        Registro * buscarRegistro(char *id,ManejadordeBloques * mb);
        void manejadorBIndice(ManejadordeBloques * mB);


    protected:

    private:
};

#endif // TABLA_H
