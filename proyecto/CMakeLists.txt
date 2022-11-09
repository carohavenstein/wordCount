cmake_minimum_required(VERSION 3.23)
project(proyecto)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(proyecto
        evaluar.txt
        file.txt
        funciones.cpp
        funciones.h
        HashMapList.h
        ign.txt
        Lista.h
        main.cpp
        Nodo.h)
