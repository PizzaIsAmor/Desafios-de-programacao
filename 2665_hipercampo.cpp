#include <bits/stdc++.h>

using namespace std;

typedef struct PONTO {
    double x;
    double y;
} ponto;

vector<ponto> pontos;
vector<ponto> poligono;
vector<int> quantCamadas;

bool operator<(const ponto &a, const ponto &b) {
    return a.y < b.y;
}

long det(ponto ini, ponto fim, ponto teste) { // verifica se teste está a esquerda de ini->fim
    return ((ini.x - teste.x) * (fim.y - teste.y) - (fim.x - teste.x) * (ini.y - teste.y));
}

bool esquerda(ponto p1, ponto p2, ponto p3) {
    return det(p1, p2, p3) > 0;
}

bool dentro(ponto p) {
    if (esquerda(poligono[0], poligono[1], p) && esquerda(poligono[1], poligono[2], p)
        && esquerda(poligono[2], poligono[0], p))
        return true;

    return false;
}

void contaTringulos(int posi) {
    int contador = 1;    // Considerando o triangulo dessa posicao
    for (int j = posi - 1; j >= 0; --j)
        if (dentro(pontos[j]) && quantCamadas[j] >= contador)
            contador = quantCamadas[j] + 1;

    quantCamadas.push_back(contador);
}

int main() {
    ponto ponto_A, ponto_B, ponto_temp;
    int num_pontos; // sem contar os pontos âncoras A e B

    ponto_A.y = 0;
    ponto_B.y = 0;

    // leitura do input
    cin >> num_pontos >> ponto_A.x >> ponto_B.x;
    for (int p = 0; p < num_pontos; p++) {
        cin >> ponto_temp.x >> ponto_temp.y;
        pontos.push_back(ponto_temp);
    }
    // fim da leitura

    sort(pontos.begin(), pontos.end(), less<ponto>());

    int max_triangulos = 0;
    poligono.push_back(ponto_A);
    poligono.push_back(ponto_B);
    for (int i = 0; i < pontos.size(); ++i) {
        poligono.push_back(pontos[i]);

        contaTringulos(i);
        if (quantCamadas[i] > max_triangulos)
            max_triangulos = quantCamadas[i];

        poligono.pop_back();
    }

    cout << max_triangulos << endl;
}