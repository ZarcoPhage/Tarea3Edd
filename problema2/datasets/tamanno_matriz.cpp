#include <iostream>
#include <fstream>
#include <string>


using namespace std;


int tamanno_matriz (int& size){

    ifstream file;
    file.open("miserables_id_to_names.csv");

    if (!file.is_open()){

        cout << "Error al abrir el archivo" << endl;
        return 0;
    }

    string line;
    size = 0;

    while (getline(file, line)){

        size++;
    }

    return size-1;

}