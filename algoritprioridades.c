#include <stdio.h>

struct Proceso {
    int id;
    int tiempo;
    int prioridad;
};

void ordenarPorPrioridad(struct Proceso procesos[], int n) {
    struct Proceso temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (procesos[i].prioridad > procesos[j].prioridad) {
                temp = procesos[i];
                procesos[i] = procesos[j];
                procesos[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Ingrese el número de procesos: ");
    scanf("%d", &n);

    struct Proceso procesos[n];

    // Ingreso de datos
    for (int i = 0; i < n; i++) {
        procesos[i].id = i + 1;
        printf("\nProceso %d\n", procesos[i].id);
        printf("Tiempo de ejecución: ");
        scanf("%d", &procesos[i].tiempo);
        printf("Prioridad (menor valor = mayor prioridad): ");
        scanf("%d", &procesos[i].prioridad);
    }

    // Ordenar por prioridad
    ordenarPorPrioridad(procesos, n);

    printf("\nOrden de ejecución de los procesos:\n");
    int tiempoTotal = 0;
    for (int i = 0; i < n; i++) {
        printf("Proceso P%d (Prioridad: %d, Tiempo: %d)\n",
               procesos[i].id,
               procesos[i].prioridad,
               procesos[i].tiempo);
        tiempoTotal += procesos[i].tiempo;
    }

    printf("\nTiempo total estimado de ejecución: %d unidades\n", tiempoTotal);

    return 0;
}
