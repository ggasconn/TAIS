
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
  
 Casos base:
  formarPalindromo(i, j) = 0, i == j

 Casos recursivos:
  formarPalindromo(i, j) = formarPalindromo(i + 1, j - 1) si str[i] == str[j]
  formarPalindromo(i, j) = min(formarPalindromo(i + 1, j) + 1, formarPalindromo(i, j - 1) + 1)
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int formarPalindromo(string const& str, int i, int j, Matriz<int>& palabras) {
  int& c = palabras[i][j];

  if (c == -1) {
    if (i > j || i == j) c = 0;
    else if (str[i - 1] == str[j - 1]) c = formarPalindromo(str, i + 1, j - 1, palabras);
    else c = min(formarPalindromo(str, i + 1, j, palabras) + 1, formarPalindromo(str, i, j - 1, palabras) + 1);
  }

  return c;
}

bool resuelveCaso() {
  string str; std::cin >> str;

  if (!std::cin) return false;

  Matriz<int> palabras(str.length() + 1, str.length() + 1, -1);

  formarPalindromo(str, 1, str.length(), palabras);
  cout << palabras << "\n";

  cout << palabras[1][str.length()] << " ";

  int i = 1, j = str.length();
  std::vector<char> sol(str.length() + palabras[1][str.length()]);

  while (i < j) {
    if (str[i - 1] == str[j - 1]) {
      cout << str[i - 1] << " ";
      i++; j--;
    } else if (palabras[i][j - 1] < palabras[i][j]) {
      cout << str[j - 1] << " ";
      j--;
    }else {
      cout << str[i + 1] << " ";
      i++;
    }
  }

  cout << "\n";
  
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
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
