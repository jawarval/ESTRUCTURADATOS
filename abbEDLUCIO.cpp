#include <iostream>
using namespace std;

struct nodo {
    int valor;
    struct nodo *izq;
    struct nodo *der;
};

struct nodo *raiz, *aux;

void posicionar(struct nodo *nuevaraiz){
    if(aux->valor<nuevaraiz->valor){
        if(nuevaraiz->izq==NULL){
            nuevaraiz->izq = aux;
        } else {
            posicionar(nuevaraiz->izq);
        }
    } else {
        if(nuevaraiz->der==NULL){
            nuevaraiz->der = aux;
        } else {
            posicionar(nuevaraiz->der);
        }
    }
}

int registrar(){
    aux = ((struct nodo *) malloc(sizeof(struct nodo)));
    aux->izq = aux->der = NULL;
    cout<<"Cual es el valor del nodo? ";
    cin>>aux->valor;
    if(raiz==NULL){
        raiz = aux;        
    } else {
        posicionar(raiz);
    }
    aux = NULL;
    free(aux);
}
//Pre Orden - In Orden - Pos Orden
int mostrar(struct nodo *nuevaraiz){
    if(nuevaraiz!=NULL){
        cout<<"Valor: "<<nuevaraiz->valor<<endl;        
        mostrar(nuevaraiz->izq);
        mostrar(nuevaraiz->der);
    }
}

int main(){
    int opcion;
    do{
        cout<<"1. Registrar"<<endl;
        cout<<"2. Mostrar"<<endl;
        cout<<"3. Salir"<<endl;
        cout<<"Su opcion es:"<<endl;
        cin>>opcion;
        switch(opcion){
            case 1: registrar(); break;
            case 2: mostrar(raiz); break;
        };
    }while(opcion!=3);
}
