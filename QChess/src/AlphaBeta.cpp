#include <math.h> // std::max
#include "../include/Plateau.h"
#include "../include/Piece.h"
#include "AlphaBeta.h"


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
int AlphaBeta::Min_Value(Plateau plateau, int alpha, int beta)
{
    int valeur;
    if (TestFinal(plateau))
    {
        return Eval(plateau);
    }
    valeur = 0;
    for(int i = 0; i <5; i++)
    {
        valeur = max(valeur,Min_Value(plateau, alpha, beta));
        if (valeur >= beta)
            return valeur;
        alpha = max(alpha, valeur);
    }
    return valeur;

}
//Max
int AlphaBeta::Max_Value(Plateau plateau,int alpha, int beta)
{
    int valeur;
    if (TestFinal(plateau))
    {
        return Eval(plateau);
    }
    valeur = 0;
    for(int i = 0; i <5; i++)
    {
        valeur = max(valeur,Min_Value(plateau, alpha, beta));
        if (valeur >= beta)
            return valeur;
        alpha = max(alpha, valeur);
    }
    return valeur;
}
//Initialisation
Deplacement AlphaBeta::AlphaBetaDecision(Plateau plateau)
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

int AlphaBeta::Eval(Plateau plateau)
{
    int valeur;
    int c_act;
    int c_adv;
    int i,j;
    Piece*  pieces[2][_NB_PIECES];

    if (m_couleur == _BLANC)
    {
        c_act = 0;
        c_adv = 1;
    }
    else
    {
        c_act = 1;
        c_adv = 1;
    }

    for (i = 0; i < 2 ; i++)
    {
        for(j = 0; j < _NB_PIECES ; j++)
        {
            pieces[i][j] = plateau.GetPiece(m_couleur,j);
        }
    }
    //[0] roi [1] tour [2] fou [3] cavalier [4} -> [7] pion
    valeur = (pieces[c_act][1]- pieces[c_adv][1]) * 5
            +(pieces[c_act][2]- pieces[c_adv][2]) * 3
            +(pieces[c_act][3]- pieces[c_adv][3]) * 3
            +(pieces[c_act][4]- pieces[c_adv][4])
            +(pieces[c_act][5]- pieces[c_adv][5])
            +(pieces[c_act][6]- pieces[c_adv][6])
            +(pieces[c_act][7]- pieces[c_adv][7]);

    if (pieces[c_act][i] != 0)
    {
        if(pieces[c_adv][i] == 0)
            switch(i)
                {
                    case 1:
                        valeur += 5;
                    break;

                    case 2:
                        valeur += 3;
                    break;

                    case 3:
                        valeur += 3;
                    break;

                    default:
                        valeur += 1;
                }
    }
    else
    {
        if(pieces[c_adv][i] != 0)
            switch(i)
            {
                case 1:
                    valeur -=  5;
                break;

                case 2:
                    valeur -=  3;
                break;

                case 3:
                    valeur -=  3;
                break;

                default:
                    valeur -= 1;
            }

    }
    return valeur;
}

bool AlphaBeta::TestFinal(Plateau plateau)
{
    bool termine;

    //test de finission du jeu dans la configuration n

    return termine;
}




