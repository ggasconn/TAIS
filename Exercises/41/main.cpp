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
#include <string>

#include "Matriz.h"

using namespace std;

//@ <answer>

/*

Casos Base:
  Hemos llegado a una posición de fuera del tablero

Casos Recursivos:
  Se busca el máximo entre las casillas posibles a las que se puede desplazar

Llamada inicial:
  N, i siendo i el número de la columna a empezar
  
*/

int buscarRuta(Matriz<int> const& tablero, int i, int j, Matriz<int>& puntuaciones) {
  if (i <= 0 || j <= 0 || j > tablero.numcols() || i > tablero.numfils()) return 0;
  if (puntuaciones[i][j] != -1) return puntuaciones[i][j];
  else puntuaciones[i][j] = max(max(buscarRuta(tablero, i - 1, j - 1, puntuaciones) + tablero[i - 1][j - 1],
                                buscarRuta(tablero, i - 1, j, puntuaciones) + tablero[i - 1][j - 1]),
                                buscarRuta(tablero, i - 1, j + 1, puntuaciones) + tablero[i - 1][j - 1]);

  return puntuaciones[i][j];
}


bool resuelveCaso() {
  int n; std::cin >> n;

  if (!std::cin) return false;

  Matriz<int> tablero(n, n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      std::cin >> tablero[i][j];
    
  Matriz<int> puntos(n + 1, n + 1, -1);

  for (int i = 1; i <= n; i++)
    buscarRuta(tablero, n, i, puntos);

  std::pair<int, int> mejorPuntuacion = { puntos[n][1], 1 }; // Puntos, posicion

  for (int i = 1; i <= n; i++)
    if (puntos[n][i] > mejorPuntuacion.first)
      mejorPuntuacion = { puntos[n][i], i };

  std::cout << mejorPuntuacion.first << " " << mejorPuntuacion.second << "\n";

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
