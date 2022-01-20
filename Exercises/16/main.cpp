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

#define lli long long int

struct market {
   int node;
   int price;
   std::vector<bool> visit;
};


class Map {
   const lli INF = std::numeric_limits<lli>::max();
   private:
      std::vector<market> m;
      Grafo g;

   public:
      Map(Grafo const& grafo, std::vector<market> &markets) : g(grafo), m(markets) {
         for (market &i : m) {
            i.visit = std::vector<bool>(g.V(), 0);
            dfs(i, i.node);
         }
      }

      int findCheapest(int source) {
         for (market i : m)
            if (i.visit[source])
               return i.price;
         
         return -1;
      }

   private:
      void dfs(market &m, int  v) {
         m.visit[v] = true;

         for (int w : g.ady(v)) {
            if (!m.visit[w]) {
               dfs(m, w);
            }
         }
      }
};

bool operator<(market const& a, market const& b) {
   return a.price < b.price;
}

bool resuelveCaso() {
   Grafo grafo(std::cin, 1);

   if (!std::cin) return false;

   int n; std::cin >> n;
   std::vector<market> markets(n);

   for (market &m : markets) {
      std::cin >> m.node >> m.price;
      m.node--;
   }

   std::sort(markets.begin(), markets.end());

   Map map(grafo, markets);

   int q; std::cin >> q;
   for (int i = 0; i < q; i++) {
      int s; std::cin >> s;
      int price = map.findCheapest(s - 1);

      if (price != -1) std::cout << price;
      else std::cout << "MENUDO MARRON";

      std::cout << "\n";
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
