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

  La solución es un control de flujo de un programa, donde debemos comprobar
  si hay ciclos y si termina la ejecución a pesar de haber ciclos.

  El programa se representa mediante un grafo dirigido donde los vertices son las instrucciones
  y las aristas apuntan a las instrucciones donde salta cada línea.

  El programa hace una búsqueda en profundidad intentando llegar al nodo más profundo, empezando
  en el vértice de origen, y durante esa búsqueda también va comprobando si hay algún ciclo.

  En el caso de existir un ciclo y no haber llegado al último vértice, el programa tiene un bucle
  infinito. Por el contrario, si existe un ciclo pero se llega al último vértice es que algunas
  veces puede darse la situación de que el programa termine. Y si no existe ningún ciclo y además
  el programa termina la ejecución, entonces siempre termina.

  El coste siendo n, el número de vértices y m el número de aristas sería de O(n + m). Puesto que
  se recorren todos los vértices 1 sola vez y se pasa por todas sus aristas en el recorrido de
  adyancentes.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class ProgramaTermina {
  private:
    std::vector<int> visitado;
    std::vector<int> apilado;
    bool hayCiclo;

  public:
    ProgramaTermina(Digrafo const& g) : visitado(g.V()), apilado(g.V()), hayCiclo(false) {
      dfs(g, 0);
    }

    void imprimirSolucion() {
      if (hayCiclo && visitado[visitado.size() - 1])
        cout << "A VECES\n";
      else if (hayCiclo && !visitado[visitado.size() - 1])
        cout << "NUNCA\n";
      else if (!hayCiclo && visitado[visitado.size() - 1])
        cout << "SIEMPRE\n";
    }
  
  private:
    void dfs(Digrafo const& g, int v) {
          apilado[v] = true;
          visitado[v] = true;

          for (int i : g.ady(v)) {
              if (!visitado[i])
                dfs(g, i);
              else if (apilado[i])
                hayCiclo = true;
          }

          apilado[v] = false;
    }
};


bool resuelveCaso() {
  // leemos la entrada
  int L;
  cin >> L;
  if (!cin)
    return false;
  
  // leer el resto del caso y resolverlo
  Digrafo grafo(L + 1);

  for (int i = 0; i < L; i++) {
    char I; std::cin >> I;
    
    switch(I) {
      case 'A':
          grafo.ponArista(i, i + 1);
        break;
      
      case 'J':
      case 'C':
        int n; std::cin >> n;
        grafo.ponArista(i, n - 1);

        if (I == 'C')
          grafo.ponArista(i, i + 1);
        break;
    }
  }

  ProgramaTermina programaTermina(grafo);

  programaTermina.imprimirSolucion();

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
