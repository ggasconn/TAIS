
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

class ArbolLibre {
   private:
      bool _esLibre = true;
      int visitados;
      int s;
      std::vector<int> visitado;
      std::vector<int> anterior;

   public:
      ArbolLibre(Grafo const& g, int s) : visitado(g.V(), false), anterior(g.V(), 0), 
                                                   visitados(0), _esLibre(true), s(s) {
         dfs(g, s);
      };
   
   bool esLibre() const { return _esLibre && visitados == visitado.size(); }

   private:
      void dfs(Grafo const& g, int v) {
         visitado[v] = true;

         for (int w : g.ady(v)) {
            if (!visitado[w]) {
               anterior[w] = v;
               dfs(g, w);
            }else if (anterior[v] != w)
               _esLibre = false;
         }

         visitados++;
      }
};

bool resuelveCaso() {
   Grafo grafo(std::cin);

   if (!std::cin) return false;

   ArbolLibre arbolLibre(grafo, 0);

   cout << (arbolLibre.esLibre() ? "SI\n" : "NO\n");

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
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
