#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOMBRE 30
#define MAX_DEPORTE 50

// Estructura Jugador
typedef struct jugador {
    int id;
    char nombre[MAX_NOMBRE];
    int edad;
    char genero;      // 'M' o 'F'
    char deporte[MAX_DEPORTE];
    struct jugador *siguiente;
} Jugador;

// Cola FIFO (lista de espera)
Jugador *cab = NULL, *ultimo = NULL;

// Pila LIFO (historial de participación)
Jugador *top = NULL;

// Contar jugadores por género en la cola
void contarGeneros(int *contM, int *contF) {
    *contM = 0;
    *contF = 0;
    Jugador *aux = cab;
    while (aux != NULL) {
        if (toupper(aux->genero) == 'M') (*contM)++;
        else if (toupper(aux->genero) == 'F') (*contF)++;
        aux = aux->siguiente;
    }
}

// Agregar jugador a la cola FIFO
void agregarJugador() {
    int contM, contF;
    contarGeneros(&contM, &contF);
    if (abs(contM - contF) > 4) {
        printf("No se puede agregar mas jugadores. Diferencia de genero supera 4.\n");
        return;
    }
    
    Jugador *nuevo = (Jugador *)malloc(sizeof(Jugador));
    if (nuevo == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        return;
    }
    
    printf("Ingrese ID: ");
    scanf("%d", &nuevo->id);
    printf("Ingrese Nombre:\n ");
    scanf(" %[^\n]", nuevo->nombre);
    printf("Ingrese Edad: ");
    scanf("%d", &nuevo->edad);
    printf("Ingrese Genero (M/F): ");
    scanf(" %c", &nuevo->genero);
    printf("Ingrese Deporte: ");
    scanf(" %[^\n]", nuevo->deporte);
    nuevo->siguiente = NULL;
    
    if (cab == NULL) {
        cab = nuevo;
        ultimo = nuevo;
    } else {
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
    }
    printf("Jugador agregado a la cola.\n");
}

// Mostrar jugadores en espera
void mostrarCola() {
    if (cab == NULL) {
        printf("No hay jugadores en espera.\n");
        return;
    }
    Jugador *aux = cab;
    printf("Lista de espera:\n");
    while (aux != NULL) {
        printf("ID: %d | Nombre: %s | Edad: %d | Genero: %c | Deporte: %s\n",
               aux->id, aux->nombre, aux->edad, toupper(aux->genero), aux->deporte);
        aux = aux->siguiente;
    }
}

// Permitir participación del siguiente jugador
void permitirParticipacion() {
    if (cab == NULL) {
        printf("No hay jugadores en espera.\n");
        return;
    }
    
    Jugador *aux = cab;
    while (aux != NULL && aux->edad < 15) {
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
    aux->siguiente = top;
    top = aux;
    printf("El jugador %s ha participado y se registra en el historial.\n", aux->nombre);
}

// Mostrar historial de participación
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

// Deshacer última participación
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
    printf("Se ha deshecho la participacion del jugador %s y regresa a la cola.\n", aux->nombre);
}

// Contar jugadores en espera
int contarCola() {
    int contador = 0;
    Jugador *aux = cab;
    while (aux != NULL) {
        contador++;
        aux = aux->siguiente;
    }
    return contador;
}

// Liberar memoria
void liberarMemoria() {
    Jugador *aux;
    while (cab != NULL) {
        aux = cab;
        cab = cab->siguiente;
        free(aux);
    }
    while (top != NULL) {
        aux = top;
        top = top->siguiente;
        free(aux);
    }
}

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
            default: printf("Opción inválida.\n");
        }
    } while (opcion != 7);
    liberarMemoria();
    return 0;
}
