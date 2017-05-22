#include "AlphaBeta.h"
#include "../include/Plateau.h"
AlphaBeta::AlphaBeta(Plateau plateau, Couleur couleur)
{
    //ctor

    m_plateau = plateau;
    m_couleur = couleur;
}

AlphaBeta::~AlphaBeta()
{
    //dtor
}

//Min
int AlphaBeta::Min_Value(Plateau state,int alpha, int beta)
{


}
//Max
int AlphaBeta::Max_Value(Plateau state,int alpha, int beta)
{


}
//Initialisation
Deplacement AlphaBeta::AlphaBetaDecision(Plateau state)
{
//if(){}
    /*
    si P est une feuille alors
       retourner la valeur de P
   sinon
       si P est un nœud Min alors
           Val = infini
           pour tout enfant Pi de P faire
               Val = Min(Val, ALPHABETA(Pi, alpha, beta))
               si alpha ≥ Val alors  /* coupure alpha
                   retourner Val
               finsi
               beta = Min(beta, Val)
           finpour
       sinon
           Val = -infini
           pour tout enfant Pi de P faire
               Val = Max(Val, ALPHABETA(Pi, alpha, beta))
               si Val ≥ beta alors /* coupure beta
                   retourner Val
               finsi
               alpha = Max(alpha, Val)
           finpour
       finsi
   retourner Val
   finsi*/

}

int Eval(Plateau plateau)
{
    int valeur;
    int c_act;
    int c_adv;
    int i,j;
    Piece[2][_NB_PIECES] pieces;

    if (m_couleur == _BLANC)
    {
        c = 0;
    }
    else
    {
        c= 1;
    }

    for (i = 0; i < 2 ; i++)
    {
        for(j = 0; j < _NB_PIECES ; j++)
        {
            pieces[i][j] = plateau::m_pieces[i][j];
        }
    }
    //[0] roi [1] tour [2] fou [3] cavalier [4} -> [7] pion
    valeur = (pieces[c_act][1]- pieces[c_adv][1] * 5
            +(pieces[c_act][2]- pieces[c_adv][2] * 3
            +(pieces[c_act][3]- pieces[c_adv][3] * 3
            +(pieces[c_act][4]- pieces[c_adv][4]
            +(pieces[c_act][5]- pieces[c_adv][5]
            +(pieces[c_act][6]- pieces[c_adv][6]
            +(pieces[c_act][7]- pieces[c_adv][7];

    return valeur;
}


