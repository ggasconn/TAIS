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
#include <vector>
#include <queue>

using namespace std;

#include "Digrafo.h"

/*@ <answer>

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class Sumidero {
  private:
    std::vector<int> visit;
    std::vector<int> gradeIn;
    int node;

  public:
    Sumidero(Digrafo const& g) : visit(g.V(), 0), gradeIn(g.V(), 0), node(-1) {
      for (int i = 0; i < g.V(); i++)
        for (int w : g.ady(i))
          gradeIn[w]++;
      
      for (int i = 0; i < g.V(); i++) {
        if (g.ady(i).size() == 0 && gradeIn[i] == g.V() - 1) {
          node = i; break;
        }
      }
    }

    int nodoSumidero() {
      return node;
    }
};

bool resuelveCaso() {
  Digrafo grafo(std::cin);

  if (!std::cin) return false;

  Sumidero sumidero(grafo);

  int nodoSumidero = sumidero.nodoSumidero();

  if (nodoSumidero == -1) std::cout << "NO\n";
  else std::cout << "SI " << nodoSumidero << "\n";

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
