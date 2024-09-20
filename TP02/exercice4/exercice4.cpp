#include "Conteneur.h"
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

int main(int argc, char** argv) {

    Conteneur<int>* objetA = new Conteneur<int>();

    int a = 5, b = 10, c = 15;
    objetA->ajouter(&a);
    objetA->ajouter(&b);
    objetA->ajouter(&c);
    
    std::cout << "Contenu de objetA :" << std::endl;
    objetA->afficher(std::cout);
    
    Conteneur<int>* objetB = new Conteneur<int>(*objetA);

    std::cout << "Contenu de objetB après copie :" << std::endl;
    objetB->afficher(std::cout);

    a = 14;

    objetA->ajouter(&a);

    cout << "A" << endl;
    objetA->afficher(std::cout);
    cout << "B" << endl;
    objetB->afficher(std::cout);

    return 0;
}