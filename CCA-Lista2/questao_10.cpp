#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;
double* abre_csv(const string& nome_arquivo, int num_de_colunas, int num_de_linhas, const char& sep);
double gerencia_prop_fisicas(const double* tabela, int num_de_colunas, int coluna_propriedade, double temperatura);
double calcula_pout(double hm, double pas, double as, double ro_b, double mpto);
double calcula_hm(double d, double l, double red, double sch, double dab);
double calcula_reynolds(double d, double mpto, double visc);
double calcula_schmidt(double visc_cin, double d);
double taxa_massica();

int main() {
    // Definindo variáveis dadas:
    double dab = 26e-6;           // m/s**2
    double d = 10e-3, l = 1.3;    // m
    double T = 25 + 273.15;       // K
    double as = M_PI*d*l;         // m**2
    auto* mpto = new double[2];   // kg/s

    for(int i = 0; i < 2; i++){
        mpto[i] = taxa_massica(); // kg/s
    }

    if (T > 645 || T < 273.15) {
        cout << "Temperatura fora da faixa." << endl;
        abort();
    }

    double *prop_ar = abre_csv("Tabela propriedades ar.txt", 5, 25, ' ');
    double *prop_agua = abre_csv("Tabela propriedades fisicas agua.txt", 12, 55, ' ');

    // Tabela propriedades fisicas ar.txt
    // T[0] Dens.[1] Cp[2] vis[3]*10**7 vis.cin[4]

    // Tabela propriedades fisicas agua.txt
    // T[0], p.vap[1], V.liq[2], V.vap[3], Calor.latente[4], cap.cal.liq[5],
    // cap.cal.vap[6], Vis.liq[7], Vis.vap[8], condut.liq[9], condut.vap[10], tensao[11]

    double visc_cin = gerencia_prop_fisicas(prop_ar, 5, 5, T);    // col5 tabela 1
    double visc = gerencia_prop_fisicas(prop_ar, 5, 4, T);        // col4 tabela 1
    double ro_b = gerencia_prop_fisicas(prop_ar, 5, 2, T);        // col1 tabela 2
    double ro_as = 1./gerencia_prop_fisicas(prop_agua, 12, 3, T); // col3 tabela 2

    double schmidt = calcula_schmidt(visc_cin, dab);

    for (int i = 0; i < 2; i++) {
        double reynolds = calcula_reynolds(d, mpto[i], visc);
        double hm = calcula_hm(d, l, reynolds, schmidt, dab);
        double pout = calcula_pout(hm, ro_as, as, ro_b, mpto[i]);
        cout << "A concentração mássica de saída quando a taxa é: " << mpto[i] << " é " << pout << "\n";
    }


    delete[] prop_ar;
    delete[] prop_agua;
    delete[] mpto;
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
    coluna_propriedade--;
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
double calcula_reynolds(double d, double mpto, double visc) {
    double reynolds = 4.*mpto/(M_PI*d*visc);
    return reynolds;
}
double calcula_schmidt(double visc_cin, double dab){
    double schmidt = visc_cin/dab;
    return schmidt;
}
double calcula_hm(double d, double l, double red, double sch, double dab) {
    double hm;
    if (10. < red && red < 2000.) { // regime laminar
        hm = 1.86*pow(d/l*red*sch, 1./3.)*dab/d;
    } else if (2000. < red && red < 35000. && 0.6 < sch && sch < 2.5) { // regime turbulento
        hm = 0.023*pow(red, 0.83)*pow(sch, 0.44)*dab/d;
    } else {
        cout << "Erro ao calcular o coeficiente de transferência de calor. Regime invalido." << endl;
        abort();
    }
    return hm;
}
double calcula_pout(double hm, double pas, double as, double ro_b, double mpto) {
    double pout = pas - pas*exp(-as*hm*ro_b/mpto);
    return pout;
}