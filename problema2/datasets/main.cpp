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


int caminoCorto(tGrafo* G, int size){

    int sumatotal = 0;
    G->restablecermarca();
    for (int i = 0 ; i < G->nVertex() ; i++){

        int* D = new int [G->nVertex()];
        for (int j = 0 ; j < G->nVertex() ; j++){

            D[j] = INT_MAX;
        }
        D[i] = 0;
        Dijkstra2(G, D, i);
        for (int k = 0; k < G->nVertex() ; k++){
            
            sumatotal+= D[k];
        }
        delete [] D;
        G->restablecermarca();
    }
    return sumatotal;
}

int caminoCortoPesos(tGrafo* G, int size){

    int sumatotal = 0;
    G->restablecermarca();
    for (int i = 0 ; i < G->nVertex() ; i++){

        int* D = new int [G->nVertex()];
        for (int j = 0 ; j < G->nVertex() ; j++){

            D[j] = INT_MAX;
        }
        D[i] = 0;
        Dijkstra(G, D, i);
        for (int k = 0; k < G->nVertex() ; k++){
            
            sumatotal+= D[k];
        }
        delete [] D;
        G->restablecermarca();
    }
    return sumatotal;

}

/*
unsigned long long factorial(int n) {
   if(n == 0) return 1;
   else if(n > 1) return n*factorial(n-1);
   return 1;
}
*/



int main(){

    int size;
    int* D;
    tamanno_matriz(size);

    tGrafo grafo(size);

    crear_y_rellenar_matriz(&grafo);
    /*
    cout << grafo.isEdge(8, 1) << " " << grafo.weight(8,1) << endl;

    for (int i = 0 ; i < size ; i++){

        cout << grafo.weight(0,i) << " - " ;

    }
    cout << "" << endl;
    cout << grafo.maxGrado()<<endl;
    */
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

    //cout << "numero de vertices: " << grafo.nVertex() << endl;
    //cout << "numero de size: " << size << endl;

    //cout << "Personaje secundario: "  << array_nombres[secundario] << endl;

    int suma;

    suma = caminoCortoPesos(&grafo, size);

    //cout << " la suma es: " << suma << endl;

    int sumaEdg;

    sumaEdg = grafo.sumadearcos();

    //cout << " la sumaEdg es: " << sumaEdg << endl;

    float f = suma;
    float l;
    l = f/sumaEdg;

    //cout << "la longuitud de camino promedio con pesos es: " << l << endl; 
    
    int suma2;

    suma2 = caminoCorto(&grafo, size);
    //cout << "suma2 = "  << suma2 << endl;

    float combinatoria = ((76*75)/2);

    float a = suma2/combinatoria;

    //cout << combinatoria << endl;
    //cout << a << endl;

    cout << "Personaje Principal: "  << array_nombres[principal] << endl;
    cout << "Personaje secundario mas relevante: " << array_nombres[secundario] << endl;
    cout << "Diametro: " << a << endl;
    cout << "Diametro (con pesos): " << l;

    delete [] array_nombres;
    delete [] D;
    return 0;

}