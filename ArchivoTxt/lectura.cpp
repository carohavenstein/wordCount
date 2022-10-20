#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
using namespace std;

//LECTURA DE .txt

void lectura();

int main(){

    lectura();

    return 0;
}

void lectura(){

    ifstream archivo;
    string texto;
    string linea;
    int contLinea = 0;

    archivo.open("hola.txt",ios::in); //abrimos el archivo en modo lectura 

    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }

    while(!archivo.eof()){ //mietras no sea el final del archivo
        getline(archivo,texto);
        cout<<"\n\n";
        cout<<texto<<endl;
        cout<<"\n\n";
    }

    while(getline(archivo,linea)){
        texto = texto + linea+"\n";
        contLinea++;
    }

    cout<<"\nCantidad de lineas: "<<contLinea<<endl;


    archivo.close(); //cerramos el archivo
}

