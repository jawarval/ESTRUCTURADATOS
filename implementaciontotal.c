#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura del nodo
struct Nodo {
    char nombre[100];
    int anio;
    char genero[50];
    float recaudacion;
    struct Nodo* izquierda;
    struct Nodo* derecha;
};

// Crear nuevo nodo
struct Nodo* crearNodo(char nombre[], int anio, char genero[], float recaudacion) {
    struct Nodo* nuevo = (struct Nodo*)malloc(sizeof(struct Nodo));
    if (nuevo == NULL) {
        printf("Error de memoria\n");
        exit(1);
    }
    strcpy(nuevo->nombre, nombre);
    nuevo->anio = anio;
    strcpy(nuevo->genero, genero);
    nuevo->recaudacion = recaudacion;
    nuevo->izquierda = nuevo->derecha = NULL;
    return nuevo;
}

// Insertar en el ABB
struct Nodo* insertar(struct Nodo* raiz, char nombre[], int anio, char genero[], float recaudacion) {
    if (raiz == NULL) {
        return crearNodo(nombre, anio, genero, recaudacion);
    } else {
        if (anio < raiz->anio || (anio == raiz->anio)) {
            raiz->izquierda = insertar(raiz->izquierda, nombre, anio, genero, recaudacion);
        } else {
            raiz->derecha = insertar(raiz->derecha, nombre, anio, genero, recaudacion);
        }
    }
    return raiz;
}

// Recorridos
void inorden(struct Nodo* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierda);
        printf("%s (%d) - %s - %.2f millones\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
        inorden(raiz->derecha);
    }
}

void preorden(struct Nodo* raiz) {
    if (raiz != NULL) {
        printf("%s (%d) - %s - %.2f millones\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
        preorden(raiz->izquierda);
        preorden(raiz->derecha);
    }
}

void posorden(struct Nodo* raiz) {
    if (raiz != NULL) {
        posorden(raiz->izquierda);
        posorden(raiz->derecha);
        printf("%s (%d) - %s - %.2f millones\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
    }
}

// Buscar película por nombre
void buscarPorNombre(struct Nodo* raiz, char nombreBuscado[]) {
    if (raiz == NULL) {
        printf("Película no encontrada.\n");
        return;
    }
    if (strcmp(raiz->nombre, nombreBuscado) == 0) {
        printf("Película encontrada:\n");
        printf("%s (%d) - %s - %.2f millones\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
    } else {
        buscarPorNombre(raiz->izquierda, nombreBuscado);
        buscarPorNombre(raiz->derecha, nombreBuscado);
    }
}

// Mostrar todas las películas de un género
void mostrarPorGenero(struct Nodo* raiz, char generoBuscado[]) {
    if (raiz != NULL) {
        mostrarPorGenero(raiz->izquierda, generoBuscado);
        if (strcmp(raiz->genero, generoBuscado) == 0) {
            printf("%s (%d) - %s - %.2f millones\n", raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
        }
        mostrarPorGenero(raiz->derecha, generoBuscado);
    }
}

// Encontrar 3 fracasos taquilleros (menor recaudación)
void encontrarFracasos(struct Nodo* raiz, struct Nodo* fracasos[], int* count) {
    if (raiz != NULL) {
        encontrarFracasos(raiz->izquierda, fracasos, count);

        // Insertar ordenadamente en los fracasos
        if (*count < 3) {
            fracasos[*count] = raiz;
            (*count)++;
        } else {
            // Encontrar el mayor de los fracasos y reemplazar si es necesario
            int posMayor = 0;
            for (int i = 1; i < 3; i++) {
                if (fracasos[i]->recaudacion > fracasos[posMayor]->recaudacion) {
                    posMayor = i;
                }
            }
            if (raiz->recaudacion < fracasos[posMayor]->recaudacion) {
                fracasos[posMayor] = raiz;
            }
        }

        encontrarFracasos(raiz->derecha, fracasos, count);
    }
}

// Función principal
int main() {
    struct Nodo* arbol = NULL;
    int opcion;
    char nombre[100], genero[50], nombreBuscado[100], generoBuscado[50];
    int anio;
    float recaudacion;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Insertar nueva película\n");
        printf("2. Mostrar Inorden\n");
        printf("3. Mostrar Preorden\n");
        printf("4. Mostrar Posorden\n");
        printf("5. Buscar película por nombre\n");
        printf("6. Mostrar películas por género\n");
        printf("7. Mostrar 3 fracasos taquilleros\n");
        printf("8. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar buffer

        switch (opcion) {
            case 1:
                printf("Nombre de la película: ");
                fgets(nombre, sizeof(nombre), stdin);
                nombre[strcspn(nombre, "\n")] = '\0'; // Quitar salto de línea
                printf("Año de realización: ");
                scanf("%d", &anio);
                getchar();
                printf("Género: ");
                fgets(genero, sizeof(genero), stdin);
                genero[strcspn(genero, "\n")] = '\0';
                printf("Dinero recaudado (millones de dolares): ");
                scanf("%f", &recaudacion);
                getchar();

                arbol = insertar(arbol, nombre, anio, genero, recaudacion);
                printf("Película insertada exitosamente.\n");
                break;

            case 2:
                printf("\nRecorrido Inorden:\n");
                inorden(arbol);
                break;

            case 3:
                printf("\nRecorrido Preorden:\n");
                preorden(arbol);
                break;

            case 4:
                printf("\nRecorrido Posorden:\n");
                posorden(arbol);
                break;

            case 5:
                printf("Ingrese el nombre de la película a buscar: ");
                fgets(nombreBuscado, sizeof(nombreBuscado), stdin);
                nombreBuscado[strcspn(nombreBuscado, "\n")] = '\0';
                buscarPorNombre(arbol, nombreBuscado);
                break;

            case 6:
                printf("Ingrese el género a buscar: ");
                fgets(generoBuscado, sizeof(generoBuscado), stdin);
                generoBuscado[strcspn(generoBuscado, "\n")] = '\0';
                printf("\nPelículas de género '%s':\n", generoBuscado);
                mostrarPorGenero(arbol, generoBuscado);
                break;

            case 7: {
                struct Nodo* fracasos[3] = {NULL, NULL, NULL};
                int count = 0;
                encontrarFracasos(arbol, fracasos, &count);

                printf("\nLos 3 fracasos taquilleros son:\n");
                for (int i = 0; i < count; i++) {
                    if (fracasos[i] != NULL) {
                        printf("%s (%d) - %s - %.2f millones\n",
                               fracasos[i]->nombre, fracasos[i]->anio, fracasos[i]->genero, fracasos[i]->recaudacion);
                    }
                }
                break;
            }

            case 8:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opción no válida\n");
        }

    } while (opcion != 8);

    return 0;
}
