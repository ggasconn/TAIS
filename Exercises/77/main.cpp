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

#include "DigrafoValorado.h"
#include "IndexPQ.h"

/*@ <answer>

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class Comarca {
  private:
    const int INF = std::numeric_limits<int>::max();

    std::vector<int> dist;
    IndexPQ<int> pq;

    std::vector<int> distInv;
    IndexPQ<int> pqInv;
  
  public:
    Comarca(DigrafoValorado<int> const& g, int s) : dist(g.V(), INF), pq(g.V()), distInv(g.V(), INF), pqInv(g.V()) {
      dist[s] = 0;
      pq.push(s, 0);
      
      while (!pq.empty()) {
        int v = pq.top().elem; pq.pop();
        
        for (auto a : g.ady(v))
          relajar(a);
      }

      DigrafoValorado<int> gInv = g.inverso();
      distInv[s] = 0;
      pqInv.push(s, 0);
      
      while (!pqInv.empty()) {
        int v = pqInv.top().elem; pqInv.pop();
        
        for (auto a : gInv.ady(v))
          relajarInverso(a);
      }
    }

    bool hayCamino(int s) { return dist[s] != INF && distInv[s] != INF; }
    int coste(int s) { return dist[s] + distInv[s]; }

  private:
    void relajar(AristaDirigida<int> a) {
      int v = a.desde(), w = a.hasta();
    
      if (dist[w] > dist[v] + a.valor()) {
        dist[w] = dist[v] + a.valor();
        pq.update(w, dist[w]);
      }
    }

    void relajarInverso(AristaDirigida<int> a) {
      int v = a.desde(), w = a.hasta();
    
      if (distInv[w] > distInv[v] + a.valor()) {
        distInv[w] = distInv[v] + a.valor();
        pqInv.update(w, distInv[w]);
      }
    }

};

bool resuelveCaso() {
  DigrafoValorado<int> grafo(std::cin, 1);

  if (!std::cin) return false;

  int s; std::cin >> s;
  Comarca comarcaOrigen(grafo, s - 1);

  int costeTotal = 0;
  bool imposible = false;

  int n; std::cin >> n;
  std::vector<int> paquetes(n);
  for (int &p : paquetes) std::cin >> p;

  for (int p : paquetes) {
    if (comarcaOrigen.hayCamino(p - 1)) {
      costeTotal += comarcaOrigen.coste(p - 1);
    }else {
      imposible = true;
      break;
    }
  }

  if (imposible) std::cout << "Imposible\n";
  else std::cout << costeTotal << "\n";
  
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
