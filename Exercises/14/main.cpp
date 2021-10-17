/*@ <answer>
 *
 * Nombre y Apellidos: Guillermo Gascón Celdrán
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>
#include <vector>

#include "Grafo.h"

using namespace std;

class SocialNet {
   using Camino = std::stack<int>;

   private:
      std::vector<bool> visitado;
      std::vector<int> amigos;
      Camino camino;
   
   public:
      SocialNet(Grafo const& g) : visitado(g.V(), 0), amigos(g.V(), 0) {
         int sol;

         for (int v = 0; v < g.V(); v++) {
            if (!visitado[v]) {
               sol = dfs(g, v);
               camino.push(v);

               while (!camino.empty()) {
                  amigos[camino.top()] = sol;
                  camino.pop();
               }
            }
         }
      }

      int getFriends(int v) { return amigos[v]; }
   
   private:
      int dfs(Grafo const& g, int v) {
         visitado[v] = true;
         int maxDepth = 1;

         for (int w : g.ady(v)) {
            if (!visitado[w]) {
               maxDepth += dfs(g, w);
               camino.push(w);
            }
         }

         return maxDepth;
      }
};

bool resuelveCaso() {
   int u, g; std::cin >> u >> g;

   if (!std::cin) return false;

   Grafo grafo(u);

   for (int i = 0; i < g; i++) {
      int n; std::cin >> n;

      if (n != 0) {
         int v, w; std::cin >> v;

         for (int j = 0; j < n - 1; j++) {
            std::cin >> w;
            grafo.ponArista(v - 1, w - 1);
         }
      }
   }

   SocialNet socialNet(grafo);

   for (int i = 0; i < grafo.V(); i++)
      cout << socialNet.getFriends(i) << " ";
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
   
   while(resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
