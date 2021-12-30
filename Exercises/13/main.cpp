
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

#include "GrafoMatriz.h"

using namespace std;


/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */

class BlackStains {
   private:
      std::vector<int> visit;
      int maxCon;
      int nComp;

   public:
      BlackStains(Grafo const& g) : visit(g.V(), false), maxCon(0), nComp(0) {
         for (int i = 0; i < g.V(); i++) {
            if (!visit[i]) {
               int tam = dfs(g, i);
               maxCon = max(tam, maxCon);
               nComp++;
            }
         }
      }

      int getMaxCon() const { return maxCon; }
      int getNComp() const { return nComp; }
   
   private:
      int dfs(Grafo const& g, int v) {
         visit[v] = true;
         int tam = 1;
         
         for (int w : g.ady(v)) {
            if (!visit[w])
               tam += dfs(g, w);
         }

         return tam;
      }
};

bool resuelveCaso() {
   int n, m; std::cin >> n >> m;

   if (!std::cin) return false;

   Grafo grafo(n * m);

   for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
         char c; std::cin >> c;

         if (c == '#')
            grafo.ponArista(i, j);
      }
   }

   BlackStains stains(grafo);

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
