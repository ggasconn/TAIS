#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <map>
#include <set>
#include <utility>

using namespace std;


bool tratar_caso() {
  return false;  
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while(tratar_caso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif

    return 0;
}