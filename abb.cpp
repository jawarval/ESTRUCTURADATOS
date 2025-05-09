#include <iostream>
using namespace std;

// Definición del nodo
struct Nodo {
    int valor;
    ||||||

    Nodo(int v) {
        valor = v;
        izquierdo = derecho = nullptr;
    }
};

// Clase Árbol Binario de Búsqueda
class ABB {
private:
    Nodo* raiz;

    // Función auxiliar para insertar
    Nodo* insertar(Nodo* nodo, int valor) {
        if (nodo == nullptr) {
            return new Nodo(valor);
        }
        if (valor < nodo->valor)
            nodo->izquierdo = insertar(nodo->izquierdo, valor);
        else if (valor > nodo->valor)
            nodo->derecho = insertar(nodo->derecho, valor);
        return nodo;
    }

    // Función auxiliar para búsqueda
    bool buscar(Nodo* nodo, int valor) {
        if (nodo == nullptr) return false;
        if (valor == nodo->valor) return true;
        if (valor < nodo->valor)
            return buscar(nodo->izquierdo, valor);
        else
            return buscar(nodo->derecho, valor);
    }

    // Recorrido inorden
    void inorden(Nodo* nodo) {
        if (nodo != nullptr) {
            inorden(nodo->izquierdo);
            cout << nodo->valor << " ";
            inorden(nodo->derecho);
        }
    }

    // Función auxiliar para encontrar el valor mínimo en un subárbol
    Nodo* encontrarMinimo(Nodo* nodo) {
        while (nodo->izquierdo != nullptr)
            nodo = nodo->izquierdo;
        return nodo;
    }

    // Función auxiliar para eliminar
    Nodo* eliminar(Nodo* nodo, int valor) {
        if (nodo == nullptr) return nodo;

        if (valor < nodo->valor)
            nodo->izquierdo = eliminar(nodo->izquierdo, valor);
        else if (valor > nodo->valor)
            nodo->derecho = eliminar(nodo->derecho, valor);
        else {
            // Caso 1: sin hijos
            if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) {
                delete nodo;
                return nullptr;
            }
            // Caso 2: un hijo
            else if (nodo->izquierdo == nullptr) {
                Nodo* temp = nodo->derecho;
                delete nodo;
                return temp;
            }
            else if (nodo->derecho == nullptr) {
                Nodo* temp = nodo->izquierdo;
                delete nodo;
                return temp;
            }
            // Caso 3: dos hijos
            Nodo* temp = encontrarMinimo(nodo->derecho);
            nodo->valor = temp->valor;
            nodo->derecho = eliminar(nodo->derecho, temp->valor);
        }
        return nodo;
    }

public:
    ABB() {
        raiz = nullptr;
    }

    void insertar(int valor) {
        raiz = insertar(raiz, valor);
    }

    bool buscar(int valor) {
        return buscar(raiz, valor);
    }

    void eliminar(int valor) {
        raiz = eliminar(raiz, valor);
    }

    void mostrarInorden() {
        inorden(raiz);
        cout << endl;
    }
};

// Programa principal
int main() {
    ABB arbol;
    arbol.insertar(50);
    arbol.insertar(30);
    arbol.insertar(70);
    arbol.insertar(20);
    arbol.insertar(40);
    arbol.insertar(60);
    arbol.insertar(80);

    cout << "Recorrido inorden del ABB: ";
    arbol.mostrarInorden();

    cout << "¿Está el 40 en el árbol? " << (arbol.buscar(40) ? "Sí" : "No") << endl;

    arbol.eliminar(30);
    cout << "Árbol tras eliminar 30: ";
    arbol.mostrarInorden();

    return 0;
}
