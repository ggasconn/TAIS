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
using namespace std;


/*@ <answer>
 
  // Explicación de la estrategia //
  Trasladamos el problema a un problema de algoritmos voraces, donde
  se plantea la siguiente estrategia:
  Tenemos los pesos de los esquiadores ordenados de mayor a menor,
  para seleccionarlos de manera óptima cubriendo huecos de 2 cogemos
  al esquiador más pesado y al menos pesado e intentamos colocarlos.
  Si se han podido colocar los dos usan un telesilla doble, en caso
  de que se supere el peso máximo el esquiador más pesado ya no se va
  a poder emparejar con ninguno menos pesado puesto que el elegido
  era el menos pesado en ese momento y se coloca en un telesilla suelto.

  Si el número de esquiadores es impar y todos menos uno pueden ir en
  telesillas dobles, este último irá en uno solo
 
  // Demostración de que siempre encuentra soluciones óptimas //
  Las soluciones se dan en pares de esquiadores, donde para cada par
  su componente izquierda siempre es mayor que su componente deracha.
  Puede haber un par donde solo una componente tenga valor.
  Además, ordenamos a su vez las parejas de mayor a menor. Todos
  los pares suman como máximo el peso máximo.

  Suponemos que ambos algoritmos se comportan de igual forma hasta un
  cierto punto:
  
  alg X  (a1, b1) (a2, b2) | (ai, bi) ...
            =        =     |    !=
  opt Y  (c1, d1) (c2, d2) | (ci, di) ...

  Distinguimos varios casos:
    - Si ai ¬= ci, entonces como mi algoritmo elige el más grande
    ci < ai e intercambio ci por ai.
    - Si ai = ci, bi < di, como mi algoritmo elige el más pequeño
    di es intercambiable por bi. Intercambio di por bi.
    - El caso de ai = ci, bi > di, no se puede dar porque mi algoritmo
    elige el más pequeño en ese momento y habría codigo di.
  
  No pueden haber más parejas porque mi estrategia habría seguido
  formando parejas o como mínimo colocando a un esquiador solo.
    
 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>



bool resuelveCaso() {
  // leemos la entrada
  int peso_maximo, N;
  cin >> peso_maximo >> N;
  
  if (!cin) return false;

  vector<int> esquiadores(N);
  for (int & x : esquiadores)
      cin >> x;

  // resolver el caso
  std::sort(esquiadores.begin(), esquiadores.end(), greater<int>());
  
  int i = 0, j = esquiadores.size() - 1;
  int t = 0;

  while (i < j) {
    if (esquiadores[i] + esquiadores[j] > peso_maximo) {
      i++; t++;
    } else {
      i++; j--; t++;
    }
  }

  if (i == j) t++; // El numero de esquiadores era impar y todos podian subir dobles

  std::cout << t << "\n";
  
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
