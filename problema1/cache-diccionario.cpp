#include <iostream>
#include <string>
#include <cstring>
#define M 128
#define VACIA -1
#define BORRADA -2
#define OCUPADA -3

using namespace std;
/*
typedef int hashKey;

struct hashEntry{
    char termino[32];
    string significado;
    
}
ranura HashTable[M];

int hashFunction(char *termino){
    unsigned int *aux = (unsigned int *)termino;
    int len = strlen(termino) / 4;
    unsigned int sum = 0;
    unsigned int auxiliarNum = 0;
    for(int i = 0; i < len; i++){
        auxiliarNum = aux[i]
        sum += auxiliarNum;
    }
    return sum;
} //método plegamiento

bool hashInsert(ranura HashTable[], hashKey key, hashEntry info){
    int inicio, i;
    int pos = inicio = hashFunction(key);
    for(i = 1; (HashTable[pos].key != VACIA || HashTable[pos].key != BORRADA) && HashTable[pos].key != key; i++){
        pos = (inicio + position(key, i)) % M;
    }
    if (HashTable[pos].key == key){
        return false;
    }else{
        HashTable[pos].key = key;
        HashTable[pos].info = info
        return true;
    }
}

int position(hashKey key, int i){
    if (i == 0){
        return 0;
    }
    return 9*i*i + 5*i + 2;
}

*/
struct ranuraHash{
    char termino[32];
    string significado;
    unsigned int consultas;
    bool signVacio;
    int estado;
};

unsigned int folder(string termino){
    cout<<"-------------------------------"<<endl;
    cout<<termino<<endl;
    int len, i;
    len = termino.length();
    /*
    cout<<"longitud del termino: "<<len<<endl;
    cout<<endl;
    for (int i = 0; i<len;i++){
        cout<<termino[i]<<" ";
    }
    cout<<endl;

    for (i = 0; i < len;i++){
        cout<<termino[i]<<(int)termino[i]<<endl;
    }
    */
    len = strlen(termino.c_str())/4;
    unsigned int sum = 0;
    for (i = 0; i < len; i++){
        cout<<"iteracion: "<<i<<endl;
        //cout<<aux[i]<<endl;
        sum += (int)termino[i];
    }
    cout<<"suma es: "<<sum<<endl;
    return sum;
}

class CacheDiccionario{
    private:
        unsigned int consultasTotales;
        unsigned int signConocidos;
        unsigned int signDesconocidos;
        unsigned int cleanups; //limpiezas totales
        unsigned int hits; //términos encontrados al realizar búsqueda
        unsigned int misses; // cantidad de veces que no se encontraron términos
        unsigned int accesses; //cantidad de accesos a ranuras del hash

        ranuraHash HashTable[M]; //hash table relacionada al TDA de la caché

        unsigned int hashFunc(int foldedTermino); //función de hash

        unsigned int probing(int key, int index); //función p para reubicar colisiones (debe ser por hash cerrado, hash cuadrático puede servir para facilitar trabajo)
    public:
        CacheDiccionario(){for (int i = 0; i<M; i++){HashTable[i].estado = -1;}};
        ~CacheDiccionario(){};

        bool erase(string termino); //borrar el término y significado, borra una ranura y la asigna como borrada
        void clean(); // limpiar la tabla, eliminar la mitad de elementos con menores consultas
        // recuperar las consultas de cada ranura de la HT y ordenarlas puede ser una opción
        // luego eliminar la mitad de las ranuras con menores consultas (ciclo for quizás??) 

        bool query(string termino, string& significado); //consultar ranura de la HT
        void insert(string termino, string significado); 
        void querystats(int& total, int& conocidos, int& desconocidos);
        void perfstats(int& accesses, int& hits, int& misses, int& cleanups);
        void printHT();
};

unsigned int CacheDiccionario::probing(int key, int index){
    return index;
}   //linear probing por ahora

void CacheDiccionario::printHT(){
    for (int i = 0; i < M; i++){
        cout<<i<< " : "<<HashTable[i].termino<<" : "<<HashTable[i].significado<<" : "<< HashTable[i].estado<<endl; 
    }
}
 
unsigned int CacheDiccionario::hashFunc(int foldedTermino){
    int claveCuadrada, len, i, hashPos;
    if(foldedTermino == 0){
        //cout<<"RETORNO CERO"<<endl;
        return 0;
    }
    claveCuadrada = (foldedTermino*foldedTermino);
    //cout<<claveCuadrada<<endl;
    string valorMedio, strCuadrada;
    strCuadrada = to_string(claveCuadrada); //transformar en string el valor de la clave al cuadrado para iterar sobre ella
    len = strlen(strCuadrada.c_str());
    for (i = 0; i<len; i++){
        if((i >= (len/2 - 1)) && (i <= len/2)){
            valorMedio += strCuadrada[i]; //toma el término central y el anterior y lo introduce al string
        }
    }
    //cout<<valorMedio<<endl;
    hashPos = stoi(valorMedio) % M; //toma el valor cuadrado medio y lo divide por la cantidad de ranuras que tenemos, el módulo es la posición indicada 
    return hashPos;
}

//void CacheDiccionario::hashInsert(ranura *HT, string termino, string significado){

void CacheDiccionario::insert(string termino, string significado){
    int claveInt;
    claveInt = folder(termino);
    int inicio, i; 
    int pos = inicio = hashFunc(claveInt);
    //cout<<"line 121"<<endl;
    for (i = 1; HashTable[pos].estado != VACIA && HashTable[pos].termino != termino; i++){
        pos = (inicio + probing(pos, i)) % M;
    //cout<<"line 125"<<endl;
    }
    if (HashTable[pos].termino == termino){
        cout<<"termino repetido"<<endl;
    }
    else{
        strcpy(HashTable[pos].termino, termino.c_str());
        HashTable[pos].significado = significado;
        HashTable[pos].estado = OCUPADA;
        HashTable[pos].signVacio = false;
    }
}




// PREGUNTA PROFE: SI LAS CLAVES SON TERMINOS DE 32 CARACTERES, PODRÍA SER UNA BUENA IDEA MANEJAR LAS LLAVES DE
// LA HASH TABLE COMO ENTEROS COMO LOS PRIMEROS 2 A 4 CARACTERES? QUIZÁS GENERE MAS COLISIONES EN LOS TERMINOS
// QUE TENGAN LOS MISMOS CARACTERES, PERO FACILITA EL TRABAJO EN TERMINOS DE CASTING DE TIPOS DE DATOS
// -> BUENA IDEA, UTIL