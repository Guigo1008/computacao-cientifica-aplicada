#include <iostream>
#include <cmath>

// Exercicio 3
using namespace std;
int main() {
    double x;
    cout << "Digite o valor de x desejado para que se calcule o cosseno hiperbolico: ";
    cin >> x;

    double cosh_x = (exp(x) + exp(-x)) / 2.;

    cout << "O cosseno hiperbolico calculado por mim vale: " << cosh_x << "\n";
    cout << "O cosseno hiperbolico nativo da biblioteca cmath vale: " << cosh(x) << "\n";
}