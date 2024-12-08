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

void Mondial::printCityInformation(const string& cityName) const {

    XMLElement* country = getCityFromProvince(cityName);

    /*const XMLElement* country = racineMondial->FirstChildElement("countriescategory")->FirstChildElement("country");
    bool found = false;

    while (country && !found) {
        const XMLElement* city = country->FirstChildElement("city");
        
        while (city) {
            const XMLElement* name = city->FirstChildElement("name");
            
            while (name) {
                if (name->GetText() == cityName) {
                    found = true;
                    printCityDetails(city, country);
                    break;
                }
                name = name->NextSiblingElement("name");
            }
            
            if (found) break;
            city = city->NextSiblingElement("city");
        }
        
        if (!found) country = country->NextSiblingElement("country");
    }

    if (!found) {
        cout << "La ville " << cityName << ", n'existe pas !" << endl;
    }*/
    //printCityDetails(city, country)
}
#include <iostream>
#include <string>
#include <algorithm> // Pour std::remove_if

using namespace std;

XMLElement* Mondial::getCityFromProvince(string cityName) const {
    XMLElement* country = racineMondial->FirstChildElement("countriescategory")->FirstChildElement("country");

    while (country) {
        string countryName = country->FirstChildElement("name")->GetText();

        // Nettoyage des espaces autour du nom du pays

        countryName = deleteSpacesInWord(countryName);

        if (countryName == "France") {
            XMLElement* province = country->FirstChildElement("province");
            while (province) {
                XMLElement* city = province->FirstChildElement("city");
                string newCityName = deleteSpacesInWord(city->FirstChildElement("name")->GetText());
                while (city) {
                    // Comparez le nom de la ville avec cityName
                    if (newCityName == cityName) {
                        return city;  // Retourne le pointeur vers la ville trouvée
                    }
                    city = city->NextSiblingElement("city");  // Passe à la ville suivante
                }
                province = province->NextSiblingElement("province");  // Passe à la province suivante
            }
        }
        country = country->NextSiblingElement("country");  // Passe au pays suivant
    }

    return nullptr;  // Retourne nullptr si aucune ville n'est trouvée
}
void Mondial::printCityDetails(const XMLElement* city, const XMLElement* country) const {

    cout << "La ville " << city->FirstChildElement("name")->GetText() << endl;
    cout << " - se trouve dans le pays : " << country->FirstChildElement("name")->GetText() << endl;
    
    const XMLElement* province = city->Parent()->ToElement();
    if (province->Name() == string("province")) {
        cout << " - dans la division administrative : " << province->FirstChildElement("name")->GetText() << endl;
    }
    
    if (const XMLElement* latitude = city->FirstChildElement("latitude")) {
        cout << " - sa latitude est : " << latitude->GetText() << endl;
    }
    
    if (const XMLElement* longitude = city->FirstChildElement("longitude")) {
        cout << " - sa longitude est : " << longitude->GetText() << endl;
    }
    
    if (const XMLElement* elevation = city->FirstChildElement("elevation")) {
        cout << " - son altitude est : " << elevation->GetText() << endl;
    }
    
    if (const XMLElement* population = city->FirstChildElement("population")) {
        cout << " - sa population est : " << getCityPopulation(city) << endl;
    }

}


int Mondial::getCityPopulation(const XMLElement* city) const{

    const XMLElement* population = city->FirstChildElement("population");

    int maxYear;
    int maxPopulation;

    int actualYear;
    int actualPopulation;

    while(population){
        actualYear = stoi(population->Attribute("year"));
        actualPopulation = stoi(population->GetText());
        if(maxYear < actualYear){
            maxYear = actualYear;
            maxPopulation = actualPopulation;
        }
        population = population->NextSiblingElement("population");
    }


    
    return maxPopulation;
}


/**
 * Exemple de question additionnelle pour l'exercice 9 afficher toutes les informations disponibles
 * dans Mondial concernant toutes les îles.
 * On peut commencer par une île en particulier à partir de son nom
 */
void Mondial::printIslandsInformations() const {
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

string Mondial::deleteSpacesInWord(string word) const{
    auto endPos = std::remove_if(word.begin(), word.end(), ::isspace);
    word.erase(endPos, word.end()); // Supprimer les espaces
    return word; // Retourner la chaîne modifiée
}

/**
 * @brief Retourne un nœud correspondant à une condition avec un chemin donné.
 *
 * Cette fonction effectue une recherche récursive dans un arbre XML pour trouver 
 * un élément qui correspond à un nom spécifié. Elle prend en compte un vecteur 
 * d'éléments qui définit le chemin à parcourir dans l'arbre XML. Si l'élément 
 * correspondant est trouvé, il est retourné ; sinon, la fonction retourne null.
 *
 * @param actualElement Pointeur vers l'élément XML actuel à partir duquel 
 *                      la recherche commence. Doit être non nul.
 * @param nodeToReturn Le nom du nœud que l'on souhaite retourner si 
 *                     trouvé. Cela correspond au premier élément du vecteur 
 *                     `elements`.
 * @param elements Vecteur de chaînes représentant le chemin des éléments à 
 *                  parcourir dans l'arbre XML. Le premier élément est traité 
 *                  en premier lors de la recherche.
 * @param name Le texte que l'élément doit contenir pour être considéré comme 
 *             une correspondance valide. Si `actualElement` contient ce texte, 
 *             il sera retourné.
 *
 * @return Un pointeur vers l'élément XML correspondant si trouvé, sinon 
 *         retourne nullptr.
 *
 * @note Cette fonction utilise une recherche récursive et parcourt tous les 
 *       frères de chaque nœud jusqu'à ce qu'un élément correspondant soit trouvé.
 */
XMLElement* Mondial::getElementWithParametersGetText(XMLElement* actualElement, string nodeToReturn, std::vector<string> elements, string name) const {
    // Vérifiez si l'élément actuel est nul
    if (actualElement == nullptr) {
        return nullptr;
    }

    // Vérifiez si le vecteur elements n'est pas vide
    if (elements.empty()) {
        // Si nous sommes au dernier élément, vérifiez s'il correspond au nom recherché
        if (actualElement->GetText() && name == actualElement->GetText()) {
            return actualElement; // Retournez actualElement si le texte correspond
        }
        return nullptr; // Retournez null si aucun élément correspondant n'est trouvé
    }

    // Obtenez le nom réel de l'élément actuel
    string actual = elements[0];
    bool elementToReturn = (nodeToReturn == actual);

    // Obtenez le premier enfant avec le nom 'actual'
    XMLElement* node = actualElement->FirstChildElement(actual.c_str());

    // Supprimez le premier élément du vecteur pour la recherche récursive
    elements.erase(elements.begin());

    // Parcourez tous les frères de 'node'
    while (node) {

        // Recherche récursive pour les éléments correspondants
        XMLElement* result = getElementWithParametersGetText(node, nodeToReturn, elements, name);
        
        if (result) {
            if (elementToReturn) {
                return node;  // Retournez le nœud correspondant à nodeToReturn
            } else {
                return result; // Retournez le résultat trouvé dans la récursion
            }
        }

        node = node->NextSiblingElement(actual.c_str()); // Passez au frère suivant
    }

    return nullptr; // Retournez null si aucun élément correspondant n'est trouvé
}




/**
 * @brief Retourne un nœud correspondant à une condition avec un chemin donné.
 *
 * Cette fonction effectue une recherche récursive dans un arbre XML pour trouver 
 * un élément qui correspond à un nom spécifié. Elle prend en compte un vecteur 
 * d'éléments qui définit le chemin à parcourir dans l'arbre XML. Si l'élément 
 * correspondant est trouvé, il est retourné ; sinon, la fonction retourne null.
 *
 * @param actualElement Pointeur vers l'élément XML actuel à partir duquel 
 *                      la recherche commence. Doit être non nul.
 * @param nodeToReturn Le nom du nœud que l'on souhaite retourner si 
 *                     trouvé. Cela correspond au premier élément du vecteur 
 *                     `elements`.
 * @param elements Vecteur de chaînes représentant le chemin des éléments à 
 *                  parcourir dans l'arbre XML. Le premier élément est traité 
 *                  en premier lors de la recherche.
 * @param name Le texte que l'élément doit contenir pour être considéré comme 
 *             une correspondance valide. Si `actualElement` contient ce texte, 
 *             il sera retourné.
 *
 * @return Un pointeur vers l'élément XML correspondant si trouvé, sinon 
 *         retourne nullptr.
 *
 * @note Cette fonction utilise une recherche récursive et parcourt tous les 
 *       frères de chaque nœud jusqu'à ce qu'un élément correspondant soit trouvé.
 */
XMLElement* Mondial::getElementWithParametersAttribute(XMLElement* actualElement, string nodeToReturn, std::vector<string> elements, string name, string attribut) const {
    // Vérifiez si l'élément actuel est nul
    if (actualElement == nullptr) {
        return nullptr;
    }

    cout << "-->" << elements[0] << endl;

    // Vérifiez si le vecteur elements n'est pas vide
    if (elements.size() == 1) {
        // Si nous sommes au dernier élément, vérifiez s'il correspond au nom recherché
        if (actualElement->Attribute(attribut.c_str()) && name == actualElement->Attribute(attribut.c_str())) {
            return actualElement; // Retournez actualElement si le texte correspond
        }
        return nullptr; // Retournez null si aucun élément correspondant n'est trouvé
    }

    // Obtenez le nom réel de l'élément actuel
    string actual = elements[0];
    bool elementToReturn = (nodeToReturn == actual);

    // Obtenez le premier enfant avec le nom 'actual'
    XMLElement* node = actualElement->FirstChildElement(actual.c_str());

    // Supprimez le premier élément du vecteur pour la recherche récursive
    elements.erase(elements.begin());

    // Parcourez tous les frères de 'node'
    while (node) {

        // Recherche récursive pour les éléments correspondants
        XMLElement* result = getElementWithParametersAttribute(node, nodeToReturn, elements, name, attribut);
        
        if (result) {
            if (elementToReturn) {
                return node;  // Retournez le nœud correspondant à nodeToReturn
            } else {
                return result; // Retournez le résultat trouvé dans la récursion
            }
        }

        node = node->NextSiblingElement(actual.c_str()); // Passez au frère suivant
    }

    return nullptr; // Retournez null si aucun élément correspondant n'est trouvé
}




void Mondial::testGetElementWithParametersGetText() const {
    XMLElement* element = racineMondial->FirstChildElement("riverscategory");
    std::vector<string> elements = {"river", "source", "latitude"};

    XMLElement* river = getElementWithParametersGetText(element, "river", elements, "64.8");

    if (river) {
        river = river->FirstChildElement("name");
        if (river) {
            cout << river->GetText() << endl;
        } else {
            cout << "Le nœud 'name' est nul." << endl;
        }
    } else {
        cout << "Aucun élément 'river' trouvé." << endl;
    }

    
    element = racineMondial->FirstChildElement("countriescategory");
    elements = {"country", "province", "city", "id"};

    XMLElement* country = getElementWithParametersAttribute(element, "country", elements, "cty-Greece-9", "id");

    if (country) {
        country = country->FirstChildElement("name");
        if (country) {
            cout << country->GetText() << endl;
        } else {
            cout << "Le nœud 'name' est nul." << endl;
        }
    } else {
        cout << "Aucun élément 'country' trouvé." << endl;
    }
    
}
