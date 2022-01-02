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

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class Isle {
  private:
    int visitedNodes;
    int coste;
    bool isConexo;
  
  public:
    Isle(GrafoValorado<int> const& g) : coste(0), visitedNodes(0), isConexo(false) {
      PriorityQueue<Arista<int>> pq(g.aristas());
      ConjuntosDisjuntos cjtos(g.V());
    
      while (!pq.empty()) {
        auto a = pq.top(); pq.pop();
        int v = a.uno(), w = a.otro(v);
      
        if (!cjtos.unidos(v,w)) {
          cjtos.unir(v, w);
          visitedNodes++; coste += a.valor();
          if (visitedNodes == g.V() - 1) break;
        }
      }

      if (visitedNodes == g.V() - 1) isConexo = true;;
    }

    int cost() const {
      return isConexo ? coste : -1;
    }
};

bool resuelveCaso() {
  GrafoValorado<int> grafo(std::cin, 1);

  if (!std::cin) return false;

  Isle isle(grafo);

  int cost = isle.cost();
  if (cost == -1) std::cout << "No hay puentes suficientes\n";
  else std::cout << cost << "\n";

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
