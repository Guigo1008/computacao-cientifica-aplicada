#include <iostream>
#include <cmath>

using namespace std;
int main() {
    cout.setf(ios_base::scientific);
    double E = 1e5; // J/(mol.K)
    double Ko = 7e16; // s**-1
    double R = 8.31446261815324; // Const. Univ. dos gases J/(mol.K)
    double Ta; // Temperatura na escala absoluta

    cout << "Digite a temperatura em Kelvin: ";
    cin >> Ta;

    double K = Ko * exp(-E/(R*Ta));
    cout << "O valor do parâmetro cinético de reação é: " << K << " s**-1" << "\n";

    return 0;
}
