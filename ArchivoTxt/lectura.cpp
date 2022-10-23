#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
using namespace std;

//LECTURA DE .txt

void lectura();

int main() {
    clock_t begin;

    cout << "Comenzando a medir Tiempo\n" << endl;

    begin = clock();
    /*
     * Insertar código a medir tiempo aquí
     */

    lectura();

    
    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs" << elapsed_secs << "\n" << std::endl;

    return 0;

}


void lectura(){

    ifstream archivo;
    string linea;
    string palabra;
    int contLinea = 0;
    int contPalabra = 0;
    int contLetras = 0;

    archivo.open("Prueba.txt",ios::in); //abrimos el archivo en modo lectura 

    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }

    while(!archivo.eof()){ //mietras no sea el final del archivo
        getline(archivo,linea);
        contLinea++;
        cout<<linea<<endl;

        //Contador Letras
        for (int i = 0; i < linea.length(); i++){
        if (isalpha(linea[i])){
            contLetras += 1;
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

    cout<<"\nNumero de LINEAS que tiene el archivo es de: " <<contLinea<<endl;
    cout<<"\nNumero de PALABRAS que tiene el archivo es de: " <<contPalabra<<endl;
    cout<<"\nNumero de LETRAS que tiene el archivo es de: " <<contLetras<<endl;

    archivo.close(); //cerramos el archivo
}