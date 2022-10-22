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
    int contLinea = 1;
    int contPalabra = 0;
    int contLetra = 0;
    int letras;



    archivo.open("Prueba.txt",ios::in); //abrimos el archivo en modo lectura 

    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }

    while(!archivo.eof()){ //mietras no sea el final del archivo
        getline(archivo,texto);
        cout<<"\n\n";
        cout<<texto<<endl;
        cout<<"\n\n";

        for (int i = 0; i < texto.length(); i++){
        if ((texto[i] >= 'a' && texto[i] <= 'z') || (texto[i] >= 'A' && texto[i] <= 'Z')){
            letras += 1;
            }
        }

        while(getline(archivo,linea)){  //Contador de lineas (n - 1 lineas)
          cout<<"L"<<contLinea<<" = "<<linea<<endl;
          contLinea++;
        }
        
        

        while(getline(archivo,palabra)){  //Contador de palabras
        

            for(int i=1; palabra[i]!='\0'; ++i)   
               if(palabra[i-1]==' '&& isalpha(palabra[i])){
                 contPalabra++;
                }
                  
                if(isalpha(palabra[0])) {
                  contPalabra++;
                }
        }

        //Contador de letras

    }
    cout<<"\nNumero de lineas que tiene el archivo es de : " <<contLinea <<endl;
    cout<<"\nNumero de palabras que tiene el archivo es de : " <<contPalabra <<endl;
    cout<<"\nNumero de letras que tiene el archivo es de : " << letras <<endl;




    archivo.close(); //cerramos el archivo
}