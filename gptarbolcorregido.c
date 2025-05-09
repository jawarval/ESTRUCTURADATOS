#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Definicion de Estructuras ---
struct Pelicula {
    char nombre[100];
    int anio;
    char genero[50];
    float recaudacion;
};

struct NodoArbol {
    struct Pelicula datosPelicula;
    struct NodoArbol *izquierda;
    struct NodoArbol *derecha;
};

// --- Prototipos de Funciones ---
struct NodoArbol* crearNodo(struct Pelicula pelicula);
struct NodoArbol* insertarPelicula(struct NodoArbol* raiz, struct Pelicula pelicula);
void mostrarPelicula(struct Pelicula p);
void recorridoInorden(struct NodoArbol* raiz);
void recorridoPreorden(struct NodoArbol* raiz);
void recorridoPosorden(struct NodoArbol* raiz);
void buscarPeliculaPorNombre(struct NodoArbol* raiz, const char* nombreBuscado);
void mostrarPeliculasPorGenero(struct NodoArbol* raiz, const char* generoBuscado);
int contarNodos(struct NodoArbol* raiz);
void recopilarPeliculasEnArreglo(struct NodoArbol* raiz, struct Pelicula* arreglo, int* indice);
int compararPeliculasPorRecaudacion(const void* a, const void* b);
void mostrarPeliculasMenorRecaudacion(struct NodoArbol* raiz, int cantidadAMostrar); // Nombre de función actualizado
void liberarArbol(struct NodoArbol* raiz);
void limpiarBufferEntrada();

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

int contarNodos(struct NodoArbol* raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return 1 + contarNodos(raiz->izquierda) + contarNodos(raiz->derecha);
}

void recopilarPeliculasEnArreglo(struct NodoArbol* raiz, struct Pelicula* arreglo, int* indice) {
    if (raiz == NULL) {
        return;
    }
    recopilarPeliculasEnArreglo(raiz->izquierda, arreglo, indice);
    arreglo[*indice] = raiz->datosPelicula;
    (*indice)++;
    recopilarPeliculasEnArreglo(raiz->derecha, arreglo, indice);
}

int compararPeliculasPorRecaudacion(const void* a, const void* b) {
    struct Pelicula* peliculaA = (struct Pelicula*)a;
    struct Pelicula* peliculaB = (struct Pelicula*)b;
    if (peliculaA->recaudacion < peliculaB->recaudacion) {
        return -1;
    } else if (peliculaA->recaudacion > peliculaB->recaudacion) {
        return 1;
    } else {
        return 0;
    }
}

// Funcion principal para mostrar las 'cantidadAMostrar' peliculas con menor recaudacion.
void mostrarPeliculasMenorRecaudacion(struct NodoArbol* raiz, int cantidadAMostrar) {
    // Contar el total de peliculas en el arbol.
    int totalPeliculas = contarNodos(raiz);

    // Si el arbol esta vacio (verificado en main, pero esta funcion es llamada solo si no es NULL),
    // y aun asi el conteo da 0, no hay nada que hacer.
    if (totalPeliculas == 0) {
        // Este mensaje es por si la raiz no es NULL pero no hay nodos (situacion anomala)
        // El main ya cubre el caso de raizArbol == NULL.
        // printf("No hay peliculas en el arbol para procesar (conteo interno 0).\n");
        return;
    }

    // Asignar memoria para el arreglo temporal.
    struct Pelicula* arregloPeliculas = (struct Pelicula*)malloc(totalPeliculas * sizeof(struct Pelicula));
    if (arregloPeliculas == NULL) {
        printf("Error: No se pudo asignar memoria para el arreglo temporal de peliculas.\n");
        return;
    }

    // Llenar el arreglo con las peliculas del arbol.
    int indice = 0; // Indice para llenar el arreglo.
    recopilarPeliculasEnArreglo(raiz, arregloPeliculas, &indice);

    // Verificacion crucial: ¿Se recopilaron todas las peliculas esperadas?
    if (indice != totalPeliculas) {
        printf("Error interno: Discrepancia entre el conteo de nodos (%d) y las peliculas recopiladas (%d).\n", totalPeliculas, indice);
        printf("Esto podria indicar un problema en la funcion contarNodos o recopilarPeliculasEnArreglo.\n");
        free(arregloPeliculas); // Liberar memoria antes de salir.
        return;
    }

    /*
    // --- INICIO BLOQUE DE DEPURACION (descomentar para usar) ---
    printf("\nDEBUG: Contenido del arreglo ANTES de qsort (Total: %d peliculas):\n", totalPeliculas);
    for (int k = 0; k < totalPeliculas; k++) {
        printf("  Pelicula: %s, Anio: %d, Genero: %s, Recaudacion: %.2f\n",
               arregloPeliculas[k].nombre,
               arregloPeliculas[k].anio,
               arregloPeliculas[k].genero,
               arregloPeliculas[k].recaudacion);
    }
    // --- FIN BLOQUE DE DEPURACION ---
    */

    // Ordenar el arreglo por recaudacion (menor a mayor) solo si hay peliculas.
    if (totalPeliculas > 0) {
        qsort(arregloPeliculas, totalPeliculas, sizeof(struct Pelicula), compararPeliculasPorRecaudacion);
    }

    /*
    // --- INICIO BLOQUE DE DEPURACION (descomentar para usar) ---
    printf("\nDEBUG: Contenido del arreglo DESPUES de qsort:\n");
    for (int k = 0; k < totalPeliculas; k++) {
        printf("  Pelicula: %s, Anio: %d, Genero: %s, Recaudacion: %.2f\n",
               arregloPeliculas[k].nombre,
               arregloPeliculas[k].anio,
               arregloPeliculas[k].genero,
               arregloPeliculas[k].recaudacion);
    }
    // --- FIN BLOQUE DE DEPURACION ---
    */
    
    // Determinar cuantas peliculas se van a mostrar realmente.
    int numRealesAMostrar = (totalPeliculas < cantidadAMostrar) ? totalPeliculas : cantidadAMostrar;

    // Imprimir el encabezado y las peliculas.
    // Se usa numRealesAMostrar para el título, para reflejar la cantidad que se mostrará.
    printf("\n--- %d Pelicula(s) con Menor Recaudacion ---\n", numRealesAMostrar);

    if (numRealesAMostrar > 0) {
        for (int i = 0; i < numRealesAMostrar; i++) {
            printf("Puesto %d (Menor Recaudacion):\n", i + 1);
            mostrarPelicula(arregloPeliculas[i]);
        }
    } else {
        // Este mensaje se mostraria si totalPeliculas > 0 pero cantidadAMostrar fue 0,
        // o si totalPeliculas fue 0 (este ultimo ya cubierto por la logica del main).
        printf("No hay peliculas para mostrar en esta categoria.\n");
    }

    // Liberar la memoria asignada para el arreglo.
    free(arregloPeliculas);
}

void liberarArbol(struct NodoArbol* raiz) {
    if (raiz == NULL) {
        return;
    }
    liberarArbol(raiz->izquierda);
    liberarArbol(raiz->derecha);
    free(raiz);
}

int main() {
    struct NodoArbol* raizArbol = NULL;
    int opcion;
    struct Pelicula peliculaTemp;
    char busquedaTexto[100];

    do {
        printf("\n--- Menu Principal Arbol de Peliculas ---\n");
        printf("1. Agregar nueva pelicula\n");
        printf("2. Mostrar recorrido Inorden\n");
        printf("3. Mostrar recorrido Preorden\n");
        printf("4. Mostrar recorrido Posorden\n");
        printf("5. Buscar pelicula por nombre\n");
        printf("6. Mostrar peliculas por genero\n");
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
            case 7:
                if (raizArbol == NULL) {
                    // Si el arbol esta vacio, se imprime el encabezado y el mensaje aqui.
                    printf("\n--- %d Pelicula(s) con Menor Recaudacion ---\n", 3); // Se esperan 3, pero no hay.
                    printf("El arbol esta vacio. No hay peliculas para analizar.\n");
                } else {
                    // Si el arbol no esta vacio, la funcion se encarga de imprimir
                    // su propio encabezado y la lista de peliculas (o un mensaje si,
                    // por alguna razon interna, no puede mostrar nada a pesar de que el arbol no este vacio).
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