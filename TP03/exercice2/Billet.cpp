#include "Billet.h"
using namespace std;

Billet::Billet(Trajet& unTrajet, Tarif& unTarif) 
    : m_trajet(unTrajet), m_tarif(unTarif) {}

Billet::~Billet() {}

Trajet& Billet::getTrajet() const {
    return const_cast<Trajet&>(m_trajet);
}

Tarif& Billet::getTarif() const {
    return const_cast<Tarif&>(m_tarif);
}

float Billet::getPrix() const{
    float distance = static_cast<float>(m_trajet.getDistance());
    return m_tarif.getPrixAuKm()*distance;
}

std::ostream &operator<<(std::ostream &sortie, const Billet &billet) {
    sortie << "- Trajet : " << billet.getTrajet() << endl << "- Tarif : " << billet.getTrajet().getDistance() << endl << "- Tarif : " << billet.getTarif() << endl << "- Prix : " << billet.getPrix() << endl;

    return sortie;
}