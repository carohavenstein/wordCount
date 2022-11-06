#compilar
g++ -c funciones.cpp -o funciones.o
g++ -c main.cpp -o main.o

#linkear
g++ main.o funciones.o -o wordCount

#limpiar
rm *.o