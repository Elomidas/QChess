#include <math.h> // std::max
#include "../include/Plateau.h"
#include "../include/Piece.h"
#include "AlphaBeta.h"
#include "algorithm"


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


int AlphaBeta::Eval(Plateau * plateau)
{
    int valeur=0;
    Couleur c_act;
    Couleur c_adv;
    int i,j;
    bool  pieces[2][_NB_PIECES];

    if (m_couleur == _BLANC)
    {
        c_act = _BLANC;
        c_adv = _NOIR;
    }
    else
    {
        c_act = _NOIR;
        c_adv = _BLANC;
    }

    for (i = 0; i < 2 ; i++)
    {
        for(j = 0; j < _NB_PIECES ; j++)
        {
            pieces[i][j] = (((*plateau).GetPiece(i,j))!= NULL);

            if (pieces[i][j])
                std::cout <<"i: " <<i <<" j: " << j << " piece rentree \n";
        }
    }
    //[0] roi [1] tour [2] fou [3] cavalier [4} -> [7] pion

    for (j = 1; j< _NB_PIECES; j++)
        {
            std::cout<<"\n" << j <<": ";
            if (pieces[c_act][j])
            {
                if(!pieces[c_adv][j])
                    switch(j)
                        {
                            case 1:
                                std::cout<<"+5";
                                valeur += 5;
                            break;

                            case 2:
                                std::cout<<"+3";
                                valeur += 3;
                            break;

                            case 3:
                                std::cout<<"+3";
                                valeur += 3;
                            break;

                            default:
                                std::cout<<"+1";
                                valeur += 1;
                        }
            }
            else
            {
                if(pieces[c_adv][j])
                    switch(j)
                    {
                        case 1:
                            std::cout<<"-5";
                            valeur -=  5;
                        break;

                        case 2:
                            std::cout<<"-3";
                            valeur -=  3;
                        break;

                        case 3:
                            std::cout<<"-3";
                            valeur -=  3;
                        break;

                        default:
                            std::cout<<"-1";
                            valeur -= 1;
                    }

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



int* AlphaBeta::ABMaxMove(Plateau* plateau, short int prof, int a, int b,int *move_env) {
	std::vector<int*> deplacements;
	if(m_couleur == _BLANC)
    {
        m_couleur = _NOIR;
    }
    else
    {
         m_couleur = _BLANC;
    }
	int* best_move = NULL;
	int* best_real_move = NULL;
	int* move_mod = NULL;
	int alpha = a,beta = b;
	Plateau p_act = *plateau;
	Plateau p_mod = *plateau;
	Plateau p_movemod = *plateau;
	Plateau p_bestmove = *plateau;
	Piece pieces[2][_NB_PIECES];
    int l;
	if (prof >= _PROF) {//if depth limit is reached
		return move_env;
	} else {


	    for(l = 0; l < _NB_PIECES ; l++)
        {
            pieces[m_couleur][l] = *(p_act.GetPiece(m_couleur,l));
        }

        for(l= 0 ; l< _NB_PIECES; l++)
        {

            deplacements = (p_act.GetPiece(m_couleur,l))->GetDeplacements(p_act);
            //assert(deplacements);
            for (std::vector<int*>::iterator i = deplacements.begin(); i != deplacements.end(); i++)
            {
                int index = (*i)[0];
                int x = (*i)[1];
                int y = (*i)[2];
                p_mod.Bouger(p_mod.GetPiece(m_couleur,index),x,y);

                move_mod = ABMinMove(&p_mod, prof+1, alpha, beta,*i);

                index = move_mod[0];
                x = move_mod[1];
                y = move_mod[2];
                p_movemod.Bouger(p_mod.GetPiece(m_couleur,index),x,y);

                index = best_move[0];
                x = best_move[1];
                y = best_move[2];
                p_bestmove.Bouger(p_mod.GetPiece(m_couleur,index),x,y);

                if (best_move == NULL ||
                        Eval(&p_bestmove) > Eval(&p_movemod))
                {
                    best_move = move_mod;
                    best_real_move = *i;
                    alpha = Eval(&p_movemod);
                }
                if(beta > alpha){
                    return best_real_move;
                }
            }
        }

		return best_real_move;
	}
	//}
}
int* AlphaBeta::ABMinMove(Plateau* plateau, short int prof, int a, int b, int * move_env)
{
    std::vector<int*> deplacements;
    if(m_couleur == _BLANC)
    {
        m_couleur = _NOIR;
    }
    else
    {
         m_couleur = _BLANC;
    }
	int* best_move = NULL;
	int* best_real_move = NULL;
	int* move_mod = NULL;
	int alpha = a,beta = b;
	Plateau p_act = *plateau;
	Plateau p_mod = *plateau;
	Plateau p_movemod = *plateau;
	Plateau p_bestmove = *plateau;
	Piece pieces[2][_NB_PIECES];
    int l;

	if (prof >= _PROF) {//if depth limit is reached
		return move_env;
	}
	else
    {

	    for(l = 0; l < _NB_PIECES ; l++)
        {
            pieces[m_couleur][l] = *(p_act.GetPiece(m_couleur,l));
        }
        for(l= 0 ; l< _NB_PIECES; l++)
        {
            deplacements = (p_act.GetPiece(m_couleur,l))->GetDeplacements(p_act);

            for (std::vector<int*>::iterator i = deplacements.begin(); i != deplacements.end(); i++)
            {
                int index = (*i)[0];
                int x = (*i)[1];
                int y = (*i)[2];
                p_mod.Bouger(p_mod.GetPiece(m_couleur,index),x,y);

                move_mod = ABMaxMove(&p_mod, prof+1, alpha, beta,*i);

                index = move_mod[0];
                x = move_mod[1];
                y = move_mod[2];
                p_movemod.Bouger(p_mod.GetPiece(m_couleur,index),x,y);

                index = best_move[0];
                x = best_move[1];
                y = best_move[2];
                p_bestmove.Bouger(p_mod.GetPiece(m_couleur,index),x,y);

                if (best_move == NULL ||
                        Eval(&p_movemod) < Eval(&p_bestmove))
                {
                    best_move = move_mod;
                    best_real_move = *i;
                    beta = Eval(&p_movemod);
                }
                if(beta < alpha){
                    return best_real_move;
                }
            }
        }
		return best_real_move;
	}
}

int* AlphaBeta::ABMinMax(Plateau* plateau) {
	if(m_couleur == _BLANC)
    {
        m_couleur = _NOIR;
    }
    else
    {
         m_couleur = _BLANC;
    }
    int * tab;

	return ABMaxMove(plateau, 1, 0, 0,tab);
}




