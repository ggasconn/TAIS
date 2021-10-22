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
    IndexPQ<T> pq;
    
  public:
    Dijkstra(DigrafoValorado<int> const& g) : distance(g.V(), INF), pq(g.V()) {
      distance[0] = 0;
      pq.push(0, 0);

      while (!pq.empty()) {
        int v = pq.top().elem; pq.pop();

        for (auto a : g.ady(v))
          relajar(a);
      }
    }

    bool hayCamino(int v) const { return distance[v - 1] != INF; }
    int distanceTo(int v) const { return distance[v - 1]; }
  
  private:
    void relajar(AristaDirigida<T> a) {
      int from = a.desde(), to = a.hasta();

      if (distance[to] > distance[from] + a.valor()) {
        distance[to] = distance[from] + a.valor();
        pq.update(to, distance[to]);
      }
    }
};

bool resuelveCaso() {
  int n; std::cin >> n;

  if (n == 0) return false;

  std::vector<int> loadingTime(n);
  for (int &i : loadingTime) 
    std::cin >> i;

  DigrafoValorado<int> grafo(n);

  int a; std::cin >> a;

  for (int i = 0; i < a; i++) {
    int v, w, k; std::cin >> v >> w >> k;
    
    k += loadingTime[w - 1];
    if (v == 1) k += loadingTime[0];

    grafo.ponArista({ v - 1, w - 1, k });
  }

  Dijkstra<int> dijkstra(grafo);

  if (dijkstra.hayCamino(n))
    cout << dijkstra.distanceTo(n) << "\n";
  else
    cout << "IMPOSIBLE\n";

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
