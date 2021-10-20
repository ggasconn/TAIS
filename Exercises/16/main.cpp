/*@ <answer>
 *
 * Nombre y Apellidos: Guillermo Gascón Celdrán
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>

#include "Grafo.h"

using namespace std;

class Mapa {
   private:
      std::vector<bool> visitado;
      std::vector<int> distancia;
      int s;

   public:
      Mapa(Grafo const& g, s) : visitado(g.V(), false), s(s) {
         bfs(g);
      }

   private:
      void bfs(Grafo const& g) {
         std::queue<int> q;

         distancia[s] = 0;
         visitado[s] = true;

         q.push(s);
         
         while (!q.empty()) {
            int v = q.front(); q.pop();
         
            for (int w : g.ady(v)) {
               if (!visitado[w]) {
                  distancia[w] = distancia[v] + 1;
                  visitado[w] = true;
                  q.push(w);
               }
            }
         }
      }
};


bool resuelveCaso() {
   Grafo grafo(std::cin);

   if (!std::cin) return false;

   int n; std::cin >> n;

   for (int i = 0; i < n; i++) {
      int node, ttl; std::cin >> node >> ttl;


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
   
   while(resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
