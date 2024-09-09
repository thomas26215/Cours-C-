#include "Point.h"
#include <iostream>

const std::string Point::NOM_DEF = "Point_Default";

Point::Point()
 : nom(NOM_DEF), x(X_DEF), y(Y_DEF) {
    std::cout << "Un point a été instancié : " << nom << std::endl;
}

Point::Point(const std::string &name, int x, int y) : nom(name), x(x), y(y) {
    std::cout << "Un point a été instancié : " << nom << std::endl;
}

Point::~Point() {
    std::cout << "Le point " << nom << " a été supprimé" << std::endl;
}

const std::string& Point::getNom() const { return nom; }

void Point::setNom(const std::string& nom) {
    this->nom = nom;
}

int Point::getX() const { return x; }

void Point::setX(int x) {
    this->x = x;
}

int Point::getY() const { return y; }

void Point::setY(int y) {
    this->y = y;
}

void Point::saisirEntree(std::istream& entree) {
    std::string nom;
    std::cout << "Entrez le nom du point : ";
    entree >> nom;
    this->setNom(nom);
    std::cout << "Entrez les coordonnées x : ";
    entree >> x;
    std::cout << "Entrez les coordonnées y : ";
    entree >> y;
}

void Point::afficher(std::ostream& sortie) const {
    sortie << "Nom : " << this->getNom() << ", Coordonnées x : " << this->getX() << ", Coordonnées y : " << this->getY() << std::endl;
}