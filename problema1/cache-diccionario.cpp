#include <iostream>
#include <string>
#include <cstring>
#define M 8
#define VACIA -1
#define BORRADA -2
#define OCUPADA -3

using namespace std;

struct ranuraHash{
    char* termino;
    string significado;
    unsigned int consultas;
    bool signVacio;
    int estado;
};

struct ranurasLimp{
    char* termino;
    unsigned int consultas;
};

/*****
*   void heapy
******
*   ordena y crea un maxHeap con el arreglo entregado
******
*   Input:
*       ranurasLimp* ranurasAlimpiar : arreglo correspondiente a las ranuras de la HashTable que contiene el termino
*                                      y sus consultas respectivas
*       int i : indice de la raíz, iteración del ciclo con cual se llamó a la función
******
*   Return:
*       void, no retorna
*****/

void heapy(ranurasLimp* ranurasAlimpiar, int i){
    int mayor = i;
    int izq = 2*i + 1;
    int der = 2*i + 2;
    
    if (izq<M && ranurasAlimpiar[izq].consultas > ranurasAlimpiar[mayor].consultas){
        mayor = izq;
    }
    if (der<M && ranurasAlimpiar[der].consultas > ranurasAlimpiar[mayor].consultas){
        mayor = der;
    }
    if(mayor != i){
        swap(ranurasAlimpiar[i], ranurasAlimpiar[mayor]);
        heapy(ranurasAlimpiar, mayor);
    }
}

/*****
*   void heapSort
******
*   ordena el arreglo entregado usando maxHeaps y cambiando posiciones del arreglo segun sea necesario
******
*   Input:
*       ranurasLimp* ranurasAlimpiar : arreglo correspondiente a las ranuras de la HashTable que contiene el termino
*                                      y sus consultas respectivas       
******
*   Return:
*       void, no retorna
*****/

void heapSort(ranurasLimp* ranurasAlimpiar){
    int i;
    for (i = M/2 -1; i>=0; i--){
        heapy(ranurasAlimpiar, i);
    }
    for (i = M - 1; i > 0; i--){
        swap(ranurasAlimpiar[0], ranurasAlimpiar[i]);
        heapy(ranurasAlimpiar, i);
    }
}

/*****
*   unsigned int folder
******
*   transforma el término en una clave de tipo entero que posteriormente se procesará, esta asignación
*   de numero entero se hace a través del método de plegamiento
******
*   Input:
*       string termino : termino que se desea plegar     
******
*   Return:
*       unsigned int, clave entera correspondiente al termino entregado
*****/

unsigned int folder(string termino){
    int len, i;
    len = termino.length();
    len = strlen(termino.c_str())/4;
    unsigned int sum = 0;
    for (i = 0; i < len; i++){
        sum += (int)termino[i];
    }
    return sum;
}

class CacheDiccionario{
    private:
        unsigned int consultasTotales;
        unsigned int signConocidos;
        unsigned int signDesconocidos;
        unsigned int limpiezas; //limpiezas totales
        unsigned int encontrados; //términos encontrados al realizar búsqueda
        unsigned int noEncontrados; // cantidad de veces que no se encontraron términos
        unsigned int accesos; //cantidad de accesos a ranuras del hash
        unsigned int ranurasOcupadas;
        unsigned int colisionesMax; //limite para controlar busquedas

        ranuraHash HashTable[M]; //hash table relacionada al TDA de la caché

        unsigned int hashFunc(int foldedTermino); //función de hash

        unsigned int probing(int key, int index); //función p para reubicar colisiones (debe ser por hash cerrado, hash cuadrático puede servir para facilitar trabajo)

        void cleaner();
    public:
        CacheDiccionario(){
            consultasTotales = 0;
            signConocidos = 0;
            signDesconocidos = 0;
            limpiezas = 0;
            encontrados = 0;
            noEncontrados = 0;
            accesos = 0;
            ranurasOcupadas = 0;
            colisionesMax = 0;
            for (int i = 0; i<M; i++){
                HashTable[i].termino = new char[32];
                HashTable[i].signVacio = true;
                HashTable[i].significado = "";
                HashTable[i].consultas = 0;
                HashTable[i].estado = VACIA;
                }
        };
        ~CacheDiccionario(){
            for(int i = 0; i<M; i++){
                delete[] HashTable[i].termino; 
            }
        };
        bool query(string termino, string& significado); //consultar ranura de la HT
        void insert(string termino, string significado); 
        void querystats(int& total, int& conocidos, int& desconocidos);
        void perfstats(int& accesses, int& hits, int& misses, int& cleanups);
        void printHT();
};

/*****
*   unsigned int probing
******
*   aplica resolución de colisiones a partir de hashing cuadrático simple
******
*   Input:
*       int key : clave retornada por el primer hash
*       int index : indice de la iteración de ciclo con el cual se llamo, indicando numero de colisiones
******
*   Return:
*       unsigned int, resolución de colisiones resultante a partir del numero de iteración entregada
*****/

unsigned int CacheDiccionario::probing(int key, int index){
    return index*index;
}   

/*****
*   void cleaner
******
*   Función que limpia la tabla hash del diccionario en caso de ser necesario, borrando la mitad de elementos totales que
*   cuenten con menor cantidad de consultas
******
*   Input:
*       no recibe input
******
*   Return:
*       void, no retorna
*****/

void CacheDiccionario::cleaner(){
    int i, o, foldTerm, pos, inicio, optimizador, ranBorradas;
    ranurasLimp* limpiador;
    string termino, str;
    limpiador = new ranurasLimp[M];
    optimizador = 0;

    for (i = 0; i < M; i++){
        limpiador[i].termino = new char[32];
        limpiador[i].consultas = 0;
    }

    for (i = 0; i < M; i++){
        termino = HashTable[i].termino;
        strcpy(limpiador[i].termino, termino.c_str());
        limpiador[i].consultas = HashTable[i].consultas;
    }
    heapSort(limpiador);

    for (i = 0; i < M; i++){
        cout<<limpiador[i].termino<<" : "<<limpiador[i].consultas<<endl;
    }
    
    ranBorradas = 0;
    for (i = M/2; i<M; i++){
        optimizador = 1;
        str = limpiador[i].termino;
        foldTerm = folder(str);
        pos = inicio = hashFunc(foldTerm);
        for (o = 0; HashTable[pos].estado != VACIA && HashTable[pos].termino != str; o++){
            if (optimizador > 32){
                pos = (inicio + o) % M;
            }else{ 
                pos = (inicio + probing(foldTerm, o)) % M;
                optimizador++;
            }
        }
        if (HashTable[pos].termino == str){
            ranBorradas++;
            delete[] HashTable[pos].termino;
            HashTable[pos].termino = new char[32];          
            HashTable[pos].significado = "";
            HashTable[pos].consultas = 0;
            HashTable[pos].signVacio = true;
            HashTable[pos].estado = BORRADA;        
        }
    }
    for (i = 0; i<M; i++){
        delete[] limpiador[i].termino;
    }
    delete[] limpiador;

    ranurasOcupadas = ranurasOcupadas - ranBorradas;
}

/*****
*   void printHT
******
*   imprime la HashTable del diccionario
******
*   Input:
*       no recibe input       
******
*   Return:
*       void, no retorna
*****/

void CacheDiccionario::printHT(){
    cout<<consultasTotales<<":"<<signConocidos<<":"<<signDesconocidos<<":"<<limpiezas<<":"<<encontrados<<":"<<noEncontrados<<":"<<accesos<<endl;
    for (int i = 0; i < M; i++){
        cout<<i<< " : "<<HashTable[i].termino<<" : "<<HashTable[i].significado<<" : "<<" : "<<HashTable[i].signVacio<<" : "<<HashTable[i].estado<<" : "<<HashTable[i].consultas<<endl; 
    }

}

/*****
*   unsigned int hashFunc
******
*   asigna una posición en la HashTable a través de método de cuadrado medio
******
*   Input:
*       int foldedTermino : clave entera correspondiente a un término      
******
*   Return:
*       unsigned int, ranura de la HashTable asignada por método de cuadrado medio a un término específico previamente plegado
*****/

unsigned int CacheDiccionario::hashFunc(int foldedTermino){
    int claveCuadrada, len, i, hashPos;
    if(foldedTermino == 0){
        return 0;
    }
    claveCuadrada = (foldedTermino*foldedTermino);
    string valorMedio, strCuadrada;
    strCuadrada = to_string(claveCuadrada); //transformar en string el valor de la clave al cuadrado para iterar sobre ella
    len = strlen(strCuadrada.c_str());
    for (i = 0; i<len; i++){
        if((i >= (len/2 - 1)) && (i <= len/2)){
            valorMedio += strCuadrada[i]; //toma el término central y el anterior y lo introduce al string
        }
    }
    hashPos = stoi(valorMedio) % M; //toma el valor cuadrado medio y lo divide por la cantidad de ranuras que tenemos, el módulo es la posición indicada 
    return hashPos;
}

/*****
*   void insert
******
*   inserta un término y su significado en una ranura de la HashTable y, por lo tanto, al diccionario
******
*   Input:
*       string termino : termino que se desea insertar en el diccionario
*       string significado : significado correspondiente al termino que se desea almacecar
******
*   Return:
*       void, no retorna
*****/

void CacheDiccionario::insert(string termino, string significado){
    int claveInt;
    unsigned int colisiones;
    colisiones = 0;
    claveInt = folder(termino);
    int inicio, i; 
    int optimizador = 1;
    string signAux;
    if(ranurasOcupadas == M){
        if((query(termino, signAux)) == false){
            //cout<<"REALIZANDO LIMPIEZA"<<endl;
            cleaner();
            limpiezas++;
        }
    }
    int pos = inicio = hashFunc(claveInt);
    //accesos++;
    for (i = 1; HashTable[pos].estado != VACIA && HashTable[pos].estado != BORRADA && HashTable[pos].termino != termino; i++){
        //accesos++;
        colisiones++;
        if(optimizador > 32){
            pos = (inicio + i)%M;
        }else{
            pos = (inicio + probing(pos, i)) % M;
            optimizador++;
        }
    }
    if (HashTable[pos].termino == termino){
        HashTable[pos].significado = significado;
        if (significado == ""){
            HashTable[pos].signVacio = true;
        }else{
            HashTable[pos].signVacio = false;
        }
    }
    else{
        strcpy(HashTable[pos].termino, termino.c_str());
        HashTable[pos].significado = significado;
        HashTable[pos].estado = OCUPADA;
        if (significado == ""){
            HashTable[pos].signVacio = true;
        }else{
            HashTable[pos].signVacio = false;
        }
        ranurasOcupadas++;
        if(colisiones > colisionesMax){
            colisionesMax = colisiones;
        }
    }
}

/*****
*   bool query
******
*   consulta por un término y retorna su significado por referencia si el término existe, 
*   en el caso de no existir en la tabla, retorna un string vacío por referencia y un valor falso
*   indicando que el término no se encuentra en la tabla
******
*   Input:
*       string termino : termino que se desea consultar en el diccionario
*       string& significado : paso por referencia de una variable donde se almacenará el significado del término en caso de encontrarse
******
*   Return:
*       bool, valor que indica la existencia del término en la HashTable
*****/

bool CacheDiccionario::query(string termino, string &significado){
    consultasTotales++;
    int inicio, i;
    unsigned int colisiones = 0;
    int foldedTermino = folder(termino);
    int pos = inicio = hashFunc(foldedTermino);
    int optimizador = 0;
    accesos++;
    for(i = 1; HashTable[pos].estado != VACIA && HashTable[pos].termino != termino; i++){
        colisiones++;
        accesos++;
        if(optimizador > 32){
            pos = (inicio + i) % M;
        }else{ 
            optimizador++; 
            pos = (inicio + probing(foldedTermino, i)) % M;
        }
        if(colisiones > colisionesMax){
            break;
        }
    }
    if (HashTable[pos].termino == termino){
        HashTable[pos].consultas += 1;
        significado = HashTable[pos].significado; 
        if (significado != ""){
            signConocidos++;
        }else{
            signDesconocidos++;
        }
        encontrados++;
        return true;
    }
    else{
        signDesconocidos++;
        noEncontrados++;
        significado = "";
        return false;
    }
}

/*****
*   void queryStats
******
*   indica las estadísticas de las consultas del diccionario (total de consultas, significados conocidos y desconocidos)
*   retornando por referencia los valores respectivos
******
*   Input:
*       int& total : paso por referencia de la variable donde se almacenará el total de consultas del diccionario
*       int& conocidos : paso por referencia de la variable donde se almacenará la cantidad de significados conocidos del diccionario
*       int& desconocidos : paso por referencia de la variable donde se almacenará la cantidad de significados desconocidos del diccionario       
******
*   Return:
*       void, no retorna
*****/

void CacheDiccionario::querystats(int &total, int &conocidos, int &desconocidos){
    total = consultasTotales;
    conocidos = signConocidos;
    desconocidos = signDesconocidos;
}

/*****
*   void perfStats
******
*   entrega estadísticas del rendimiento del diccionario
******
*   Input:
*       int& accesses : paso por referencia de la variable donde se almacenará el total de accesos realizados
*                       a la HashTable     
*       int& hits : paso por referencia de la variable donde se almacenará la cantidad de veces que se encontró
*                   un término consultado
*       int& misses : paso por referencia de la variable donde se almacenará la cantidad de veces que no se encontró
*                     un término consultado
*       int& cleanups : paso por referencia de la variable donde se almacenará la cantidad de limpiezas realizadas a la
*                       HashTable del diccionario
******
*   Return:
*       void, no retorna
*****/

void CacheDiccionario::perfstats(int& accesses, int& hits, int& misses, int& cleanups){
    accesses = accesos;
    hits = encontrados;
    misses = noEncontrados;
    cleanups = limpiezas;
}
