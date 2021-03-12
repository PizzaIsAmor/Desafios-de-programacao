#include <iostream>
#include <list>
using namespace std;
#define MAXN 10000

typedef struct str_arco {
    int destino;
    int capacidade;
    int fluxo;
    int tipo;
    str_arco* proximo;
    str_arco* reverso;
} ARCO, *pARCO;

pARCO grafo[MAXN]; //Lista de adjacência com capacidade, fluxo e tipo do arco
int M; //Limitante superior para o fluxo de qualquer arco

//Semelhante ao BFS, encontra um caminho aumentador com número mínimo de vértices
void encontra_caminho_aumentador(int s, int t, int caminho_pred[], pARCO caminho_arcos[]) {
    list< int > expandir; //Fila de vértices que precisa expandir
    int expandido[MAXN]; //Indica se o vértice foi adicionado na fila
    expandir.push_back(s); //Indica que precisa expandir o vértice
    expandido[s] = 1; //Marca como expandido
    while(!expandir.empty()){//Enquanto a fila não estiver vazia
        v = expandir.pop_front();//Retira o primeiro vértice da fila
        if(v == t) break;//Se chegou em t, já achou um caminho aumentador
        //Percorre os adjacêntes
        for(pARCO arco = grafo[v]; arco != NULL; arco = arco->proximo) {
            int adjacente = arco->destino; //Obtém o adjacente
            //Calcula a diferênça entre a capacidade e o fluxo do arco
            int folga = arco->capacidade - arco->fluxo;
            //Verifica se o adjacente não foi expandido e se o arco não está cheio
            if(expandido[adjacente] == 0 && folga > 0) {
                expandir.push_back(adjacente); //Adiciona na fila para expandir
                expandido[adjacente] = 1; //Marca que foi adicionado na fila expandido
                caminho_pred[adjacente] = v; //Coloca v como predecessor do adjacente
                caminho_arcos[adjacente] = arco; //Coloca arco usado
            }
        }
    }
}

//Encontra um caminho aumentador e calcula o máximo aumento dele
int min_caminho_aumentador(int s, int t, int caminho_pred[], pARCO caminho_arcos[]) {
    caminho_pred[t] = -1; //Coloca que ainda não há caminho aumentador até t
    encontra_caminho_aumentador(s, t, caminho_pred, caminho_arcos);
    if(caminho_pred[t] == -1) //Se não chegou até t, então não há caminhos aumentadores
        return 0;
    //Calcula folga para aumentar o caminho
    int v = t; //Começa pelo arco que chega no destino
    int delta = M; //Assume que a folga inicial é o máximo possível
    while(v != s) { //Enquanto não chega no fonte
         //Calcula a folga do arco até v
        int folga = caminho_arcos[v]->capacidade - caminho_arcos[v]->fluxo;
        if(delta > folga)//O fluxo não pode aumentar mais do que a folga do arco
            delta = folga;
        v = caminho_pred[v]; //Se movimenta para o predecessor
    }
    return delta;
}

int ford_fulkerson(int s, int t) {
    int delta, fluxo = 0, v;
    int caminho_pred[MAXN];
    pARCO caminho_arcos[MAXN];
    do {
        //Calcula o caminho aumentador com menor número de vértices
        delta = min_caminho_aumentador(s, t, caminho_pred, caminho_arcos);
        if(delta > 0) { //Se existe caminho aumentador atualiza o fluxo no grafo
            //Percorre os vértices do caminho de t até s
            for(v = t; v != s; v = caminho_pred[v]) {
                //Atualiza o valor do fluxo do arco
                caminho_arcos[v]->fluxo += delta;
                //Atualiza o valor do fluxo do arco inverso
                caminho_arcos[v]->reverso->fluxo = -caminho_arcos[v]->fluxo;
            }
            fluxo += delta; //incrementa o fluxo
        }
    } while(delta > 0);

    return fluxo;
}

int le_grafo() {
    int n, m, v, camisas, pessoas;
    string tamanho;
    //No final M será igual à máxima capacidade que é um limitante para o fluxo dos arcos
    M = 0;
    cin >> camisas >> pessoas;//Lê o número de vértices e arcos



    int quantidade_camisas = camisas / 6;
    for(int i = 1; i <= pessoas; i++) {
        auto arco = (pARCO) calloc(1, sizeof(ARCO));

        int inicio_camisa = 0;
        switch(tamanho) {
            case "L": inicio_camisa = 3; break;
            case "M": inicio_camisa = 2; break;
            case "S": inicio_camisa = 1; break;
            case "XL": inicio_camisa = 4; break;
            case "XS": inicio_camisa = 0; break;
            case "XXL": inicio_camisa = 5; break;
            default: break;
        }

        for (int i = 0; i < quantidade_camisas; ++i) {
            arco->destino[i] = grafo[inicio_camisa + i];
        }



        arco->capacidade = 1;//Lê origem, destino e capacidade
        arco->tipo = 1;//Coloca que é arco original
        arco->fluxo = 0;//Inicialmente o fluxo é zero
        arco->proximo = grafo[i];//O próximo é o primeiro arco do mesmo vértice (lista)
        grafo[i] = arco;
    }

    return n;
}

void adiciona_arcos_artificiais(int n) {
    for(int v = 1; v <= n; v++) {
        for(pARCO arco = grafo[v]; arco != nullptr; arco = arco->proximo) {
            if(arco->tipo == 1) { //Somente adiciona cópia de arco original
                arco->reverso = (pARCO)calloc(1, sizeof(ARCO)); //Separa memória
                arco->reverso->destino = v; //O destino do reverso é a origem
                arco->reverso->capacidade = 0; //A capacidade do reverso é zero
                arco->reverso->fluxo = 0;//O fluxo inicial é zero
                arco->reverso->tipo = -1;//O tipo é reverso
                arco->reverso->reverso = arco;//O reverso do reverso é o próprio arco
                //Adiciona o reverso no grafo
                arco->reverso->proximo = grafo[arco->destino];
                grafo[arco->destino] = arco->reverso;
            }
        }
    }
}


int main() {
    int vezes;

    cin >> vezes;
    for (int i = 0; i < vezes; ++i) {
        adiciona_arcos_artificiais(le_grafo());

        cout << ford_fulkerson(s, t);
    }

    return 0;
}