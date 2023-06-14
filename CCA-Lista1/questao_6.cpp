#include <iostream>
#include <cmath>

// Exercicio 6
using namespace std;
int main() {
    double t[2];
    double med_temp_diaria[3][2];

    cout << "Insira o dia 1 para o calculo da temperatura media: ";
    cin  >> t[0];
    cout << "Insira o dia 2 para o calculo da temperatura media: ";
    cin  >> t[1];

    double temp_media_anual[3] = {22.1, 10.6, 10.7}; // (Tm) Miami, Seattle, Boston
    double dia_temp_pico[3]    = {28.3, 17.6, 22.9}; // (Tp) Miami, Seattle, Boston
    double freq_anual_var      = 2. * M_PI / 365.; // (w) Miami, Seattle, Boston

    for(int j = 0; j < 2; j++) {
        for(int i = 0; i < 3; i++) {
            string aux;
            med_temp_diaria[i][j] = temp_media_anual[i] + (dia_temp_pico[i] - temp_media_anual[i]) * cos(freq_anual_var * (t[j] - dia_temp_pico[i]));
            if (i == 0) {
                aux = "Miami";
            } else if (i == 1) {
                aux = "Seattle";
            } else {
                aux = "Boston";
            }
            cout << "Para o dia " << t[j] << ", a temperatura media em " << aux << " eh: " << med_temp_diaria[i][j] << "\n";
        }
    }
}