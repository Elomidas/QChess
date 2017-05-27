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
    std::cout<<"Couleur de m_alphabeta finc constructeur Alphabeta: " << Getcouleur() <<std::endl;
}

AlphaBeta::~AlphaBeta()
{
    //dtor
}

void AlphaBeta::VerifAssertMove(int * moveAB)
{
    assert(moveAB!= NULL);
    std::cout <<"ligne: "<<moveAB[0] <<std::endl;
    std::cout <<"colonne: "<<moveAB[1] <<std::endl;
    std::cout <<"Index! " <<moveAB[2] <<std::endl;
    assert(moveAB[0] > 0);
    assert(moveAB[0] < 8);
    assert(moveAB[1] > 0);
    assert(moveAB[1] < 8);
}


int AlphaBeta::Eval(Plateau * plateau, Couleur couleur)
{
    int valeur=0;
    Couleur c_act = couleur;
    Couleur c_adv ;

    std::cout<< "\n \n Debut Eval: \n c_act= " << c_act << "\n";

    if(c_act == _BLANC)
        c_adv = _NOIR;
    else
        c_adv = _BLANC;

    int i,j;
    std::cout<< "Apres if c_act= " << c_act <<std::endl;
    Piece *  pieces[2][_NB_PIECES];
    std::cout<< "Apres piece * c_act= " << c_act <<std::endl;
    //On recupere toutes les pieces du tableau et on mets un boolean selon leur existence dans deux lignes distinctes suivant la couleur;
    //[0] roi, [1] tour, [2] fou, [3] cavalier, [4} -> [7] pion.
    plateau->GetPieces(pieces);
    std::cout<< "Après plateau->GetPieces c_act= " << c_act <<std::endl;
    //On traite chaque type de piece un par un et on calcule la différence entre les pieces de la couleur actuelle(c_act)
    // avec celles de l'adversaire(c_adv)
    for (j = 1; j < _NB_PIECES; j++)
        {
            std::cout<<"\n indice:" << j <<": \n";
            assert(c_act >= 0);
            std::cout<< "c_act= " << c_act <<std::endl;
            assert(c_act < 2);
            assert(c_adv >= 0);
            assert(c_adv < 2);
            //Si la j ème piece existe chez la couleur actuelle
            if (&pieces[c_act][j] != NULL)
            {
                //Si la j ème piece n'existe pas chez la couleur adversaire -> on gagne des points d'évaluation
                if(&pieces[c_adv][j] == NULL)
                {
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
    std::cout <<"c_adv: "<<c_adv << " BLANC\n";
    std::cout <<"c_act: "<<c_act << " NOIR\n";
    //Definition des mouvements
	int* best_move = NULL;
	int* best_real_move = NULL;
	int* move_mod = NULL;
	//Declaration des alpha beta
	int alpha = a,beta = b;

	//declaration des plateaux qui vont etre utilisés
	Plateau p_act(*plateau);
	Plateau p_mod(*plateau);
	Plateau p_movemod(*plateau);
	Plateau p_bestmove(*plateau);
	Piece * pieces[2][_NB_PIECES];
	//declaration iterateur
    int index;

    std::cout <<"Debut Max \n";

	if (prof >= _PROF) {//si on se retrouve à la profondeur max demandée
		//retourne dernier mouvement effectué
		assert(move_env != NULL);
		return move_env;
	}
	else
    {
         std::cout <<"pas la prof max \n";
        //On recupere toutes les pieces de la couleur actuelle
        p_act.GetPieces(pieces);
        std::cout <<"pieces recuperees\n";
        //pour chasque piece une par une
        for(index= 0 ; index< _NB_PIECES; index++)
        {
            std::cout <<"dans le for des pieces";
            std::cout <<"c_adv: "<<c_adv ;
            std::cout <<"c_act: "<<c_act ;
            //on stocke ses deplacements possibles
            deplacements = (p_act.GetPiece(c_act,index))->GetDeplacements(p_act);
            //assert(deplacements);
            std::cout <<"deplacements recup" <<std::endl ;
            //Pour chaque deplacement possiblze de la piece
            for (std::vector<int*>::iterator i = deplacements.begin(); i != deplacements.end(); i++)
            {
                VerifAssertMove(*i);
                //on recupere les informations du mouvement de la boucle
                //position x de la piece
                int ligne = (*i)[0];
                //position y de la piece
                int colonne = (*i)[1];
                //index de la piece
                (*i)[2] = index;
                //on fait effectuer le mouvement à cette piece sur le plateau p_mod
                p_mod.Bouger(p_mod.GetPiece(c_act,index),ligne,colonne);

                //Appelle de la methode ABMinMovee(mouvement de l'adversaire sur le plateau que l'on vient de modifier(p_mod))
                //le mouvement qui en resortira sera stocke dans move_mod
                move_mod = ABMinMove(&p_mod, prof+1, alpha, beta,*i,c_adv);

                //on recupere les informations du mouvement recupere
                //position x de la piece
                ligne = move_mod[0];
                //position y de la piece
                colonne = move_mod[1];
                //on fait effectuer le mouvement à cette piece sur le plateau p_movemod
                p_movemod.Bouger(p_movemod.GetPiece(c_act,index),ligne,colonne);

                //Si aucun best_move n'a été enregistré pour une autre pièce
                if(best_move != NULL)
                 {
                    //on recupere les informations du best_move

                    ligne = best_move[0];
                    colonne = best_move[1];
                    p_bestmove.Bouger(p_mod.GetPiece(c_act,index),ligne,colonne);
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


//Lamême à l'inverse pour alpha et beta dans ABMinMove
int* AlphaBeta::ABMinMove(Plateau* plateau, short int prof, int a, int b, int * move_env, Couleur c_act)
{
    std::vector<int*> deplacements;
    Couleur c_adv;
    if(c_act == _BLANC)
    {
        c_adv = _NOIR;
        std::cout <<"c_act: BLANC\n";
    }
    else
    {
         c_adv = _BLANC;

         std::cout <<"c_act: NOIR\n";
    }
	int* best_move = NULL;
	int* best_real_move = NULL;
	int* move_mod = NULL;
	int alpha = a,beta = b;
	Plateau p_act = *plateau;
	Plateau p_mod = *plateau;
	Plateau p_movemod = *plateau;
	Plateau p_bestmove = *plateau;
	Piece * pieces[2][_NB_PIECES];
    int index;

     std::cout <<"DébutMin\n";

	if (prof >= _PROF) {//if depth limit is reached

		assert(move_env != NULL);
		return move_env;
	}
	else
    {
        std::cout <<"Pas la prof max \n";
        //On recupere toutes les pieces de la couleur actuelle
        p_act.GetPieces(pieces);
        std::cout <<"pieces récuperees\n";

        for(index= 0 ; index< _NB_PIECES; index++)
        {
            //on stocke ses deplacements possibles
            deplacements = (p_act.GetPiece(c_act,index))->GetDeplacements(p_act);

            for (std::vector<int*>::iterator i = deplacements.begin(); i != deplacements.end(); i++)
            {
                VerifAssertMove(*i);
                int ligne = (*i)[0];
                int colonne = (*i)[1];
                *i[2] = index;
                p_mod.Bouger(p_mod.GetPiece(c_act,index),ligne,colonne);

                move_mod = ABMaxMove(&p_mod, prof+1, alpha, beta,*i,c_adv);

                VerifAssertMove(move_mod);
                ligne = move_mod[0];
                colonne = move_mod[1];

                p_movemod.Bouger(p_mod.GetPiece(c_act,index),ligne,colonne);

                if(best_move!= NULL)
                {
                    VerifAssertMove(best_move);
                    ligne = best_move[0];
                    colonne = best_move[1];
                    best_move[2] = index;
                    p_bestmove.Bouger(p_mod.GetPiece(c_act,index),ligne,colonne);
                }


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

int* AlphaBeta::ABMinMax(Plateau plateau) {

    int * tab;
    std::cout <<"Rentre ici, c_act: " <<m_couleur <<"\n\n";
	return ABMaxMove(&plateau, 1, 0, 0,tab,m_couleur);
}






