#ifndef BILLETREDUIT_H
#define BILLETREDUIT_H

#include "Billet.h"
#include "Promotion.h"

class BilletReduit : public Billet{
private:
    Promotion& m_promotion;

public:
    BilletReduit(Trajet& unTrajet, Tarif& unTarif, Promotion& unePromotion);
    virtual ~BilletReduit();

    float getPrix() const override;
    const Promotion& getPromotion() const;
    
    void afficher(std::ostream& sortie) const override;
};

std::ostream& operator<<(std::ostream& sortie, const BilletReduit& billet_reduit);

#endif // BILLETREDUIT_H