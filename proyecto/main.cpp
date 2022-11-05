#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <vector>

#include "HashMapList.h"
using namespace std;

unsigned int hashFunc(string clave){
    
    int hashValue;

    for(int i = 0; i < clave.length(); i++) {
        hashValue += clave[i];
    }
    hashValue += clave[0];
    return hashValue;
}
/*
funcion:
cuenta cantidad de letras, palabras y lineas del file.txt
cuenta cantidad de palabras diferentes
*/
void funcionesBasicas(string fileName) {
    
    HashMapList<string, int> tablaPalabras(4000, hashFunc);

    int contLineas = 0;
    int contPalabras = 0;
    int contLetras = 0;
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

        for (int i = 0; i < linea.length()+1; i++) {

            if (isalpha(linea[i])){
                contLetras += 1;
                palabra += tolower(linea[i]);
            } else {
                if (palabra != "") {
                    //meterla en el hash map que vaya contando palabras DIF
                    unsigned int valor = hashFunc(palabra);
                    tablaPalabras.put(palabra);
                    contPalabras++;
                }
                palabra = "";
            }
        }

    }
    
    cout<<"\nNumero de LINEAS: " <<contLineas<<endl;
    cout<<"\nNumero de PALABRAS: " <<contPalabras<<endl;
    cout<<"\nNumero de LETRAS: " <<contLetras<<endl;
    cout<<"\nNumero de PALABRAS DIFERENTES: " <<tablaPalabras.getPalabrasDiferentes()<<endl;

    archivo.close(); //cerramos el archivo

}


/*
funcion que lee archivo.txt
mete palabra por palabra en hashmap
recibe un archivo .txt
devuelve hashmap
*/
HashMapList<string, int>* leerArchivo(string fileName) {

    HashMapList<string, int>* tablaPalabras = new HashMapList<string, int>(4000, hashFunc);

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
                palabra += tolower(linea[i]);
            } else {
                if (palabra != "") {
                    //meterla en el hash map que vaya contando palabras DIF !!!!!!!!!!!!!!
                    unsigned int valor = hashFunc(palabra);
                    tablaPalabras->put(palabra);
                }
                palabra = "";
            }
        }

    }

    archivo.close(); //cerramos el archivo
    return tablaPalabras;          
}


void funcionExcluir(string palabrasArgv, HashMapList<string, int>* map) {
    
    //trasnformo argv de palabras a excluir en stringstream: son las palabras a excluir separadas por ,
    stringstream palabrasExcluir(palabrasArgv);
    string aExcluir;

    while (getline(palabrasExcluir, aExcluir, ',')) {
        //eliminar espacios de la palabra
        aExcluir.erase(remove(aExcluir.begin(), aExcluir.end(), ' '), aExcluir.end());
        map->remove(aExcluir);
        //va eliminando las palabras del hashmap
        //para que despues comandos palabras y ocurrencias no las muestren
    }
    
}

void funcionExcluirF(string palabrasArgv, HashMapList<string, int>* map){
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

        string palabra = "";

        for (int i = 0; i < linea.length()+1; i++){

            if (isalpha(linea[i])){
                palabra += linea[i];
            } else {
                if (palabra != "") {
                    //eliminarla del hashmap
                    map->remove(palabra);
                }
                palabra = "";
            }
        }

    }
}

void funcionMostrar(string palabrasArgv, HashMapList<string, int>* map){
    //trasnformo argv de palabras a mostrar en stringstream: son las palabras a mostrar separadas por ,
    stringstream palabrasMostrar(palabrasArgv);
    string aMostrar;
    vector<HashEntry<string, int>> vectorPalabrasAMostrar;
    while (getline(palabrasMostrar, aMostrar, ',')) {
        //eliminar espacios de la palabra
        aMostrar.erase(remove(aMostrar.begin(), aMostrar.end(), ' '), aMostrar.end());
        //la busco en el hashmap
        HashEntry<string, int> hashEntryEncontrada = map->getHashEntry(aMostrar);
        //si la encontro la guarda en vector
        if (hashEntryEncontrada.clave == aMostrar) {
            vectorPalabrasAMostrar.push_back(hashEntryEncontrada);
        }    
    }

    if (vectorPalabrasAMostrar.size() == 0) {
        cout << "Las palabras a mostrar no estan en el archivo de texto" << endl;
        return;
    }
  
            //para transformar el vector en arreglo
    quickSortOcurrencias((vectorPalabrasAMostrar.data()), 0, (vectorPalabrasAMostrar.size()-1));
    for (int i = 0; i < (vectorPalabrasAMostrar.size()); i++) {
        cout << vectorPalabrasAMostrar[i].clave << " " << vectorPalabrasAMostrar[i].valor << endl;
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


void ejecutarArgumentos(unordered_map<string, Argumento> args) {

    Argumento palabras = args["-palabras"];
    Argumento ocurrencias = args["-ocurrencias"];
    Argumento mostrar = args["-mostrar"];
    Argumento excluir = args["-excluir"];
    Argumento excluirF = args["-excluirF"];
    Argumento file = args["archivo"];

    HashMapList<string, int>* tablaPalabras = nullptr;
    string fileName = file.palabrasArgv;

    tablaPalabras = leerArchivo(fileName);

    if (excluir.id == ArgType::Excluir) {
        funcionExcluir(excluir.palabrasArgv, tablaPalabras);
    }

    if (excluirF.id == ArgType::ExcluirF) {
        funcionExcluirF(excluirF.palabrasArgv, tablaPalabras);
    }

    if (palabras.id == ArgType::Palabras) {
        //para controlar si existe arg palabras, si no existe argType es nulo - PARA TODOS IGUAL
        HashEntry<string, int>* arregloPalabras = tablaPalabras->sortAlfabetico();
        int n;
        if (palabras.n == 0) {
            n = tablaPalabras->getPalabrasDiferentes(); //imprime todo el arreglo
        } else {
            n = palabras.n; //imprime n primeros
        }

        for (int i = 0; i < n; i++) {
            cout << arregloPalabras[i].clave << endl;
        }
    }

    if (ocurrencias.id == ArgType::Ocurrencias) {
        cout << "ocurrencias" <<endl;
        HashEntry<string, int>* arregloPalabras = tablaPalabras->sortOcurrencias();
        int n;
        if (ocurrencias.n == 0) {
            n = tablaPalabras->getPalabrasDiferentes(); //imprime todo el arreglo
        } else {
            n = ocurrencias.n; //imprime n primeros
        }
        
        for (int i = 0; i < n; i++) {
            cout << arregloPalabras[i].clave << " " << arregloPalabras[i].valor << endl;
        }
    }

    if (mostrar.id == ArgType::Mostrar) {
        funcionMostrar(mostrar.palabrasArgv, tablaPalabras);
    }
}



int main(int argc, char** argv) {
    clock_t begin;
    cout << "Comenzando a medir Tiempo\n" << endl;
    begin = clock();

    if (argc == 1) {
        cout << "grave error de usuario" << endl;
        return -1;
    }

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