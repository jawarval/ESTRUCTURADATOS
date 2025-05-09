#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición del nodo para el ABB
typedef struct Nodo {
    char nombre[100];
    int anio;
    char genero[50];
    float recaudacion;
    struct Nodo* izquierdo;
    struct Nodo* derecho;
} Nodo;

// Crear un nuevo nodo
Nodo* crearNodo(const char* nombre, int anio, const char* genero, float recaudacion) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    strcpy(nuevo->nombre, nombre);
    nuevo->anio = anio;
    strcpy(nuevo->genero, genero);
    nuevo->recaudacion = recaudacion;
    nuevo->izquierdo = NULL;
    nuevo->derecho = NULL;
    return nuevo;
}

// Insertar nodo en el ABB ordenado por año
Nodo* insertar(Nodo* raiz, const char* nombre, int anio, const char* genero, float recaudacion) {
    if (raiz == NULL) {
        return crearNodo(nombre, anio, genero, recaudacion);
    }

    if (anio < raiz->anio) {
        raiz->izquierdo = insertar(raiz->izquierdo, nombre, anio, genero, recaudacion);
    } else {
        raiz->derecho = insertar(raiz->derecho, nombre, anio, genero, recaudacion);
    }

    return raiz;
}

// Mostrar datos de una película
void mostrarPelicula(Nodo* nodo) {
    printf("Nombre: %s\n", nodo->nombre);
    printf("Genero: %s\n", nodo->genero);
    printf("Anio: %d\n", nodo->anio);
    printf("Recaudacion: %.2f millones USD\n", nodo->recaudacion);
    printf("-----------------------------\n");
}

// Recorrido inorden (izquierda, raíz, derecha)
void inorden(Nodo* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierdo);
        mostrarPelicula(raiz);
        inorden(raiz->derecho);
    }
}

// Recorrido preorden (raíz, izquierda, derecha)
void preorden(Nodo* raiz) {
    if (raiz != NULL) {
        mostrarPelicula(raiz);
        preorden(raiz->izquierdo);
        preorden(raiz->derecho);
    }
}

// Recorrido posorden (izquierda, derecha, raíz)
void posorden(Nodo* raiz) {
    if (raiz != NULL) {
        posorden(raiz->izquierdo);
        posorden(raiz->derecho);
        mostrarPelicula(raiz);
    }
}

// Liberar memoria del árbol
void liberar(Nodo* raiz) {
    if (raiz != NULL) {
        liberar(raiz->izquierdo);
        liberar(raiz->derecho);
        free(raiz);
    }
}

int main() {
    Nodo* raiz = NULL;

    // Inserción de las 15 películas
    raiz = insertar(raiz, "Avatar", 2009, "Ciencia ficcion", 2923.0);
    raiz = insertar(raiz, "Avengers: Endgame", 2019, "Superheroes", 2799.0);
    raiz = insertar(raiz, "Titanic", 1997, "Drama/Romance", 2264.0);
    raiz = insertar(raiz, "Star Wars: The Force Awakens", 2015, "Ciencia ficcion", 2071.0);
    raiz = insertar(raiz, "Avengers: Infinity War", 2018, "Superheroes", 2048.0);
    raiz = insertar(raiz, "Spider-Man: No Way Home", 2021, "Superheroes", 1921.0);
    raiz = insertar(raiz, "Jurassic World", 2015, "Aventura", 1671.0);
    raiz = insertar(raiz, "The Lion King", 2019, "Animacion/Musical", 1662.0);
    raiz = insertar(raiz, "The Avengers", 2012, "Superheroes", 1519.0);
    raiz = insertar(raiz, "Furious 7", 2015, "Accion", 1515.0);
    raiz = insertar(raiz, "Frozen II", 2019, "Animación/Fantasia", 1450.0);
    raiz = insertar(raiz, "Top Gun: Maverick", 2022, "Accion/Drama", 1495.0);
    raiz = insertar(raiz, "Barbie", 2023, "Comedia/Fantasia", 1446.0);
    raiz = insertar(raiz, "Harry Potter and the Deathly Hallows Part 2", 2011, "Fantasia", 1342.0);
    raiz = insertar(raiz, "Black Panther", 2018, "Superheroes", 1347.0);

    printf("\n🎬 PELiCULAS ORDENADAS POR INORDEN (Anio ascendente):\n\n");
    inorden(raiz);

    printf("\n🎥 PELiCULAS EN PREORDEN (Primero la raiz):\n\n");
    preorden(raiz);

    printf("\n📼 PELiCULAS EN POSORDEN (Procesa nodos al final):\n\n");
    posorden(raiz);

    liberar(raiz); // Limpieza de memoria

    return 0;
}
