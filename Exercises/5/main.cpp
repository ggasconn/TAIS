
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

struct patient {
   string name;
   int priority;
   int arrivalTime;
};

bool operator<(patient const& p1, patient const& p2) {
   return p1.priority < p2.priority || 
         (p1.priority == p2.priority && p1.arrivalTime > p2.arrivalTime);
}

bool resuelveCaso() {
   int n;

   std::cin >> n;

   if (n == 0) return false;

   char c;
   priority_queue<patient> patientQueue;

   for (int i = 0; i < n; i++) {
      std::cin >> c;
   
      if (c == 'I') {
         patient newPatient;
         std::cin >> newPatient.name >> newPatient.priority;
         newPatient.arrivalTime = i;

         patientQueue.push(newPatient);
      }else if (c == 'A') {
         std::cout << patientQueue.top().name << "\n";
         patientQueue.pop();
      }
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
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
