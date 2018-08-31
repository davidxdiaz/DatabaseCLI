#ifndef MANEJADORJSON_H
#define MANEJADORJSON_H
#include <iostream>
#include "json.hpp"

using json=nlohmann::json;
using namespace std;

class ManejadorJson
{
    public:
        ManejadorJson();
        json j;
        void guardar();
        void cargar();

};

#endif // MANEJADORJSON_H
