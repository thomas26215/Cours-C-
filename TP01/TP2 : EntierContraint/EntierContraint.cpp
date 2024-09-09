#include "EntierContraint.h"
#include <iostream>
#include <algorithm>

EntierContraint::EntierContraint(int valeur, int min, int max)
    : m_min(min), m_max(max), m_val(valeur) {
    setValeur(valeur); // Pour s'assurer que la valeur initiale est dans les limites
}

EntierContraint::~EntierContraint() {}

void EntierContraint::setValeur(int valeur) {
    m_val = std::clamp(valeur, m_min, m_max);
}

int EntierContraint::getValeur() const {
    return m_val;
}

void EntierContraint::setMin(int min) {
    m_min = min;
    setValeur(m_val); // Ajuster la valeur si nécessaire
}

int EntierContraint::getMin() const {
    return m_min;
}

void EntierContraint::setMax(int max) {
    m_max = max;
    setValeur(m_val); // Ajuster la valeur si nécessaire
}

int EntierContraint::getMax() const {
    return m_max;
}

void EntierContraint::saisir(std::istream& entree) {
    int valeur;
    entree >> valeur;
    setValeur(valeur);
}

void EntierContraint::afficher(std::ostream& sortie) const {
    sortie << "Valeur: " << m_val << " (min: " << m_min << ", max: " << m_max << ")";
}