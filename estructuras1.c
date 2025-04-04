#include<stdio.h>
struct perro
{
char nombre[30];
int edad;
float peso;
}perro1={"osito",12,8.5};

int main(){
    
printf("El nombre de mi mascota No 1 es :%s, y su edad en meses es de %d y su peso es de %.2f kg \n", perro1.nombre,perro1.edad,perro1.peso);
    return 0;
}