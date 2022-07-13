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


int shortestWeightedPath(tGrafo* G, int size, int* D){
    tVertice s;
    int i, o, sumaTotal;
    sumaTotal = 0;
    for(i = 0; i < G->nVertex(); i++){
        s = i;
        for (o = 0 ; o < size ; o++){
            D[o] = INT_MAX;
        }
        D[s] = 0;
        Dijkstra(G,D,i);
        for(o = 0; o < G->nVertex(); o++){
            sumaTotal += D[o];
        }
        G->restablecermarca();
    }
    return sumaTotal;
}


int caminocorto(tGrafo G, int size){

    int sumatotal = 0;
    G.restablecermarca();
    for (int i = 0 ; i < G.nVertex() ; i++){

        int* D = new int [G.nVertex()];
        for (int j = 0 ; j < G.nVertex() ; j++){

            D[j] = INT_MAX;
        }
        D[i] = 0;
        Dijkstra(&G, D, i);
        for (int k = 0; k < G.nVertex() ; k++){
            
            sumatotal+= D[k];
        }
        delete [] D;
        G.restablecermarca();
    }
    return sumatotal;

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
    
    D = new int [size];
    
    for (int i = 0 ; i < size ; i++){

        D[i] = INT_MAX;
    }
    D[principal] = 0;

    Dijkstra(&grafo, D, principal);

    tVertice secundario;
    secundario = grafo.secondcharacter(D);

    cout << "numero de vertices: " << grafo.nVertex() << endl;
    cout << "numero de size: " << size << endl;

    cout << "Personaje secundario: "  << array_nombres[secundario] << endl;

    int suma;

    suma = caminocorto(grafo, size);

    cout << " la suma es: " << suma << endl;

    int sumaEdg;

    sumaEdg = grafo.sumadearcos(&grafo);

    cout << " la sumaEdg es: " << sumaEdg << endl;

    float f = suma;
    float l;
    l = f/sumaEdg;

    cout << "la longuitud de camino promedio con pesos es: " << l << endl; 
    
    delete [] array_nombres;
    delete [] D;
    return 0;
}