#include <iostream>
#include <vector>

using namespace std;

int ordem_atual;

void constroi(int *cjt, int* n, int max) {
    for(int i = 0; i < max; i++) {
        cjt[i] = i;
        n[i] = 1;
    }
}

int busca(int i, int* cjt) {
    if(i != cjt[i])
        cjt[i] = busca(cjt[i], cjt);
    return cjt[i];
}

void une(int i, int j, int* n, int* cjt) {
    int si = busca(i, cjt), sj = busca(j, cjt);
    if(si != sj) {
        if(n[si] >= n[sj]) {
            n[si] += n[sj];
            cjt[sj] = si;
        } else {
            n[sj] += n[si];
            cjt[si] = sj;
        }
    }
}

void dfs_pontes(int vertice, vector<int>* grafo, int* expandido, int* ordem,
                int* alcanca, vector<int>* pontes, int pai = -1) {
    expandido[vertice] = 1;
    ordem_atual ++;
    ordem[vertice] = ordem_atual;
    alcanca[vertice] = ordem_atual;

    for(int i = 0; i < grafo[vertice].size(); i++) {
        int adjacente = grafo[vertice][i];

        if(expandido[adjacente] == 1 && adjacente != pai) {
            alcanca[vertice] = min(alcanca[vertice], ordem[adjacente]);
        } else if (expandido[adjacente] == 0){
            dfs_pontes(adjacente, grafo, expandido, ordem, alcanca, pontes, vertice);
            alcanca[vertice] = min(alcanca[vertice], alcanca[adjacente]);
            if(alcanca[adjacente] > ordem[vertice]) {
                pontes[vertice].push_back(adjacente);
            }
        }
    }
}

void dfs_conjuntos(int vertice, vector<int>* grafo, int* expandido, int* n, int* cjt) {
    expandido[vertice] = 1;

    for (int i = 0; i < grafo[vertice].size(); i++) {
        int adjacente = grafo[vertice][i];
        if (expandido[adjacente] == 0) {
            une(vertice, adjacente, n, cjt);
            dfs_conjuntos(adjacente, grafo, expandido, n, cjt);
        }
    }
}

int main() {
    int salas, corredores, consultas, inicio, fim;
    string resposta;
    cin >> salas >> corredores >> consultas;

    while (salas != 0 && corredores != 0 && consultas != 0) {
        vector<int> grafo[salas];
        vector<int> pontes[salas];
        int expandido[salas];
        int ordem[salas];
        int alcanca[salas];
        int conjunto[salas];
        int quantidade_de_elementos[salas];

        fill(expandido, expandido + salas, 0);
        fill(alcanca, alcanca + salas, 0);
        fill(ordem, ordem + salas, 0);
        constroi(conjunto, quantidade_de_elementos, salas);

        for (int i = 0; i < corredores; ++i) {
            cin >> inicio >> fim;
            grafo[inicio - 1].push_back(fim - 1);
            grafo[fim - 1].push_back(inicio - 1);
        }

        ordem_atual = 0;
        dfs_pontes(0, grafo, expandido, ordem, alcanca, pontes);

        for (int j = 0; j < salas; ++j)
            for (int k = 0; k < pontes[j].size(); ++k) {
                fill(expandido, expandido + salas, 0);
                dfs_conjuntos(pontes[j][k], pontes, expandido, quantidade_de_elementos, conjunto);

                fill(expandido, expandido + salas, 0);
                dfs_conjuntos(j, pontes, expandido, quantidade_de_elementos, conjunto);
            }

        for (int i = 0; i < consultas; ++i) {
            cin >> inicio >> fim;

            if (busca(inicio-1, conjunto) == busca(fim-1, conjunto) )
                resposta = "Y";
            else
                resposta = "N";

            cout << resposta << endl;
        }

        cout << "-" << endl;

        cin >> salas >> corredores >> consultas;
    }

    return 0;
}