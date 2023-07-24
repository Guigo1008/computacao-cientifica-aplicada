#include <Eigen/Dense>
#include <vector>
#include <iostream>

using namespace std;
using namespace Eigen;

int main() {
    double a = 0.72, b = 0.0;
    double G = 66.7, L = 40.8;
    vector<int> stages = {2, 4, 6, 10, 20, 40};

    vector<pair<double, double>> cases = {{0.0, 0.2}, {0.0, 0.3}};

    for (auto& c : cases) {
        double x0 = c.first, yn1 = c.second;

        for (int n : stages) {
            // (x,y) - x eh respectivo a equacao, y eh respectivo ao xi.
            // Pela relacao eh possivel transformar todos yi em xi.
            MatrixXd A = MatrixXd::Zero(n, n);
            VectorXd B = VectorXd::Zero(n);

            // Para primeira eq. (B=0)
            A(0,0) = 0.;
            A(0,1) = -L-G*a;
            A(0,2) = G*a;

            // Para ultima eq. (B!=0)
            A(n-1, n-2) = -L;
            A(n-1, n-1) = L+G;
            B(n-1) = yn1;

            for (int i = 1; i < n-1; ++i) {
                A(i, i-1) = L;
                A(i, i+1) = G*a;
                A(i, i)   = -L-G*a;
            }

            VectorXd solution = A.colPivHouseholderQr().solve(B);

            cout << "A solucao para " << n << " estagios: " << solution.transpose() << endl;
        }
    }

    return 0;
}