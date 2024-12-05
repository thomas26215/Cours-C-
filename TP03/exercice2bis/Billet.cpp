#include "Billet.h"

Billet::Billet(Trajet& unTrajet, Tarif& unTarif) 
    : m_trajet(unTrajet), m_tarif(unTarif) {}

Billet::~Billet() {}

const Trajet& Billet::getTrajet() const {
    return m_trajet;
}

const Tarif& Billet::getTarif() const {
    return m_tarif;
}

float Billet::getPrix() const {
    float distance = static_cast<float>(m_trajet.getDistance());
    return m_tarif.getPrixAuKm() * distance;
}

void Billet::afficher(std::ostream& sortie) const {
    sortie << "- Trajet : " << getTrajet() << std::endl
           << "- Distance : " << getTrajet().getDistance() << std::endl
           << "- Tarif : " << getTarif() << std::endl
           << "- Prix : " << getPrix() << std::endl;
}

std::ostream& operator<<(std::ostream& sortie, const Billet& billet) {
    billet.afficher(sortie);
    return sortie;
}