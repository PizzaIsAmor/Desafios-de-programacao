#include <iostream>
#include <utility>
#include <vector>
#include <cstring>

#define ALFABETO 28

using namespace std;

typedef struct vertice {
    int arcos[ALFABETO];
    bool chave = false;
    string val;

    vertice() {
        fill(begin(arcos), end(arcos), -1);
    }
} nodo;

vector<nodo> trie(1);

void adiciona(string const &s, string valor) {
    int v = 0;
    for (char ch : s) {
        int c;
        if (ch == ' ')
            c = 27;
        else
            c = ch - 'a';
        if (trie[v].arcos[c] == -1) {
            trie[v].arcos[c] = trie.size();
            trie.emplace_back();
        }
        v = trie[v].arcos[c];
    }
    trie[v].chave = true;
    trie[v].val = std::move(valor);
}

string busca(const string &s) {
    int v = 0;
    for (char ch : s) {
        int c;
        if (ch == ' ')
            c = 27;
        else
            c = ch - 'a';

        if (trie[v].arcos[c] == -1)
            return "";

        v = trie[v].arcos[c];
    }

    if (trie[v].chave)
        return trie[v].val;
    return "";
}

size_t split(const string &txt, vector<string> &strs, char ch) {
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while (pos != std::string::npos) {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    // Add the last one
    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return strs.size();
}

string traducao(const string &pal) {
    vector<string> list;
    string resp;

    split(pal, list, ' ');

    for (int i = 0; i < list.size(); ++i) {
        int j = i + 1;
        string auxP = list[i];
        string val = busca(auxP);
        while (val.empty() && j < list.size()) {
            auxP = auxP + ' ' + list[j];
            j++;
            val = busca(auxP);
        }

        if (val.empty())
            resp += list[i] + ' ';
        else
            resp += val + ' ';
    }
    resp.pop_back();

    return resp;
}

int main() {
    int quant, dicionario, musica;
    string jap, significado;

    for (cin >> quant; quant > 0; --quant) {
        cin >> dicionario >> musica;
        for (; dicionario > 0; --dicionario) {
            getline(cin >> ws, jap);
            getline(cin >> ws, significado);

            adiciona(jap, significado);
        }

        for (; musica > 0; --musica) {
            getline(cin >> ws, jap);

            cout << traducao(jap) << endl;
        }

        cout << endl;

        while (!trie.empty())
            trie.pop_back();

        nodo reset;
        trie.push_back(reset);
    }

    return 0;
}