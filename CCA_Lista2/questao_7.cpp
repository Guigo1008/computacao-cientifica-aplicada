#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

inline void escreve_arquivo(const string& nome_arquivo, const string& resultado) {
    ofstream arquivo(nome_arquivo, ios::out | ios::app);
    if(arquivo.is_open()) {
        arquivo << resultado;
        arquivo.close();
    } else {
        cerr << "Nao foi possivel abrir o arquivo para escrever a resposta." << endl;
    }
}
void limpa_arquivo(const string& nome_arquivo);

int main(int argc, char** argv) {
    limpa_arquivo("questao_7_resposta.txt");
    double grav = 9.81, dist_max = 0.;

    for(int i = 0; i <= 90; i++){
        // conversao de graus para radianos
        double teta = i * M_PI / 180.0;
        double velocidade_x = 20. * cos(teta);
        double velocidade_y = 20. * sin(teta);
        double tempo_f = (2. * velocidade_y) / grav;
        double distancia_x = velocidade_x * tempo_f;

        if(dist_max < distancia_x) {
            dist_max = i;
        }

        string resposta = to_string(i) + ";" + to_string(distancia_x) + "\n";
        escreve_arquivo("questao_7_resposta.txt", resposta);
    }
    cout << "O angulo, em graus, que a distancia foi maxima foi: " << dist_max << endl;

    return 0;
}

void limpa_arquivo(const string& nome_arquivo) {
    ofstream arquivo(nome_arquivo, ios::out);
    if(arquivo.is_open()) {
        arquivo << "";
        arquivo.close();
    } else {
        cerr << "Nao foi possivel abrir o arquivo para escrever a resposta." << endl;
    }
}