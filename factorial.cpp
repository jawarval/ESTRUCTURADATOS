#include <iostream>
using namespace std;


int factorial(int n){
    if(n == 0)
        return 1;    
    else 
        return n * factorial(n-1);
}

int main(){
    int n;
    cout <<"ingrese el valor a calcular factorial :";
    cin >> n;

    if ( n < 0) {
        cout << "El factorial no está definido para números negativos." << endl;  
    }else{
        int resultado = factorial(n);
        cout <<"el resultado  factorial del numero  " << n << " es : " << resultado << endl;
    }
    
    
    return 0;
}
