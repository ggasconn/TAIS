#include <fstream>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

#define lli long long int

bool resolver_caso() {
    int n; std::cin >> n;

    if ( n == 0 ) return false;

    std::priority_queue<lli, std::vector<lli>, std::greater<lli>> seguidores;

    int temp;
    for (int i = 0; i < n; i++) {
        std::cin >> temp;
        seguidores.push(temp);
    }

    lli t1, t2; // equipos
    lli gorras = 0;

    while(!seguidores.empty() && seguidores.size() > 1) {
        t1 = seguidores.top(); seguidores.pop(); // menor que t2, gana este
        t2 = seguidores.top(); seguidores.pop();
        gorras += t1 + t2;
        seguidores.push(t1 + t2);
    }

    std::cout << gorras << "\n";

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