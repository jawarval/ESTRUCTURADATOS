#include <stdio.h>

int main() {
    float num1, num2;

    // Solicitar al usuario los dos números
    printf("Ingrese el primer número: ");
    scanf("%f", &num1);
    printf("Ingrese el segundo número: ");
    scanf("%f", &num2);

    // Realizar las operaciones matemáticas
    float suma = num1 + num2;
    float resta = num1 - num2;
    float multiplicacion = num1 * num2;
    float division = (num2 != 0) ? (num1 / num2) : 0; // Evitar división por cero

    // Imprimir los resultados
    printf("\nResultados:\n");
    printf("Suma: %.2f\n", suma);
    printf("Resta: %.2f\n", resta);
    printf("Multiplicación: %.2f\n", multiplicacion);
    
    if (num2 != 0) {
        printf("División: %.2f\n", division);
    } else {
        printf("División: No se puede dividir por cero.\n");
    }

    return 0;
}