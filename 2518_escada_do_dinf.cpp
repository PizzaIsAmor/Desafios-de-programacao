#include <iostream>
#include <iomanip>
#include <valarray>

using namespace std;

int main() {
    double degraus, largura, comprimento, altura;

    while (cin >> degraus >> altura >> comprimento >> largura) {
        double hipo = 0;

        hipo = sqrt(pow(comprimento, 2) + pow(altura, 2));

        cout << fixed << setprecision(4) << (hipo * largura * degraus)/10000 << endl;
    }

    return 0;
}