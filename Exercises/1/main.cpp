#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <utility>

#include "bintree.h"

using namespace std;

bool isAVL(const BinTree<int>& root) {
    if (root.empty()) return true;

    int hLeft = 0, hRight = 0;
    bool lAVL = true, rAVL = true;

    if (!root.left().empty()) { // call recursively left
        lAVL = isAVL(root.left());
        hLeft++;
    }

    if (!root.right().empty()) { // call recursively left
        rAVL = isAVL(root.right());
        hRight++;
    }

    // abs(hLeft - hRight <= 1) 

    if (lAVL && rAVL && hLeft - hRight <= 1 && hRight - hLeft <= 1)
        return true;
    
    return false;
}

void tratar_caso() {
    BinTree<int> tree;

    tree.read_tree(std::cin);
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int n;
    std::cin >> n;

    for (int i= 0 ; i < n; i++) tratar_caso();

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif

    return 0;
}