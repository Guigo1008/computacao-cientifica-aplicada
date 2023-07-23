#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
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

int main() {
    string comp1;
    string comp2;
    double T   = 0.; // K
    double p   = 0.; // Bar
    cout << "Insira a sigla do componente 1 desejado >> ";
    cin >> comp1;
    cout << "Insira agora a do componente 2 >> ";
    cin >> comp2;
    cout << "Insira a temperatura >> ";
    cin >> T;
    cout << "Insira a pressao >> ";
    cin >> p;

    double epsilon_dado_composto1 = ler_json("lennard.json", comp1, "epsilon");
    double sigma_dado_composto1 = ler_json("lennard.json", comp1, "sigma");
    double  epsilon_dado_composto2 = ler_json("lennard.json", comp2, "epsilon");
    double sigma_dado_composto2 = ler_json("lennard.json", comp2, "sigma");
    double massa_molecular_composto1 = ler_json("lennard.json", comp1, "MM");
    double massa_molecular_composto2 = ler_json("lennard.json", comp2, "sigma");


    double M_a = massa_molecular_composto1, M_b = massa_molecular_composto2; // g/mol

    double epsilon_a = epsilon_dado_composto1, epsilon_b = epsilon_dado_composto2; // Kelvin*(Const k)


    double sigma_a = sigma_dado_composto1, sigma_b = sigma_dado_composto2; // Å

    calcula cal(p,T);
    cal.calculinhos(M_a, M_b, epsilon_a,epsilon_b,sigma_a,sigma_b);

    std::cout << "O valor de Dab, em centimetros quadrados por segundo eh: " << cal.get_D_total() << " cm**2/s \n";
    std::cout << "Comparando com o valor obtido pela correlacao com o experimental, \n"
                 "obtem-se uma discrepancia relativa de: " << cal.get_discrepancia() << " % \n";

}
