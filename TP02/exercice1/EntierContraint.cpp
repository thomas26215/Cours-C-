#include "EntierContraint.h"
#include <iostream>
using namespace std;

// A Compléter
// Il faut Implémenter operator int, operator << et operator >>

EntierContraint::EntierContraint(int valeur, int min, int max)
: m_min(min), m_max(max) {
    this->setVal(valeur); // Il faut utiliser setVal pour vérifier que m_min<=valeur<=m_max
}

void EntierContraint::setVal(int valeur) {
    if (valeur < getMin() || valeur > getMax()) // exception levée aussi si m_min>m_max
        throw ("Valeur entier contraint hors intervalle");
    this->m_val = valeur;
}

int EntierContraint::getMin() const {
    return this->m_min;
}

int EntierContraint::getMax() const {
    return this->m_max;
}

int EntierContraint::getVal() const {
    return this->m_val;
}

void EntierContraint::saisir(istream& entree) {
    int val;
    entree >> val;
    entree.ignore(256, '\n'); // pour "consommer" le retour chariot tapé après l'entier
    this->setVal(val); // Il faut utiliser setVal pour vérifier que m_min<=valeur<=m_max
}

void EntierContraint::afficher(ostream& sortie) const {
    sortie << this->getVal();
}

std::ostream & operator << (std::ostream & sortie, const EntierContraint & ec){
    cout << "coucou";
    return sortie;
    /*
    
    Dans la fonction main, quand on fera cout << entier << endl;
    => Cela affichera "coucouc" car c'est l'opérateur qui le dit. Je peux lui faire afficher n'importe quoi
    
    */
}

std::istream& operator>>(std::istream& entree, EntierContraint& ec) {
    int val;
    cout << "Rentrez une valeur" << endl;
    entree >> val;
    ec.setVal(val);
    return entree;
}