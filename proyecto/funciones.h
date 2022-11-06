#pragma once

#include <string>
#include <unordered_map>
#include "HashMapList.h"
using namespace std;


unsigned int hashFunc(string clave);

/*
funcion:
cuenta cantidad de letras, palabras y lineas del file.txt
cuenta cantidad de palabras diferentes
*/
void funcionesBasicas(string fileName);

/*
funcion que lee archivo.txt
mete palabra por palabra en hashmap
recibe un archivo .txt
devuelve hashmap
*/
HashMapList<string, int>* leerArchivo(string fileName);

void funcionExcluir(string palabrasArgv, HashMapList<string, int>* map);

void funcionExcluirF(string palabrasArgv, HashMapList<string, int>* map);

void funcionMostrar(string palabrasArgv, HashMapList<string, int>* map);

enum class ArgType {
    Nulo = 0,
    Archivo,
    Palabras,
    Ocurrencias,
    Mostrar,
    Excluir,
    ExcluirF
};

struct Argumento {
    ArgType id = ArgType::Nulo;
    bool activo;
    int n;
    string palabrasArgv;
};

unordered_map<string, Argumento> parseArgumentos(int argc, char* argv[]);

void ejecutarArgumentos(unordered_map<string, Argumento> args);

void quickSortAlfabetico(HashEntry<string, int> *arr, int inicio, int fin);

void quickSortOcurrencias(HashEntry<string, int> *arr, int inicio, int fin);