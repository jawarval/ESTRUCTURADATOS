#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo *izq, *der;
} Nodo;

// Crear nuevo nodo
Nodo* crearNodo(int dato) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->dato = dato;
    nuevo->izq = nuevo->der = NULL;
    return nuevo;
}

// Insertar en ABB con validación de duplicados
Nodo* insertar(Nodo* raiz, int dato) {
    if (raiz == NULL) return crearNodo(dato);
    if (dato < raiz->dato)
        raiz->izq = insertar(raiz->izq, dato);
    else if (dato > raiz->dato)
        raiz->der = insertar(raiz->der, dato);
    else
        printf("⚠️  El valor %d ya existe y no será insertado.\n", dato); // Dato duplicado
    return raiz;
}

// Recorrido in-order para guardar en arreglo
void guardarInOrder(Nodo* raiz, int* arreglo, int* index) {
    if (raiz == NULL) return;
    guardarInOrder(raiz->izq, arreglo, index);
    arreglo[(*index)++] = raiz->dato;
    guardarInOrder(raiz->der, arreglo, index);
}

// Construcción de árbol balanceado desde arreglo ordenado
Nodo* construirBalanceado(int* arreglo, int inicio, int fin) {
    if (inicio > fin) return NULL;
    int medio = (inicio + fin) / 2;
    Nodo* raiz = crearNodo(arreglo[medio]);
    raiz->izq = construirBalanceado(arreglo, inicio, medio - 1);
    raiz->der = construirBalanceado(arreglo, medio + 1, fin);
    return raiz;
}

// Mostrar árbol gráficamente (de derecha a izquierda)
void imprimirArbol(Nodo* raiz, int espacio) {
    if (raiz == NULL) return;
    espacio += 10;
    imprimirArbol(raiz->der, espacio);
    printf("\n");
    for (int i = 10; i < espacio; i++) printf(" ");
    printf("%d\n", raiz->dato);
    imprimirArbol(raiz->izq, espacio);
}

// Liberar memoria del árbol
void liberarArbol(Nodo* raiz) {
    if (raiz == NULL) return;
    liberarArbol(raiz->izq);
    liberarArbol(raiz->der);
    free(raiz);
}

// Programa principal
int main() {
    Nodo* raiz = NULL;
    int n, dato;

    printf("¿Cuántos elementos desea ingresar?: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Ingrese el elemento %d: ", i + 1);
        scanf("%d", &dato);
        raiz = insertar(raiz, dato);
    }

    // Guardar en arreglo ordenado
    int* arreglo = (int*)malloc(n * sizeof(int)); // Puede sobrar espacio si hubo duplicados
    int index = 0;
    guardarInOrder(raiz, arreglo, &index);

    // Liberar árbol original
    liberarArbol(raiz);

    // Construir árbol balanceado
    raiz = construirBalanceado(arreglo, 0, index - 1);

    // Mostrar árbol balanceado como gráfico
    printf("\n🌳 Árbol balanceado (vista gráfica):\n");
    imprimirArbol(raiz, 0);

    // Liberar memoria final
    liberarArbol(raiz);
    free(arreglo);

    return 0;
}
