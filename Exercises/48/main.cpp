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

//@ <answer>

/*
Dos secuencias X e Y, dos índices i y j.

buscarSecuencia(i, j):
  busca el segmento máximo desde 0 hasta las posiciones i y j.
    X [0 ... i] ..]
    Y [0 ... j] ...]

Casos Base:
  buscarSubsecuencia(0, j) = 0. Si acaba la palabra con indice i.
  buscarSubsecuencia(i, 0) = 0. Si acaba la palabra con indice j.

Casos Recursivos
  Si las posiciones de la palabra son iguales:
    buscarSubsecuencia(i, j) = buscarSubsecuencia(i - 1, j - 1) + 1. 
  
  Si no buscamos el máximo entre usar la letra X[i] e Y[j]:
    buscarSubsecuencia(i, j) = max(buscarSubsecuencia(i, j - 1),
                                    buscarSubsencuencia(i - 1, j). 

Llamada inicial:
  buscarSubsecuencia(X, Y, i, j);

Coste en espacio y tiempo: O(X.length() * Y.length())
*/

int buscarSubsecuencia(string const& X, string const& Y, int i, int j, Matriz<int>& secuencias) {
  if (secuencias[i][j] != -1) return secuencias[i][j];
  
  if (i == 0 || j == 0) 
    secuencias[i][j] = 0;
  else if (X[i - 1] == Y[j - 1]) 
    secuencias[i][j] = buscarSubsecuencia(X, Y, i - 1, j - 1, secuencias) + 1;
  else secuencias[i][j] = max(buscarSubsecuencia(X, Y, i - 1, j, secuencias),
                              buscarSubsecuencia(X, Y, i, j - 1, secuencias));
  
  return secuencias[i][j];
}

string reconstruir(string const& X, string const& Y, Matriz<int> const& secuencias) {
  string subcadena = "";

  int i = X.length(), j = Y.length();
  int size = secuencias[X.length()][Y.length()];

  while (size) {
    if (X[i - 1] == Y[j - 1]) {
      subcadena += X[i - 1];
      i--;
      j--;
      size--;
    } else if (secuencias[i - 1][j] > secuencias[i][j - 1]) i--;
    else j--;
  }

  reverse(subcadena.begin(), subcadena.end());

  return subcadena;
}

bool resuelveCaso() {
  string X, Y;
  std::cin >> X >> Y;

  if (!std::cin) return false;

  Matriz<int> secuencias(X.length() + 1, Y.length() + 1, -1);
  buscarSubsecuencia(X, Y, X.length(), Y.length(), secuencias);

  if (secuencias[X.length()][Y.length()] > 0)
    std::cout << reconstruir(X, Y, secuencias);

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
  
  // Resolvemos
  while (resuelveCaso());
  
  // para dejar todo como estaba al principio
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  system("PAUSE");
#endif
  return 0;
}
