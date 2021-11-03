/*@ <answer>
 *
 * Nombre y Apellidos: Guillermo Gascón Celdrán TAIS34
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <istream>
#include <string>

using namespace std;

struct building {
  int start;
  int end;
};

bool operator<(building const& a, building const& b) {
  return a.end < b.end;
}

int minimizeTunnels(std::vector<building> const& buildings) {
  int tunnels = 0;
  int tunnelEnd = 0;

  for (auto b : buildings)
    if (b.start >= tunnelEnd) {
      tunnels++;
      tunnelEnd = b.end;
    }

  return tunnels;
}

bool resuelveCaso() {
  int n; std::cin >> n;

  if (n == 0) return false;

  std::vector<building> buildings(n);
  for (auto &b : buildings) {
    int w, e; std::cin >> w >> e;
    b = { w, e };
  }

  std::sort(buildings.begin(), buildings.end(), std::less<building>());

  cout << minimizeTunnels(buildings) << "\n";

  return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
  // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
  std::ifstream in("casos.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  // Resolvemos
  while (resuelveCaso());
  
  // para dejar todo como estaba al principio
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  system("PAUSE");
#endif
  return 0;
}
