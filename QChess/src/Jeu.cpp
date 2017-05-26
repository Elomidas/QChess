#include "Jeu.h"
#include <iostream>
#include "../include/AlphaBeta.h"
Jeu::Jeu() : m_plateau(), m_affichage()
{
    m_affichage.SetPlateau(&m_plateau);

    //Les blancs jouent en premier
    m_affichage.SetCouleur(_NOIR);
    //Les deux couleurs sont jouées par l'humain
    m_affichage.SetActif(_NOIR, true);
    m_affichage.SetActif(_BLANC, false);

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
    std::cout <<" \n\n" <<b;*/
}

