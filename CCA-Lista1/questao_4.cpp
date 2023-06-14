#include <iostream>

// Exercicio 4
using namespace std;
int main() {
    cout.setf(ios_base::scientific);
    double massa_kg; // kg
    cout << "Digite a massa, em kilograma, desejada para a conversão: ";
    cin >> massa_kg;

    double massa_g  = massa_kg / 1000.; // g
    double massa_mg = massa_kg / 1000000.; // mg
    double massa_lb = massa_kg * 2.20462262185; // lb
    double massa_oz = massa_kg * 35.2739619; // oz

    cout << "A massa dada, convertida para gramas eh "     << massa_g  << "\n";
    cout << "A massa dada, convertida para miligramas eh " << massa_mg << "\n";
    cout << "A massa dada, convertida para libras eh "     << massa_lb << "\n";
    cout << "A massa dada, convertida para onces eh "      << massa_oz << "\n";
}