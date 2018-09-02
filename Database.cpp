//
// Created by David Diaz on 31/08/2018.
//

#include "Database.h"


Database::Database(string name,int tBloque) {
    string a="C:\\Users\\USUARIO\\Desktop\\BaseDatos\\";
    string b=".data";
    string p= a+name+b;
    string nomb= name+b;
    dataName = new char[nomb.length()];
    path= new char[p.length()];
    strcpy(dataName,nomb.c_str());
    strcpy(path,p.c_str());
    archivo = new DataFile(path);
    iniciarConexion(tBloque);
}

bool Database::dropDatabase() {
    cerrarConexion();
    if( remove( path)!=0 ){
        cout<<"Error al removerlo: "<<strerror(errno)<<endl;
    }else{
        cout<<"Base de Datos con el nombre "<< dataName<<" removido con exito"<<endl;
    }
}

void Database::cerrarConexion() {
    archivo->cerrar();
}

void Database::iniciarConexion(int t) {
    archivo->abrir();
    mBloques= new ManejadordeBloques(archivo,t);
    mTablas=new ManejadroTablas(archivo,mBloques->masterBlock);
}

void Database::createDataBase(int tamano,string tipo)
{
    //Defino los tamaños
    int GB=1073741824;//El tamaño de 1 GB en Bytes
    int MB=1048576;//El tamaño de 1 MB en Bytes
    if(tipo=="GB"){
        cout<<"Entra al GB"<<endl;
        for(int c=0;c<tamano;c++){
            mBloques->createDataBase(GB,mBloques->masterBlock->ultimoBloque);
        }
        cout<<"Termina el de GB"<<endl;
    }

    else if(tipo=="MB") {
        cout << "Entra al MB" << endl;
        for (int c = 0; c < tamano; c++) {
            mBloques->createDataBase(MB, mBloques->masterBlock->ultimoBloque);

        }
        cout<<"Termina el de MB"<<endl;
    }
    else{
        cout<<"No se creo la base de datos"<<endl;
        cout<<"Error tipo de datos incorrecto, recuerde que solo puede ser(GB o MB"<<endl;
        return;
    }
    cout<<"Se creo la base de datos exitosamente"<<endl;
}