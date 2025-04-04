/*
*JAIRO WALINTON RAMIREZ VALENCIA
*JHON EDUER MOSQUERA CANGA
*/
#include <stdio.h>
#include <malloc.h>

//Declaracion Nodo
struct nodo {
    int valor;
    struct nodo *sig;//NULL
};
struct nodo *top, *aux, *aux2;

int crearNodo(){    
    aux = ((struct nodo *) malloc(sizeof(struct nodo)));
    printf("Registre el valor: ");
    scanf("%d", &aux->valor);
    
    if(top==NULL){
        top = aux;
        top->sig = NULL;
    } else {
        aux->sig = top;
        top = aux;
    }
    aux = NULL;
    free(aux);
}

int mostrarNodos(){
    for(aux=top; aux!=NULL; aux=aux->sig){
        printf("Nodo: %d\n", aux->valor);        
    }
}

int main(){
    int opc;
    do {
        printf("1. Registrar Nodo\n");
        printf("2. Mostrar Nodos\n");
        printf("3. Salir\n");
        scanf("%d", &opc);
        switch (opc)
        {
            case 1: crearNodo(); break;
            case 2: mostrarNodos(); break;
        }
    }while(opc!=3);
}