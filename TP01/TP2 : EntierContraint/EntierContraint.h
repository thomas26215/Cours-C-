// EntierContraint.h
#ifndef ENTIERCONTRAINT_H
#define ENTIERCONTRAINT_H

#include <iostream>
#include <stdexcept>

class EntierContraint {
public:
    EntierContraint(int valeur, int min, int max);
    ~EntierContraint();
    int getValeur() const;
    void setValeur(int valeur);
    int getMin() const;
    void setMin(int min);
    int getMax() const;
    void setMax(int max);
    void saisir(std::istream& entree = std::cin);
    void afficher(std::ostream& sortie = std::cout) const;

private:
    int m_min;
    int m_max;
    int m_val;
};

#endif