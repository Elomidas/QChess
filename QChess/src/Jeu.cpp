#include "Jeu.h"
#include <iostream>
#include "../include/AlphaBeta.h"
Jeu::Jeu() : m_plateau(), m_affichage(), m_alphabeta(m_plateau,_BLANC)
{
    std::cout<<"Couleur de m_alphabeta C0 " << m_alphabeta.Getcouleur()<<std::endl;
    m_affichage.SetPlateau(&m_plateau);
    std::cout<<"Couleur de m_alphabeta C1 " << m_alphabeta.Getcouleur()<<std::endl;
    //Les blancs jouent en premier
    m_affichage.SetCouleur(_NOIR);
    std::cout<<"Couleur de m_alphabeta C2 " << m_alphabeta.Getcouleur()<<std::endl;
    //Les couleurs sont jouées par l'humain (true) ou l'IA (false)
    ModeJeu(_NOIR, true);
    ModeJeu(_BLANC, false);
    SetActu(_BLANC);
    m_continuer = true;

    std::cout << "Couleur envoyée C3 " <<_BLANC <<std::endl;
    std::cout<<"Couleur de m_alphabeta C4 " << m_alphabeta.Getcouleur()<<std::endl;
}

Jeu::~Jeu()
{
    //dtor
}

void Jeu::Fin()
{
    //
}

void Jeu::ModeJeu(const Couleur couleur, const bool gui)
{
    std::cout<<"Couleur de m_alphabeta C5 " << m_alphabeta.Getcouleur()<<std::endl;
    m_gui[couleur] = gui;
    m_affichage.SetActif(couleur, gui);
}

void Jeu::SetActu(const Couleur c)
{
    std::cout<<"Couleur de m_alphabeta C6 " << m_alphabeta.Getcouleur()<<std::endl;
    m_actu = c;
    m_affichage.SetCouleur(c);
}

void Jeu::Jouer()
{
    std::cout<<"Couleur de m_alphabeta C7 " << m_alphabeta.Getcouleur()<<std::endl;
    while(m_continuer && m_affichage.Open())
    {
        if(m_gui[m_actu])
        {
            if(m_affichage.Event())
                SetActu((Couleur)(1 - m_actu));
        }
        else
        {
            //Tour de l'IA
            //std::cout<<"Couleur de m_alphabeta C8 " << m_alphabeta.Getcouleur()<<std::endl;
            int * movementIA = m_alphabeta.ABMinMax(m_plateau);
            m_alphabeta.VerifAssertMove(movementIA,"CoteJeu");
            m_plateau.Bouger(m_actu,movementIA[2],movementIA[0],movementIA[1]);
            //On repasse la main à l'adversaire
            SetActu((Couleur)(1 - m_actu));
        }
    }
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

