#include <iostream>

#include "Plateau.h"

using namespace std;

int main()
{
    Plateau p;
    p.InitialiserPieces();
    cout << p.ToStr() << endl;
    return 0;
}
