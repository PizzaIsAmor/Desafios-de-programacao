#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int mdc(int m, int n) {
    if (m == 0)
        return n;
    return mdc(n % m, m);
}

int main() {
    int azulejos, a, b;

    cin >> azulejos >> a >> b;
    while (azulejos != 0 && a != 0 && b != 0) {
        long resp = 0;

        resp += floor(azulejos / a);
        resp += floor(azulejos / b);
        resp -= floor(azulejos / ((a * b) / mdc(a, b)));
        cout << resp << endl;

        cin >> azulejos >> a >> b;
    }
}