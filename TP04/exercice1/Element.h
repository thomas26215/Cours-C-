#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>
#include <vector>

class Usager; // Déclaration anticipée

class Element {
public:
    virtual ~Element() = default;

    inline virtual const std::string& getNom() const { return nom; }
    inline virtual void setNom(const std::string& newNom) { nom = newNom; }
    inline virtual const std::string& getLogin() const {return login; }
    inline virtual void getLogin(const std::string& newLogin){login = newLogin; }
    inline virtual const Usager* getProprietaire() const { return proprietaire; }
    inline virtual void setProprietaire(const Usager* newProprietaire) { proprietaire = newProprietaire; }
    virtual unsigned int getTaille() const = 0;
    virtual const std::string& getDateModification() const = 0;
    inline virtual void setDateModification(const std::string& date) {
        throw "Impossible de changer la date de modifications";
    }
    virtual void afficher() const = 0;
    inline virtual void ajouter(Element* element) {
        throw "Impossible d'ajouter un élément";
    }
    virtual const std::string type() const = 0;
protected:
    std::string nom;
    std::string login;
    std::string groupe;
    std::string date_modification;
    unsigned int taille = 0;
    const Usager* proprietaire = nullptr;
    std::vector<Element*> elements;
};

#endif /* ELEMENT_H */