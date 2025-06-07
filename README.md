struct Nodo** arreglo;
estamos diciendo que arreglo es un puntero a un puntero de tipo Nodo,
es decir, un arreglo de punteros a nodos.
Esto es necesario porque queremos almacenar varios punteros a struct Nodo,
no solo uno. En C, los arreglos dinámicos se representan como punteros,
y un arreglo de punteros se representa como un puntero a puntero.
