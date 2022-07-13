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

void Dijkstra(tGrafo* G, int* D, tVertice s) {
    
    int v, w;
    for (int i = 0 ; i < G->nVertex() ; i++) { 

        v = minVertex(G, D);
        if (D[v] == INFINITY){ 
        return; 
        }
        G->setMark(v, VISITADO);

        for ( w = G->first(v) ; w < G->nVertex(); w = G->next(v,w) )
            if (D[w] > (D[v] + G->weight(v, w) ) )
                D[w] = D[v] + G->weight(v, w);
    }
}



int main(){

    int size;

    tamanno_matriz(size);

    tGrafo grafo(size);

    crear_y_rellenar_matriz(&grafo);

    cout << grafo.isEdge(0, 3) << " " << grafo.weight(0,3) << endl;
    cout << grafo.maxGrado()<<endl;

    string* array_nombres;

    size -= 1;
    array_nombres = id_array(size);

    asignar_nombres(array_nombres, size);

    /*for (int i = 0 ; i < size ; i++){

        cout << array_nombres[i] << " - " ;

    }*/

    tVertice principal = grafo.maxGrado();
    tVertice secundario = grafo.secondcharacter(principal); 
    cout << "Personaje principal = " << array_nombres[principal] << endl;
    cout << "Personaje secundario = " << array_nombres[secundario] << endl;

    cout << "Peso de " << array_nombres[principal] << " y " << array_nombres[secundario] << " es de: " << grafo.weight(principal, secundario) << endl;
    cout << " " << endl;
    delete [] array_nombres;
    return 0;
}