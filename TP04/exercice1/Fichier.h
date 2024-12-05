#ifndef FICHIER_H
#define FICHIER_H

#include "Element.h"
#include <string>

class Fichier : public Element {
public:
    Fichier(const std::string& nom, unsigned int taille, const std::string& dateModification, const Usager& proprietaire);
    ~Fichier() override = default;

    unsigned int getTaille() const override;
    const std::string& getDateModification() const override;
    void setDateModification(const std::string& date) override;
    void afficher() const override;
    void ajouter(Element* element) override;

    inline const std::string type() const override { return "file"; }


};

#endif