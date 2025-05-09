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

    // Ordenamiento (Bubble Sort)
    for (int i = 0; i < 5 - 1; i++) {
        for (int j = 0; j < 5 - 1 - i; j++) {
            if (numeros[j] > numeros[j + 1]) {
                // Intercambiar los elementos
                int temp = numeros[j];
                numeros[j] = numeros[j + 1];
                numeros[j + 1] = temp;
            }
        }
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
