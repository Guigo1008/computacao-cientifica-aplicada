#include <iostream>
#include <cmath>
using namespace std;

int main(){
   int n;

   //verificando quem sera N

    cout<< "Insira o número de dados: ";
    cin>> n;

    //criando o array

    auto* array = new double[n];

    for(int i = 0; i < n; i++){
       cout << "Insira os valores adquiridos: ";
       cin  >> array[i];
        if(array[i] < 0){
            cerr << "Voce nao pode entrar com um valor negativo"<< endl;
            abort();
        }
    }

    //executando apenas se nao tiver negativo
    double y = 0., z = 0.;

    //primeiro somatorio
    for(int i = 0; i < n; i ++){
        y += array[i];
    }

    double media = y / n;
    cout<< "A media dos valores eh " << media << endl;

    //segundo somatorio usado no desvio padrao
    for(int i = 0; i < n; i ++){
        z += (pow(array[i],2.));
    }
    double desvio = sqrt(((n * z) - pow(y,2.)) / (n * (n - 1.)));

    cout<< "O desvio padrao dos valores eh " << desvio << endl;

    delete[] array;
    return 0;
}