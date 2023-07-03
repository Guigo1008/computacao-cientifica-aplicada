#include <iostream>
#include <cmath>

using namespace std;
int main(){
    double v;
    
    //comecando o loop
    
    for(int t = -5; t < 51; t++){
    
    //realizando cada condicional
    
    if(t <= 8 && t >= 0){
      v = 10. * pow(t,2) - 5. * t;
    } else if(t >= 8 && t <= 16) {
        v = 624. - 5 * t;
    } else if(t >=16 && t <=26){
        v= 36. * t + 12. * pow((t-16.),2);
    }
    else if(t >=26){
        v = 2136. * exp(-0.1 * (t - 26.));
    }
    else {
        v = 0;}
        
    //printando os resultados
    cout<< "Quando t = " << t << ", v = " << v << endl;}

    return 0;
}
