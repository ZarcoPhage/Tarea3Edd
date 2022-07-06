#include "grafo.hpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

typedef int tVertice;

tGrafo::tGrafo(int n){

ifstream file;
file.open("miserables.csv");

string line;

while (getline(file, line)){

    cout << line << endl;

}

}

tGrafo::~tGrafo(){

}

int tGrafo::nVertex(){

}

int tGrafo::nEdges(){

}

tVertice tGrafo::first(tVertice v){

}

tVertice tGrafo::next(tVertice v1, tVertice v2){

}

void tGrafo::setEdge(tVertice v1, tVertice v2, int peso){

}

void tGrafo::deleteEdge(tVertice v1, tVertice v2){

}

int tGrafo::isEdge(tVertice v1, tVertice v2){

}

int tGrafo::weight(tVertice v1, tVertice v2){

}

int tGrafo::getMark(tVertice v){

}

int tGrafo::setMark(tVertice v){

}


