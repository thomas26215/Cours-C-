#include "Groupe.h"
#include "Personne.h"
#include <string>
#include <iostream>

using namespace std;

// A COMPLETER
// Implémenter les méthodes nécessaires pour la forme canonique de COPLIEN

Groupe::Groupe(const std::string &intitule)
        : m_intitule(intitule) {
            int nb_eleves;
            /*cout << "Combien d'élèves ?"; cin >> nb_eleves;
            m_effectif.resize(nb_eleves, nullptr);
            for (int i = 0; i < nb_eleves; ++i) {
                m_effectif[i] = new Personne("");
            }*/
}

Groupe::~Groupe(){
    cout << "Le groupe " << m_intitule << " a été supprimé";
}

Groupe::Groupe(const Groupe& autre) : m_intitule(autre.m_intitule) {
    for (const auto& personne : autre.m_effectif) {
        m_effectif.push_back(new Personne(*personne));
    }
}

Groupe& Groupe::operator=(const Groupe& autre) {
    if (this != &autre) {
        // Libérer la mémoire existante
        for (auto& personne : m_effectif) {
            delete personne;
        }
        m_effectif.clear();
        
        // Copier les nouvelles données
        m_intitule = autre.m_intitule;
        for (const auto& personne : autre.m_effectif) {
            m_effectif.push_back(new Personne(*personne));
        }
    }
    return *this;
}

///////////////////////////////////////////////////
void Groupe::setIntitule(const std::string &intitule) {
    this->m_intitule = intitule;
}

///////////////////////////////////////////////////
void Groupe::addPersonne(const std::string &nom) {
    this->m_effectif.push_back(new Personne(nom));
}

///////////////////////////////////////////////////
void Groupe::setNomPersonne(unsigned int i,
                            const std::string nom) {
    if (i < this->m_effectif.size())
        this->m_effectif[i]->setNom(nom);
}

///////////////////////////////////////////////////
void Groupe::affiche() const {
    cout << "Groupe " << this->m_intitule << " = { ";
    for (Personne *personne: this->m_effectif)
        cout << personne->getNom() << " ";
    cout << "}" << endl;
}
