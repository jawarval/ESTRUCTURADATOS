#include <iostream>
using namespace std;

int main() {
    int numeros[5];  // Arreglo de 5 enteros

    // Entrada de datos
    cout << "Ingrese 5 números:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Número " << i + 1 << ": ";
        cin >> numeros[i];
    }

    // Ordenamiento con Insertion Sort
    for (int i = 1; i < 5; i++) {
        int clave = numeros[i];     // Elemento a insertar
        int j = i - 1;

        // Mover los elementos mayores que la clave una posición a la derecha
        while (j >= 0 && numeros[j] > clave) {
            numeros[j + 1] = numeros[j];
            j--;
        }

        // Insertar la clave en su posición correcta
        numeros[j + 1] = clave;
    }

    // Mostrar el arreglo ordenado
    cout << "Números ordenados de menor a mayor:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << numeros[i] << " ";
    }

    // Mostrar el mayor (último del arreglo ordenado)
    cout << "\nEl número mayor es: " << numeros[4] << endl;

    return 0;
}
