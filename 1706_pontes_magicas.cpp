#include <iostream>
#include <vector>

using namespace std;

bool dfs(int vertice, int* expandido, vector<int>* grafo, char*& valor, bool* achou, int max) {
    expandido[vertice] = 1;

    if (valor[vertice] == 'B') {
        valor[vertice] = 'A';
        *achou = true;
        return true;
    }

    for(int i = 0; i < grafo[vertice].size(); i++) {
        int adjacente = grafo[vertice][i];

        if(expandido[adjacente] == 0) {
            bool resultado = dfs(adjacente, expandido, grafo, valor, achou, max);
            if (*achou)
                return resultado;
        }
    }

    return false;
}

void acha_b(const char* lista, int ultimo, int* numero) {
    for(;*numero < ultimo; (*numero)++) {
        if(lista[*numero] == 'B')
            break;
    }
}

int main() {
    int torres, pontes, posicao, proximo;
    bool quebra_ciclo;

    while (cin >> torres >> pontes) {
        char *valor, palavra[torres];
        vector<int> grafo[torres];
        int expandido[torres];
        valor = palavra;

        for (int i = 0; i < torres; ++i) {
            cin >> palavra[i];
        }

        for (int i = 0; i < pontes; ++i) {
            int origem, destino;
            cin >> origem >> destino;
            grafo[origem - 1].push_back(destino - 1);
            grafo[destino - 1].push_back(origem - 1);
        }

        posicao = 0;
        acha_b(valor, torres, &posicao);
        proximo = posicao + 1;
        acha_b(valor, torres, &proximo);
        while (posicao != torres && proximo != torres) {
            fill(expandido, expandido + torres, 0);
            quebra_ciclo = false;
            valor[posicao] = 'A';
            if (!dfs(posicao, expandido, grafo, valor, &quebra_ciclo, torres)) {
                valor[posicao] = 'B';
                break;
            }

            acha_b(valor, torres, &posicao);
            proximo = posicao + 1;
            acha_b(valor, torres, &proximo);
        }

        posicao = 0;
        acha_b(valor, torres, &posicao);

        if (posicao < torres) {
            cout << "N" << endl;
        } else {
            cout << "Y" << endl;
        }
    }
    return 0;
}
