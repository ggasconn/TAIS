
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
#include <unordered_map>

#include "Digrafo.h"

using namespace std;


/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */
using Camino = std::deque<int>;

class CicloDirigido {
   private:

      std::vector<int> anterior;
      std::vector<bool> visitado;
      std::vector<bool> apilado;
      Camino _camino;

      bool _hayCiclo;
   
   public:
      CicloDirigido(Digrafo const& g) : anterior(g.V(), 0), visitado(g.V(), false), 
                                             apilado(g.V(), false), _hayCiclo(false) {
         for (int v = 0; v < g.V(); v++)
            if (!visitado[v])
               dfs(g, v);
      }

      bool hayCiclo() const { return _hayCiclo; }
      Camino const& camino() { return _camino; }
   
   private:
      void dfs(Digrafo const& g, int v) {
         apilado[v] = true;
         visitado[v] = true;

         for (int i : g.ady(v)) {
            if (_hayCiclo) return;

            if (!visitado[i]) {
               dfs(g, i);
               anterior[i] = v;
            }else if (apilado[i])
               _hayCiclo = true;
         }

         _camino.push_front(v);
         apilado[v] = false;
      }
};

bool resuelveCaso() {
   Digrafo grafo(std::cin, 1);
   if (!std::cin) return false;

   CicloDirigido ciclo(grafo);

   if (!ciclo.hayCiclo()) {
      for (int i : ciclo.camino())
         std::cout << i + 1 << " ";
   } else
      std::cout << "Imposible";

   std::cout << "\n"; 

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
