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

void resuelveCaso() {
  int p, V; std::cin >> p >> V;

  std::vector<int> batteries(p);
  for (int &i : batteries)
    cin >> i;
  
  std::sort(batteries.begin(), batteries.end(), std::greater<int>());

  int nCars = 0;
  int maxIndex = 0, minIndex = batteries.size() - 1;
  while (maxIndex < minIndex) {
    if (batteries[maxIndex] + batteries[minIndex] < V)
      minIndex--;
    else {
      maxIndex++;
      minIndex--;
      nCars++;
    }
  }

  std::cout << nCars << "\n";
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
  int n; std::cin >> n;
  for (int i = 0; i < n; i++) resuelveCaso();
  
  // para dejar todo como estaba al principio
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  system("PAUSE");
#endif
  return 0;
}
