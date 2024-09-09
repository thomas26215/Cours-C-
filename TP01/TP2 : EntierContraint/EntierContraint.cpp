// EntierContraint.cpp
#include "EntierContraint.h"
#include <iostream>

EntierContraint::EntierContraint(int valeur, int min, int max) {
    setMin(min);
    setMax(max);
    try {
        setValeur(valeur);
    } catch (char const* erreur) {
        std::cout << "Erreur lors de l'initialisation : " << erreur << std::endl;
        m_val = m_min; // Initialiser avec la valeur minimale par défaut
    }
}

EntierContraint::~EntierContraint() {}

void EntierContraint::setValeur(int valeur) {
    if (valeur >= m_min && valeur <= m_max) {
        m_val = valeur;
    } else {
        throw "La valeur est hors des limites";
    }
}

int EntierContraint::getValeur() const {
    return m_val;
}

void EntierContraint::setMin(int min) {
    if (min <= m_max) {
        m_min = min;
        if (m_val < m_min) m_val = m_min;
    } else {
        throw "La valeur minimale ne peut pas être supérieure à la valeur maximale";
    }
}

int EntierContraint::getMin() const {
    return m_min;
}

void EntierContraint::setMax(int max) {
    if (max >= m_min) {
        m_max = max;
        if (m_val > m_max) m_val = m_max;
    } else {
        throw "La valeur maximale ne peut pas être inférieure à la valeur minimale";
    }
}

int EntierContraint::getMax() const {
    return m_max;
}

void EntierContraint::saisir(std::istream& entree) {
    int valeur;
    entree >> valeur;
    try {
        setValeur(valeur);
    } catch (char const* erreur) {
        std::cout << "Erreur de saisie : " << erreur << std::endl;
    }
}

void EntierContraint::afficher(std::ostream& sortie) const {
    sortie << "Valeur: " << m_val << " (min: " << m_min << ", max: " << m_max << ")";
}