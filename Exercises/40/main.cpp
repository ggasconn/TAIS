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

#include "EnterosInf.h"
#include "Matriz.h"

using namespace std;

/*
Casos Base:
  maxPuntuacion(i, 0) = 0, no hay puntos que sumar
  maxPuntuacion(0, j) = inf, no quedan sectores

Casos Recursivos:
  maxPuntuacion(i, j) = maxPuntuacion(i - 1, j) si s[i] > j
  maxPuntuacion(i, j) = max(maxPuntuacion(i, j - s[i]) + 1,
                            maxPuntuacion(i - 1, j))
*/

void maxPuntuacion(std::vector<int> const& sectores, int S, int V, Matriz<EntInf>& puntuaciones) {
  puntuaciones[0][0] = 0;

  for (int i = 1; i <= S; i++) {
    puntuaciones[i][0] = 0;

    for (int j = 1; j <= V; j++) {
      if (sectores[i - 1] > j)
        puntuaciones[i][j] = puntuaciones[i - 1][j];
      else
        puntuaciones[i][j] = min(puntuaciones[i - 1][j], puntuaciones[i][j - sectores[i - 1]] + 1);
    }
  }
}

bool resuelveCaso() {
  int V, S; std::cin >> V >> S;

  if (!std::cin) return false;

  std::vector<int> sectores(S);
  for (int &i : sectores)
    std::cin >> i;
  
  Matriz<EntInf> puntuaciones(S + 1, V + 1, Infinito);

  maxPuntuacion(sectores, S, V, puntuaciones);

  if (puntuaciones[S][V] == Infinito)
    cout << "Imposible";
  else {
    std::vector<int> dardos(S, 0);
    
    int i = S, j = V;
    while (j > 0) {

      if (sectores[i - 1] > j)
        i--;
      else if (puntuaciones[i][j - sectores[i - 1]] < puntuaciones[i][j]) {
        dardos[i - 1]++;
        j -= sectores[i - 1];
      }else
        i--;
    }

    cout << puntuaciones[S][V] << ": ";
    for (int i = dardos.size() - 1; i >= 0; i--) {
      for (int j = 0; j < dardos[i]; j++)
        cout << sectores[i] << " ";
    }
  }

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
