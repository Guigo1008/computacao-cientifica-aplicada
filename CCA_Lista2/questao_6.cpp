#include <iostream>
#include <cmath>

using namespace std;

double* inicializa_array();
unsigned int tamanho;

int main(int argc, char** argv) {
    double soma1 = 0, soma2 = 0, media, desvio_padrao;
    auto* array_valores = inicializa_array();

    // Calculando a media
    for(int i = 0; i < tamanho; i++){
        soma1 += array_valores[i];
    }
    media = soma1/tamanho;

    // Calculando o Desvio Padrao
    for(int i = 0; i < tamanho; i++){
        soma2 += pow(array_valores[i], 2.);
    }
    desvio_padrao = sqrt((tamanho * soma2 - pow(soma1, 2.))
            / tamanho / (tamanho-1));

    cout << "A media encontrada para esses valores eh: " << media << "\n";
    cout << "O desvio padrao encontrado para esses valores eh: " << desvio_padrao << "\n";
}

double* inicializa_array() {
    string valores;
    cout << "Quantos valores voce deseja inserir? ";
    cin >> tamanho;
    auto* array_valores = new double[tamanho];

    for(int i = 0; i < tamanho; i++){
        cout << "Insira os valores, um a um, que voce deseja inserir: ";
        cin >> array_valores[i];
        if(array_valores[i] < 0) {
            cout << "Infelizmente, neste codigo, valores negativos nao sao permitidos." << endl;
            return 0;
        }
    }

    return array_valores;
}



