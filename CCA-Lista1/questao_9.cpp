#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

double* abre_arquivo(const string& nome_arquivo);
void escreve_arquivo(const string& nome_arquivo, double resultado);

int main() {
    double* lista_dados = abre_arquivo("dados_questao_9.txt");
// D[0], v[1]
    double diametro         = lista_dados[0]; // m
    double vel_escoamento   = lista_dados[1]; // m/s
    double coef_difusao_ar  = 0.26e-4;        // m**2/s

    // Interpolando para descobrir os valores:
    // Viscosidade dinâmica, massa específica e concentração mássica a 298K.
    double visc_din_ar_300      = 184.6e-7; // N*s/m**2
    double visc_din_ar_250      = 159.6e-7; // N*s/m**2
    double visc_din_ar_298      = visc_din_ar_250 + (298. - 250.) / (300. - 250.) * (visc_din_ar_300 - visc_din_ar_250); // N*s/m**2
    double massa_esp_ar_300     = 1.1614; // Kg/m**3
    double massa_esp_ar_250     = 1.3947; // Kg/m**3
    double massa_esp_ar_298     = massa_esp_ar_250 + (298. - 250.) / (300. - 250.) * (massa_esp_ar_300 - massa_esp_ar_250); // Kg/m**3
    double conc_massica_300     = 1/1.003e-3;  // m**3/kg
    double conc_massica_295     = 1/1.002e-3;  // m**3/kg
    double conc_massica_298     = conc_massica_295 + (298. - 295.) / (300. - 295.) * (conc_massica_300 - conc_massica_295); // m**3/kg


    double reynolds = massa_esp_ar_298 * vel_escoamento * diametro / visc_din_ar_298;
    if (reynolds <= 50 || reynolds >= 5e3) {
        cout << "Os valores fornecidos no arquivo texto geram um numero de Reynolds incompativel: " << reynolds << endl;
        return 0;
    }

    double schmidt = visc_din_ar_298 / massa_esp_ar_298 / coef_difusao_ar;

    double coef_trans_massa = (2. + 0.552 * pow(reynolds, 0.5) *
            pow(schmidt, 1/3)) * coef_difusao_ar / diametro; // m/s

    double fluxo_massico = coef_trans_massa * conc_massica_298; // kg/(m**2*s)
    cout << fluxo_massico << endl;

    escreve_arquivo("resultado_questao_9.txt", fluxo_massico);
    return 0;
}

double* abre_arquivo(const string& nome_arquivo) {
    // O arquivo em questao foi feito de forma que todos os valores
    // estao armazenados e separados cada um por ";" na seguinte ordem:
    // D, v
    string auxiliar;
    auto* array = new double[2];
    ifstream my_data(nome_arquivo, ios::in);
    if(my_data.is_open()) {
        getline(my_data, auxiliar, ';');
        array[0] = stod(auxiliar);
        getline(my_data, auxiliar, ';');
        array[1] = stod(auxiliar);

        my_data.close();
    } else {
        cerr << "Nao foi possivel abrir o arquivo contendo os dados." << endl;
    }
    return array;
}

void escreve_arquivo(const string& nome_arquivo, double resultado) {
    ofstream arquivo(nome_arquivo, ios::out);
    if(arquivo.is_open()) {
        arquivo << resultado << ";";
        arquivo.close();
    } else {
        cerr << "Nao foi possivel abrir o arquivo para escrever a resposta." << endl;
    }
}