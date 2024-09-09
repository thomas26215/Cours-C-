#ifndef POINT_H
#define POINT_H

#include <string>
#include <iostream>

class Point {
public:
    Point();
    Point(const std::string &name, int x, int y);  
    ~Point();
    const std::string& getNom() const;
    void setNom(const std::string &nom);  
    void saisirEntree(std::istream& entree = std::cin);
    void afficher(std::ostream& sortie = std::cout) const;
    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);

private:
    std::string nom; 
    int x;
    int y;
    static const std::string NOM_DEF;
    static const int X_DEF = 0;
    static const int Y_DEF = 0;
};

#endif