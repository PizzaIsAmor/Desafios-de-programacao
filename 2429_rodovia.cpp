#include <iostream>
#include <vector>
#include <list>
#define MAX_VETOR 10000
using namespace std;

int bfs(int vertice,  vector<int> *grafo, int quantidade) {
    list<int> expandir;
    expandir.push_back(vertice);

    vector<int> expandido(quantidade, 0);
    expandido[vertice] = 1;
    int nodos_visitados = 1;

    while(!expandir.empty()) {
        int v = expandir.front();
        expandir.pop_front();

        for(int i = 0; i < grafo[v].size(); i++) {
            int adjacente = grafo[v][i];

            if(expandido[adjacente] != 1) {
                nodos_visitados++;
                expandir.push_back(adjacente);
                expandido[adjacente] = 1;
            }
        }
    }

    return nodos_visitados;
}


int main() {
    int cidades;
    cin >> cidades;
    string mensagem = "S";
    vector<int> grafo[cidades];

    for (int i = 0; i < cidades; ++i) {
        int origem, destino;
        cin >> origem >> destino;
        grafo[origem-1].push_back(destino-1);
    }

    for (int i = 0; i < 2; i++) {
        int nodos_visitados = bfs(i, grafo, cidades);

        if (nodos_visitados != cidades) {
            mensagem = "N";
            break;
        }
    }

    cout << mensagem << endl;
    return 0;
}