#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Clasa pentru reprezentarea digrafului
class Digraf {
private:
    int numarVarfuri; // Numarul de varfuri
    vector<vector<int>> listeAdiacenta; // Liste de adiacenta

public:
    Digraf(int V) : numarVarfuri(V) {
        listeAdiacenta.resize(numarVarfuri);
    }

    // Functie pentru adaugarea unei muchii in digraf
    void adaugaMuchie(int sursa, int destinatie) {
        listeAdiacenta[sursa].push_back(destinatie);
    }

    // Functie utilitara pentru sortarea topologica
    void sortareTopologicaUtil(int varf, vector<bool>& vizitat, stack<int>& stiva) {
        vizitat[varf] = true;

        // Se parcurg toti vecinii varfului curent
        for (int vecin : listeAdiacenta[varf]) {
            if (!vizitat[vecin]) {
                sortareTopologicaUtil(vecin, vizitat, stiva);
            }
        }

        // Se adauga varful curent in stiva
        stiva.push(varf);
    }

    // Functie pentru sortarea topologica a digrafului
    void sortareTopologica() {
        vector<bool> vizitat(numarVarfuri, false); // Vector de vizitare
        stack<int> stiva; // Stiva pentru rezultatul final

        // Se aplica sortarea topologica pe toate varfurile nevizitate
        for (int i = 0; i < numarVarfuri; i++) {
            if (!vizitat[i]) {
                sortareTopologicaUtil(i, vizitat, stiva);
            }
        }

        // Se afiseaza rezultatul din stiva
        while (!stiva.empty()) {
            cout << stiva.top() << " ";
            stiva.pop();
        }
    }
};

// Functia main
int main() {
    // Se creează un digraf aciclic cu 6 varfuri
    Digraf digraf(6);
    digraf.adaugaMuchie(5, 2);
    digraf.adaugaMuchie(5, 0);
    digraf.adaugaMuchie(4, 0);
    digraf.adaugaMuchie(4, 1);
    digraf.adaugaMuchie(2, 3);
    digraf.adaugaMuchie(3, 1);

    cout << "Sortarea topologica a varfurilor digrafului este: ";
    digraf.sortareTopologica();

    return 0;
}
