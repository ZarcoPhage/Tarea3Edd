#include <iostream>
#include <fstream>
#include <string>
#include <cstring>


#include "grafo.hpp"


using namespace std;

/*****
*   tVertice* str_to_int_array
******
*   Crea un arreglo con la información de la línea entregada,
*   sin el componente ';'.
******
*   Input:
*   string line : Linea a guardar en el arreglo.
*   int* n : Tamaño del arreglo a crear.
******
*   Returns:
*   tVertice*, arreglo con los números que contiene la línea entregada.
*****/
tVertice* str_to_int_array (string line, int &n){

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

    tVertice* firstline_array = new tVertice [n-1];
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



/*****
*   void crear_y_rellenar_matriz
******
*   Establece las conexiones entre vértices de la matriz de manera ordenada.
******
*   Input:
*   tGrafo* grafo : grafo dónde se harán los cambios.
******
*   Returns:
*   No retorna, solo modifica la matriz asociada al grafo.
*****/
void crear_y_rellenar_matriz (tGrafo* grafo){

    ifstream file;
    file.open("miserables.csv", ios::in);
    
    if (!file.is_open()){

        cout << "Error al abrir el archivo." << endl;
    }

    string stringline;
    getline(file, stringline);

    int fla_size;
    tVertice* first_line_array = str_to_int_array(stringline, fla_size);

    while(getline(file, stringline)){

        int fla2_size;
        tVertice* i_line = str_to_int_array(stringline, fla2_size);

        for (int i = 0 ; i < fla_size ; i++){

            grafo->setEdge(first_line_array[i], i_line[0], i_line[i+1]);
            

        }

        delete [] i_line;
    }
    delete[] first_line_array;
    file.close();
}



