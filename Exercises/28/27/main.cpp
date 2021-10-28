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
#include <limits>

using namespace std;

#include "DigrafoValorado.h"
#include "IndexPQ.h"

//@ <answer>

template <typename T>
class Dijkstra {
  #define INF 2147483647 // max(int)

  private:
    std::vector<T> distance;
    std::vector<int> paths;
    IndexPQ<T> pq;
    
  public:
    Dijkstra(DigrafoValorado<int> const& g) : distance(g.V(), INF), pq(g.V()), paths(g.V(), 0) {
      distance[0] = 0;
      paths[0] = 1; // Camino vacío
      pq.push(0, 0);

      while (!pq.empty()) {
        int v = pq.top().elem; pq.pop();

        for (auto a : g.ady(v))
          relajar(a);
      }
    }

    bool hayCamino(int v) const { return distance[v - 1] != INF; }
    int distanceTo(int v) const { return distance[v - 1]; }
    int differentPaths(int v) const { return paths[v - 1]; }
  
  private:
    void relajar(AristaDirigida<T> a) {
      int from = a.desde(), to = a.hasta();

      if (distance[to] > distance[from] + a.valor()) {
        distance[to] = distance[from] + a.valor();
        paths[to] = paths[from];
        pq.update(to, distance[to]);
      } else if (distance[to] ==  distance[from] + a.valor())
        paths[to] += paths[from];
    }
};

bool resuelveCaso() {
  int n, a; std::cin >> n >> a;
  if (!std::cin) return false;

  DigrafoValorado<int> grafo(n);
  for (int i = 0; i < a; i++) {
    int v, w, k; std::cin >> v >> w >> k;
    grafo.ponArista({ v - 1, w - 1, k });
    grafo.ponArista({ w - 1, v - 1, k });
  }

  Dijkstra<int> dijkstra(grafo);

  cout << (dijkstra.hayCamino(grafo.V()) ? dijkstra.differentPaths(grafo.V()) : 0) << "\n";

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
