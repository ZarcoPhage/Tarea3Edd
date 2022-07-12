#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#include "tamanno_matriz.cpp"
#include "grafo.hpp"



using namespace std;


int* str_to_int_array (string line, int &n){

    char* char_array = new char [line.length()];
    strcpy(char_array, line.c_str());

    char* p2;
    char* p3;
    n = 0;
    
    p2 = strtok(char_array, ";");
    while(p2 != NULL){

        n++;
        p2 = strtok(NULL, ";");
    }

    int* firstline_array = new int [n-1];
    int i = 0;

    strcpy(char_array, line.c_str());

    p3 = strtok(char_array, ";");
    while(p3 != NULL){

        firstline_array[i] = stoi(p3);
        i++;
        p3 = strtok(NULL, ";");
    }

    delete [] char_array;
    return firstline_array;
    
}

int crear_y_rellenar_matriz(int &size, tGrafo* grafo){

    ifstream file;
    file.open("miserables.csv", ios::in);
    
    if (!file.is_open()){

        cout << "Error al abrir el archivo." << endl;
    }

    string stringline;
    getline(file, stringline);

    int fla_size;
    int* first_line_array = str_to_int_array(stringline, fla_size);

    while(getline(file, stringline)){

        int fla2_size;
        int* i_line = str_to_int_array(stringline, fla2_size);

        for (int i = 0 ; i < fla_size ; i++){

            grafo->setEdge(first_line_array[i], i_line[0], i_line[i+1]);


        }

        delete [] i_line;
    }
    delete[] first_line_array;
    return fla_size;
}

int main(){

    int size;

    tamanno_matriz(size);

    tGrafo grafo(size);

    crear_y_rellenar_matriz(size, &grafo);

    //cout << grafo.isEdge(48, 11) << endl;

    grafo.printMatrix();
    
    return 0;
}