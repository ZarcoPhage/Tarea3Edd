#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#include "tamanno_matriz.cpp"
#include "grafo.hpp"
#include "crear_y_rellenar_matriz.cpp"

using namespace std;

int main(){

    int size;

    tamanno_matriz(size);

    tGrafo grafo(size);

    crear_y_rellenar_matriz(size, &grafo);

    cout << grafo.isEdge(48, 11) << endl;

    
    return 0;
}