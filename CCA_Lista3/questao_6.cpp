#include <iostream>
#include <vector>
#include <cmath>
#include <matplot/matplot.h>

using namespace std;


class reacoes{
private:

    double k1, k2, k3;
    double dt;
    int n;
    double time = 0.;
    double CA0;
    double CB0;
    double CC0;
    double CAaux = 0.;
    double CBaux = 0.;
    double CCaux = 0.;
    double timeaux = 0.;
    std::vector<double> tempo_corte = {0, 20, 40, 60, 80, 100, 120, 200};
    std::vector<double> tempo_oficial;
    std::vector<double> CA;
    std::vector<double> CB;
    std::vector<double> CC;

public: //definindo meus objetos

    reacoes(double k1, double k2, double k3, double dt, double CA0, double CB0, double CC0, int n) {

        this->k1 = k1;
        this->k2 = k2;
        this->k3 = k3;
        this->dt = dt;
        this->CA0 = CA0;
        this->CB0 = CB0;
        this->n = n;
        this->CC0 = CC0;
        this-> tempo_corte.resize(tempo_corte.size());
        this-> tempo_oficial.resize(tempo_corte.size());
        this-> CA.resize(tempo_corte.size());
        this-> CB.resize(tempo_corte.size());
        this-> CC.resize(tempo_corte.size());
    }

    void resolve(double t0,double deltat) {

        int k = 0;
        time = t0;

        for (int i = 0; i < n; i++) { //resolvendo o metodo de euler

            timeaux = time + deltat;
            CAaux = CA0 + (dt * (((-k1) * CA0) + (k2 * CB0 * CC0)));
            CBaux = CB0 + (dt * ((k1 * CA0) - (k2 * CB0 * CC0) - (k3 * CB0 * CB0)));
            CCaux = CC0 + (dt * (k3 * CB0 * CB0));

            if (timeaux >= tempo_corte[k]){  //salvando os pontos desejados

                tempo_oficial[k] = time;
                CA[k] = CAaux;
                CB[k] = CBaux;
                CC[k] = CCaux;
                k++;
            }

            time = timeaux;
            CA0 = CAaux;
            CB0 = CBaux;
            CC0 = CCaux;
        }
    }


    //possibilitando o acesso aos vetores de fora da classe

    vector<double> get_time() {
        return tempo_oficial;
    }

    vector<double> get_CA() {
        return CA;
    }
    vector<double> get_CB() {
        return CB;
    }
    vector<double> get_CC() {
        return CC;
    }

};

int main() {

    double k1 = 0.08;
    double k2 = 2e4;
    double k3 = 6e7;
    double dt = 1e-5;
    double t0 = 0.0;
    double tf = 200.0;
    int n = ceil(((tf - t0)/ dt));  //arredondando n para cima
    double CA0 = 1.0;
    double CB0 = 0.0;
    double CC0 = 0.0;

    reacoes reacao(k1, k2, k3, dt, CA0, CB0, CC0, n);

    reacao.resolve(t0, dt);


    //fazendo com que a memoria nao seja dinamica


    std::vector<double> aux1 = reacao.get_time();
    std::vector<double> aux2 = reacao.get_CA();
    std::vector<double> aux3 = reacao.get_CB();
    std::vector<double> aux4= reacao.get_CC();

    //grafico de A

    matplot::plot(aux1, aux2);
    matplot::title("Concentracao de A pelo tempo");
    matplot::xlabel("Tempo");
    matplot::ylabel("Concentracao");
    matplot::show();

    //grafico de B

    matplot:: plot(aux1, aux3);
    matplot:: title("Concentracao de B pelo tempo");
    matplot:: xlabel("Tempo");
    matplot:: ylabel("Concentracao");
    matplot:: show();

    //grafico de C

    matplot::plot(aux1, aux4);
    matplot::title("Concentracao de C pelo tempo");
    matplot::xlabel("Tempo");
    matplot::ylabel("Concentracao");
    matplot::show();

    return 0;

}
