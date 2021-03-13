#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <limits>
#define MAX_X_Y 10000
using namespace std;

float prim(int tamanho, vector< pair<float, int> >* grafo, int* antecessor) {
    priority_queue< pair<float, int>, vector < pair<float, int> > , greater< pair<float, int> > > heap;
    int adicionado[tamanho];
    float custos[tamanho];

    fill(adicionado, adicionado + tamanho, 0);
    fill(custos, custos + tamanho, numeric_limits<float>::max());
    heap.push(make_pair(0, 0));

    while (!heap.empty()) {
        int vertice = heap.top().second;// seleciona o vértice do topo

        heap.pop();
        adicionado[vertice] = 1;
        for(int i = 0; i < grafo[vertice].size(); i++) {
            int adjacente = grafo[vertice][i].second;

            if (adicionado[adjacente] == 0 && custos[adjacente] > grafo[vertice][i].first) {
                custos[adjacente] = grafo[vertice][i].first;
                heap.push(make_pair(custos[adjacente], adjacente));
                antecessor[adjacente] = vertice;
            }
        }
    }

    float menor_em_metros = 0;
    for (int i = 1; i < tamanho; ++i) {
        menor_em_metros += custos[i];
    }
    return menor_em_metros;
}

int main() {
    int quantidade, nodos, i, j;
    float distancia, metros;
    int x[MAX_X_Y], y[MAX_X_Y];
    cin >> quantidade;
    cout << fixed;
    cout << setprecision(2);

    for (int k = 0; k < quantidade; ++k) {
        cin >> nodos;
        vector<pair<float, int> > grafo[nodos];
        int antecessor[nodos];

        for (i = 0; i < nodos; ++i)
            antecessor[i] = 0;

        for (i = 0; i < nodos; ++i) {
            cin >> x[i] >> y[i];
        }

        for (j = 0; j < nodos; ++j)
            for (i = 0; i < nodos; ++i)
                if (i != j) {
                    distancia = sqrt( pow((x[i]-x[j]), 2) + pow((y[i]-y[j]), 2) );
                    grafo[j].emplace_back(distancia, i);
                }

        metros = prim(nodos, grafo, antecessor);

        cout << metros/100 << endl;
    }

    return 0;
}