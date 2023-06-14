#include <iostream>

// Exercicio 2
using namespace std;
int main() {
    double nota1;
    cout << "Digite a sua nota da primeira prova: ";
    cin >> nota1;

    double nota2;
    cout << "Digite a sua nota da segunda prova: ";
    cin >> nota2;

    double media_parcial = (nota1 + nota2) / 2.;

    cout << "A sua media parcial, considerando p1 e p2 eh " << media_parcial << "\n";
}