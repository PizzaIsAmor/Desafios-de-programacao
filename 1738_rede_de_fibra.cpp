#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#define MAX_NOS 200

using namespace std;

int grafo [MAX_NOS][MAX_NOS][26];

void floyd_warshall(int n) {
    int u, v, w, x;
    bool adicionou;

    for (u = 0; u < n; ++u)
        for (x = 0; x < 26; ++x)
            grafo[u][u][x] = 1;

    do {
        adicionou = false;
        for (w = 0; w < n; ++w)
            for (u = 0; u < n; ++u)
                for (v = 0; v < n; ++v)
                    for (x = 0; x < 26; ++x)
                        if(grafo[u][w][x] == 1 && grafo[w][v][x] == 1 && grafo[u][v][x] == 0) {
                            grafo[u][v][x] = 1;
                            adicionou = true;
                        }
    } while(adicionou);
}

int main() {
    int nodos, x, y, i, j, letra;
    string texto, resultado;

    cin >> nodos;
    while (nodos != 0) {
        for (i = 0; i < nodos; ++i)
            for (j = 0; j < nodos; ++j)
                fill(grafo[i][j], grafo[i][j] + 26, 0);

        cin >> x >> y;
        while (x != 0 && y != 0) {
            cin >> texto;

            for (i = 0; i < texto.length(); ++i) {
                letra = (int) (texto[i] - 'a');
                grafo[x - 1][y - 1][letra] = 1;
            }

            cin >> x >> y;
        }

        floyd_warshall(nodos);

        cin >> x >> y;
        while (x != 0 && y != 0) {
            resultado = "";
            for (i = 0; i < 26; ++i) {
                if (grafo[x - 1][y - 1][i] == 1) {
                    resultado.push_back((char) (i + 'a'));
                }
            }

            if (resultado.empty())
                resultado = "-";

            cout << resultado << endl;

            cin >> x >> y;
        }

        cout << endl;
        cin >> nodos;
    }

    return 0;
}