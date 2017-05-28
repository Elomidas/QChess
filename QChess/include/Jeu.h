#ifndef JEU_H
#define JEU_H

#include <SFML/System.hpp>
#include "AlphaBeta.h"
#include "Plateau.h"
#include "AffichagePlateau.h"

class Jeu
{
    public:
        Jeu();
        virtual ~Jeu();
        void Fin();
        void Jouer();
        void ModeJeu(const Couleur, const bool);
        void SetActu(const Couleur);
        int * TourIA();

    protected:
        Plateau m_plateau;
        AffichagePlateau m_affichage;
        Couleur m_actu;
        bool m_gui[2];
        bool m_continuer;
        AlphaBeta m_alphabeta, m_AB2;

    private:
};

#endif // JEU_H
