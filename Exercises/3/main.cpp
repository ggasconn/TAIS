
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

using namespace std;


/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */

int findSum(priority_queue<int, std::vector<int>, greater<int>>& myQueue) {
   int effort = 0;
   int n = 0;

   if (!myQueue.empty()) {
      n = myQueue.top();
      myQueue.pop();
   }

   while (!myQueue.empty()) {
      effort += n + myQueue.top();
      n += myQueue.top();
      myQueue.pop();
   }

   return effort;
}

bool resuelveCaso() {
   int n;

   std::cin >> n;

   if (n == 0) return false;

   priority_queue<int, std::vector<int>, greater<int>> myQueue;

   for (int i = 0; i < n; i++) {
      int t; std::cin >> t;
      myQueue.push(t);
   }

   std::cout << findSum(myQueue) << "\n";

   /* while(!myQueue.empty()) {
      std::cout << myQueue.top() << "\n";
      myQueue.pop();
   } */
   
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
