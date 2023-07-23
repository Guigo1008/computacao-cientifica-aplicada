#include <iostream>
#include <cmath>
#include <vector>
#include "matplot/matplot.h"

using namespace std;
using namespace matplot;

class minim_quadrados{

    int n_;
    vector<double> x_;
    vector<double> y_;

public:

    void set_dados(const vector<double>& x, const vector<double>& y) {
        if (x.size() == y.size()) {
            n_ = int(x.size());
            x_ = x;
            y_ = y;

            cout << "Arrays armazenados com sucesso." << endl;

        } else {

            cout << "Os arrays fornecidos têm tamanhos diferentes." << endl;

        }
    }

    double media_x();
    double media_y();
    double sumx();
    double sumy();
    double sumxy();
    double sumx_2();
    double sumy_2();

    // coeficientes ajuste linear

    double m();
    double b();

    // gráfico

    void grafico();

    // coeficiente de correlação

    double r();


};

//somatorios


double minim_quadrados::sumx(){

    double sumx =0.;
    for(int i=0; i<n_; i++){
        sumx += x_[i];
    }
    return sumx;
}

double minim_quadrados::sumx_2() {
    double sumx2 =0.;
    for(int i=0; i<n_; i++){
        sumx2 += x_[i] *  x_[i];
    }
    return sumx2;
}

double minim_quadrados::sumy() {
    double sumy =0.;

    for(int i=0; i<n_; i++){
        sumy += y_[i];
    }
    return sumy;
}

double minim_quadrados::sumy_2() {
    double sumy2 =0.;

    for(int i=0; i<n_; i++){
        sumy2 += y_[i]*y_[i];
    }
    return sumy2;
}

double minim_quadrados::sumxy() {
    double sumxy = 0.;
    for(int i=0; i<n_; i++){
        sumxy += x_[i]*y_[i];
    }
    return sumxy;
}

double minim_quadrados::media_x() {
    return sumx()/n_;
}

double minim_quadrados::media_y() {
    return sumy()/n_;
}

double minim_quadrados::m() {
    return (sumxy() - sumy()*media_x())/(sumx_2() - sumx()*media_x());
}

double minim_quadrados::b(){
    return media_y() - m()*media_x();
}

void minim_quadrados::grafico(){

    vector<double> x = linspace(x_[0], x_[n_]);
    vector<double> y = transform(x, [this](double x){return m()*x+b();});

    plot(x_,y_);
    plot(x, y);
    title("Ajuste dos dados: método dos mínimos quadrados");
    show();
}

double minim_quadrados::r() {
    return (n_*sumxy()-sumx()*sumy())/ pow((n_*sumx_2()-pow(sumx(),2.))*(n_*sumy_2()- pow(sumy(),2.)), 0.5);
}


int main(){

    string documento_usuario = "info_ex4.txt";
    int n = 20; // número de itens nos arrays

    vector<double> x;
    vector<double> y;

    string dados;

    ifstream my_data(documento_usuario, ios::in);
    if(my_data.is_open()) {

        my_data.ignore(80,'{');
        for (int i=0; i<(n-1); i++){

            getline(my_data, dados, ',');
            x.push_back(stod(dados));
        }

        getline(my_data, dados, '}');
        x.push_back(stod(dados));

        my_data.ignore(80,'{');

        for (int i=0; i<(n-1); i++){

            getline(my_data, dados, ',');
            y.push_back(stod(dados));
        }

        getline(my_data, dados, '}');
        y.push_back(stod(dados));
    }

    minim_quadrados xy;
    xy.set_dados(x,y);

    cout<<"Os coeficientes do ajuste por mínimos quadrados são:\nm = " << xy.m()<<"\nb = "<< xy.b()<<endl;
    cout<<"O coeficiente de correlação foi de "<<xy.r()<<endl;

    if(xy.r()<0.2 && xy.r()>-0.2){

        cout<<"AVISO: COEFICIENTE DE CORRELAÇÃO MUITO BAIXO."<<endl;
    }

    xy.grafico();

    return 0;
}
