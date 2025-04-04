#include <stdio.h>
#include <stdlib.h>

// Declaración Nodo
struct nodo {
    int valor;
    struct nodo *sig; // NULL
};

// Punteros globales
struct nodo *cab = NULL, *aux = NULL, *ultimo = NULL;

// Función para mostrar los nodos
void mostrarNodos() {
    for (aux = cab; aux != NULL; aux = aux->sig) {
        printf("%d <- Valor del Nodo\n", aux->valor);
    }
}

// Función para crear un nodo
void crearNodo() {
    aux = (struct nodo *)malloc(sizeof(struct nodo));
    if (aux == NULL) {
        printf("Error al asignar memoria\n");
        return;
    }
    
    printf("Registre el valor: ");
    scanf("%d", &aux->valor);
    aux->sig = NULL;
    
    if (cab == NULL) {
        cab = aux;
    } else {
        ultimo = cab;
        while (ultimo->sig != NULL) {
            ultimo = ultimo->sig;
        }
        ultimo->sig = aux;
    }
}

// Función para buscar un valor en la lista
void buscar() {
    int aguja;
    int contador = 0;
    printf("Cual es el valor a buscar: ");
    scanf("%d", &aguja);
    
    for (aux = cab; aux != NULL; aux = aux->sig) {
        if (aguja == aux->valor) {
            contador++;
        }
    }
    
    if (contador == 0) {
        printf("Pailas, no se encontro el valor en el arreglo FIFO.\n");
    } else {
        printf("Felicidades!!, Se encontro el valor en el arreglo FIFO. En %d ocasiones.\n", contador);
    }
}

int main() {
    int opc;
    do {
        printf("1. Registrar Nodo\n");
        printf("2. Mostrar Nodos\n");
        printf("3. Buscar Nodo\n");
        printf("4. Salir\n");
        scanf("%d", &opc);
        
        switch (opc) {
            case 1: crearNodo(); break;
            case 2: mostrarNodos(); break;
            case 3: buscar(); break;
        }
    } while (opc != 4);
    
    return 0;
}
