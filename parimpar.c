#include<stdio.h>
int main(){
    int numero;
    printf("ingrese el numero:");
    scanf("%d",&numero);
    if ((numero % 2 )==0)
    {
        printf("el numero ingresado es par");
    }
    else
    {
        printf("el numero ingresado es impar");
    }


    return 0;

}