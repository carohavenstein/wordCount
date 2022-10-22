#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <windows.h>
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
    string palabra;
    string letra;
    int contLinea = 0;
    int contPalabra = 0;
    int contLetra = 0;
    int letras;



    archivo.open("Prueba.txt",ios::in); //abrimos el archivo en modo lectura 

    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }

    while(!archivo.eof()){ //mietras no sea el final del archivo
        getline(archivo,linea);
        contLinea++;
        cout<<linea<<endl;

        //Contador Lineas
        for (int i = 0; i < linea.length(); i++){
        if ((linea[i] >= 'a' && linea[i] <= 'z') || (linea[i] >= 'A' && linea[i] <= 'Z')){
            letras += 1;
            }
        }

        //Contador Palabra
        for(int i=1; linea[i]!='\0'; ++i)   
               if(linea[i-1]==' '&& isalpha(linea[i])){
                 contPalabra++;
                }
                if(isalpha(linea[0])) {
                  contPalabra++;
                }
        }

        //Contador Letras

    cout<<"\nNumero de LINEAS que tiene el archivo es de : " <<contLinea <<endl;
    cout<<"\nNumero de PALABRAS que tiene el archivo es de : " <<contPalabra <<endl;
    cout<<"\nNumero de LETRAS que tiene el archivo es de : " << letras <<endl;


    archivo.close(); //cerramos el archivo
}