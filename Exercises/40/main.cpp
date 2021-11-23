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


int maxPuntuacion(std::vector<int> const& sectores, int i, int j, Matriz<int> puntuaciones) {

  if (puntuaciones[i][j] != -1)
    return puntuaciones[i][j];
  
  if (i == 0 || j == 0)
    return 0;
  else if (sectores[i - 1] > j)
    puntuaciones[i][j] = maxPuntuacion(sectores, i - 1, j, puntuaciones);
  else
    puntuaciones[i][j] = max(maxPuntuacion(sectores, i - 1, j, puntuaciones),
                             maxPuntuacion(sectores, i - 1, j - sectores[i - 1], puntuaciones) + sectores[i - 1]);
  
  return puntuaciones[i][j];
}

bool resuelveCaso() {
  int v, s; std::cin >> v >> s;

  if (!std::cin) return false;

  std::vector<int> sectores(s);
  for (int &i : sectores)
    std::cin >> i;
  
  Matriz<int> puntuaciones(v + 1, s + 1, -1);

  maxPuntuacion(sectores, v, s, puntuaciones);

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
