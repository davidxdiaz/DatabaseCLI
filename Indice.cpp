//
// Created by David on 17/9/2017.
//

#include "Indice.h"
#include "BloqueIndice.h"
#include "HashTableEntry.h"
#include "BloqueLlave.h"
#include <iostream>
using  namespace std;

Indice::Indice(DataFile * a, int primer,int actual,int maximo)
{
    archivo=a;
    primerBIndice=primer;
    actualBIndice=actual;
    if(maximo==0)
        M=62;
    else
        M=maximo;
}

bool Indice::insertar(Idx_Entry * e,ManejadordeBloques * mb)
{
    int pos= hash(e->id);

    if(buscar(e->id,mb)==0){

        Idx_Entry * entrada=e; //new Idx_Entry(id,nBloque,nRegistroR);
        int cont=0;
        if(pos>62) {

            for (int x = 0; x < pos; x += 62) {
                cont++;
            }
        }
        int bloqueActual = primerBIndice;
        for(int c=0;c<cont;c++)
        {
            BloqueIndice * bIndice= new BloqueIndice(archivo,bloqueActual,mb->masterBlock->tamanoBloque);
            bIndice->cargar();
            bloqueActual=bIndice->siguiente;
            delete bIndice;
        }
        if(cont>0)
            cont--;
        int posDef= pos - (cont * 62);
        BloqueIndice * bloque= new BloqueIndice(archivo,bloqueActual,mb->masterBlock->tamanoBloque);
        bloque->cargar();
        HashTableEntry * entry= bloque->getEntrada(posDef);
        if(entry->primerBloqueLLave==-1)
        {

            int n = mb->asignarNueboBloque()->nBloque;
            BloqueLlave * bLlave= new BloqueLlave(archivo,n,mb->masterBlock->tamanoBloque);

            bLlave->llaves[0]=entrada;
            bLlave->actualizarCantidad();

            entry->primerBloqueLLave=bLlave->nBloque;
            entry->actualBloqueLLave=bLlave->nBloque;
            bloque->escribir();//Porque actualice uno de sus entry
            bLlave->escribir();
            return true;

        }
        int bloqueLlaves= entry->actualBloqueLLave;
        BloqueLlave * b = new BloqueLlave(archivo,bloqueLlaves,mb->masterBlock->tamanoBloque);
        b->cargar();
        int posicion=b->cantidad;
        if(posicion<17)
        {
            b->llaves[posicion]=entrada;
            b->actualizarCantidad();
            b->escribir();
            return true;
        }
        else
        {
            Bloque * block = mb->asignarNueboBloque();
            BloqueLlave *bLlave = new BloqueLlave(archivo,block->nBloque,mb->masterBlock->tamanoBloque);
            BloqueLlave * tmp= new BloqueLlave(archivo,entry->actualBloqueLLave,mb->masterBlock->tamanoBloque);
            tmp->cargar();
            tmp->siguiente=bLlave->nBloque;
            tmp->escribir();
            bLlave->llaves[0]=entrada;
            bLlave->actualizarCantidad();
            entry->actualBloqueLLave=bLlave->nBloque;
            bloque->escribir();//Porque actualice uno de sus entry
            bLlave->escribir();
            return true;
        }
    }
    return false;
}

int Indice::hash(char * id)
{
    int clave=0;
    int ascii;
    for(int c=0;id[c]!='\0';c++)
    {
        ascii = (int)(id[c]);
        clave+=ascii;
    }
    int n=clave%M;
    return n;
}

Idx_Entry * Indice::buscar(char * id,ManejadordeBloques * mb)
{
    int pos = hash(id);
    cout<<"Pos "<<pos<<endl;
    int cont=0;
    if(pos>62)
    {
        for(int x=0;x<pos;x+=62){
            cont++;
        }
    }

    int bloqueActual = primerBIndice;
    for(int c=0;c<cont;c++)
    {
        BloqueIndice * bIndice= new BloqueIndice(archivo,bloqueActual,mb->masterBlock->tamanoBloque);
        bIndice->cargar();
        bloqueActual=bIndice->siguiente;
        delete bIndice;
    }
    if(cont>0)
        cont--;
    int posDef= pos - (cont * 62);
    BloqueIndice * bloque= new BloqueIndice(archivo,bloqueActual,mb->masterBlock->tamanoBloque);
    bloque->cargar();

    HashTableEntry * entry= bloque->getEntrada(posDef);
    int bloqueLlaves = entry->primerBloqueLLave;

    while (bloqueLlaves !=-1){
        BloqueLlave * b= new BloqueLlave(archivo,bloqueLlaves,mb->masterBlock->tamanoBloque);

        b->cargar();

        for (int c = 0; c < b->cantidad; c++) {
            Idx_Entry *entrada = b->llaves[c];
            if (strcmp(entrada->id,id)==0) {
                return entrada;
            }
            delete entrada;
        }
        bloqueLlaves = b->siguiente;
        delete b;
    }
    return 0;
}

void Indice::actualizarIndice(int p, int a, int m) {
    primerBIndice=p;
    actualBIndice=a;
    M=m;
}


/*void Indice::reHash(ManejadordeBloques * mB)
{
    HashTableEntry * tmp[M];
    for(int c=0;c<M;c++)
    {

    }

    M=M *2;
    HashTableEntry * tabla[M];
    int actual = primerBIndice;
    while (actual!=-1){
        BloqueIndice * bloque = new BloqueIndice(archivo,actual);
        bloque->cargar();
        for(int c=0;c<bloque->cantidad;c++)
        {
            HashTableEntry * tmp= bloque->getEntrada(c);
            int actualBLLave= tmp->primerBloqueLLave;
            while (actualBLLave!=-1)
            {
                BloqueLlave * bLlave= new BloqueLlave(archivo,actualBLLave);
                bLlave->cargar();
                for(int x=0;x<bLlave->cantidad;x++)
                {
                    Idx_Entry * idx= bLlave->llaves[x];
                    insertar(idx->id,idx->numeroBloque,idx->numeroRR,mB);
                }
                actualBLLave=bLlave->siguiente;
                delete  bLlave;
            }
        }
        actual=bloque->siguiente;
        delete  bloque;
    }



}*/