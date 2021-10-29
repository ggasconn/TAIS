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

using namespace std;

//@ <answer>
int maximizarDefensa(std::vector<int> const& e, std::vector<int> const& d) {
  int dIndex = 0;
  int nVictorias = 0;
  
  for (int i = 0; i < e.size(); i++) {
    if (e[i] <= d[dIndex]) {
      dIndex++;
      nVictorias++;
    }
  }

  return nVictorias;
}

bool resuelveCaso() {
  int n; std::cin >> n;

  if (!std::cin) return false;

  std::vector<int> enemigos(n);
  for (int &i : enemigos)
    std::cin >> i;

  std::vector<int> defensa(n);
  for (int &i : defensa)
    std::cin >> i;

  std::sort(enemigos.begin(), enemigos.end(), greater<int>());
  std::sort(defensa.begin(), defensa.end(), greater<int>());

  std::cout << maximizarDefensa(enemigos, defensa) << "\n";

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
