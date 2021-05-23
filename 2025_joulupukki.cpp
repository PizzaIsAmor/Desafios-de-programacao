#include <iostream>
#include <cstring>

using namespace std;

void computeLPSArray(const char *pat, int M, int *lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(char *pat, char *txt) {
    int M = strlen(pat);
    int N = strlen(txt);
    int lps[M];

    computeLPSArray(pat, M, lps);

    int i = 0;
    int j = 0;
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            int posi = i - j;

            txt[posi - 1] = 'J';
            txt[posi]     = 'o';
            txt[posi + 1] = 'u';
            txt[posi + 2] = 'l';
            txt[posi + 3] = 'u';
            txt[posi + 4] = 'p';
            txt[posi + 5] = 'u';
            txt[posi + 6] = 'k';
            txt[posi + 7] = 'k';
            txt[posi + 8] = 'i';

            j = lps[j - 1];
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
}

int main() {
    string msg;
    int quant;
    cin >> quant;

    for (int i = 0; i < quant; ++i) {
        getline(cin >> ws, msg);

        char arr[msg.length() + 1];

        strcpy(arr, msg.c_str());
        KMPSearch("oulupukk", arr);
        cout << arr << endl;
    }

    return 0;
}