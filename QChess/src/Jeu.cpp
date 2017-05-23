#include "Jeu.h"
#include <iostream>
#include "../include/AlphaBeta.h"
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
    /*AlphaBeta al = AlphaBeta(m_plateau,_NOIR);
    int b = al.Eval(&m_plateau);
    std::cout << b;*/
}

