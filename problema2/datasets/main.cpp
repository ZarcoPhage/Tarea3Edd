#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#include "tamanno_matriz.cpp"
#include "grafo.hpp"
#include "crear_y_rellenar_matriz.cpp"


#define NOVISITADO 0
#define VISITADO 1

using namespace std;


int minVertex(tGrafo* G, int* D) {
    
    int i, v = -1;
    
    for (i = 0 ; i < G->nVertex(); i++ ){
        if (G->getMark(i) == NOVISITADO){ 
            v = i;
            break;
        }
    }
    for (i++ ; i < G->nVertex() ; i++ ){ 
        if ((G->getMark(i) == NOVISITADO) && (D[i] < D[v]))
        v = i;
    }
    return v;
}



int main(){

    int size;

    tamanno_matriz(size);

    tGrafo grafo(size);

    crear_y_rellenar_matriz(size, &grafo);

    cout << grafo.isEdge(0, 3) << " " << grafo.weight(0,3) << endl;
    cout << grafo.maxGrado()<<endl;


    return 0;
}