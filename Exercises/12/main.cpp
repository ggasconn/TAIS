
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

class MaximaConexa {
   private:
      int _maxima;
      std::vector<int> visitado;

   public:
      MaximaConexa(Grafo const& g) : _maxima(0), visitado(g.V(), false) {
         // Se recorren todos los vertices por si hay más de una componente conexa
         for (int i = 0; i < g.V(); i++)
            if (!visitado[i])
               _maxima = std::max(_maxima, dfs(g, i));
      };
   
   int maxima() const { return _maxima; }

   private:
      int dfs(Grafo const& g, int v) {
         visitado[v] = true;
         
         int t = 1;

         for (int w : g.ady(v))
            if (!visitado[w])
               t += dfs(g, w);

         return t;
      }
};

bool resuelveCaso() {
   Grafo grafo(std::cin, 1);

   if (!std::cin) return false;

   MaximaConexa maximaConexa(grafo);

   cout << maximaConexa.maxima() << "\n";

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
   
   int n; std::cin >> n;
   for (int i = 0; i < n; i++) resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
