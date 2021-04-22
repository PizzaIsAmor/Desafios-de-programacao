#include <iostream>

#define NUM_MAX 1000007

using namespace std;

long long combinacao(long long n, long long p) {
    long long max, min;
    long long resp = 1, div = 1;

    if (n - p > p) {
        max = n - p;
        min = p;
    } else {
        max = p;
        min = n - p;
    }

    for (; n > max; --n)
        resp *= n;

    for (; min >= 2; --min)
        div *= min;

    return (resp / div) % NUM_MAX;
}

long long colorindoTetraedro(long long n) {
    long long resp = 0;
    if (n > 0)      // colorir esolhendo 1 cor
        resp += n % NUM_MAX;

    if (n >= 2) {     // colorir escolhendo 2 cores
        resp += (n * (n - 1)) % NUM_MAX;
        resp += combinacao(n, 2) % NUM_MAX;  // caso para pintar colorindo 3 cores
    }

    if (n >= 3)     //escolher colorindo 3 cores
        resp += (n * combinacao(n - 1, 2)) % NUM_MAX;

    if (n >= 4)     //escolher colorindo 4 cores
        resp += (2 * combinacao(n, 4)) % NUM_MAX;

    return resp % NUM_MAX;
}

int main() {
    int cores;
    cin >> cores;

    while (cores != 0) {
        cout << colorindoTetraedro(cores) << endl;

        cin >> cores;
    }

    return 0;
}