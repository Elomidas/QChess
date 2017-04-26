#include <iostream>

#include "Jeu.h"

using namespace std;

void Ech();

int main()
{
    Jeu j;
    j.Fin();
    return 0;
}
/*
void Ech()
{
    sf::Image iBl, iNo, ech;
    ech.create(8 * _TAILLE_CASE, 8 * _TAILLE_CASE);
    iBl.loadFromFile("img/marbre_b.jpg");
    iNo.loadFromFile("img/marbre_n.jpg");
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(((i + j) % 2) == 0)
            {
                //Blanc
                for(int x = 0; x < _TAILLE_CASE; x++)
                {
                    for(int y = 0; y < _TAILLE_CASE; y++)
                    {
                        ech.setPixel((_TAILLE_CASE * i) + x, (_TAILLE_CASE * j) + y, iBl.getPixel((_TAILLE_CASE * i) + x, (_TAILLE_CASE * j) + y));
                    }
                }
            }
            else
            {
                for(int x = 0; x < _TAILLE_CASE; x++)
                {
                    for(int y = 0; y < _TAILLE_CASE; y++)
                    {
                        ech.setPixel((_TAILLE_CASE * i) + x, (_TAILLE_CASE * j) + y, iNo.getPixel((_TAILLE_CASE * i) + x, (_TAILLE_CASE * j) + y));
                    }
                }
            }
        }
    }
    //Enregistrement
    ech.saveToFile("img/plateau.jpg");
}
*/
