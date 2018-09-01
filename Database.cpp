//
// Created by David Diaz on 31/08/2018.
//

#include "Database.h"


Database::Database(string name) {
    string a="C:\\Users\\USUARIO\\Desktop\\BaseDatos\\";
    string b=".data";
    string p= a+name+b;
    string nomb= name+b;
    dataName = new char[nomb.length()];
    path= new char[p.length()];
    strcpy(dataName,nomb.c_str());
    strcpy(path,p.c_str());
    archivo = new DataFile(path);
    iniciarConexion();
}

bool Database::dropDatabase() {
    cerrarConexion();
    if( remove( path)!=0 ){
        cout<<"Error al removerlo: "<<strerror(errno)<<endl;
    }else{
        cout<<"Archivo removido"<<endl;
    }
}

void Database::cerrarConexion() {
    archivo->cerrar();
}

void Database::iniciarConexion() {
    archivo->abrir();
    mBloques= new ManejadordeBloques(archivo);
    mTablas=new ManejadroTablas(archivo,mBloques->masterBlock);
}