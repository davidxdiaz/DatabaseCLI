#include "manejadorjson.h"
#include <fstream>
using namespace std;
ManejadorJson::ManejadorJson()
{
    json h=j;
}

void ManejadorJson::guardar()
{
    ofstream y("C:\\Users\\David\\Desktop\\BaseDatos.json");
    y << j << endl;
}

void ManejadorJson::cargar()
{
    ifstream y("C:\\Users\\David\\Desktop\\BaseDatos.json");
    y >> j;
}

