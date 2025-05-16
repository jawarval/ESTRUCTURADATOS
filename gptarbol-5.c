//Jairo Walinton Ramirez Valencia
//yeimy Alejandra Berrio Gonzalez
#include <stdio.h>// Para entrada/salida estandar (printf, scanf)
#include <stdlib.h>// Para gestion de memoria dinamica (malloc, free) y qsort
#include <string.h>// Para manipulacion de cadenas (strcpy, strcmp)

// Definicion de estructura para representar una pelicula en el nodo del arbol
struct Nodo {
    char nombre[100];            // Nombre de la pelicula
    int anio;                    // Anio de realizacion
    char genero[50];            // Genero de la pelicula
    float recaudacion;          // Dinero recaudado en millones
    struct Nodo* izquierda;     // Puntero al hijo izquierdo
    struct Nodo* derecha;       // Puntero al hijo derecho
};

// Definicion del maximo de peliculas posibles para ordenar
#define MAX_PELICULAS 100

// Arreglo de punteros para guardar todas las peliculas insertadas
struct Nodo* listaPeliculas[MAX_PELICULAS];
int totalPeliculas = 0; // Contador de peliculas totales insertadas

// Funcion para crear un nuevo nodo con los datos de la pelicula
struct Nodo* crearNodo(char nombre[], int anio, char genero[], float recaudacion) {
    struct Nodo* nuevo = (struct Nodo*)malloc(sizeof(struct Nodo)); // Reservar memoria
    strcpy(nuevo->nombre, nombre);     // Copiar nombre
    nuevo->anio = anio;                // Asignar anio
    strcpy(nuevo->genero, genero);     // Copiar genero
    nuevo->recaudacion = recaudacion;  // Asignar recaudacion
    nuevo->izquierda = NULL;           // Inicializar punteros
    nuevo->derecha = NULL;
    return nuevo;                      // Retornar el nodo creado
}

// Funcion para insertar una pelicula en el arbol segun el anio
struct Nodo* insertar(struct Nodo* raiz, char nombre[], int anio, char genero[], float recaudacion) {
    if (raiz == NULL) {
        return crearNodo(nombre, anio, genero, recaudacion); // Si el arbol esta vacio, crear nodo
    }
    if (anio < raiz->anio) {
        raiz->izquierda = insertar(raiz->izquierda, nombre, anio, genero, recaudacion); // Insertar a la izquierda
    } else if (anio > raiz->anio) {
        raiz->derecha = insertar(raiz->derecha, nombre, anio, genero, recaudacion); // Insertar a la derecha
    } else {
        raiz->izquierda = insertar(raiz->izquierda, nombre, anio, genero, recaudacion); // Si es igual, va a la izquierda
    }
    return raiz; // Retornar la raiz del arbol
}

// Recorrido Inorden: izquierda - nodo - derecha
void inorden(struct Nodo* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierda);
        printf("Nombre: %s, Anio: %d, Genero: %s, Recaudacion: %.1f\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
        inorden(raiz->derecha);
    }
}

// Recorrido Preorden: nodo - izquierda - derecha
void preorden(struct Nodo* raiz) {
    if (raiz != NULL) {
        printf("Nombre: %s, Anio: %d, Genero: %s, Recaudacion: %.1f\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
        preorden(raiz->izquierda);
        preorden(raiz->derecha);
    }
}

// Recorrido Posorden: izquierda - derecha - nodo
void posorden(struct Nodo* raiz) {
    if (raiz != NULL) {
        posorden(raiz->izquierda);
        posorden(raiz->derecha);
        printf("Nombre: %s, Anio: %d, Genero: %s, Recaudacion: %.1f\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
    }
}

// Funcion para buscar una pelicula por nombre
void buscarPorNombre(struct Nodo* raiz, char nombre[]) {
    if (raiz != NULL) {
        if (strcmp(raiz->nombre, nombre) == 0) {
            printf("Pelicula encontrada:\n");
            printf("Nombre: %s, Anio: %d, Genero: %s, Recaudacion: %.1f\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
        }
        buscarPorNombre(raiz->izquierda, nombre);
        buscarPorNombre(raiz->derecha, nombre);
    }
}

// Funcion para mostrar todas las peliculas de un genero especifico
void mostrarPorGenero(struct Nodo* raiz, char genero[]) {
    if (raiz != NULL) {
        mostrarPorGenero(raiz->izquierda, genero);
        if (strcmp(raiz->genero, genero) == 0) {
            printf("Nombre: %s, Anio: %d, Recaudacion: %.1f\n", raiz->nombre, raiz->anio, raiz->recaudacion);
        }
        mostrarPorGenero(raiz->derecha, genero);
    }
}

// Funcion para recolectar todas las peliculas del arbol en una lista
void recolectarPeliculas(struct Nodo* raiz) {
    if (raiz != NULL) {
        recolectarPeliculas(raiz->izquierda);
        if (totalPeliculas < MAX_PELICULAS) {
            listaPeliculas[totalPeliculas++] = raiz;
        }
        recolectarPeliculas(raiz->derecha);
    }
}

// Funcion de comparacion para ordenar por recaudacion ascendente
int comparar(const void* a, const void* b) {
    struct Nodo* p1 = *(struct Nodo**)a;
    struct Nodo* p2 = *(struct Nodo**)b;
    if (p1->recaudacion < p2->recaudacion) return -1;
    if (p1->recaudacion > p2->recaudacion) return 1;
    return 0;
}

// Funcion para mostrar las 3 peliculas con menor recaudacion
void mostrarFracasosTaquilleros(struct Nodo* raiz) {
    totalPeliculas = 0; // Reiniciar el contador
    recolectarPeliculas(raiz); // Llenar arreglo con peliculas del arbol
    qsort(listaPeliculas, totalPeliculas, sizeof(struct Nodo*), comparar); // Ordenar

    int mostrar = totalPeliculas < 3 ? totalPeliculas : 3;
    printf("3 fracasos taquilleros:\n");
    for (int i = 0; i < mostrar; i++) {
        printf("Nombre: %s, Recaudacion: %.1f\n", listaPeliculas[i]->nombre, listaPeliculas[i]->recaudacion);
    }
}

// Funcion principal del programa
int main() {
    struct Nodo* raiz = NULL; // Inicializar arbol vacio
    int opcion;
    char nombre[100], genero[50];
    int anio;
    float recaudacion;

    do {
        // Mostrar menu de opciones
        printf("\n--- MENU ---\n");
        printf("1. Insertar pelicula\n");
        printf("2. Mostrar Inorden\n");
        printf("3. Mostrar Preorden\n");
        printf("4. Mostrar Posorden\n");
        printf("5. Buscar pelicula por nombre\n");
        printf("6. Mostrar peliculas por genero\n");
        printf("7. Mostrar 3 fracasos taquilleros\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer

        switch(opcion) {
            case 1:
                printf("Ingrese nombre: ");
                fgets(nombre, 100, stdin);// Lee una línea de texto con espacios desde el teclado
                nombre[strcspn(nombre, "\n")] = 0;// Elimina el salto de línea al final
                printf("Ingrese anio: ");
                scanf("%d", &anio);
                getchar();//Limpia el buffer de entrada para evitar errores al usar fgets después
                printf("Ingrese genero: ");
                fgets(genero, 50, stdin);// Lee el género con espacios
                genero[strcspn(genero, "\n")] = 0;// Elimina el salto de línea
                printf("Ingrese recaudacion: ");
                scanf("%f", &recaudacion);// Lee el valor de recaudación en millones
                raiz = insertar(raiz, nombre, anio, genero, recaudacion);// Inserta la película en el árbol
                break;
            case 2:
                printf("Recorrido Inorden:\n");
                inorden(raiz);// Llama al recorrido inorden del árbol (izquierda - raíz - derecha)
                break;
            case 3:
                printf("Recorrido Preorden:\n");
                preorden(raiz);// Llama al recorrido preorden (raíz - izquierda - derecha)
                break;
            case 4:
                printf("Recorrido Posorden:\n");
                posorden(raiz);// Llama al recorrido posorden (izquierda - derecha - raíz)
                break;
            case 5:
                printf("Ingrese nombre de la pelicula a buscar: ");
                fgets(nombre, 100, stdin);// Lee el nombre de la película a buscar
                nombre[strcspn(nombre, "\n")] = 0;// Elimina el salto de línea
                buscarPorNombre(raiz, nombre);// Busca e imprime información si se encuentra
                break;
            case 6:
                printf("Ingrese genero: ");
                fgets(genero, 50, stdin);// Lee el género
                genero[strcspn(genero, "\n")] = 0;// Elimina el salto de línea
                mostrarPorGenero(raiz, genero);// Muestra todas las películas de ese género
                break;
            case 7:
                mostrarFracasosTaquilleros(raiz);// Llama a la función que muestra películas con baja recaudación
                break;
            case 0:
                printf("Saliendo del programa\n");// Mensaje de salida
                break;
            default:
                printf("Opcion no valida\n");// Opción no reconocida
        }
    } while(opcion != 0);// Repite el menú hasta que el usuario ingrese 0

    return 0;
}