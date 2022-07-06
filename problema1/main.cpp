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
    bool flag = true;
    while (flag){
        std::cout<<"ingrese termino: ";
        std::cin>>arr;
        std::cout<<"ingrese sign: ";
        std::cin>>sign;
        if (strcmp(arr, str.c_str()) == 0){
            cout<<arr;
            cout<<str;
            flag = false;
            break;
        }
        cout<<"preinsert"<<endl;
        diccionario.insert(arr, sign);
        cout<<"postinsert"<<endl;
        diccionario.printHT();
        cout<<"end insert"<<endl;
    }


    return 0;
}