#include <iostream>
#include "EntierContraint.h"

int main() {
    try {
        EntierContraint entier(10, 0, 20);
        std::cout << "Entier 1 : ";
        entier.afficher();
        std::cout << std::endl;

        //entier.setValeur(30); // Ceci devrait lancer une exception
    }
    catch (const char* erreur) {
        std::cout << "Une exception a été attrapée : " << erreur << std::endl;
    }
    
    return 0;
}