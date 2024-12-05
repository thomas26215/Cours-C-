#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

#include "Salarie.h"

int main() {
    try {
        Salarie salarie("test", "1234567890123", 2000.0);
        salarie.saisir(std::cin);
        salarie.afficher(std::cout);
    } catch (const SalarieException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }
    return 0;

    cout << "test";
}