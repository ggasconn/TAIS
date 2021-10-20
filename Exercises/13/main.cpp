
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
