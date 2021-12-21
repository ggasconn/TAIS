#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>


bool resolver_caso() {
    int n; std::cin >> n;

    if ( n == 0 ) return false;

    std::vector<int> people(n);
    for (int &p : people) std::cin >> p;

    std::vector<int> skis(n);
    for (int &s : skis) std::cin >> s;

    sort(people.begin(), people.end());
    sort(skis.begin(), skis.end());

    int totalDiference = 0;
    for (int i = 0; i < n; i++)
        totalDiference += std::abs(people[i] - skis[i]);
    
    std::cout << totalDiference << "\n";

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