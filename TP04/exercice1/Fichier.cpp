#include "Fichier.h"
#include <iostream>
#include <stdexcept>

Fichier::Fichier(const std::string& nom, unsigned int taille, const std::string& dateModification, const Usager& proprietaire){
    this->nom = nom;
    this->taille = taille;
    this->date_modification = dateModification;
    this->proprietaire = &proprietaire;
}

unsigned int Fichier::getTaille() const {
    return taille;
}

const std::string& Fichier::getDateModification() const {
    return date_modification;
}

void Fichier::setDateModification(const std::string& date) {
    this->date_modification = date;
}

void Fichier::afficher() const {
    std::cout << "Fichier: " << getNom()
              << "; taille: " << getTaille() 
              << "; date de modification: " << date_modification;
    if (proprietaire != nullptr) {
        std::cout << "; proprietaire: " << getNom();
    }
    std::cout << std::endl;
}

void Fichier::ajouter(Element* element) {
    throw std::runtime_error("Impossible d'ajouter un élément à un fichier.");
}