
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

bool resuelveCaso() {
   int d, a, b; std::cin >> d >> a >> b;
   
   if (!std::cin) return false;

   priority_queue<int> aBatteries;
   priority_queue<int> bBatteries;

   for (int i = 0; i < a; i++) {
      int temp; std::cin >> temp;
      aBatteries.push(temp);
   }

   for (int i = 0; i < b; i++) {
      int temp; std::cin >> temp;
      bBatteries.push(temp);
   }

   while (!aBatteries.empty() && !bBatteries.empty()) {
      int dTemp = d;
      int totalFlightTime = 0;

      std::vector<int> remainingA;
      std::vector<int> remainingB;

      while (dTemp && !aBatteries.empty() && !bBatteries.empty()) {
         int aBatt = aBatteries.top(); aBatteries.pop();
         int bBatt = bBatteries.top(); bBatteries.pop();

         int maxFlightTime = min(aBatt, bBatt);
         totalFlightTime += maxFlightTime;
         aBatt -= maxFlightTime;
         bBatt -= maxFlightTime;

         if (aBatt) remainingA.push_back(aBatt) ;
         if (bBatt) remainingB.push_back(bBatt) ;

         dTemp--;
      }

      for (int i : remainingA) aBatteries.push(i);
      for (int i : remainingB) bBatteries.push(i);

      std::cout << totalFlightTime << " ";
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
