#include <iostream>
#include <string>
#include <stdexcept>
#include "Conteneur.h"
#include "Trajet.h"
#include "Tarif.h"
#include "Promotion.h"
#include "Billet.h"
#include "BilletReduit.h"

using namespace std;
/**/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Billet *newBillet(Conteneur<Trajet> &trajets,
                  Conteneur<Tarif> &tarifs,
                  Conteneur<Promotion> &promotions) {

                    std::string isPromotion = "0";

    trajets.afficher();
    Trajet& trajet = trajets.choisir();

    cout << "-- Liste des tarifs" << endl;
    tarifs.afficher();
    Tarif& tarif = tarifs.choisir();

    cout << "Ajouter une promotion ?" << endl;
    cin >> isPromotion;

    if(isPromotion == "O"){
        cout << "--Liste des promotions" << endl;
        promotions.afficher();
        Promotion& promotion = promotions.choisir();
        return new BilletReduit(trajet, tarif, promotion);
    }else{
        return new Billet(trajet, tarif);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    // Création des conteneurs de Trajets, TArifs, Promotions
    Conteneur<Trajet> trajets;
    trajets.ajouter(new Trajet("Grenoble", "Lyon", 100));
    trajets.ajouter(new Trajet("Grenoble", "Paris", 600));
    trajets.ajouter(new Trajet("Grenoble", "Marseille", 300));
    Conteneur<Tarif> tarifs;
    tarifs.ajouter(new Tarif("Normal", 2.00));
    tarifs.ajouter(new Tarif("Jeune", 1.00));
    tarifs.ajouter(new Tarif("Vermeil", 3.00));
    Conteneur<Promotion> promotions;
    promotions.ajouter(new Promotion("Noël", 0.5));
    promotions.ajouter(new Promotion("Anniversaire", 0.2));

    //TODO:Prendre des notes sur les pointeurs

    /*Trajet* trajet = new Trajet("Grenoble", "Lyon", 100);
    Tarif* tarif =  new Tarif("Normal", 2.00);
    Promotion* promotion = new Promotion("Anniversaire", 0.2);


    Billet* billet = new Billet(*trajet, *tarif);
    BilletReduit* billetReduit = new BilletReduit(*trajet, *tarif, *promotion);*/

    Conteneur <Billet> billets;

    std::string ajouter = "0";
    
    int i = 0;
    cout << "Ajouter un billet [O]/N ?";
    cin >> ajouter;

    while(ajouter == "O"){
        cout << "--- Création d'un Billet ---" << endl << "-- Liste des trajets" << endl;

        Billet* billet = newBillet(trajets, tarifs, promotions);
        billets.ajouter(billet);

        cout << billet;

        cout << "Ajouter un billet [O]/N ?";
        cin >> ajouter;

    


    }

    billets.afficher();

    return 0;
}

