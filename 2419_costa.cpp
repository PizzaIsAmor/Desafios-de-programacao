#include <iostream>

using namespace std;

int main() {
    int linhas, colunas, i, j, costa;
    char letra;
    cin >> linhas >> colunas;
    char tabela[linhas][colunas];

    for (i = 0; i < linhas; ++i)
        for (j = 0; j < colunas; ++ j) {
            cin >> letra;
            tabela[i][j] = letra;
        }

    costa = 0;
    for (i = 0; i < linhas; ++i)
        for (j = 0; j < colunas; ++ j) {
            if (tabela[i][j] == '.')
                continue;

            if (i == 0 || i == linhas - 1 || j == 0 || j == colunas - 1) {
                costa++;
                continue;
            }

            if (i > 0 && tabela[i - 1][j] == '.') {
                costa++;
                continue;
            }

            if (i < linhas-1 && tabela[i + 1][j] == '.') {
                costa++;
                continue;
            }

            if (j > 0 && tabela[i][j - 1] == '.') {
                costa++;
                continue;
            }

            if (j < colunas - 1 && tabela[i][j + 1] == '.') {
                costa++;
                continue;
            }
        }

    cout << costa << endl;
    return 0;
}