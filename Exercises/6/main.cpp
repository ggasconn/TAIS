
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

struct task {
   int ini;
   int fin;
   int scheduleTime;
};

bool operator<(task const& a, task const& b) {
   return b.ini < a.ini;
}

bool resuelveCaso() {
   int t, p, n;

   std::cin >> t >> p >> n;

   if (!std::cin) return false;
   
   priority_queue<task> planner;

   for (int i = 0; i < t; i++) {
      int ini, fin;
      std::cin >> ini >> fin;

      planner.push({ini, fin, 0});
   }

   for (int i = 0; i < p; i++) {
      int ini, fin, scheduleTime;
      std::cin >> ini >> fin >> scheduleTime;

      planner.push({ini, fin, scheduleTime});
   }

   int time = 0; bool isPlanned = true;
   while (time < n && isPlanned && !planner.empty()) {
      task tempTask = planner.top();
      planner.pop();

      if (tempTask.ini >= time) {
         time = tempTask.fin;
         
         if (tempTask.scheduleTime > 0) {
            tempTask.ini += tempTask.scheduleTime;
            tempTask.fin += tempTask.scheduleTime;
            planner.push(tempTask);
         }

      }else
         isPlanned = false;
   }

   std::cout << (isPlanned ? "NO\n" : "SI\n");

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
