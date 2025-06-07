
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>
using namespace std;

struct Pelicula {
    string nombre;
    int year;
    string genero;
    float recaudacion;
    Pelicula *izquierda;
    Pelicula *derecha;

    Pelicula(string n, int y, string g, float r)
        : nombre(n), year(y), genero(g), recaudacion(r), izquierda(nullptr), derecha(nullptr) {}
};

Pelicula* crearNodo(string nombre, int year, string genero, float recaudacion) {
    return new Pelicula(nombre, year, genero, recaudacion);
}

Pelicula* insertar(Pelicula* raiz, string nombre, int year, string genero, float recaudacion) {
    if (raiz == nullptr) {
        return crearNodo(nombre, year, genero, recaudacion);
    }
    if (year < raiz->year) {
        raiz->izquierda = insertar(raiz->izquierda, nombre, year, genero, recaudacion);
    } else if (year > raiz->year) {
        raiz->derecha = insertar(raiz->derecha, nombre, year, genero, recaudacion);
    } else {
        cout << "Error: Ya existe una película con el año " << year << ". No se puede insertar '" << nombre << "'." << endl;
    }
    return raiz;
}

Pelicula* encontrarMinimo(Pelicula* nodo) {
    while (nodo && nodo->izquierda != nullptr) {
        nodo = nodo->izquierda;
    }
    return nodo;
}

Pelicula* eliminarPelicula(Pelicula* raiz, string nombreEliminar) {
    if (raiz == nullptr) return nullptr;

    if (nombreEliminar == raiz->nombre) {
        if (raiz->izquierda == nullptr) {
            Pelicula* temp = raiz->derecha;
            delete raiz;
            return temp;
        } else if (raiz->derecha == nullptr) {
            Pelicula* temp = raiz->izquierda;
            delete raiz;
            return temp;
        }
        Pelicula* temp = encontrarMinimo(raiz->derecha);
        raiz->nombre = temp->nombre;
        raiz->year = temp->year;
        raiz->genero = temp->genero;
        raiz->recaudacion = temp->recaudacion;
        raiz->derecha = eliminarPelicula(raiz->derecha, temp->nombre);
    } else {
        raiz->izquierda = eliminarPelicula(raiz->izquierda, nombreEliminar);
        raiz->derecha = eliminarPelicula(raiz->derecha, nombreEliminar);
    }
    return raiz;
}

void inorden(Pelicula* raiz) {
    if (raiz != nullptr) {
        inorden(raiz->izquierda);
        cout << "Nombre: " << raiz->nombre << ", Año: " << raiz->year
             << ", Género: " << raiz->genero << ", Recaudación: "
             << fixed << setprecision(2) << raiz->recaudacion << " millones" << endl;
        inorden(raiz->derecha);
    }
}

void buscarPelicula(Pelicula* raiz, string nombreBuscar) {
    if (raiz == nullptr) return;
    if (raiz->nombre == nombreBuscar) {
        cout << "Película encontrada:\n";
        cout << "Nombre: " << raiz->nombre << ", Año: " << raiz->year
             << ", Género: " << raiz->genero << ", Recaudación: "
             << fixed << setprecision(2) << raiz->recaudacion << " millones" << endl;
        return;
    }
    buscarPelicula(raiz->izquierda, nombreBuscar);
    buscarPelicula(raiz->derecha, nombreBuscar);
}

void mostrarPeliculasPorGenero(Pelicula* raiz, string generoBuscar) {
    if (raiz != nullptr) {
        mostrarPeliculasPorGenero(raiz->izquierda, generoBuscar);
        if (raiz->genero == generoBuscar) {
            cout << "Nombre: " << raiz->nombre << ", Año: " << raiz->year
                 << ", Género: " << raiz->genero << ", Recaudación: "
                 << fixed << setprecision(2) << raiz->recaudacion << " millones" << endl;
        }
        mostrarPeliculasPorGenero(raiz->derecha, generoBuscar);
    }
}

void contarNodos(Pelicula* nodo, int& count) {
    if (nodo != nullptr) {
        contarNodos(nodo->izquierda, count);
        count++;
        contarNodos(nodo->derecha, count);
    }
}

bool compararRecaudacion(const Pelicula* a, const Pelicula* b) {
    return a->recaudacion < b->recaudacion;
}

void recolectarPeliculas(Pelicula* raiz, vector<Pelicula*>& peliculas) {
    if (raiz != nullptr) {
        recolectarPeliculas(raiz->izquierda, peliculas);
        peliculas.push_back(raiz);
        recolectarPeliculas(raiz->derecha, peliculas);
    }
}

void recolectarDatosPeliculas(Pelicula* raiz, vector<Pelicula>& peliculas) {
    if (raiz != nullptr) {
        recolectarDatosPeliculas(raiz->izquierda, peliculas);
        peliculas.push_back(*raiz);
        recolectarDatosPeliculas(raiz->derecha, peliculas);
    }
}

void mostrarFracasosTaquilleros(Pelicula* raiz) {
    if (raiz == nullptr) {
        cout << "No hay películas en el sistema." << endl;
        return;
    }

    vector<Pelicula*> peliculasPointers;
    recolectarPeliculas(raiz, peliculasPointers);

    if (peliculasPointers.size() < 3) {
        cout << "No hay suficientes películas para mostrar los 3 fracasos taquilleros." << endl;
        return;
    }

    sort(peliculasPointers.begin(), peliculasPointers.end(), compararRecaudacion);

    cout << "\nLos 3 fracasos taquilleros son:\n";
    for (int i = 0; i < 3; ++i) {
        cout << i + 1 << ". Nombre: " << peliculasPointers[i]->nombre
             << ", Año: " << peliculasPointers[i]->year
             << ", Género: " << peliculasPointers[i]->genero
             << ", Recaudación: " << fixed << setprecision(2)
             << peliculasPointers[i]->recaudacion << " millones" << endl;
    }
}

void liberarArbol(Pelicula* raiz) {
    if (raiz != nullptr) {
        liberarArbol(raiz->izquierda);
        liberarArbol(raiz->derecha);
        delete raiz;
    }
}

Pelicula* construirArbolBalanceadoDesdeVector(const vector<Pelicula>& peliculas, int inicio, int fin) {
    if (inicio > fin) return nullptr;
    int medio = inicio + (fin - inicio) / 2;
    Pelicula* nodo = crearNodo(peliculas[medio].nombre, peliculas[medio].year,
                               peliculas[medio].genero, peliculas[medio].recaudacion);
    nodo->izquierda = construirArbolBalanceadoDesdeVector(peliculas, inicio, medio - 1);
    nodo->derecha = construirArbolBalanceadoDesdeVector(peliculas, medio + 1, fin);
    return nodo;
}

Pelicula* balancearArbol(Pelicula* raiz) {
    if (raiz == nullptr) {
        cout << "El árbol está vacío, no hay nada que balancear." << endl;
        return nullptr;
    }
    vector<Pelicula> peliculasOrdenadas;
    recolectarDatosPeliculas(raiz, peliculasOrdenadas);
    liberarArbol(raiz);
    cout << "Balanceando el árbol..." << endl;
    return construirArbolBalanceadoDesdeVector(peliculasOrdenadas, 0, peliculasOrdenadas.size() - 1);
}

// ======================== MAIN ========================
int main() {
    Pelicula* raiz = nullptr;
    int opcion;

    do {
        cout << "\n===== MENÚ PELÍCULAS =====" << endl;
        cout << "1. Insertar película" << endl;
        cout << "2. Mostrar películas (inorden)" << endl;
        cout << "3. Buscar película por nombre" << endl;
        cout << "4. Mostrar películas por género" << endl;
        cout << "5. Eliminar película por nombre" << endl;
        cout << "6. Balancear árbol" << endl;
        cout << "7. Mostrar 3 fracasos taquilleros" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese opción: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpiar buffer

        string nombre, genero;
        int year;
        float recaudacion;

        switch (opcion) {
            case 1:
                cout << "Nombre: "; getline(cin, nombre);
                cout << "Año: "; cin >> year;
                cout << "Género: "; cin.ignore(); getline(cin, genero);
                cout << "Recaudación (en millones): "; cin >> recaudacion;
                raiz = insertar(raiz, nombre, year, genero, recaudacion);
                break;
            case 2:
                cout << "\nPelículas en el árbol (inorden):\n";
                inorden(raiz);
                break;
            case 3:
                cout << "Nombre a buscar: "; getline(cin, nombre);
                buscarPelicula(raiz, nombre);
                break;
            case 4:
                cout << "Género a buscar: "; getline(cin, genero);
                mostrarPeliculasPorGenero(raiz, genero);
                break;
            case 5:
                cout << "Nombre de la película a eliminar: "; getline(cin, nombre);
                raiz = eliminarPelicula(raiz, nombre);
                break;
            case 6:
                raiz = balancearArbol(raiz);
                break;
            case 7:
                mostrarFracasosTaquilleros(raiz);
                break;
            case 0:
                cout << "Saliendo..." << endl;
                liberarArbol(raiz);
                break;
            default:
                cout << "Opción inválida." << endl;
        }
    } while (opcion != 0);

    return 0;
}
