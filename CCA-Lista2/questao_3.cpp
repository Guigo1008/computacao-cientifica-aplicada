#include <iostream>
#include <cmath>
using namespace std;

int main(){

    double x = 1.0;
    double b;

    cout<< "Insira o valor de b: ";
    cin>> b;

    //definindo o algoritimo

    while(1) {

        double y = 0.5 * (x + (b / x));

        if (abs(x-y) < 1e-14){
            break;
        }
        else{
            x = y;
        }
    }

    cout<< "A raiz quadrada de " << b << " eh " << x << endl;

    //comparando com a raiz sqrt do cmath

    cout<< "A raiz quadrada de acordo com o cmath de " << b << " eh " << sqrt(b) << endl;

    //calculando o erro relativo

    double erro = abs((x - sqrt(b)) / sqrt(b));

    cout<< "O erro relativo eh " << erro << endl;

    return 0;
}