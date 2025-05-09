#include <iostream>
using namespace std;

// Estructura del nodo
struct Nodo {
    int valor;
    Nodo* izquierdo;
    Nodo* derecho;
};

// Crear un nuevo nodo
Nodo* crearNodo(int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->valor = valor;
    nuevo->izquierdo = nullptr;
    nuevo->derecho = nullptr;
    return nuevo;
}

// Insertar un valor en el ABB
Nodo* insertar(Nodo* raiz, int valor) {
    if (raiz == nullptr) return crearNodo(valor);
    if (valor < raiz->valor)
        raiz->izquierdo = insertar(raiz->izquierdo, valor);
    else if (valor > raiz->valor)
        raiz->derecho = insertar(raiz->derecho, valor);
    return raiz;
}

// Buscar un valor
bool buscar(Nodo* raiz, int valor) {
    if (raiz == nullptr) return false;
    if (valor == raiz->valor) return true;
    if (valor < raiz->valor)
        return buscar(raiz->izquierdo, valor);
    else
        return buscar(raiz->derecho, valor);
}

// Recorrido inorden
void inorden(Nodo* raiz) {
    if (raiz != nullptr) {
        inorden(raiz->izquierdo);
        cout << raiz->valor << " ";
        inorden(raiz->derecho);
    }
}

// Encontrar el mínimo
Nodo* minimo(Nodo* raiz) {
    while (raiz->izquierdo != nullptr)
        raiz = raiz->izquierdo;
    return raiz;
}

// Eliminar un nodo
Nodo* eliminar(Nodo* raiz, int valor) {
    if (raiz == nullptr) return raiz;

    if (valor < raiz->valor)
        raiz->izquierdo = eliminar(raiz->izquierdo, valor);
    else if (valor > raiz->valor)
        raiz->derecho = eliminar(raiz->derecho, valor);
    else {
        if (raiz->izquierdo == nullptr && raiz->derecho == nullptr) {
            delete raiz;
            return nullptr;
        } else if (raiz->izquierdo == nullptr) {
            Nodo* temp = raiz->derecho;
            delete raiz;
            return temp;
        } else if (raiz->derecho == nullptr) {
            Nodo* temp = raiz->izquierdo;
            delete raiz;
            return temp;
        } else {
            Nodo* temp = minimo(raiz->derecho);
            raiz->valor = temp->valor;
            raiz->derecho = eliminar(raiz->derecho, temp->valor);
        }
    }
    return raiz;
}

// Menú principal
int main() {
    Nodo* raiz = nullptr;
    int opcion, valor, cantidad;

    do {
        cout << "\n--- MENU DEL ARBOL BINARIO DE BUSQUEDA ---\n";
        cout << "1. Insertar valores\n";
        cout << "2. Buscar un valor\n";
        cout << "3. Eliminar un valor\n";
        cout << "4. Mostrar recorrido Inorden\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "¿Cuántos valores desea insertar? ";
                cin >> cantidad;
                for (int i = 0; i < cantidad; i++) {
                    cout << "Ingrese el valor #" << i + 1 << ": ";
                    cin >> valor;
                    raiz = insertar(raiz, valor);
                }
                break;

            case 2:
                cout << "Ingrese el valor a buscar: ";
                cin >> valor;
                if (buscar(raiz, valor))
                    cout << "El valor " << valor << " está en el árbol.\n";
                else
                    cout << "El valor " << valor << " NO está en el árbol.\n";
                break;

            case 3:
                cout << "Ingrese el valor a eliminar: ";
                cin >> valor;
                raiz = eliminar(raiz, valor);
                cout << "Valor eliminado (si existía).\n";
                break;

            case 4:
                cout << "Recorrido Inorden del árbol: ";
                inorden(raiz);
                cout << endl;
                break;

            case 5:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opcion inválida. Intente nuevamente.\n";
        }

    } while (opcion != 5);

    return 0;
}
