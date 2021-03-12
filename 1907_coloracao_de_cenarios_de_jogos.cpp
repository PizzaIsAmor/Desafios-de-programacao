#include <iostream>
#include <bits/stdc++.h>
#define MAX 1024

using namespace std;

char tabela[MAX][MAX];

void bfs(int linha, int coluna, int max_lin, int max_col) {
    list< pair<int,int> > expandir;
    expandir.push_back( make_pair(linha, coluna) );

    tabela[linha][coluna] = '*';
    while(!expandir.empty()) {
        pair<int, int> v = expandir.front();
        expandir.pop_front();

        if (v.first > 0 && tabela[v.first - 1][v.second] == '.') {
            tabela[v.first - 1][v.second] = '*';
            expandir.push_back(make_pair(v.first - 1, v.second));
        }

        if (v.second > 0 && tabela[v.first][v.second - 1] == '.') {
            tabela[v.first][v.second - 1] = '*';
            expandir.push_back(make_pair(v.first, v.second - 1));
        }

        if (v.first < max_lin - 1  && tabela[v.first + 1][v.second] == '.') {
            tabela[v.first + 1][v.second] = '*';
            expandir.push_back(make_pair(v.first + 1, v.second));
        }

        if (v.second < max_col - 1 && tabela[v.first][v.second + 1] == '.') {
            tabela[v.first][v.second + 1] = '*';
            expandir.push_back(make_pair(v.first, v.second + 1));
        }
    }
}

int main() {
    int linhas, colunas, i, j, areas;
    char letra;
    cin >> linhas >> colunas;

    for (i = 0; i < linhas; ++i)
        for (j = 0; j < colunas; ++ j) {
            cin >> letra;
            tabela[i][j] = letra;
        }

    areas = 0;
    for (i = 0; i < linhas; ++i)
        for (j = 0; j < colunas; ++ j)
            if (tabela[i][j] == '.') {
                areas++;
                bfs(i, j, linhas, colunas);
            }


    cout << areas << endl;
    return 0;
}