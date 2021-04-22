#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main() {
    long long ana, beto, num = 1, minimun;
    cin >> ana >> beto;

    for (long long i = 2; i < 1000000LL; ++i) {
        long long expA = 0, expB = 0;

        while (ana % i == 0) {
            expA++;
            ana /= i;
        }

        while (beto % i == 0) {
            expB++;
            beto /= i;
        }

        minimun = min(expA, expB);
        num *= pow(i, ((minimun + (minimun % 2)) / 2LL));
    }

    if (ana == beto)
        num *= ana;

    cout << num << endl;

    return 0;
}