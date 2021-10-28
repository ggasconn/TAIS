/*@ <answer>
 *
 * Nombre y Apellidos: Guillermo Gascón Celdrán TAIS34
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

//@ <answer>
int minimizarParches(std::vector<int> const& m, int l) {
  int nParches = 1;
  int maxDist = m[0] + l;

  for (int i = 1; i < m.size(); i++) {
    if (m[i] > maxDist) {
      nParches++;
      maxDist = m[i] + l;
    }
  }

  return nParches;
}

bool resuelveCaso() {
  int a, l; std::cin >> a >> l;

  if (!std::cin) return false;

  std::vector<int> manguera(a);
  for (int &i : manguera)
    std::cin >> i;

  std::cout << minimizarParches(manguera, l) << "\n";
  
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
