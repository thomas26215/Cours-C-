#ifndef USAGER_H
#define USAGER_H

#include <string>
#include <iostream>

class Usager {
public:
    Usager(const std::string& login, const std::string& groupe);
    inline void setLogin(const std::string& newLogin){login = newLogin;}
    inline const std::string& getLogin(){return login;}
    inline void setGroupe(const std::string& newGroupe){groupe = newGroupe;}
    inline const std::string& getGroupe(){return groupe;}
    inline void afficher(){std::cout << getLogin() << " " << getGroupe();}

private:
    std::string login;
    std::string groupe;
};

#endif /* USAGER_H */

