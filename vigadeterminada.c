#include <stdio.h>

void calcular_resultados(double L, double P, double a) {
    double R1 = P * (L - a) / L; // Reacción en el apoyo izquierdo
    double R2 = P * a / L;       // Reacción en el apoyo derecho

    printf("\nDistancia (x)\tCortante (V)\tMomento (M)\n");
    printf("-------------------------------------------------\n");

    for (double x = 0; x <= L; x += 0.1) {
        double V, M;

        if (x < a) {
            V = R1;
            M = R1 * x;
        } else {
            V = R1 - P;
            M = R1 * x - P * (x - a);
        }

        printf("%.2f m\t\t%.2f N\t\t%.2f Nm\n", x, V, M);
    }
}

int main() {
    double L, P, a;

    printf("ANÁLISIS DE VIGA SIMPLEMENTE APOYADA CON CARGA PUNTUAL\n");
    printf("--------------------------------------------------------\n");

    // Ingresar la longitud total de la viga
    printf("Ingrese la longitud de la viga (en metros): ");
    scanf("%lf", &L);

    // Ingresar el valor de la carga puntual
    printf("Ingrese la magnitud de la carga puntual (en Newtons): ");
    scanf("%lf", &P);

    // Ingresar la posición donde se aplica la carga puntual
    printf("Ingrese la distancia desde el apoyo izquierdo hasta la carga (en metros): ");
    scanf("%lf", &a);

    if (a < 0 || a > L) {
        printf("Error: La posición de la carga está fuera del rango de la viga.\n");
        return 1;
    }

    calcular_resultados(L, P, a);

    return 0;
}
