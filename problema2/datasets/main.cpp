#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#include "tamanno_matriz.cpp"
#include "grafo.hpp"
#include "crear_y_rellenar_matriz.cpp"
#include "vertice_a_persona.cpp"


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

    crear_y_rellenar_matriz(&grafo);

    cout << grafo.isEdge(0, 3) << " " << grafo.weight(0,3) << endl;
    cout << grafo.maxGrado()<<endl;

    string* array_nombres;

    
    cout << "valor de size: "<<size << endl;

    size -= 1;
    array_nombres = id_array(size);

    asignar_nombres(array_nombres, size);

    for (int i = 0 ; i < size ; i++){

        cout << array_nombres[i] << " - " ;

    }

    cout << " " << endl;
    return 0;
}