#include <stdio.h>
int main() {
    int edad ;
    printf("ingrese su edad: ");
    scanf("%d",&edad);
    if(edad >= 18)
    {
        printf("la persona es mayor de edad");
    }
    else
    {
        printf("es un bebe");
    }

    return 0;
}