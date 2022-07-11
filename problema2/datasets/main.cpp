#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#include "tamaño_matriz.cpp"
#include "grafo.hpp"
#include "str_to_int_array.cpp"
#include "crear_y_rellenar_matriz.cpp"

using namespace std;

int main(){

    int size;

    tamaño_matriz(size);

    tGrafo grafo(size);

    crear_y_rellenar_matriz(size, &grafo);

    cout << grafo.isEdge(48, 11) << endl;

    
    return 0;
}