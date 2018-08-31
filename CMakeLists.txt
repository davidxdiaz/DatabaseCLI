cmake_minimum_required(VERSION 3.7)
project(ProyectoED2_master)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        bloque.cpp
        bloque.h
        bloquecampo.cpp
        bloquecampo.h
        BloqueIndice.cpp
        BloqueIndice.h
        BloqueLlave.cpp
        BloqueLlave.h
        bloqueregistro.cpp
        bloqueregistro.h
        bloquetabla.cpp
        bloquetabla.h
        campo.cpp
        campo.h
        campodatos.cpp
        campodatos.h
        datafile.cpp
        datafile.h
        HashTableEntry.cpp
        HashTableEntry.h
        Idx_Entry.cpp
        Idx_Entry.h
        Indice.cpp
        Indice.h
        json.hpp
        listbloquetablas.cpp
        listbloquetablas.h
        listcampodatos.cpp
        listcampodatos.h
        listcampos.cpp
        listcampos.h
        listregistros.cpp
        listregistros.h
        listtabla.cpp
        listtabla.h
        main.cpp
        manejadordebloques.cpp
        manejadordebloques.h
        manejadorjson.cpp
        manejadorjson.h
        manejadrotablas.cpp
        manejadrotablas.h
        masterblock.cpp
        masterblock.h
        registro.cpp
        registro.h
        tabla.cpp
        tabla.h)

add_executable(ProyectoED2_master ${SOURCE_FILES})