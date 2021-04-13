#include <iostream>

#define INF 11

using namespace std;

int altura;
int largura;
int quadro[INF][INF];
int respostas[INF + 1][INF + 1];

void proximaPosicao(int *x, int *y) {
    while ((*y) < altura) {
        for ((*x) = 0; (*x) < largura; ++(*x))
            if (quadro[(*x)][(*y)] == -1) {
                return;
            }

        ++(*y);
    }
}

int mondriaan(int x, int y) {
    if (respostas[x][y] != -1)
        return respostas[x][y];

    if (x == largura && y == altura)
        return 1;

    int resp = 0;

    // adiciona horizontal
    if (x + 1 <= largura - 1 && quadro[x + 1][y] == -1) {
        // marca quadro
        quadro[x][y] = 1;
        quadro[x + 1][y] = 1;

        // acha proxima posicao
        int xLocal, yLocal = y;
        proximaPosicao(&xLocal, &yLocal);

        resp += mondriaan(xLocal, yLocal);

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

        resp += mondriaan(xLocal, yLocal);

        //reseta quadro
        quadro[x][y] = -1;
        quadro[x][y + 1] = -1;
    }

    return resp;
}

int main() {
    // Prepara tabela de resolução
    for (int i = 0; i < INF; ++i)
        fill(quadro[i], quadro[i] + INF, -1);

    // prepara tabela dos calculos salvos
    for (int i = 0; i < INF + 1; ++i)
        fill(respostas[i], respostas[i] + INF + 1, -1);

    cin >> altura >> largura;
    while (altura != 0 && largura != 0) {
        cout << mondriaan(0, 0) << endl;

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