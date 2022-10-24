#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
#include <sstream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
funcion:
construye el arbol
cuenta cantidad de letras palabras y lineas del .txt
devuelve el arbol de palabras diferentes
*/
//Arbol<string>
void construirArbol(ifstream& archivo, int& contLineas, int& contPalabras, int& contLetras) {
            
    string linea;

    while(!archivo.eof()) { //mietras no sea el final del archivo
        
        getline(archivo,linea);
        contLineas++;
        //cout<<linea<<endl;
        //Contador Letras

        string palabra = "";

        for (int i = 0; i < linea.length()+1; i++){
            // cout << linea[i]  << " ";
            if (isalpha(linea[i])){
                contLetras += 1;
                palabra += linea[i];
            } else {
                if (palabra != "") {
                    //arbolPalabrasDif.put(palabra); !!!!!!!!!!!!!!
                    // cout << palabra << endl;
                    contPalabras++;
                }
                palabra = "";
            }
        }

    }

    //return arbolPalabrasDif;

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
    string palabras;
};

unordered_map<string, Argumento> parseArgumentos(int argc, char* argv[]) {
    unordered_map<string, Argumento> argumentos;
    for (int i = 0; i < argc; i++) {

        string arg(argv[i]); //convierto puntero a caracter en string para comparar los contenidos

        if (arg == "-excluir") { //-excluir "palabra, palabra"
            //eliminar esas palabras del arbol
            stringstream palabrasExcluir(argv[i+1]); //trasnformo arg siguiente en stringstream: son las palabras a excluir separadas por ,
            string aExcluir;
            while (getline(palabrasExcluir, aExcluir, ',')) {
                //aEliminar.remove()
                // va eliminando las palabras del arbol ordenado alfbtcmt
                //para que despues comandos palabras y ocurrencias no las muestren
            }

        } else if (arg == "-palabras") {
            
            int cantMostrar = 0;
            if (isdigit(argv[i+1][0])) { //si el primer caracter del siguiente argv es un numero
                string argumentoSig(argv[i+1]);
                i++;
                cantMostrar = stoi(argumentoSig); //string to int
            }

            Argumento arg;
            arg.id = ArgType::Palabras;
            arg.n = cantMostrar;
            argumentos["palabras"] = arg;
           
            if(cantMostrar == 0) {
                //imprimir todo el arbol en orden alfabetico
            } else {
                //imprimir el arbol en orden alfabetico de las n primeras palabras
            }
            
        } else if (arg == "-ocurrencias") {

            int cantMostrar = 0;
            if (isdigit(argv[i+1][0])) { //si el primer caracter del siguiente argv es un numero
                string argumentoSig(argv[i+1]);
                i++;
                cantMostrar = stoi(argumentoSig); //string to int
            }
           
            if(cantMostrar == 0) {
                //mostrar todas las palabras ordenadas segun ocurrencia creciente
            } else {
                //mostrar n palabras segun ocurrencia creciente
            }

        } else if (arg == "-mostrar") { // -mostrar "palabra, palabra" segun ocurrencia creciente

            stringstream palabrasMostrar(argv[i+1]); //trasnformo arg siguiente en stringstream: son las palabras a mostrar separadas por ,
            string aMostrar;
            while (getline(palabrasMostrar, aMostrar, ',')) {
                //aMostrar.search() la busco en el arbol ordenado alfbtcmt, para obtener la palabra con las ocurrencias?
                //que vaya guardando las palabras a mostrar en algun lado
                //despues hay que ordenalas por ocurrencia (con quicksort?) y mostrarlas
            }
        }
    }

    return argumentos;
}

void EjecutarArgumentos(unordered_map<string, Argumento> args) {
    Argumento palabras = args["palabras"];
    if (palabras.id == ArgType::Palabras) {
        // mostrarPalabras(palabras.n);
    }
}

int main(int argc, char** argv) {

    clock_t begin;
    cout << "Comenzando a medir Tiempo\n" << endl;
    begin = clock();


    int contLineas = 0;
    int contPalabras = 0;
    int contLetras = 0;
    
    //Arbol arbolPalabrasDif;

    ifstream archivo;
    archivo.open(argv[1],ios::in); //abrimos el archivo en modo lectura 

    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }

    
    //arbolPalabrasDif = construirArbol(archivo, contLineas, contPalabras, contLetras);
    construirArbol(archivo, contLineas, contPalabras, contLetras);

    cout<<"\nNumero de LINEAS que tiene el archivo es de: " <<contLineas<<endl;
    cout<<"\nNumero de PALABRAS que tiene el archivo es de: " <<contPalabras<<endl;
    cout<<"\nNumero de LETRAS que tiene el archivo es de: " <<contLetras<<endl;

    archivo.close(); //cerramos el archivo

    auto argumentos = parseArgumentos(argc, argv);
    EjecutarArgumentos(argumentos);    

    clock_t end = clock();
    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    cout << "Tardo elapsed_secs" << elapsed_secs << "\n" << std::endl;

    return 0;
}