#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>


bool resolver_caso() {
    int n; std::cin >> n;

    if (!std::cin) return false;

    std::vector<int> precios(n);
    for (int &p : precios) std::cin >> p;

    std::sort(precios.begin(), precios.end(), std::greater<int>());

    int descuento = 0;
    int index = 2;

    while (index < precios.size()) {
        descuento += precios[index];
        index += 3;
    }

    std::cout << descuento << "\n";

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