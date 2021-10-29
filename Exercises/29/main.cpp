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
#include <limits>

#include "DigrafoValorado.h"
#include "IndexPQ.h"

using namespace std;


/*@ <answer>

 El problema se puede trasladar a un problema de grafos, en concreto grafos
 dirigidos y valorados. Cada vértice del grafo representa una celda desde 
 la que sale un ratón y cada arista representa un pasadizo, el valor de la
 arista es lo que le cuesta a un ratón pasar por los obstáculos.

 Para resolverlo, como tenemos que llegar a todos los vértices con el menor
 camino y sin superar el tiempo, invertimos las aristas del grafo y empezamos
 a mirar desde la salida cuáles son los caminos mínimos que no superan el tiempo
 dado. Una vez se haya intentando llegar a todos los vértices, podemos mirar
 el resultado de este recorrido y veremos que los vértices que se han podido
 alcanzar no están a distancia infinita.

 El coste de la solución es O(A log V + V), siendo A el número de aristas del grafo
 y V el número de vértices. La suma de V al coste es debido a que hay que contar
 los vértices alcanzables, y esto se hace en tiempo lineal al número de vértices.
 
 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

template <typename Valor>
class Laberinto {
private:
	const Valor INF = std::numeric_limits<Valor>::max();
	int origen;
	int maxTime;
	std::vector<Valor> dist;
	IndexPQ<Valor> pq;

public:
	Laberinto(DigrafoValorado<Valor> const& g, int orig, int maxTime) : origen(orig), maxTime(maxTime),
		dist(g.V(), INF), pq(g.V()) {
		dist[origen] = 0;
		pq.push(origen, 0);
		
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}

	int cuantosAcaban() const {
		/* El raton que sale de la salida no cuenta y siempre será distinto de INF */
		int n = -1;
		
		for (int d : dist)
			if (d != INF) n++;

		return n;
	}

private:
	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor() && dist[v] + a.valor() <= maxTime) {
			dist[w] = dist[v] + a.valor();
			pq.update(w, dist[w]);
		}
	}
};

bool resuelveCaso() {
  
  // leemos la entrada
  int N, S, T, P;
  cin >> N >> S >> T >> P;
  
  if (!cin) return false;

  // leer el resto del caso y resolverlo
  DigrafoValorado<int> grafo(N);

  for (int i = 0; i < P; i++) {
	  int v, w, k; std::cin >> v >> w >> k;
	  grafo.ponArista({ w - 1, v - 1, k });
  }

  Laberinto<int> laberinto(grafo, S - 1, T);
  
  cout << laberinto.cuantosAcaban() << "\n";

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
