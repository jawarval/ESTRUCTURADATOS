#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura de cada nodo del árbol
struct Nodo {
    char nombre[100];
    int anio;
    char genero[50];
    float recaudacion;
    struct Nodo* izquierda;
    struct Nodo* derecha;
};

// Función para crear un nuevo nodo
struct Nodo* crearNodo(char nombre[], int anio, char genero[], float recaudacion) {
    struct Nodo* nuevo = (struct Nodo*)malloc(sizeof(struct Nodo));
    if (nuevo == NULL) {
        printf("Error al asignar memoria\n");
        exit(1);
    }
    strcpy(nuevo->nombre, nombre);
    nuevo->anio = anio;
    strcpy(nuevo->genero, genero);
    nuevo->recaudacion = recaudacion;
    nuevo->izquierda = NULL;
    nuevo->derecha = NULL;
    return nuevo;
}

// Función para insertar un nodo en el árbol (por año)
struct Nodo* insertar(struct Nodo* raiz, char nombre[], int anio, char genero[], float recaudacion) {
    if (raiz == NULL) {
        return crearNodo(nombre, anio, genero, recaudacion);
    }

    if (anio <= raiz->anio) {
        raiz->izquierda = insertar(raiz->izquierda, nombre, anio, genero, recaudacion);
    } else {
        raiz->derecha = insertar(raiz->derecha, nombre, anio, genero, recaudacion);
    }

    return raiz;
}

// Recorrido inorden: izquierda - nodo - derecha
void inorden(struct Nodo* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierda);
        printf("Película: %s | Año: %d | Género: %s | Recaudación: %.1f millones\n",
               raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
        inorden(raiz->derecha);
    }
}

int main() {
    struct Nodo* raiz = NULL;

    // Inserción de películas de prueba
    raiz = insertar(raiz, "Titanic", 1997, "Romance", 2200.0);
    raiz = insertar(raiz, "Avengers: Endgame", 2019, "Acción", 2798.0);
    raiz = insertar(raiz, "El Padrino", 1972, "Crimen", 245.0);
    raiz = insertar(raiz, "Shrek", 2001, "Animación", 484.4);

    printf("Recorrido INORDEN del árbol:\n");
    inorden(raiz);

    return 0;
}
