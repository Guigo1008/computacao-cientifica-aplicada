#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;
double* abre_csv(const string& nome_arquivo, int num_de_colunas, int num_de_linhas, const char& sep=',');

class dicionario{
    string* lista_indices;
    double* lista_valores;

public:
    dicionario(double* lista_indices, double* lista_valores){
        lista_indices = lista_indices;
        lista_valores = lista_valores;
    };

    double operator[](const string& buscar_valor){
        int tamanho_array = sizeof(lista_valores) / sizeof(double);
        for(int i=0; i < tamanho_array; i++){
            if (buscar_valor == lista_indices[i]) {
                return lista_valores[i];
            }
        }
        return -1.;
    };
};

int main() {
    cout.setf(ios_base::scientific);

    double* lista_dados = abre_csv("lennard_jones_param.csv", 4, 13);

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

    double lista_valores[3] {1,2,3};
    string lista_indices[3] {"peixe", "caminhao", "teste"};
    dicionario(lista_indices, lista_valores);
    cout << "testando o" << lista_dados[1] << endl;
    cout << "O valor de Dab, em centimetros quadrados por segundo eh: " << D_total << " cm**2/s \n";
    cout << "Comparando com o valor obtido pela correlacao com o experimental, \n"
            "obtem-se uma discrepancia relativa de: " << discrep_relativa << "% \n";

    delete[] lista_dados;
}

double* abre_csv(const string& nome_arquivo, int num_de_colunas, int num_de_linhas, const char& sep) {
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
