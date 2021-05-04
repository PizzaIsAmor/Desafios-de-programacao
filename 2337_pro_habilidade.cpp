#include <iostream>
#include <valarray>
#define lli long long int

using namespace std;

lli mdc(lli a, lli b) {
    if (a == 0)
        return b;

    return mdc(b % a, a);
}

lli fib(lli n) {
    lli f[n + 1];
    lli i;

    f[0] = 0;
    f[1] = 1;

    for (i = 2; i <= n; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }

    return f[n];
}

int main() {
    lli n;

    while (cin >> n) {
        lli a = fib(n + 2);
        double b = pow(2, n);

        lli m = abs(mdc(a, b));

        lli A = a / m;
        lli B = (lli) b / m;

        cout << A << "/" << B << endl;
    }

    return 0;
}