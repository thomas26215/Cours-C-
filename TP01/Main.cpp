#include <iostream>
#include "Point.h"

int main() {
    Point p1;
    std::cout << "Point 1 : ";
    p1.afficher();

    Point p2("MonPoint", 5, 10);
    std::cout << "Point 2 : ";
    p2.afficher();

    p1.setNom("PointModifié");
    std::cout << "Point 1 après modification : ";
    p1.afficher();

    std::cout << "Nom du Point 2 : " << p2.getNom() << std::endl;

    Point p3;
    std::cout << "Saisissez les informations pour le Point 3 :" << std::endl;
    p3.saisirEntree();
    std::cout << "Point 3 saisi : ";
    p3.afficher();

    return 0;
}