
/*@ <answer>
 *
 * Nombre y Apellidos: Guillermo Gascón Celdrán
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;


/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El problema consta de dos partes:

 # Añadir el valor tam_i a cada nodo, simplemente cada vez que se añade
 un elemento por la izquierda de una raíz se incrementa en uno a dicha raiz. 
 En caso de que haya que reequilibrar el árbol y los nodos del subárbol
 izquierdo pasen el derecho se restan dichos nodos a la raíz y se suman
 en caso contrario. No contemplo la función de borrado.

 # Algoritmo para devolver la posición, se recorre el árbol decidiendo
 por que rama bajar según el número acumulado de nodos. En caso de que
 el número acumulado de nodos más los nodos de la raíz actual sea menor
 que la posición que busco, entonces bajo por la izquierda y viceversa 
 en el caso contrario. Si llego a un nodo nullptr es que no existe dicha
 posición y si llego a una raíz cuya suma de nodos acumulados + nodos 
 izquierdos es la posición, entonces lo he encontrado.

  * COSTE *
 En el peor caso tiene coste O(log N), ya que se va recorriendo el árbol
 por sus ramas pero nunca se explora entero, se va decidiendo si bajar por
 la derecha o por la izquierda.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

//
//  TreeSet_AVL.h
//
//  Implementación de conjuntos mediante árboles de búsqueda AVL
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020 Alberto Verdejo
//

#ifndef TREESET_AVL_H_
#define TREESET_AVL_H_

#include <algorithm>
#include <functional>
#include <stack>
#include <stdexcept>
#include <utility>


template <class T, class Comparator = std::less<T>>
class Set {
protected:
   
   /*
    Nodo que almacena internamente el elemento (de tipo T),
    punteros al hijo izquierdo y derecho, que pueden ser
    nullptr si el hijo es vacío, y la altura.
    */
   struct TreeNode;
   using Link = TreeNode *;
   struct TreeNode {
      T elem;
      Link iz, dr;
      int altura;
      int tam_i; // Nuevo valor en cada nodo con su tamaño + 1
      TreeNode(T const& e, Link i = nullptr, Link d = nullptr,
               int alt = 1, int t = 1) : elem(e), iz(i), dr(d), altura(alt), tam_i(t) {}
   };
   
   // puntero a la raíz de la estructura jerárquica de nodos
   Link raiz;
   
   // número de elementos (cardinal del conjunto)
   int nelems;
   
   // objeto función que compara elementos (orden total estricto)
   Comparator menor;
   
public:
   
   // constructor (conjunto vacío)
   Set(Comparator c = Comparator()) : raiz(nullptr), nelems(0), menor(c) {}
   
   // constructor por copia
   Set(Set const& other) {
      copia(other);
   }
   
   // operador de asignación
   Set & operator=(Set const& that) {
      if (this != &that) {
         libera(raiz);
         copia(that);
      }
      return *this;
   }
   
   ~Set() {
      libera(raiz);
   };
   
   bool insert(T const& e) {
      return inserta(e, raiz);
   }
   
   bool empty() const {
      return raiz == nullptr;
   }
   
   int size() const {
      return nelems;
   }
   
   bool contains(T const& e) const {
      return pertenece(e, raiz);
   }
      
   bool erase(T const& e) {
      return borra(e, raiz);
   }

   T const& kesimo(int k) const { return kesimoAux(k, 0, raiz); }
      
protected:
   
   void copia(Set const& other) {
      raiz = copia(other.raiz);
      nelems = other.nelems;
      menor = other.menor;
   }
   
   static Link copia(Link a) {
      if (a == nullptr) return nullptr;
      else return new TreeNode(a->elem, copia(a->iz), copia(a->dr), a->altura);
   }
   
   static void libera(Link a) {
      if (a != nullptr){
         libera(a->iz);
         libera(a->dr);
         delete a;
      }
   }
   
   bool pertenece(T const& e, Link a) const {
      if (a == nullptr) {
         return false;
      }
      else if (menor(e, a->elem)) {
         return pertenece(e, a->iz);
      }
      else if (menor(a->elem, e)) {
         return pertenece(e, a->dr);
      }
      else { // e == a->elem
         return true;
      }
   }
   
   bool inserta(T const& e, Link & a) {
      bool crece;
      if (a == nullptr) { // se inserta el nuevo elemento e
         a = new TreeNode(e);
         ++nelems;
         crece = true;
      } else if (menor(e, a->elem)) {
         crece = inserta(e, a->iz);
         if (crece) {
            ++a->tam_i;
            reequilibraDer(a);
         }
      } else if (menor(a->elem, e)) {
         crece = inserta(e, a->dr);
         if (crece) reequilibraIzq(a);
      } else // el elemento e ya está en el árbol
         crece = false;
      return crece;
   }
      
   int altura(Link a) {
      if (a == nullptr) return 0;
      else return a->altura;
   }
   
   void rotaDer(Link & r2) {
      Link r1 = r2->iz;
      r2->iz = r1->dr;
      r1->dr = r2;
      r2->altura = std::max(altura(r2->iz), altura(r2->dr)) + 1;
      r1->altura = std::max(altura(r1->iz), altura(r1->dr)) + 1;
      r2->tam_i -= r1->tam_i; // Quitar a r2 el valor de tam_i para el nodo B
      r2 = r1;
   }
   
   void rotaIzq(Link & r1) {
      Link r2 = r1->dr;
      r1->dr = r2->iz;
      r2->iz = r1;
      r1->altura = std::max(altura(r1->iz), altura(r1->dr)) + 1;
      r2->altura = std::max(altura(r2->iz), altura(r2->dr)) + 1;
      r2->tam_i += r1->tam_i; // Sumar a r2 el valor de tam_i para el nodo A
      r1 = r2;
   }
   
   void rotaIzqDer(Link & r3) {
      rotaIzq(r3->iz);
      rotaDer(r3);
   }
   
   void rotaDerIzq(Link & r1) {
      rotaDer(r1->dr);
      rotaIzq(r1);
   }
   
   void reequilibraIzq(Link & a) {
      if (altura(a->dr) - altura(a->iz) > 1) {
         if (altura(a->dr->iz) > altura(a->dr->dr))
            rotaDerIzq(a);
         else rotaIzq(a);
      }
      else
         a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
   }
   
   void reequilibraDer(Link & a) {
      if (altura(a->iz) - altura(a->dr) > 1) {
         if (altura(a->iz->dr) > altura(a->iz->iz))
            rotaIzqDer(a);
         else rotaDer(a);
      }
      else
         a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
   }
   
   // devuelve y borra el mínimo del árbol con raíz en a
   T borraMin(Link & a) {
      if (a->iz == nullptr) {
         T min = a->elem;
         a = a->dr;
         --nelems;
         return min;
      } else {
         T min = borraMin(a->iz);
         reequilibraIzq(a);
         return min;
      }
   }
   
   bool borra(T const& e, Link & a)  {
      bool decrece = false;
      if (a != nullptr) {
         if (menor(e, a->elem)) {
            decrece = borra(e, a->iz);
            if (decrece) reequilibraIzq(a);
         }
         else if (menor(a->elem, e)) {
            decrece = borra(e, a->dr);
            if (decrece) reequilibraDer(a);
         }
         else { // e == a->elem
            if (a->iz == nullptr || a->dr == nullptr) {
               Link aux = a;
               a = (a->iz == nullptr) ? a->dr : a->iz;
               --nelems;
               delete aux;
            }
            else { // tiene dos hijos
               T min = borraMin(a->dr);
               a->elem = min;
               reequilibraDer(a);
            }
            decrece = true;
         }
      }
      return decrece;
   }

   T const& kesimoAux(int k, int acumulatedTam_i, Link root) const {
      if (root == nullptr)
         throw std::out_of_range("Position not found!");

      int tempSize = acumulatedTam_i + root->tam_i;
      
      if (tempSize == k)
         return root->elem;
      else if (tempSize < k)
         return kesimoAux(k, tempSize, root->dr);
      else if (tempSize > k)
         return kesimoAux(k, acumulatedTam_i, root->iz);
   }
         
public:
   // iteradores que recorren los elementos del conjunto de menor a mayor
   class const_iterator {
   public:
      T const& operator*() const {
         if (act == nullptr)
            throw std::out_of_range("No hay elemento a consultar");
         return act->elem;
      }
      
      T const* operator->() const {
         return &operator*();
      }
      
      const_iterator & operator++() {  // ++ prefijo
         next();
         return *this;
      }
      
      bool operator==(const_iterator const& that) const {
         return act == that.act;
      }
      
      bool operator!=(const_iterator const& that) const {
         return !(this->operator==(that));
      }
      
   protected:
      friend class Set;
      Link act;
      std::stack<Link> ancestros;  // antecesores no visitados
      
      // construye el iterador al primero
      const_iterator(Link raiz) { act = first(raiz); }
      
      // construye el iterador al último
      const_iterator() : act(nullptr) {}
      
      Link first(Link ptr) {
         if (ptr == nullptr) {
            return nullptr;
         } else { // buscamos el nodo más a la izquierda
            while (ptr->iz != nullptr) {
               ancestros.push(ptr);
               ptr = ptr->iz;
            }
            return ptr;
         }
      }
      
      void next() {
         if (act == nullptr) {
            throw std::out_of_range("El iterador no puede avanzar");
         } else if (act->dr != nullptr) { // primero del hijo derecho
            act = first(act->dr);
         } else if (ancestros.empty()) { // hemos llegado al final
            act = nullptr;
         } else { // podemos retroceder
            act = ancestros.top();
            ancestros.pop();
         }
      }
   };
   
   const_iterator begin() const {
      return const_iterator(raiz);
   }
   
   const_iterator end() const {
      return const_iterator();
   }
};


#endif

bool resuelveCaso() {
     int N;
     cin >> N;
     if (N == 0)
        return false;
     
    // los valores de la entrada se insertan en el conjunto
     Set<int> cjto;
     int valor;
     for (int i = 0; i < N; ++i) {
        cin >> valor;
        cjto.insert(valor);
     }
     
     int consultas, k;
     cin >> consultas;
     // para cada consulta se utiliza el nuevo método kesimo
     for (int i = 0; i < consultas; ++i) {
        cin >> k;
        try {
           cout << cjto.kesimo(k) << "\n";
        } catch (std::out_of_range & e) {
           cout << "??\n";
        }
        
     }
     
     cout << "---\n";
     
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
