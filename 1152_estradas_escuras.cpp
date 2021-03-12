#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

int prim(int tamanho, vector< pair<int, int> >* grafo, int* antecessor) {
    priority_queue< pair<int, int>, vector < pair<int, int> > , greater< pair<int, int> > > heap;
    int adicionado[tamanho];
    int custos[tamanho];

    fill(adicionado, adicionado + tamanho, 0);

    memset(custos, INF, sizeof(custos));
    heap.push(make_pair(0, 0));

    while (!heap.empty()) {
        int vertice = heap.top().second;// seleciona o vértice do topo
        heap.pop();
        adicionado[vertice] = 1;
        for(int i = 0; i < grafo[vertice].size(); i++) {
            int adjacente = grafo[vertice][i].second;
            if (adicionado[adjacente] == 0 && grafo[vertice][i].first < custos[adjacente]) {
                custos[adjacente] = grafo[vertice][i].first;
                heap.push(make_pair(custos[adjacente], adjacente));
                antecessor[adjacente] = vertice;
            }
        }
    }

    int menor_em_metros = 0;
    for (int i = 1; i < tamanho; i++)
        menor_em_metros += custos[i];

    return menor_em_metros;
}

int main() {
    int nodos, arestas, i, j, x, y, distancia, metros;
    cin >> nodos >> arestas;

    while (nodos != 0 && arestas != 0) {
        vector< pair<int, int> > grafo[nodos];
        int antecessor[nodos];

        for (i = 0; i < nodos; ++i)
            antecessor[i] = 0;

        metros = 0;
        for (i = 0; i < arestas; ++i) {
            cin >> x >> y >> distancia;
            grafo[x].emplace_back(distancia, y);
            grafo[y].emplace_back(distancia, x);
            metros += distancia;
        }

        metros -= prim(nodos, grafo, antecessor);

        cout << metros << endl;

        cin >> nodos >> arestas;
    }

    return 0;
}