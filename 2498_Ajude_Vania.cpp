#include <iostream>

#define MAXN 1000
#define MAXP 1000

using namespace std;

int valores[MAXN];
int pesos[MAXN];
int n;
int tabela[2][MAXP + 1];

int mochila(int peso_mochila) {
    int atual = 0;

    fill(tabela[0], tabela[0] + MAXP + 1, 0);
    fill(tabela[1], tabela[1] + MAXP + 1, 0);

    for (int item = n - 1; item >= 0; item--) {
        atual = 1 - atual;
        for (int peso = 0; peso <= peso_mochila; peso++) {
            int solucao = tabela[1 - atual][peso];
            if (pesos[item] <= peso && solucao < valores[item] + tabela[1 - atual][peso - pesos[item]]) {
                solucao = valores[item] + tabela[1 - atual][peso - pesos[item]];
            }

            tabela[atual][peso] = solucao;
        }
    }

    return tabela[atual][peso_mochila];
}

int main() {
    int capacidade, i, resposta, caso = 0;

    do {
        cin >> n >> capacidade;

        for (i = 0; i < n; ++i) {
            cin >> pesos[i] >> valores[i];
        }

        caso++;
        resposta = mochila(capacidade);
        if (n != 0 && capacidade != 0)
            cout << "Caso " << caso << ": " << resposta << endl;

    } while (n != 0 && capacidade != 0);

    return 0;
}