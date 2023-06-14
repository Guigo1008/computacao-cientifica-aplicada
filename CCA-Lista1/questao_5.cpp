#include <iostream>

// Exercicio 5
using namespace std;
int main() {
    double temp_fahr; // ºF
    cout << "Digite a temperatura, em fahrenheit, desejada para a conversao: ";
    cin >> temp_fahr;

    double temp_kelvin = (temp_fahr - 32) * 5/9 + 273; // K

    cout << "A temperatura dada, convertida para kelvins vale:  " << temp_kelvin << "\n";
}
