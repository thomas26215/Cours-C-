/* 
 * File:   Mondial.cpp
 * Author: hb
 * 
 * Created on 22 novembre 2018, 16:05
 */

#include "Mondial.h"
#include "tinyxml2.h"


#include <cstdlib>
#include <iostream>     // pour cout
#include <iomanip>      // pour setw()
#include <sstream>
#include <iterator>
#include <string>
#include <vector>

Mondial::Mondial(const char* filename) {
    // Chargement du fichier XML en mémoire
    imageMondial.LoadFile(filename);
    // Initialisation de l'attribut racineMondial avec la racine (élément <mondial>)
    racineMondial = imageMondial.FirstChildElement();
}

void Mondial::Print() {
    imageMondial.Print();
}

/*
 * FOURNIE
 */
int Mondial::getNbAirports() const {
    // initialisation du nombre d’aéroports
    int nb = 0;
    // accéder à <airportscategory>, c’est un fils de l'élément <racineMondial>
    XMLElement* airportsCategory = racineMondial->FirstChildElement("airportscategory");
    // parcours complet des fils de <airportscategory> en les comptants
    // 1) accéder au premier fils <airport> de <airportscategory>
    XMLElement* currentAirport = airportsCategory->FirstChildElement();
    // 2) parcourir tous les <airport> qui sont des frères
    while (currentAirport != nullptr) {
        // un aéroport supplémentaire
        nb = nb + 1;
        // avancer au frère <airport> suivant de currentAirport
        currentAirport = currentAirport->NextSiblingElement();
    }
    // currentAirport n’a plus de frère {currentAirport == nullptr}, c’est le dernier
    return nb;
}

/*
 * FOURNIE
 */
void Mondial::printCountriesCode() const {
    int rank = 1; // rang du pays
    string carcodeValue; // valeur de l'attribut "car_cod" du pays courant
    // accéder à <countriescategory>, c’est un fils de l'élément <racineMondial>)
    XMLElement* countriesCategory = racineMondial->FirstChildElement("countriescategory");
    // parcours complet des fils de <countriescategory> en affichant le rang et le code
    // 1) accéder au premier fils <country> de <countriescategory>
    XMLElement* currentCountry = countriesCategory->FirstChildElement();
    // 2) parcourir tous les <country> qui sont des frères
    while (currentCountry != nullptr) {
        // traiter le pays courant
        //      1) récupérer la valeur de l’attribut "car_code"
        carcodeValue = currentCountry->Attribute("car_code");
        //      2) faire l’affichage
        cout << setw(5) << rank << " : " << carcodeValue << endl;
        // avancer au frère <country> suivant de currentCountry
        currentCountry = currentCountry->NextSiblingElement();
        // mettre à jour le rang
        rank = rank + 1;
    }
    // currentCountry n’a pas de frère {currentCountry == nullptr}, c’est fini
}


int Mondial::getNbDeserts() const {
    XMLElement* pDesert = racineMondial->FirstChildElement("desertscategory")->FirstChildElement("desert");
    int nbDeserts = 0;
    while(pDesert){
        nbDeserts++;
        pDesert = pDesert->NextSiblingElement("desert");
    }
    return nbDeserts;
}

/*
 * A COMPLETER
 */
int Mondial::getNbElemCat(const string categoryName) {
    // Obtenir le nom de la catégorie XML correspondante
    const string xmlCategoryName = decod_category[categoryName];
    
    // Trouver l'élément de catégorie dans le document XML
    XMLElement* categoryElement = racineMondial->FirstChildElement(xmlCategoryName.c_str());
    
    // Si la catégorie n'existe pas, retourner 0
    if (!categoryElement) {
        return 0;
    }
    
    // Compter les éléments de la catégorie
    int count = 0;
    XMLElement* currentElement = categoryElement->FirstChildElement();
    while (currentElement) {
        count++;
        currentElement = currentElement->NextSiblingElement();
    }
    
    return count;
}
/*
 * A COMPLETER
 */
XMLElement* Mondial::getCountryXmlelementFromNameRec(string countryName) const {
    XMLElement* element = racineMondial->FirstChildElement("countriescategory")->FirstChildElement();
    

   
   return getCountryXmlelementFromNameRecWorker(element,  countryName); 
}

/*
 * A COMPLETER
 */
XMLElement* Mondial::getCountryXmlelementFromNameRecWorker(XMLElement* currentCountryElement, string countryName) const {
    if (currentCountryElement == nullptr) {
        return nullptr; // Si l'élément courant est nul, retourner nul
    }

    // Accéder à l'élément <name>
    XMLElement* nameElement = currentCountryElement->FirstChildElement("name");
    if (nameElement) {
        const char* countryText = nameElement->GetText();
        // Vérifier que countryText n'est pas nul avant de comparer
        if (countryText && countryName == countryText) {
            return currentCountryElement; // Retourner l'élément courant si le nom correspond
        }
    }

    // Appeler récursivement pour le frère suivant
    return getCountryXmlelementFromNameRecWorker(currentCountryElement->NextSiblingElement("country"), countryName);
}
/*
 * A COMPLETER
 */
string Mondial::getCountryCodeFromName(string countryName) const noexcept(false) {
    XMLElement* name = getCountryXmlelementFromNameRec(countryName);
    if(name == nullptr){
        return "Erreur";
    }else{
        return name->Attribute("car_code");
    }
    return nullptr;
}

/*
 * A COMPLETER
 */
/**
 * élément <country> d'un pays identifié par son nom countryName
 * @param countryName
 * @return pointeur sur l'élément <country> dont la valeur du fils <name> est égal à countryName, nullprt sinon
 */
XMLElement* Mondial::getCountryXmlelementFromNameIter(string countryName) const {
    XMLElement* element = racineMondial->FirstChildElement("countriescategory")->FirstChildElement("country");

    
    while(element){
        if(element->FirstChildElement("name")->GetText() == countryName){
            return nullptr;
        }
        cout << element->FirstChildElement("name")->GetText() << endl;
        element = element->NextSiblingElement();
    }

    return nullptr;

}

XMLElement* Mondial::getCountryXmlelementFromCode(string countryCode) const {
    if (!racineMondial) {
        cerr << "Erreur : racineMondial est nul." << endl;
        return nullptr; // Retourne nullptr si racineMondial est nul
    }

    XMLElement* countriesCategory = racineMondial->FirstChildElement("countriescategory");
    if (!countriesCategory) {

        cerr << "Erreur : countriesCategory est nul." << endl;
        return nullptr; // Retourne nullptr si countriesCategory est nul
    }

    XMLElement* element = countriesCategory->FirstChildElement("country");

    while (element) {
        const char* carCode = element->Attribute("car_code");
        if (carCode && countryCode == carCode) {
            return element; // Retourne l'élément si trouvé
        }
        element = element->NextSiblingElement("country"); // Avance à l'élément suivant
    }
    return nullptr; // Retourne nullptr si aucun élément n'est trouvé
}
/*
 * A COMPLETER
 */
int Mondial::getCountryPopulationFromName(string countryName) const {
    // Trouver l'élément <country> correspondant au nom donné
    XMLElement* countryElement = getCountryXmlelementFromNameRec(countryName);
    
    if (countryElement == nullptr) {
        return -1; // Retourner -1 si le pays n'est pas trouvé
    }

    int lastPopulation = 0; // Initialiser la dernière population à 0
    bool hasPopulationData = false; // Indicateur pour savoir si des données de population existent

    // Accéder aux éléments de population
    XMLElement* populationElement = countryElement->FirstChildElement("population");

    while (populationElement != nullptr) {
        const char* popText = populationElement->GetText();
        
        if (popText) {
            lastPopulation = atoi(popText); // Convertir le texte en entier
            hasPopulationData = true; // On a trouvé des données de population
        }

        populationElement = populationElement->NextSiblingElement("population"); // Passer à l'élément suivant
    }

    return hasPopulationData ? lastPopulation : 0; // Retourner la dernière population ou 0 si aucune donnée
}
/*
 * A COMPLETER
 */
void Mondial::printCountryBorders(string countryName) const {
    XMLElement* countryElement = racineMondial->FirstChildElement("countriescategory")->FirstChildElement("country");
    
    bool found = false;

    while (countryElement) {
        const char* nameText = countryElement->FirstChildElement("name")->GetText();
        
        if (nameText && countryName == nameText) {
            found = true;
            cout << "----------------------------------------------------------------------------------------------" << endl;
            cout << "Frontières de " << countryName << ":" << endl;

            XMLElement* borderElement = countryElement->FirstChildElement("border");
            while (borderElement) {
                const char* borderCountry = borderElement->Attribute("country");
                XMLElement* newCountryElement = getCountryXmlelementFromCode(borderCountry);

                if (newCountryElement) {
                    cout << " est frontalier avec  " << newCountryElement->FirstChildElement("name")->GetText() << ", la longueur de sa frontière avec celui-ci est de  : " << borderElement->Attribute("length") << endl;
                }
                borderElement = borderElement->NextSiblingElement("border");
            }
            break;
        }

        countryElement = countryElement->NextSiblingElement("country");
    }

    if (!found) {
        cout << "Le pays " << countryName << " n'a pas été trouvé." << endl;
    }
}

/*
 * A COMPLETER
 */
XMLElement* Mondial::getRiverXmlelementFromNameIter(string riverName) const {
    XMLElement* element = racineMondial->FirstChildElement("riverscategory")->FirstChildElement("river");
    while(element){
        if(element->FirstChildElement("name")->GetText() == riverName){
            return element;
        }
        element = element->NextSiblingElement("river");

    }
    return nullptr;
}
/*
 * A COMPLETER
 */
void Mondial::printAllCountriesCrossedByRiver(string riverName) const {
    XMLElement* riverElement = getRiverXmlelementFromNameIter(riverName);
    XMLElement* country;
    string countries = riverElement->Attribute("country");
    std::vector<string> rivers = Mondial::split(countries, ' ');

    cout << "--Pays du fleuve " << riverName << " : " << endl;

    for (size_t i = 0; i < rivers.size(); i++) {
        country = getCountryXmlelementFromCode(rivers[i]);
        cout << country->FirstChildElement("name")->GetText() << endl;
    }
    cout << endl << "La longueur du fleuve est de : " << riverElement->FirstChildElement("length")->GetText() << endl;
    cout << endl << endl;

}

/*
 * A COMPLETER
 */
void Mondial::printCountriesWithProvincesCrossedByRiver(string riverName) const {
    // Obtenir l'élément XML de la rivière par son nom
    XMLElement* riverElement = getRiverXmlelementFromNameIter(riverName);
    
    // Vérifier si l'élément de la rivière existe
    if (!riverElement) {
        cout << "La rivière '" << riverName << "' n'a pas été trouvée." << endl;
        return;
    }

    cout << "coucou";

    // Obtenir le premier élément "located" qui contient les pays
    XMLElement* locatedElement = riverElement->FirstChildElement("located");
    
    
    
    // Boucle tant qu'il y a des éléments "located"
    while (locatedElement) {
        // Récupérer le code du pays à partir du texte de l'élément "located"
        const char* countryCode = locatedElement->Attribute("country");
        
        // Vérifier si countryCode n'est pas nul
        if (countryCode) {
            // Obtenir l'élément XML du pays par son code
            XMLElement* country = getCountryXmlelementFromCode(countryCode);


            
            // Vérifier si l'élément du pays existe
            if (country) {
                // Afficher le nom du pays
                cout << country->FirstChildElement("name")->GetText() << endl;
            } else {
                cout << "Erreur : Le pays avec le code '" << countryCode << "' n'a pas été trouvé." << endl;
            }
        } else {
            cout << "Erreur : Le code du pays est nul." << endl;
        }

        // Passer à l'élément suivant "located"
        locatedElement = locatedElement->NextSiblingElement("located");
    }
        cout << riverElement->FirstChildElement("length")->GetText() << endl;
}

/*
 * A COMPLETER
 */
void Mondial::printCountriesAndProvincesCrossedByRiver(string riverName) const {
    // Retrieve the XML element for the specified river
    XMLElement* riverElement = getRiverXmlelementFromNameIter(riverName);
    
    if (riverElement == nullptr) {
        cout << "Le fleuve : " << riverName << ", n'existe pas !" << endl;
        return;
    }

    // Get the countries attribute from the river element
    string countries = riverElement->Attribute("country");
    std::vector<string> rivers = Mondial::split(countries, ' ');

    cout << "Le fleuve " << riverName 
         << " de longueur " << riverElement->FirstChildElement("length")->GetText() 
         << " traverse les pays suivants :" << endl;

    // Iterate over each country code
    for (const auto& countryCode : rivers) {
        XMLElement* country = getCountryXmlelementFromCode(countryCode);
        
        if (country) {
            cout << "   - " << country->FirstChildElement("name")->GetText() 
                 << ", où il traverse les divisions administratives suivantes :" << endl;

            // Retrieve all <located> elements related to this river
            XMLElement* divisionAdministrative = riverElement->FirstChildElement("located");
            while (divisionAdministrative) {
                // Check if the located element matches the current country code
                if (divisionAdministrative->Attribute("country") == countryCode) {
                    string provinceCodes = divisionAdministrative->Attribute("province");
                    std::vector<std::string> provinces = Mondial::split(provinceCodes, ' ');

                    // Iterate over each province code
                    for (const auto& provinceCode : provinces) {
                        XMLElement* province = country->FirstChildElement("province");
                        while (province) {
                            if (province->Attribute("id") == provinceCode) {
                                cout << "      - " << province->FirstChildElement("name")->GetText() << endl;
                                break; // Found the matching province, no need to continue
                            }
                            province = province->NextSiblingElement("province");
                        }
                    }
                }
                divisionAdministrative = divisionAdministrative->NextSiblingElement("located"); // Move to next <located> element
            }
        } else {
            cout << "Erreur : pays non trouvé pour le code " << countryCode << endl;
        }
    }
}
/*
 * A COMPLETER
 */
void Mondial::printCityInformation(string cityName) const {
    /*
     * A COMPLETER
     */
}

/**
 * Exemple de question additionnelle pour l'exercice 9 afficher toutes les informations disponibles
 * dans Mondial concernant toutes les îles.
 * On peut commencer par une île en particulier à partir de son nom
 */
void Mondial::printIslandsInformations() const {
    /*
     * A COMPLETER
     */
}

/*
 * Méthodes de service fournies
 */

template<typename Out>
void Mondial::split(string& s, char delim, Out result) const {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }
}

/**
 * Méthode à utiliser pour découper les mots d'une chaîne dans un vecteur
 * Utile pour la gestion des attributs à valeurs multiples
 * @param s chaîne à découper
 * @param delim délimiteur des mots de la chaîne à découper
 * @return vecteur contenant les mots de la chaîne découpée
 */
vector<std::string> Mondial::split(string& s, char delim) const {
    vector<std::string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}

Mondial::~Mondial() {
}
