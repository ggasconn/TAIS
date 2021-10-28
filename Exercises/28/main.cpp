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
class City {
  #define INF std::numeric_limits<int>::max()

  private:
    std::vector<int> distance;
    std::vector<int> distanceDijkstra;
    std::vector<int> distanceUsed;
    std::vector<int> visit;
    std::vector<AristaDirigida<T>> last;

    IndexPQ<int> pq;
  
  public:
    City(DigrafoValorado<int> const& g) : distance(g.V(), 0), visit(g.V(), false), distanceDijkstra(g.V(), INF), last(g.V()), pq(g.V()), distanceUsed(g.V(), 0) {
      bfs(g);
      dijkstra(g);
    }

    bool hayCamino(int v) { return distanceDijkstra[v] != INF; }
    int valorMinimo(int v) { return distanceDijkstra[v]; }
    bool caminosMinimizados(int v) { return distance[v] == distanceUsed[v]; }

  private:
    void bfs(DigrafoValorado<int> const& g) {
      std::queue<int> q;
      distance[0] = 0;
      visit[0] = true;
      q.push(0);

      while (!q.empty()) {
        int v = q.front(); q.pop();
        for (auto w : g.ady(v)) {
          int other = w.hasta();
          if (!visit[other]) {
            distance[other] = distance[v] + 1;
            visit[other] = true;
            q.push(other);
          }
        }
      }
    }

    void dijkstra(DigrafoValorado<int> const& g) {
      distanceDijkstra[0] = 0;
      pq.push(0, 0);
      while (!pq.empty()) {
        int v = pq.top().elem; pq.pop();
        
        for (auto a : g.ady(v))
          relajar(a);
      }
    }

    void relajar(AristaDirigida<T> a) {
      int v = a.desde(), w = a.hasta();
    
      if (distanceDijkstra[w] > distanceDijkstra[v] + a.valor()) {
        distanceUsed[w] = distanceUsed[v] + 1;
        distanceDijkstra[w] = distanceDijkstra[v] + a.valor();
        last[w] = a;
        pq.update(w, distanceDijkstra[w]);
      }
    }
};

bool resuelveCaso() {
  int n, m; std::cin >> n >> m;
  
  if (!std::cin) return false;

  DigrafoValorado<int> grafo(n);

  for (int i = 0; i < m; i++) {
    int v, w, k; std::cin >> v >> w >> k;
    grafo.ponArista({ v - 1, w - 1, k });
    grafo.ponArista({ w - 1, v - 1, k });
  }

  City<int> city(grafo);

  int k; std::cin >> k;
  for (int i = 0; i < k; i++) {
    int v, w; std::cin >> v >> w;

    if (city.hayCamino(w)) {
      //cout << city.distanciaMinima(v)
    } else cout << "IMPOSIBLE\n";
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
