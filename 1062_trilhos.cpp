#include <iostream>
#include <vector>

using namespace std;

vector<int> ordena(vector<int> lista, int max) {
    vector<int> ordenando, estacao;

    while (!lista.empty()) {
        int val = lista.back();
        lista.pop_back();

        if (val == max) {
            ordenando.push_back(val);
            max--;

            while (!estacao.empty() && estacao[estacao.size() - 1] == max) {
                val = estacao.back();
                estacao.pop_back();
                ordenando.push_back(val);
                max--;
            }
        } else
            estacao.push_back(val);
    }

    return ordenando;
}


int main() {
    int quant, posi;
    vector<int> vagoes, ordenado;

    cin >> quant;
    while (quant != 0) {
        cin >> posi;
        while (posi != 0) {
            vagoes.push_back(posi);

            for (int i = 1; i < quant; ++i) {
                cin >> posi;
                vagoes.push_back(posi);
            }

            ordenado = ordena(vagoes, quant);

            if (ordenado.size() == quant)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;

            cin >> posi;
            vagoes.clear();
        }

        cin >> quant;
        cout << endl;
    }

    return 0;
}