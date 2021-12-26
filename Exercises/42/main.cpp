/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

/*@ <answer>
 *
 * Nombre y Apellidos: Guillermo Gascón Celdrán TAIS34
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <string>

#include "Matriz.h"

using namespace std;

#define INF 1000000

//@ <answer>

/*
Mapa de tamaño N, M

Casos Base:

Casos Recursivos:

Llamada inicial:

*/

void floyd(Matriz<char> const& G, Matriz<char> & C, Matriz<int> & A) {
  int V = G.numfils(); // número de vértices de G
  
  // inicialización
  C = G;
  A = Matriz<int>(V, V, -1);
  
  for (int i = 0; i < V; ++i)
    for (int j = 0; j < V; ++j)
      if (i != j && G[i][j] != INF)
        A[i][j] = i;

  // actualizaciones de las matrices
  for (int k = 0; k < V; ++k) {
    for (int i = 0; i < V; ++i) {
      for (int j = 0; j < V; ++j) {
        auto temp = C[i][k] + C[k][j];
        
        if (temp < C[i][j]) { // es mejor pasar por k
          C[i][j] = temp;
          A[i][j] = A[k][j];
        }
      }
    }
  }
}

bool resuelveCaso() {
  int N, M; std::cin >> N >> M;

  if (!std::cin) return false;

  Matriz<char> mapa(N, M);
  
  char t;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++)
      std::cin >> mapa[i][j];


  Matriz<char> C;
  Matriz<int> A;
  floyd(mapa, C, A);

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
  
  // Resolvemos
  while (resuelveCaso());
  
  // para dejar todo como estaba al principio
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  system("PAUSE");
#endif
  return 0;
}
