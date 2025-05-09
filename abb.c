#include<stdio.h>
#include<stdlib.h>
#include<string.h>



   typedef struct pelicula {
        char nombre[100];
        int anio;
        char genero[50];
        float recaudacion;
        pelicula* izquierda;
        pelicula* derecha;