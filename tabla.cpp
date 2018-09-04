#include "tabla.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "listcampos.h"
#include "bloquecampo.h"
#include "datafile.h"
#include "bloqueregistro.h"
#include "registro.h"
#include "campodatos.h"
#include "listregistros.h"
#include "manejadordebloques.h"
#include "listbloquetablas.h"
#include "bloquecampo.h"
#include "registro.h"
#include "Idx_Entry.h"
#include "BloqueIndice.h"
#include <stdio.h>

#include <string.h>
#include <sstream>

using namespace std;

tabla::tabla(char name[20],int i,int pBCampos,int actualBCampos,int pBDatos,int actualBDatos,int nB,DataFile *a,int primerBIndice,int actualBIndice,int tChar,int tamBloque)
{
    archivo=a;
    strncpy(nombre,name,20);
    id=i;
    primerBloqueCampos=pBCampos;
    actualBloqueCampos=actualBCampos;
    primerBloqueDatos=pBDatos;
    actualBloqueDatos=actualBDatos;
    primerBloqueIndice=primerBIndice;
    actualBloqueIndice=actualBIndice;
    nBloque=nB;
    tamChar=tChar;
    sig=0;
    campos= new ListCampos();
    registros= new ListRegistros();
    indice=new Indice(archivo,primerBloqueIndice,primerBloqueDatos,getTamanoHashTable(tamBloque));
    contRegistros=0;
    eliminado=1; // 0 para indicar que ha sido eliminado
}


char * tabla::toChar()
{
    char * data= new char[64];
    int pos=0;
    memcpy(&data[pos],nombre,20);
    pos+=20;
    memcpy(&data[pos],&id,4);
    pos+=4;
    memcpy(&data[pos],&primerBloqueCampos,4);
    pos+=4;
    memcpy(&data[pos],&actualBloqueCampos,4);
    pos+=4;
    memcpy(&data[pos],&primerBloqueDatos,4);
    pos+=4;
    memcpy(&data[pos],&actualBloqueDatos,4);
    pos+=4;
    memcpy(&data[pos],&primerBloqueIndice,4);
    pos+=4;
    memcpy(&data[pos],&actualBloqueIndice,4);
    pos+=4;
    memcpy(&data[pos],&nBloque,4);
    pos+=4;
    memcpy(&data[pos],&tamChar,4);
    pos+=4;
    memcpy(&data[pos],&contRegistros,4);
    pos+=4;
    memcpy(&data[pos],&eliminado,4);
    pos+=4;
    return data;
}

void tabla::charToTabla(char * data,int tamBloque)
{
    int pos=0;
    memcpy(nombre,&data[pos],20);
    pos+=20;
    memcpy(&id,&data[pos],4);
    pos+=4;
    memcpy(&primerBloqueCampos,&data[pos],4);
    pos+=4;
    memcpy(&actualBloqueCampos,&data[pos],4);
    pos+=4;
    memcpy(&primerBloqueDatos,&data[pos],4);
    pos+=4;
    memcpy(&actualBloqueDatos,&data[pos],4);
    pos+=4;
    memcpy(&primerBloqueIndice,&data[pos],4);
    pos+=4;
    memcpy(&actualBloqueIndice,&data[pos],4);
    pos+=4;
    memcpy(&nBloque,&data[pos],4);
    pos+=4;
    memcpy(&tamChar,&data[pos],4);
    pos+=4;
    memcpy(&contRegistros,&data[pos],4);
    pos+=4;
    memcpy(&eliminado,&data[pos],4);
    pos+=4;
    indice=new Indice(archivo,primerBloqueIndice,actualBloqueIndice,getTamanoHashTable(tamBloque));
}

void tabla::crearRegistro(ManejadordeBloques * mbloques,Registro *r) {
    Idx_Entry *entry;

    int longitudRegistro= this->getLongitudRegistros();
    int disponible = mbloques->masterBlock->tamanoBloque - 16; // 16 es la metaData de BloqueRegistro no necesito los 4 de cantidad ya que guardare un registro en un solo bloqueDatos
    int tmp=disponible;
    int cantBloques=1;
    for(;tmp < longitudRegistro;cantBloques++){
        tmp+=disponible;
    }
    int dif=0;
    if(cantBloques > 1){
        int restar= tmp - longitudRegistro;
        dif= disponible - restar;
    }

    cout<<"Cant Bloques para el registro"<< cantBloques<<endl;
    // IDX

    stringstream idd;
    string iden="id";
    idd<<iden<<'_'<<contRegistros;
    string i="id"+ contRegistros;
    char * id=new char[20];
    strcpy(id,idd.str().c_str());
    strncpy(r->idRegistro,id,20);

    char *registro= r->toChar();
    //calculos para escribir
    int posicion=0;
    int longitudAEscribir =0;
    if(cantBloques > 1){
        longitudAEscribir = disponible;
    }
    else
        longitudAEscribir=longitudRegistro;
    char *registroFinal = new char[this->getLongitudRegistros()];
    memcpy(&registroFinal[posicion],registro,longitudAEscribir);

    if (primerBloqueDatos == -1) {

        Bloque *b = mbloques->asignarNueboBloque();
        BloqueRegistro *br = new BloqueRegistro(archivo,b->nBloque,&registroFinal[posicion],mbloques->masterBlock->tamanoBloque);
        int pos= b->nBloque * mbloques->masterBlock->tamanoBloque + mbloques->masterBlock->sizeMasterB + 16;//metaData

        br->longitudRegistro=longitudAEscribir;
        br->escribir();
        posicion+=longitudAEscribir;
        primerBloqueDatos = b->nBloque;
        actualBloqueDatos = b->nBloque;
        //Lo agrego a la Hash table
        entry = new Idx_Entry(id, b->nBloque, pos);
        manejadorBIndice(mbloques);
        indice->insertar(entry, mbloques);

        registros->add(r);

        for(int c=1;c < cantBloques;c++){
            Bloque *b1 = mbloques->asignarNueboBloque();
            BloqueRegistro *br1 = new BloqueRegistro(archivo,b1->nBloque,&registroFinal[posicion],mbloques->masterBlock->tamanoBloque);
            BloqueRegistro * temporal = new BloqueRegistro(archivo,actualBloqueDatos,"",mbloques->masterBlock->tamanoBloque);
            temporal->cargar();
            temporal->siguiente=br1->nBloque;
            temporal->escribir();
            br1->longitudRegistro=longitudAEscribir;
            br1->escribir();
            posicion+=longitudAEscribir;
            if(c+2 == cantBloques)
                longitudAEscribir=dif;
            actualBloqueDatos = b1->nBloque;
            delete b1;
            delete br1;
            delete temporal;
            registros->add(r);

        }
        return;
    }


    //Hacer en adelante
    int actual=actualBloqueDatos;


    int pos= mbloques->masterBlock->sigBloqueDisponible * mbloques->masterBlock->tamanoBloque + mbloques->masterBlock->sizeMasterB + 16;

    entry= new Idx_Entry(id,mbloques->masterBlock->sigBloqueDisponible,pos);
    //Verifico si se pudo agregar a la hashtable
    if(indice->insertar(entry,mbloques))
    {
        cout<<"Entra"<<endl;
        Bloque *b = mbloques->asignarNueboBloque();
        BloqueRegistro *br = new BloqueRegistro(archivo,b->nBloque,&registroFinal[posicion],mbloques->masterBlock->tamanoBloque);

        br->longitudRegistro=longitudAEscribir;
        br->escribir();
        posicion+=longitudAEscribir;
        actualBloqueDatos = b->nBloque;
        cout<<"Agrega"<<endl;
        for(int c=1;c < cantBloques;c++){
            Bloque *b1 = mbloques->asignarNueboBloque();
            BloqueRegistro *br1 = new BloqueRegistro(archivo,b1->nBloque,reinterpret_cast<char *>(registroFinal[posicion]),mbloques->masterBlock->tamanoBloque);
            BloqueRegistro * temporal = new BloqueRegistro(archivo,actualBloqueDatos,id,mbloques->masterBlock->tamanoBloque);
            temporal->cargar();
            temporal->siguiente=br1->nBloque;
            temporal->escribir();
            br1->longitudRegistro=longitudAEscribir;
            br1->escribir();
            posicion+=longitudAEscribir;
            if(c+2 == cantBloques)
                longitudAEscribir=dif;
            delete b1;
            delete br1;
            registros->add(r);
            actualBloqueDatos = b1->nBloque;
        }
        return;
    }
    else
        cout<<"No se pudo agregar el registro debido al id del registro"<<endl;


}

void tabla::crearCampo(ManejadordeBloques * mbloques,char name[20],int tipo)
{
    // Obtengo la longitud dependiendo del tipo de datos, si es 0 es int,si es 1 es double y si es 2 es char;
    int lon=0;
    if(tipo==0)
        lon=4;
    else if(tipo==1)
        lon=8;
    else if(tipo==2)
        lon=tamChar;
    else
        cout<<"Error el tipo de datos que desea ingresar es incorrecto ---- Recuerde que solo puede ingresar 0(int),1(double,2(char)"<<endl;
    cout<<"Longitud del campo "<<lon<<endl;
    campo * c= new campo(name,tipo,lon);
    if(primerBloqueCampos==-1)
    {
        Bloque * b =mbloques->asignarNueboBloque();
        BloqueCampo * bc= new BloqueCampo(archivo,b->nBloque,mbloques->masterBlock->tamanoBloque);
        bc->campos->add(c);
        bc->cantidad++;
        bc->escribir();
        campos->add(c);
        primerBloqueCampos=bc->nBloque;
        actualBloqueCampos=bc->nBloque;


        //Tengo que guardar la tabla en el archivo o por lo menos el bloqueTabla
        return;
    }
    int actual=primerBloqueCampos;
    while(actual!=-1)
    {
        BloqueCampo *bc = new BloqueCampo(archivo,actual,mbloques->masterBlock->tamanoBloque);
        bc->cargar();
        int maximo=17;
        if(bc->cantidad<maximo)
        {
            bc->campos->add(c);
            bc->cantidad++;
            bc->escribir();
            campos->add(c);
            return;
            //Tenqo que guardar la tabla o por lo menos el bloqueTabla como tal
        }
        actual=bc->siguiente;

    }
    Bloque *b=mbloques->asignarNueboBloque();
    BloqueCampo * bc = new BloqueCampo(archivo,b->nBloque,mbloques->masterBlock->tamanoBloque);
    BloqueCampo * tmp = new BloqueCampo(archivo,actualBloqueCampos,mbloques->masterBlock->tamanoBloque);
    tmp->cargar();
    tmp->siguiente=bc->nBloque;
    tmp->escribir();
    bc->campos->add(c);
    bc->cantidad++;
    bc->escribir();
    actualBloqueCampos=bc->nBloque;
    //Tengo que guardar la tabla o el Bloque Tabla
}

void tabla::cargarCampos(int tamBloques)
{
    int actual=primerBloqueCampos;
    while(actual!=-1)
    {
        BloqueCampo *bc= new BloqueCampo(archivo,actual,tamBloques);
        bc->cargar();
        for(int c=0;c<bc->cantidad;c++)
        {
            campos->add(bc->campos->get(c));
        }
        actual=bc->siguiente;
    }
}

void tabla::cargarRegistros(ManejadordeBloques * mbloques)
{
    int actual=primerBloqueDatos;
    int longitudRegistro = this->getLongitudRegistros();
    int disponible = mbloques->masterBlock->tamanoBloque - 16; // 16 es la metaData de BloqueRegistro no necesito los 4 de cantidad ya que guardare un registro en un solo bloqueDatos
    int tmp=disponible;
    int cantBloques=1;
    for(;tmp < longitudRegistro;cantBloques++){
        tmp+=disponible;
    }


    for(int c=0;c<contRegistros;c++){
        // debo cargar un solo registro de uno o varios bloques
        char * r= new char[longitudRegistro];
        int pos=0;
        for(int x=0;x<cantBloques;x++){
            BloqueRegistro *br= new BloqueRegistro(archivo,actual,"",mbloques->masterBlock->tamanoBloque);
            br->cargar();
            memcpy(&r[pos],br->registro,br->longitudRegistro);
            pos+=br->longitudRegistro;
            actual=br->siguiente;
            delete br;
        }
        registros->add(interpretarRegistro(r,longitudRegistro));
    }
}

Registro * tabla::interpretarRegistro(char * data,int longitud)
{
    int pos=0;
    Registro * reg= new Registro(longitud);// debo de cambiar el valor del id en registro donde esta 0
    for(int c=0;c<campos->cantidad;c++)
    {
        campo * defCampo= campos->get(c);
        CampoDatos * campDatos= new CampoDatos("",defCampo);

        campDatos->defCampos=defCampo;
        memcpy(campDatos->valor,&data[pos],defCampo->longitud);
        //campDatos->valor=&data[pos];
        //memcpy(campDatos->valor,&data[pos],defCampo->longitud);
        pos+=defCampo->longitud;
        reg->campoDatos->add(campDatos);
    }
    return reg;
}

int tabla::getLongitudRegistros()
{
    int sum=0;
    for(int c=0;c<campos->cantidad;c++)
    {
        sum+=campos->get(c)->longitud;
    }
    return sum+20;// +20 del id registro

}

void tabla::toString()
{
    cout<<"Nombre: "<<nombre<<"  ID: "<<id<<"  PrimerBloqueCampo: "<<primerBloqueCampos<<"  ActualBloqueCampo: "<<actualBloqueCampos<<"  PrimerBloqueDatos: "<<primerBloqueDatos<<"  ActualBloqueDatos: "<<actualBloqueDatos<<"  Numero de Bloque: "<<nBloque<<" pbloqueindice "<<primerBloqueIndice<<" actualbloqueindice"<<actualBloqueIndice<<" Tamano Char "<<tamChar<<endl<<endl;
}

void tabla::printTabla()
{
    cout<<"Nombre de la Tabla: "<<nombre<<endl;
    for(int c=0;c<campos->cantidad;c++)
    {
        cout<<" "<<campos->get(c)->nombre<<"    ";
    }
    cout<<endl;
    for(int c=0;c<registros->cantidad;c++)
    {
        Registro * r= registros->get(c);
        for(int x=0;x<r->campoDatos->cantidad;x++)
        {
            CampoDatos * camDatos=r->campoDatos->get(x);
            //camDatos->printValor();
            if(camDatos->defCampos->tipo==1)
            {
                cout<<"   ";
            }
            cout<<" "<<camDatos->valor;
            cout<<"     ";
             if(camDatos->defCampos->tipo==1)
            {
                cout<<"   ";
            }

        }
        cout<<endl;
    }
}

int tabla::getTamanoHashTable(int t) {
    int sum=0;
    int actual=primerBloqueIndice;
    while(actual!=-1)
    {
        BloqueIndice * bloque= new BloqueIndice(archivo,actual,t);
        bloque->cargar();
        sum+=62;
        actual=bloque->siguiente;
        delete bloque;
    }
    return sum;
}

Registro * tabla::buscarRegistro(char *id, ManejadordeBloques * mbloques) {
    Idx_Entry * entry = indice->buscar(id,mbloques);
    if(entry==0){
        cout<<"No se encontro el id"<<endl;
        return 0;
    }

    //calculos

    int longitudRegistro = this->getLongitudRegistros();
    int disponible = mbloques->masterBlock->tamanoBloque - 16; // 16 es la metaData de BloqueRegistro no necesito los 4 de cantidad ya que guardare un registro en un solo bloqueDatos
    int tmp=disponible;
    int cantBloques=1;
    for(;tmp < longitudRegistro;cantBloques++){
        tmp+=disponible;
    }
    Registro * registro;
    char * r = new char[longitudRegistro];
    int pos=0;
    for(int c=0;c<cantBloques;c++){
        BloqueRegistro * bloque= new BloqueRegistro(archivo,entry->numeroBloque,"",mbloques->masterBlock->tamanoBloque);
        bloque->cargar();
        memcpy(&r[pos],bloque->registro,bloque->longitudRegistro);
        cout<<"long registro"<<bloque->longitudRegistro<<endl;
        pos+=bloque->longitudRegistro;
        delete bloque;
    }
    registro= new Registro(longitudRegistro);
    registro=interpretarRegistro(r,longitudRegistro);

    for(int c=0;c<campos->cantidad;c++)
    {
        campo * defCampo = campos->get(c);
        registro->campoDatos->get(c)->defCampos=defCampo;
    }
    return registro;
}

void tabla::manejadorBIndice(ManejadordeBloques * mB)
{
    int n= mB->asignarNueboBloque()->nBloque;
    BloqueIndice * bi = new BloqueIndice(archivo,n,mB->masterBlock->tamanoBloque);
    bi->escribir();
    if(primerBloqueIndice==-1)
        primerBloqueIndice=n;
    this->actualBloqueIndice=n;
    indice->actualizarIndice(primerBloqueIndice,actualBloqueIndice,getTamanoHashTable(mB->masterBlock->tamanoBloque));
}

