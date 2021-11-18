/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

/*@ <answer>
 *
 * Nombre y Apellidos: Guillermo Gascón Celdrán TAIS34
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>

#include "Matriz.h"

using namespace std;

//@ <answer>
struct tesoro {
  int prof;
  int oro;
};

int encontrarTesoros(std::vector<tesoro> const& tesoros, int i, int t, Matriz<int> &tablaTesoros) {
  if (tablaTesoros[i][t] != -1)
    return tablaTesoros[i][t];

  if (t == 0 || i == 0)
    tablaTesoros[i][t] = 0;
  else if ((tesoros[i - 1].prof * 2) +  tesoros[i - 1].prof > t)
    tablaTesoros[i][t] = encontrarTesoros(tesoros, i - 1, t, tablaTesoros);
  else
    tablaTesoros[i][t] = max(encontrarTesoros(tesoros, i - 1, t, tablaTesoros),
                             encontrarTesoros(tesoros, i - 1, t - ((tesoros[i - 1].prof * 2) + tesoros[i - 1].prof), tablaTesoros) + tesoros[i - 1].oro);
  
  return tablaTesoros[i][t];
}

bool resuelveCaso() {
  int t; std::cin >> t;

  if (!std::cin) return false;

  int n; std::cin >> n;
  std::vector<tesoro> tesoros(n);

  for (auto &t : tesoros)
    cin >> t.prof >> t.oro;

  Matriz<int> tablaTesoros(n + 1, t + 1, -1);
  
  encontrarTesoros(tesoros, n, t, tablaTesoros);

  int i = n, j = t;
  std::deque<tesoro> sol;

  while (i > 0 && j > 0) {
    if (tablaTesoros[i][j] != tablaTesoros[i - 1][j]) {
      sol.push_front(tesoros[i - 1]); j -= ((tesoros[i - 1].prof * 2) +  tesoros[i - 1].prof);
    }
    --i;
  }

  std::cout << tablaTesoros[n][t] << "\n";
  std::cout << sol.size() << "\n";
  for (auto t : sol)
    std::cout << t.prof << " " << t.oro << "\n";
  std::cout << "---\n"; 

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
