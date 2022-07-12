#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

<<<<<<< HEAD
#include "grafo.hpp"


using namespace std;

tVertice* str_to_int_array (string line, int &n){
=======
using namespace std;

int* str_to_int_array (string line, int &n){
>>>>>>> 2338c1391a8127585457f4b4422ac938bf9986ee

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

<<<<<<< HEAD
    tVertice* firstline_array = new tVertice [n-1];
=======
    int* firstline_array = new int [n-1];
>>>>>>> 2338c1391a8127585457f4b4422ac938bf9986ee
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