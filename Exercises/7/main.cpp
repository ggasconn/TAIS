
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
#include <stack>

using namespace std;


/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */

struct myStack {
   stack<int> s;
};

bool operator<(myStack const& a, myStack const& b) {
   return b.s.top() < a.s.top();
}


bool resuelveCaso() {
   int n; std::cin >> n;
   
   if (!std::cin) return false;

   priority_queue<myStack> line;

   for (int i = 0; i < n; i++) {
      int stackSize; std::cin >> stackSize;
      myStack s;

      for (int j = 0; j < stackSize; j++) {
         int tempN; std::cin >> tempN;
         s.s.push(tempN);
      }

      line.push(s);
   }

   pair<int, int> bestComic = { 0, 100000001 }; // pos, ID
   int queuePos = 1;

   while(!line.empty()) {
      myStack s = line.top();
      line.pop();

      if (s.s.top() < bestComic.second) bestComic = { queuePos, s.s.top() };

      queuePos++;

      s.s.pop();

      if (!s.s.empty()) line.push(s);
   }

   std::cout << bestComic.first << "\n";
   
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
