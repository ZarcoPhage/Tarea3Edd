#include <iostream>
#include <fstream>
#include <string>


using namespace std;

/*****
*   int tamanno_matriz.
******
*   Lee el largo del archivo para definir el tamaño de la matriz
*   a crear.
******
*   Input:
*   int &size : Tamaño de la matriz.
******
*   Returns:
*   size-1, cantidad de lineas que contiene el archivo, menos la primera linea.
*****/
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
    file.close();
    return size-1;


}