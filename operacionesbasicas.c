#include <stdio.h>

int main() {
    float num1, num2;
    printf("Ingrese el primer número: ");
    scanf("%f", &num1);
    printf("Ingrese el segundo número: ");
    scanf("%f", &num2);

    // Suma
    printf("Suma: %.2f + %.2f = %.2f\n", num1, num2, num1 + num2);

    // Resta
    printf("Resta: %.2f - %.2f = %.2f\n", num1, num2, num1 - num2);

    // Multiplicación
    printf("Multiplicación: %.2f * %.2f = %.2f\n", num1, num2, num1 * num2);

    // División con verificación de división por cero
    if (num2 != 0) {
        printf("División: %.2f / %.2f = %.2f\n", num1, num2, num1 / num2);
    } else {
        printf("División: No se puede dividir por cero.\n");
    }

    return 0;
}
