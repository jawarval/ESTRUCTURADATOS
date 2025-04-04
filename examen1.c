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
    char genero;  // 'M' o 'F'
    char deporte[MAX_DEPORTE];
    struct jugador *siguiente;
} Jugador;

// Cola FIFO
Jugador *cab = NULL, *final = NULL;

// Pila LIFO
Jugador *top = NULL;

// Contar jugadores por género en la cola
void contarGeneros(int *contM, int *contF) {
    *contM = 0;
    *contF = 0;
    Jugador *aux = cab;
    while (aux) {
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
        printf("No se puede agregar más jugadores. La diferencia entre géneros supera 4.\n");
        return;
    }
    
    Jugador *nuevo = (Jugador *)malloc(sizeof(Jugador));
    if (!nuevo) {
        printf("Error: No se pudo asignar memoria.\n");
        return;
    }
    printf("Ingrese ID: ");
    scanf("%d", &nuevo->id);
    printf("Ingrese nombre: ");
    scanf(" %[^\n]", nuevo->nombre);
    printf("Ingrese edad: ");
    scanf("%d", &nuevo->edad);
    printf("Ingrese género (M/F): ");
    scanf(" %c", &nuevo->genero);
    printf("Ingrese deporte: ");
    scanf(" %[^\n]", nuevo->deporte);
    nuevo->siguiente = NULL;

    if (!cab) {
        cab = final = nuevo;
    } else {
        final->siguiente = nuevo;
        final = nuevo;
    }
    printf("Jugador agregado a la cola.\n");
}

// Mostrar jugadores en espera (cola FIFO)
void mostrarCola() {
    if (!cab) {
        printf("La cola de espera esta vacia.\n");
        return;
    }
    Jugador *aux = cab;
    printf("Jugadores en espera:\n");
    while (aux) {
        printf("ID: %d | Nombre: %s | Edad: %d | Género: %c | Deporte: %s\n", 
               aux->id, aux->nombre, aux->edad, toupper(aux->genero), aux->deporte);
        aux = aux->siguiente;
    }
}

// Permitir participación del siguiente jugador
void permitirParticipacion() {
    while (cab && cab->edad < 15) {
        Jugador *descartado = cab;
        cab = cab->siguiente;
        free(descartado);
        printf("Jugador descartado por edad.\n");
    }
    if (!cab) {
        final = NULL;
        printf("No hay jugadores elegibles.\n");
        return;
    }
    
    Jugador *participante = cab;
    cab = cab->siguiente;
    if (!cab) final = NULL;
    
    participante->siguiente = top;
    top = participante;
    printf("El jugador ID %d (%s) ha participado.\n", participante->id, participante->nombre);
}

// Mostrar historial de participación (pila LIFO)
void mostrarHistorial() {
    if (!top) {
        printf("El historial esta vacio.\n");
        return;
    }
    Jugador *aux = top;
    printf("Historial de participaciones:\n");
    while (aux) {
        printf("ID: %d | Nombre: %s | Edad: %d | Genero: %c | Deporte: %s\n", 
               aux->id, aux->nombre, aux->edad, toupper(aux->genero), aux->deporte);
        aux = aux->siguiente;
    }
}

// Deshacer última participación
void deshacerParticipacion() {
    if (!top) {
        printf("No hay participaciones para deshacer.\n");
        return;
    }
    
    Jugador *ultimoParticipante = top;
    top = top->siguiente;
    ultimoParticipante->siguiente = NULL;
    
    if (!cab) {
        cab = final = ultimoParticipante;
    } else {
        final->siguiente = ultimoParticipante;
        final = ultimoParticipante;
    }
    printf("Se ha deshecho la participación del jugador ID %d (%s).\n", 
           ultimoParticipante->id, ultimoParticipante->nombre);
}

// Liberar memoria de la cola y la pila
void liberarMemoria() {
    Jugador *aux;
    while (cab) {
        aux = cab;
        cab = cab->siguiente;
        free(aux);
    }
    final = NULL;
    while (top) {
        aux = top;
        top = top->siguiente;
        free(aux);
    }
}

int main() {
    int opcion;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Agregar jugador\n2. Mostrar cola\n3. Permitir participacion\n");
        printf("4. Mostrar historial\n5. Deshacer participacion\n6. Salir\nSeleccione una opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1: agregarJugador(); break;
            case 2: mostrarCola(); break;
            case 3: permitirParticipacion(); break;
            case 4: mostrarHistorial(); break;
            case 5: deshacerParticipacion(); break;
            case 6: printf("Saliendo...\n"); break;
            default: printf("Opcion invalida.\n");
        }
    } while (opcion != 6);
    liberarMemoria();
    return 0;
}
