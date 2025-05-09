#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura del nodo
typedef struct Nodo {
    char nombre[100];
    int anio;
    char genero[50];
    float recaudacion;
    struct Nodo* izquierdo;
    struct Nodo* derecho;
} Nodo;

// Crear nuevo nodo
Nodo* crearNodo(const char* nombre, int anio, const char* genero, float recaudacion) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("Error de memoria.\n");
        exit(1);
    }
    strcpy(nuevo->nombre, nombre);
    nuevo->anio = anio;
    strcpy(nuevo->genero, genero);
    nuevo->recaudacion = recaudacion;
    nuevo->izquierdo = nuevo->derecho = NULL;
    return nuevo;
}

// Insertar nodo en el arbol (ordenado por anio)
Nodo* insertar(Nodo* raiz, const char* nombre, int anio, const char* genero, float recaudacion) {
    if (raiz == NULL) {
        return crearNodo(nombre, anio, genero, recaudacion);
    }
    if (anio < raiz->anio)
        raiz->izquierdo = insertar(raiz->izquierdo, nombre, anio, genero, recaudacion);
    else
        raiz->derecho = insertar(raiz->derecho, nombre, anio, genero, recaudacion);
    return raiz;
}

// Mostrar informacion individual de una pelicula
void mostrar(Nodo* nodo) {
    printf("========== PELICULA ==========\n");
    printf("Nombre           : %s\n", nodo->nombre);
    printf("Anio de estreno  : %d\n", nodo->anio);
    printf("Genero           : %s\n", nodo->genero);
    printf("Recaudacion (USD): %.2f millones\n", nodo->recaudacion);
    printf("==============================\n\n");
}

// Recorridos
void inorden(Nodo* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierdo);
        mostrar(raiz);
        inorden(raiz->derecho);
    }
}

void preorden(Nodo* raiz) {
    if (raiz != NULL) {
        mostrar(raiz);
        preorden(raiz->izquierdo);
        preorden(raiz->derecho);
    }
}

void posorden(Nodo* raiz) {
    if (raiz != NULL) {
        posorden(raiz->izquierdo);
        posorden(raiz->derecho);
        mostrar(raiz);
    }
}

// Liberar memoria del arbol
void liberar(Nodo* raiz) {
    if (raiz != NULL) {
        liberar(raiz->izquierdo);
        liberar(raiz->derecho);
        free(raiz);
    }
}

// Menu principal
void menu() {
    printf("\n======= MENU DE PELICULAS =======\n");
    printf("1. Ingresar pelicula (anio, genero, dinero recaudado en millones de dolares)\n");
    printf("2. Mostrar en INORDEN (por anio)\n");
    printf("3. Mostrar en PREORDEN\n");
    printf("4. Mostrar en POSORDEN\n");
    printf("5. Salir\n");
    printf("Seleccione una opcion: ");
}

int main() {
    Nodo* raiz = NULL;
    int opcion;
    char nombre[100], genero[50];
    int anio;
    float recaudacion;

    do {
        menu();
        scanf("%d", &opcion);
        getchar(); // Limpiar buffer

        switch (opcion) {
            case 1:
                printf("\n--- Ingresar nueva pelicula ---\n");
                printf("Nombre de la pelicula: ");
                fgets(nombre, sizeof(nombre), stdin);
                nombre[strcspn(nombre, "\n")] = '\0';

                printf("Genero: ");
                fgets(genero, sizeof(genero), stdin);
                genero[strcspn(genero, "\n")] = '\0';

                printf("Anio de realizacion: ");
                scanf("%d", &anio);

                printf("Dinero recaudado (millones de dolares): ");
                scanf("%f", &recaudacion);

                raiz = insertar(raiz, nombre, anio, genero, recaudacion);
                printf("Pelicula insertada correctamente.\n");
                break;

            case 2:
                printf("\nPeliculas en INORDEN:\n\n");
                inorden(raiz);
                break;

            case 3:
                printf("\nPeliculas en PREORDEN:\n\n");
                preorden(raiz);
                break;

            case 4:
                printf("\nPeliculas en POSORDEN:\n\n");
                posorden(raiz);
                break;

            case 5:
                printf("Saliendo del programa...\n");
                liberar(raiz);
                break;

            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }

    } while (opcion != 5);

    return 0;
}
