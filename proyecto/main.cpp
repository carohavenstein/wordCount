#include <iostream>
#include <string>
#include <ctime>
#include "funciones.h"
using namespace std;

int main(int argc, char** argv) {
    clock_t begin;
    cout << "Comenzando a medir Tiempo\n" << endl;
    begin = clock();

    if (argc == 1) {
        cout << "Error: debe pasar archivo de texto" << endl;
        return -1;
    }

    auto argumentos = parseArgumentos(argc, argv);
    Argumento file = argumentos["archivo"];

    //si ademas del ejecutable solo te pasaron como argumento un archivo.txt
    if (argc == 2 && file.id != ArgType::Nulo) {
        string fileName = file.palabrasArgv;
        funcionesBasicas(fileName);
    } else {
        string fileName = file.palabrasArgv;
        ejecutarArgumentos(argumentos);
    }
    
    clock_t end = clock();
    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    cout << "Tardo elapsed_secs: " << elapsed_secs << "\n" << std::endl;

    return 0;
}