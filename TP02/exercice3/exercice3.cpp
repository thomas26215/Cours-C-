#include "ObjetContraint.h"
#include "Point.h"
#include <iostream>

int main() {
    try {
        ObjetContraint<int> a(5, 0, 10);
        std::cout << "a = " << a.getVal() << std::endl;

        a.setVal(7);
        std::cout << "a après setVal(7) = " << a.getVal() << std::endl;

        a.setVal(15); // Ceci devrait lever une exception
    }
    catch (char const* erreur) {
        std::cout << "Exception capturée : " << erreur << std::endl;
    }

    try {
        ObjetContraint<double> b(3.14, 0.0, 10.0);
        std::cout << "b = " << b.getVal() << std::endl;

        b.setVal(-1.0); // Ceci devrait lever une exception
    }
    catch (char const* erreur) {
        std::cout << "Exception capturée : " << erreur << std::endl;
    }

    return 0;
}

