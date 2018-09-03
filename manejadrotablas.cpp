#include "manejadrotablas.h"
#include "listbloquetablas.h"
#include "listtabla.h"
#include "bloquetabla.h"
#include "tabla.h"
#include "manejadordebloques.h"
#include "bloque.h"
#include <iostream>
#include "masterblock.h"
#include "registro.h"
using namespace std;


ManejadroTablas::ManejadroTablas(DataFile *a,MasterBlock * masterBlock,ManejadordeBloques * mbl)
{
    archivo=a;
    mj= new ManejadorJson();
    listaBT= new ListBloqueTablas();
    mb=masterBlock;
    if(masterBlock->primerBloqueTabla!=-1)
    {
        cargarBT();
        for(int x=0;x<listaBT->cantidad;x++)
        {
            BloqueTabla * bt=listaBT->get(x);
            for(int c=0;c<bt->cantidad;c++)
            {
                tabla * t=bt->tablas->get(c);
                t->cargarCampos(masterBlock->tamanoBloque);
                t->cargarRegistros(mbl);
            }
        }

    }

}

void ManejadroTablas::crearTabla(char name[20],int id,ManejadordeBloques * manejador)
{
    tabla * t = new tabla(name,id,-1,-1,-1,-1,0,archivo,-1,-1,manejador->masterBlock->tamChar,manejador->masterBlock->tamanoBloque);//Debe asignarse correctamente el Tamano del char
    if(manejador->masterBlock->primerBloqueTabla==-1)
    {
        BloqueTabla * bt= new BloqueTabla(archivo,0,manejador->masterBlock->tamanoBloque);
        bt->tablas->addTabla(t);
        bt->actualizarCantidad();
        bt->escribir();
        listaBT->addBT(bt);
        manejador->masterBlock->actualBloqueTabla=0;
        manejador->masterBlock->primerBloqueTabla=0;
        manejador->masterBlock->guardar();
        return;
    }
    //Meto la tabla en la lista de algun bloque tabla
    int op=0;
    for(int x=0;x<listaBT->cantidad;x++)
    {
        BloqueTabla * bt=listaBT->get(x);
        int maximo = 9;
        if(bt->cantidad<maximo)
        {
            t->nBloque=bt->nBloque;
            bt->tablas->addTabla(t);
            bt->actualizarCantidad();
            bt->escribir();
            return;
        }
        op=x;
    }

    Bloque * b =manejador->asignarNueboBloque();
    BloqueTabla * bt=listaBT->get(op);
    bt->siguiente=b->nBloque;
    bt->escribir();
    BloqueTabla * tmp= new BloqueTabla(b->archivo,b->nBloque,manejador->masterBlock->tamanoBloque);
    t->nBloque=tmp->nBloque;
    tmp->tablas->addTabla(t);
    tmp->actualizarCantidad();
    tmp->escribir();
    manejador->masterBlock->actualBloqueTabla=tmp->nBloque;
    manejador->masterBlock->guardar();
    listaBT->addBT(tmp);

}

void ManejadroTablas::listarTablas()
{
    for(int x=0;x<listaBT->cantidad;x++)
    {
        BloqueTabla * bt=listaBT->get(x);
        for(int c=0;c<bt->cantidad;c++)
        {
            tabla * t=bt->tablas->get(c);
            //printf(t->nombre);
            //printf("\n");
            //cout<<t->nombre<<endl;
            t->toString();
        }
    }
}

tabla * ManejadroTablas::buscarTabla(int id)
{
    for(int x=0;x<listaBT->cantidad;x++)
    {
        BloqueTabla * bt=listaBT->get(x);
        for(int c=0;c<bt->tablas->cantidad;c++)
        {
            tabla * t=bt->tablas->get(c);
            if(t->id==id)
                return t;
        }
    }
    return 0;
}

BloqueTabla * ManejadroTablas::buscarBloqueTabla(int n)
{
    for(int c=0;c<listaBT->cantidad;c++)
    {
        BloqueTabla * bt= listaBT->get(c);
        if(bt->nBloque==n)
            return bt;
    }
    return 0;
}

void ManejadroTablas::cargarBT()
{
    int actual=mb->primerBloqueTabla;
    BloqueTabla * bloque= new BloqueTabla(archivo,actual,mb->tamanoBloque);
    bloque->cargar();
    listaBT->addBT(bloque);
    while(bloque->siguiente !=-1)
    {
        actual=bloque->siguiente;
        bloque= new BloqueTabla(archivo,actual,mb->tamanoBloque);
        bloque->cargar();
        listaBT->addBT(bloque);
    }
}

void ManejadroTablas::crearCampo(int id,char nombreCampo[20],int tipo,ManejadordeBloques * manejador)
{
    tabla * t = buscarTabla(id);
    if(t!=0)
    {
        t->crearCampo(manejador,nombreCampo,tipo);
        BloqueTabla * bt = buscarBloqueTabla(t->nBloque);
        bt->escribir();
    }
    else
    {
        cout<<"Nombre Incorrecto"<<endl;
    }
}

void ManejadroTablas::addRegistro(int id,ManejadordeBloques * manejador,Registro * r)
{
    tabla * t = buscarTabla(id);
    if(t!=0)
    {
        t->crearRegistro(manejador,r);
        t->contRegistros++;
        BloqueTabla * bt = buscarBloqueTabla(t->nBloque);
        bt->escribir();
    }
    else
    {
        cout<<"Nombre Incorrecto"<<endl;
    }
}

void ManejadroTablas::importar(ManejadordeBloques *mb, int sig)
{
    if(sig==-1)
        return;
    string bTabla= "BloqueTabla";
    string tabla= "Tabla";
    string campos="Campos";
    string registros="Registros";
    string tipo="Tipo";
    //BloqueTabla * bt;
    ostringstream bt;
    bt<<bTabla<<'_'<<sig;
    int cantTablas=  mj->j[bt.str()]["NumeroTablas"].get<int>();

    for(int c=0;c < cantTablas;c++)
    {

        ostringstream ta;
        ta<<tabla<<'_'<<c;


        //Saco las variables para crear la tabla y enlazar los campos y registros de la tabla
        int id=mj->j[bt.str()][ta.str()]["Id"].get<int>();
        char * nombre= new char[20];
        string ntemp;
        ntemp=mj->j[bt.str()][ta.str()]["Nombre"].get<string>();
        strncpy(nombre,ntemp.c_str(),20);
        //Creo la tabla
        crearTabla(nombre,id,mb);

        //Obtengo la cantidad de campos
        int cantCampos= mj->j[bt.str()][ta.str()]["NCampos"].get<int>();
        //Obtengo la cantidad de registros
        int nRegistros =mj->j[bt.str()][ta.str()]["NRegistros"].get<int>();
        for(int x=0;x< cantCampos;x++)
        {
            ostringstream cam;
            ostringstream tp;

            cam<<campos<<'_'<<x;
            tp<<campos<<'_'<<x<<'_'<<tipo;

            char * nameCampo= new char[20];

            ntemp= mj->j[bt.str()][ta.str()][cam.str()].get<string>();
            strncpy(nameCampo,ntemp.c_str(),20);
            int tipo=  mj->j[bt.str()][ta.str()][tp.str()].get<int>();

            campo * camp= new campo(nameCampo,tipo,0);//Debo modificar correctamente la longitud donde esta 0, cambiarlo por una funcion que devuelva la longitud segun el tipo de dato
            crearCampo(id,nameCampo,tipo,mb);


        }
        for(int i=0;i<nRegistros;i++)
        {
            Registro * registro = new Registro(buscarTabla(id)->getLongitudRegistros());// Debeo de cambiar el tam de char

            for(int x=0;x< cantCampos;x++)
            {
                ostringstream reg;
                reg<<registros<<'_'<<i<<'_'<<x;
                char *valor= new char[20];

                ntemp=mj->j [bt.str()][ta.str()][reg.str()].get<string>();
                strncpy(valor,ntemp.c_str(),20);
                CampoDatos * campDatos= new CampoDatos(valor,buscarTabla(id)->campos->get(x));
                registro->campoDatos->add(campDatos);
            }
            addRegistro(id,mb,registro);


        }


    }
    sig=mj->j [bt.str()]["BloqueSiguiente"].get<int>();
    importar(mb,sig);


}

void ManejadroTablas::exportar(int n)
{
    if(n==-1)
        return;
    BloqueTabla * bt = buscarBloqueTabla(n);
    int cantTablas= bt->tablas->cantidad;
    string bTabla= "BloqueTabla";
    string tabla= "Tabla";
    string campos="Campos";
    string registros="Registros";
    string tipo="Tipo";


    for(int c=0;c<cantTablas;c++)
    {
        ostringstream t;
        ostringstream b;
        b<<bTabla<<'_'<<n;
        t<<tabla<<'_'<<c;

        mj->j[b.str()]["NumeroTablas"]=bt->tablas->cantidad;
        mj->j [b.str()]["BloqueSiguiente"]=bt->siguiente;

        mj->j[b.str()] [t.str()] ["Id"]=bt->tablas->get(c)->id;
        mj->j [b.str()] [t.str()] ["Nombre"]=bt->tablas->get(c)->nombre;
        int nCampos=bt->tablas->get(c)->campos->cantidad;
        mj->j [b.str()] [t.str()] ["NCampos"]=nCampos;
        int nRegistros=bt->tablas->get(c)->registros->cantidad;
        mj->j [b.str()] [t.str()] ["NRegistros"]=nRegistros;

        for(int x=0;x<nCampos;x++)
        {
            ostringstream cam;
            ostringstream tp;
            cam<<campos<<'_'<<x;
            tp<<campos<<'_'<<x<<'_'<<tipo;

            mj->j[b.str()] [t.str()] [cam.str()] = bt->tablas->get(c)->campos->get(x)->nombre;
            mj->j[b.str()] [t.str()] [tp.str()] = bt->tablas->get(c)->campos->get(x)->tipo;

            for(int i=0;i<nRegistros;i++)
            {
                ostringstream reg;
                reg<<registros<<'_'<<i<<'_'<<x;

                mj->j [b.str()][t.str()][reg.str()]= bt->tablas->get(c)->registros->get(i)->campoDatos->get(x)->valor;
            }

        }

    }
    exportar(bt->siguiente);
}


