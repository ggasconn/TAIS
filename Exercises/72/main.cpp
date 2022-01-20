#include <fstream>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

struct bateria {
    int id;
    int duracion;
    int recarga;

    bateria(int id, int duracion) : id(id), duracion(duracion), recarga(duracion) { }
};

bool operator>(bateria const& a, bateria const& b) {
    if (a.duracion == b.duracion) return b.id < a.id;
    return b.duracion < a.duracion;
}

bool resolver_caso() {
    int B; std::cin >> B;

    if (!std::cin) return false;

    std::priority_queue<bateria, std::vector<bateria>, std::greater<bateria>> nave;

    int t;
    int id = 1;
    for (int i = 0; i < B; i++) {
        std::cin >> t;
        nave.push({ id++, t });
    }

    int R; std::cin >> R;
    std::queue<bateria> repuesto;
    for (int i = 0; i < R; i++) {
        std::cin >> t;
        repuesto.push({id, t});
        id++;
    }

    int Z, T; std::cin >> Z >> T;

    int duracion = 0;
    bool naveOK = true;
    while (duracion <= T && naveOK) {
        bateria b = nave.top(); nave.pop();

        duracion += b.duracion - duracion;

        if (duracion > T) {
            nave.push(b);
            naveOK = false;
        }else if (b.recarga - Z > 0) {
            b.duracion = duracion + (b.recarga - Z);
            b.recarga -= Z;
            nave.push(b);
        }else {
            if (!repuesto.empty()) {
                bateria bAux = repuesto.front(); repuesto.pop();
                bAux.duracion += duracion;
                nave.push(bAux);
            }else {
                naveOK = false;
            }
        }
    }

    if (nave.size() == B)
        std::cout << "CORRECTO\n";
    else if (nave.size() > 0)
        std::cout << "FALLO EN EL SISTEMA\n";
    else
        std::cout << "ABANDONEN INMEDIATAMENTE LA BASE\n";
    
    while (!nave.empty()) {
        std::cout << nave.top().id << " " << nave.top().duracion << "\n";
        nave.pop();
    }
    
    std::cout << "---\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while(resolver_caso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif

    return 0;
}