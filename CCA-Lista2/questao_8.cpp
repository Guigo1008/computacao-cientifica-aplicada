#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;
int main(){

    float p = 1; // Barr
    double sigmaa, sigmab, ea, eb;
    double a = 1.06036, b =  0.15610, c = 0.19300,
            d = 0.47635, e = 1.03587, f = 1.52996, g = 1.76474, h = 3.89411;

    //lendo os dados armazenados no arquivo "dados.txt"

    ifstream arquivo("dados.txt", ios::in);
    string dados; //armazenamento de cada dado

    if(arquivo.is_open()){

        getline(arquivo, dados, '\n');
        sigmaa = atof(dados.c_str()); //convertendo para float

        getline(arquivo, dados, '\n');
        sigmab = atof(dados.c_str());

        getline(arquivo, dados, '\n');
        ea = atof(dados.c_str());

        getline(arquivo, dados, '\n');
        eb = atof(dados.c_str());

        arquivo.close();
    } else {
        cerr << "Erro ao abrir arquivo" << endl;
        abort();
    }

    //calculo de mab
    float ma = 44.01 , mb = 28.0134; // massa molar CO2 e N2
    double mab = 2 * ( pow(((1 / ma) + (1 / mb)),-1));

    //calculo de sigmaab
    double sigmaab = (sigmaa + sigmab) / 2;

    //calculo de eab
    double eab = sqrt(ea * eb);

    //calculo de t*
    //O k foi ignorado pois matematicamente se cancelaria ao adicionar o valor de eab * k
    auto* temp = new double[20];

    //criando um array com as temperaturas para serem colocados no loop

    double atualizador = 400.;
    for(int i= 0; i < 20; i++) {
        temp[i] = atualizador;
        atualizador += 10.;
    }

    for(int i= 0; i < 20; i++) {
        double t1 = temp[i] / eab;

        //calculo de omega
        double omega;
        omega = (a / (pow(t1, b)) + c / exp(d * t1) + e / exp(f * t1) + g / exp(h * t1));

        //calculo de dab
        float dab = 0.00266 * (pow(temp[i], 1.5) / (p * (pow(mab, 0.5)) * (pow(sigmaab, 2)) * omega));
        cout << "O valor de dab na Temperatura de " << temp[i] << "K é: " << dab << endl;


    }
    delete[] temp;
    return 0;
}