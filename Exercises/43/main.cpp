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
#include <limits>

#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;

//@ <answer>

/*
  Caso Base:
    buscar(0, j) = INF. No quedan bombillas i
    buscar(i, 0) = 0. Se ha llegado a la potencia j

  Caso Recursivo:
    buscar(i, j) = buscar(i - 1, j) si b[i].potencia > j
    buscar(i, j) = min(buscar(i, j - b[i].potencia) + b.precio,
                                buscar(i - 1, j)) busco el minimo entre usar la bombilla i y no usarla
*/

#define INF 2000000000

struct bombilla {
  int potencia;
  int precio;
};

bool resuelveCaso() {
  int N, Pmax, Pmin; std::cin >> N >> Pmax >> Pmin;

  if (!std::cin) return false;

  std::vector<bombilla> v(N);
  for (bombilla &b : v) std::cin >> b.potencia;
  for (bombilla &b : v) std::cin >> b.precio;


  Matriz<int> precios(N + 1, Pmax + 1, INF);
  
  precios[0][0] = 0;

  for (int i = 1; i <= N; i++) {
    precios[i][0] = 0;
    for (int j = 1; j <= Pmax; j++) {
      if (v[i - 1].potencia > j) precios[i][j] = precios[i - 1][j];
      else
        precios[i][j] = min(precios[i - 1][j], precios[i][j - v[i - 1].potencia] + v[i - 1].precio);
    }
  }

  std::pair<int, int> bestPrice = {INF, Pmin}; // bestValue, bestValuePosition

  for (int i = Pmin; i <= Pmax; i++)
    if (precios[N][i] < bestPrice.first)
      bestPrice = {precios[N][i], i};
  
  if (bestPrice.first == INF) std::cout << "IMPOSIBLE";
  else std::cout << bestPrice.first << " " << bestPrice.second;

  cout << "\n";

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
