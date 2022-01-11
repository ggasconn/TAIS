
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

  i = presupuesto a gastar
  j = festivales disponibles

  Casos Base:
    elegirFestivales(i, j): 0 si i == 0 || j == 0
  
  Casos Recursivos:
    - Si no puedo pagar el festival lo descarto
    elegirFestivales(i, j): elegirFestivales(i, j - 1) si j.precio > i
    
    - Busco si es mejor ir al festival j o descartarlo
    elegirFesrtivales(i ,j): max(
        elegirFestivales(i - j.valor, j - 1) + j.grupos,
        elegirFestivale(i, j - 1))

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct festival {
  int grupos;
  int precio;
};

int elegirFestivales(int i, int j, std::vector<festival> const& festivales, Matriz<int> &matriz) {
  if (matriz[i][j] != -1) return matriz[i][j];

  if (i == 0 || j == 0) return 0;

  if (i < festivales[j - 1].precio) matriz[i][j] = elegirFestivales(i, j - 1, festivales, matriz);
  else matriz[i][j] = max(elegirFestivales(i - festivales[j - 1].precio, j - 1, festivales, matriz) + festivales[j - 1].grupos,
                            elegirFestivales(i, j - 1, festivales, matriz));
  
  return matriz[i][j];
}

bool resuelveCaso() {
  int P, N; std::cin >> P >> N;

  if (!std::cin) return false;

  std::vector<festival> festivales(N);

  for (festival &f : festivales)
    std::cin >> f.grupos >> f.precio;

  Matriz<int> matriz(P + 1, N + 1, -1);
  elegirFestivales(P, N, festivales, matriz);

  std::cout << matriz[P][N] << "\n";
  
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