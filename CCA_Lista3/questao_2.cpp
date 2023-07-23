#include <iostream>
#include <fstream>
#include <string>
#include <utility>

using namespace std;

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

int main() {
    double temperatura = 298.15;
    prop_fisicas ar = prop_fisicas("Ar", temperatura);

    double viscosidade_ar = ar.propriedade(4);
    double viscosidade_cin_ar = ar.propriedade(5);

    cout << "O valor da viscosidade do ar na temperatura de " <<  temperatura << " eh de " << viscosidade_ar << "\n";
    cout << "O valor da viscosidade cinematica do ar na temperatura de " <<  temperatura << " eh de " << viscosidade_cin_ar << "\n";

    return 0;
}
