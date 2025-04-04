/*
*JAIRO WALINTON RAMIREZ VALENCIA
*JHON EDUER MOSQUERA CANGA
*/
#include <stdio.h>   // Biblioteca estándar para entrada y salida (printf, scanf).
#include <stdlib.h>  // Biblioteca estándar para manejo de memoria dinámica (malloc, free).
#include <string.h>  // Biblioteca para manejo de cadenas de caracteres (strcpy, strcmp).
#include <ctype.h>   // Biblioteca para manipulación de caracteres (toupper, tolower).

// Definición de constantes
#define MAX_NOMBRE 30   // Máximo de caracteres para el nombre de un jugador.
#define MAX_DEPORTE 50  // Máximo de caracteres para el nombre del deporte.

// Definición de la estructura Jugador
typedef struct jugador {
    int id;                      // Identificador único del jugador.
    char nombre[MAX_NOMBRE];      // Nombre del jugador.
    int edad;                     // Edad del jugador.
    char genero;                  // Género del jugador ('M' o 'F').
    char deporte[MAX_DEPORTE];     // Deporte en el que participa.
    struct jugador *siguiente;    // Puntero al siguiente jugador en la lista.
} Jugador;

// Variables globales para manejar la cola FIFO y la pila LIFO
Jugador *cab = NULL, *ultimo = NULL;  // 'cab' apunta al primer jugador en la cola, 'ultimo' al último.
Jugador *top = NULL;                  // 'top' apunta al último jugador en el historial (pila).

// Función para contar jugadores en la cola según su género
void contarGeneros(int *contM, int *contF) {
    *contM = 0;
    *contF = 0;
    Jugador *aux = cab;  // Puntero auxiliar para recorrer la cola.
    
    while (aux != NULL) {  // Mientras haya jugadores en la cola...
        if (toupper(aux->genero) == 'M') (*contM)++;  // Si el género es 'M', incrementa contM.
        else if (toupper(aux->genero) == 'F') (*contF)++;  // Si es 'F', incrementa contF.
        aux = aux->siguiente;  // Avanza al siguiente jugador.
    }
}

// Función para agregar un nuevo jugador a la cola
void agregarJugador() {
    int contM, contF;
    contarGeneros(&contM, &contF);  // Cuenta la cantidad de hombres y mujeres en la cola.

    if (abs(contM - contF) > 4) {  // Si la diferencia de género supera 4, no se permite agregar más.
        printf("No se puede agregar mas jugadores. Diferencia de genero supera 4.\n");
        return;
    }
    
    Jugador *nuevo = (Jugador *)malloc(sizeof(Jugador));  // Se reserva memoria para un nuevo jugador.
    if (nuevo == NULL) {  // Si malloc devuelve NULL, significa que no hay suficiente memoria.
        printf("Error: No se pudo asignar memoria.\n");
        return;
    }
    
    // Se solicitan los datos del jugador.
    printf("Ingrese ID: ");
    scanf("%d", &nuevo->id);
    printf("Ingrese Nombre:\n ");
    scanf(" %[^\n]", nuevo->nombre);  // Se usa `scanf(" %[^\n]", ...)` para leer nombres con espacios.
    printf("Ingrese Edad: ");
    scanf("%d", &nuevo->edad);
    printf("Ingrese Genero (M/F): ");
    scanf(" %c", &nuevo->genero);
    printf("Ingrese Deporte: ");
    scanf(" %[^\n]", nuevo->deporte);

    nuevo->siguiente = NULL;  // Se inicializa el puntero 'siguiente' como NULL.

    if (cab == NULL) {  // Si la cola está vacía...
        cab = nuevo;
        ultimo = nuevo;
    } else {  // Si ya hay jugadores en la cola...
        ultimo->siguiente = nuevo;  // Se enlaza el último nodo con el nuevo jugador.
        ultimo = nuevo;  // Se actualiza el puntero 'ultimo'.
    }
    printf("Jugador agregado a la cola.\n");
}

// Función para mostrar los jugadores en espera (cola FIFO)
void mostrarCola() {
    if (cab == NULL) {  // Si la cola está vacía...
        printf("No hay jugadores en espera.\n");
        return;
    }
    Jugador *aux = cab;
    printf("Lista de espera:\n");
    while (aux != NULL) {  // Recorre la lista de jugadores e imprime sus datos.
        printf("ID: %d | Nombre: %s | Edad: %d | Genero: %c | Deporte: %s\n",
               aux->id, aux->nombre, aux->edad, toupper(aux->genero), aux->deporte);
        aux = aux->siguiente;
    }
}

// Función para permitir la participación del siguiente jugador en la cola
void permitirParticipacion() {
    if (cab == NULL) {  // Si no hay jugadores en espera...
        printf("No hay jugadores en espera.\n");
        return;
    }
    
    Jugador *aux = cab;
    while (aux != NULL && aux->edad < 15) {  // Si el jugador es menor de 15 años, se descarta.
        printf("Jugador %s no cumple la edad minima y es descartado.\n", aux->nombre);
        cab = aux->siguiente;
        free(aux);
        aux = cab;
    }
    if (aux == NULL) {
        ultimo = NULL;
        return;
    }
    
    cab = aux->siguiente;
    if (cab == NULL) ultimo = NULL;
    aux->siguiente = top;  // Se mueve el jugador al historial (pila LIFO).
    top = aux;
    printf("El jugador %s ha participado y se registra en el historial.\n", aux->nombre);
}

// Función para mostrar el historial de participación (pila LIFO)
void mostrarHistorial() {
    if (top == NULL) {
        printf("El historial esta vacio.\n");
        return;
    }
    Jugador *aux = top;
    printf("Historial de participacion:\n");
    while (aux != NULL) {
        printf("ID: %d | Nombre: %s | Edad: %d | Genero: %c | Deporte: %s\n",
               aux->id, aux->nombre, aux->edad, toupper(aux->genero), aux->deporte);
        aux = aux->siguiente;
    }
}

// Función para deshacer la última participación (devolver jugador del historial a la cola)
void deshacerParticipacion() {
    if (top == NULL) {
        printf("No hay participaciones para deshacer.\n");
        return;
    }
    Jugador *aux = top;
    top = top->siguiente;
    aux->siguiente = NULL;
    
    if (cab == NULL) {
        cab = aux;
        ultimo = aux;
    } else {
        ultimo->siguiente = aux;
        ultimo = aux;
    }
    printf("Se ha deshecho la participación del jugador %s y regresa a la cola.\n", aux->nombre);
}

// Función para contar los jugadores en la cola
int contarCola() {
    int contador = 0;
    Jugador *aux = cab;
    while (aux != NULL) {
        contador++;
        aux = aux->siguiente;
    }
    return contador;
}

// Función para liberar la memoria utilizada
void liberarMemoria() {
    Jugador *aux;
    while (cab != NULL) {  // Libera la memoria de la cola.
        aux = cab;
        cab = cab->siguiente;
        free(aux);
    }
    while (top != NULL) {  // Libera la memoria del historial.
        aux = top;
        top = top->siguiente;
        free(aux);
    }
}

// Función principal (menú de opciones)
int main() {
    int opcion;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Agregar jugador a la cola\n");
        printf("2. Mostrar jugadores en espera\n");
        printf("3. Contar jugadores en espera\n");
        printf("4. Permitir participacion del siguiente jugador\n");
        printf("5. Mostrar historial de participacion\n");
        printf("6. Deshacer ultima participacion\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: agregarJugador(); break;
            case 2: mostrarCola(); break;
            case 3: printf("Total jugadores en espera: %d\n", contarCola()); break;
            case 4: permitirParticipacion(); break;
            case 5: mostrarHistorial(); break;
            case 6: deshacerParticipacion(); break;
            case 7: printf("Saliendo...\n"); break;
            default: printf("Opcion invalida.\n");
        }
    } while (opcion != 7);
    liberarMemoria();  // Limpia la memoria antes de salir.
    return 0;
}
