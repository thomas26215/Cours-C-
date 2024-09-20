#ifndef CONTENEUR_H
#define CONTENEUR_H

#include <vector>
#include <iostream>
#include <stdexcept>

template<class T>
class Conteneur {
public:
    Conteneur() {}
    
    Conteneur(const Conteneur & unConteneur) {
        for(const auto& element: unConteneur.contenu) {
            contenu.push_back(new T(*element));
        }
    }
    
    ~Conteneur() {
        for(auto& element : contenu) {
            delete element;
        }
        contenu.clear();
    }

    void ajouter(T* element) {
        if(element == nullptr) {
            throw std::invalid_argument("Élément invalide");
        } else {
            contenu.push_back(new T(*element));
        }
    }
    
    void afficher(std::ostream& os) const {
        for(size_t i = 0; i < contenu.size(); ++i) {
            os << "Élément " << i+1 << " : " << *contenu[i] << std::endl;
        }
    }

    Conteneur<T>& operator=(const Conteneur<T> &unConteneur) {
        if (this != &unConteneur) {
            for(auto& element : contenu) {
                delete element;
            }
            contenu.clear();
            for(const auto& element: unConteneur.contenu) {
                contenu.push_back(new T(*element));
            }
        }
        return *this;
    }

private:
    std::vector<T*> contenu;
};

#endif /* CONTENEUR_H */