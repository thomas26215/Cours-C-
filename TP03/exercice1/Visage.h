#ifndef VISAGE_H
#define VISAGE_H

#include "AttributsVisage.h"
#include <vector>
#include <optional>

class Visage {
public:
    Visage(int longueurNez, const Ethnie &uneEthnie);
    void setMoustache(int largeur);
    void addBouton(int diametre);
    void addChapeau(const Chapeau &unChapeau);
    void addBijou(const Bijou &unBijou);
    Visage& operator=(const Visage &unVisage);
    Visage(const Visage &unVisage);
    ~Visage();

    friend std::ostream &operator<<(std::ostream &sortie, const Visage &visage);

private:
    Nez m_nez;
    const Ethnie& m_ethnie;
    std::optional<Moustache> m_moustache;
    Chapeau* m_chapeaux;
    std::vector<const Bijou*> m_bijoux;
    std::vector<Bouton> m_boutons;
};

#endif /* VISAGE_H */