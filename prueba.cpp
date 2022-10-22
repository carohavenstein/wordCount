#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string.h>
using namespace std;

/*
int main(){
ifstream archivoEntrada;
ofstream archivoSalida;
int contLinea = 0;
string linea;
string texto;

archivoEntrada.open("Prueba.txt");

if(archivoEntrada.fail()){
    cout << "Error al abrir el archivo." << endl;
    exit(1);
}
archivoSalida.open("salida.txt",ios::in);

while(getline(archivoEntrada,linea)){
    texto = texto + linea+"\n";
    contLinea++;

}
archivoSalida << texto << endl;

cout<<"\nCantidad de lineas: "<<contLinea<<endl;

archivoSalida.close();
archivoEntrada.close();
return 0;


}
*/

int main(){
ifstream archivoEntrada;
ofstream archivoSalida;
int contLinea = 0;
string linea;
string texto;

archivoEntrada.open("C:\\Users\\HP\\Desktop\\Universidad\\2° Año - Ing. de Sistemas\\Programacion III\\Parcial 2\\wordCount\\ArchivoTxt\\Prueba.txt",ios::in);
    if(archivoEntrada.fail()){
        cout << "Error al abrir el archivo." << endl;
        exit(1);
    }
//archivoSalida.open("salida.txt");

while(getline(archivoEntrada,linea)){
    cout<<"L"<<contLinea<<"= "<<linea<<endl;
    contLinea++;
}
cout<< "El numero de lineas que tiene el archivo es de: " <<contLinea <<endl;
//archivoSalida << texto << endl;

//archivoSalida.close();
archivoEntrada.close();
return 0;
}