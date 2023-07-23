#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <utility>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

class calcula {
private:

    double pressao;
    double temperatura;
    double D_total;

public:
    calcula(double pressao, double temperatura) {

        this->pressao = pressao;
        this->temperatura = temperatura;

    }
    void calculinhos(double M_a, double M_b, double epsilon_a, double epsilon_b, double sigma_a, double sigma_b){
        double A   = 1.06036, B = 0.15610, C = 0.19300, D = 0.47635, E = 1.03587,
                F = 1.52996, G = 1.76474, H = 3.89411;
        // (A constante K ira cortar logo depois, entao nao foi considerada para as contas)

        double epsilon_total = sqrt(epsilon_a * epsilon_b); // Kelvin*(Const k)
        double sigma_total = (sigma_a + sigma_b) / 2 ; // Å
        double T_ast = temperatura/epsilon_total;

        double omega_D = pow(A/T_ast,B) + C/exp(D*T_ast) + E/exp(F*T_ast) + G/exp(H*T_ast);
        double M_total = 2/(1 / M_b + 1 / M_a); // g/mol
        D_total = 0.00266 * pow(temperatura, 1.5) / pressao / pow(M_total, 0.5) / pow(sigma_total, 2) / omega_D; // cm**2/s

    }
    double get_D_total(){
        return D_total;
    }

    double get_discrepancia(){
        double discrep_relativa = abs(D_total - 0.583) / 0.583; // Adimensional
        return discrep_relativa;
    }

};


class prop_fisicas {
private:
    string especie_aplicada; // escolher entre agua e ar
    double temperatura; // valor na escala absoluta (K)

    static double* abre_csv(const string& nome_arquivo, int num_de_colunas, int num_de_linhas, const char& sep=';') {
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

    static double interpolar(const double* tabela, int num_de_colunas, int coluna_propriedade, double temperatura) {
        int i = 0;
        coluna_propriedade--;
        while(true) {
            if(temperatura >= tabela[i*num_de_colunas] && temperatura < tabela[(i+1)*num_de_colunas]) {
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

public:
    prop_fisicas (string especie, double temp){
        this->especie_aplicada = std::move(especie);
        this->temperatura = temp;
    }

    double propriedade(int propriedade){
        if (especie_aplicada == "ar" || especie_aplicada == "AR" || especie_aplicada == "Ar") {
            double* prop_ar = abre_csv("Tabela propriedades ar.txt", 5, 25, ' ');
            // 0 - temp, 1 - massa_esp, 2 - Cp, 3 - Visc. Din., 4 - Visc. Cin.
            double propriedadef = interpolar(prop_ar, 5, propriedade, this->temperatura);
            delete[] prop_ar;
            return propriedadef;

        } else if (especie_aplicada == "agua" || especie_aplicada == "água" || especie_aplicada == "Água" || especie_aplicada == "ÁGUA") {
            double* prop_agua = abre_csv("Tabela propriedades fisicas agua.txt", 12, 55, ' ');
            // T[0], p.vap[1], V.liq[2], V.vap[3], Calor.latente[4], cap.cal.liq[5],
            // cap.cal.vap[6], Vis.liq[7], Vis.vap[8], condut.liq[9], condut.vap[10], tensao[11]
            double propriedadef = interpolar(prop_agua, 12, propriedade, this->temperatura);
            delete[] prop_agua;
            return propriedadef;
        } else {
            cout << "o nome da especie aplicada deve ser agua ou ar. Rode o programa novamente." << endl;
            abort();
        }
    }
};

class coeficientes_vazao_massica {
private:
    double D;
    double L;
    double DAB;
    double taxa_massica;
    double visc;
    double visc_cin;
    double ro_b;
    double ro_as;
    double As;

public:
    coeficientes_vazao_massica(double D, double L, double Dab, double taxa_massica, double visc, double visc_cin, double ro_b, double ro_as) {
        this->D = D;
        this->L = L;
        this->DAB = Dab;
        this->taxa_massica = taxa_massica;
        this->visc = visc;
        this->visc_cin = visc_cin;
        this->ro_b = ro_b;
        this->ro_as = ro_as;
        this->As = M_PI*D*L;
    }

    double calcula_reynolds() {
        double reynolds = 4.*taxa_massica/(M_PI*D*visc);
        return reynolds;
    }

    double calcula_schmidt(){
        double schmidt = visc_cin / DAB;
        return schmidt;
    }

    double calcula_hm(double red, double sch) {
        double hm;
        if (10. < red && red < 2000.) { // regime laminar
            hm = 1.86*pow(D/L*red*sch, 1./3.)*DAB/D;
        } else if (2000. < red && red < 35000. && 0.6 < sch && sch < 2.5) { // regime turbulento
            hm = 0.023*pow(red, 0.83)*pow(sch, 0.44)*DAB/D;
        } else {
            cout << "Erro ao calcular o coeficiente de transferencia de calor. Regime invalido." << endl;
            abort();
        }
        return hm;
    }

    double calcula_pout(double hm) {
        double pout = this->ro_as - this->ro_as*exp(-this->As*hm*this->ro_b/this->taxa_massica);
        return pout;
    }
};

double ler_json(const string& nome_json, const string& subst1, const string& prop) {
    double dado = 0;
    ifstream f(nome_json);
    if (f.is_open()) {
        json data = json::parse(f);
        dado = data.at(subst1).at(prop);
    } else {
        cerr << "Erro ao abrir o arquivo com os dados." << "\n";
    }
    return dado;
}

int main(){
    double D = 10e-3, L = 1.3, DAB;
    double taxa_massica1 = 2.2e-4, taxa_massica2 = 4e-6, taxa_massica3 = 1e-5, taxa_massica4 = 2e-4;
    double temp = 298.15, p = 1.;

    prop_fisicas ar = prop_fisicas("Ar", temp);
    prop_fisicas agua = prop_fisicas("agua", temp);
    double eps1 = ler_json("lennard.json", "H2O", "epsilon");
    double sig1 = ler_json("lennard.json", "H2O", "sigma");
    double MM1 = ler_json("lennard.json", "H2O", "MM");
    double eps2 = ler_json("lennard.json", "Air", "epsilon");
    double sig2 = ler_json("lennard.json", "Air", "sigma");
    double MM2 = ler_json("lennard.json", "Air", "sigma");

    calcula cal(p,temp);
    cal.calculinhos(MM1, MM2, eps1,eps2,sig1,sig2);

    DAB = cal.get_D_total() * 1e-6; // converte-se para m^2/s
    cout << DAB << endl;

    double viscosidade_ar = ar.propriedade(4);
    double viscosidade_cin_ar = ar.propriedade(5);
    double ro_b = ar.propriedade(2);
    double ro_as = 1./agua.propriedade(3);

    coeficientes_vazao_massica teste1 = coeficientes_vazao_massica(D, L, DAB, taxa_massica1, viscosidade_ar, viscosidade_cin_ar, ro_b, ro_as);
    double reynolds1 = teste1.calcula_reynolds();
    double schmidt1 = teste1.calcula_schmidt();
    double hm1 = teste1.calcula_hm(reynolds1, schmidt1);
    double pout1 = teste1.calcula_pout(hm1);
    cout << "A taxa massica de saida eh " << pout1 << "\n";

    coeficientes_vazao_massica teste2 = coeficientes_vazao_massica(D, L, DAB, taxa_massica2, viscosidade_ar, viscosidade_cin_ar, ro_b, ro_as);
    double reynolds2 = teste2.calcula_reynolds();
    double schmidt2 = teste2.calcula_schmidt();
    double hm2 = teste2.calcula_hm(reynolds2, schmidt2);
    double pout2 = teste2.calcula_pout(hm2);
    cout << "A taxa massica de saida eh " << pout2 << "\n";

    coeficientes_vazao_massica teste3 = coeficientes_vazao_massica(D, L, DAB, taxa_massica3, viscosidade_ar, viscosidade_cin_ar, ro_b, ro_as);
    double reynolds3 = teste3.calcula_reynolds();
    double schmidt3 = teste3.calcula_schmidt();
    double hm3 = teste3.calcula_hm(reynolds3, schmidt3);
    double pout3 = teste3.calcula_pout(hm3);
    cout << "A taxa massica de saida eh " << pout3 << "\n";

    coeficientes_vazao_massica teste4 = coeficientes_vazao_massica(D, L, DAB, taxa_massica4, viscosidade_ar, viscosidade_cin_ar, ro_b, ro_as);
    double reynolds4 = teste4.calcula_reynolds();
    double schmidt4 = teste4.calcula_schmidt();
    double hm4 = teste4.calcula_hm(reynolds4, schmidt4);
    double pout4 = teste4.calcula_pout(hm4);
    cout << "A taxa massica de saida eh " << pout4 << "\n";

    return 0;
}
