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

    m_couleur = couleur;

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

int AlphaBeta::Eval(Plateau plateau, Couleur couleur)
{
    int valeur=0;
    Couleur c_act = couleur;

    std::cout<< "\n \n Debut Eval: " <<std::endl;

    int i,j;
    Piece *  pieces[2][_NB_PIECES];
    //On recupere toutes les pieces du tableau et on mets un boolean selon leur existence dans deux lignes distinctes suivant la couleur;
    //[0] roi, [1] tour, [2] fou, [3] cavalier, [4} -> [7] pion.
    plateau.GetPieces(pieces);
    //On traite chaque type de piece un par un et on calcule la différence entre les pieces de la couleur actuelle(c_act)
    // avec celles de l'adversaire(c_adv)
    for (j = 0; j < _NB_PIECES; j++)
    {

        assert(c_act >= 0);
        assert(c_act < 2);
        //Si la j ème piece existe chez la couleur actuelle
        if (pieces[c_act][j] != NULL)
        {
            //Si la j ème piece n'existe pas chez la couleur adversaire -> on gagne des points d'évaluation
            //if(pieces[c_adv][j] == NULL)
            //{
                switch(j)
                {
                    //cas roi couleur actuelle
                    case 0:

                        valeur += 30;
                    break;
                    //cas tour couleur actuelle
                    case 1:

                        valeur += 5;
                    break;
                    //cas fou couleur actuelle
                    case 2:

                        valeur += 3;
                    break;
                    //cas cavalier couleur actuelle
                    case 3:

                        valeur += 3;
                    break;
                    //cas pions couleur actuelle
                    default:

                        valeur += 1;
                }
            }
        }


    std::cout << "Valeur sorti du Eval : " << valeur <<"\n"<<std::endl;
    return valeur;
}

int AlphaBeta::AlphaBetaMax(Plateau plateau, int alpha, int beta, int prof, Couleur couleur ) {

    std::cout <<"Rentre dans ABMax: "<< prof<<std::endl;

    int score;
    std::vector<int*> deplacements;

    Plateau plateau_mod(plateau);

    if ( prof >= _PROF )
        return Eval(plateau,(Couleur) (_NOIR - couleur));
    for (int index = 0;index<_NB_PIECES; index++)
    {
        std::cout <<"Piece : " <<index <<std::endl;
        //on stocke ses deplacements possibles
        deplacements = (plateau.GetPiece(couleur,index))->GetDeplacements(plateau);

        for (std::vector<int*>::iterator i = deplacements.begin(); i != deplacements.end(); i++)
        {

            //on recupere les informations du mouvement de la boucle
            //position x de la piece
            int ligne = (*i)[0];
            //position y de la piece
            int colonne = (*i)[1];
            assert(ligne >= 0);
            assert(colonne >= 0);
            assert(ligne < 8);
            assert(colonne < 8);
            //std::cout << "ligne: " <<ligne << " colonne: " << colonne <<std::endl;
            plateau_mod.Bouger(plateau.GetPiece(couleur,index),ligne,colonne);

            score = AlphaBetaMin(plateau_mod, alpha, beta, prof + 1 ,(Couleur) (_NOIR - couleur));

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

    Plateau plateau_mod(plateau);

    std::cout <<"Rentre dans ABMin: "<< prof<<std::endl;
    if ( prof >=_PROF )
        return -Eval(plateau,(Couleur) (_NOIR - couleur));
    for (int index = 0;index<_NB_PIECES; index++)
    {
        std::cout <<"Piece : " <<index <<std::endl;

        //on stocke ses deplacements possibles
        deplacements = (plateau.GetPiece(couleur,index))->GetDeplacements(plateau);

        for (std::vector<int*>::iterator i = deplacements.begin(); i != deplacements.end(); i++)
        {

            //on recupere les informations du mouvement de la boucle
            //position x de la piece
            int ligne = (*i)[0];
            //position y de la piece
            int colonne = (*i)[1];
            assert(ligne >= 0);
            assert(colonne >= 0);
            assert(ligne < 8);
            assert(colonne < 8);
            //std::cout << "ligne: " <<ligne << " colonne: " << colonne <<std::endl;


            plateau_mod.Bouger(plateau.GetPiece(couleur,index),ligne,colonne);

            score = AlphaBetaMax( plateau_mod, alpha, beta, prof + 1 ,(Couleur) (_NOIR - couleur));

            if( score <= alpha )
                return alpha; // fail hard alpha-cutoff
            if( score < beta )
                beta = score; // beta acts like min in MiniMax
        }
    }
    return beta;
}

void AlphaBeta::AlphaBetaBigMax(Plateau plateau,int alpha, int beta, int prof, Couleur couleur,int (&tab)[3])
{
    std::cout <<"Rentre dans ABBigMax: "<< prof<<std::endl;

    int score;
    int score_temp;
    int first_movement[3];
    first_movement[0] = 0;
    first_movement[1] = 0;
    first_movement[2] = 0;
    std::vector<int*> deplacements;

    Plateau plateau_mod(plateau);

    for (int index = 0;index<_NB_PIECES; index++)
    {
        std::cout <<"Piece : " <<index <<std::endl;
        //on stocke ses deplacements possibles
        deplacements = (plateau.GetPiece(couleur,index))->GetDeplacements(plateau);

        for (std::vector<int*>::iterator i = deplacements.begin(); i != deplacements.end(); i++)
        {

            //on recupere les informations du mouvement de la boucle
            //position x de la piece
            int ligne = (*i)[0];
            //position y de la piece
            int colonne = (*i)[1];
            assert(ligne >= 0);
            assert(colonne >= 0);
            assert(ligne < 8);
            assert(colonne < 8);
            //std::cout << "ligne: " <<ligne << " colonne: " << colonne <<std::endl;


            plateau_mod.Bouger(plateau.GetPiece(couleur,index),ligne,colonne);
            score_temp = AlphaBetaMin(plateau_mod, alpha, beta, prof + 1 ,(Couleur) (_NOIR - couleur));
            if (score <=score_temp)
            {
                score = score_temp;
                first_movement[0] = (*i)[0];
                first_movement[1] = (*i)[1];
                first_movement[2] = index;
                std::cout << "ligne: " << first_movement[0]<< " colonne: " << first_movement[1] <<" index: "<< first_movement[2]<<std::endl;
                VerifAssertMove(first_movement,"first_movement");
            }
        }
    }
    tab[0] = first_movement[0];
    tab[1] = first_movement[1];
    tab[2] = first_movement[2];
}

void AlphaBeta::ABMinMax(Plateau plateau,int (&tab)[3]) {


    std::cout <<"Rentre dans ABMinMax \n\n\n";
	AlphaBetaBigMax(plateau, -100, +100, 1,m_couleur,tab);

}
