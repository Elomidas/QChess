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

    protected:
        Plateau m_plateau;
        AffichagePlateau m_affichage;

    private:
};

#endif // JEU_H
