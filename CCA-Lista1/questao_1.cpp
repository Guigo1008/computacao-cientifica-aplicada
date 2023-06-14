#include <iostream>
#include <cmath>

using namespace std;

// Exercicio 1 - A
void letra_a() {
    double altura = 6.; // m
    double const_grav = 9.81; // m*s**-2
    double velocidade = sqrt(2 * const_grav * altura); // m/s

    cout << "A velocidade do corpo eh " << velocidade << " m/s" << "\n";
}

// Exercicio 1 - B
void letra_b() {
    double altura; // m
    cout << "Digite a altura, em metros, do corpo para calculo de sua velocidade terminal:" << "\n";
    cin >> altura;

    double const_grav = 9.81; // m*s**-2
    double velocidade = sqrt(2. * const_grav * altura); // m/s

    cout << "A velocidade do corpo eh " << velocidade << " m/s" << "\n";
}

int main() {
    letra_a(); // Chama a função letra_a()
    letra_b(); // Chama a função letra_b()

    return 0;
}
