#include <iostream>
#include <fstream>

using namespace std;

double* cria_matriz_temperaturas();
int* cria_array_mudar();

int main() {

    int soma_array_mudar;
    auto *aux = new double[100];
    int *array_mudar = cria_array_mudar();
    double *matriz_temp = cria_matriz_temperaturas();

    //calculando as temperaturas em cada no

    while (true) {
        for (int i = 1; i < 9; i++) {
            for (int j = 1; j < 9; j++) {
                aux[i * 10 + j] = (matriz_temp[(i + 1) * 10 + j] + matriz_temp[(i - 1) * 10 + j]
                                   + matriz_temp[i * 10 + (j + 1)] + matriz_temp[i * 10 + (j - 1)]) / 4.;

                //decidindo quais nos mudarao de temperatura

                if ((abs(matriz_temp[i * 10 + j] - aux[i * 10 + j]) > 0.001) &&
                    (abs(matriz_temp[i * 10 + j] - 100.) > 0.001)) {
                    array_mudar[i * 10 + j] = 1;
                } else {
                    array_mudar[i * 10 + j] = 0;
                }
            }
        }

        //caso em que mudara
        for (int i = 0; i < 100; i++) {
            if (array_mudar[i] == 1) {
                matriz_temp[i] = aux[i];
            }
        }

        for (int i = 0; i < 100; i++) {
            soma_array_mudar += array_mudar[i];
        }

        //caso em que nao mudara mais

        if (soma_array_mudar == 0) {
            break;
        }
        soma_array_mudar = 0;
    }

    ofstream tabela("res_q5.txt", ios::out);
    if (tabela.is_open()) {

        // escrevendo os resultados no arquivo txt

        for (int i = 0; i < 10; i++) {
            tabela << "|" << " ";
            tabela << matriz_temp[i * 10 + 0] << " ";
            tabela << matriz_temp[i * 10 + 1] << " ";
            tabela << matriz_temp[i * 10 + 2] << " ";
            tabela << matriz_temp[i * 10 + 3] << " ";
            tabela << matriz_temp[i * 10 + 4] << " ";
            tabela << matriz_temp[i * 10 + 5] << " ";
            tabela << matriz_temp[i * 10 + 6] << " ";
            tabela << matriz_temp[i * 10 + 7] << " ";
            tabela << matriz_temp[i * 10 + 8] << " ";
            tabela << matriz_temp[i * 10 + 9] << "|" << "\n";
        }
        tabela.close();

        //printando em tela a temperatura do no 5,5

        cout << matriz_temp[5*10+5] << endl;

        //deletando arrays para nao vazar memoria

        delete[] aux;
        delete[] array_mudar;
        delete[] matriz_temp;
        return 0;
    }
}

//criando a matriz

double* cria_matriz_temperaturas(){
    auto* matriz = new double[100];

    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            matriz[i*10 + j] = 20.;
        }
    }

    matriz[2*10 + 7] = 100.;
    return matriz;
}

//criando um array com identificacoes em 0 para todos os nos

int* cria_array_mudar() {
    auto* array = new int[100];

    for(int i=0; i<100; i++){
        array[i] = 0;
    }
    return array;
}
