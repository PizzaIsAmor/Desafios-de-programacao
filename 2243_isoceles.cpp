#include <iostream>

#define INF 1000000

using namespace std;

int n;
int tamMax = 0;
int numeros[INF];

void isoceles(int index) {
    for (int j = 0; j < n; ++j) {
        while (tamMax < numeros[j]) {
            int level = tamMax + 1;
            int altura = tamMax;

            if ((j - tamMax) < 0 || n < (j + tamMax)) // Acesso invalido, sai do laco
                break;

            bool isVal = true;
            for (int i = 1; i < level; ++i) {
                if (numeros[j - i] < altura || numeros[j + i] < altura) {
                    isVal = false;
                    break;
                }

                altura--;
            }

            if (!isVal)
                break;

            tamMax = level;
        }
    }
}

int main() {
    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> numeros[i];

    isoceles(0);
    cout << tamMax << endl;

    return 0;
}