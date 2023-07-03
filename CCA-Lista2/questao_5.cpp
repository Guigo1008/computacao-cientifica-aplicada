#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

struct Dados {

    double angulo;
    double distancia;
    double altura;

};

int main(){
    double y0 = 0, g = 9.81, v0 = 28, y;
    vector<Dados> tabela;

    //intervalos de teta
    for(double teta = 15.; teta <= 75.; teta += 15.){

        //intervalos de x
        for(double x = 0.; x <= 80.; x += 20.){

            double tetarad = (M_PI / 180.) * teta;

            y = y0 + (x * tan(tetarad)) - ((g * pow(x,2.)  / (2. * pow(v0,2)) * (pow(cos(tetarad),2))));

            //nao deixando a altura ser menor do que zero
            if(y<0){
                y = 0;
            }

            tabela.push_back({teta, x,y});
        }}

    //printando a tabela

    cout << "Angulo\tDistancia\tAltura\n";
    cout << "--------------------------------\n";

    for(const auto& dados : tabela){
        cout << std::fixed << std::setprecision(2) << dados.angulo << "\t"<< dados.distancia << "\t\t" << dados.altura << "\n";
    }

return 0;
}
