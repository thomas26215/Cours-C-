#ifndef PARAMETRES_H
#define PARAMETRES_H
#include <string>
#include "Theme.h"
#include "Joueur.h"

class Parametres {
public:
    static Parametres& getInstance(const std::string& intituleTheme = "Par défaut");
    ~Parametres();
    Theme& getTheme();
    void setTheme(const Theme& newTheme);
    Joueur* getJoueur();
    void setJoueur(Joueur* newJoueur);
    void afficher();

    // Empêcher la copie et l'assignation
    Parametres(const Parametres&) = delete;
    Parametres& operator=(const Parametres&) = delete;

private:
    Parametres(const std::string& intituleTheme);
    Theme theme;
    Joueur* joueur;
    static Parametres* m_instance;
};

#endif /* PARAMETRES_H */