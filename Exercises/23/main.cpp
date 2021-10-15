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
#include <vector>
#include <queue>

using namespace std;

#include "GrafoValorado.h"

/*@ <answer>

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class Mapa {
  private:
    std::vector<bool> visitado;
    GrafoValorado<int> g;

  public:
    Mapa(GrafoValorado<int> const& g) : g(g) { }

    bool validRoute(int o, int d, int k) {
      visitado = std::vector<bool>(g.V(), 0);
      dfs(o, d, k);
      return visitado[d];
    }

  private:
    void dfs(int v, int d, int k) {
      visitado[v] = true;

      for (auto w : g.ady(v))
        if (k <= w.valor())
          if (!visitado[w.otro(v)])
            dfs(w.otro(v), d, k);
    }
};

bool resuelveCaso() {
  GrafoValorado<int> grafo(std::cin, 1);

  if (!std::cin) return false;

  int k; std::cin >> k;
  Mapa mapa(grafo);

  for (int i = 0; i < k; i++) {
    int o, d, a; std::cin >> o >> d >> a;

    cout << (mapa.validRoute(o - 1, d - 1, a) ? "SI\n" : "NO\n");
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
