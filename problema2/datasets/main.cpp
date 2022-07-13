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

using namespace std;

/*****
*   int minVertex.
******
*   Escanear la lista de vértices en busca del valor mínimo.
******
*   Input:
*   tGrafo* G : grafo donde se hará correr la función.
*   int* D : arreglo donde estan guardados los valores de Dijkstra.
******
*   Returns:
*   v : vertice de mínima distancia.
*****/
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



/*****
*   void Dijkstra.
******
*   Algoritmo de Dijkstra, el cual busca el camino más corto a cualquier vértice a partir de un 
*   vértice base. 
******
*   Input:
*   tGrafo* G : grafo donde se hará correr la función.
*   int* D : arreglo donde serán guardados los valores de Dijkstra.
*   tVertice s : vértice base.
******
*   Returns:
*   No retorna, solo modifica el valor de D. 
*****/
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



/*****
*   void Dijkstra2.
******
*   Algoritmo de Dijkstra, el cual busca el camino más corto a cualquier vértice a partir de un 
*   vértice base, solo que ahora suma 1 o 0.
******
*   Input:
*   tGrafo* G : grafo donde se hará correr la función.
*   int* D : arreglo donde serán guardados los valores de Dijkstra.
*   tVertice s : vértice base.
******
*   Returns:
*   No retorna, solo modifica el valor de D. 
*****/
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



/*****
*   void caminoCorto.
******
*   Suma el valor de Dijkstra2 en una variable para cada nodo del vértice. 
******
*   Input:
*   tGrafo* G : grafo donde se hará correr la función.
*   int size : tamaño de la matriz.
******
*   Returns:
*   sumaTotal = valor de cada casilla del arreglo D aplicandole algoritmo de Dijkstra2 "size" veces. 
*****/
int caminoCorto(tGrafo* G, int size){

    int sumatotal = 0;
    G->restablecerMarca();
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
        G->restablecerMarca();
    }
    return sumatotal;
}



/*****
*   void caminoCortoPesos.
******
*   Suma el valor de Dijkstra en una variable para cada nodo del vértice. 
******
*   Input:
*   tGrafo* G : grafo donde se hará correr la función.
*   int size : tamaño de la matriz.
******
*   Returns:
*   sumaTotal = valor de cada casilla del arreglo D aplicandole algoritmo de Dijkstra "size" veces. 
*****/
int caminoCortoPesos(tGrafo* G, int size){

    int sumatotal = 0;
    G->restablecerMarca();
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
        G->restablecerMarca();
    }
    return sumatotal;

}


int main(){

    int size;
    int* D;
    tamanno_matriz(size);

    tGrafo grafo(size);

    crear_y_rellenar_matriz(&grafo);
    
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
    secundario = grafo.secondCharacter(D);
    int suma, sumaEdg;

    suma = caminoCortoPesos(&grafo, size);
    sumaEdg = grafo.sumaDeArcos();

    

    float f = suma;
    float l;
    l = f/sumaEdg;

    
    
    int suma2;
    suma2 = caminoCorto(&grafo, size);
    

    float combinatoria = ((76*75)/2);
    float a = suma2/combinatoria;

    

    cout << "Personaje Principal: "  << array_nombres[principal] << endl;
    cout << "Personaje secundario mas relevante: " << array_nombres[secundario] << endl;
    cout << "Diametro: " << a << endl;
    cout << "Diametro (con pesos): " << l << endl;

    delete [] array_nombres;
    delete [] D;
    return 0;

}