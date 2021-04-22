#include <iostream>

using namespace std;
long long resto[3], tamPacotes[3], m[3], m_b[3], m_bi[3];

long long algoritmoChinesDoResto(void) {
    m[0] = tamPacotes[1] * tamPacotes[2];
    m[1] = tamPacotes[0] * tamPacotes[2];
    m[2] = tamPacotes[0] * tamPacotes[1];

    m_b[0] = m[0] % tamPacotes[0];
    m_b[1] = m[1] % tamPacotes[1];
    m_b[2] = m[2] % tamPacotes[2];

    m_bi[0] = 1;
    while (((m_bi[0] * m_b[0]) % tamPacotes[0]) != 1)
        m_bi[0]++;

    m_bi[1] = 1;
    while (((m_bi[1] * m_b[1]) % tamPacotes[1]) != 1)
        m_bi[1]++;

    m_bi[2] = 1;
    while (((m_bi[2] * m_b[2]) % tamPacotes[2]) != 1)
        m_bi[2]++;

    long long result = resto[0] * m[0] * m_bi[0] + resto[1] * m[1] * m_bi[1] + resto[2] * m[2] * m_bi[2];
    result %= tamPacotes[0] * tamPacotes[1] * tamPacotes[2];

    if (result == 0)
        result += tamPacotes[0] * tamPacotes[1] * tamPacotes[2];

    return result;
}

int main() {
    int caso = 1;

    while (cin >> resto[0] >> tamPacotes[0] >> resto[1] >> tamPacotes[1] >> resto[2] >> tamPacotes[2]) {
        cout << "Caso #" << caso << ": " << algoritmoChinesDoResto() << " laranja(s)" << endl;
        caso++;
    }

    return 0;
}