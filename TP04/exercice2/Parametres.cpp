#include "Parametres.h"
#include <iostream>
using namespace std;

Parametres* Parametres::m_instance = nullptr;

Parametres::Parametres(const std::string& intituleTheme) : theme(intituleTheme), joueur(nullptr) {}

Parametres::~Parametres() {
    delete joueur;
}

Parametres& Parametres::getInstance(const std::string& intituleTheme) {
    if (m_instance == nullptr) {
        m_instance = new Parametres(intituleTheme);
    }
    return *m_instance;
}

Theme& Parametres::getTheme() {
    return theme;
}

void Parametres::setTheme(const Theme& newTheme) {
    theme = newTheme;
}

Joueur* Parametres::getJoueur() {
    return joueur;
}

void Parametres::setJoueur(Joueur* newJoueur) {
    delete joueur;
    joueur = newJoueur;
}

void Parametres::afficher() {
    cout << "Theme: " << theme.getIntitule() << endl;
    if (joueur) {
        cout << "Joueur: " << joueur->getPseudo() << endl;
    } else {
        cout << "Joueur: Anonyme" << endl;
    }
}