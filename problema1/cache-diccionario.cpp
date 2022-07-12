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

unsigned int CacheDiccionario::probing(int key, int index){
    return index*index;
}   

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

void CacheDiccionario::printHT(){
    cout<<consultasTotales<<":"<<signConocidos<<":"<<signDesconocidos<<":"<<limpiezas<<":"<<encontrados<<":"<<noEncontrados<<":"<<accesos<<endl;
    for (int i = 0; i < M; i++){
        cout<<i<< " : "<<HashTable[i].termino<<" : "<<HashTable[i].significado<<" : "<<" : "<<HashTable[i].signVacio<<" : "<<HashTable[i].estado<<" : "<<HashTable[i].consultas<<endl; 
    }

}
 
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

void CacheDiccionario::querystats(int &total, int &conocidos, int &desconocidos){
    total = consultasTotales;
    conocidos = signConocidos;
    desconocidos = signDesconocidos;
}

void CacheDiccionario::perfstats(int& accesses, int& hits, int& misses, int& cleanups){
    accesses = accesos;
    hits = encontrados;
    misses = noEncontrados;
    cleanups = limpiezas;
}
