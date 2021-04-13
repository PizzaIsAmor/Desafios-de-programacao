#include <iostream>

#define INF 11

using namespace std;

int altura;
int largura;
int x;  // x = largura
int y;  // y = altura
int quadro[INF][INF];
int respostas[INF + 1][INF + 1];

void atualizaPosicao(int alt) {
    for (y = alt; y < altura; ++y)
        for (x = 0; x < largura; ++x)
            if (quadro[x][y] == -1)
                return;
}

int mondriaan() {
    if (x == largura && y == altura)
        return 1;

    int xLocal = x, yLocal = y, resp = 0;

    if (xLocal + 1 <= largura - 1 && quadro[xLocal + 1][yLocal] == -1) {
        quadro[xLocal][yLocal] = 1;
        quadro[xLocal + 1][yLocal] = 1;
        atualizaPosicao(yLocal);

        resp += mondriaan();

        quadro[xLocal][yLocal] = -1;
        quadro[xLocal + 1][yLocal] = -1;
    }
    if (yLocal + 1 <= altura - 1) {
        quadro[xLocal][yLocal] = 1;
        quadro[xLocal][yLocal + 1] = 1;
        atualizaPosicao(yLocal);

        resp += mondriaan();

        quadro[xLocal][yLocal] = -1;
        quadro[xLocal][yLocal + 1] = -1;
    }

    x = xLocal;
    y = yLocal;

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
        // prepara posição
        x = 0;
        y = 0;
        // Calcula
        cout << mondriaan() << endl;

        cin >> altura >> largura;
    }

    return 0;
}