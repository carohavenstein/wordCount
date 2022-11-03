#pragma once

//HashEntry = Nodo = Fila = Entrada de la tabla
/**
 * tipo de dato atómica de tabla hash.
 * Toda tabla hash tiene una clave y un valor.
 * @tparam K //de cualquier tipo de dato: string, int,etc.
 * Dependiendo esta clave, la posición del nodo en donde se
 * almacenará.
 * @tparam T //Cualquier tipo de objeto:int, lista, pila,
 * cola, otra clase propia,etc.
 */
template <class K, class T>
class HashEntry {//mapear un valor de un lugar a otro a través de alguna función, de algún método
private:

    K clave; //palabra
    T valor; //palabra despues de funcion hash
    int ocurrencias = 1; //A CHECKEAR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! o 0?

public:
    HashEntry(K c, T v) {
        clave = c;
        valor = v;
    }

    /*
     * Getters y setters
     */

    K getClave() {
        return clave;
    }

    void setClave(K c) {
        clave = c;
    }

    T getValor() {
        return valor;
    }

    void setValor(T v) {
        valor = v;
    }
};