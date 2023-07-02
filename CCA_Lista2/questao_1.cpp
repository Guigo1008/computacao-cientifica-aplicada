#include <iostream>
#include <cmath>

using namespace std;
int main() {
    // Letra A
    double somatorio;
    for (int i = 0; i <= 100; i++) {
        for (int j = 5; j <= 300; j++) {
            somatorio += cos(pow(i, 2.) + pow(j, 0.5));
        }
    }
    cout << "O resultado do somatório da letra A é: " << somatorio << "\n";

    // Letra B
    double somatorio2;
    for (int i = 0; i <= 99; i++) {
        for (int j = 200; j <= 500; j++) {
            somatorio2 += (i - j);
        }
    }

    cout << "O resultado do somatório da letra B é: " << somatorio2 << "\n";

    // Letra C
    double produtorio;
    for (int i = 1; i <= 4; i++) {
        for (int j = -3; j <= 27; j++) {
            produtorio *= (i + pow(j, 2.));
        }
    }

    produtorio *= 5.;
    cout << "O resultado do produtório da letra C é: " << produtorio << "\n";
}