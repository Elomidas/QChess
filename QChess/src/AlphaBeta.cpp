#include <math.h> // std::max
#include "../include/Plateau.h"
#include "../include/Piece.h"
#include "AlphaBeta.h"
#include "algorithm"

AlphaBeta::AlphaBeta()
{
    //ctor

   // m_plateau = NULL;
   // m_couleur = NULL;
   m_couleur = _NOIR;
}

AlphaBeta::AlphaBeta(Plateau &plateau, Couleur couleur) : m_plateau(plateau)
{
    //ctor
    std::cout <<"Couleur rentree dans le constructeur : " << couleur <<std::endl;
    m_couleur = couleur;
    std::cout<<"Couleur de m_alphabeta fin constructeur Alphabeta: " << Getcouleur() <<std::endl;
}

AlphaBeta::~AlphaBeta()
{
    //dtor
}

void AlphaBeta::VerifAssertMove(int * moveAB, std::string titre)
{
    assert(moveAB!= NULL);
    std::cout << titre <<std::endl;
    std::cout <<"ligne : "<<moveAB[0] <<std::endl;
    std::cout <<"colonne : "<<moveAB[1] <<std::endl;
    std::cout <<"Index : " <<moveAB[2] <<std::endl;
    assert(moveAB[0] >= 0);
    assert(moveAB[0] < 8);
    assert(moveAB[1] >= 0);
    assert(moveAB[1] < 8);
    assert(moveAB[2] >= 0);
    assert(moveAB[2] < 12 );

}

int AlphaBeta::Eval(Plateau * plateau, Couleur couleur)
{
    int valeur=0;
    Couleur c_act = couleur;
    Couleur c_adv ;

    std::cout<< "\n \n Debut Eval: " <<std::endl;

    if(c_act == _BLANC)
        c_adv = _NOIR;
    else
        c_adv = _BLANC;

    int i,j;
    Piece *  pieces[2][_NB_PIECES];
    //On recupere toutes les pieces du tableau et on mets un boolean selon leur existence dans deux lignes distinctes suivant la couleur;
    //[0] roi, [1] tour, [2] fou, [3] cavalier, [4} -> [7] pion.
    plateau->GetPieces(pieces);
    //On traite chaque type de piece un par un et on calcule la différence entre les pieces de la couleur actuelle(c_act)
    // avec celles de l'adversaire(c_adv)
    for (j = 1; j < _NB_PIECES; j++)
    {
        //std::cout<<"\n indice : " << j <<" : \n";
        assert(c_act >= 0);
        assert(c_act < 2);
        assert(c_adv >= 0);
        assert(c_adv < 2);
        //Si la j ème piece existe chez la couleur actuelle
        if (pieces[c_act][j] != NULL)
        {
            //Si la j ème piece n'existe pas chez la couleur adversaire -> on gagne des points d'évaluation
            if(pieces[c_adv][j] == NULL)
            {
                switch(j)
                {
                    //cas roi couleur actuelle
                    case 0:
                        //std::cout<<"+30";
                        valeur += 30;
                    break;
                    //cas tour couleur actuelle
                    case 1:
                        //std::cout<<"+5";
                        valeur += 5;
                    break;
                    //cas fou couleur actuelle
                    case 2:
                        //std::cout<<"+3";
                        valeur += 3;
                    break;
                    //cas cavalier couleur actuelle
                    case 3:
                        //std::cout<<"+3";
                        valeur += 3;
                    break;
                    //cas pions couleur actuelle
                    default:
                        //std::cout<<"+1";
                        valeur += 1;
                }
            }
        }
        //Si la j ème piece n'existe pas chez la couleur actuelle
        else
        {
            //Mais la jème piece existe chez l'adversaire --> On perd des points d'évaluation
            if(&pieces[c_adv][j] != NULL)
                switch(j)
                {
                    //cas roi adverse
                    case 0:
                        //std::cout<<"-30";
                        valeur -=  30;
                    //cas tour adverse
                    case 1:
                        //std::cout<<"-5";
                        valeur -=  5;
                    break;
                    //cas fou adverse
                    case 2:
                        //std::cout<<"-3";
                        valeur -=  3;
                    break;
                    //cas cavalier adverse
                    case 3:
                        //std::cout<<"-3";
                        valeur -=  3;
                    break;
                    //cas pion adverses
                    default:
                        //std::cout<<"-1";
                        valeur -= 1;
                }

        }
    }

    std::cout << "Valeur sorti du Eval : " << valeur <<"\n"<<std::endl;
    return valeur;
}

int AlphaBeta::AlphaBetaMax(Plateau plateau, int alpha, int beta, int prof, Couleur couleur ) {
    int score;
    std::vector<int*> deplacements;
    if ( prof >= _PROF )
        return Eval(&plateau,(Couleur) (_NOIR - couleur));
    for (int index = 0;index<_NB_PIECES; index++)
    {
        std::cout <<"Piece : " <<index <<std::endl;
        //on stocke ses deplacements possibles
        deplacements = (plateau.GetPiece(couleur,index))->GetDeplacements(plateau);

        for (std::vector<int*>::iterator i = deplacements.begin(); i != deplacements.end(); i++)
        {


            score = AlphaBetaMin(plateau, alpha, beta, prof + 1 ,(Couleur) (_NOIR - couleur));
            if( score >= beta )
               return beta;   // fail hard beta-cutoff
            if( score > alpha )
               alpha = score; // alpha acts like max in MiniMax
        }
   }
   return alpha;
}

int AlphaBeta::AlphaBetaMin(Plateau plateau, int alpha, int beta, int prof, Couleur couleur )  {
    int score;
    std::vector<int*> deplacements;
    if ( prof >=_PROF )
        return Eval(&plateau,(Couleur) (_NOIR - couleur));
    for (int index = 0;index<_NB_PIECES; index++)
    {
        std::cout <<"Piece : " <<index <<std::endl;

        //on stocke ses deplacements possibles
        deplacements = (plateau.GetPiece(couleur,index))->GetDeplacements(plateau);

        for (std::vector<int*>::iterator i = deplacements.begin(); i != deplacements.end(); i++)
        {
            score = AlphaBetaMax( plateau, alpha, beta, prof - 1 ,(Couleur) (_NOIR - couleur));
            if( score <= alpha )
                return alpha; // fail hard alpha-cutoff
            if( score < beta )
                beta = score; // beta acts like min in MiniMax
        }
    }
    return beta;
}

int* AlphaBeta::AlphaBetaBigMax(Plateau plateau,int alpha, int beta, int prof, Couleur couleur)
{
    int score;
    int score_temp;
    int first_movement[3];
    first_movement[0] = 0;
    first_movement[1] = 0;
    first_movement[2] = 0;
    std::vector<int*> deplacements;

    for (int index = 0;index<_NB_PIECES; index++)
    {
        std::cout <<"Piece : " <<index <<std::endl;
        //on stocke ses deplacements possibles
        deplacements = (plateau.GetPiece(couleur,index))->GetDeplacements(plateau);

        for (std::vector<int*>::iterator i = deplacements.begin(); i != deplacements.end(); i++)
        {


            score_temp = AlphaBetaMin(plateau, alpha, beta, prof + 1 ,(Couleur) (_NOIR - couleur));
            if (score <score_temp)
            {
                score = score_temp;
                first_movement[0] = (*i)[0];
                first_movement[1] = (*i)[1];
                first_movement[2] = index;
                VerifAssertMove(first_movement,"first_movement");
            }
        }
    }

    return first_movement;
}

int* AlphaBeta::ABMinMax(Plateau plateau) {


    std::cout <<"Rentre dans ABMinMax \n\n\n";
	return AlphaBetaBigMax(plateau, -100, +100, 1,m_couleur);

}
