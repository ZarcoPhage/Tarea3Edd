#include <iostream>
#include <fstream>
#include <string>


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