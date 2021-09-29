/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

/*@ <answer>
 *
 * Nombre y Apellidos: Guillermo Gascon Celdran - TAIS34
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include <queue>  // propios o los de las estructuras de datos de clase

/*@ <answer>

 La solución se calcula en base al número de músicos que tocan cada instrumento
 y el número de atriles que se pueden comprar. Por definición, todos los 
 instrumentos tienen un atril asignado por lo que empezamos a distrubuir atriles
 contando con que tenemos (ATRILES - N_INSTRUMENTOS) atriles.

 Para distribuirlos, ordenamos a los instrumentos en una cola con prioridad según 
 el número de personas que hay en cada atril. Así, si hay dos instrumentos con
 8 y 4 personas por atril respectivamente, el grupo de 8 personas será el que
 reciba el próximo atril que se compre. Una vez se le ha asignado un atril extra
 a un grupo, se vuelve a calcular el número de personas que hay por atril y se
 vuelve a meter a la cola para seguir repartiendo atriles, es posible que si el
 grupo que acabamos de reintroducir sigue siendo muy numeroso vuelva a recibir 
 un atril en la siguiente entrega.

 En el caso de que un grupo tenga un número de personas y de atriles de tal manera
 que no se puedan repartir equitativamente, habrá hasta (ATRILES - 1) atril dentro de ese
 instrumento que estarán más concurridos y será el que se tenga en cuenta para 
 saber las personas por atril de dicho instrumento. Por ejemplo, 14 violinistas y
 3 atriles, se repatirán en dos grupos de 5 y uno de 4, por lo que el número de
 personas por atril es de 5.


 Coste detallado:

 ATRILES = P     INSTRUMENTOS = N

 El coste de hacer push a una cola de prioridad es de O(logn). Se realizan P push() 
 a la cola, ya que al principio se meten todos los instrumentos y luego se van metiendo 
 conforme se van sacando. El coste de pop() es también de O(logn) y se realizan
 P - N pop(), ya que cuando sobran atriles se van repartiendo y para ello se saca de la cola
 al más numeroso.

 Por lo que el coste es de O(P logn + P-N logn), donde P son los atriles y N los instrumentos. 

 @ </answer> */

// =======================================================================
// Escribe el código completo de tu solución aquí debajo, tras la etiqueta
// =======================================================================
//@ <answer>

struct instrumento {
  int musicos;
  int atriles;
  int musicosAtril;
};


bool operator<(instrumento const& a, instrumento const& b) {
  return a.musicosAtril < b.musicosAtril || a.musicosAtril == b.musicosAtril;
}

bool resuelveCaso() {
  
  // leemos la entrada
  int P, N; // P partituras, N instrumentos
  cin >> P >> N;
  if (!cin) return false;
  
  // leer el resto del caso y resolverlo
  priority_queue<instrumento> orquesta;

  for (int i = 0; i < N; i++) {
    int temp; std::cin >> temp;
    orquesta.push({ temp, 1, temp }); // Se garantiza que todos al menos tienen 1 atril
  }

  P -= N; // Como se garantiza que todos tienen un atril, empiezo con N atriles menos
  
  while (P) {
    instrumento temp = orquesta.top();
    orquesta.pop();

    temp.atriles++;

    temp.musicosAtril = temp.musicos / temp.atriles;

    /* Los musicos saben distribuirse bien, pero si al repartirse sobra gente habrá un grupo con más */
    if (temp.musicos % temp.atriles > 0) temp.musicosAtril++;

    P--;

    orquesta.push(temp);
  }

  std::cout << orquesta.top().musicosAtril << "\n";
  
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
