#include <iostream>
#include "cache-diccionario.cpp"
#include <cstring>
using namespace std;

int main(){
    CacheDiccionario diccionario;
    char *arr;
    arr = new char[32];
    string str = "END";
    string sign;
    string comm;
    bool flag = true;
    while (flag){
        cout<<"ingrese comando: ";
        cin>>comm;
        if (comm == "END"){
            flag = false;
        }
        if (comm == "insert"){
            std::cout<<"ingrese termino: ";
            std::cin>>arr;
            std::cout<<"ingrese sign: ";
            std::cin>>sign;
            //cout<<"preinsert"<<endl;
            diccionario.insert(arr, sign);
            //cout<<"postinsert"<<endl;
            diccionario.printHT();
        }
        if (comm == "query"){
            cout<<"ingrese termino a buscar: ";
            cin>>arr;
            cout<<diccionario.query(arr, sign)<<" "<<sign<<endl;
        }    
    }

    delete[] arr;
    diccionario.printHT();
    return 0;
}