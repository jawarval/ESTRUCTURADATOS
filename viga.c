#include <stdio.h>
#include <stdlib.h>

#define MAX 50

typedef struct {
    double P;   // Magnitud (N)
    double x;   // Posición (m)
} CargaPuntual;

typedef struct {
    double w;   // Intensidad (N/m)
    double x1;  // Inicio (m)
    double x2;  // Fin (m)
} CargaDistribuida;

// Variables globales
double L = -1;
CargaPuntual cp[MAX];
CargaDistribuida cd[MAX];
int nP = 0, nD = 0;

// Mostrar las cargas ingresadas
void mostrarCargas() {
    printf("\n--- CARGAS PUNTUALES ---\n");
    if (nP == 0) printf("Ninguna.\n");
    for (int i = 0; i < nP; i++)
        printf("P%d: %.2f N en %.2f m\n", i + 1, cp[i].P, cp[i].x);

    printf("\n--- CARGAS DISTRIBUIDAS ---\n");
    if (nD == 0) printf("Ninguna.\n");
    for (int i = 0; i < nD; i++)
        printf("D%d: %.2f N/m de %.2f m a %.2f m\n", i + 1, cd[i].w, cd[i].x1, cd[i].x2);
}

// Calcular reacciones y mostrar V(x), M(x)
void calcularResultados() {
    if (L <= 0) {
        printf("Debe ingresar primero la longitud de la viga.\n");
        return;
    }

    // Suma de fuerzas y momentos
    double sumF = 0, sumM = 0;

    for (int i = 0; i < nP; i++) {
        sumF += cp[i].P;
        sumM += cp[i].P * (L - cp[i].x);
    }

    for (int i = 0; i < nD; i++) {
        double Fd = cd[i].w * (cd[i].x2 - cd[i].x1);
        double xc = (cd[i].x1 + cd[i].x2) / 2.0;
        sumF += Fd;
        sumM += Fd * (L - xc);
    }

    // Reacciones en apoyos (simplemente apoyada)
    double R1 = sumM / L;
    double R2 = sumF - R1;

    printf("\nReacción en apoyo izquierdo (R1): %.2f N\n", R1);
    printf("Reacción en apoyo derecho  (R2): %.2f N\n", R2);

    // Mostrar diagrama de V y M
    printf("\nDistancia (x)\tCortante V(x)\tMomento M(x)\n");
    printf("------------------------------------------------\n");

    for (double x = 0; x <= L; x += 0.5) {
        double V = R1;
        double M = R1 * x;

        for (int i = 0; i < nP; i++) {
            if (cp[i].x <= x) {
                V -= cp[i].P;
                M -= cp[i].P * (x - cp[i].x);
            }
        }

        for (int i = 0; i < nD; i++) {
            double a = cd[i].x1;
            double b = cd[i].x2;
            if (x > a) {
                double xi = (x < b) ? x : b;
                double l = xi - a;
                double Fd = cd[i].w * l;
                V -= Fd;
                M -= Fd * (x - (a + xi) / 2.0);
            }
        }

        printf("%.2f m\t\t%.2f N\t\t%.2f Nm\n", x, V, M);
    }
}

// Menú principal
int main() {
    int opcion;

    do {
        printf("\n========== MENÚ DE ANÁLISIS DE VIGA ==========\n");
        printf("1. Ingresar longitud de la viga\n");
        printf("2. Agregar carga puntual\n");
        printf("3. Agregar carga distribuida\n");
        printf("4. Mostrar cargas ingresadas\n");
        printf("5. Calcular reacciones, cortante y momento\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese la longitud de la viga (m): ");
                scanf("%lf", &L);
                if (L <= 0) {
                    printf("Longitud no válida. Debe ser mayor que cero.\n");
                    L = -1;
                }
                break;

            case 2:
                if (nP >= MAX) {
                    printf("Máximo de cargas puntuales alcanzado.\n");
                    break;
                }
                printf("Ingrese la magnitud de la carga puntual (N): ");
                scanf("%lf", &cp[nP].P);
                printf("Ingrese la posición sobre la viga (m): ");
                scanf("%lf", &cp[nP].x);
                if (cp[nP].x < 0 || cp[nP].x > L) {
                    printf("Error: posición fuera de la viga.\n");
                } else {
                    nP++;
                }
                break;

            case 3:
                if (nD >= MAX) {
                    printf("Máximo de cargas distribuidas alcanzado.\n");
                    break;
                }
                printf("Ingrese la intensidad de la carga (N/m): ");
                scanf("%lf", &cd[nD].w);
                printf("Inicio del tramo (m): ");
                scanf("%lf", &cd[nD].x1);
                printf("Fin del tramo (m): ");
                scanf("%lf", &cd[nD].x2);
                if (cd[nD].x1 < 0 || cd[nD].x2 > L || cd[nD].x1 >= cd[nD].x2) {
                    printf("Error: tramo inválido.\n");
                } else {
                    nD++;
                }
                break;

            case 4:
                mostrarCargas();
                break;

            case 5:
                calcularResultados();
                break;

            case 6:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opción inválida. Intente de nuevo.\n");
        }

    } while (opcion != 6);

    return 0;
}
