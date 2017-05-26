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


    AlphaBeta m_alphabeta(m_plateau,_BLANC);



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

int * Jeu::TourIA()
{
    int * moveAB = m_alphabeta.ABMinMax(m_plateau);
    assert(moveAB!= NULL);

    assert(moveAB[0] >= 0);
    assert(moveAB[0] < 8);
    assert(moveAB[1] >= 0);
    assert(moveAB[1] < 8);
    return moveAB;

}

