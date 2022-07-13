#include "grafo.hpp"
#include <fstream>
#include <iostream>
#include <string>

#define VISITADO 1
#define NOVISITADO 0

using namespace std;

typedef int tVertice;

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



tGrafo::~tGrafo(){

    for (int i = 0 ; i < nVert ; i++ ){

        delete [] p_matrix[i];
    }
    delete [] p_matrix;
    delete [] Marca;
}

int tGrafo::nVertex(){

    return nVert;
}



int tGrafo::nEdges(){

    return nEdg;
}

tVertice tGrafo::first(tVertice v){

    for (int i = 0 ; nVert ; i++){
        if (p_matrix[v][i] != 0){ 
            return i;
            }
    }
    return nVert;
}

tVertice tGrafo::next(tVertice v1, tVertice v2){

    for (int i = v2+1 ; v2 < nVert ; i++ ){
        if (p_matrix[v1][i] != 0){

            return i;
        }
    }
    return nVert;
}

void tGrafo::setEdge(tVertice v1, tVertice v2, int peso){

    if (p_matrix[v1][v2] == 0) nEdg++;
    p_matrix[v1][v2] = peso;

}

void tGrafo::deleteEdge(tVertice v1, tVertice v2){

    if (p_matrix[v1][v2] != 0) nEdg--;
    p_matrix[v1][v2] = 0;

}

bool tGrafo::isEdge(tVertice v1, tVertice v2){

    return p_matrix[v1][v2] != 0;
}

int tGrafo::weight(tVertice v1, tVertice v2){

    return p_matrix[v1][v2];
}

int tGrafo::getMark(tVertice v){

    return Marca[v];
}

void tGrafo::setMark(tVertice v, int val){

    Marca[v] = val;

}

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

tVertice tGrafo::secondcharacter(tVertice principal){

    int peso, mayor = 0;
    tVertice secundario;

    for (int i = 0 ; i < this->nVertex() ; i++ ){

        peso = this->weight(principal, i);
        if (peso > mayor){

            secundario = i;
            mayor = peso;
        }
    }
    return secundario;
}
