#include <iostream>
#include <valarray>

#define NUMERAL_POSITION 17
#define NUMERO_DE_CORTE 131071

using namespace std;

void arrumaPow(int *n, int *rest) {
    int original = *n;
    vector<int> fatores;
    for (int i = 2; i * i <= *n; i++)
        if (*n % i == 0)
            while (*n % i == 0) {
                fatores.push_back(i);
                *n /= i;
            }

    if (*n > 1)
        fatores.push_back(*n);

//    cout << "tamanho: " << fatores.size();
//    for (int i = fatores.size() - 1; i >= 0; --i) {
//        cout << " val " << i << ": " << fatores[i] << " |";
//    }
//    cout << endl;

    *n = 1;
    while (!fatores.empty()) {
        if (*n < NUMERAL_POSITION)
            *n *= fatores.back();
        else
            *rest *= fatores.back();
        fatores.pop_back();
    }

//    cout << "original: " << original << " n: " << *n << " rest: " << *rest << endl;
}

int main() {
    string num;
    int posicao, potencia = 0;
    long long val = 0;

    while (cin >> num) {
        posicao = 0;
        while (posicao < num.length() && num[posicao] != '#') {
            if (num[posicao] == '1') {
                if (posicao > NUMERAL_POSITION) {
                    int numPow = potencia;
                    int restPow = 1;
                    arrumaPow(&numPow, &restPow);

                    val += (long long) pow((int) pow(2, numPow) % NUMERO_DE_CORTE, restPow);
                } else
                    val += (long long) pow(2, potencia) % NUMERO_DE_CORTE;
            }

            potencia++;
            posicao++;
        }

        val = val % NUMERO_DE_CORTE;
//        cout << "Val: " << val << " posicao: " << posicao << " potencia: " << potencia << " chacracter: " << num[posicao] << endl;

        if (num[posicao] == '#' && val == 0) {
            cout << "YES" << endl;
            val = 0;
            potencia = 0;
        } else if (num[posicao] == '#') {
            cout << "NO" << endl;
            val = 0;
            potencia = 0;
        }
    }

    return 0;
}