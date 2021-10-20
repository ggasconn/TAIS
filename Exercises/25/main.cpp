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
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"

//@ <answer>

template <typename Valor>
class ARM_Kruskal {
  private:
    std::vector<Arista<int> > arm;
    int _coste;
    int _nArboles;
    int _nAeropuertos;
  
  public:
    ARM_Kruskal(GrafoValorado<Valor> const& g, int costeAeropuerto) : _coste(0), _nArboles(g.V()), _nAeropuertos(0) {
      PriorityQueue<Arista<Valor>> pq(g.aristas());
      ConjuntosDisjuntos cjtos(g.V());
    
      while (!pq.empty()) {
        auto a = pq.top(); pq.pop();
        int v = a.uno(), w = a.otro(v);
        
        if (a.valor() >= costeAeropuerto) {
          _nAeropuertos += 2;
          _coste += costeAeropuerto * 2;
          arm.push_back(a);
          if (arm.size() == g.V() - 1) break;
        }else if (!cjtos.unidos(v,w)) {
          cjtos.unir(v, w);
          arm.push_back(a);
          _coste += a.valor();
          _nArboles = cjtos.num_cjtos();
          if (arm.size() == g.V() - 1) break;
        }
      }

      _coste += (_nArboles - _nAeropuertos) * costeAeropuerto;
      _nAeropuertos += _nArboles - _nAeropuertos;
    }

    int coste() const { return _coste; }
    int nArboles() const { return _nArboles; }
};


bool resuelveCaso() {
  int n, m, a; std::cin >> n >> m >> a;

  if (!std::cin) return false;

  GrafoValorado<int> grafo(n);

  for (int i = 0; i < m; i++) {
      int v, w, k; std::cin >> v >> w >> k;
      grafo.ponArista({v - 1, w - 1, k});
  }

  ARM_Kruskal<int> arm(grafo, a);

  std::cout << arm.coste() << " " << arm.nArboles() << "\n";

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
