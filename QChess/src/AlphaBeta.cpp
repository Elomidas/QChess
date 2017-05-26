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


int AlphaBeta::Eval(Plateau * plateau, Couleur couleur)
{
    int valeur=0;
    Couleur c_act = couleur;
    Couleur c_adv ;

    if(c_act == _BLANC)
        c_adv = _NOIR;
    else
        c_adv = _BLANC;

    int i,j;
    bool  pieces[2][_NB_PIECES];

    //On recupere toutes les pieces du tableau et on mets un boolean selon leur existence dans deux lignes distinctes suivant la couleur;
    //[0] roi, [1] tour, [2] fou, [3] cavalier, [4} -> [7] pion.
    for (i = 0; i < 2 ; i++)
    {
        for(j = 0; j < _NB_PIECES ; j++)
        {
            pieces[i][j] = (((*plateau).GetPiece(i,j))!= NULL);
            std::cout
                << "Piece: " << (*plateau).GetPiece(i,j)->GetChar()
                <<" Couleur :" << (*plateau).GetPiece(i,j)->GetCouleur()
                << " Colonne : " << (*plateau).GetPiece(i,j)->GetColonne()
                << " Ligne: " << (*plateau).GetPiece(i,j)->GetLigne() <<"\n";
            if (pieces[i][j])
                std::cout <<"i: " <<i <<" j: " << j << " piece rentree \n";
        }
    }

    //On traite chasue type de piece un par un et on calcule la différence entre les pieces de la couleur actuelle(c_act)
    // avec celles de l'adversaire(c_adv)
    for (j = 1; j< _NB_PIECES; j++)
        {
            std::cout<<"\n" << j <<": ";
            //Si la j ème piece existe chez la couleur actuelle
            if (pieces[c_act][j])
            {
                //Si la j ème piece n'existe pas chez la couleur adversaire -> on gagne des points d'évaluation
                if(!pieces[c_adv][j])
                    switch(j)
                        {
                            //cas roi couleur actuelle
                            case 0:
                                std::cout<<"+30";
                                valeur += 30;
                            break;
                            //cas tour couleur actuelle
                            case 1:
                                std::cout<<"+5";
                                valeur += 5;
                            break;
                            //cas fou couleur actuelle
                            case 2:
                                std::cout<<"+3";
                                valeur += 3;
                            break;
                            //cas cavalier couleur actuelle
                            case 3:
                                std::cout<<"+3";
                                valeur += 3;
                            break;
                            //cas pions couleur actuelle
                            default:
                                std::cout<<"+1";
                                valeur += 1;
                        }
            }
            //Si la j ème piece n'existe pas chez la couleur actuelle
            else
            {
                //Mais la jème piece existe chez l'adversaire --> On perd des points d'évaluation
                if(pieces[c_adv][j])
                    switch(j)
                    {
                        //cas roi adverse
                        case 0:
                            std::cout<<"-30";
                            valeur -=  30;
                        //cas tour adverse
                        case 1:
                            std::cout<<"-5";
                            valeur -=  5;
                        break;
                        //cas fou adverse
                        case 2:
                            std::cout<<"-3";
                            valeur -=  3;
                        break;
                        //cas cavalier adverse
                        case 3:
                            std::cout<<"-3";
                            valeur -=  3;
                        break;
                        //cas pion adverses
                        default:
                            std::cout<<"-1";
                            valeur -= 1;
                    }

            }
        }

    return valeur;
}



int* AlphaBeta::ABMaxMove(Plateau* plateau, short int prof, int a, int b,int *move_env, Couleur c_act) {
    //vecteur de stockage des déplacements(un pointeur sur tableau de 3 cases.)
	std::vector<int*> deplacements;
	//Définission couleur adverse
	Couleur c_adv;
	if(c_act == _BLANC)
    {
        c_adv = _NOIR;
    }
    else
    {
         c_adv = _BLANC;
    }
    //Definition des mouvements
	int* best_move = NULL;
	int* best_real_move = NULL;
	int* move_mod = NULL;
	//Declaration des alpha beta
	int alpha = a,beta = b;

	//declaration des plateaux qui vont etre utilisés
	Plateau p_act = *plateau;
	Plateau p_mod = *plateau;
	Plateau p_movemod = *plateau;
	Plateau p_bestmove = *plateau;
	Piece pieces[2][_NB_PIECES];
	//declaration iterateur
    int l;


	if (prof >= _PROF) {//si on se retrouve à la profondeur max demandée
		//retourne dernier mouvement effectué
		return move_env;
	}
	else
    {
        //On recupere toutes les pieces de la couleur actuelle
        for(l = 0; l < _NB_PIECES ; l++)
        {
            pieces[c_act][l] = *(p_act.GetPiece(c_act,l));
        }

        //pour chasque piece une par une
        for(l= 0 ; l< _NB_PIECES; l++)
        {
            //on stocke ses deplacements possibles
            deplacements = (p_act.GetPiece(c_act,l))->GetDeplacements(p_act);
            //assert(deplacements);

            //Pour chaque deplacement possiblze de la piece
            for (std::vector<int*>::iterator i = deplacements.begin(); i != deplacements.end(); i++)
            {
                //on recupere les informations du mouvement de la boucle
                //index de la piece
                int index = (*i)[0];
                //position x de la piece
                int x = (*i)[1];
                //position y de la piece
                int y = (*i)[2];
                //on fait effectuer le mouvement à cette piece sur le plateau p_mod
                p_mod.Bouger(p_mod.GetPiece(c_act,index),x,y);

                //Appelle de la methode ABMinMovee(mouvement de l'adversaire sur le plateau que l'on vient de modifier(p_mod))
                //le mouvement qui en resortira sera stocke dans move_mod
                move_mod = ABMinMove(&p_mod, prof+1, alpha, beta,*i,c_adv);

                //on recupere les informations du mouvement recupere
                //index de la piece
                index = move_mod[0];
                //position x de la piece
                x = move_mod[1];
                //position y de la piece
                y = move_mod[2];
                //on fait effectuer le mouvement à cette piece sur le plateau p_movemod
                p_movemod.Bouger(p_movemod.GetPiece(c_act,index),x,y);

                //Si aucun best_move n'a été enregistré pour une autre pièce
                if(best_move != NULL)
                 {
                    //on recupere les informations du best_move
                    index = best_move[0];
                    x = best_move[1];
                    y = best_move[2];
                    p_bestmove.Bouger(p_mod.GetPiece(c_act,index),x,y);
                 }
                 //si il existe  et que son evaluation est meilleur que celle du mouvement recupere de ABMinMove
                if (best_move == NULL ||
                        Eval(&p_bestmove,c_act) > Eval(&p_movemod,c_act))
                {
                    best_move = move_mod;
                    best_real_move = *i;
                    alpha = Eval(&p_movemod,c_act);
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
int* AlphaBeta::ABMinMove(Plateau* plateau, short int prof, int a, int b, int * move_env, Couleur c_act)
{
    std::vector<int*> deplacements;
    Couleur c_adv;
    if(c_act == _BLANC)
    {
        c_adv = _NOIR;
    }
    else
    {
         c_adv = _BLANC;
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
            pieces[c_act][l] = *(p_act.GetPiece(c_act,l));
        }
        for(l= 0 ; l< _NB_PIECES; l++)
        {
            deplacements = (p_act.GetPiece(c_act,l))->GetDeplacements(p_act);

            for (std::vector<int*>::iterator i = deplacements.begin(); i != deplacements.end(); i++)
            {
                int index = (*i)[0];
                int x = (*i)[1];
                int y = (*i)[2];
                p_mod.Bouger(p_mod.GetPiece(c_act,index),x,y);

                move_mod = ABMaxMove(&p_mod, prof+1, alpha, beta,*i,c_adv);

                index = move_mod[0];
                x = move_mod[1];
                y = move_mod[2];
                p_movemod.Bouger(p_mod.GetPiece(c_act,index),x,y);

                index = best_move[0];
                x = best_move[1];
                y = best_move[2];
                p_bestmove.Bouger(p_mod.GetPiece(c_act,index),x,y);

                if (best_move == NULL ||
                        Eval(&p_movemod,c_act) < Eval(&p_bestmove,c_act))
                {
                    best_move = move_mod;
                    best_real_move = *i;
                    beta = Eval(&p_movemod,c_act);
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

    int * tab;

	return ABMaxMove(plateau, 1, 0, 0,tab,m_couleur);
}




