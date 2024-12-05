#ifndef BILLET_H
#define BILLET_H

#include <iostream>
#include "Trajet.h"
#include "Tarif.h"

class Billet {
protected:
    const Trajet& m_trajet;
    const Tarif& m_tarif;

public:
    Billet(Trajet& unTrajet, Tarif& unTarif);
    virtual ~Billet();

    const Trajet& getTrajet() const;
    const Tarif& getTarif() const;
    virtual float getPrix() const;
    
    virtual void afficher(std::ostream& sortie) const;
};

std::ostream& operator<<(std::ostream& sortie, const Billet& billet);

#endif // BILLET_H