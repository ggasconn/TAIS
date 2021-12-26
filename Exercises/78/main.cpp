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
    //if (a.tiempo == b.tiempo) return a.idCaja < b.idCaja;
    return a.tiempo < b.tiempo;
}

bool resolver_caso() {
    int cajas, clientes; std::cin >> cajas >> clientes;

    if (cajas == 0 && clientes == 0) return false;

    std::priority_queue<cliente> fila;
    cliente c;
    cliente cAux;
    int cajasOcupadas = 0;
    int caja = 1;
    while(clientes) {
        if (cajasOcupadas < cajas) {
            std::cin >> c.tiempo;
            c.idCaja = caja;
            caja++;
            fila.push(c);
        }
        if (cajasOcupadas == cajas) {
            cAux = fila.top();
            fila.pop();
            std::cin >> c.tiempo;
            c.tiempo += cAux.tiempo;
            c.idCaja = cAux.idCaja;
            caja = c.idCaja;
            fila.push(c);
        }

        clientes--;
    }

    std::cout << caja << "\n";

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