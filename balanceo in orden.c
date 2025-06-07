#include <stdio.h>
#include <stdlib.h>

// Estructura de un nodo del árbol
typedef struct Nodo {
    int dato;
    struct Nodo* izquierda;
    struct Nodo* derecha;
} Nodo;

// Función para crear un nuevo nodo
Nodo* crearNodo(int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->dato = valor;
    nuevo->izquierda = NULL;
    nuevo->derecha = NULL;
    return nuevo;
}

// Inserta en el árbol binario de búsqueda
Nodo* insertar(Nodo* raiz, int valor) {
    if (raiz == NULL) return crearNodo(valor);
    if (valor < raiz->dato)
        raiz->izquierda = insertar(raiz->izquierda, valor);
    else
        raiz->derecha = insertar(raiz->derecha, valor);
    return raiz;
}

// Paso 1: Guardar nodos en recorrido inorden
void guardarInorden(Nodo* raiz, Nodo** arreglo, int* index) {
    if (raiz == NULL) return;
    guardarInorden(raiz->izquierda, arreglo, index);
    arreglo[(*index)++] = raiz;
    guardarInorden(raiz->derecha, arreglo, index);
}

// Paso 2: Construir árbol balanceado desde arreglo ordenado
Nodo* construirBalanceado(Nodo** arreglo, int inicio, int fin) {
    if (inicio > fin) return NULL;
    int medio = (inicio + fin) / 2;
    Nodo* raiz = arreglo[medio];
    raiz->izquierda = construirBalanceado(arreglo, inicio, medio - 1);
    raiz->derecha = construirBalanceado(arreglo, medio + 1, fin);
    return raiz;
}

// Balancea el árbol dado
Nodo* balancearArbol(Nodo* raiz) {
    int n = 0;
    Nodo* temp[100]; // suponemos como máximo 100 nodos
    guardarInorden(raiz, temp, &n);
    return construirBalanceado(temp, 0, n - 1);
}

// Imprimir árbol en inorden
void imprimirInorden(Nodo* raiz) {
    if (raiz == NULL) return;
    imprimirInorden(raiz->izquierda);
    printf("%d ", raiz->dato);
    imprimirInorden(raiz->derecha);
}

// Función principal para probar
int main() {
    Nodo* raiz = NULL;

    // Inserción desbalanceada
    raiz = insertar(raiz, 5);
    raiz = insertar(raiz, 3);
    raiz = insertar(raiz, 2);
    raiz = insertar(raiz, 4);
    raiz = insertar(raiz, 1);

    printf("Árbol original (inorden): ");
    imprimirInorden(raiz);

    // Balancear el árbol
    raiz = balancearArbol(raiz);

    printf("\nÁrbol balanceado (inorden): ");
    imprimirInorden(raiz);

    return 0;
}
