
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


/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */

class Network {
   private:
      std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
      std::vector<int> dist; // visit[v] = ¿hay camino de s a v?
      int nNodes;
      Grafo G;

   public:
      Network(Grafo const& g) : G(g) { }

      int reachableNodes(int s, int ttl) {
         visit = std::vector<bool>(G.V(), 0);
         dist = std::vector<int>(G.V(), 0);
         nNodes = 1;

         std::queue<int> q;
         dist[s] = 0;
         visit[s] = true;
         q.push(s);

         while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : G.ady(v)) {
               if (!visit[w]) {
                  dist[w] = dist[v] + 1; visit[w] = true;
                  if (dist[w] <= ttl) nNodes++;
                  q.push(w);
               }
            }
         }

         return G.V() - nNodes;
      }
};

bool resuelveCaso() {
   Grafo grafo(std::cin, 1);

   if (!std::cin) return false;

   Network network(grafo);

   int q; std::cin >> q;
   for (int i = 0; i < q; i++) {
      int s, ttl; std::cin >> s >> ttl;
      std::cout << network.reachableNodes(s - 1, ttl) << "\n";
   }

   std::cout << "---\n";

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
