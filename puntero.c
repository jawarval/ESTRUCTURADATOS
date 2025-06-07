#include <stdio.h>

int main() {
    int x = 5;
    int *p = &x;  // El puntero p guarda la dirección de x

    printf("Valor de x: %d\n", x);       // Imprime 5
    printf("Dirección de x: %p\n", &x);  // Dirección de x
    printf("Contenido de p: %p\n", p);   // Debe ser igual a &x
    printf("Valor apuntado por p: %d\n", *p); // Imprime el valor de x (5)

    *p = 20;  // Modifica el valor de x a través del puntero

    printf("Nuevo valor de x: %d\n", x);  // Ahora x es 20

    return 0;
}
