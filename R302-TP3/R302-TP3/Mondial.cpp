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
#include <algorithm>

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

XMLElement* Mondial::getCountryXmlelementFromNameRec(string countryName) const {
    XMLElement* element = racineMondial->FirstChildElement("countriescategory")->FirstChildElement();
    

   
   return getCountryXmlelementFromNameRecWorker(element,  countryName); 
}


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

void Mondial::printCountryBorders(string countryName) const {
    XMLElement* countryElement = racineMondial->FirstChildElement("countriescategory")->FirstChildElement("country");
    
    while (countryElement) {
        XMLElement* nameElement = countryElement->FirstChildElement("name");
        if (nameElement && nameElement->GetText() == countryName) {
            XMLElement* borderElement = countryElement->FirstChildElement("border");

            if (!borderElement) {
                cout << "Le pays : " << countryName << ", n'a pas de pays frontalier !" << endl;
                return;
            }

            cout << "Le pays : " << countryName << endl;

            while (borderElement) {
                const char* borderCountry = borderElement->Attribute("country");
                XMLElement* newCountryElement = getCountryXmlelementFromCode(borderCountry);

                if (newCountryElement) {
                    const char* borderName = newCountryElement->FirstChildElement("name")->GetText();
                    const char* borderLength = borderElement->Attribute("length");
                    cout << " est frontalier avec : " << borderName 
                         << ", la longueur de sa frontière avec celui-ci est de : " << borderLength << endl;
                }
                borderElement = borderElement->NextSiblingElement("border");
            }
            return;
        }
        countryElement = countryElement->NextSiblingElement("country");
    }

    cout << "Le pays " << countryName << " n'a pas été trouvé." << endl;
}



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

void Mondial::printAllCountriesCrossedByRiver(string riverName) const {
    XMLElement* riverElement = getRiverXmlelementFromNameIter(riverName);
    XMLElement* country;
    string countries = riverElement->Attribute("country");
    std::vector<string> rivers = Mondial::split(countries, ' ');

    cout << "Le fleuve : " << riverName << endl << " traverse les pays suivants : ";

    for (size_t i = 0; i < rivers.size(); i++) {
        country = getCountryXmlelementFromCode(rivers[i]);
        cout << country->FirstChildElement("name")->GetText();
        if(rivers.size()-1 != i){
            cout << ", ";
        }
    }
    cout << " ; Il a la longueur suivante : " << riverElement->FirstChildElement("length")->GetText() << endl;
    cout << endl << endl;

}


void Mondial::printCountriesWithProvincesCrossedByRiver(string riverName) const {
    XMLElement* riverElement = getRiverXmlelementFromNameIter(riverName);
    
    if (!riverElement) {
        cout << "Le fleuve : " << riverName << ", n'existe pas !" << endl;
        return;
    }

    cout << "Le fleuve : " << riverName << endl;
    cout << " traverse les pays suivants : ";

    XMLElement* locatedElement = riverElement->FirstChildElement("located");
    bool firstCountry = true;
    
    while (locatedElement) {
        const char* countryCode = locatedElement->Attribute("country");
        
        if (countryCode) {
            XMLElement* country = getCountryXmlelementFromCode(countryCode);
            
            if (country) {
                if (!firstCountry) {
                    cout << ", ";
                }
                cout << country->FirstChildElement("name")->GetText();
                firstCountry = false;
            }
        }

        locatedElement = locatedElement->NextSiblingElement("located");
    }

    cout << " ; il a la longueur suivante : " << riverElement->FirstChildElement("length")->GetText() << endl;
}


void Mondial::printCountriesAndProvincesCrossedByRiver(string riverName) const {
    XMLElement* riverElement = getRiverXmlelementFromNameIter(riverName);
    
    if (riverElement == nullptr) {
        cout << "Le fleuve : " << riverName << ", n'existe pas !" << endl;
        return;
    }

    string countries = riverElement->Attribute("country");
    std::vector<string> rivers = Mondial::split(countries, ' ');

    cout << "Le fleuve " << riverName 
         << " de longueur " << riverElement->FirstChildElement("length")->GetText() 
         << " traverse les pays suivants :" << endl;

    for (const auto& countryCode : rivers) {
        XMLElement* country = getCountryXmlelementFromCode(countryCode);
        
        if (country) {
            cout << "   - " << country->FirstChildElement("name")->GetText() 
                 << ", où il traverse les divisions administratives suivantes :" << endl;

            XMLElement* divisionAdministrative = riverElement->FirstChildElement("located");
            while (divisionAdministrative) {
                if (divisionAdministrative->Attribute("country") == countryCode) {
                    string provinceCodes = divisionAdministrative->Attribute("province");
                    std::vector<std::string> provinces = Mondial::split(provinceCodes, ' ');

                    for (const auto& provinceCode : provinces) {
                        XMLElement* province = country->FirstChildElement("province");
                        while (province) {
                            if (province->Attribute("id") == provinceCode) {
                                cout << "      * " << province->FirstChildElement("name")->GetText() << endl;
                                break;                             }
                            province = province->NextSiblingElement("province");
                        }
                    }
                }
                divisionAdministrative = divisionAdministrative->NextSiblingElement("located");            }
        } else {
            cout << "Erreur : pays non trouvé pour le code " << countryCode << endl;
        }
    }
}


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
                    // Comparer le nom de la ville avec cityName
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

void Mondial::printCityInformation(const std::string& cityName) const {
    const XMLElement* country = racineMondial->FirstChildElement("countriescategory")->FirstChildElement("country");
    bool found = false;

    while (country && !found) {
        // Recherche dans country->city->name
        const XMLElement* cityDirect = country->FirstChildElement("city");
        while (cityDirect && !found) {
            const XMLElement* nameDirect = cityDirect->FirstChildElement("name");
            if (nameDirect && nameDirect->GetText() == cityName) {
                found = true;
                printCityDetails(cityDirect, country);
                break;
            }
            cityDirect = cityDirect->NextSiblingElement("city");
        }

        // Recherche dans country->province->city->name
        if (!found) {
            const XMLElement* province = country->FirstChildElement("province");
            while (province && !found) {
                const XMLElement* city = province->FirstChildElement("city");
                while (city && !found) {
                    const XMLElement* name = city->FirstChildElement("name");
                    if (name && name->GetText() == cityName) {
                        found = true;
                        printCityDetails(city, country);
                        break;
                    }
                    city = city->NextSiblingElement("city");
                }
                province = province->NextSiblingElement("province");
            }
        }

        if (!found) {
            country = country->NextSiblingElement("country");
        }
    }

    if (!found) {
        std::cout << "La ville " << cityName << " n'existe pas !" << std::endl;
    }
}

void Mondial::printCityDetails(const XMLElement* city, const XMLElement* country) const {
    std::cout << "La ville " << city->FirstChildElement("name")->GetText() << std::endl;
    std::cout << " - se trouve dans le pays : " << country->FirstChildElement("name")->GetText() << std::endl;

    const XMLElement* province = city->Parent()->ToElement();
    if (province && province->Name() == std::string("province")) {
        std::cout << " - dans la division administrative : " << province->FirstChildElement("name")->GetText() << std::endl;
    }

    if (const XMLElement* latitude = city->FirstChildElement("latitude")) {
        std::cout << " - sa latitude est : " << latitude->GetText() << std::endl;
    }

    if (const XMLElement* longitude = city->FirstChildElement("longitude")) {
        std::cout << " - sa longitude est : " << longitude->GetText() << std::endl;
    }

    if (const XMLElement* elevation = city->FirstChildElement("elevation")) {
        std::cout << " - son altitude est : " << elevation->GetText() << std::endl;
    }

    if (const XMLElement* population = city->FirstChildElement("population")) {
        std::cout << " - sa population est : " << getCityPopulation(city) << std::endl;
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


XMLElement* Mondial::getElementWithParametersGetText(XMLElement* actualElement, string nodeToReturn, std::vector<string> elements, string name, int actualNode) const {

    

    // Vérifier si l'élément actuel est nul
    if (actualElement == nullptr) {
        return nullptr;
    } 
    // Vérifier si le vecteur elements n'est pas vide
    if (actualNode == elements.size()) {
        // Si nous sommes au dernier élément, vérifier s'il correspond au nom recherché
        if (actualElement->GetText() && name == actualElement->GetText()) {
            return actualElement; // Retournez actualElement si le texte correspond
        }
        return nullptr; // Retourner null si aucun élément correspondant n'est trouvé
    }

    // Obtenir le nom réel de l'élément actuel
    string actual = elements[actualNode];

    // Obtenir le premier enfant avec le nom 'actual'
    XMLElement* node = actualElement->FirstChildElement(actual.c_str());


    // Parcourir tous les frères de 'node'
    while (node) {

        // Recherche récursive pour les éléments correspondants
        XMLElement* result = getElementWithParametersGetText(node, nodeToReturn, elements, name, actualNode+1);
        
        if (result) {
            if (elements[actualNode] == nodeToReturn) {
                return node;  // Retourner le nœud correspondant à nodeToReturn
            }
            std::vector<string> noeuds = split(nodeToReturn, '-');
            if(noeuds[0] == elements[actualNode]){
                for (size_t i = 1; i < noeuds.size(); ++i) {
                    if(node == nullptr){
                        return result;
                    }
                    node = node->FirstChildElement(noeuds[i].c_str());
                }
                if(node == nullptr){
                    return result;
                }else{
                    return node;
                }
            }else{
                return result;
            }
            return result; // Retourner le résultat trouvé dans la récursion
        
        }

        node = node->NextSiblingElement(actual.c_str()); // Passer au frère suivant
    }

    return nullptr; // Retourner null si aucun élément correspondant n'est trouvé
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
    // Vérifier si l'élément actuel est nul
    if (actualElement == nullptr) {
        return nullptr;
    }


    // Vérifier si le vecteur elements n'est pas vide
    if (elements.size() == 1) {
        // Si nous sommes au dernier élément, vérifier s'il correspond au nom recherché
        if (actualElement->Attribute(attribut.c_str()) && name == actualElement->Attribute(attribut.c_str())) {
            return actualElement; // Retourner actualElement si le texte correspond
        }
        return nullptr; // Retourner null si aucun élément correspondant n'est trouvé
    }

    // Obtenir le nom réel de l'élément actuel
    string actual = elements[0];
    bool elementToReturn = (nodeToReturn == actual);

    // Obtenir le premier enfant avec le nom 'actual'
    XMLElement* node = actualElement->FirstChildElement(actual.c_str());

    // Supprimer le premier élément du vecteur pour la recherche récursive
    elements.erase(elements.begin());

    // Parcourir tous les frères de 'node'
    while (node) {

        // Recherche récursive pour les éléments correspondants
        XMLElement* result = getElementWithParametersAttribute(node, nodeToReturn, elements, name, attribut);
        
        if (result) {
            if (elementToReturn) {
                return node;  // Retourner le nœud correspondant à nodeToReturn
            } else {
                return result; // Retourner le résultat trouvé dans la récursion
            }
        }

        node = node->NextSiblingElement(actual.c_str()); // Passer au frère suivant
    }

    return nullptr; // Retourner null si aucun élément correspondant n'est trouvé
}




void Mondial::testGetElementWithParametersGetText() const {
    // Étape 1: Récupération de l'élément racine pour les rivières
    XMLElement* element = racineMondial->FirstChildElement("riverscategory");
    std::vector<string> elements = {"river", "estuary", "longitude"};

    // Étape 2: Recherche d'un élément 'river' avec des paramètres spécifiques
    cout << "Recherche de l'élément 'river-area' dans 'riverscategory' avec les éléments : ";
    for (const auto& el : elements) {
        cout << el << " ";
    }
    cout << "et la valeur '-0.69'." << endl;

    XMLElement* river = getElementWithParametersGetText(element, "river-area", elements, "-0.69");

    // Étape 3: Vérification du résultat de la recherche de l'élément 'river'
    if (river) {
        cout << "Élément 'river' trouvé : " << river->GetText() << endl;
    } else {
        cout << "Aucun élément 'river' trouvé." << endl;
    }

    // Étape 4: Récupération de l'élément racine pour les pays
    element = racineMondial->FirstChildElement("countriescategory");
    elements = {"country", "province", "city", "id"};

    // Étape 5: Recherche d'un élément 'country' avec des paramètres spécifiques
    cout << "Recherche de l'élément 'country' dans 'countriescategory' avec les éléments : ";
    for (const auto& el : elements) {
        cout << el << " ";
    }
    cout << "et l'identifiant 'cty-Greece-9'." << endl;

    XMLElement* country = getElementWithParametersAttribute(element, "country", elements, "cty-Greece-9", "id");

    // Étape 6: Vérification du résultat de la recherche de l'élément 'country'
    if (country) {
        XMLElement* nameNode = country->FirstChildElement("name");
        if (nameNode) {
            cout << "Nom du pays trouvé : " << nameNode->GetText() << endl;
        } else {
            cout << "Le nœud 'name' est nul dans l'élément 'country'." << endl;
        }
    } else {
        cout << "Aucun élément 'country' trouvé." << endl;
    }
}

