#include <vector>
#include <matplot/matplot.h>
#include <boost/numeric/odeint.hpp>
#include <cmath>

using namespace boost::numeric::odeint;


class verifica_temp{

private:

    double k, kc, v0, cb0, cw0, ua, cpc, cpd, cpa, delta_H, cpb, cpw, ow, fb0, t0, ta;

public:

    verifica_temp(double v0, double cb0, double cw0, double ua, double cpa, double delta_H,
                  double cpb, double cpw, double ow, double fb0, double t0, double ta, double cpc, double cpd){

        this -> v0 = v0;
        this -> cb0 = cb0;
        this -> cw0 = cw0;
        this -> ua = ua;
        this -> cpa = cpa;
        this -> cpb = cpb;
        this -> cpc = cpc;
        this -> cpd = cpd;
        this -> cpw = cpw;
        this ->  delta_H = delta_H;
        this -> ow = ow;
        this -> fb0 = fb0;
        this -> t0 = t0;
        this -> ta = ta;
    }

    // definindo meu operador - arrumando as edos para serem calculadas pelo boost
    //vetor x constante para poder ser integrado (necessariamente valores fixos)

    void operator() (const std::vector<double>& x, std::vector<double>& dxdt, double t);
};
void verifica_temp :: operator()(const std::vector<double>& x, std::vector<double>& dxdt, const double t){

    k = (0.39175 * exp(5472.7 * ((1./273.) - (1./x[6])))) * 1e3; // (m³/ mol.s)
    kc = pow(10, (3885.44/x[6]));

    dxdt[0] = (-k * (x[0] *   x[1] - ((x[2] * x[3])/kc))) - (v0 *  x[0] / x[5]);
    dxdt[1] = (-k * (x[0] *   x[1] - ((x[2] * x[3])/kc)))  +  ((v0/x[5]) * (cb0 - x[1]));
    dxdt[2] =  (k * (x[0] *   x[1] - ((x[2] * x[3])/kc))) - (v0 * x[2] / x[5]);
    dxdt[3] = dxdt[2];
    dxdt[4] = cw0 * v0;
    dxdt[5] = v0;
    dxdt[6] = (((ua * (ta - x[6])) -((fb0 * cpb) * (1. + ow) * (x[6] - t0))) + (((-k * (x[0] *   x[1] - ((x[2] * x[3])/kc)))
                                                                                 * x[5] * delta_H))) / ((x[0] * x[5] * cpa) + (x[1] * x[5] * cpb) + (x[2] * x[5] * cpc) +
                                                                                                        (x[3] * x[5] * cpd) + ( x[4] * cpw));

}


struct armazenamento{

    //estruturando meus vetores que guardarao meus pontos desejados

    std::vector< std::vector<double> >& m_states;
    std::vector< double >& m_times;
    double write_dt;
    int counter;

    armazenamento(std::vector< std::vector<double> > &states,std::vector< double > &times,double dt):
            m_states( states ) , m_times( times ), write_dt(dt), counter(0) { }

    //definindo minha condicao para armazenamento

    void operator()(const std::vector<double> &x, double t ) {
        if (t >= counter * write_dt) {

            //colocando dentro dos vetores m_states e m_times os estados e tempos nos pontos desejados

            m_states.push_back(x);
            m_times.push_back(t);
            counter++;
        }
    }
};

int main(){

    //definindo constantes dadas no problema

    double v0 = 0.004;
    double cw0 = 55. * 1e-3, cb0 = 1. * 1e-3; //mol/m³
    double ua = 3000.; //J/s.K
    double ow = 55;
    double delta_H = -79076.; //J/mol
    double fb0 = 0.004, t0 = 300., ta = 290.; // m³/s , K, K
    double cpa = 170.7, cpb = 74.24; //J/mol.K
    double cpc = 74.24, cpd = 74.24, cpw = 74.24; //J/mol.K

    verifica_temp ver(v0, cb0, cw0, ua, cpa, delta_H, cpb, cpw, ow, fb0, t0, ta, cpc, cpd);

    //condicoes iniciais

    std::vector<double>x(7);

    x[0] = 5. * 1e-3; //mol/m³
    x[1] = 0.; //mol/m³
    x[2] =0; //mol/m³
    x[3] = 0; //mol/m³
    x[4]= 6.14 * 1e-3; //mol
    x[5] = 0.2; //m³
    x[6] = 300. ; //K

    //tempos analisados e passo de tempo adotado

    double tempo0 = 0.0; //s
    double tempof = 360.0; //s
    double dt = 0.01; //s

    std::vector<std::vector<double>> x_i;
    std::vector<double> times;

    //condicao de quanto em quanto tempo os pontos serao armazenados

    double dt_write = 2.0;

    armazenamento storage(x_i, times, dt_write);

    size_t steps = integrate(ver,x,tempo0,tempof,dt,storage);

    //preparando vectors para plotar o grafico

    int tamanho = int(times.size());
    std::vector<double> ca(tamanho);
    std::vector<double> cb(tamanho);
    std::vector<double> cc(tamanho);
    std::vector<double> cd(tamanho);
    std::vector<double> T(tamanho);

    //extraindo os pontos da matriz e os inserindo nos vectors


    for (int i = 0; i < tamanho; ++i) {

        ca[i] = x_i[i][0];
        cb[i] = x_i[i][1];
        cc[i] = x_i[i][2];
        cd[i] = x_i[i][3];
        T[i] = x_i[i][6];
    }

    //plotando os graficos

    matplot::hold(true);
    matplot::plot(times, ca)->color("b").line_width(2);
    matplot::plot(times, cb)->color("g").line_width(2);
    matplot::plot(times, cc)->color("p").line_width(2);
    matplot::plot(times, cd)->color("r").line_width(2);
    matplot::xlabel("tempo (s)");
    matplot::ylabel("concentracao (mol/m^3)");
    matplot::show();

    matplot::hold(true);
    matplot::plot(times, T)->color("p");
    matplot::xlabel("tempo (s)");
    matplot::ylabel("temperatura (K)");
    matplot::show();

    return 0;

    //A temperatura se manteve praticamente constante em torno de 290K
    //Ja para as concentracoes, A foi consumido enquando que B alimentado e consumido ao passo que C e D foram gerados
}