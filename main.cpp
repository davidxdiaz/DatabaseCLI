#include <iostream>
#include "datafile.h"
#include "bloque.h"
#include "manejadrotablas.h"
#include "manejadordebloques.h"
#include "bloquecampo.h"
#include "bloquetabla.h"
#include <stdio.h>
#include "masterblock.h"
#include "tabla.h"
#include "registro.h"
#include "campodatos.h"
#include "bloque.h"
#include "bloquecampo.h"
#include "bloqueregistro.h"
#include "campo.h"
#include "campodatos.h"
#include "BloqueIndice.h"
#include "Database.h"
using namespace std;

int main()
{
    //Creo la base de Datos
    Database * db = new Database("BaseDatos",8192,2000);
    //Pruebo el crear la base de datos
    //->createDataBase(10,"MB");
    db->mBloques->masterBlock->print();


    //Proyecto anterior
    /*DataFile * archivo = new DataFile("C:\\Users\\USUARIO\\Desktop\\BaseDatos.data");
    archivo->abrir();
    ManejadordeBloques * mbloques= new ManejadordeBloques(archivo);
    ManejadroTablas * mtablas=new ManejadroTablas(archivo,mbloques->masterBlock);*/


    for(int c=0;c<1;c++)
    {
        char * nombre= new char[20];
        nombre[0]='t';
        nombre[1]='a';
        nombre[2]='b';
        nombre[3]='l';
        nombre[4]='a';
        nombre[5]='_';
        char cadena[1000];
        sprintf(cadena, "%d", c);
        for(int x=0;cadena[x]!='\0';x++)
        {
            nombre[x+6]=cadena[x];
        }
        db->mTablas->crearTabla(nombre,c,db->mBloques);
        string id="ID";
        string name="Nombre";
        string edad="Edad";
        //ostringstream nom;
        //ostringstream i;
        //ostringstream e;
        char * nom = const_cast<char *>(name.c_str());
        char * i = const_cast<char *>(id.c_str());
        char * e = const_cast<char *>(edad.c_str());
        db->mTablas->crearCampo(c,i,0,db->mBloques);
        db->mTablas->crearCampo(c,nom,2,db->mBloques);
        db->mTablas->crearCampo(c,e,0,db->mBloques);

    }//*/
    for(int c=1;c<2;c++)
    {
        int x=0;

        cout<<"tabla "<<x<<endl;
        Registro * r= new Registro(db->mTablas->buscarTabla(x)->getLongitudRegistros());
        string id="id";
        string name="nombre";
        char edad= (char) (c+48);
        ostringstream nomb;
        stringstream idd;
        ostringstream ed;
        idd<<id<<'_'<<c;
        nomb<<name<<'_'<<c;
        ed<<c;
        char * nom = const_cast<char *>(nomb.str().c_str());
        char * i = const_cast<char *>(idd.str().c_str());
        char * e = const_cast<char *>(ed.str().c_str());
        CampoDatos * d1=new CampoDatos(i,db->mTablas->buscarTabla(x)->campos->get(0));
        CampoDatos * d2=new CampoDatos(nom,db->mTablas->buscarTabla(x)->campos->get(1));
        CampoDatos * d3=new CampoDatos(e,db->mTablas->buscarTabla(x)->campos->get(2));
        cout<<"Agrego CampoDatos"<<endl;
        r->campoDatos->add(d1);
        r->campoDatos->add(d2);
        r->campoDatos->add(d3);
        cout<<"Antes de agregar registro"<<endl;
        db->mTablas->addRegistro(x,db->mBloques,r);
        cout<<"Agrego el registro"<<endl;
    }//*/

    //Probando listar Tablas
    db->mTablas->listarTablas();
    db->mBloques->masterBlock->print();

    //Probando la hashTable//
    //db->mTablas->buscarTabla(0)->toString();

   /* BloqueIndice * b = new BloqueIndice(db->archivo,3);
    b->cargar();
    b->listarElementos();//*/
    db->mTablas->buscarTabla(0)->buscarRegistro("id_0",db->mBloques)->printRegistro();


    //Probando Json
    /*mtablas->exportar(0);
    mtablas->mj->guardar();//*/
    /*mtablas->mj->cargar();
    mtablas->importar(mbloques,0);//*/

    //db->dropDatabase();
    db->cerrarConexion();

    return 0;
}
