#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

double* calcular_gamma(const double* xi, const double* tau,const double* gij);
double* ler_json(const string& nome_json, const string& subst1, const string& subst2);
double* calcula_tau(const double* aij, const double* bij, const double& T);
double* calcula_fator_interacao_nrtl(const double* tau, const double* cij);
double temperatura();
double* fracao_molar();

int main(){
    double* xi = fracao_molar();
    double T = temperatura();

    string subst1 = "Methanol",
           subst2 = "Benzene";

    double* aij = ler_json("nrtl_aij_data.json", subst1, subst2);
    double* bij = ler_json("nrtl_bij_data.json", subst1, subst2);
    double* cij = ler_json("nrtl_cij_data.json", subst1, subst2);

    double* tau = calcula_tau(aij, bij, T);
    double* gij = calcula_fator_interacao_nrtl(tau, cij);
    double* gamma = calcular_gamma(xi, tau, gij);

    cout.setf(ios_base::scientific);
    cout << "Os valores da matriz que estima o coeficiente de atividade são: " << endl;
    cout << "| " << gamma[0] << " "<< gamma[1] << " |\n"
         << "| " << gamma[2] << " " << gamma[3] << " |\n";

    delete[] gij;
    delete[] tau;
    delete[] aij;
    delete[] bij;
    delete[] cij;
    delete[] xi;
    delete[] gamma;
}

double* calcular_gamma(const double* xi, const double* tau,const double* gij) {
    auto* gamma = new double[4]();

    auto* soma1 = new double[4]();
    // Somatorio 1 (Varrer Colunas)
    for(int j = 0; j < 2; j++){
        for(int i = 0; i < 2; i++) {
            soma1[j*2+i] = xi[j] * tau[j*2+i] * gij[j*2+i]; // tau e gij são matrizes([i*colums + j])
        }
    }

    auto* soma2 = new double[4]();
    for(int j = 0; j < 2; j++){
        for(int i = 0; i < 2; i++) {
            soma2[j*2+i] = xi[i] * gij[i*2]; // Gij é matriz e precisa ser acessado com ([i*colums + j])
        }
    }

    auto* soma3 = new double[4]();
    for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
            soma3[j*2+k] += xi[j] * gij[k*2+j]
                    /xi[k] / gij[j*2+k]; // Gij, no numerador, é transposta e multiplicada.
        }
    }

    auto* soma4 = new double[4]();
    for (int m = 0; m < 2; m++) {
        for (int j = 0; j < 2; j++) {
            soma4[m*2+j] = xi[m] * tau[m*2+j] * gij[m*2+j];
        }
    }

    auto* soma5 = new double[4]();
    for (int k = 0; k < 2; k++) {
        for (int j = 0; j < 2; j++) {
            soma5[k*2+j] = xi[k] * gij[k*2+j];
        }
    }

    for (int i = 0; i < 4; i++) {
        gamma[i] = exp((soma1[i] / soma2[i]) + soma3[i] * (tau[i] - (soma4[i] / soma5[i])));
    }

    delete[] soma1;
    delete[] soma2;
    delete[] soma3;
    delete[] soma4;
    delete[] soma5;
    return gamma;
}

double* fracao_molar(){
    auto* frac_molar = new double[2];

    for(int i = 0; i < 2; i++){
        do {
            cout << "Escreva o valor entre 0 e 1 desejado para a fracao molar: ";
            cin  >> frac_molar[i];
        } while(frac_molar[i] < 0. || frac_molar[i] > 1.);
    }

    return frac_molar;
}

double temperatura(){
    double T;

    do {
        cout << "Escreva o valor da temperatura desejada, em Kelvin (maior que 0): ";
        cin  >> T;
    } while(T < 0.);

    return T;
}

double* ler_json(const string& nome_json, const string& subst1, const string& subst2) {
    auto* array = new double[4];

    array[0] = array[3] = 0.;

    ifstream f(nome_json);
    if (f.is_open()) {
        json data = json::parse(f);
        array[1] = data.at(subst1).at(subst2);
        array[2] = data.at(subst2).at(subst1);
    } else {
        cerr << "Erro ao abrir o arquivo com os dados." << "\n";
    }

    return array;
}

double* calcula_tau(const double* aij, const double* bij, const double& T) {
    auto* array = new double[4];

    for(int i = 0; i < 4; i++){
        array[i] = aij[i] + bij[i] / T;
    }

    return array;
}

double* calcula_fator_interacao_nrtl(const double* tau, const double* cij) {
    auto* array = new double[4];

    for(int i = 0; i < 4; i++){
        array[i] = exp(-tau[i] * cij[i]);
    }

    return array;
}

