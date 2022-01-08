/*@ <answer>
 *
 * Nombre y Apellidos: Guillermo Gascón Celdrán TAIS34
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <istream>

using namespace std;

struct pelicula {
  int comienzo;
  int fin;
  int duracion;

  pelicula(int comienzo, int duracion) : comienzo(comienzo), duracion(duracion), fin (comienzo + duracion) { }
};

bool operator<(pelicula const& a, pelicula const& b) {
  return a.fin < b.fin;
}

//@ <answer>
bool resuelveCaso() {
  int n; std::cin >> n;

  if (n == 0) return false;

  std::vector<pelicula> peliculas;

  int h, m, d;
  char c;
  for (int i = 0; i < n; i++) {
    cin >> h >> c >> m >> d;
    h *= 60;
    peliculas.push_back({ h + m, d + 10 });
  }

  std::sort(peliculas.begin(), peliculas.end());

  int nPeliculas = 0;
  int time = 0;

  for (pelicula p : peliculas) {
    if (time <= p.comienzo) {
      nPeliculas++;
      time = p.fin;
    }
  }

  std::cout << nPeliculas << "\n";
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
