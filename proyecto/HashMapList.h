#pragma once

#include "HashEntry.h"
#include "Lista.h"

//Tabla hash con manejo de colisiones usando listas enlazadas
template <class K, class T>
class HashMapList {
private:
    Lista<HashEntry<K, T>> **tabla;

    unsigned int tamanio;

    static unsigned int hashFunc(K clave);

    unsigned int (*hashFuncP)(K clave);

public:
    explicit HashMapList(unsigned int k);

    HashMapList(unsigned int k, unsigned int (*hashFuncP)(K clave));

    void getList(K clave);

    void put(K clave, T valor);

    void remove(K clave);

    ~HashMapList();

    bool esVacio();

    void print();
};

template <class K, class T>
HashMapList<K, T>::HashMapList(unsigned int k) {
    tamanio = k;
    tabla = new Lista<HashEntry<K, T>> *[tamanio];
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
void HashMapList<K, T>::put(K clave, T valor) {
    unsigned int pos = hashFuncP(clave) % tamanio;

    if(tabla[pos] == NULL) {

        tabla[pos] = new Lista<HashEntry<K, T>>();

    } else {
        //controla para la lista ya existente en esa posicion,
        //si algun nodo tiene la misma clave (palabra)
        //si hay, sumarle 1 a ocurrencias
        //si no, insertar ultimo
        Nodo<HashEntry<K, T>> *aux = tabla[pos]->getInicio();

        while (aux != NULL) {

            std::cout <<"Clave: "<< aux->getDato().getClave() << std::endl;
            std::cout <<"Valor: "<< aux->getDato().getValor() << std::endl;
            
            if (clave == aux->getDato().getClave()) {
                aux->getDato().aumentarOcurrencias(); //NO ANDA BIEN
                std::cout <<"Ocurrencias: "<< aux->getDato().getOcurrencias() << std::endl;
                //return; //esto sale solo del if? o del metodo tmb?
                break;
            } else {

                aux = aux->getSiguiente();

            }

        } 
    
    }

    //o no habia nada en esta posicion o,
    //recorrio lista y no encontro la misma clave (palabra), hay que agregarla
    tabla[pos]->insertarUltimo(HashEntry<K, T>(clave, valor));
}

template <class K, class T>
void HashMapList<K, T>::remove(K clave) {
    unsigned int pos = hashFuncP(clave) % tamanio;

    if(tabla[pos] == NULL) {
        throw 404;
    }

    T dato; // = get(clave)

    tabla[pos]->remove({clave, dato});

    if(tabla[pos]->esVacio()) {
        delete tabla[pos];
        tabla[pos] = NULL;
    }
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
        std::cout << aux->getDato().getValor() << std::endl;
        aux = aux->getSiguiente();
    }
}