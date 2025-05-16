#include <stdio.h>     // Libreria estandar de entrada/salida
#include <stdlib.h>    // Libreria para funciones de memoria dinamica
#include <string.h>    // Libreria para manejo de cadenas

// Estructura de un nodo del arbol
struct Nodo {
    char nombre[100];        // Nombre de la pelicula
    int anio;                // Anio de estreno
    char genero[50];         // Genero de la pelicula
    float recaudacion;       // Monto recaudado
    struct Nodo *izquierda;  // Hijo izquierdo
    struct Nodo *derecha;    // Hijo derecho
};

// Funcion para crear un nuevo nodo con los datos ingresados
struct Nodo* crearNodo(char nombre[], int anio, char genero[], float recaudacion) {
    struct Nodo* nuevo = (struct Nodo*)malloc(sizeof(struct Nodo)); // Reserva memoria para el nodo
    strcpy(nuevo->nombre, nombre);      // Copia el nombre
    nuevo->anio = anio;                 // Asigna el anio
    strcpy(nuevo->genero, genero);      // Copia el genero
    nuevo->recaudacion = recaudacion;  // Asigna la recaudacion
    nuevo->izquierda = nuevo->derecha = NULL; // Inicializa los hijos
    return nuevo;                       // Devuelve el nodo creado
}

// Inserta un nodo en el arbol binario de busqueda
struct Nodo* insertar(struct Nodo* raiz, char nombre[], int anio, char genero[], float recaudacion) {
    if (raiz == NULL) return crearNodo(nombre, anio, genero, recaudacion); // Si arbol vacio, crea nodo
    if (strcmp(nombre, raiz->nombre) < 0)                                  // Si nombre menor, va a izquierda
        raiz->izquierda = insertar(raiz->izquierda, nombre, anio, genero, recaudacion);
    else                                                                   // Si nombre mayor o igual, va a derecha
        raiz->derecha = insertar(raiz->derecha, nombre, anio, genero, recaudacion);
    return raiz;                                                           // Retorna la raiz
}

// Busca una pelicula por nombre
void buscarPorNombre(struct Nodo* raiz, char nombre[]) {
    if (raiz == NULL) {                              // Si el arbol esta vacio
        printf("Pelicula no encontrada.\n");
        return;
    }
    if (strcmp(nombre, raiz->nombre) == 0) {         // Si se encuentra la pelicula
        printf("\nNombre: %s\nAnio: %d\nGenero: %s\nRecaudacion: %.2f\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
    } else if (strcmp(nombre, raiz->nombre) < 0) {   // Buscar en subarbol izquierdo
        buscarPorNombre(raiz->izquierda, nombre);
    } else {                                         // Buscar en subarbol derecho
        buscarPorNombre(raiz->derecha, nombre);
    }
}

// Muestra peliculas por genero
void filtrarPorGenero(struct Nodo* raiz, char genero[]) {
    if (raiz == NULL) return; // Si el arbol esta vacio
    filtrarPorGenero(raiz->izquierda, genero); // Busca en el subarbol izquierdo
    if (strcmp(raiz->genero, genero) == 0) {   // Si coincide el genero
        printf("\nNombre: %s\nAnio: %d\nGenero: %s\nRecaudacion: %.2f\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
    }
    filtrarPorGenero(raiz->derecha, genero);  // Busca en el subarbol derecho
}

// Muestra peliculas por anio
void mostrarPorAnio(struct Nodo* raiz, int anio) {
    if (raiz == NULL) return;
    mostrarPorAnio(raiz->izquierda, anio);     // Recorre izquierdo
    if (raiz->anio == anio) {                  // Si coincide anio
        printf("\nNombre: %s\nAnio: %d\nGenero: %s\nRecaudacion: %.2f\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
    }
    mostrarPorAnio(raiz->derecha, anio);      // Recorre derecho
}

// Recorridos del arbol
void mostrarInOrden(struct Nodo* raiz) {
    if (raiz == NULL) return;
    mostrarInOrden(raiz->izquierda);
    printf("\nNombre: %s\nAnio: %d\nGenero: %s\nRecaudacion: %.2f\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
    mostrarInOrden(raiz->derecha);
}

void mostrarPreOrden(struct Nodo* raiz) {
    if (raiz == NULL) return;
    printf("\nNombre: %s\nAnio: %d\nGenero: %s\nRecaudacion: %.2f\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
    mostrarPreOrden(raiz->izquierda);
    mostrarPreOrden(raiz->derecha);
}

void mostrarPostOrden(struct Nodo* raiz) {
    if (raiz == NULL) return;
    mostrarPostOrden(raiz->izquierda);
    mostrarPostOrden(raiz->derecha);
    printf("\nNombre: %s\nAnio: %d\nGenero: %s\nRecaudacion: %.2f\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
}

// Cuenta la cantidad de nodos del arbol
int contarNodos(struct Nodo* raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNodos(raiz->izquierda) + contarNodos(raiz->derecha);
}

// Llena un arreglo con los nodos para ordenarlos
void llenarArreglo(struct Nodo* raiz, struct Nodo** arreglo, int* index) {
    if (raiz == NULL) return;
    llenarArreglo(raiz->izquierda, arreglo, index);
    arreglo[(*index)++] = raiz;
    llenarArreglo(raiz->derecha, arreglo, index);
}

// Funcion para ordenar por recaudacion con qsort
int compararRecaudacion(const void* a, const void* b) {
    struct Nodo* nodoA = *(struct Nodo**)a;
    struct Nodo* nodoB = *(struct Nodo**)b;
    if (nodoA->recaudacion < nodoB->recaudacion) return -1;
    else if (nodoA->recaudacion > nodoB->recaudacion) return 1;
    return 0;
}

// Muestra las tres peliculas con menor recaudacion
void mostrarTresMenores(struct Nodo* raiz) {
    int total = contarNodos(raiz); // Cuenta los nodos
    if (total < 3) {
        printf("Hay menos de tres peliculas registradas.\n");
        return;
    }
    struct Nodo** arreglo = (struct Nodo**)malloc(total * sizeof(struct Nodo*));
    int index = 0;
    llenarArreglo(raiz, arreglo, &index);
    qsort(arreglo, total, sizeof(struct Nodo*), compararRecaudacion);
    printf("\nTres peliculas con menor recaudacion:\n");
    for (int i = 0; i < 3; i++) {
        printf("\nNombre: %s\nAnio: %d\nGenero: %s\nRecaudacion: %.2f\n", arreglo[i]->nombre, arreglo[i]->anio, arreglo[i]->genero, arreglo[i]->recaudacion);
    }
    free(arreglo); // Libera el arreglo
}

// Encuentra el nodo minimo del subarbol derecho
struct Nodo* encontrarMinimo(struct Nodo* nodo) {
    while (nodo->izquierda != NULL) nodo = nodo->izquierda;
    return nodo;
}

// Elimina un nodo por nombre
struct Nodo* eliminarPorNombre(struct Nodo* raiz, char nombre[]) {
    if (raiz == NULL) return NULL;
    int cmp = strcmp(nombre, raiz->nombre);
    if (cmp < 0) raiz->izquierda = eliminarPorNombre(raiz->izquierda, nombre);
    else if (cmp > 0) raiz->derecha = eliminarPorNombre(raiz->derecha, nombre);
    else {
        if (raiz->izquierda == NULL && raiz->derecha == NULL) {
            free(raiz); return NULL;
        } else if (raiz->izquierda == NULL) {
            struct Nodo* temp = raiz->derecha;
            free(raiz); return temp;
        } else if (raiz->derecha == NULL) {
            struct Nodo* temp = raiz->izquierda;
            free(raiz); return temp;
        } else {
            struct Nodo* sucesor = encontrarMinimo(raiz->derecha);
            strcpy(raiz->nombre, sucesor->nombre);
            raiz->anio = sucesor->anio;
            strcpy(raiz->genero, sucesor->genero);
            raiz->recaudacion = sucesor->recaudacion;
            raiz->derecha = eliminarPorNombre(raiz->derecha, sucesor->nombre);
        }
    }
    return raiz;
}

// Libera toda la memoria del arbol
void liberarArbol(struct Nodo* raiz) {
    if (raiz == NULL) return;
    liberarArbol(raiz->izquierda);
    liberarArbol(raiz->derecha);
    free(raiz);
}

// Funcion principal
int main() {
    struct Nodo* raiz = NULL;
    int opcion, anio;
    float recaudacion;
    char nombre[100], genero[50];

    do {
        printf("\n\n--- MENU ---\n");
        printf("1. Insertar pelicula\n");
        printf("2. Buscar por nombre\n");
        printf("3. Filtrar por genero\n");
        printf("4. Mostrar por anio\n");
        printf("5. Mostrar peliculas (inorden)\n");
        printf("6. Mostrar peliculas (preorden)\n");
        printf("7. Mostrar peliculas (postorden)\n");
        printf("8. Mostrar tres peliculas con menor recaudacion\n");
        printf("9. Eliminar pelicula por nombre\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch(opcion) {
            case 1:
                printf("Ingrese nombre: ");
                fgets(nombre, 100, stdin);
                nombre[strcspn(nombre, "\n")] = 0;
                printf("Ingrese anio: ");
                scanf("%d", &anio);
                getchar();
                printf("Ingrese genero: ");
                fgets(genero, 50, stdin);
                genero[strcspn(genero, "\n")] = 0;
                printf("Ingrese recaudacion: ");
                scanf("%f", &recaudacion);
                getchar();
                raiz = insertar(raiz, nombre, anio, genero, recaudacion);
                break;
            case 2:
                printf("Ingrese nombre: ");
                fgets(nombre, 100, stdin);
                nombre[strcspn(nombre, "\n")] = 0;
                buscarPorNombre(raiz, nombre);
                break;
            case 3:
                printf("Ingrese genero: ");
                fgets(genero, 50, stdin);
                genero[strcspn(genero, "\n")] = 0;
                filtrarPorGenero(raiz, genero);
                break;
            case 4:
                printf("Ingrese anio: ");
                scanf("%d", &anio);
                getchar();
                mostrarPorAnio(raiz, anio);
                break;
            case 5:
                printf("Peliculas en inorden:\n");
                mostrarInOrden(raiz);
                break;
            case 6:
                printf("Peliculas en preorden:\n");
                mostrarPreOrden(raiz);
                break;
            case 7:
                printf("Peliculas en postorden:\n");
                mostrarPostOrden(raiz);
                break;
            case 8:
                mostrarTresMenores(raiz);
                break;
            case 9:
                printf("Ingrese nombre de la pelicula a eliminar: ");
                fgets(nombre, 100, stdin);
                nombre[strcspn(nombre, "\n")] = 0;
                raiz = eliminarPorNombre(raiz, nombre);
                printf("Pelicula eliminada (si existia).\n");
                break;
            case 0:
                liberarArbol(raiz);
                printf("Programa finalizado.\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while(opcion != 0);

    return 0;
}
