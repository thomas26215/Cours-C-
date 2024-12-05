#ifndef SALARIE_H
#define	SALARIE_H

#include <string>
#include <iostream>
#include "SalarieException.h"
#include "ObjetContraint.h"
#include <map>

class Salarie {
public:
    // A COMPLETER : Spécifier les méthodes d'instance d'un Salarie

    Salarie(const std::string& nom, const std::string& numeroSS, const float salaire);
    ~Salarie();
    const std::string& getNom() const{return nom;}
    inline const std::string getNumeroSS() const{return numeroSS;}
    inline const float getSalaireMensuel() const{return salaireMensuel.getVal();}

    void setNom(const std::string& newNom);
    void setNumeroSS(const std::string& newNumeroSS);
    void setSalaireMensuel(float salaire);

    float getImpots() const;
    void saisir(std::istream& entree);
    void afficher(std::ostream& sortie) const;

    
    
    // Fourni : Constantes de Classe
    static const float                 SMIC;
    static const float                 COEFF_SMIC;
    static const std::string           NOM_DEF;
    static const std::string           NUMERO_SS_DEF;
    static const std::map<float,float> TRANCHES_IMPOT;

private:
    std::string nom;
    std::string numeroSS;
    ObjetContraint<float> salaireMensuel;
};

#endif	/* SALARIE_H */

