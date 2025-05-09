#include <stdio.h>
#include <stdlib.h>

// Definición del nodo
typedef struct Nodo {
    int valor;
    struct Nodo* izquierdo;
    struct Nodo* derecho;
} Nodo;

// Crear un nuevo nodo
Nodo* crearNodo(int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->valor = valor;
    nuevo->izquierdo = NULL;
    nuevo->derecho = NULL;
    return nuevo;
}

// Insertar un valor en el árbol
Nodo* insertar(Nodo* raiz, int valor) {
    if (raiz == NULL) {
        return crearNodo(valor);
    }

    if (valor < raiz->valor)
        raiz->izquierdo = insertar(raiz->izquierdo, valor);
    else if (valor > raiz->valor)
        raiz->derecho = insertar(raiz->derecho, valor);

    return raiz;
}

// Buscar un valor en el árbol
int buscar(Nodo* raiz, int valor) {
    if (raiz == NULL) return 0;
    if (valor == raiz->valor) return 1;

    if (valor < raiz->valor)
        return buscar(raiz->izquierdo, valor);
    else
        return buscar(raiz->derecho, valor);
}

// Recorrido inorden
void inorden(Nodo* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierdo);
        printf("%d ", raiz->valor);
        inorden(raiz->derecho);
    }
}

// Encontrar el valor mínimo
Nodo* encontrarMinimo(Nodo* nodo) {
    while (nodo->izquierdo != NULL)
        nodo = nodo->izquierdo;
    return nodo;
}

// Eliminar un nodo
Nodo* eliminar(Nodo* raiz, int valor) {
    if (raiz == NULL) return NULL;

    if (valor < raiz->valor)
        raiz->izquierdo = eliminar(raiz->izquierdo, valor);
    else if (valor > raiz->valor)
        raiz->derecho = eliminar(raiz->derecho, valor);
    else {
        // Caso 1: sin hijos
        if (raiz->izquierdo == NULL && raiz->derecho == NULL) {
            free(raiz);
            return NULL;
        }
        // Caso 2: un hijo
        else if (raiz->izquierdo == NULL) {
            Nodo* temp = raiz->derecho;
            free(raiz);
            return temp;
        }
        else if (raiz->derecho == NULL) {
            Nodo* temp = raiz->izquierdo;
            free(raiz);
            return temp;
        }
        // Caso 3: dos hijos
        Nodo* temp = encontrarMinimo(raiz->derecho);
        raiz->valor = temp->valor;
        raiz->derecho = eliminar(raiz->derecho, temp->valor);
    }
    return raiz;
}

// Programa principal
int main() {
    Nodo* raiz = NULL;

    // Insertar elementos
    raiz = insertar(raiz, 50);
    raiz = insertar(raiz, 30);
    raiz = insertar(raiz, 70);
    raiz = insertar(raiz, 20);
    raiz = insertar(raiz, 40);
    raiz = insertar(raiz, 60);
    raiz = insertar(raiz, 80);

    printf("Recorrido inorden del ABB: ");
    inorden(raiz);
    printf("\n");

    printf("¿Esta el 40 en el arbol? %s\n", buscar(raiz, 40) ? "Si" : "No");

    raiz = eliminar(raiz, 30);
    printf("Arbol tras eliminar 30: ");
    inorden(raiz);
    printf("\n");

    return 0;
}
