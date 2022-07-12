#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

string* id_array (int size){

    string* id_array;
    id_array = new string [size];
    return id_array;
}

void asignar_nombres (string* id_array, int size){

    ifstream file;
    file.open("miserables_id_to_names.csv");

    if (!file.is_open()){
        cout << "Error al abrir el archivo." << endl;
        exit(1);
    }

    string line;
    getline(file,line);

    for (int i = 0 ; i < size ; i++){

        getline(file, line);
        char* new_array = new char[line.length()];
        strcpy(new_array, line.c_str());

        char* p;

        p = strtok(new_array, ",");
        int j = stoi(p);
        p = strtok(NULL, ",");
        string name(p);
        //cout << name << endl;
        id_array[j] = name;
        delete [] new_array;
    }
}
/*
int main(){

    cout << "introduce el size: " << endl;
    int size;
    cin >> size;

    string* p = id_array(size);

    asignar_nombres(p, size);

    for (int i = 0 ; i < size ; i++){

        cout << p[i] << " - " ;

    }
    
    cout << "" << endl;
    return 0;
}
*/