#include "Visage.h"
#include <iostream>
using namespace std;

Visage::Visage(int longueurNez, const Ethnie &uneEthnie) 
    : m_nez(longueurNez), m_ethnie(uneEthnie), m_chapeaux(nullptr), m_moustache(0) {
}

void Visage::setMoustache(int largeur) {
    m_moustache = Moustache(largeur);
}

void Visage::addBouton(int diametre) {
    m_boutons.push_back(Bouton(diametre));
}

void Visage::addChapeau(const Chapeau &unChapeau) {
    if (m_chapeaux) delete m_chapeaux;
    m_chapeaux = new Chapeau(unChapeau);
}

void Visage::addBijou(const Bijou &unBijou) {
    m_bijoux.push_back(new Bijou(unBijou));
}

Visage& Visage::operator=(const Visage &unVisage) {
    if (this != &unVisage) {
        m_nez = unVisage.m_nez;
        m_moustache = unVisage.m_moustache;
        m_boutons = unVisage.m_boutons;

        if (m_chapeaux) delete m_chapeaux;
        m_chapeaux = unVisage.m_chapeaux ? new Chapeau(*unVisage.m_chapeaux) : nullptr;

        for (auto* bijou : m_bijoux) {
            delete bijou;
        }
        m_bijoux.clear();
        for (const auto* bijou : unVisage.m_bijoux) {
            m_bijoux.push_back(new Bijou(*bijou));
        }
    }
    return *this;
}

Visage::Visage(const Visage &unVisage) 
    : m_nez(unVisage.m_nez), m_ethnie(unVisage.m_ethnie), 
      m_moustache(unVisage.m_moustache), m_boutons(unVisage.m_boutons),
      m_chapeaux(unVisage.m_chapeaux ? new Chapeau(*unVisage.m_chapeaux) : nullptr) {
    for (const auto& bijou : unVisage.m_bijoux) {
        m_bijoux.push_back(new Bijou(*bijou));
    }
}

Visage::~Visage() {
    if (m_chapeaux) delete m_chapeaux;
    for (auto& bijou : m_bijoux) {
        delete bijou;
    }
}

std::ostream &operator<<(std::ostream &sortie, const Visage &visage) {
    sortie << "Attributs du Visage :" << endl
           << "- " << visage.m_ethnie << endl
           << "- " << visage.m_nez << endl;
    
    if (visage.m_moustache) {
        sortie << "- " << *visage.m_moustache << endl;
    } else {
        sortie << "- pas de moustache" << endl;
    }
    
    if (visage.m_chapeaux) {
        sortie << "- " << *visage.m_chapeaux << endl;
    }
    
    for (const auto& bouton : visage.m_boutons) {
        sortie << "- " << bouton << endl;
    }
    
    for (const auto& bijou : visage.m_bijoux) {
        sortie << "- " << *bijou << endl;
    }
    
    return sortie;
}