
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

#define lli long long int

bool resuelveCaso() {
   int n;

   std::cin >> n;

   if (n == 0) return false;

   std::priority_queue<lli, std::vector<lli>, std::greater<lli>> sumandos;

   int temp;
   for (int i = 0; i < n; i++) {
      std::cin >> temp; sumandos.push(temp);
   }

   lli suma = 0;
   lli s1, s2;
   while (sumandos.size() > 1) {
      s1 = sumandos.top(); sumandos.pop();
      s2 = sumandos.top(); sumandos.pop();

      suma += (s1 + s2);

      sumandos.push(s1 + s2);
   }

   std::cout << suma << "\n";
   
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
