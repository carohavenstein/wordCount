#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
using namespace std;


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
archivoSalida.open("salida.txt");

while(getline(archivoEntrada,linea)){
    texto = texto + linea+"\n";
    contLinea++;

}
archivoSalida << texto << endl;

archivoSalida.close();
archivoEntrada.close();
return 0;


}