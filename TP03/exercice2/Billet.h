#ifndef BILLET_H
#define BILLET_H

#include <iostream>
#include <iomanip>

#include "Trajet.h"
#include "Tarif.h"

class Billet {
public:
    Billet(Trajet& unTrajet, Tarif& unTarif);
    ~Billet();
    Trajet& getTrajet() const;
    Tarif& getTarif() const;
    float getPrix() const;
    

protected:
    Trajet const& m_trajet;  // Changé de 'trajet' à 'm_trajet'
    Tarif const& m_tarif;    // Changé de 'tarif' à 'm_tarif'
};

std::ostream & operator<<(std::ostream &sortie, const Billet & billet);

#endif