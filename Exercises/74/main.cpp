
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#include "Matriz.h" // propios o los de las estructuras de datos de clase

/*@ <answer>

  b: array con los trozos de bizcocho
  bizcocho(i, j): encuentra los mejores trozos a comer de i a j

  Caso Base:
  bizcocho(i, j): b[i] == b[j], si i + 1 == j. Solo quedan dos trozos por comer

  Caso Recursivo:
  bizcocho(i, j) = { bizcocho(i + 1, j - 1) + 1, si b[i] == b[j]
                     max(bizcocho(i + 2, j), bizcocho(i, j - 2), bizcocho(i + 1, j - 1) E.O.C.
  
 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int bizcocho(int i, int j, std::vector<int> const& trozos, Matriz<int> &matriz) {
  if (matriz[i][j] != -1) return matriz[i][j];

  if (i + 1 == j) 
    matriz[i][j] = 0; // Siempre es 0 porque nunca hay dos trozos juntos iguales
  else {
    if (trozos[i] == trozos[j] && trozos[i] != 0)
      matriz[i][j] = bizcocho(i + 1, j - 1, trozos, matriz) + 1;
    else
      /* 
        Como no pueden haber dos trozos seguidos iguales y son las únicas opciones que me quedan
        busco entre que trozos son mejor descartar
      */
      matriz[i][j] = max(bizcocho(i + 2, j, trozos, matriz), max(bizcocho(i, j - 2, trozos, matriz), bizcocho(i + 1, j - 1, trozos, matriz)));
  }

  return matriz[i][j];
}

bool resuelveCaso() {
  int n; std::cin >> n;

  if (!std::cin) return false;

  std::vector<int> trozos(n);
  for(int &t : trozos) std::cin >> t;

  Matriz<int> matriz(n, n, -1);

  bizcocho(0, n - 1, trozos, matriz);

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

  while (resuelveCaso())
    ;

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  system("PAUSE");
#endif
  return 0;
}