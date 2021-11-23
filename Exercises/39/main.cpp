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
#include "EnterosInf.h"

using namespace std;

//@ <answer>

struct cordel {
  int lon;
  int coste;
};

bool resuelveCaso() {
  int N, L; std::cin >> N >> L;

  if (!std::cin) return false;

  std::vector<cordel> cordeles(N);
  for (auto &c : cordeles)
    std::cin >> c.lon >> c.coste;
  
  Matriz<EntInf> tablaCometa(N + 1, L + 1, Infinito);

  tablaCometa[0][0] = 0;
  for (int i = 0; i <= N; i++) {
    tablaCometa[i][0] = 0;
    for (int j = 1; j <= L; j++) {
      if ()
    }
  }
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
