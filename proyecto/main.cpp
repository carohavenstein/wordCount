#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
#include <sstream>
#include <unordered_map>
using namespace std;

/*
funcion:
cuenta cantidad de letras palabras y lineas del file.txt
cuenta cantidad de palabras diferentes
*/
void funcionesBasicas(ifstream& archivo, int& contLineas, int& contPalabras, int& contLetras, int& contPalabrasDif) {
            
    string linea;

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
                    //meterla en el hash map; !!!!!!!!!!!!!!
                    contPalabras++;
                }
                palabra = "";
            }
        }

    }

    //contPalabrasDif = cantpalabrasdif del hashmap

}


//deberia devolver el hashmap
void funcionExcluir(string palabrasArgv) {
    
    //trasnformo argv de palabras a expluir en stringstream: son las palabras a excluir separadas por ,
    stringstream palabrasExcluir(palabrasArgv);
    string aExcluir;

    while (getline(palabrasExcluir, aExcluir, ',')) {
        cout<<"palabra a excluir: "<<aExcluir<<endl;
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

        string palabra = "";

        for (int i = 0; i < linea.length()+1; i++){

            if (isalpha(linea[i])){
                palabra += linea[i];
            } else {
                if (palabra != "") {
                    cout << "palabra a excluir del file ign.txt: " << palabra << endl;
                    //eliminarla del hashmap
                }
                palabra = "";
            }
        }

    }
}

void funcionMostrar(string palabrasArgv){

    //trasnformo argv de palabras a expluir en stringstream: son las palabras a excluir separadas por ,
    stringstream palabrasMostrar(palabrasArgv);
    string aMostrar;
    int size = 0;
    while (getline(palabrasMostrar, aMostrar, ',')) {
        size ++;
        //aMostrar.search() la busco en el hashmap
        //que vaya guardando las palabras a mostrar en algun lado
        //despues hay que ordenalas por ocurrencia (con quicksort?) y mostrarlas
    }

}

enum class ArgType {
    Nulo = 0,
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
            arg.palabrasArgv = string(argv[i+1]);
            argumentos["-excluir"] = arg;
            i++;
        }
    }

    return argumentos;
}

void ejecutarArgumentos(unordered_map<string, Argumento> args) { //pasarle el hashmap de palabras

    Argumento palabras = args["-palabras"];
    Argumento ocurrencias = args["-ocurrrencias"];
    Argumento mostrar = args["-mostrar"];
    Argumento excluir = args["-excluir"];
    Argumento excluirF = args["-excluirF"];

    if (excluir.id == ArgType::Excluir) {
        //reciba el hashmap, y el string de palabras a ignorar y las elimine del hashmap
        //que devuelva el hashmap, mapaPalabras = mapa devuelto.
        funcionExcluir(excluir.palabrasArgv);

    }

    if (excluirF.id == ArgType::ExcluirF) {
        funcionExcluirF(excluirF.palabrasArgv);
        
    }

    if (palabras.id == ArgType::Palabras) {
        //para controlar si existe arg palabras, si no existe argType es nulo
        if(palabras.n == 0) {
            //ordenar todo el hashmap alfabeticamente y mostrarlo
        } else {
            //ordenar todo el hashmap alfabeticamente y mostrar las primeras n
        }

    }

    if (ocurrencias.id == ArgType::Ocurrencias) {
        
    }

    if (mostrar.id == ArgType::Mostrar) {
        
        if(mostrar.n == 0) {
            //mostrar todas las palabras ordenadas segun ocurrencia creciente
        } else {
            //mostrar n palabras segun ocurrencia creciente
        } 

        funcionMostrar(mostrar.palabrasArgv);
    }
}



int main(int argc, char** argv) {

    clock_t begin;
    cout << "Comenzando a medir Tiempo\n" << endl;
    begin = clock();


    int contLineas = 0;
    int contPalabras = 0;
    int contLetras = 0;
    int contPalabrasDif = 0;

    if (argc == 2 && string(argv[1]) == "file.txt") {
        
        ifstream archivo;
        //abrimos el archivo en modo lectura 
        archivo.open(argv[1],ios::in);
        
        if (archivo.fail()) {
            cout<<"No se pudo abrir el archivo";
            exit(1);
        }

        //Arbol arbolPalabrasDif;
        //arbolPalabrasDif = construirArbol(archivo, contLineas, contPalabras, contLetras);
        funcionesBasicas(archivo, contLineas, contPalabras, contLetras, contPalabrasDif);

        cout<<"\nNumero de LINEAS: " <<contLineas<<endl;
        cout<<"\nNumero de PALABRAS: " <<contPalabras<<endl;
        cout<<"\nNumero de LETRAS: " <<contLetras<<endl;
        //cout<<"\nPalabras diferentes: " <<contPalabrasDif<<endl;
        
        archivo.close(); //cerramos el archivo

    } else {
        //creo el hashmap
        auto argumentos = parseArgumentos(argc, argv);
        ejecutarArgumentos(argumentos);
    }
    

    clock_t end = clock();
    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    cout << "Tardo elapsed_secs: " << elapsed_secs << "\n" << std::endl;

    return 0;
}