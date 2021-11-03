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

int maximizeWins(std::vector<int> const& r, std::vector<int> const& w) {
  int points = 0;

  for (int i = 0; i < r.size(); i++)
    if (w[i] > r[i]) points += w[i] - r[i];
  
  return points;
}

bool resuelveCaso() {
  int n; std::cin >> n;

  if (n == 0) return false;

  std::vector<int> rivals(n);
  for (auto &i : rivals) std::cin >> i;
  
  std::vector<int> wins(n);
  for (auto &i : wins) std::cin >> i;

  std::sort(rivals.begin(), rivals.end(), std::greater<int>());
  std::sort(wins.begin(), wins.end(), std::less<int>());

  std::cout << maximizeWins(rivals, wins) << "\n";

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
