#include <iostream>
using namespace std;

// Función para calcular el factorial
int factorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

int main() {
    int n;

    // Solicitar número al usuario
    cout << "Ingrese el valor a calcular factorial: ";
    cin >> n;

    // Validar si el número es negativo
    if (n < 0) {
        cout << "El factorial no está definido para números negativos." << endl;
    } else {
        int resultado = factorial(n);
        cout << "Factorial: " << resultado << endl;
    }

    return 0;
}
