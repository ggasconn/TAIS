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

#define INF 1000000000

void devolverCambio(vector<int> const& M, int C, vector<int>& monedas) {
  int n = M.size();
  monedas[0] = 0;

  // calcular la matriz sobre el propio vector
  for (int i = 1; i <= n; ++i)
      for (int j = M[i-1]; j <= C; ++j)
        monedas[j] = min(monedas[j], monedas[j - M[i-1]] + 1);
}

bool resuelveCaso() {
  int C, N; std::cin >> C >> N;

  if (!std::cin) return false;

  std::vector<int> M(N);

  for (int &m : M) std::cin >> m;

  vector<int> monedas(C + 1, INF);
  devolverCambio(M, C, monedas);

  int minMonedas = monedas[C];
  int maneras = 0;

  for (int i = 0; i < N; i++) {
    int monedasUsadas = 0;
    int monedaActual = i;
    int cambio = C;

    while (monedasUsadas <= minMonedas && cambio > 0) {
      if (monedas[cambio - M[monedaActual]] + 1 == monedas[cambio]) {
        monedasUsadas++; cambio -= M[monedaActual];
      }else if (monedaActual + 1 < N) monedaActual++;
      else break;
    }

    if (cambio == 0) maneras++;
  }

  std::cout << maneras << "\n";

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
