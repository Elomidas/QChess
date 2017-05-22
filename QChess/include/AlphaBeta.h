#ifndef ALPHABETA_H
#define ALPHABETA_H

#include "Plateau.h"

#define _NB_PIECES  12

class AlphaBeta
{
    public:
        AlphaBeta(Plateau plateau, Couleur couleur);
        virtual ~AlphaBeta();

        Plateau Getplateau() { return m_plateau; }
        void Setplateau(Plateau val) { m_plateau = val; }

        //Min
        int Min_Value(Plateau state,int alpha, int beta);
        //Max
        int Max_Value(Plateau state,int alpha, int beta);
        //Initialisation
        Deplacement AlphaBetaDecision(Plateau state);

        int Eval(Plateau plateau);
    protected:

    private:
        Plateau m_plateau;
        Couleur m_couleur;
};

#endif // ALPHABETA_H
