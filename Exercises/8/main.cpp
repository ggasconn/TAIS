
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

class MiddleTopQueue {

   public:
      void push(int n) {
         if (firstHalf.empty())
            firstHalf.push(n);
         else 
            firstHalf.top() < n ? secondHalf.push(n) : firstHalf.push(n);

         equilibrateQueues();
      }

      void pop() {
         firstHalf.pop();
         equilibrateQueues();
      }

      int top() const {
         return firstHalf.top();
      }

      bool empty() const {
         return firstHalf.empty();
      }

   private:
      priority_queue<int> firstHalf; // minors and middle point
      priority_queue<int, std::vector<int>, greater<int>> secondHalf; // gratears than the middle point

      void equilibrateQueues() {
         if (secondHalf.size() > firstHalf.size()) {
            firstHalf.push(secondHalf.top());
            secondHalf.pop();
         }else if (firstHalf.size() > secondHalf.size() + 1) {
            secondHalf.push(firstHalf.top());
            firstHalf.pop();
         }
      }
};

bool resuelveCaso() {
   int n; std::cin >> n;
   
   if (!std::cin) return false;

   int t;
   MiddleTopQueue myQueue;

   for (int i = 0; i < n; i++) {
      std::cin >> t;

      if (t == 0) {
         if (myQueue.empty()) std::cout << "ECSA ";
         else {
            std::cout << myQueue.top() << " ";
            myQueue.pop();
         }
      }else {
         myQueue.push(t);
      }
         
   }

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
