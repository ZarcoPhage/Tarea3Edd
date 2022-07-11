#include <iostream>
#include <fstream>
#include <string>
#include <cstring>


#include "grafo.hpp"
#include "str_to_int_array.cpp"


using namespace std;

/*

*/

int crear_y_rellenar_matriz (int &size, tGrafo* grafo){

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