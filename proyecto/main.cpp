#include <iostream>
using namespace std;

int main(int argc, char** argv) {

    clock_t begin;

    cout << "Comenzando a medir Tiempo\n" << endl;

    begin = clock();
    /*
     * Insertar código a medir tiempo aquí
     */

    if (argc < 2) {
        cout << "no pasaste archivo txt" << endl;
        return 1;
    }

    //lectura();

    
    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs" << elapsed_secs << "\n" << std::endl;

    return 0;

}