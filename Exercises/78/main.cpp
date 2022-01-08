#include <fstream>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

struct cliente {
    int tiempo;
    int idCaja;
};

bool operator<(cliente const& a, cliente const& b) {
    if (a.tiempo == b.tiempo) return b.idCaja < a.idCaja;
    return b.tiempo < a.tiempo;
}

bool resolver_caso() {
    int N, C; std::cin >> N >> C;

    if (N == 0 && C == 0) return false;

    std::priority_queue<cliente> cola;

    int cajasOcupadas = 0;
    int tAux;
    for (int i = 0; i < C; i++) {
        std::cin >> tAux;

        if (cajasOcupadas >= N) {
            cliente c = cola.top(); cola.pop();
            cola.push({ tAux + c.tiempo, c.idCaja });
        }else {
            cola.push({ tAux, cajasOcupadas });
            cajasOcupadas++;
        }
    }

    if (cajasOcupadas < N) std::cout << cajasOcupadas + 1 << "\n";
    else std::cout << cola.top().idCaja + 1<< "\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while(resolver_caso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif

    return 0;
}