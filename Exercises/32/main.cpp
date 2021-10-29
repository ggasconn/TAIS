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
int minimizarCompra(std::vector<int> const& t, std::vector<int> const& e) {
  int i = 0, j = 0;
  int prendasComprar = t.size();

  while (i < t.size() && j < e.size()) {
    if (t[i] == e[j] || t[i] + 1 == e[j]) { // La prenda le vale
      i++; j++; prendasComprar--;
    } else if (t[i] > e[j]) // El jugador más pequeño es mayor que la minima talla
      j++;
    else
      i++;
  }

  return prendasComprar;
}

bool resuelveCaso() {
  int n, m; std::cin >> n >> m;

  if (!std::cin) return false;

  std::vector<int> tallaJugadores(n);
  for (int &i : tallaJugadores)
    std::cin >> i;
  
  std::vector<int> equipacionesDisponibles(m);
  for (int &i : equipacionesDisponibles)
    std::cin >> i;

  std::sort(tallaJugadores.begin(), tallaJugadores.end(), less<int>());
  std::sort(equipacionesDisponibles.begin(), equipacionesDisponibles.end(), less<int>());
  
  cout << minimizarCompra(tallaJugadores, equipacionesDisponibles) << "\n";

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
