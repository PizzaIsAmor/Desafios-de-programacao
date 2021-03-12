#include <iostream>
#include <vector>
#include <functional>
#include <queue>

using namespace std;

bool dominou_alguem;

struct NODO {
    int posicao{};
    int soldados{};
    int refens{};
    vector<int> observa;
};

struct OrdenaMenorExercito {
    bool operator()(NODO const& n1, NODO const& n2)
    {
        return n1.soldados < n2.soldados;
    }
};

void imprime_dados(int postos, int visao, int soldados, struct NODO *grupo, vector<int> *grafo_invertido) {
    cout << "Quantidade" << endl << "Nodos: " << postos << " arestas: " << visao << " soldadosIniciais: " << soldados << endl;

    cout << endl << "Nodos" << endl;
    for (int i = 0; i < postos; i++) {
        cout << "[Id: "<< grupo[i].posicao + 1 << ", soldados: "<< grupo[i].soldados << ", refens: "
        << grupo[i].refens << "]" << endl;
    }

    cout << endl << "ARESTAS Invertidas" << endl;
    for (int j = 0; j < postos; ++j) {
        for (int k = 0; k < grafo_invertido[j].size(); ++k) {
            cout << "NodoSaida: " << j+1 << " NodoChegada: " << (grafo_invertido[j][k] + 1) << endl;
        }
    }
}


void dfs_invertido(const NODO& nodo, vector<int>* grafo_invertido, int* expandido,
                   int* soldados, NODO* grupo, vector<int>* grafo, int postos) {
    int vertice = nodo.posicao;
    expandido[vertice] = 1;

    if (grafo_invertido[vertice].empty() && (*soldados >= nodo.soldados)) {
        *soldados += nodo.refens;
        dominou_alguem = true;


        //apaga link para nodos já concluidos
        for (int i = 0; i < postos; ++i) {
            for (int j = 0; j < grafo[i].size(); ++j) {
                if (grafo[i][j] == vertice) {
                    vector<int> copia;
                    for (int & k : grafo[i]) {
                        if (k != vertice) {
                          copia.push_back(k);
                        }
                    }
                    grafo[i] = copia;
                    break;
                }
            }
        }
    }

    for(int i = 0; i < grafo_invertido[vertice].size(); i++) {
        int adjacente = grafo_invertido[vertice][i];
        if(expandido[adjacente] == 0)
            //testa com nodos que estao vigiando
            dfs_invertido(grupo[adjacente], grafo_invertido, expandido, soldados, grupo, grafo, postos);
    }
}

int main() {
    int postos, visao, soldados, origem, destino;
    cin >> postos >> visao >> soldados;
    struct NODO um_nodo;

    while (postos != 0 && visao != 0 && soldados != 0) {
        vector<int> grafo[postos];
        vector<int> grafo_invertido[postos];
        int expandido[postos];
        struct NODO grupo[postos];
        priority_queue<NODO, vector<NODO>, OrdenaMenorExercito> fila;
        priority_queue<NODO, vector<NODO>, OrdenaMenorExercito> fila_aux;

        fill(expandido, expandido + postos, 0);

        for (int i = 0; i < postos; ++i) {
            cin >> grupo[i].soldados;
            grupo[i].posicao = i;
        }

        for (int i = 0; i < postos; ++i) {
            cin >> grupo[i].refens;
        }

        for (int i = 0; i < visao; ++i) {
            cin >> origem >> destino;
            grafo[origem - 1].push_back(destino - 1);
            grafo_invertido[destino - 1].push_back(origem - 1);
            grupo[origem - 1].observa.push_back(destino - 1);
        }

        for (int i = 0; i < postos; ++i) {
            fila.push(grupo[i]);
        }

        imprime_dados(postos, visao, soldados, grupo, grafo_invertido); // Impressão

        dominou_alguem = false;
        string resposta = "possivel";
        while (!fila.empty()) {
            um_nodo = fila.top();
            fila.pop();
            if (expandido[um_nodo.posicao] == 0) {
                dfs_invertido(um_nodo, grafo_invertido, expandido, &soldados, grupo, grafo, postos);
                if (expandido[um_nodo.posicao] == 0)
                    fila_aux.push(um_nodo);
            }

            if (fila.empty()) {
                if(!dominou_alguem) {
                    resposta = "impossivel";
                    break;
                }

                //preenche fila com variaveis nao descartadas
                while (!fila_aux.empty()) {
                    fila.push( fila_aux.top() );
                    fila_aux.pop();
                }
            }
        }

        cout << resposta << endl;
        cin >> postos >> visao >> soldados;
    }

    return 0;
}