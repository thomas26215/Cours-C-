#include "Repertoire.h"
#include <iostream>
#include <iostream>
#include <string>

using namespace std;

Repertoire::Repertoire(const string& nom, Usager& proprietaire){
    this->nom = nom;
    this->proprietaire = &proprietaire;
}

void Repertoire::ajouter(Element* element){
    elements.push_back(element);
}

const std::string& Repertoire::getDateModification() const{
    return date_modification;
}

void Repertoire::rechercher(const string& nom) {
    std::vector<string> chemin;
    chemin.push_back(this->nom);
    rechercherRecursif(nom, chemin);
}

void Repertoire::rechercherRecursif(const string& nom, std::vector<string>& chemin) {
    for (const auto& element : elements) {
        // Ajouter le nom de l'élément courant au chemin
        chemin.push_back(element->getNom());

        if (element->getNom() == nom) {
            // Construire le chemin complet
            string cheminComplet = "";
            for (const auto& partie : chemin) {
                cheminComplet += "/" + partie;
            }

            if (element->type() == "file") {
                cout << "Fichier trouvé : " << cheminComplet << endl;
            } else if (element->type() == "folder") {
                cout << "Répertoire trouvé : " << cheminComplet << endl;
            }
        }
        
        // Si c'est un répertoire, rechercher récursivement
        if (element->type() == "folder") {
            if (Repertoire* rep = dynamic_cast<Repertoire*>(element)) {
                rep->rechercherRecursif(nom, chemin);
            }
        }

        // Retirer le nom de l'élément courant du chemin avant de passer au suivant
        chemin.pop_back();
    }
}

void Repertoire::afficher() const {
    std::cout << "Répertoire: " << nom << std::endl;
    std::cout << "Propriétaire: " << getNom() << std::endl;
    std::cout << "Contenu:" << std::endl;
    for (const auto& element : elements) {
        element->afficher();
    }
}