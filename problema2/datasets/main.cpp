#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <climits>

#include "tamanno_matriz.cpp"
#include "grafo.hpp"
#include "crear_y_rellenar_matriz.cpp"
#include "vertice_a_persona.cpp"


#define NOVISITADO -1
#define VISITADO 1
//#define INFINITY intmax_t

using namespace std;


int minVertex(tGrafo* G, int* D) {
    
    int i;
    int v = -1;
    
    for (i = 0 ; i < G->nVertex(); i++ )
        if (G->getMark(i) == NOVISITADO){ v = i; break; }
    for (i++ ; i < G->nVertex() ; i++ ) 
        if ((G->getMark(i) == NOVISITADO) && (D[i] < D[v]))
            v = i;
    
    return v;
}

void Dijkstra(tGrafo* G, int* D, tVertice s) {

    int i, v, w;
    for (i = 0 ; i < G->nVertex() ; i++) { 

        v = minVertex(G, D);
        if (D[v] == INT_MAX) return;
        G->setMark(v, VISITADO);

        for ( w = G->first(v) ; w < G->nVertex(); w = G->next(v,w) )
            if (D[w] > (D[v] + G->weight(v, w) ) )
                D[w] = D[v] + G->weight(v, w);
    }
}


void Dijkstra2(tGrafo* G, int* D, tVertice s) {

    int i, v, w;
    for (i = 0 ; i < G->nVertex() ; i++) { 

        v = minVertex(G, D);
        if (D[v] == INT_MAX) return;
        G->setMark(v, VISITADO);

        for ( w = G->first(v) ; w < G->nVertex(); w = G->next(v,w) )
            if (D[w] > (D[v] + G->isEdge(v, w) ) )
                D[w] = D[v] + G->isEdge(v, w);
    }
}



int main(){

    int size;
    int* D;
    tamanno_matriz(size);

    tGrafo grafo(size);

    crear_y_rellenar_matriz(&grafo);

    cout << grafo.isEdge(0, 3) << " " << grafo.weight(0,3) << endl;
    cout << grafo.maxGrado()<<endl;

    string* array_nombres;

    size -= 1;
    array_nombres = id_array(size);
    asignar_nombres(array_nombres, size);


    tVertice principal = grafo.maxGrado();
    

    //int size2 = grafo.nVertex();
    D = new int [size];
    
    for (int i = 0 ; i < size ; i++){

        D[i] = INT_MAX;
    }
    D[principal] = 0;

    Dijkstra(&grafo, D, principal);

    tVertice secundario;
    secundario = grafo.secondcharacter(D);

    for (int i = 0 ; i < size ; i++){

        cout << " posicion i:  " << i  << " Tiene peso de: " << D[i] << endl;

    }

    cout << "Personaje secundario: "  << array_nombres[secundario] << endl;

    delete [] array_nombres;
    delete [] D;
    return 0;
}