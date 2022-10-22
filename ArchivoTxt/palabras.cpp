
#include<iostream>
#include<stdio.h>
#include<stdlib.h>


using namespace std;

int ContarPalabras(char[]);
 
int main (){

     char cadena[200];

     cout<<"Ingrese cadena:\n";
     cin.getline(cadena, 200);
     cout<<"\nLa cadena de texto ingresada contiene:  "<<ContarPalabras(cadena)<<"  palabras.\n\n";

     system("pause");
     return 0;
}
     
int ContarPalabras(char cad[]){
     
     int palabras = 0;
     for(int i=1; cad[i]!='\0';++i)   
         if(cad[i-1]==' '&& isalpha(cad[i]))
             ++palabras;
         if(isalpha(cad[0])) ++palabras;
         return palabras;
}