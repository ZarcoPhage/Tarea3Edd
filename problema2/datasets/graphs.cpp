#include "grafo.hpp"
#include <fstream>
#include <iostream>
#include <string>

#define VISITADO 1
#define NOVISITADO -1

using namespace std;

typedef int tVertice;

/*****
*   Constructor de tGrafo.
******
*   Inicializa los datos de la matriz y a la vez pide memoria para el tamaño de esta,
*   colocando 0 en cada posicion del arreglo bidimensional.
******
*   Input:
*   int n : Cantidad de vértices de la matriz.
******
*   Returns:
*   No retorna, solo establece la memoria para la matriz.
*****/
tGrafo::tGrafo(int n){
    
    
    nVert = n;
    nEdg = 0;
    
    Marca = new int [n];
    p_matrix = new int* [n];

    for (int i = 0 ; i < n ; i++){

        Marca[i] = NOVISITADO;
    }

    for (int i = 0 ; i < n ; i++){

        p_matrix[i] = new int [n];
    }

    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){

            p_matrix[i][j] = 0;
        }
    }
}



/*****
*   Destructor de tGrafo
******
*   Elimina toda la memoria pedida en la construcción de la matriz.
******
*   Input:
*   No recibe input.
******
*   Returns:
*   No retorna algun dato.
*****/
tGrafo::~tGrafo(){

    for (int i = 0 ; i < nVert ; i++ ){

        delete [] p_matrix[i];
    }
    delete [] p_matrix;
    delete [] Marca;
}



/*****
*   int nVertex.
******
*   Da la cantidad de vértices de la matriz.
******
*   Input:
*   No recibe input.
******
*   Returns:
*   nVert : la cantidad de vértices existentes.
*****/
int tGrafo::nVertex(){

    return nVert;
}



/*****
*   int nEdges.
******
*   Da la cantidad de arcos de la matriz.
******
*   Input:
*   No recibe input.
******
*   Returns:
*   nEdg : la cantidad de arcos existentes.
*****/
int tGrafo::nEdges(){

    return nEdg;
}



/*****
*   tVertice first.
******
*   Busca el primer vecino de un vértice v.
******
*   Input:
*   tVertice V : El vértice base donde se buscarán sus vecinos.
******
*   Returns:
*   i : El primer vecino del vértice v.
*   nVert : La cantidad de vértices en la matriz en caso de no encontrar un vecino de v.
*****/
tVertice tGrafo::first(tVertice v){

    for (int i = 0 ; nVert ; i++){
        if (p_matrix[v][i] != 0){ 
            return i;
            }
    }
    return nVert;
}



/*****
*   tVertice next.
******
*   Busca el siguiente vértice vecino de V1 que sea mayor a V2.
******
*   Input:
*   tVertice v1 : vértice base.
*   tVertice v2 : vértice vecino de v2.
******
*   Returns:
*   i : vértice vecino de v1, y mayor que v2.
*   nVert : La cantidad de vértices de la matriz en caso de no encontrar un vecino de v1 mayor a v2.
*****/
tVertice tGrafo::next(tVertice v1, tVertice v2){

    for (int i = v2+1 ; v2 < nVert ; i++ ){
        if (p_matrix[v1][i] != 0){

            return i;
        }
    }
    return nVert;
}



/*****
*   void setEdge.
******
*   Asigna un valor o peso al arco entre dos vértices.
******
*   Input:
*   tVertice v1,v1 : par de vértices donde se quiere establecer un peso.
*   int peso : valor que recibira el arco entre los vértices.
******
*   Returns:
*   No retorna, solo modifica un valor en la matriz del grafo.
*****/
void tGrafo::setEdge(tVertice v1, tVertice v2, int peso){

    if (p_matrix[v1][v2] == 0) nEdg++;
    p_matrix[v1][v2] = peso;

}



/*****
*   void deleteEdge.
******
*   "Elimina" el valor de un arco entre vértices, dandole valor 0 en la matriz.
******
*   Input:
*   tVertice v1, v2 : Par de vértices donde se eliminará el arco que los une.
******
*   Returns:
*   No retorna, solo modifica un valor en la matriz del grafo.
*****/
void tGrafo::deleteEdge(tVertice v1, tVertice v2){

    if (p_matrix[v1][v2] != 0) nEdg--;
    p_matrix[v1][v2] = 0;

}



/*****
*   int isEdge.
******
*   Consulta la posición de la matriz para ver si existe un arco entre un par de vértices.
******
*   Input:
*   tVertice v1, v2 : Par de vértices donde se quiere verificar la existencia de un arco distinto de 0
******
*   Returns:
*   p_matrix[v1][v2] : valor 0 o 1 dependiendo de lo que encuentre.
*****/
int tGrafo::isEdge(tVertice v1, tVertice v2){

    return p_matrix[v1][v2] != 0;
}



/*****
*   int weight.
******
*   Entrega el valor del arco entre dos vértices.
******
*   Input:
*   tVertice v1, v2 : Par de vértices donde se quiere consultar el peso del arco entre ellos.
******
*   Returns:
*   p_matrix[v1][v2] : valor del arco entre v1 y v2.
*****/
int tGrafo::weight(tVertice v1, tVertice v2){

    return p_matrix[v1][v2];
}



/*****
*   int getMark.
******
*   Pide la marca de un vértice.
******
*   Input:
*   tVertice v : Vértice del cual se quiere saber su marca.
******
*   Returns:
*   Marca[v] : La marca relacionada a tal vértice.
*****/
int tGrafo::getMark(tVertice v){

    return Marca[v];
}



/*****
*   void setMark.
******
*   Le asigna una marca a un vértice.
******
*   Input:
*   tVertice v : vértice al cual se le quiere aplicar una marca.
*   int val : valor que temdrá la marca.
******
*   Returns:
*   No retorna, solo cambia el valor de la marca de un vértice v.
*****/
void tGrafo::setMark(tVertice v, int val){

    Marca[v] = val;

}



/*****
*   tVertice maxGrado.
******
*   Busca el vértice con el mayor grado dentro de la matriz, entendiéndose como grafo a cualquier arco
*   con valor distinto de 0.
******
*   Input:
*   No recibe input.
******
*   Returns:
*   nodoMax : número del vértice con mayor grado del grafo.
*****/
tVertice tGrafo::maxGrado(){
    int grado, gradoMax, i;
    tVertice w, nodoMax;
    gradoMax = 0;
    for(i = 0; i < this->nVertex(); i++){
        grado = 0; //iniciar grado del nodo a analizar en 0
        for (w = this->first(i); w < this->nVertex(); w = this->next(i,w)){
            if(this->isEdge(i,w) == 1){
                grado++;
            }
        }
        if(grado > gradoMax){
            gradoMax = grado;
            nodoMax = i;
        }
    }
    return nodoMax;
}



/*****
*   tVertice secondCharacter.
******
*   Busca el personaje secundario más relevante dentro del grafo, entendiéndose como el personaje
*   que tenga la mayor distancia a la del personaje principal.
******
*   Input:
*   int* D : arreglo con los valores del algoritmo de Dijkstra aplicado al vértice
*   del personaje principal.
******
*   Returns:
*   secundario : Valor del vértice del personaje secundario mas relevante.
*****/
tVertice tGrafo::secondCharacter(int* D){

    int peso = 1; 
    int mayor = 0;
    tVertice secundario;

    for (int i = 0 ; i < this->nVertex() ; i++ ){

        peso = D[i];
        if (peso > mayor){

            secundario = i;
            mayor = peso;
        }
    }
    return secundario;
}



/*****
*   void restablecerMarca.
******
*   Marca como NOVISITADO a cada vértice del grafo.
******
*   Input:
*   No recibe input.
******
*   Returns:
*   No retorna nada, solo modifica el arreglo de marcas del grafo.
*****/
void tGrafo::restablecerMarca(){

    for (int i = 0 ; i < this->nVertex() ; i++){

        Marca[i] = NOVISITADO;
    }
}



/*****
*   int sumaDeArcos
******
*   Suma el valor de todos los arcos del grafo, aunque solo de la "diagonal" hacia la derecha,
*   sin repetir el peso de un arco entre dos vértices.
******
*   Input:
*   No recibe input.
******
*   Returns:
*   suma : valor de la suma de todos los arcos (solo de una "triangular").
*****/
int tGrafo::sumaDeArcos(){

    int suma = 0;
    int size = this->nVertex();
    size -= 1;
    for (int i = 0 ; i < size ; i++){
        
        for (int j = i; j < size ; j++){
            suma += this->weight(i, j); 
        }
    }

    return suma;
}

