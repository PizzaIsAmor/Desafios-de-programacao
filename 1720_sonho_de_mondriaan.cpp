#include <iostream>
#include <vector>

#define INF 11
#define MAX_BLOCOS 61

using namespace std;

int altura;
int largura;
int quadro[INF][INF];
int respostas[MAX_BLOCOS][INF + 1][INF + 1];

void proximaPosicao(int *x, int *y) {
    while ((*y) < altura) {
        for ((*x) = 0; (*x) < largura; ++(*x))
            if (quadro[(*x)][(*y)] == -1) {
                return;
            }

        (*y) += 1;
    }
}

int mondriaan(int x, int y, int bloco) {
    if (respostas[bloco][x][y] != -1)
        return respostas[bloco][x][y];

    respostas[bloco][x][y] = 0;

    if (x == largura && y == altura)
        respostas[bloco][x][y]++;

    // adiciona horizontal
    if (x + 1 <= largura - 1 && quadro[x + 1][y] == -1) {
        // marca quadro
        quadro[x][y] = 1;
        quadro[x + 1][y] = 1;

        // acha proxima posicao
        int xLocal, yLocal = y;
        proximaPosicao(&xLocal, &yLocal);

        respostas[bloco][x][y] += mondriaan(xLocal, yLocal, bloco + 1);

        // reseta quadro
        quadro[x][y] = -1;
        quadro[x + 1][y] = -1;
    }

    // adiciona vertical
    if (y + 1 <= altura - 1) {
        //marca quadro
        quadro[x][y] = 1;
        quadro[x][y + 1] = 1;

        // acha proxima posicao
        int xLocal, yLocal = y;
        proximaPosicao(&xLocal, &yLocal);

        respostas[bloco][x][y] += mondriaan(xLocal, yLocal, bloco + 1);

        //reseta quadro
        quadro[x][y] = -1;
        quadro[x][y + 1] = -1;
    }

    return respostas[bloco][x][y];
}

int main() {
    // Prepara tabela de resolução
    for (auto & i : quadro)
        fill(i, i + INF, -1);

    cin >> altura >> largura;
    while (altura != 0 && largura != 0) {
        // prepara tabela dos calculos salvos
        for (auto & resposta : respostas)
            for (auto & i : resposta)
                fill(i, i + INF + 1, -1);

        cout << mondriaan(0, 0, 0) << endl;

        cin >> altura >> largura;
    }

    return 0;
}

//1 2
//1 3
//1 4
//2 2
//2 3
//2 4
//2 11
//4 11
//0 0