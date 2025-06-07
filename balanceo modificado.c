//Jairo Walinton Ramirez Valencia
//Torres Mondragón Ander Jhovany
//Ortiz Vivas Katherine

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura de un nodo del árbol
struct Nodo {
    char nombre[100];
    int anio;
    char genero[50];
    float recaudacion;
    struct Nodo *izquierda;
    struct Nodo *derecha;
};

struct Nodo* crearNodo(char nombre[], int anio, char genero[], float recaudacion) {
    struct Nodo* nuevo = (struct Nodo*)malloc(sizeof(struct Nodo));
    if (nuevo == NULL) {
        perror("Error al asignar memoria para un nuevo nodo");
        exit(EXIT_FAILURE);
    }
    strcpy(nuevo->nombre, nombre);
    nuevo->anio = anio;
    strcpy(nuevo->genero, genero);
    nuevo->recaudacion = recaudacion;
    nuevo->izquierda = nuevo->derecha = NULL;
    return nuevo;
}

struct Nodo* insertar(struct Nodo* raiz, char nombre[], int anio, char genero[], float recaudacion) {
    if (raiz == NULL) return crearNodo(nombre, anio, genero, recaudacion);
    if (strcmp(nombre, raiz->nombre) < 0)
        raiz->izquierda = insertar(raiz->izquierda, nombre, anio, genero, recaudacion);
    else
        raiz->derecha = insertar(raiz->derecha, nombre, anio, genero, recaudacion);
    return raiz;
}

void buscarPorNombre(struct Nodo* raiz, char nombre[]) {
    if (raiz == NULL) {
        printf("Pelicula no encontrada.\n");
        return;
    }
    int cmp = strcmp(nombre, raiz->nombre);
    if (cmp == 0) {
        printf("\nNombre: %s\nAnio: %d\nGenero: %s\nRecaudacion: %.2f\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
    } else if (cmp < 0) {
        buscarPorNombre(raiz->izquierda, nombre);
    } else {
        buscarPorNombre(raiz->derecha, nombre);
    }
}

void filtrarPorGenero(struct Nodo* raiz, char genero[]) {
    if (raiz == NULL) return;
    filtrarPorGenero(raiz->izquierda, genero);
    if (strcmp(raiz->genero, genero) == 0) {
        printf("\nNombre: %s\nAnio: %d\nGenero: %s\nRecaudacion: %.2f\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
    }
    filtrarPorGenero(raiz->derecha, genero);
}

void mostrarPorAnio(struct Nodo* raiz, int anio) {
    if (raiz == NULL) return;
    mostrarPorAnio(raiz->izquierda, anio);
    if (raiz->anio == anio) {
        printf("\nNombre: %s\nAnio: %d\nGenero: %s\nRecaudacion: %.2f\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
    }
    mostrarPorAnio(raiz->derecha, anio);
}

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

int contarNodos(struct Nodo* raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNodos(raiz->izquierda) + contarNodos(raiz->derecha);
}

void llenarArreglo(struct Nodo* raiz, struct Nodo** arreglo, int* index) {
    if (raiz == NULL) return;
    llenarArreglo(raiz->izquierda, arreglo, index);
    arreglo[(*index)++] = raiz;
    llenarArreglo(raiz->derecha, arreglo, index);
}

int compararRecaudacion(const void* a, const void* b) {
    struct Nodo* nodoA = *(struct Nodo**)a;
    struct Nodo* nodoB = *(struct Nodo**)b;
    return (nodoA->recaudacion > nodoB->recaudacion) - (nodoA->recaudacion < nodoB->recaudacion);
}

void mostrarTresMenores(struct Nodo* raiz) {
    int total = contarNodos(raiz);
    if (total == 0) {
        printf("No hay peliculas registradas.\n");
        return;
    }
    struct Nodo** arreglo = malloc(total * sizeof(struct Nodo*));
    int index = 0;
    llenarArreglo(raiz, arreglo, &index);
    qsort(arreglo, total, sizeof(struct Nodo*), compararRecaudacion);
    printf("\n--- Tres peliculas con menor recaudacion ---\n");
    for (int i = 0; i < (total > 3 ? 3 : total); i++) {
        printf("\nNombre: %s\nAnio: %d\nGenero: %s\nRecaudacion: %.2f\n", arreglo[i]->nombre, arreglo[i]->anio, arreglo[i]->genero, arreglo[i]->recaudacion);
    }
    free(arreglo);
}

struct Nodo* encontrarMinimo(struct Nodo* nodo) {
    while (nodo->izquierda != NULL) nodo = nodo->izquierda;
    return nodo;
}

struct Nodo* eliminarPorNombre(struct Nodo* raiz, char nombre[]) {
    if (raiz == NULL) return NULL;
    int cmp = strcmp(nombre, raiz->nombre);
    if (cmp < 0) raiz->izquierda = eliminarPorNombre(raiz->izquierda, nombre);
    else if (cmp > 0) raiz->derecha = eliminarPorNombre(raiz->derecha, nombre);
    else {
        if (raiz->izquierda == NULL) {
            struct Nodo* temp = raiz->derecha;
            free(raiz);
            return temp;
        } else if (raiz->derecha == NULL) {
            struct Nodo* temp = raiz->izquierda;
            free(raiz);
            return temp;
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

struct Nodo* buildBalancedBST(struct Nodo** nodes, int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;
    struct Nodo* root = nodes[mid];
    root->izquierda = buildBalancedBST(nodes, start, mid - 1);
    root->derecha = buildBalancedBST(nodes, mid + 1, end);
    return root;
}

void mostrarArregloOrdenadoPorNombre(struct Nodo** arreglo, int total) {
    printf("\n--- Arreglo ordenado por nombre (inorden) ---\n");
    for (int i = 0; i < total; i++) {
        printf("\nNombre: %s\nAnio: %d\nGenero: %s\nRecaudacion: %.2f\n", 
               arreglo[i]->nombre, arreglo[i]->anio, arreglo[i]->genero, arreglo[i]->recaudacion);
    }
}

struct Nodo* balancearArbol(struct Nodo* root) {
    int count = contarNodos(root);
    if (count == 0) {
        printf("El arbol esta vacio.\n");
        return NULL;
    }

    struct Nodo** nodes = malloc(count * sizeof(struct Nodo*));
    int index = 0;
    llenarArreglo(root, nodes, &index);
    struct Nodo* balancedRoot = buildBalancedBST(nodes, 0, count - 1);
    printf("Arbol balanceado con exito.\n");

    // Mostrar el arreglo ordenado por nombre
    mostrarArregloOrdenadoPorNombre(nodes, count);

    free(nodes);
    return balancedRoot;
}

void liberarArbol(struct Nodo* raiz) {
    if (raiz == NULL) return;
    liberarArbol(raiz->izquierda);
    liberarArbol(raiz->derecha);
    free(raiz);
}

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
        printf("10. Balancear Arbol ABB y mostrar ordenado\n");
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
                raiz = insertar(raiz, nombre, anio, genero, recaudacion);
                break;
            case 2:
                printf("Ingrese nombre a buscar: ");
                fgets(nombre, 100, stdin);
                nombre[strcspn(nombre, "\n")] = 0;
                buscarPorNombre(raiz, nombre);
                break;
            case 3:
                printf("Ingrese genero a filtrar: ");
                fgets(genero, 50, stdin);
                genero[strcspn(genero, "\n")] = 0;
                filtrarPorGenero(raiz, genero);
                break;
            case 4:
                printf("Ingrese anio a mostrar: ");
                scanf("%d", &anio);
                mostrarPorAnio(raiz, anio);
                break;
            case 5:
                mostrarInOrden(raiz);
                break;
            case 6:
                mostrarPreOrden(raiz);
                break;
            case 7:
                mostrarPostOrden(raiz);
                break;
            case 8:
                mostrarTresMenores(raiz);
                break;
            case 9:
                printf("Ingrese nombre a eliminar: ");
                fgets(nombre, 100, stdin);
                nombre[strcspn(nombre, "\n")] = 0;
                raiz = eliminarPorNombre(raiz, nombre);
                break;
            case 10:
                raiz = balancearArbol(raiz);
                break;
            case 0:
                liberarArbol(raiz);
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while(opcion != 0);

    return 0;
}
