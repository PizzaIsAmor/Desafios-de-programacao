#include <iostream>

using namespace std;

long long mdc(long long m, long long n) {
    if (m == 0)
        return n;

    return mdc(n % m, m);
}

long long MMC(long long m, long long n) {
    return (m * n) / mdc(m, n);
}

int main() {
    long long N, B[100], j;
    long long T = 1, mmc;

    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> B[i];

    for (int i = 0; i < N; i++) {
        j = B[i] - 1;
        while (B[i] != B[j]) {
            j = B[j] - 1;
            T++;
        }

        if (i == 0)
            mmc = T;
        else
            mmc = MMC(T, mmc);
        T = 1;
    }

    cout << mmc << endl;

    return 0;
}