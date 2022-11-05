#pragma once

#include "Lista.h"
#include <string>
using namespace std;

//Tabla hash con manejo de colisiones usando listas enlazadas

template <class K, class T>
struct HashEntry {
    HashEntry() {}
    HashEntry(K c, T v) {
        clave = c; //palabra
        valor = v; //ocurrencias
    }

    bool operator != (HashEntry<K, T> otro) {
        return clave != otro.clave;
    }

    K clave; //palabra
    T valor; //ocurrencias
};

void quickSortAlfabetico(HashEntry<string, int> *arr, int inicio, int fin);
void quickSortOcurrencias(HashEntry<string, int> *arr, int inicio, int fin);

template<class K, class T>
class HashMapList {
private:    
    Lista<HashEntry<K, T>> **tabla;

    unsigned int tamanio;

    static unsigned int hashFunc(K clave);

    unsigned int (*hashFuncP)(K clave);

    int palabrasDif = 0;

public:
    explicit HashMapList(unsigned int k);

    HashMapList(unsigned int k, unsigned int (*hashFuncP)(K clave));

    void getList(K clave);

    void put(K clave);

    int getPalabrasDiferentes() { return palabrasDif; }

    void remove(K clave);

    ~HashMapList();

    bool esVacio();

    void print();

    HashEntry<K, T> getHashEntry(K clave);

    HashEntry<K, T>* transformarMapaToArreglo();
    HashEntry<K, T>* sortAlfabetico();
    HashEntry<K, T>* sortOcurrencias();
};

template <class K, class T>
HashMapList<K, T>::HashMapList(unsigned int k) {
    tamanio = k;
    tabla = new Lista<HashEntry<K, T>>*[tamanio];
    for(int i = 0; i < tamanio; i++) {
        tabla[i] = NULL;
    }
    hashFuncP = hashFunc;
}

template <class K, class T>
HashMapList<K, T>::HashMapList(unsigned int k, unsigned int (*fp)(K)) {
    tamanio = k;
    tabla = new Lista<HashEntry<K, T>> *[tamanio];
    for(int i = 0; i < tamanio; i++) {
        tabla[i] = NULL;
    }
    hashFuncP = fp;
}

template <class K, class T>
HashMapList<K, T>::~HashMapList() {
    for(int i = 0; i < tamanio; i++) {
        if(tabla[i] != NULL) {
            delete tabla[i];
        }
    }
}

template <class K, class T>
void HashMapList<K, T>::put(K clave) {
    unsigned int hash = hashFuncP(clave);
    unsigned int pos = hash % tamanio;

    if(tabla[pos] == NULL) {
        tabla[pos] = new Lista<HashEntry<K, T>>();
    } else {
        //controla para la lista ya existente en esa posicion,
        //si algun nodo tiene la misma clave (palabra)
        //si hay, sumarle 1 a ocurrencias
        //si no, insertar ultimo
        Nodo<HashEntry<K, T>> *aux = tabla[pos]->getInicio();
        while (aux != NULL) {
            if (clave == aux->getDato().clave) {
                aux->getDato().valor++;
                return;
            } else {
                aux = aux->getSiguiente();
            }

        } 
    
    }

    //o no habia nada en esta posicion o,
    //recorrio lista y no encontro la misma clave (palabra), hay que agregarla
    tabla[pos]->insertarUltimo(HashEntry<K, T>(clave, 1));
    palabrasDif++;  
}

template <class K, class T>
void HashMapList<K, T>::remove(K clave) {
    unsigned int pos = hashFuncP(clave) % tamanio;

    if(tabla[pos] == NULL) {
        return;
    }

    bool d = tabla[pos]->removerPrimeraIncidencia(HashEntry<K, T>(clave, 1));
    if (d) {
        palabrasDif--;
    }

    if(tabla[pos]->esVacia()) {
        delete tabla[pos];
        tabla[pos] = NULL;
    }
}

template <class K, class T>
HashEntry<K, T> HashMapList<K, T>::getHashEntry(K clave) {
    unsigned int pos = hashFuncP(clave) % tamanio;

    if(tabla[pos] == NULL) {
        return HashEntry<K, T>(); //no existe hashEntry con esa clave, devuelve un hashEntry vacio
    }

    return tabla[pos]->buscarNodo(HashEntry<K, T>(clave, 1));
}

template <class K, class T>
bool HashMapList<K, T>::esVacio() {
    for(int i = 0; i < tamanio; i++) {
        if(tabla[i] != NULL) {
            return false;
        }
    }
    return true;
}

template <class K, class T>
unsigned int HashMapList<K, T>::hashFunc(K clave) {
    return (unsigned int) clave;
}

template <class K, class T>
void HashMapList<K, T>::getList(K clave) { //Método que devuelve la lista según la clave que recibe
    unsigned int pos = hashFuncP(clave) % tamanio;

    if(tabla[pos] == NULL) {
        throw 404;
    }

    Nodo<HashEntry<K, T>> *aux = tabla[pos]->getInicio();

    while (aux != NULL) {
        std::cout << aux->getDato().valor << std::endl;
        aux = aux->getSiguiente();
    }
}

template <class K, class T>
void HashMapList<K, T>::print() {
    for (int i = 0; i < tamanio; ++i) {
        if(tabla[i] == NULL) {
            continue;
        }

        Nodo<HashEntry<K, T>> *aux = tabla[i]->getInicio();
        while (aux != NULL) {
            std::cout << aux->getDato().clave << " " << aux->getDato().valor << std::endl;
            aux = aux->getSiguiente();
        }
    }
}

template <class K, class T>
HashEntry<K, T>* HashMapList<K, T>::transformarMapaToArreglo() {
    HashEntry<K, T>* arregloPalabras = new HashEntry<K, T>[palabrasDif];
    //pasa todos los hashentry a un arreglo
    int pos = 0;
    for (int i = 0; i < tamanio; ++i) {
        if(tabla[i] == NULL) {
            continue;
        }

        Nodo<HashEntry<K, T>> *aux = tabla[i]->getInicio();
        while (aux != NULL) {
            arregloPalabras[pos] = aux->getDato();
            aux = aux->getSiguiente();
            pos++;
        }
    }

    return arregloPalabras;
}

void quickSortAlfabetico(HashEntry<string, int> *arr, int inicio, int fin) {
  int i, j, medio;
  HashEntry<string, int> pivot, aux;

  medio = (inicio + fin) / 2;
  pivot = arr[medio];
  i = inicio;
  j = fin;

  do
  {
    while (arr[i].clave < pivot.clave)
      i++;
    while (arr[j].clave > pivot.clave)
      j--;

    if (i <= j)
    {
      aux = arr[i];
      arr[i] = arr[j];
      arr[j] = aux;
      i++;
      j--;
    }
  } while (i <= j);

  if (j > inicio)
    quickSortAlfabetico(arr, inicio, j);
  if (i < fin)
    quickSortAlfabetico(arr, i, fin);
}

void quickSortOcurrencias(HashEntry<string, int> *arr, int inicio, int fin) {
    int i, j, medio;
    HashEntry<string, int> pivot, aux;

    medio = (inicio + fin) / 2;
    pivot = arr[medio];
    i = inicio;
    j = fin;

  do
  {
    while (arr[i].valor > pivot.valor)
      i++;
    while (arr[j].valor < pivot.valor)
      j--;

    if (i <= j)
    {
      aux = arr[i];
      arr[i] = arr[j];
      arr[j] = aux;
      i++;
      j--;
    }
  } while (i <= j);

  if (j > inicio)
    quickSortOcurrencias(arr, inicio, j);
  if (i < fin)
    quickSortOcurrencias(arr, i, fin);
}

template <class K, class T>
HashEntry<K, T>* HashMapList<K, T>::sortAlfabetico() {
    auto arr = transformarMapaToArreglo();
    quickSortAlfabetico(arr, 0, palabrasDif-1);
    return arr;
}

template <class K, class T>
HashEntry<K, T>* HashMapList<K, T>::sortOcurrencias() {
    auto arr = transformarMapaToArreglo();
    quickSortOcurrencias(arr, 0, palabrasDif-1);
    return arr;
}