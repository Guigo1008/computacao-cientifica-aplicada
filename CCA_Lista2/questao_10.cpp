#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;
double* abre_csv(const string& nome_arquivo, int num_de_colunas, int num_de_linhas, const char& sep);
double gerencia_prop_fisicas(const double* tabela, int num_de_colunas, int coluna_propriedade, double temperatura);
double taxa_massica();

int main() {
    // Definindo variáveis dadas:
    double dab = 25e-6;           // m/s**2
    double d = 10e-3, l = 1.3;    // m
    double T = 25 + 273.15;       // K
    double p = 1.;                // Atm
    double as = M_PI*d*l;         // m**2
    double mpto = taxa_massica(); // kg/s

    if (T > 645 || T < 273.15) {
        cout << "Temperatura fora da faixa." << endl;
        abort();
    }

    // Tabela propriedades fisicas ar.txt
    // T[0] Dens.[1] Cp[2] vis[3]*10**7 vis.cin[4]
    double *prop_ar = abre_csv("Tabela propriedades ar.txt", 5, 25, ' ');
    double *prop_agua = abre_csv("Tabela propriedades fisicas agua.txt", 12, 55, ' ');

    // Tabela propriedades fisicas agua.txt
    // T[0], p.vap[1], V.liq[2], V.vap[3], Calor.latente[4], cap.cal.liq[5],
    // cap.cal.vap[6], Vis.liq[7], Vis.vap[8], condut.liq[9], condut.vap[10], tensao[11]
    double visc_cin = gerencia_prop_fisicas(prop_ar, 5, 4, T); // col4 tabela 1
    double visc = gerencia_prop_fisicas(prop_ar, 5, 3, T);     // col3 tabela 1
    double ro_agua = gerencia_prop_fisicas(prop_agua, 12, 2, T); // col2 tabela 2



    delete[] prop_ar;
    delete[] prop_agua;
}

double* abre_csv(const string& nome_arquivo, int num_de_colunas, int num_de_linhas, const char& sep=';') {
    string auxiliar;
    double num_aux;
    auto* array = new double[num_de_colunas * num_de_linhas];

    ifstream my_data(nome_arquivo);
    if (my_data.is_open()) {
        for(int i = 0; i < num_de_linhas; i++) {
            for(int j = 0; j < num_de_colunas; j++) {
                getline(my_data, auxiliar, sep);
                num_aux = stod(auxiliar);
                array[i*num_de_colunas + j] = num_aux;
            }
            std::getline(my_data, auxiliar, '\n');
        }
        my_data.close();
    } else {
        cerr << "Erro ao abrir o arquivo com os dados." << endl;
    }
    return array;
}
double taxa_massica(){
    double mpto;
    cout << "Insira a taxa de massa de vapor de agua: ";
    cin  >> mpto;

    if (mpto < 0) {
        cout << "Taxa mássica negativa." << endl;
        abort();
    }

    return mpto;
}
double gerencia_prop_fisicas(const double* tabela, int num_de_colunas, int coluna_propriedade, double temperatura) {
    int i = 0;

    while(true) {
        if(temperatura > tabela[i*num_de_colunas] && temperatura < tabela[(i+1)*num_de_colunas]) {
            break;
        } else {
            i++;
        }
    }

    double el_1 = tabela[i*num_de_colunas + coluna_propriedade];
    double t_1 = tabela[i*num_de_colunas];
    double el_2 = tabela[(i+1)*num_de_colunas + coluna_propriedade];
    double t_2 = tabela[(i+1)*num_de_colunas];
    double interpolar = (el_2 - el_1)/(t_2 - t_1) * (temperatura - t_1) + el_1;

    return interpolar;
}
double calcula_reynolds(double dab, double d, double l, double visc_cin) {
    double reynolds = dab*d/(visc_cin*l);
    return reynolds;
}