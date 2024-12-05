#ifndef SALARIEEXCEPTION_H
#define SALARIEEXCEPTION_H

#include <stdexcept>
#include <string>

// Classe de base pour toutes les exceptions liées à Salarie
class SalarieException : public std::domain_error {
public:
    SalarieException(const std::string& message) : std::domain_error(message) {}
};

// Exception spécifique pour les noms incorrects
class NomIncorrectException : public SalarieException {
public:
    NomIncorrectException(const std::string& message) : SalarieException("Nom incorrect : " + message) {}
};

// Exception spécifique pour les numéros de sécurité sociale incorrects
class NumeroIncorrectException : public SalarieException {
public:
    NumeroIncorrectException(const std::string& message) : SalarieException("Numéro de sécurité sociale incorrect : " + message) {}
};

// Exception spécifique pour les salaires incorrects
class SalaireIncorrectException : public SalarieException {
public:
    SalaireIncorrectException(const std::string& message) : SalarieException("Salaire incorrect : " + message) {}
};

#endif /* SALARIEEXCEPTION_H */