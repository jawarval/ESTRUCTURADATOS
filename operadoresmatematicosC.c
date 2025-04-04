#include <stdio.h>
int main() {
    float nota1, nota2;
    printf("Ingrese la nota del primer examen: ");
    scanf( "%f",&nota1);
    printf("Ingrese la nota del segundo examen: ");
    scanf ("%f",&nota2);
    float notaFinal;
    notaFinal=(nota1+nota2)/2;
    printf("la nota final de examenes es : %.2f",notaFinal);

    return 0;
}