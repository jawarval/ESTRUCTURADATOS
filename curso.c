#include <stdio.h>

int main() {
int numero;
int suma = 0;
printf("Digite um numero positivo. \n: ");
printf("Digite um numero negativo para terminar. \n: ");
scanf("%d", &numero);
while (numero >= 0) {
    printf("su numero digitado es: %d\n", numero);
    suma += numero;
   
    scanf("%d", &numero);
}
printf("La suma de los numeros es: %d\n", suma);
return 0;


}