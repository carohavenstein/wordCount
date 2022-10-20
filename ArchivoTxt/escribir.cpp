#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

//ESCRIBIR en un archivo de texto

void escribir();


int main(){

    escribir();
    
    return 0;
}


void escribir(){

    ofstream archivo;
    string nombreArchivo,frase;

    cout<<"Digite el nombre del archivo: ";
    getline(cin,nombreArchivo);

    archivo.open(nombreArchivo.c_str(),ios::out); //abriendo el archivo

    if(archivo.fail()){
        cout<<"No se puedo abrir el archivo";
        exit(1);
    }

    cout<<"\nIngrese el texto del archivo: ";
    getline(cin,frase);

    archivo<<frase;

    archivo.close(); //cerrar el archivo
}