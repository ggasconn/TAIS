
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

  Caso Base:
    pagarCoche(i, j): 0, si j == 0 Ya se ha pagado todo
    pagarCoche(i, j): INF, si i == 0 No quedan monedas y no se puede pagar la cantidad

  Caso recursivo:
    pagarCoche(i, j): pagarCoche(i - 1, j), si i.valor > j || usadas >= i.cantidad
    pagarCoche(i, j): min(pagarCoche(i - 1, j), pagarCoche(i, j - i.valor)), Busco la mejor opcion

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

#define INF 100000000

struct moneda {
  int valor;
  int cantidad;
};

bool operator<(moneda const &a, moneda const &b) { return a.valor < b.valor; }

int pagarCoche(int i, int j, int usadas, std::vector<moneda> const& monedas, Matriz<int> &matriz) {
  if (matriz[i][j] != -1) return matriz[i][j];

  if (j == 0) return 0;
  if (i == 0) return INF;
  
  if (monedas[i - 1].valor > j || monedas[i - 1].cantidad <= usadas)
    matriz[i][j] = pagarCoche(i - 1, j, 0, monedas, matriz);
  else {
    int usadasTemp = usadas;
    matriz[i][j] = min(
        pagarCoche(i - 1, j, usadasTemp, monedas, matriz),
        pagarCoche(i, j - monedas[i - 1].valor, ++usadas, monedas, matriz) + 1);
  }

  return matriz[i][j];
}

bool resuelveCaso() {
  int n; std::cin >> n;

  if (!std::cin)
   return false;

  std::vector<moneda> monedas(n);
  for (moneda &m : monedas) std::cin >> m.valor;
  for (moneda &m : monedas) std::cin >> m.cantidad;

  int p; std::cin >> p;

  std::sort(monedas.begin(), monedas.end());

  Matriz<int> matriz(n + 1, p + 1, -1);

  pagarCoche(n, p, 0, monedas, matriz);

  if (matriz[n][p] == INF) std::cout << "NO\n";
  else std::cout << "SI " << matriz[n][p] << "\n";

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