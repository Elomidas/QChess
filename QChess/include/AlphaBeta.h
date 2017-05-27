#ifndef ALPHABETA_H
#define ALPHABETA_H

#include "Piece.h"
#include "Plateau.h"

#define _NB_PIECES  12
#define    _PROF    3

class AlphaBeta
{
    public:
        AlphaBeta();
        AlphaBeta(Plateau &plateau, Couleur couleur);
        virtual ~AlphaBeta();

        Plateau Getplateau() { return m_plateau; }
        void Setplateau(Plateau val) { m_plateau = val; }

        Couleur Getcouleur() { return m_couleur; }
        void Setcouleur(Couleur couleur) { std::cout << "Couleur changee : " << couleur; m_couleur = couleur; }

        int Eval(Plateau plateau, Couleur couleur);

        //Retourne le mouvement � faire
        //contient [2] l'index de la piece, [1] la ligne [2] la colonne
        int* ABMinMax(Plateau plateau);
        int* ABMaxMove(Plateau* plateau, short int prof, int a, int b, int * move_env,int &index_move,Couleur couleur);
        int* ABMinMove(Plateau* plateau, short int prof, int a, int b, int * move_env,int &index_move,Couleur couleur);


        int AlphaBetaMax(Plateau plateau, int alpha, int beta, int prof, Couleur couleur );
        int AlphaBetaMin(Plateau plateau, int alpha, int beta, int prof, Couleur couleur );
        int *AlphaBetaBigMax(Plateau plateau,int alpha, int beta, int prof, Couleur couleur);
        void VerifAssertMove(int* move, std::string titre);
    protected:

    private:
        Plateau m_plateau;
        Couleur m_couleur;
};

#endif // ALPHABETA_H

