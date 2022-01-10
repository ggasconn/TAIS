
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Disponemos un vector cubos.

 Casos base:
  cubos(i, j): cubos[i], si i == j
  cubos(i, j): 0, si i > j

 Casos recursivos:
  Busco si es mejor comer el del extremo derecho o el del izquierdo y quito los cubos de Devoradora

  cubos(i, j): max(
    cubos(i + 2, j) + cubos[i] si i + 1 > j, Devoradora cogerá i + 1 porque es mayor que j y lo necesitamos descartar
    cubos(i + 1, j - 1) + cubos[i] en otro caso

    cubos(i, j - 2) + cubos[j] si j - 1 > i, Devoradora cogerá j - 1 porque es mayor que i
    cubos(i + 1, j - 1) + cubos[j]
  )
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int maximizarCantidad(int i, int j, std::vector<int> const& cubos, Matriz<int> &matriz) {
  if (matriz[i][j] != -1) return matriz[i][j];

  if (i == j)
    matriz[i][j] =  cubos[i];
  else if (i > j)
    matriz[i][j] =  0;
  else {
    // Calculo el índice para quitar el próximo cubo que comerá Devoradora
    int iL = i + 1, jL = j - 1;
    if (cubos[i + 1] > cubos[j]) {
      iL = i + 2; jL = j;
    }

    // Calculo el índice para quitar el próximo cubo que comerá Devoradora
    int iR = i + 1, jR = j - 1;
    if (cubos[j - 1] > cubos[i]) {
       iR = i; jR = j - 2;
    }

    matriz[i][j] = max(maximizarCantidad(iL, jL, cubos, matriz) + cubos[i],
                        maximizarCantidad(iR, jR, cubos, matriz) + cubos[j]);
  }

  return matriz[i][j];
}

bool resuelveCaso() {
  int n; std::cin >> n;

  if (n == 0) return false;

  std::vector<int> cubos(n);

  for (int &c : cubos) std::cin >> c;

  Matriz<int> matriz(n, n , -1);
  maximizarCantidad(0, n - 1, cubos, matriz);

  std::cout << matriz[0][n - 1] << "\n";

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
