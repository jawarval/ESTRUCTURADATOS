#include <iostream> // Para entrada y salida
using namespace std;

int main() {
    int numeros[5];      // Arreglo para guardar 5 números
    int mayor;           // Variable para almacenar el número mayor

    // Pedir al usuario que ingrese 5 números
    cout << "Ingrese 5 números:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Número " << i + 1 << ": ";
        cin >> numeros[i];
    }

    // Asumimos que el primero es el mayor inicialmente
    mayor = numeros[0];

    // Recorremos el arreglo para encontrar el número mayor
    for (int i = 1; i < 5; i++) {
        if (numeros[i] > mayor) {
            mayor = numeros[i];
        }
    }

    // Mostrar el resultado
    cout << "El número mayor es: " << mayor << endl;

    return 0; // Fin del programa
}
