#include "Jeu.h"
#include <iostream>
Jeu::Jeu() : m_plateau(), m_affichage()
{
    m_affichage.SetPlateau(&m_plateau);
    m_affichage.SetCouleur(_NOIR);
    m_affichage.ActiverJeu();
}

Jeu::~Jeu()
{
    //dtor
}

void Jeu::Fin()
{
    m_affichage.Event();
}

void Jeu::Jouer()
{
    //
}
