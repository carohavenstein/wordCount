#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
#include <sstream>
#include <unordered_map>
#include "HashMamp.h"
using namespace std;


/*
funcion:
cuenta cantidad de letras, palabras y lineas del file.txt
cuenta cantidad de palabras diferentes
*/
void funcionesBasicas(string fileName) {
            
    int contLineas = 0;
    int contPalabras = 0;
    int contLetras = 0;
    int contPalabrasDif = 0;
    string linea;

    ifstream archivo;
    //abrimos el archivo en modo lectura 
    archivo.open(fileName,ios::in);
        
    if (archivo.fail()) {
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }

    while(!archivo.eof()) { //mietras no sea el final del archivo
        
        getline(archivo,linea);
        contLineas++;

        string palabra = "";

        for (int i = 0; i < linea.length()+1; i++){

            if (isalpha(linea[i])){
                contLetras += 1;
                palabra += linea[i];
            } else {
                if (palabra != "") {
                    //meterla en el hash map que vaya contando palbras DIF !!!!!!!!!!!!!!
                    contPalabras++;
                }
                palabra = "";
            }
        }

    }

    //contPalabrasDif = cantpalabrasdif del hashmap
    
    cout<<"\nNumero de LINEAS: " <<contLineas<<endl;
    cout<<"\nNumero de PALABRAS: " <<contPalabras<<endl;
    cout<<"\nNumero de LETRAS: " <<contLetras<<endl;
    //cout<<"\nPalabras diferentes: " <<contPalabrasDif<<endl;

    archivo.close(); //cerramos el archivo

}

/*
funcion que lee archivo.txt
mete palabra por palabra en hashmap
recibe un archivo .txt
devuelve hashmap
*/
HashMap<string, int> leerArchivo(string fileName) {

    string linea;
    ifstream archivo;
    //abrimos el archivo en modo lectura 
    archivo.open(fileName,ios::in);
        
    if (archivo.fail()) {
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }

    while(!archivo.eof()) { //mietras no sea el final del archivo
        
        getline(archivo,linea);

        string palabra = "";

        for (int i = 0; i < linea.length()+1; i++){

            if (isalpha(linea[i])){
                palabra += linea[i];
            } else {
                if (palabra != "") {
                    //meterla en el hash map que vaya contando palbras DIF !!!!!!!!!!!!!!
                }
                palabra = "";
            }
        }

    }

    archivo.close(); //cerramos el archi            
}



void funcionExcluir(string palabrasArgv) {
    
    //trasnformo argv de palabras a excluir en stringstream: son las palabras a excluir separadas por ,
    stringstream palabrasExcluir(palabrasArgv);
    string aExcluir;

    while (getline(palabrasExcluir, aExcluir, ',')) {
        //cout<<"palabra a excluir: "<<aExcluir<<endl;
        //aEliminar.remove()
        //va eliminando las palabras del hashmap
        //para que despues comandos palabras y ocurrencias no las muestren
    }
    
}

//deberia devolver el hasmap
void funcionExcluirF(string palabrasArgv){
    ifstream archivo;
    //abrimos el archivo en modo lectura 
    archivo.open(palabrasArgv,ios::in);
        
    if (archivo.fail()) {
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }

    string linea;

    while(!archivo.eof()) { //mietras no sea el final del archivo
        
        getline(archivo,linea);
        cout << linea << endl;

        string palabra = "";

        for (int i = 0; i < linea.length()+1; i++){

            if (isalpha(linea[i])){
                palabra += linea[i];
            } else {
                if (palabra != "") {
                    //cout << "palabra a excluir del file ign.txt: " << palabra << endl;
                    //eliminarla del hashmap
                }
                palabra = "";
            }
        }

    }
}

void funcionMostrar(string palabrasArgv){

    //trasnformo argv de palabras a mostrar en stringstream: son las palabras a mostrar separadas por ,
    stringstream palabrasMostrar(palabrasArgv);
    string aMostrar;
    int size = 0;
    while (getline(palabrasMostrar, aMostrar, ',')) {
        size ++;
        //aMostrar.search() la busco en el hashmap
        //que vaya guardando las palabras a mostrar en algun lado, PROBLEMA: como se tamaño del arreglo donde las guardo?
        //despues hay que ordenalas por ocurrencia (con quicksort?) y mostrarlas
    }

}

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

unordered_map<string, Argumento> parseArgumentos(int argc, char* argv[]) {

    unordered_map<string, Argumento> argumentos;

    for (int i = 0; i < argc; i++) {

        string arg(argv[i]); //convierto puntero a caracter en string para comparar los contenidos

        if (arg == "-palabras") {
            
            int cantMostrar = 0;
            //si el primer caracter del siguiente argv es un numero
            //y que exista el siguiente argv, porque puede no haber
            if ((i+1 < argc) && isdigit(argv[i+1][0])) {
                string argumentoSig(argv[i+1]);
                i++;
                cantMostrar = stoi(argumentoSig); //string to int
            }

            Argumento arg;
            arg.id = ArgType::Palabras;
            arg.n = cantMostrar;
            argumentos["-palabras"] = arg;
            
        } else if (arg == "-ocurrencias") {

            int cantMostrar = 0;
            //si el primer caracter del siguiente argv es un numero
            //y que exista el siguiente argv, porque puede no haber
            if ((i+1 < argc) && isdigit(argv[i+1][0])) {
                string argumentoSig(argv[i+1]);
                i++;
                cantMostrar = stoi(argumentoSig); //string to int
            }

            Argumento arg;
            arg.id = ArgType::Ocurrencias;
            arg.n = cantMostrar;
            argumentos["-ocurrencias"] = arg;
            i++;

        } else if (arg == "-mostrar") { //-mostrar "palabra, palabra" segun ocurrencia creciente

            Argumento arg;
            arg.id = ArgType::Mostrar;
            arg.palabrasArgv = string(argv[i+1]); //transformo el siguiente argv en string (palabras a mostrar)
            argumentos["-mostrar"] = arg;
            i++;

        } else if (arg == "-excluir") { //-excluir "palabra, palabra"

            Argumento arg;
            arg.id = ArgType::Excluir;
            arg.palabrasArgv = string(argv[i+1]); //transformo el siguiente argv en string (palabras a excluir)
            argumentos["-excluir"] = arg;
            i++;
           
        } else if (arg == "-excluirF") { //el siguiente arg es un ign.txt
            Argumento arg;
            arg.id = ArgType::ExcluirF;
            //guarda nombre del archivo a ignorar en palabrasArgv
            arg.palabrasArgv = string(argv[i+1]); //transformo el siguiente argv en string (.txt a ignorar)
            argumentos["-excluirF"] = arg;
            i++;

        } else {
            Argumento arg;
            arg.id = ArgType::Archivo;
            arg.palabrasArgv = string(argv[i]); //transformo el argv en string (.txt)
            argumentos["archivo"] = arg;
        }
    }

    return argumentos;
}

unsigned int hashFunc(string clave){
    
    int hash;

    for(int i = 0; i < clave.length(); i++) {
        hash += clave[i];
    }
    hash += clave[0];
    hash = hash % 4000;
    return hash;
}

void ejecutarArgumentos(unordered_map<string, Argumento> args) {
    Argumento palabras = args["-palabras"];
    Argumento ocurrencias = args["-ocurrrencias"];
    Argumento mostrar = args["-mostrar"];
    Argumento excluir = args["-excluir"];
    Argumento excluirF = args["-excluirF"];
    Argumento file = args["archivo"];


    HashMap<string, int> tablaPalabras(4000, hashFunc);
    string fileName = file.palabrasArgv;

    tablaPalabras = leerArchivo(fileName);

    if (excluir.id == ArgType::Excluir) {
        //que leerArchivo devuelva el hashmap
        leerArchivo(file.palabrasArgv);

        funcionExcluir(excluir.palabrasArgv);

    }

    if (excluirF.id == ArgType::ExcluirF) {
        funcionExcluirF(excluirF.palabrasArgv);

    }

    if (palabras.id == ArgType::Palabras) {
        //para controlar si existe arg palabras, si no existe argType es nulo - PARA TODOS IGUAL
        if(palabras.n == 0) {
            //ordenar todo el hashmap alfabeticamente y mostrarlo
        } else {
            //ordenar todo el hashmap alfabeticamente y mostrar las primeras n
        }

    }

    if (ocurrencias.id == ArgType::Ocurrencias) {
        if(ocurrencias.n == 0) {
            //ordenar todo el hashmap por ocurrencia creciente y mostrarlo
        } else {
            //ordenar todo el hashmap por ocurrencia creciente y mostrar las primeras n
        }
    }

    if (mostrar.id == ArgType::Mostrar) {

        funcionMostrar(mostrar.palabrasArgv);
    }
}



int main(int argc, char** argv) {

    clock_t begin;
    cout << "Comenzando a medir Tiempo\n" << endl;
    begin = clock();

    auto argumentos = parseArgumentos(argc, argv);
    Argumento file = argumentos["archivo"];

    //si ademas del ejecutable solo te pasaron como argumento un archivo .txt ->funciones basicas
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