#include <iostream>
#include <cmath>

using namespace std;

double iterador(double xit, float tolerancia) {
    while (true) {
        double K = 8.;
        double xit1 = xit - (pow(xit, 3.) - K) / (3. * pow(xit, 2.));
        if (abs(xit1 - xit) < tolerancia) {
            return xit1;
        }
        xit = xit1;
    }
}
int main(int arg, char **argv) {
    cout << iterador(100000000, 1e-6) << "\n";

    return 0;
}