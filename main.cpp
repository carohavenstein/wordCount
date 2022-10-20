#include <iostream>
using namespace std;

int main(int argc, char** argv) {

    if (argc != 2) {
        cout << "" << endl;
        return 1;
    }

    char* caracter = nullptr;
    int largo = 0;
    int letras = 0;
    
    for (int i = 0; i < largo; i++){
        if ((caracter[i] >= 'a' && caracter[i] <= 'z') || (caracter[i] >= 'A' && caracter[i] <= 'Z')){
            letras += 1;
        }
    }
}