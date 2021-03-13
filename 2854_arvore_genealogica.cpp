#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int* bfs(int vertice,  vector<int> *grafo, int* expandido) {
    list<int> expandir;
    expandir.push_back(vertice);

    expandido[vertice] = 1;
    while(!expandir.empty()) {
        int v = expandir.front();
        expandir.pop_front();

        for(int i = 0; i < grafo[v].size(); i++) {
            int adjacente = grafo[v][i];

            if(expandido[adjacente] != 1) {
                expandir.push_back(adjacente);
                expandido[adjacente] = 1;
            }
        }
    }

    return expandido;
}

int main() {
    int nodos, arestas, i, j, k, areas, ultima_posicao = 0;
    int* visitados;
    string parente, parente2, relacao;
    cin >> nodos >> arestas;

    vector<int> grafo[nodos];
    int expandido[nodos];
    map<string, int> posicao_nodos;
    fill(expandido, expandido+nodos, 0);

    for (i = 0; i < arestas; ++i) {
        cin >> parente >> relacao >> parente2;

        if (posicao_nodos.find(parente) == posicao_nodos.end()) {
            posicao_nodos.insert(pair<string, int>(parente, ultima_posicao));
            ultima_posicao++;
        }
        if (posicao_nodos.find(parente2) == posicao_nodos.end()) {
            posicao_nodos.insert(pair<string, int>(parente2, ultima_posicao));
            ultima_posicao++;
        }

        j = posicao_nodos.at(parente);
        k = posicao_nodos.at(parente2);
        grafo[j].push_back(k);
        grafo[k].push_back(j);
    }

    areas = 0;
    visitados = expandido;
    for (i = 0; i < nodos; ++i)
            if (visitados[i] == 0) {
                areas++;
                visitados = bfs(i, grafo, visitados);
            }

    cout << areas << endl;
    return 0;
}
