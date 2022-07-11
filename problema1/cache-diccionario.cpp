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
    char termino[32];
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
    //cout<<"-------------------------------"<<endl;
    //cout<<termino<<endl;
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
        //cout<<"iteracion: "<<i<<endl;
        //cout<<aux[i]<<endl;
        sum += (int)termino[i];
    }
    //cout<<"suma es: "<<sum<<endl;
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
        unsigned int colisionesMax;

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
        ~CacheDiccionario(){};

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
    return index*index;
}   //simple quadratic probing por ahora

void CacheDiccionario::cleaner(){
    int i, o, foldTerm, pos, inicio;
    ranurasLimp* limpiador;
    limpiador = new ranurasLimp[M];
    for (i = 0; i < M; i++){
        strcpy(limpiador[i].termino, HashTable[i].termino);
        limpiador[i].consultas = HashTable[i].consultas;
    }
    heapSort(limpiador);

    
    for (i = M/2; i<M; i++){
        foldTerm = folder(limpiador[i].termino);
        pos = inicio = hashFunc(foldTerm);
        for (o = 0; HashTable[pos].estado != VACIA && HashTable[pos].termino != limpiador[i].termino; o++){
            pos = (inicio + probing(foldTerm, o)) % M;                  
        }
        if (HashTable[pos].termino == limpiador[i].termino){
            HashTable[pos].termino = NULL;          
            HashTable[pos].significado = "";
            HashTable[pos].consultas = 0;
            HashTable[pos].signVacio = true;
            HashTable[pos].estado = BORRADA;        
        }
    }
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
    unsigned int colisiones;
    colisiones = 0;
    claveInt = folder(termino);
    int inicio, i; 
    int optimizador = 1;
    if(ranurasOcupadas == M){
        cleaner();
    }
    int pos = inicio = hashFunc(claveInt);
    accesos++;
    //cout<<"line 121"<<endl;
    for (i = 1; HashTable[pos].estado != VACIA && HashTable[pos].estado != BORRADA && HashTable[pos].termino != termino; i++){
        //cout<<"colisionado"<<endl;
        accesos++;
        colisiones++;
        if(optimizador > 32){
            cout<<"lineal"<<endl;
            pos = (inicio + i)%M;
        }else{
            cout<<"optimizador: "<<optimizador<<endl;
            pos = (inicio + probing(pos, i)) % M;
            optimizador++;
        }
    //cout<<"line 125"<<endl;
    }
    if (HashTable[pos].termino == termino){
        //cout<<"termino repetido"<<endl;
        HashTable[pos].significado = significado;
        if (significado == ""){
            HashTable[pos].signVacio = true;
        }else{
            HashTable[pos].signVacio = false;
        }
    }
    else{
        cout<<"CREANDO TERMINO"<<endl;
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
    //bool* marcas;
    //bool flag;
    //marcas = new bool[M];
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
            cout<<"lineal"<<endl;
            pos = (inicio + i) % M;
        }else{ 
            cout<<"optimizador: "<<optimizador<<endl;
            optimizador++; 
            pos = (inicio + probing(foldedTermino, i)) % M;
        }
        if(colisiones > colisionesMax){
            break;
        }
        //marcas[pos] = true;
        /*for (o = 0; o<M; o++){
            flag = true;
            cout<<marcas[o]<<endl;
            if(marcas[o]!= true){
                flag = false;                
                break;
            }
        }
        if(flag == true){
            cout<<"FLAG ACTIVADA"<<endl;
            noEncontrados++;
            significado = "";
        }*/
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

// PREGUNTA PROFE: SI LAS CLAVES SON TERMINOS DE 32 CARACTERES, PODRÍA SER UNA BUENA IDEA MANEJAR LAS LLAVES DE
// LA HASH TABLE COMO ENTEROS COMO LOS PRIMEROS 2 A 4 CARACTERES? QUIZÁS GENERE MAS COLISIONES EN LOS TERMINOS
// QUE TENGAN LOS MISMOS CARACTERES, PERO FACILITA EL TRABAJO EN TERMINOS DE CASTING DE TIPOS DE DATOS
// -> BUENA IDEA, UTIL
