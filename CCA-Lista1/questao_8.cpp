#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
double* abre_arquivo(const string& nome_arquivo);

int main() {
    cout.setf(ios_base::scientific);

    double* lista_dados = abre_arquivo("dados_questao_8.txt");
// sigma_a[0], sigma_b[1], epsilon_a[2], epsilon_b[3], m_molar_a[4], m_molar_b[5]

    double T   = 590.; // K
    double p   = 1.; // Bar
    double M_a = lista_dados[4], M_b = lista_dados[5]; // g/mol
    double A   = 1.06036, B = 0.15610, C = 0.19300, D = 0.47635, E = 1.03587,
            F = 1.52996, G = 1.76474, H = 3.89411;

    double epsilon_a = lista_dados[2], epsilon_b = lista_dados[3]; // Kelvin*(Const k)
// (A constante K ira cortar logo depois, entao nao foi considerada para as contas)

    double epsilon_total = sqrt(epsilon_a * epsilon_b); // Kelvin*(Const k)

    double sigma_a = lista_dados[0], sigma_b = lista_dados[1]; // Å
    double sigma_total = (sigma_a + sigma_b) / 2 ; // Å

    double T_ast = T/epsilon_total;
    double omega_D = pow(A/T_ast,B) + C/exp(D*T_ast) + E/exp(F*T_ast) + G/exp(H*T_ast);
    double M_total = 2/(1 / M_b + 1 / M_a); // g/mol

    double D_total = 0.00266 * pow(T, 1.5) / p / pow(M_total, 0.5) / pow(sigma_total, 2) / omega_D; // cm**2/s
    double discrep_relativa = abs(D_total - 0.583) / 0.583; // Adimensional

    cout << "O valor de Dab, em centimetros quadrados por segundo eh: " << D_total << " cm**2/s \n";
    cout << "Comparando com o valor obtido pela correlacao com o experimental, \n"
            "obtem-se uma discrepancia relativa de: " << discrep_relativa << "% \n";
}

double* abre_arquivo(const string& nome_arquivo) {
    // O arquivo em questao foi feito de forma que todos os valores
    // estao armazenados e separados cada um por ; na seguinte ordem:
    // sigma_a, sigma_b, epsilon_a, epsilon_b, massa_molar_a, massa_molar_b
    string auxiliar;
    auto* array = new double[6];
    ifstream my_data(nome_arquivo, ios::in);
    if(my_data.is_open()) {
        getline(my_data, auxiliar, ';');
        array[0] = stod(auxiliar);
        getline(my_data, auxiliar, ';');
        array[1] = stod(auxiliar);
        getline(my_data, auxiliar, ';');
        array[2] = stod(auxiliar);
        getline(my_data, auxiliar, ';');
        array[3] = stod(auxiliar);
        getline(my_data, auxiliar, ';');
        array[4] = stod(auxiliar);
        getline(my_data, auxiliar, ';');
        array[5] = stod(auxiliar);

        my_data.close();
    } else {
        cerr << "Erro ao abrir o arquivo com os dados." << endl;
    }
    return array;
}