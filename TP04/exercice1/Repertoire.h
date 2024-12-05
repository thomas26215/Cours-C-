#ifndef REPERTOIRE_H
#define REPERTOIRE_H

#include <string>
#include <vector>
#include "Element.h"
#include "Usager.h"

class Repertoire : public Element {
private:
    std::vector<Element*> elements;

public:
    Repertoire(const std::string& nom, Usager& proprietaire);
    
    unsigned int getTaille() const override { return 4; }
    void ajouter(Element* element) override;
    void afficher() const override;
    const std::string& getDateModification() const override; // Ajout de const

    virtual ~Repertoire() = default;
    inline const std::string type() const override { return "folder"; }

    void rechercher(const std::string& nom);
    void rechercherRecursif(const std::string& nom, std::vector<std::string>& chemin);
};

#endif /* REPERTOIRE_H */