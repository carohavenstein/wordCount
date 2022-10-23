#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
#include <sstream>
using namespace std;

class Opciones {};

class MainLoop {
    private:
    int letras = 0;
    int palabras = 0;
    int lineas = 0;
    // Arbol arbol;
    Opciones opciones;

    public:
        MainLoop() {}
        MainLoop(Opciones ops)
            : opciones(ops) {}

        void construirArbol(ifstream& archivo) {
            string linea;

            while(!archivo.eof()) { //mietras no sea el final del archivo
                getline(archivo,linea);
                lineas++;
                //cout<<linea<<endl;
                //Contador Letras
                string palabra2 = "";
                for (int i = 0; i < linea.length()+1; i++){
                    // cout << linea[i]  << " ";
                    if (isalpha(linea[i])){
                        letras += 1;
                        palabra2 += linea[i];
                    } else {
                        if (palabra2 != "") {
                            //arbol.agregar(palabra2); !!!!!!!!!!!!!!
                            // cout << palabra2 << endl;
                            palabras++;
                        }
                        palabra2 = "";
                    }
                }

            }
        }

        void EjecutarOpciones(Opciones opciones);

        int Letras() { return letras; }
        int Palabras() { return palabras; }
        int Lineas() { return lineas; }

};

/*
static const string argumentos[] = {
    "palabras",
    "explotar"
};

*/




void parseArgumentos(int argc, char* argv[]) {

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
}

/*
class Handler {
    string arg;
    Func func;
};

static const Handler handlers[] = {
    {"palabras", HandlePalabras},
}

void HandlePalabras(int argp, char* argv[]) {

}

void parseArgumentos(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        string arg(argv[i]); //convierto puntero a caracter en string para comparar los contenidos
        for (auto& handler : handlers) {
            if (handler.arg == arg) {
                handler.func(i, argv);
            }
        }
    }
}

*/


int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "error" << endl;
        return -1;
    }

    clock_t begin;

    cout << "Comenzando a medir Tiempo\n" << endl;

    begin = clock();

    ifstream archivo;
    archivo.open(argv[1],ios::in); //abrimos el archivo en modo lectura 

    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }

    MainLoop loop;
    loop.construirArbol(archivo);
    //construir arbol ocurrencias tambien;
    loop.EjecutarOpciones(Opciones{});

    cout<<"\nNumero de LINEAS que tiene el archivo es de: " <<loop.Lineas()<<endl;
    cout<<"\nNumero de PALABRAS que tiene el archivo es de: " <<loop.Palabras()<<endl;
    cout<<"\nNumero de LETRAS que tiene el archivo es de: " <<loop.Letras()<<endl;

    archivo.close(); //cerramos el archivo

    
    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs" << elapsed_secs << "\n" << std::endl;

    return 0;

}