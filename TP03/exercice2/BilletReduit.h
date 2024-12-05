#ifndef BILLETREDUIT_H
#define BILLETREDUIT_H

#include "Billet.h"
#include "Promotion.h"

class BilletReduit : public Billet {
public:
    BilletReduit(Trajet& unTrajet, Tarif& unTarif, Promotion& unePromotion);
    ~BilletReduit();
    float getPrix() const;
    Promotion const& getPromotion() const;
private:
    Promotion const& m_promotion;

    
};
std::ostream &operator<<(std::ostream &sortie, const BilletReduit &billet_reduit);
#endif