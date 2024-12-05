#include "BilletReduit.h"

BilletReduit::BilletReduit(Trajet& unTrajet, Tarif& unTarif, Promotion& unePromotion)
    : Billet(unTrajet, unTarif), m_promotion(unePromotion) {}

BilletReduit::~BilletReduit() {}

float BilletReduit::getPrix() const {
    float distance = (m_trajet.getDistance());
    return m_promotion.calculePrixReduit(Billet::getPrix());
}

const Promotion& BilletReduit::getPromotion() const {
    return m_promotion;
}

void BilletReduit::afficher(std::ostream& sortie) const {
    Billet::afficher(sortie);
    sortie << "- Promo : " << getPromotion() << std::endl;
}

/*std::ostream& operator<<(std::ostream& sortie, const BilletReduit& billet_reduit) {
    billet_reduit.afficher(sortie);
    return sortie;
}*/