#include <iostream>
#include <climits>

using namespace std;

int diferenca(string str1, string str2) {
    int diffs = 0;

    if (str2.size() < str1.size()) {
        string aux = str2;
        str2 = str1;
        str1 = aux;
    }

    for (int i = 0; i < str1.size(); ++i)
        if (str1[i] != str2[i])
            diffs++;

    diffs += str2.size() - str1.size();

    return diffs;
}


int main() {
    string pal, strAux;
    int bstPosi, bstDiff = INT_MAX;
    int k;

    cin >> pal;
    cin >> k;
    for (int i = 1; i <= 5; ++i) {
        cin >> strAux;
        int diff = diferenca(pal, strAux);

        if (diff < bstDiff) {
            bstDiff = diff;
            bstPosi = i;
        }
    }

    if (bstDiff > k)
        cout << "-1" << endl;
    else
        cout << bstPosi << endl << bstDiff << endl;

    return 0;
}