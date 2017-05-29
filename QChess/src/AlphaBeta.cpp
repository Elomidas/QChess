#include <math.h> // std::max
#include "../include/Plateau.h"
#include "../include/Piece.h"
#include "AlphaBeta.h"
#include "algorithm"

AlphaBeta::AlphaBeta()
{
   m_couleur = _NOIR;
}

AlphaBeta::AlphaBeta(Plateau &plateau, Couleur couleur) : m_plateau(plateau)
{
    m_couleur = couleur;
}

AlphaBeta::~AlphaBeta()
{
    //dtor
}

void AlphaBeta::VerifAssertMove(int * moveAB, std::string titre)
{
    assert(moveAB!= NULL);
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
    Couleur c_act = couleur, c_adv = (Couleur)(_NOIR - couleur);

    int i,j;
    Piece *  pieces[2][_NB_PIECES];
    //On recupere toutes les pieces du tableau et on mets un boolean selon leur existence dans deux lignes distinctes suivant la couleur;
    //[0] roi, [1] tour, [2] fou, [3] cavalier, [4} -> [7] pion.
    plateau.GetPieces(pieces);
    //On traite chaque type de piece un par un et on calcule la différence entre les pieces de la couleur actuelle(c_act)
    // avec celles de l'adversaire(c_adv)
    //Fn Martial
    for (j = 0; j < _NB_PIECES; j++)
    {

        assert(c_act >= 0);
        assert(c_act < 2);
        //Si la j ème piece existe chez la couleur actuelle
        if (pieces[c_act][j] != NULL)
        {
            //Si la j ème piece n'existe pas chez la couleur adversaire -> on gagne des points d'évaluation
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
    //Fn Victor
    /*
    //Roi
    if(pieces[c_act][0] != NULL)
        valeur += 100;
    if(pieces[c_adv][0] != NULL)
        valeur -= 100;
    //Tour
    if(pieces[c_act][1] != NULL)
        valeur += 5;
    if(pieces[c_adv][1] != NULL)
        valeur -= 5;
    //Fou
    if(pieces[c_act][2] != NULL)
        valeur += 3;
    if(pieces[c_adv][2] != NULL)
        valeur -= 3;
    //Cavalier
    if(pieces[c_act][3] != NULL)
        valeur += 3;
    if(pieces[c_adv][3] != NULL)
        valeur -= 3;
    for(int i = 4; i < 12; i++)
    {
        //Pion
        if(pieces[c_act][i] != NULL)
            valeur += 1;
        if(pieces[c_adv][i] != NULL)
            valeur -= 1;
    }
    */
    return valeur;
}

int AlphaBeta::AlphaBetaMax(Plateau plateau, int alpha, int beta, int prof, Couleur couleur )
{
    //std::cout << "max" << std::endl;
    int score;
    std::vector<int*> deplacements;


    if ( prof >= _PROF )
        return Eval(plateau,(Couleur) (_NOIR - couleur));
    //Pour chaque piece une par une
    for (int index = 0;index<_NB_PIECES; index++)
    {
        if( plateau.GetPieceI(couleur,index) != NULL )
        {
            //on stocke ses deplacements possibles
            deplacements = (plateau.GetPieceI(couleur,index))->GetDeplacements(plateau);

            if(!deplacements.empty())
            {
                //pour chaque deplacement de la piece un par un
                for(unsigned int i = 0; i < deplacements.size(); i++)
                {
                    Plateau plateau_mod(plateau);
                    assert(deplacements[i] != NULL);
                    //on recupere les informations du déplacement
                    //position x de la piece
                    int ligne = deplacements[i][0];
                    //position y de la piece
                    int colonne = deplacements[i][1];
                    assert(ligne >= 0);
                    assert(colonne >= 0);
                    assert(ligne < 8);
                    assert(colonne < 8);

                    //On effectue le déplacement sur le plateau plateau _mod
                    if(!plateau_mod.Bouger((Couleur)couleur, index, ligne, colonne))
                    {
                        std::cout << "Mouvement impossible" << std::endl
                                  << "> Couleur : " << couleur << std::endl
                                  << "> Index : " << index << std::endl
                                  << "> Ligne : " << ligne << std::endl
                                  << "> Colonne : " << colonne << std::endl;
                        assert(false);
                    }

                    //On lance AlphaBetaMin sur le plateau ou la piece a été bougée
                    if(plateau_mod.Fin())
                        score = Eval(plateau_mod, couleur);
                    else score = AlphaBetaMin(plateau_mod, alpha, beta, prof + 1 ,(Couleur) (_NOIR - couleur));

                    if( score >= beta )
                       return beta;   // fail hard beta-cutoff
                    if( score > alpha )
                       alpha = score; // alpha acts like max in MiniMax
                }
            }
           //On nettoie le vecteur de déplacement
            NettoieVecteur(deplacements);
        }
    }
    return alpha;
}

//La meme chose que ABMax en inverse  pour ABMin
int AlphaBeta::AlphaBetaMin(Plateau plateau, int alpha, int beta, int prof, Couleur couleur )
{
    int score;
    std::vector<int*> deplacements;

    if ( prof >=_PROF )
        return -Eval(plateau,(Couleur) (_NOIR - couleur));
    for (int index = 0;index<_NB_PIECES; index++)
    {
        if( plateau.GetPieceI(couleur,index) != NULL )
        {
            //on stocke ses deplacements possibles
            deplacements = (plateau.GetPieceI(couleur,index))->GetDeplacements(plateau);
            if(!deplacements.empty())
            {
                for(int i = 0; i < deplacements.size(); i++)
                {
                    Plateau plateau_mod(plateau);
                    assert(deplacements[i] != NULL);
                    //on recupere les informations du mouvement de la boucle
                    //position x de la piece
                    int ligne = deplacements[i][0];
                    //position y de la piece
                    int colonne = deplacements[i][1];
                    assert(ligne >= 0);
                    assert(colonne >= 0);
                    assert(ligne < 8);
                    assert(colonne < 8);
                    //std::cout << "Test 1" << std::endl;
                    if(!plateau_mod.Bouger((Couleur)couleur, index, ligne, colonne))
                    {
                        std::cout << "Mouvement impossible" << std::endl
                                  << "> Couleur : " << couleur << std::endl
                                  << "> Index : " << index << std::endl
                                  << "> Ligne : " << ligne << std::endl
                                  << "> Colonne : " << colonne << std::endl;
                        assert(false);
                    }
                    //std::cout << "OK 1" << std::endl;
                    if(plateau_mod.Fin())
                        score = Eval(plateau_mod, couleur);
                    else score = AlphaBetaMax( plateau_mod, alpha, beta, prof + 1 ,(Couleur) (_NOIR - couleur));

                    if( score <= alpha )
                        return alpha; // fail hard alpha-cutoff
                    if( score < beta )
                        beta = score; // beta acts like min in MiniMax

                }
            }
            NettoieVecteur(deplacements);
        }
    }
    return beta;
}

//Lors du premier appel --> permet de sauvegarder le tout premier deplacement (celui qui compte pour l'IA)
//la fonction ne sera plus appelée par la suite , on appelera ABMax dans ABMin
void AlphaBeta::AlphaBetaBigMax(Plateau plateau,int alpha, int beta, int prof, Couleur couleur,int (&tab)[3])
{
    int score = -1000; //meilleur score enregistré
    int score_temp; //score recueilli à partir d'ABMin
    int first_movement[3]; //tableau du mouvement final comprenant [0] ligne [1] colonne [2] index de la piece

    //initialisation du mouvement
    first_movement[0] = -1;
    first_movement[1] = -1;
    first_movement[2] = -1;

    //déclaration du vecteur
    std::vector<int*> deplacements;



    //pour chaque piece une par une du plateau
    for (int index = 0;index<_NB_PIECES; index++)
    {
        //on stocke ses deplacements possibles

        if( plateau.GetPieceI(couleur,index) != NULL )
        {
            deplacements = (plateau.GetPieceI(couleur,index))->GetDeplacements(plateau);
            if(!deplacements.empty())
            {
                //pour chaque deplacement de la piece d'index index
                for(int i = 0; i < deplacements.size(); i++)
                {
                    Plateau plateau_mod(plateau);
                    assert(deplacements[i] != NULL);
                    //on recupere les informations du mouvement
                    //position x de la piece
                    int ligne = deplacements[i][0];
                    //position y de la piece
                    int colonne = deplacements[i][1];
                    assert(ligne >= 0);
                    assert(colonne >= 0);
                    assert(ligne < 8);
                    assert(colonne < 8);

                    //on effectue le deplacement de la piece d'indice index sur le plateau plateau_mod
                    if(!plateau_mod.Bouger((Couleur)couleur, index, ligne, colonne))

                    {
                        std::cout << "Mouvement impossible" << std::endl
                                  << "> Couleur : " << couleur << std::endl
                                  << "> Index : " << index << std::endl
                                  << "> Ligne : " << ligne << std::endl
                                  << "> Colonne : " << colonne << std::endl;
                        assert(false);
                    }

                    //score_temp recevra le score de ABMin
                    if(plateau_mod.Fin())
                        score_temp = Eval(plateau_mod, couleur);
                    else score_temp = AlphaBetaMin(plateau_mod, alpha, beta, prof + 1 ,(Couleur) (_NOIR - couleur));
                    //Si le score obtenue est meilleur que celui actuellement enregistré
                    if (score <= score_temp)
                    {
                        //on le retiens
                        score = score_temp;

                        //on recupere l'indice de la piece du nouveau meilleur score ainsi que son déplacement(ligne,colonne)
                        first_movement[0] = deplacements[i][0];
                        first_movement[1] = deplacements[i][1];
                        first_movement[2] = index;
                        //On verifie qu'il n'y a pas d'erreur
                        VerifAssertMove(first_movement,"first_movement");
                    }
                }
            }
            //Nettoie le vecteur deplacement
            NettoieVecteur(deplacements);
        }
    }
    //le tableau passé en reference prend les valeur du meilleur mouvement
    tab[0] = first_movement[0];
    tab[1] = first_movement[1];
    tab[2] = first_movement[2];
}

//fonction principale qui appelle ABMax (appelée dans Jeu) qui lance la recheche du mouvement avec les variable initialisées.
void AlphaBeta::ABMinMax(Plateau plateau,int (&tab)[3])
{
	AlphaBetaBigMax(plateau, -100, +100, 1,m_couleur,tab);
}


//Fonction a verifier!!!!
void AlphaBeta::NettoieVecteur(std::vector<int *> &v)
{
    for(unsigned int i = 0; i < v.size(); i++)
    {
        if(v[i] != NULL)
            delete v[i];
        v[i] = NULL;
    }
    if(!v.empty())
        v.clear();
}
