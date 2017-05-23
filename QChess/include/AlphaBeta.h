#ifndef ALPHABETA_H
#define ALPHABETA_H

#include "Piece.h"
#include "Plateau.h"

#define _NB_PIECES  12
#define    _PROF    5

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
        //renvoie le mouvement optimal : tab[3] = {index piece, x,y}
        int * AlphaBetaDecision(Plateau state);

        int Eval(Plateau * plateau);

        bool TestFinal(Plateau plateau);

        int* ABMinMax(Plateau* plateau);
        int* ABMaxMove(Plateau* plateau, short int prof, int a, int b, int * move_env);
        int* ABMinMove(Plateau* plateau, short int prof, int a, int b, int * move_env);
    protected:

    private:
        Plateau m_plateau;
        Couleur m_couleur;
        bool m_gagne;
};

#endif // ALPHABETA_H
