#include "Parametres.h"

int main() {
    
    Joueur* joueur1 = new Joueur("Thomas");
    Joueur* joueur2 = new Joueur("Sophie");

    Theme* theme1 = new Theme("Black");
    Theme* theme2 = new Theme("White");

    Parametres& params1 = Parametres::getInstance("Orange");
    params1.afficher();

    Parametres& params2 = Parametres::getInstance("Orange");
    params2.setJoueur(joueur1);
    params2.setTheme(*theme1);
    params2.afficher();
    

    return 0;
}

/////// TRACE ATTENDUE //////////////////////////////////
//
// Paramètres { Theme: 'Par Défaut', Joueur: 'Anonyme' }
// Paramètres { Theme: 'Urbain', Joueur: 'Yoloutre' }
//
/////////////////////////////////////////////////////////