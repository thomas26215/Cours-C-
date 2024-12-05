#include "Salarie.h"
#include "SalarieException.h"
#include <ctype.h>
#include <map>
#include <limits>
#include <string>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <exception>

using namespace std;

// Constructeur
Salarie::Salarie(const string& nom, const string& numeroSS, const float salaire) :
    nom(nom), numeroSS(numeroSS), salaireMensuel(salaire, SMIC, SMIC*COEFF_SMIC) {
    setNom(nom);
    setNumeroSS(numeroSS);
    setSalaireMensuel(salaire);
}

// Destructeur
Salarie::~Salarie() {}

// Méthode pour calculer les impôts
float Salarie::getImpots() const {
    float salaireAnnuel = salaireMensuel.getVal() * 12;
    float impot = 0.0f;
    float tranchePrecedente = 0.0f;

    cout << salaireAnnuel << endl;
    cout << TRANCHES_IMPOT.begin()->first;

    // Vérifier si le salaire est inférieur à la première tranche
    if (salaireAnnuel <= TRANCHES_IMPOT.begin()->first) {
        return 0.0f; // Pas d'impôt pour les salaires inférieurs à la première tranche
    }

    for (auto it = std::next(TRANCHES_IMPOT.begin()); it != TRANCHES_IMPOT.end(); ++it) {
        if (salaireAnnuel > std::prev(it)->first) {
            cout << it->first;
            continue;
        } else {
            return it->first * it->second; 
        }
    }

    return impot; // Retourne l'impôt mensuel
}

// Setter pour le nom
void Salarie::setNom(const std::string& newNom) {
    if (newNom.empty() || !std::isalpha(newNom[0])) {
        throw NomIncorrectException("Le nom doit commencer par une lettre et ne pas être vide.");
    }
    
    for (char c : newNom) {
        if (!std::isalpha(c) && c != '-') {
            throw NomIncorrectException("Le nom ne doit contenir que des lettres ou des tirets.");
        }
    }
    nom = newNom;
}

// Setter pour le numéro de sécurité sociale
void Salarie::setNumeroSS(const std::string& newNumeroSS) {
    if (newNumeroSS.length() != 13 || (newNumeroSS[0] != '1' && newNumeroSS[0] != '2')) {
        throw NumeroIncorrectException("Le numéro de sécurité sociale doit avoir 13 chiffres et commencer par 1 ou 2.");
    }
    
    for (char c : newNumeroSS) {
        if (!std::isdigit(c)) {
            throw NumeroIncorrectException("Le numéro de sécurité sociale ne doit contenir que des chiffres.");
        }
    }
    numeroSS = newNumeroSS;
}

// Setter pour le salaire mensuel
void Salarie::setSalaireMensuel(float newSalaire) {
    try {
        salaireMensuel.setVal(newSalaire);
    } catch (const std::domain_error& e) {
        throw SalaireIncorrectException(e.what());
    }
}

// Méthode de saisie
void Salarie::saisir(std::istream& entree) {
    std::string nom_temp, numeroSS_temp;
    float salaire_temp;

    while (true) {
        std::cout << "Entrez le nom : ";
        std::getline(entree >> std::ws, nom_temp);
        try {
            setNom(nom_temp);
            break;
        } catch (const NomIncorrectException& e) {
            std::cout << "Erreur : " << e.what() << " Veuillez réessayer." << std::endl;
        }
    }

    while (true) {
        std::cout << "Entrez le numéro de sécurité sociale : ";
        entree >> numeroSS_temp;
        try {
            setNumeroSS(numeroSS_temp);
            break;
        } catch (const NumeroIncorrectException& e) {
            std::cout << "Erreur : " << e.what() << " Veuillez réessayer." << std::endl;
        }
    }

    while (true) {
        std::cout << "Entrez le salaire mensuel : ";
        entree >> salaire_temp;
        try {
            setSalaireMensuel(salaire_temp);
            break;
        } catch (const SalaireIncorrectException& e) {
            std::cout << "Erreur : " << e.what() << " Veuillez réessayer." << std::endl;
        }
    }
}

// Méthode d'affichage
void Salarie::afficher(std::ostream& sortie) const {
    sortie << "Nom : " << nom << std::endl;
    sortie << "Numéro de sécurité sociale : " << numeroSS << std::endl;
    sortie << "Salaire mensuel : " << salaireMensuel.getVal() << " €" << std::endl;
    sortie << "Impôts mensuels : " << std::fixed << std::setprecision(2) << getImpots() << " €" << std::endl;
    getImpots();
}

// Constantes de classe
const float Salarie::SMIC = 1257.0f;
const float Salarie::COEFF_SMIC = 500.0f;
const std::string Salarie::NOM_DEF = "Martin";
const std::string Salarie::NUMERO_SS_DEF = "1234567890123";
const std::map<float, float> Salarie::TRANCHES_IMPOT {
    {  6000.0f, 0.000f},
    { 12000.0f, 0.055f},
    { 26600.0f, 0.140f},
    { 71400.0f, 0.300f},
    {151200.0f, 0.410f},
    {std::numeric_limits<float>::max(), 0.50f} 
};