#include "gtest/gtest.h"
#include <map>
#include <iostream>
#include <string>
#include "Salarie.h"
#include "SalarieException.h"
using namespace std;

/*

    cmake ..
    make
    ./test

*/

TEST(SalarieTest, Constructeur) {
    EXPECT_THROW(Salarie("T-omas"), NomIncorrectException) << "On veut une exception sur le nom";
    EXPECT_THROW(Salarie("Thomas", "12405157286"), NumeroIncorrectException) << "On veut une exception sur le numero";
    EXPECT_THROW(Salarie("Thomas", "7418529637418", 10), SalaireIncorrectException) << "On veut une exception sur le salaire";
}

TEST(SalarieTest, GetNom) {
   Salarie salarie("Thomas");
   Salarie salarie2("Valentin");
   EXPECT_EQ(salarie.getNom(), "THOMAS");
   EXPECT_EQ(salarie2.getNom(), "VALENTIN");
}

TEST(SalarieTest, SetNom) {
    Salarie salarie("Thomas");
    EXPECT_NO_THROW(salarie.setNom("Thomas")) << "setNomm sur Thomas ne renvoie pas d'exceptions";
    EXPECT_THROW(salarie.setNom("4"), NomIncorrectException) << "Le prénom contient un chiffre dans setNom()";
    EXPECT_THROW(salarie.setNom("-Thomas"), NomIncorrectException) << "Cela devrait renvoyer un exception pour -Thomas";
    EXPECT_THROW(salarie.setNom("Tho-mas"), NomIncorrectException) << "Cela devrait renvoyer un exception pour Tho-mas";
    EXPECT_THROW(salarie.setNom(""), NomIncorrectException) << "Cela devrait renvoyer un exception pour ''";
}

TEST(SalarieTest, SetNumeroSS) {
    Salarie salarie("test", "1234567890123");
    EXPECT_THROW(salarie.setNumeroSS("123"), NumeroIncorrectException) << "NumeroSS trop petit";
    EXPECT_THROW(salarie.setNumeroSS("a125s4"), NumeroIncorrectException) << "Le numéroSS ne doit pas contenir de lettres";
    EXPECT_THROW(salarie.setNumeroSS("7418529637418529638545254"), NumeroIncorrectException) << "NumeroSS trop long";
}


TEST(SalarieTest, SetSalaire) {
    Salarie salarie("Thomas");
    EXPECT_THROW(salarie.setSalaireMensuel(10), SalaireIncorrectException) << "Le salaire est trop petit";
    EXPECT_THROW(salarie.setSalaireMensuel(1500000), SalaireIncorrectException) << "Le salaire est trop grand";
}

TEST(SalarieTest, GetImpot) {
    Salarie salarie("Thomas");

    salarie.setSalaireMensuel(1257.0f);
    ASSERT_EQ(salarie.getImpot(), 1257.0f*12*0.140f) << "Les impôts devraient être 0 pour un revenu mensuel de 500 euros";
    salarie.setSalaireMensuel(26600.0f/12.0f);
    ASSERT_EQ(salarie.getImpot(), 3724) << "Les impôts devraient être 3724 pour un revenu annuel de 26200 euros";
    salarie.setSalaireMensuel(71400.0f/12);
    ASSERT_EQ(salarie.getImpot(), 71400.0f*0.300) << "Les impôts ne sont pas corrects pour un revenu mensuel de 5000 euros";
    salarie.setSalaireMensuel(151200.0f / 12);
    ASSERT_EQ(salarie.getImpot(), 61992) << "Les impôts ne sont pas corrects pour un revenu mensuel de 2216.67 euros";
    
}
