#include <math.h> // std::max
#include "../include/Plateau.h"
#include "../include/Piece.h"
#include "AlphaBeta.h"
#include "algorithm"

#define _SCORE  600
#define _V_ROI  200
#define _V_TOUR 5.5
#define _V_FOU  3.5
#define _V_CAV  3.5
#define _V_PION 1
#define _V_MOB  0.1
#define _V_BLO  0.5

AlphaBeta::AlphaBeta()
{
   m_couleur = _NOIR;
}

AlphaBeta::AlphaBeta(Couleur couleur)
{
    m_couleur = couleur;
}

AlphaBeta::~AlphaBeta()
{
    //dtor
}

void AlphaBeta::VerifAssertMove(const int * moveAB)
{
    assert(moveAB!= NULL);
    assert(moveAB[0] >= 0);
    assert(moveAB[0] < 8);
    assert(moveAB[1] >= 0);
    assert(moveAB[1] < 8);
    assert(moveAB[2] >= 0);
    assert(moveAB[2] < 12 );
}

double AlphaBeta::Eval(const Plateau &plateau)
{
    double valeur = _V_ROI;
    Couleur c_act = m_couleur, c_adv = (Couleur)(_NOIR - m_couleur);

    Piece *  pieces[2][_NB_PIECES];
    //On recupere toutes les pieces du tableau et on mets un boolean selon leur existence dans deux lignes distinctes suivant la couleur;
    //[0] roi, [1] tour, [2] fou, [3] cavalier, [4} -> [7] pion.
    plateau.GetPieces(pieces);
    //On traite chaque type de piece un par un et on calcule la diff�rence entre les pieces de la couleur actuelle(c_act)
    // avec celles de l'adversaire(c_adv)
    if(pieces[c_act][0] == NULL)
        valeur = - _V_ROI;
    else
    {
        if(pieces[c_adv][0] != NULL)
            valeur -= _V_ROI;
        //Tour
        if(pieces[c_act][1] != NULL)
            valeur += _V_TOUR;
        if(pieces[c_adv][1] != NULL)
            valeur -= _V_TOUR;
        //Fou
        if(pieces[c_act][2] != NULL)
            valeur += _V_FOU;
        if(pieces[c_adv][2] != NULL)
            valeur -= _V_FOU;
        //Cavalier
        if(pieces[c_act][3] != NULL)
            valeur += _V_CAV;
        if(pieces[c_adv][3] != NULL)
            valeur -= _V_CAV;
        for(int i = 4; i < 12; i++)
        {
            //Pion
            if(pieces[c_act][i] != NULL)
                valeur += _V_PION;
            if(pieces[c_adv][i] != NULL)
                valeur -= _V_PION;
        }

        int bloquesAl = 0, bloquesAd = 0;
        int mobility = NombreMovePossible(plateau, m_couleur, bloquesAl) - NombreMovePossible(plateau,(Couleur) (_NOIR - m_couleur), bloquesAd);
        //std::cout << "Mob : " << mobility * _V_MOB << std::endl;
        valeur += mobility * _V_MOB;
        //std::cout << "Bloques : " << (bloquesAl - bloquesAd) * _V_BLO << std::endl;
        valeur -= (bloquesAl - bloquesAd) * _V_BLO;
    }
    //std::cout << "Score : " << valeur << std::endl;
    return valeur;
}

int AlphaBeta::NombreMovePossible(const Plateau &plateau, const Couleur couleur, int &bloques)
{
    int valeur = 0;
    for(int index =  0; index < _NB_PIECES; index++)
    {
        if( plateau.GetPieceI(couleur,index) != NULL )
        {
            int taille = (plateau.GetPieceI(couleur,index))->GetDeplacements(plateau).size();
            valeur += taille;
            bloques += (taille == 0);
        }
    }
    return valeur;
}

double AlphaBeta::AlphaBetaMax(const Plateau &plateau, double alpha, double beta, const int prof, const Couleur couleur )
{
    //std::cout << "max" << std::endl;
    double score;
    std::vector<int*> deplacements;


    if ( prof >= _PROF )
        return Eval(plateau);
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
                    //on recupere les informations du d�placement
                    //position x de la piece
                    int ligne = deplacements[i][0];
                    //position y de la piece
                    int colonne = deplacements[i][1];
                    assert(ligne >= 0);
                    assert(colonne >= 0);
                    assert(ligne < 8);
                    assert(colonne < 8);

                    //On effectue le d�placement sur le plateau plateau _mod
                    if(!plateau_mod.Bouger((Couleur)couleur, index, ligne, colonne))
                    {
                        std::cout << "Mouvement impossible" << std::endl
                                  << "> Couleur : " << couleur << std::endl
                                  << "> Index : " << index << std::endl
                                  << "> Ligne : " << ligne << std::endl
                                  << "> Colonne : " << colonne << std::endl;
                        assert(false);
                    }

                    //On lance AlphaBetaMin sur le plateau ou la piece a �t� boug�e
                    if(plateau_mod.Fin())
                        score = Eval(plateau_mod);
                    else score = AlphaBetaMin(plateau_mod, alpha, beta, prof + 1 ,(Couleur) (_NOIR - couleur));

                    if( score >= beta )
                       return beta;   // fail hard beta-cutoff
                    if( score > alpha )
                       alpha = score; // alpha acts like max in MiniMax
                }
            }
           //On nettoie le vecteur de d�placement
            NettoieVecteur(deplacements);
        }
    }
    return alpha;
}

//La meme chose que ABMax en inverse  pour ABMin
double AlphaBeta::AlphaBetaMin(const Plateau &plateau, double alpha, double beta, const int prof, const Couleur couleur )
{
    //std::cout << "min" << std::endl;
    double score;
    std::vector<int*> deplacements;

    if ( prof >=_PROF )
        return Eval(plateau);
    for (int index = 0;index<_NB_PIECES; index++)
    {
        if( plateau.GetPieceI(couleur,index) != NULL )
        {
            //on stocke ses deplacements possibles
            deplacements = (plateau.GetPieceI(couleur,index))->GetDeplacements(plateau);
            if(!deplacements.empty())
            {
                for(unsigned int i = 0; i < deplacements.size(); i++)
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
                    if(!plateau_mod.Bouger((Couleur)couleur, index, ligne, colonne))
                    {
                        std::cout << "Mouvement impossible" << std::endl
                                  << "> Couleur : " << couleur << std::endl
                                  << "> Index : " << index << std::endl
                                  << "> Ligne : " << ligne << std::endl
                                  << "> Colonne : " << colonne << std::endl;
                        assert(false);
                    }
                    if(plateau_mod.Fin())
                        score = Eval(plateau_mod);
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
//la fonction ne sera plus appel�e par la suite , on appelera ABMax dans ABMin
void AlphaBeta::AlphaBetaBigMax(const Plateau &plateau, double alpha, double beta, const int prof, const Couleur couleur,int tab[3])
{
    double score = -1000; //meilleur score enregistr�
    double score_temp; //score recueilli � partir d'ABMin
    int first_movement[3]; //tableau du mouvement final comprenant [0] ligne [1] colonne [2] index de la piece

    //initialisation du mouvement
    first_movement[0] = -1;
    first_movement[1] = -1;
    first_movement[2] = -1;

    //d�claration du vecteur
    std::vector<int*> deplacements;



    //pour chaque piece une par une du plateau
    for (int index = 0;index<_NB_PIECES; index++)
    {
        //on stocke ses deplacements possibles

        if( plateau.GetPieceI(couleur,index) != NULL )
        {
            //deplacements = (plateau.GetPieceI(couleur,index))->GetDeplacements(plateau);
            deplacements = plateau.GetDeplacements(couleur, index);
            if(!deplacements.empty())
            {
                //pour chaque deplacement de la piece d'index index
                for(unsigned int i = 0; i < deplacements.size(); i++)
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
                        score_temp = Eval(plateau_mod);
                    else score_temp = AlphaBetaMin(plateau_mod, alpha, beta, prof + 1 ,(Couleur) (_NOIR - couleur));
                    //Si le score obtenue est meilleur que celui actuellement enregistr�
                    if (score <= score_temp)
                    {
                        //on le retiens
                        score = score_temp;

                        //on recupere l'indice de la piece du nouveau meilleur score ainsi que son d�placement(ligne,colonne)
                        first_movement[0] = deplacements[i][0];
                        first_movement[1] = deplacements[i][1];
                        first_movement[2] = index;
                        //On verifie qu'il n'y a pas d'erreur
                        VerifAssertMove(first_movement);
                    }
                }
            }
            //Nettoie le vecteur deplacement
            NettoieVecteur(deplacements);
        }
    }
    //le tableau pass� en reference prend les valeur du meilleur mouvement
    tab[0] = first_movement[0];
    tab[1] = first_movement[1];
    tab[2] = first_movement[2];
}

//fonction principale qui appelle ABMax (appel�e dans Jeu) qui lance la recheche du mouvement avec les variable initialis�es.
void AlphaBeta::ABMinMax(const Plateau &plateau, int tab[3])
{
	AlphaBetaBigMax(plateau, -_SCORE, _SCORE, 1,m_couleur,tab);
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
