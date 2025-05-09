#include <stdio.h>  // Para entrada/salida estandar (printf, scanf)
#include <stdlib.h> // Para gestion de memoria dinamica (malloc, free) y qsort
#include <string.h> // Para manipulacion de cadenas (strcpy, strcmp)
// Ya no se necesita <float.h> para FLT_MAX en este contexto

// --- Definicion de Estructuras ---

// Estructura para almacenar los datos de una pelicula
struct Pelicula {
    char nombre[100]; // Nombre de la pelicula, maximo 99 caracteres mas el caracter nulo de fin de cadena
    int anio;         // Anio de realizacion de la pelicula
    char genero[50];  // Genero de la pelicula, maximo 49 caracteres mas el caracter nulo
    float recaudacion; // Dinero recaudado en millones de dolares (ej: 3.2)
};

// Estructura del nodo del arbol binario de busqueda (ABB)
struct NodoArbol {
    struct Pelicula datosPelicula; // Contiene los datos de la pelicula para este nodo
    struct NodoArbol *izquierda;   // Puntero al hijo izquierdo (peliculas con anio menor, o igual segun la regla)
    struct NodoArbol *derecha;     // Puntero al hijo derecho (peliculas con anio mayor)
};

// --- Prototipos de Funciones (declaraciones anticipadas) ---

// Funciones del Arbol Binario de Busqueda
struct NodoArbol* crearNodo(struct Pelicula pelicula);
struct NodoArbol* insertarPelicula(struct NodoArbol* raiz, struct Pelicula pelicula);
void mostrarPelicula(struct Pelicula p);

// Funciones de Recorridos del Arbol
void recorridoInorden(struct NodoArbol* raiz);
void recorridoPreorden(struct NodoArbol* raiz);
void recorridoPosorden(struct NodoArbol* raiz);

// Funciones de Busqueda y Filtro
void buscarPeliculaPorNombre(struct NodoArbol* raiz, const char* nombreBuscado);
void mostrarPeliculasPorGenero(struct NodoArbol* raiz, const char* generoBuscado);

// NUEVAS Funciones para la logica de "Menor Recaudacion"
int contarNodos(struct NodoArbol* raiz); // Cuenta el total de peliculas en el arbol
void recopilarPeliculasEnArreglo(struct NodoArbol* raiz, struct Pelicula* arreglo, int* indice); // Llena un arreglo con las peliculas
int compararPeliculasPorRecaudacion(const void* a, const void* b); // Funcion de comparacion para qsort
void mostrarPeliculasMenorRecaudacion(struct NodoArbol* raiz, int cantidad); // Logica principal para esta funcionalidad

// Funcion para liberar la memoria del arbol
void liberarArbol(struct NodoArbol* raiz);

// Funcion auxiliar para limpiar el buffer de entrada de datos
void limpiarBufferEntrada();

// Banderas globales para funciones de busqueda
int peliculaEncontradaFlag;
int contadorPeliculasGenero;


// --- Implementacion de Funciones ---

void limpiarBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

struct NodoArbol* crearNodo(struct Pelicula pelicula) {
    struct NodoArbol* nuevoNodo = (struct NodoArbol*)malloc(sizeof(struct NodoArbol));
    if (nuevoNodo == NULL) {
        printf("Error critico: No se pudo asignar memoria para un nuevo nodo de pelicula.\n");
        return NULL;
    }
    strcpy(nuevoNodo->datosPelicula.nombre, pelicula.nombre);
    nuevoNodo->datosPelicula.anio = pelicula.anio;
    strcpy(nuevoNodo->datosPelicula.genero, pelicula.genero);
    nuevoNodo->datosPelicula.recaudacion = pelicula.recaudacion;
    nuevoNodo->izquierda = NULL;
    nuevoNodo->derecha = NULL;
    return nuevoNodo;
}

struct NodoArbol* insertarPelicula(struct NodoArbol* raiz, struct Pelicula pelicula) {
    if (raiz == NULL) {
        return crearNodo(pelicula);
    }
    if (pelicula.anio == raiz->datosPelicula.anio) {
        raiz->izquierda = insertarPelicula(raiz->izquierda, pelicula);
    } else if (pelicula.anio < raiz->datosPelicula.anio) {
        raiz->izquierda = insertarPelicula(raiz->izquierda, pelicula);
    } else {
        raiz->derecha = insertarPelicula(raiz->derecha, pelicula);
    }
    return raiz;
}

void mostrarPelicula(struct Pelicula p) {
    printf("Nombre: %s\n", p.nombre);
    printf("Anio: %d\n", p.anio);
    printf("Genero: %s\n", p.genero);
    printf("Recaudacion (millones): %.2f\n", p.recaudacion);
    printf("\n");
}

void recorridoInorden(struct NodoArbol* raiz) {
    if (raiz != NULL) {
        recorridoInorden(raiz->izquierda);
        mostrarPelicula(raiz->datosPelicula);
        recorridoInorden(raiz->derecha);
    }
}

void recorridoPreorden(struct NodoArbol* raiz) {
    if (raiz != NULL) {
        mostrarPelicula(raiz->datosPelicula);
        recorridoPreorden(raiz->izquierda);
        recorridoPreorden(raiz->derecha);
    }
}

void recorridoPosorden(struct NodoArbol* raiz) {
    if (raiz != NULL) {
        recorridoPosorden(raiz->izquierda);
        recorridoPosorden(raiz->derecha);
        mostrarPelicula(raiz->datosPelicula);
    }
}

void buscarPeliculaPorNombre(struct NodoArbol* raiz, const char* nombreBuscado) {
    if (raiz == NULL) {
        return;
    }
    if (strcmp(raiz->datosPelicula.nombre, nombreBuscado) == 0) {
        printf("Pelicula encontrada:\n");
        mostrarPelicula(raiz->datosPelicula);
        peliculaEncontradaFlag = 1;
    }
    buscarPeliculaPorNombre(raiz->izquierda, nombreBuscado);
    buscarPeliculaPorNombre(raiz->derecha, nombreBuscado);
}

void mostrarPeliculasPorGenero(struct NodoArbol* raiz, const char* generoBuscado) {
    if (raiz == NULL) {
        return;
    }
    mostrarPeliculasPorGenero(raiz->izquierda, generoBuscado);
    if (strcmp(raiz->datosPelicula.genero, generoBuscado) == 0) {
        mostrarPelicula(raiz->datosPelicula);
        contadorPeliculasGenero++;
    }
    mostrarPeliculasPorGenero(raiz->derecha, generoBuscado);
}

// --- Implementacion de NUEVAS Funciones para "Menor Recaudacion" ---

// Funcion recursiva para contar el numero total de nodos (peliculas) en el arbol.
// Recibe: la 'raiz' del arbol (o subarbol).
// Devuelve: el numero de nodos.
int contarNodos(struct NodoArbol* raiz) {
    // Caso base: si el nodo es NULL, no cuenta.
    if (raiz == NULL) {
        return 0;
    }
    // Cuenta 1 (por el nodo actual) mas la cuenta de los subarboles izquierdo y derecho.
    return 1 + contarNodos(raiz->izquierda) + contarNodos(raiz->derecha);
}

// Funcion recursiva para llenar un arreglo con todas las peliculas del arbol.
// Recibe: la 'raiz' del arbol, el 'arreglo' a llenar, y un puntero al 'indice' actual del arreglo.
// El recorrido es Inorden, pero cualquier recorrido completo serviria para recopilar todos los elementos.
void recopilarPeliculasEnArreglo(struct NodoArbol* raiz, struct Pelicula* arreglo, int* indice) {
    // Caso base: si el nodo es NULL, no hay nada que agregar.
    if (raiz == NULL) {
        return;
    }
    // Recopila del subarbol izquierdo.
    recopilarPeliculasEnArreglo(raiz->izquierda, arreglo, indice);

    // Agrega la pelicula del nodo actual al arreglo en la posicion 'indice'.
    arreglo[*indice] = raiz->datosPelicula;
    // Incrementa el indice para la proxima pelicula.
    (*indice)++;

    // Recopila del subarbol derecho.
    recopilarPeliculasEnArreglo(raiz->derecha, arreglo, indice);
}

// Funcion de comparacion necesaria para qsort.
// Compara dos peliculas basandose en su 'recaudacion'.
// Recibe: dos punteros genericos 'a' y 'b', que seran casteados a 'struct Pelicula*'.
// Devuelve:
//   - un valor negativo si la recaudacion de 'a' es menor que la de 'b'.
//   - cero si las recaudaciones son iguales.
//   - un valor positivo si la recaudacion de 'a' es mayor que la de 'b'.
int compararPeliculasPorRecaudacion(const void* a, const void* b) {
    // Castea los punteros void* a punteros struct Pelicula*.
    struct Pelicula* peliculaA = (struct Pelicula*)a;
    struct Pelicula* peliculaB = (struct Pelicula*)b;

    // Realiza la comparacion de las recaudaciones.
    if (peliculaA->recaudacion < peliculaB->recaudacion) {
        return -1; // peliculaA viene antes que peliculaB.
    } else if (peliculaA->recaudacion > peliculaB->recaudacion) {
        return 1;  // peliculaA viene despues que peliculaB.
    } else {
        return 0;  // Son iguales en terminos de recaudacion.
    }
}

// Funcion principal para mostrar las 'cantidad' peliculas con menor recaudacion.
// Recibe: la 'raiz' del arbol y la 'cantidad' de peliculas a mostrar.
void mostrarPeliculasMenorRecaudacion(struct NodoArbol* raiz, int cantidadAMostrar) {
    // Primero, se cuentan cuantos nodos (peliculas) hay en el arbol.
    int totalPeliculas = contarNodos(raiz);

    // Si no hay peliculas, se informa y se sale.
    if (totalPeliculas == 0) {
        printf("No hay peliculas en el arbol para mostrar.\n");
        return;
    }

    // Se asigna memoria dinamicamente para un arreglo que contendra todas las peliculas.
    // Se usa malloc para esto, como es requerido.
    struct Pelicula* arregloPeliculas = (struct Pelicula*)malloc(totalPeliculas * sizeof(struct Pelicula));
    // Se verifica si la asignacion de memoria fue exitosa.
    if (arregloPeliculas == NULL) {
        printf("Error: No se pudo asignar memoria para el arreglo temporal de peliculas.\n");
        return;
    }

    // Se inicializa un indice para llenar el arreglo.
    int indice = 0;
    // Se llama a la funcion que llena el 'arregloPeliculas' con los datos del arbol.
    recopilarPeliculasEnArreglo(raiz, arregloPeliculas, &indice);

    // Se ordena el 'arregloPeliculas' usando qsort.
    // qsort es una funcion estandar de C para ordenamiento rapido.
    // Parametros: el arreglo, numero de elementos, tamano de cada elemento, funcion de comparacion.
    qsort(arregloPeliculas, totalPeliculas, sizeof(struct Pelicula), compararPeliculasPorRecaudacion);

    // Se determina cuantas peliculas se van a mostrar realmente.
    // Sera 'cantidadAMostrar' o 'totalPeliculas' si hay menos peliculas que las solicitadas.
    int numRealesAMostrar = (totalPeliculas < cantidadAMostrar) ? totalPeliculas : cantidadAMostrar;

    printf("--- %d Peliculas con Menor Recaudacion ---\n", numRealesAMostrar);
    // Se muestran las peliculas del arreglo ya ordenado.
    for (int i = 0; i < numRealesAMostrar; i++) {
        printf("Top %d Menor Recaudacion:\n", i + 1);
        mostrarPelicula(arregloPeliculas[i]);
    }

    // Es crucial liberar la memoria asignada dinamicamente para evitar fugas de memoria.
    free(arregloPeliculas);
}


// --- Funcion para Liberar Memoria del Arbol ---
void liberarArbol(struct NodoArbol* raiz) {
    if (raiz == NULL) {
        return;
    }
    liberarArbol(raiz->izquierda);
    liberarArbol(raiz->derecha);
    free(raiz);
}

// --- Funcion Principal (main) ---
int main() {
    struct NodoArbol* raizArbol = NULL;
    int opcion;
    struct Pelicula peliculaTemp;
    char busquedaTexto[100];

    // YA NO SE INICIALIZAN FRACASOS GLOBALES AQUI

    do {
        printf("\n--- Menu Principal Arbol de Peliculas ---\n");
        printf("1. Agregar nueva pelicula\n");
        printf("2. Mostrar recorrido Inorden\n");
        printf("3. Mostrar recorrido Preorden\n");
        printf("4. Mostrar recorrido Posorden\n");
        printf("5. Buscar pelicula por nombre\n");
        printf("6. Mostrar peliculas por genero\n");
        // El texto del menu puede mantenerse o cambiarse. Lo dejare como antes para consistencia con la solicitud.
        printf("7. Mostrar los 3 fracasos taquilleros (menor recaudacion)\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            printf("Entrada invalida. Por favor ingrese un numero del menu.\n");
            limpiarBufferEntrada();
            opcion = -1;
            continue;
        }
        limpiarBufferEntrada();

        switch (opcion) {
            case 1:
                printf("\n--- Agregar Nueva Pelicula ---\n");
                printf("Nombre de la pelicula: ");
                scanf(" %99[^\n]", peliculaTemp.nombre);
                limpiarBufferEntrada();

                printf("Anio de realizacion: ");
                while (scanf("%d", &peliculaTemp.anio) != 1) {
                    printf("Anio invalido. Por favor ingrese un numero: ");
                    limpiarBufferEntrada();
                }
                limpiarBufferEntrada();

                printf("Genero: ");
                scanf(" %49[^\n]", peliculaTemp.genero);
                limpiarBufferEntrada();

                printf("Dinero recaudado (en millones, ej: 3.2): ");
                while (scanf("%f", &peliculaTemp.recaudacion) != 1) {
                    printf("Recaudacion invalida. Por favor ingrese un numero (ej: 3.2): ");
                    limpiarBufferEntrada();
                }
                limpiarBufferEntrada();

                raizArbol = insertarPelicula(raizArbol, peliculaTemp);
                printf("Pelicula agregada exitosamente al arbol.\n");
                break;

            case 2:
                printf("\n--- Recorrido Inorden (Anio Ascendente) ---\n");
                if (raizArbol == NULL) {
                    printf("El arbol esta vacio. No hay peliculas para mostrar.\n");
                } else {
                    recorridoInorden(raizArbol);
                }
                break;

            case 3:
                printf("\n--- Recorrido Preorden ---\n");
                if (raizArbol == NULL) {
                    printf("El arbol esta vacio.\n");
                } else {
                    recorridoPreorden(raizArbol);
                }
                break;

            case 4:
                printf("\n--- Recorrido Posorden ---\n");
                if (raizArbol == NULL) {
                    printf("El arbol esta vacio.\n");
                } else {
                    recorridoPosorden(raizArbol);
                }
                break;

            case 5:
                printf("\n--- Buscar Pelicula por Nombre ---\n");
                if (raizArbol == NULL) {
                    printf("El arbol esta vacio. No se puede buscar.\n");
                } else {
                    printf("Ingrese el nombre de la pelicula a buscar: ");
                    scanf(" %99[^\n]", busquedaTexto);
                    limpiarBufferEntrada();
                    peliculaEncontradaFlag = 0;
                    buscarPeliculaPorNombre(raizArbol, busquedaTexto);
                    if (!peliculaEncontradaFlag) {
                        printf("Pelicula con nombre '%s' no encontrada en el arbol.\n", busquedaTexto);
                    }
                }
                break;

            case 6:
                printf("\n--- Mostrar Peliculas por Genero ---\n");
                if (raizArbol == NULL) {
                    printf("El arbol esta vacio.\n");
                } else {
                    printf("Ingrese el genero a buscar: ");
                    scanf(" %49[^\n]", busquedaTexto);
                    limpiarBufferEntrada();
                    contadorPeliculasGenero = 0;
                    printf("Peliculas del genero '%s':\n", busquedaTexto);
                    mostrarPeliculasPorGenero(raizArbol, busquedaTexto);
                    if (contadorPeliculasGenero == 0) {
                        printf("No se encontraron peliculas del genero '%s'.\n", busquedaTexto);
                    }
                }
                break;

            case 7: // Mostrar los 3 fracasos taquilleros (menor recaudacion)
                // Se llama a la nueva funcion. Le pasamos 3 para mantener la funcionalidad original de "top 3".
                if (raizArbol == NULL) {
                    printf("\n--- 3 Peliculas con Menor Recaudacion ---\n");
                    printf("El arbol esta vacio. No hay peliculas para analizar.\n");
                } else {
                     // El encabezado se imprime dentro de la funcion mostrarPeliculasMenorRecaudacion
                    mostrarPeliculasMenorRecaudacion(raizArbol, 3);
                }
                break;

            case 0:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opcion no valida. Por favor, elija una opcion del menu.\n");
                break;
        }
    } while (opcion != 0);

    liberarArbol(raizArbol);
    printf("Memoria del arbol liberada. Programa terminado.\n");

    return 0;
}