#include <iostream>
#include "BilletReduit.h"
using namespace std;

BilletReduit::BilletReduit(Trajet& unTrajet, Tarif& unTarif, Promotion& unePromotion) : m_promotion(unePromotion), Billet(unTrajet, unTarif){}
BilletReduit::~BilletReduit(){}
float BilletReduit::getPrix() const{
    float distance = static_cast<float>(m_trajet.getDistance());
    return m_promotion.calculePrixReduit(m_tarif.getPrixAuKm()*distance);
    
}
Promotion const& BilletReduit::getPromotion() const{
    return m_promotion;
}

std::ostream &operator<<(std::ostream &sortie, const BilletReduit &billet_reduit) {
    sortie << "- Trajet : " << billet_reduit.getTrajet() << endl << "- Tarif : " << billet_reduit.getTrajet().getDistance() << endl << "- Tarif : " << billet_reduit.getTarif() << endl << "- Prix : " << billet_reduit.getPrix() << endl << "- Promo : " << billet_reduit.getPromotion();

    return sortie;
}