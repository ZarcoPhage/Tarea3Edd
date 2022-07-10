#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int cant_nodos (int &a){

    ifstream file;

    file.open("miserables_id_to_name.csv");

    string line;
    a = 0;

    while(getline(file, line)){

        a++;
    }

    a--;

    return a;
}