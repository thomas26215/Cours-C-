#include <cstdlib>
#include <iostream>
#include "EntierContraint.h"
using namespace std;

int main(int argc, char** argv) {
    
    try{
        EntierContraint entier(10, 1, 20);

        cout << entier << endl;
        entier.saisir();s
        cin >> entier;
        

    }catch(char const* erreur){
        cout << "erreur";
    }
    return 0;
}

