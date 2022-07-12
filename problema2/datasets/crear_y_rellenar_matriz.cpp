#include <iostream>
#include <fstream>
#include <string>
#include <cstring>


#include "grafo.hpp"


using namespace std;

/*

*/

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

void crear_y_rellenar_matriz (int &size, tGrafo* grafo){

    ifstream file;
    file.open("miserables.csv", ios::in);
    
    if (!file.is_open()){

        cout << "Error al abrir el archivo." << endl;
    }

    string stringline;
    getline(file, stringline);

    int fla_size;
<<<<<<< HEAD
    tVertice* first_line_array = str_to_int_array(stringline, fla_size);
=======
    int* first_line_array = str_to_int_array(stringline, fla_size);
>>>>>>> 2338c1391a8127585457f4b4422ac938bf9986ee

    while(getline(file, stringline)){

        int fla2_size;
<<<<<<< HEAD
        tVertice* i_line = str_to_int_array(stringline, fla2_size);
=======
        int* i_line = str_to_int_array(stringline, fla2_size);
>>>>>>> 2338c1391a8127585457f4b4422ac938bf9986ee

        for (int i = 0 ; i < fla_size ; i++){

            grafo->setEdge(first_line_array[i], i_line[0], i_line[i+1]);
<<<<<<< HEAD
            
=======

>>>>>>> 2338c1391a8127585457f4b4422ac938bf9986ee

        }

        delete [] i_line;
    }

    delete[] first_line_array;
<<<<<<< HEAD

}



=======
    return fla_size;


}
>>>>>>> 2338c1391a8127585457f4b4422ac938bf9986ee
