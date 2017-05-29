#include "Jeu.h"
#include <iostream>
#include "../include/AlphaBeta.h"
Jeu::Jeu() : m_plateau(), m_affichage(), m_alphabeta(m_plateau,_BLANC), m_AB2(m_plateau, _NOIR)
{
    m_affichage.SetPlateau(&m_plateau);
    //Les couleurs sont jouées par l'humain (true) ou l'IA (false)
    ModeJeu(_NOIR, false);
    ModeJeu(_BLANC, false);
    //Choix de la couleur qui commence
    SetActu(_BLANC);
    m_continuer = true;
}

Jeu::~Jeu()
{
    //dtor
}

void Jeu::Fin()
{
    bool bl = (m_plateau.GetPieceI(_BLANC, 0) != NULL);
    bool bn = (m_plateau.GetPieceI(_NOIR, 0) != NULL);
    if(bl && bn)
        std::cout << "Egalite" << std::endl;
    else std::cout << "Les " << (bl ? "blanc" : "noir") << "s ont gagnes !" << std::endl;
}

void Jeu::ModeJeu(const Couleur couleur, const bool gui)
{
    m_gui[couleur] = gui;
    m_affichage.SetActif(couleur, gui);
}

void Jeu::SetActu(const Couleur c)
{
    m_actu = c;
    m_affichage.SetCouleur(c);
}

void Jeu::Jouer()
{
    while(m_continuer && m_affichage.Open() && !m_plateau.Fin())
    {
        if(m_gui[m_actu])
        {
            if(m_affichage.Event())
                SetActu((Couleur)(1 - m_actu));
        }
        else
        {
            m_affichage.Event();
            if(m_affichage.Open())
            {
                //Tour de l'IA
                int movementIA[3];
                AlphaBeta * algo = NULL;
                if(m_actu == _BLANC)
                    algo = &m_alphabeta;
                else algo = &m_AB2;
                algo->ABMinMax(m_plateau,movementIA);
                algo->VerifAssertMove(movementIA,"CoteJeu");
                std::cout << "Mouvement : " << movementIA[2] << ", " << movementIA[0] << ", " << movementIA[1] << std::endl;
                m_plateau.Bouger(m_actu, movementIA[2], movementIA[0], movementIA[1]);
                //On repasse la main à l'adversaire
                SetActu((Couleur)(1 - m_actu));
                m_plateau.Reset();
                sf::sleep(sf::milliseconds(200));
            }
        }
    }
    m_affichage.Event();
    sf::sleep(sf::milliseconds(600));
}

