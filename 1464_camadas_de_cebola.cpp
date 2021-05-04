#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct PONTO {
    double x, y;
} ponto;

bool operator==(const struct PONTO &lhs, const struct PONTO &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

ponto extremo; // extremo esquerdo inferior

bool compara(ponto p1, ponto p2) { // compara pela tangente do angulo
    double dx1 = p1.x - extremo.x, dx2 = p2.x - extremo.x;
    double dy1 = p1.y - extremo.y, dy2 = p2.y - extremo.y;
    if (dx1 == 0) return dy1 == 0 || (dx2 == 0 && dy1 < dy2);
    if (dx2 == 0) return dy2 != 0;
    if (dy1 * dx2 == dy2 * dx1) return dx1 < dx2;
    if (dx1 * dx2 < 0) return dy1 * dx2 > dy2 * dx1;
    return dy1 * dx2 < dy2 * dx1;
}

bool esquerda(ponto p1, ponto p2, ponto p3) { // verifica se p3 está a esquerda de p1->p2
    return ((p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y)) > 0;
}

bool naLinha(ponto p1, ponto p2, ponto p3) { // verifica se p3 está a esquerda de p1->p2
    return ((p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y)) == 0;
}

vector<ponto> convexo(vector<ponto> pontos) {
    extremo = pontos[0];

    for (int i = 1; i < (int) pontos.size(); i++)
        if (pontos[i].x < extremo.x || (pontos[i].x == extremo.x && pontos[i].y < extremo.y))
            extremo = pontos[i];

    sort(pontos.begin(), pontos.end(), compara);

    vector<ponto> envoltorio;
    envoltorio.push_back(pontos[0]);
    int n = 1;

    for (int i = 1; i < (int) pontos.size(); i++) {
        while (n > 1 && !esquerda(envoltorio[n - 2], envoltorio[n - 1], pontos[i])) {
            n--;
            envoltorio.pop_back();
        }
        envoltorio.push_back(pontos[i]);
        n++;
    }

    return envoltorio;
}

int main() {
    int camadas, maxPontos;
    vector<ponto> pontos;

    cin >> maxPontos;
    while (maxPontos != 0) {
        // iniciliza conjunto de pontos
        for (int i = 0; i < maxPontos; ++i) {
            ponto p;
            cin >> p.x >> p.y;
            pontos.push_back(p);
        }

        camadas = 0;
        while (pontos.size() > 2) {
            camadas++;
            vector<ponto> conv = convexo(pontos);

            //Tira pontos do conv;
            for (auto &j : conv)
                pontos.erase(remove(pontos.begin(), pontos.end(), j), pontos.end());

            int vezes = 0;
            for (int j = 0; j < pontos.size(); ++j) {
                for (int i = 1; i < conv.size(); ++i)
                    if (naLinha(conv[i - 1], conv[i], pontos[j])) {
                        pontos.erase(remove(pontos.begin(), pontos.end(), pontos[j]), pontos.end());
                        j--;
                        break;
                    }

                if (naLinha(conv[conv.size() - 1], conv[0], pontos[j])) {
                    pontos.erase(remove(pontos.begin(), pontos.end(), pontos[j]), pontos.end());
                    j--;
                }
                vezes++;
            }
        }

        if (camadas % 2 == 0)
            cout << "Do not take this onion to the lab!" << endl;
        else
            cout << "Take this onion to the lab!" << endl;

        cin >> maxPontos;
    }

    return 0;
}