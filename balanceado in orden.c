// Programa de peliculas con arbol balanceado por recorrido inorden
// Autor: Jairo Walinton Ramirez Valencia y Yeimy Alejandra Berrio Gonzalez

#include <stdio.h>      // Entrada y salida estandar
#include <stdlib.h>     // Memoria dinamica
#include <string.h>     // Manejo de cadenas

// Nodo del arbol
struct Nodo {
    char nombre[100];         // Nombre de la pelicula
    int anio;                 // Anio de estreno
    char genero[50];          // Genero de la pelicula
    float recaudacion;        // Monto recaudado
    struct Nodo *izq;         // Hijo izquierdo
    struct Nodo *der;         // Hijo derecho
};

// Crea un nodo nuevo
struct Nodo* crearNodo(char n[], int a, char g[], float r) {
    struct Nodo* p = (struct Nodo*)malloc(sizeof(struct Nodo));   // Reserva nodo
    strcpy(p->nombre, n);                                         // Copia nombre
    p->anio = a;                                                  // Copia anio
    strcpy(p->genero, g);                                         // Copia genero
    p->recaudacion = r;                                           // Copia recaudacion
    p->izq = p->der = NULL;                                       // Inicia hijos
    return p;                                                     // Devuelve nodo
}

// Inserta en ABB
struct Nodo* insertar(struct Nodo* raiz, char n[], int a, char g[], float r) {
    if (!raiz) return crearNodo(n, a, g, r);                       // Arbol vacio
    if (strcmp(n, raiz->nombre) < 0)                               // Nombre menor
        raiz->izq = insertar(raiz->izq, n, a, g, r);               // Inserta izq
    else                                                           // Nombre mayor
        raiz->der = insertar(raiz->der, n, a, g, r);               // Inserta der
    return raiz;                                                   // Retorna raiz
}

// Busca por nombre
void buscar(struct Nodo* raiz, char n[]) {
    if (!raiz) { printf("Pelicula no encontrada\n"); return; }     // No encontrada
    if (strcmp(n, raiz->nombre) == 0)                              // Coincide
        printf("Nombre %s Anio %d Genero %s Recaudacion %.2f\n",
               raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
    else if (strcmp(n, raiz->nombre) < 0) buscar(raiz->izq, n);    // Busca izq
    else buscar(raiz->der, n);                                     // Busca der
}

// Filtra por genero
void filtrarGenero(struct Nodo* raiz, char g[]) {
    if (!raiz) return;                                             // Arbol vacio
    filtrarGenero(raiz->izq, g);                                   // Recorre izq
    if (strcmp(raiz->genero, g) == 0)                              // Coincide genero
        printf("Nombre %s Anio %d Genero %s Recaudacion %.2f\n",
               raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
    filtrarGenero(raiz->der, g);                                   // Recorre der
}

// Muestra por anio
void mostrarAnio(struct Nodo* raiz, int a) {
    if (!raiz) return;                                             // Arbol vacio
    mostrarAnio(raiz->izq, a);                                     // Izq
    if (raiz->anio == a)                                           // Coincide anio
        printf("Nombre %s Anio %d Genero %s Recaudacion %.2f\n",
               raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion);
    mostrarAnio(raiz->der, a);                                     // Der
}

// Inorden para listado
void inorden(struct Nodo* raiz) {
    if (!raiz) return;                                             // Arbol vacio
    inorden(raiz->izq);                                            // Izq
    printf("Nombre %s Anio %d Genero %s Recaudacion %.2f\n",
           raiz->nombre, raiz->anio, raiz->genero, raiz->recaudacion); // Nodo
    inorden(raiz->der);                                            // Der
}

// Cuenta nodos
int contar(struct Nodo* r) {
    return r ? 1 + contar(r->izq) + contar(r->der) : 0;            // Recursivo
}

// Llena arreglo con inorden
void llenar(struct Nodo* r, struct Nodo** v, int* i) {
    if (!r) return;                                                // Base
    llenar(r->izq, v, i);                                          // Izq
    v[(*i)++] = r;                                                 // Guarda
    llenar(r->der, v, i);                                          // Der
}

// Construye balanceado
struct Nodo* construir(struct Nodo** v, int l, int h) {
    if (l > h) return NULL;                                        // Rango vacio
    int m = (l + h) / 2;                                           // Mitad
    struct Nodo* r = v[m];                                         // Raiz
    r->izq = construir(v, l, m - 1);                               // Subarbol izq
    r->der = construir(v, m + 1, h);                               // Subarbol der
    return r;                                                      // Devuelve raiz
}

// Balancea arbol
struct Nodo* balancear(struct Nodo* raiz) {
    int n = contar(raiz);                                          // Total nodos
    if (n == 0) return NULL;                                       // Arbol vacio
    struct Nodo** v = (struct Nodo**)malloc(n * sizeof(struct Nodo*)); // Vector
    int i = 0; llenar(raiz, v, &i);                                // Llena vector
    struct Nodo* nuevo = construir(v, 0, n - 1);                   // Nuevo arbol
    free(v);                                                       // Libera vector
    return nuevo;                                                  // Devuelve raiz
}

// Encuentra minimo
struct Nodo* minimo(struct Nodo* r) {
    while (r && r->izq) r = r->izq;                                // Bajada izq
    return r;                                                      // Devuelve minimo
}

// Elimina por nombre
struct Nodo* eliminar(struct Nodo* r, char n[]) {
    if (!r) return NULL;                                           // Nodo nulo
    int c = strcmp(n, r->nombre);                                  // Comparacion
    if (c < 0) r->izq = eliminar(r->izq, n);                       // Izq
    else if (c > 0) r->der = eliminar(r->der, n);                  // Der
    else {                                                         // Encontrado
        if (!r->izq && !r->der) { free(r); return NULL; }          // Sin hijos
        else if (!r->izq) { struct Nodo* t = r->der; free(r); return t; } // Solo der
        else if (!r->der) { struct Nodo* t = r->izq; free(r); return t; } // Solo izq
        else {                                                     // Dos hijos
            struct Nodo* s = minimo(r->der);                       // Sucesor
            strcpy(r->nombre, s->nombre);                          // Copia datos
            r->anio = s->anio; strcpy(r->genero, s->genero);       // Copia
            r->recaudacion = s->recaudacion;                       // Copia
            r->der = eliminar(r->der, s->nombre);                  // Elimina sucesor
        }
    }
    return r;                                                      // Devuelve raiz
}

// Libera arbol
void liberar(struct Nodo* r) {
    if (!r) return;                                                // Base
    liberar(r->izq); liberar(r->der); free(r);                     // Postorden
}

// Principal
int main() {
    struct Nodo* raiz = NULL;                                      // Arbol vacio
    int op, anio; float rec; char nom[100], gen[50];               // Variables

    do {                                                           // Menu loop
        printf("\nMenu\n");
        printf("1 Insertar pelicula\n2 Buscar por nombre\n3 Filtrar por genero\n");
        printf("4 Mostrar por anio\n5 Listar inorden\n6 Eliminar pelicula\n0 Salir\n");
        printf("Opcion "); scanf("%d", &op); getchar();            // Lee opcion

        if (op == 1) {                                             // Insertar
            printf("Ingrese nombre "); fgets(nom, 100, stdin); nom[strcspn(nom,"\n")]=0;
            printf("Ingrese anio "); scanf("%d", &anio); getchar();
            printf("Ingrese genero "); fgets(gen, 50, stdin); gen[strcspn(gen,"\n")]=0;
            printf("Ingrese recaudacion "); scanf("%f", &rec); getchar();
            raiz = insertar(raiz, nom, anio, gen, rec);            // Inserta
            raiz = balancear(raiz);                                // Balancea
        }
        else if (op == 2) {                                        // Buscar
            printf("Ingrese nombre "); fgets(nom,100,stdin); nom[strcspn(nom,"\n")]=0;
            buscar(raiz, nom);                                     // Busca
        }
        else if (op == 3) {                                        // Filtrar genero
            printf("Ingrese genero "); fgets(gen,50,stdin); gen[strcspn(gen,"\n")]=0;
            filtrarGenero(raiz, gen);                              // Filtra
        }
        else if (op == 4) {                                        // Mostrar anio
            printf("Ingrese anio "); scanf("%d",&anio); getchar();
            mostrarAnio(raiz, anio);                               // Muestra
        }
        else if (op == 5) {                                        // Listado
            inorden(raiz);                                         // Inorden
        }
        else if (op == 6) {                                        // Eliminar
            printf("Ingrese nombre "); fgets(nom,100,stdin); nom[strcspn(nom,"\n")]=0;
            raiz = eliminar(raiz, nom);                            // Elimina
            raiz = balancear(raiz);                                // Balancea
        }
        else if (op == 0) { liberar(raiz); printf("Programa finalizado\n"); }
        else printf("Opcion no valida\n");                         // Error
    } while (op != 0);                                             // Fin loop

    return 0;                                                      // Termina
}
