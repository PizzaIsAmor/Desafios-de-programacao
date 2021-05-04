#include <iostream>
#include <vector>
#include <valarray>
#include <iomanip>

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

vector <ponto> convexo(vector <ponto> pontos) {
    extremo = pontos[0];

    for (int i = 1; i < (int) pontos.size(); i++)
        if (pontos[i].x < extremo.x || (pontos[i].x == extremo.x && pontos[i].y < extremo.y))
            extremo = pontos[i];

    sort(pontos.begin(), pontos.end(), compara);

    vector <ponto> envoltorio;
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

double distancia(ponto pi, ponto pf) {
    return sqrt(pow((pi.x - pf.x), 2) + pow((pi.y - pf.y), 2));
}

int main() {
    int quant;
    double resp;
    vector <ponto> pontos;

    cin >> quant;
    while (quant != 0) {
        resp = 0;
        for (int i = 0; i < quant; ++i) {
            ponto p;
            cin >> p.x >> p.y;
            pontos.push_back(p);
        }

        vector <ponto> conv = convexo(pontos);
        for (int i = 1; i < conv.size(); ++i)
            resp += distancia(conv[i - 1], conv[i]);
        resp += distancia(conv[conv.size()-1], conv[0]);

        cout << "Tera que comprar uma fita de tamanho " << fixed << setprecision(2) << resp << "." << endl;

        while (!pontos.empty()) {
            pontos.pop_back();
        }

        cin >> quant;
    }
}