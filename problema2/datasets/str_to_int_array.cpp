#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

#include "grafo.hpp"


using namespace std;

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