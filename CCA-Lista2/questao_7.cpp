#include <iostream>
#include <cmath>
#include <matplot/matplot.h>
#include <vector>


using namespace std;

int main(){
    //definindo as variaveis
    double v0 = 20., x0 = 0.,t, g = 9.81;

    //criando os arrays
    auto* array_distancia = new double[91];
    auto* array_teta = new double[91];
    auto* array_tempo = new double[91];

    //calculando o tetas
    for(int teta = 0; teta <= 90; teta++){
        double tetarad = teta * M_PI / 180.;
        array_teta[teta] = tetarad;
    }

    //calculando o tempo de voo para todos os tetas
    for(int i = 0.; i <= 90; i++) {
        t = (2. * v0 * sin(array_teta[i])) / g;
        array_tempo[i] = t;
    }

    //calculando a distancia
    for(int i = 0; i < 91; i++){
        double x = x0 + (v0 * cos(array_teta[i]) * array_tempo[i]);
        array_distancia[i] = x;
    }

    //verificando o alcance maximo
    double xmax = array_distancia[0];
    double tetamax = array_teta[0];

    for(int i = 1; i < 91; i++){
        if (array_distancia[i] > xmax){
            xmax = array_distancia[i];
            tetamax = array_teta[i];
        }
    }

    //Deletando os arrays para recuperar a memória
    delete[] array_distancia;
    delete[] array_teta;
    delete[] array_tempo;

    //calculando as alturas para o teta de deslocamento horizontal maximo
    auto* array_altura_tetamax = new double[20];
    auto* array_tempo_tetamax = new double[20];
    double t_tetamax = 0.;

    for(int i=0; i < 20; i++){
        array_tempo_tetamax[i] = t_tetamax;
        t_tetamax += 0.15;
    }

    //Colocando o sinal de menos na equacao pois g funciona de forma a desacelerar a particula3
    for(int i = 0; i < 20; i++){
        array_altura_tetamax[i] = (v0 * sin(tetamax) * array_tempo_tetamax[i]) - (1./2. * g * pow(array_tempo_tetamax[i],2.) );
    }

    //printando os resultados
    cout<< "O alcance maximo eh " << xmax << " metros" << endl;
    cout<< "O angulo no alcance maximo eh " << tetamax << " radianos" << endl;

    std:: vector <double> eixo_x;
    std:: vector <double> eixo_y;

    for(int i = 0; i < 20; i++){
        eixo_x.push_back(array_tempo_tetamax[i]);
        eixo_y.push_back(array_altura_tetamax[i]);
    }

    //plotando o grafico
    matplot::plot(eixo_x,eixo_y);
    matplot::title("Altura x tempo");
    matplot::xlabel("Tempo");
    matplot::ylabel("Altura");
    matplot::show();

    delete[] array_tempo_tetamax;
    delete[] array_altura_tetamax;

    return 0;
}